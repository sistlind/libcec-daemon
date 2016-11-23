/**
 * libcec-daemon
 * A simple daemon to connect libcec to uinput. That is, using your TV to control your PC! 
 * by Andrew Brampton
 *
 * TODO
 *
 */
#include "main.h"
#include "config.h"
#include "hdmi.h"

#define CEC_NAME    "linux PC"
#define UINPUT_NAME "libcec-daemon"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <csignal>
#include <cstdlib>
#include <vector>
#include <unistd.h>

#include <boost/program_options.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/thread.hpp>
#include "accumulator.hpp"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

using namespace CEC;
using namespace log4cplus;

using std::cout;
using std::cerr;
using std::endl;
using std::min;
using std::string;
using std::vector;
using std::queue;
using std::list;

static Logger logger = Logger::getInstance("main");
static boost::mutex libcec_sync;
static boost::condition_variable libcec_cond;
std::map<const std::string, int> Main::uinputKeyMap = Main::setupKeyMap();
const vector<list<__u16>> Main::uinputCecMap = Main::setupUinputMap();
enum
{
	COMMAND_STANDBY,
	COMMAND_ACTIVE,
	COMMAND_INACTIVE,
	COMMAND_RESTART,
	COMMAND_KEYPRESS,
	COMMAND_KEYRELEASE,
	COMMAND_EXIT,
};

Main & Main::instance() {
	// Singleton pattern so we can use main from a sighandle
	static Main main;
	return main;
}

Main::Main() : cec(getCecName(), this), uinput(UINPUT_NAME, uinputCecMap),
	makeActive(true), running(false), lastUInputKeys({ }), logicalAddress(CECDEVICE_UNKNOWN)
{
	LOG4CPLUS_TRACE_STR(logger, "Main::Main()");
}

Main::~Main() {
	LOG4CPLUS_TRACE_STR(logger, "Main::~Main()");
	stop();
}

void Main::loop(const string & device) {
	LOG4CPLUS_TRACE_STR(logger, "Main::loop()");

	struct sigaction action;

	action.sa_handler = &Main::signalHandler;
	action.sa_flags = SA_RESETHAND;
	sigemptyset(&action.sa_mask);

	int restart = false;

	do
	{
		/* Get logicalAddress after openning device */
		logicalAddress = cec.open(device);
		LOG4CPLUS_INFO(logger, "Address \"" << logicalAddress << "\"");
		if ( logicalAddress != CECDEVICE_UNKNOWN)
		    running = true;

		/* install signals */
		sigaction (SIGHUP,  &action, NULL);
		sigaction (SIGINT,  &action, NULL);
		sigaction (SIGTERM, &action, NULL);

		if (makeActive) {
			cec.makeActive();
		}

		do
		{
			boost::unique_lock<boost::mutex> libcec_lock(libcec_sync);

			while( running && !commands.empty() )
			{
				Command cmd = commands.front();
				switch( cmd.command )
				{
					case COMMAND_STANDBY:
						if( ! onStandbyCommand.empty() )
						{
							LOG4CPLUS_DEBUG(logger, "Standby: Running \"" << onStandbyCommand << "\"");
							int ret = system(onStandbyCommand.c_str());
                            if( ret )
                                LOG4CPLUS_ERROR(logger, "Standby command failed: " << ret);
							
						}
						else
						{
							onCecKeyPress( CEC_USER_CONTROL_CODE_POWER_OFF_FUNCTION );
						}
						break;
					case COMMAND_ACTIVE:
						makeActive = true;
						if( ! onActivateCommand.empty() )
						{
							LOG4CPLUS_DEBUG(logger, "Activated: Running \"" << onActivateCommand << "\"");
							int ret = system(onActivateCommand.c_str());
                            if( ret )
                                LOG4CPLUS_ERROR(logger, "Activate command failed: " << ret);
						}
						break;
					case COMMAND_INACTIVE:
						makeActive = false;
						if( ! onDeactivateCommand.empty() )
						{
							LOG4CPLUS_DEBUG(logger, "Deactivated: Running \"" << onDeactivateCommand << "\"");
							int ret = system(onDeactivateCommand.c_str());
                            if( ret )
                                LOG4CPLUS_ERROR(logger, "Deactivate command failed: " << ret);
						}
						break;
					case COMMAND_KEYPRESS:
						onCecKeyPress( cmd.keycode );
						break;
					case COMMAND_RESTART:
						running = false;
						restart = true;
						break;
					case COMMAND_EXIT:
						running = false;
						break;
				}
				commands.pop();
			}
			int retriesRemaining = 3;
			while( running && !libcec_cond.timed_wait(libcec_lock, boost::posix_time::seconds(43)) )
			{
				// Since libcec's CAdapterPingThread::Process() tries pinging 3 times before raising a
				// connection lost alert, lets also make 3 attempts otherwise we'll stop running
				// before our alert handling gets a chance to do its job
				bool pinged = false;
				if( retriesRemaining > 0 && !(pinged = cec.ping()) )
				{
					--retriesRemaining;
					boost::this_thread::sleep(boost::posix_time::milliseconds(CEC_DEFAULT_TRANSMIT_RETRY_WAIT));
				}
				else
				{
					running = pinged;
				}
			}
		}
		while( running );

		/* reset signals */
		signal (SIGHUP,  SIG_DFL);
		signal (SIGINT,  SIG_DFL);
		signal (SIGTERM, SIG_DFL);

		cec.close(!restart);
	}
	while( restart );
}

