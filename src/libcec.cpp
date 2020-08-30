/**
 * libcec.cpp
 * By Andrew Brampton
 *
 * Notes:
 *   Turn off:
 *     SetInactiveView() // We don't want to be in control anymore
 *     StandbyDevices()  // We now turn off all devices
 *
 *   Turn on:
 *     PowerOnDevices()  // Turn on all devices
 *     SetActiveSource(m_configuration.deviceTypes[0]) // Enable us as Active source
 *
 *     SetOSDString(CECDEVICE_TV, CEC_DISPLAY_CONTROL_DISPLAY_FOR_DEFAULT_TIME, g_localizeStrings.Get(36016).c_str());
 *
 */
#include "libcec.h"
#include "hdmi.h"
#include "maps.h"

#include <cstdio>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <cassert>
#include <map>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using namespace CEC;
using namespace log4cplus;

using std::endl;
using std::map;
using std::ostream;
using std::string;
using std::hex;

// cecloader has to be after some #includes and using namespaces :(
using std::cout;
using std::cerr;
#include <libcec/cecloader.h>

static Logger logger = Logger::getInstance("libcec");

#define MAX_CEC_PORTS (CEC_MAX_HDMI_PORTNUMBER-CEC_MIN_HDMI_PORTNUMBER)

// We store a global handle, so we can use g_cec->ToString(..) in certain cases. This is a bit of a HACK :(
static ICECAdapter * g_cec = NULL;

void cecLogMessage(void *cbParam, const cec_log_message *message) {
	try {
		((CecCallback*) cbParam)->onCecLogMessage(*message);
	} catch (...) {}
}

void cecKeyPress(void *cbParam, const cec_keypress *key) {
	try {
		((CecCallback*) cbParam)->onCecKeyPress(*key);
	} catch (...) {}
}

void cecCommandReceived(void *cbParam, const cec_command *command) {
	try {
		((CecCallback*) cbParam)->onCecCommandReceived(*command);
	} catch (...) {}
}

void cecAlert(void *cbParam, const libcec_alert alert, const libcec_parameter param) {
	try {
		((CecCallback*) cbParam)->onCecAlert(alert, param);
	} catch (...) {}
}

void cecConfigurationChanged(void *cbParam, const libcec_configuration *configuration) {
	try {
		((CecCallback*) cbParam)->onCecConfigurationChanged(*configuration);
	} catch (...) {}
}

int cecMenuStateChanged(void *cbParam, const cec_menu_state menu_state) {
	try {
		return ((CecCallback*) cbParam)->onCecMenuStateChanged(menu_state);
	} catch (...) {}
	return 0;
}

void cecSourceActivated(void *cbParam, const cec_logical_address address, const uint8_t val) {
	try {
		return ((CecCallback*) cbParam)->onCecSourceActivated(address, val);
	} catch (...) {}
}

struct ICECAdapterDeleter : std::default_delete<ICECAdapter> {
	//ICECAdapterDeleter() = default;

	void operator()(ICECAdapter* ptr) const {
		if (ptr) {
			UnloadLibCec(ptr);
			g_cec = NULL;
		}
	}
};

/**
 * Redirects the stream buffer for a stream for the lifetime of this object
 */
class RedirectStreamBuffer {
private:
	std::ios & stream;
	std::streambuf * orig_sb;

public:
	RedirectStreamBuffer(std::ios &stream, std::streambuf * new_sb) : stream(stream) {
		orig_sb = stream.rdbuf( new_sb );
	}

	~RedirectStreamBuffer() {
		restore();
	}

	void restore() {
		stream.rdbuf( orig_sb );
	}
};

Cec::Cec(const char * name, CecCallback * callback)
{
	assert(name != NULL);
	assert(callback != NULL);

	config.Clear();

	strncpy(config.strDeviceName, name, sizeof(config.strDeviceName));
    //config.deviceTypes.Add(CEC_DEVICE_TYPE_TUNER);
	config.deviceTypes.Add(CEC_DEVICE_TYPE_RECORDING_DEVICE);


	callbacks.logMessage           = &::cecLogMessage;
	callbacks.keyPress             = &::cecKeyPress;
	callbacks.commandReceived      = &::cecCommandReceived;
	callbacks.configurationChanged = &::cecConfigurationChanged;
	callbacks.alert                = &::cecAlert;
	callbacks.menuStateChanged     = &::cecMenuStateChanged;
	callbacks.sourceActivated      = &::cecSourceActivated;

	config.callbackParam           = callback;
	config.callbacks               = &callbacks;
}

Cec::~Cec() {}

void Cec::init()
{
    if (!cec)
    {
        // LibCecInitialise is noisy, so we redirect cout to nowhere
        RedirectStreamBuffer redirect(cout, 0);
        g_cec = LibCecInitialise(&config);
        if (! g_cec) {
            throw std::runtime_error("Failed to initialise libCEC");
        }
        cec = std::unique_ptr<CEC::ICECAdapter>(g_cec, ICECAdapterDeleter());
        cec->InitVideoStandalone();
    }
}