void Main::push(Command cmd) {
	boost::lock_guard<boost::mutex> lock(libcec_sync);
	if( running )
	{
		commands.push(cmd);
		libcec_cond.notify_one();
	}
}

void Main::stop() {
	LOG4CPLUS_TRACE_STR(logger, "Main::stop()");
	push(Command(COMMAND_EXIT));
}

void Main::restart() {
	LOG4CPLUS_TRACE_STR(logger, "Main::restart()");
	push(Command(COMMAND_RESTART));
}

void Main::listDevices() {
	LOG4CPLUS_TRACE_STR(logger, "Main::listDevices()");
	cec.listDevices(cout);
}

void Main::signalHandler(int sigNum) {
	LOG4CPLUS_DEBUG_STR(logger, "Main::signalHandler()");
	switch( sigNum )
	{
		case SIGHUP:
			Main::instance().restart();
			break;
		default:
			Main::instance().stop();
			break;
	}
}

char *Main::getCecName() {
	LOG4CPLUS_TRACE_STR(logger, "Main::getCecName()");
	if (gethostname(cec_name, HOST_NAME_MAX) < 0 ) {
		LOG4CPLUS_TRACE_STR(logger, "Main::getCecName()");
		strncpy(cec_name, CEC_NAME, sizeof(HOST_NAME_MAX));
	}

	return cec_name;
}

std::list<__u16> Main::lookupCecUinputMapping(CEC::cec_user_control_code symbol) {
    //lookup cec string in config
    string str = Cec::cecUserControlCodeName.find(symbol)->second;
    std::list<std::string> uinputKeys = lookupConfigMappings(str);
    std::list<__u16> uinputKeyCodes = {};
    
    for (auto iterator = uinputKeys.begin(), end = uinputKeys.end(); iterator != end; ++iterator) {
        uinputKeyCodes.emplace_back(uinputKeyMap.find(*iterator)->second);
    }
    
    return uinputKeyCodes;
}

//TODO: get this information from a config file instead of hardcoded here
std::list<std::string> Main::lookupConfigMappings(std::string cecName) {
    static std::map<const std::string, std::list<std::string>> uinputCecMap;

	if (uinputCecMap.empty()) {
		uinputCecMap["SELECT"                      ] = { "KEY_OK" };
		uinputCecMap["UP"                          ] = { "KEY_UP" };
		uinputCecMap["DOWN"                        ] = { "KEY_DOWN" };
		uinputCecMap["LEFT"                        ] = { "KEY_LEFT" };
		uinputCecMap["RIGHT"                       ] = { "KEY_RIGHT" };
		uinputCecMap["RIGHT_UP"                    ] = { "KEY_RIGHT", "KEY_UP" };
		uinputCecMap["RIGHT_DOWN"                  ] = { "KEY_RIGHT", "KEY_DOWN" };
		uinputCecMap["LEFT_UP"                     ] = { "KEY_LEFT", "KEY_UP" };
		uinputCecMap["LEFT_DOWN"                   ] = { "KEY_LEFT", "KEY_DOWN" };
		uinputCecMap["ROOT_MENU"                   ] = { "KEY_HOME" };
		uinputCecMap["SETUP_MENU"                  ] = { "KEY_SETUP" };
		uinputCecMap["CONTENTS_MENU"               ] = { "KEY_MENU" };
		uinputCecMap["FAVORITE_MENU"               ] = { "KEY_FAVORITES" };
		uinputCecMap["EXIT"                        ] = { "KEY_EXIT" };
		uinputCecMap["NUMBER0"                     ] = { "KEY_0" };
		uinputCecMap["NUMBER1"                     ] = { "KEY_1" };
		uinputCecMap["NUMBER2"                     ] = { "KEY_2" };
		uinputCecMap["NUMBER3"                     ] = { "KEY_3" };
		uinputCecMap["NUMBER4"                     ] = { "KEY_4" };
		uinputCecMap["NUMBER5"                     ] = { "KEY_5" };
		uinputCecMap["NUMBER6"                     ] = { "KEY_6" };
		uinputCecMap["NUMBER7"                     ] = { "KEY_7" };
		uinputCecMap["NUMBER8"                     ] = { "KEY_8" };
		uinputCecMap["NUMBER9"                     ] = { "KEY_9" };
		uinputCecMap["DOT"                         ] = { "KEY_DOT" };
		uinputCecMap["ENTER"                       ] = { "KEY_ENTER" };
		uinputCecMap["CLEAR"                       ] = { "KEY_BACKSPACE" };
		uinputCecMap["NEXT_FAVORITE"               ] = { };
		uinputCecMap["CHANNEL_UP"                  ] = { "KEY_CHANNELUP" };
		uinputCecMap["CHANNEL_DOWN"                ] = { "KEY_CHANNELDOWN" };
		uinputCecMap["PREVIOUS_CHANNEL"            ] = { "KEY_PREVIOUS" };
		uinputCecMap["SOUND_SELECT"                ] = { "KEY_SOUND" };
		uinputCecMap["INPUT_SELECT"                ] = { "KEY_TUNER" };
		uinputCecMap["DISPLAY_INFORMATION"         ] = { "KEY_INFO" };
		uinputCecMap["HELP"                        ] = { "KEY_HELP" };
		uinputCecMap["PAGE_UP"                     ] = { "KEY_PAGEUP" };
		uinputCecMap["PAGE_DOWN"                   ] = { "KEY_PAGEDOWN" };
		uinputCecMap["POWER"                       ] = { "KEY_POWER" };
		uinputCecMap["VOLUME_UP"                   ] = { "KEY_VOLUMEUP" };
		uinputCecMap["VOLUME_DOWN"                 ] = { "KEY_VOLUMEDOWN" };
		uinputCecMap["MUTE"                        ] = { "KEY_MUTE" };
		uinputCecMap["PLAY"                        ] = { "KEY_PLAY" };
		uinputCecMap["STOP"                        ] = { "KEY_STOP" };
		uinputCecMap["PAUSE"                       ] = { "KEY_PAUSE" };
		uinputCecMap["RECORD"                      ] = { "KEY_RECORD" };
		uinputCecMap["REWIND"                      ] = { "KEY_REWIND" };
		uinputCecMap["FAST_FORWARD"                ] = { "KEY_FASTFORWARD" };
		uinputCecMap["EJECT"                       ] = { "KEY_EJECTCD" };
		uinputCecMap["FORWARD"                     ] = { "KEY_FORWARD" };
		uinputCecMap["BACKWARD"                    ] = { "KEY_BACK" };
		uinputCecMap["STOP_RECORD"                 ] = { };
		uinputCecMap["PAUSE_RECORD"                ] = { };
		uinputCecMap["ANGLE"                       ] = { "KEY_SCREEN" };
		uinputCecMap["SUB_PICTURE"                 ] = { "KEY_SUBTITLE" };
		uinputCecMap["VIDEO_ON_DEMAND"             ] = { "KEY_VIDEO" };
		uinputCecMap["ELECTRONIC_PROGRAM_GUIDE"    ] = { "KEY_EPG" };
		uinputCecMap["TIMER_PROGRAMMING"           ] = { "KEY_TIME" };
		uinputCecMap["INITIAL_CONFIGURATION"       ] = { "KEY_CONFIG" };
		uinputCecMap["PLAY_FUNCTION"               ] = { };
		uinputCecMap["PAUSE_PLAY_FUNCTION"         ] = { };
		uinputCecMap["RECORD_FUNCTION"             ] = { };
		uinputCecMap["PAUSE_RECORD_FUNCTION"       ] = { };
		uinputCecMap["STOP_FUNCTION"               ] = { };
		uinputCecMap["MUTE_FUNCTION"               ] = { };
		uinputCecMap["RESTORE_VOLUME_FUNCTION"     ] = { };
		uinputCecMap["TUNE_FUNCTION"               ] = { };
		uinputCecMap["SELECT_MEDIA_FUNCTION"       ] = { "KEY_MEDIA" };
		uinputCecMap["SELECT_AV_INPUT_FUNCTION"    ] = { };
		uinputCecMap["SELECT_AUDIO_INPUT_FUNCTION" ] = { };
		uinputCecMap["POWER_TOGGLE_FUNCTION"       ] = { "KEY_POWER" };
		uinputCecMap["POWER_OFF_FUNCTION"          ] = { "KEY_POWER2" };
		uinputCecMap["POWER_ON_FUNCTION"           ] = { "KEY_WAKEUP" };
		uinputCecMap["F1_BLUE"                     ] = { "KEY_BLUE" };
		uinputCecMap["F2_RED"                      ] = { "KEY_RED" };
		uinputCecMap["F3_GREEN"                    ] = { "KEY_GREEN" };
		uinputCecMap["F4_YELLOW"                   ] = { "KEY_YELLOW" };
		uinputCecMap["F5"                          ] = { };
		uinputCecMap["DATA"                        ] = { "KEY_TEXT" };
		uinputCecMap["AN_RETURN"                   ] = { "KEY_ESC" };
		uinputCecMap["AN_CHANNELS_LIST"            ] = { "KEY_LIST" };
	}

	return uinputCecMap.find(cecName)->second;
}