CEC::cec_logical_address Cec::open(const std::string &name) {
	LOG4CPLUS_TRACE_STR(logger, "Cec::open()");
	int id = 0;

	init();

	// Search for adapters
	cec_adapter_descriptor devices[MAX_CEC_PORTS];

	uint8_t ret = cec->DetectAdapters(devices, MAX_CEC_PORTS);
	if (ret < 0) {
		throw std::runtime_error("Error occurred searching for adapters");
	}

	if (ret == 0) {
		throw std::runtime_error("No adapters found");
	}

	if( ! name.empty() )
	{
        LOG4CPLUS_INFO(logger, "Looking for " << name);
		for(id=0; id<ret; ++id)
		{
			if( name.compare(devices[id].strComPath) == 0 )
				break;
			if( name.compare(devices[id].strComName) == 0 )
				break;
		}
		if( id == ret )
		{
			throw std::runtime_error("adapter not found");
		}
	}

	// Just use the first found
	LOG4CPLUS_INFO(logger, "Opening " << devices[id].strComPath);

	if (!cec->Open(devices[id].strComName)) {
		throw std::runtime_error("Failed to open adapter");
	}

	LOG4CPLUS_INFO(logger, "Opened " << devices[id].strComPath);
	/* return logical address as negociated by libcec */
	return (cec->GetLogicalAddresses()).primary;
}

void Cec::close(bool makeInactive) {
	assert(cec);

    if (makeInactive){
        //cec->SetInactiveView();
    }
    cec->Close();
}

void Cec::setTargetAddress(const HDMI::address & address) {
	LOG4CPLUS_INFO(logger, "Physical Address is set to " << address.physical);
        config.iPhysicalAddress = address.physical;
	LOG4CPLUS_INFO(logger, "Base device is set to " << address.logical);
	config.baseDevice =  address.logical;
	LOG4CPLUS_INFO(logger, "HDMI port is set to " << (int)address.port);
	config.iHDMIPort = 2;
  
}

void Cec::waitTVready() {
    while (!cec->PollDevice(CECDEVICE_TV)) {
	//cout << "poll-status:" << cec->PollDevice(CECDEVICE_TV) << "\n";        
	sleep(1);
    }

    while (cec->GetDevicePowerStatus(CECDEVICE_TV) != CEC_POWER_STATUS_ON ) {
	//cout << "pwr-status:" << cec->ToString(cec->GetDevicePowerStatus(CECDEVICE_TV)) << "\n";        
	sleep(1);
    }
 
}

void Cec::makeActive() {
	assert(cec);

	if (!cec->SetActiveSource()) {
		throw std::runtime_error("Failed to become active");
	}
 
}
bool Cec::ping() {
	assert(cec);

    return cec->PingAdapter();
}


/**
 * Prints the name of all found adapters
 * This will close any open device!
 */
ostream & Cec::listDevices(ostream & out) {
	cec_adapter_descriptor devices[MAX_CEC_PORTS];

    init();

	int8_t ret = cec->DetectAdapters(devices, MAX_CEC_PORTS);
	if (ret < 0) {
		LOG4CPLUS_ERROR(logger, "Error occurred searching for adapters");
		return out;
	}

	if (ret == 0) {
		LOG4CPLUS_ERROR(logger, "No adapters found");
	}

	for (int8_t i = 0; i < ret; i++) {
		out << "[" << (int) i << "] port:" << devices[i].strComName << " path:" << devices[i].strComPath << endl;

		if (!cec->Open(devices[i].strComName)) {
			out << "\tFailed to open" << endl;
		}

		cec_logical_addresses devices = cec->GetActiveDevices();
		for (int j = 0; j < 16; j++) {
			if (devices[j]) {
				cec_logical_address logical_addres = (cec_logical_address) j;

                HDMI::physical_address physical_address(cec->GetDevicePhysicalAddress(logical_addres));
				string name = cec->GetDeviceOSDName(logical_addres);
				cec_vendor_id vendor = (cec_vendor_id) cec->GetDeviceVendorId(logical_addres);

				out << "\t"  << cec->ToString(logical_addres)
				    << " @ 0x" << hex << physical_address
				    << " "   << name << " (" << cec->ToString(vendor) << ")"
				    << endl;
			}
		}
	}
	return out;
}

std::ostream& operator<<(std::ostream &out, const cec_user_control_code code) {
  cec_code_map::left_const_iterator it;

	it = Maps::cecUserControlCodeName.left.find(code);
	if (it == Maps::cecUserControlCodeName.left.end()) {
		it = Maps::cecUserControlCodeName.left.find(CEC_USER_CONTROL_CODE_UNKNOWN);
		assert(it != Maps::cecUserControlCodeName.left.end());
	}

	return out << it->second;
}

std::ostream& operator<<(std::ostream &out, const cec_log_level & log) {
	if (log & CEC_LOG_ERROR)
		out << "E";
	if (log & CEC_LOG_WARNING)
		out << "W";
	if (log & CEC_LOG_NOTICE)
		out << "N";
	if (log & CEC_LOG_TRAFFIC)
		out << "T";
	if (log & CEC_LOG_DEBUG)
		out << "D";
	return out;
}

std::ostream& operator<<(std::ostream &out, const cec_log_message & message) {
	return out << message.time << " [" << message.level << "]" << message.message;
}

std::ostream& operator<<(std::ostream &out, const cec_keypress & key) {
	return out << "Key press: " << key.keycode << " for " << key.duration << "ms";
}

std::ostream& operator<<(std::ostream &out, const cec_command & cmd) {
	return out << "Command "
			<< cmd.initiator << "->" << cmd.destination
			<< "[" << (cmd.ack ? "A" : " ") << (cmd.eom ? "A" : " ") << "]"
			<< " " << cmd.opcode;
}

std::ostream& operator<<(std::ostream &out, const cec_opcode & opcode) {
	if (g_cec)
		return out << g_cec->ToString(opcode);
	return out << "UNKNOWN";
}

std::ostream& operator<<(std::ostream &out, const cec_logical_address & address) {
	if (g_cec)
		return out << g_cec->ToString(address);
	return out << "UNKNOWN";
}

std::ostream& operator<<(std::ostream &out, const libcec_configuration & configuration) {
	throw std::runtime_error("unsupported operator<<(std::ostream &out, const libcec_configuration & configuration)");
}