const std::vector<list<__u16>> Main::setupUinputMap() {
    std::vector<list<__u16>> values;
    for (auto iterator = uinputKeyMap.begin(), end = uinputKeyMap.end(); iterator != end; ++iterator) {
       values.emplace_back(iterator[1]);
    }
    return values;
}

int Main::onCecLogMessage(const cec_log_message &message) {
	LOG4CPLUS_DEBUG(logger, "Main::onCecLogMessage(" << message << ")");
	return 1;
}

int Main::onCecKeyPress(const cec_keypress &key) {
	LOG4CPLUS_DEBUG(logger, "Main::onCecKeyPress(" << key << ")");

	// Check bounds and find uinput code for this cec keypress
	if (key.keycode >= 0 && key.keycode <= CEC_USER_CONTROL_CODE_MAX) {
		const list<__u16> & uinputKeys = lookupCecUinputMapping(key.keycode);

		if ( !uinputKeys.empty() ) {
			if( key.duration == 0 ) {
				if( uinputKeys == lastUInputKeys )
				{
					/*
					** KEY REPEAT
					*/
					for (std::list<__u16>::const_iterator ukeys = uinputKeys.begin(); ukeys != uinputKeys.end(); ++ukeys) {
						__u16 ukey = *ukeys;

						LOG4CPLUS_DEBUG(logger, "repeat " << ukey);

						uinput.send_event(EV_KEY, ukey, EV_KEY_REPEAT);
					}
				}
				else
				{
					/*
					** KEY PRESSED
					*/
					if( ! lastUInputKeys.empty() )
					{
						/* what happened with the last key release ? */
						for (std::list<__u16>::const_iterator ukeys = lastUInputKeys.begin(); ukeys != lastUInputKeys.end(); ++ukeys) {
							__u16 ukey = *ukeys;

							LOG4CPLUS_DEBUG(logger, "release " << ukey);

							uinput.send_event(EV_KEY, ukey, EV_KEY_RELEASED);
						}
					}
					for (std::list<__u16>::const_iterator ukeys = uinputKeys.begin(); ukeys != uinputKeys.end(); ++ukeys) {
						__u16 ukey = *ukeys;

						LOG4CPLUS_DEBUG(logger, "send " << ukey);

						uinput.send_event(EV_KEY, ukey, EV_KEY_PRESSED);
					}
					lastUInputKeys = uinputKeys;
				}
			}
			else {
				if( lastUInputKeys != uinputKeys ) {
					if( ! lastUInputKeys.empty() ) {
						/* what happened with the last key release ? */
						for (std::list<__u16>::const_iterator ukeys = lastUInputKeys.begin(); ukeys != lastUInputKeys.end(); ++ukeys) {
							__u16 ukey = *ukeys;

							LOG4CPLUS_DEBUG(logger, "release " << ukey);

							uinput.send_event(EV_KEY, ukey, EV_KEY_RELEASED);
						}
					}
					for (std::list<__u16>::const_iterator ukeys = uinputKeys.begin(); ukeys != uinputKeys.end(); ++ukeys) {
						__u16 ukey = *ukeys;

						LOG4CPLUS_DEBUG(logger, "send " << ukey);

						uinput.send_event(EV_KEY, ukey, EV_KEY_PRESSED);
					}
					boost::this_thread::sleep(boost::posix_time::milliseconds(100));
				}
				/*
				** KEY RELEASED
				*/
				for (std::list<__u16>::const_iterator ukeys = uinputKeys.begin(); ukeys != uinputKeys.end(); ++ukeys) {
					__u16 ukey = *ukeys;

					LOG4CPLUS_DEBUG(logger, "release " << ukey);

					uinput.send_event(EV_KEY, ukey, EV_KEY_RELEASED);

				}
				lastUInputKeys.clear();
			}
			uinput.sync();
		}
	}

	return 1;
}

int Main::onCecKeyPress(const cec_user_control_code & keycode) {
	cec_keypress key = { key.keycode=keycode };

	/* PUSH KEY */
	key.duration = 0;
	onCecKeyPress( key );

	/* simulate delay */
	key.duration = 100;
	boost::this_thread::sleep(boost::posix_time::milliseconds(key.duration));

	/* RELEASE KEY */
	onCecKeyPress( key );

	return 1;
}

int Main::onCecCommand(const cec_command & command) {
	LOG4CPLUS_DEBUG(logger, "Main::onCecCommand(" << command << ")");
	switch( command.opcode )
	{
		case CEC_OPCODE_STANDBY:
			if( (command.initiator == CECDEVICE_TV)
                         && ( (command.destination == CECDEVICE_BROADCAST) || (command.destination == logicalAddress))  )
			{
				push(Command(COMMAND_STANDBY));
			}
			break;
		case CEC_OPCODE_REQUEST_ACTIVE_SOURCE:
			if( (command.initiator == CECDEVICE_TV)
                         && ( (command.destination == CECDEVICE_BROADCAST) || (command.destination == logicalAddress))  )
			{
                if( makeActive )
                {
                    /* remind TV we are active */
                    push(Command(COMMAND_ACTIVE));
                }
			}
		case CEC_OPCODE_SET_MENU_LANGUAGE:
			if( (command.initiator == CECDEVICE_TV) && (command.parameters.size == 3)
                         && ( (command.destination == CECDEVICE_BROADCAST) || (command.destination == logicalAddress))  )
			{
				/* TODO */
			}
			break;
		case CEC_OPCODE_DECK_CONTROL:
			if( (command.initiator == CECDEVICE_TV) && (command.parameters.size == 1)
                         && ( (command.destination == CECDEVICE_BROADCAST) || (command.destination == logicalAddress))  )
			{
				if( command.parameters[0] == CEC_DECK_CONTROL_MODE_STOP ) {
					push(Command(COMMAND_KEYPRESS, CEC_USER_CONTROL_CODE_STOP));
				}
				else if( command.parameters[0] == CEC_DECK_CONTROL_MODE_SKIP_FORWARD_WIND ) {
					push(Command(COMMAND_KEYPRESS, CEC_USER_CONTROL_CODE_FAST_FORWARD));
				}
				else if( command.parameters[0] == CEC_DECK_CONTROL_MODE_SKIP_REVERSE_REWIND ) {
					push(Command(COMMAND_KEYPRESS, CEC_USER_CONTROL_CODE_REWIND));
				}
			}
			break;
		case CEC_OPCODE_PLAY:
			if( (command.initiator == CECDEVICE_TV) && (command.parameters.size == 1)
                         && ( (command.destination == CECDEVICE_BROADCAST) || (command.destination == logicalAddress))  )
			{
				if( command.parameters[0] == CEC_PLAY_MODE_PLAY_FORWARD ) {
					push(Command(COMMAND_KEYPRESS, CEC_USER_CONTROL_CODE_PLAY));
				}
				else if( command.parameters[0] == CEC_PLAY_MODE_PLAY_STILL ) {
					push(Command(COMMAND_KEYPRESS, CEC_USER_CONTROL_CODE_PAUSE));
				}
			}
			break;
		default:
			break;
	}
	return 1;
}

int Main::onCecAlert(const CEC::libcec_alert alert, const CEC::libcec_parameter & param) {
	LOG4CPLUS_ERROR(logger, "Main::onCecAlert(alert=" << alert << ")");
	switch( alert )
	{
		case CEC_ALERT_SERVICE_DEVICE:
			break;
		case CEC_ALERT_CONNECTION_LOST:
		case CEC_ALERT_PERMISSION_ERROR:
		case CEC_ALERT_PORT_BUSY:
		case CEC_ALERT_PHYSICAL_ADDRESS_ERROR:
		case CEC_ALERT_TV_POLL_FAILED:
			Main::instance().restart();
			break;
		default:
			break;
	}
	return 1;
}

int Main::onCecConfigurationChanged(const libcec_configuration & configuration) {
	//LOG4CPLUS_DEBUG(logger, "Main::onCecConfigurationChanged(" << configuration << ")");
	LOG4CPLUS_DEBUG(logger, "Main::onCecConfigurationChanged(logicalAddress=" << configuration.logicalAddresses.primary << ")");
	logicalAddress = configuration.logicalAddresses.primary;
	return 1;
}


int Main::onCecMenuStateChanged(const cec_menu_state & menu_state) {
	LOG4CPLUS_DEBUG(logger, "Main::onCecMenuStateChanged(" << menu_state << ")");

	return onCecKeyPress(CEC_USER_CONTROL_CODE_CONTENTS_MENU);
}

void Main::onCecSourceActivated(const cec_logical_address & address, bool bActivated) {
	LOG4CPLUS_DEBUG(logger, "Main::onCecSourceActivated(logicalAddress " << address << " = " << bActivated << ")");
	if( logicalAddress == address )
	{
		push(Command(bActivated ? COMMAND_ACTIVE : COMMAND_INACTIVE));
	}
}

#if defined(HAVE_BOOST_PO_TYPED_VALUE_NAME)

/*
** boost versions 1.50 and newer support value_name() program option value
*/

using boost::program_options::value;

#else

/*
** provide a value_name() replacement for older versions
*/

template<class T> class typed_value_name : public boost::program_options::typed_value<T>
{
    public:
        typed_value_name(T *my_value = new T()) : boost::program_options::typed_value<T>(my_value), val_name("arg") {};
        boost::program_options::typed_value<T> *value_name(const char *name) { val_name = name;; return this; };
        std::string name() const { return std::string(val_name); };

    protected:
        const char *val_name;
};

template<class T> typed_value_name<T> *value(T *my_value = new T()) { return new typed_value_name<T>(my_value); };

#endif

int main (int argc, char *argv[]) {

    BasicConfigurator config;
    config.configure();

    int loglevel = 0;

	namespace po = boost::program_options;

	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help,h",    "show help message")
	    ("version,V", "show version (and exit)")
	    ("daemon,d",  "daemon mode, run in background")
	    ("list,l",    "list available CEC adapters and devices")
	    ("verbose,v", accumulator<int>(&loglevel)->implicit_value(1), "verbose output (use -vv for more)")
	    ("quiet,q",   "quiet output (print almost nothing)")
	    ("donotactivate,a", "do not activate device on startup")

	    ("onstandby", value<string>()->value_name("<path>"),  "command to run on standby")
	    ("onactivate", value<string>()->value_name("<path>"),  "command to run on activation")
	    ("ondeactivate", value<string>()->value_name("<path>"),  "command to run on deactivation")
	    ("port,p", value<HDMI::address>()->value_name("<a[.b.c.d]>"),  "HDMI port A or address A.B.C.D (overrides autodetected value)")
	    ("usb", value<string>()->value_name("<path>"), "USB adapter path (as shown by --list)")
	;

	po::positional_options_description p;
	p.add("usb", 1);

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    }
    catch( po::error &e )
    {
        cerr << argv[0] << ": " << e.what() << endl;
        cerr << "Type \"" << argv[0] << " --help\" for more information." << endl;
        return 1;
    }
    po::notify(vm);

	if (vm.count("help")) {
		cout << "Usage: " << argv[0] << " [options] [usb]" << endl << endl;
	    cout << desc << endl;
	    return 0;
	}

	if (vm.count("version")) {
		cout << PACKAGE_STRING << endl;
		return 0;
	}

	if(vm.count("quiet")) {
		loglevel = -1;
	} else {
		loglevel = min(loglevel, 2);
	}

	Logger root = Logger::getRoot();
	switch (loglevel) {
		case 2:  root.setLogLevel(TRACE_LOG_LEVEL); break;
		case 1:  root.setLogLevel(DEBUG_LOG_LEVEL); break;
		default: root.setLogLevel(INFO_LOG_LEVEL); break;
		case -1: root.setLogLevel(FATAL_LOG_LEVEL); break;
	}

	try {
		// Create the main
		Main & main = Main::instance();
        string device = "";

		if (vm.count("list")) {
			main.listDevices();
			return 0;
		}

		if (vm.count("donotactivate")) {
			main.setMakeActive(false);
		}

		if (vm.count("usb")) {
			device = vm["usb"].as< string >();
		}

		if (vm.count("onstandby")) {
			main.setOnStandbyCommand(vm["onstandby"].as< string >());
		}

		if (vm.count("onactivate")) {
			main.setOnActivateCommand(vm["onactivate"].as< string >());
		}

		if (vm.count("ondeactivate")) {
			main.setOnDeactivateCommand(vm["ondeactivate"].as< string >());
		}

		if (vm.count("port")) {
            main.setTargetAddress(vm["port"].as< HDMI::address >());
        }

        if (vm.count("daemon")) {
            if( daemon(0, 0) )
                return -1;
        }

		main.loop(device);

	} catch (std::exception & e) {
		cerr << e.what() << endl;
		return -1;
	}

	return 0;
}

