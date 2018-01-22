libcec-daemon
=============
A simple daemon to connect libcec to uinput. That is, using your TV to control your PC!
by Andrew Brampton, Ben Klopfenstein, and others. Check out the git commit history!

Licence
=======
Currently under the GPL, but only because libcec (on which we depend) is under
the GPL. I have full intentions to relicence this project as BSD when libcec
changes to either LGPL, or I do not need to depend on it anymore.

Install
=======

This package can be installed on Ubuntu Xenial from a PPA:

https://launchpad.net/~benklop/+archive/ubuntu/mmc/

sudo add-apt-repository ppa:benklop/mmc
sudo apt-get update
sudo apt-get install libcec-daemon

Configure
=========

My (benklop's) fork of this project makes the keymapping fully configurable via a config file, which is installed at */etc/libcec-daemon.conf*. 
A line exists in the sample config for every available CEC key mapping. They may be set to Linux key event codes, as listed in [the Linux kernel source here](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h). Specifying a specific CEC input button twice with two different keycodes will make both those keys be pressed simultaneously.

It's important to note that although you may select any `KEY_` prefixed code present in that list, only codes with a value up to 254 are usable in X11 - [This article explains why](http://who-t.blogspot.com/2014/12/why-255-keycode-limit-in-x-is-real.html). Also note that even some of those codes don't actually work with certain applications even if they are passed by Xorg - MythTV (built with Qt) for example can only support the keys listed [in their documentation](http://doc.qt.io/qt-5/qt.html#Key-enum). That list is mostly the same as those with keycodes supported by the X11 protocol, but if you are experiencing odd behavior with a specific code, it helps to know that the world of keyboard behavior is not nearly as straightforward as one would assume. In general, however, any keycode in that file with an ID that is not prefixed by `0x___` should be ok.

A problematic config file might be:

```ini
[key_mapping]
SELECT = KEY_OK
UP = KEY_UP
DOWN = KEY_DOWN
LEFT = KEY_LEFT
RIGHT = KEY_RIGHT
RIGHT_UP = KEY_RIGHT
RIGHT_UP = KEY_UP
RIGHT_DOWN = KEY_RIGHT
RIGHT_DOWN = KEY_DOWN
LEFT_UP = KEY_LEFT
LEFT_UP = KEY_UP
LEFT_DOWN = KEY_LEFT
LEFT_DOWN = KEY_DOWN
ROOT_MENU = KEY_HOME
SETUP_MENU = KEY_SETUP
CONTENTS_MENU = KEY_MENU
FAVORITE_MENU = KEY_FAVORITES
EXIT = KEY_EXIT
...
```

 Note that several of these keybindings, like `KEY_OK`, seem like especially good choices based on name alone, but have values outside of the 0-254 range. `KEY_OK` has a hex [input evrent code](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h) of `0x160` which is [352 in decimal](https://www.google.com/search?q=0x160+in+decimal). Keybindings like this may work for some applications, but not likely for most.

A better mapping would be:

```ini
SELECT = KEY_KPENTER
UP = KEY_UP
DOWN = KEY_DOWN
LEFT = KEY_LEFT
RIGHT = KEY_RIGHT
RIGHT_UP = KEY_RIGHT
RIGHT_UP = KEY_UP
RIGHT_DOWN = KEY_RIGHT
RIGHT_DOWN = KEY_DOWN
LEFT_UP = KEY_LEFT
LEFT_UP = KEY_UP
LEFT_DOWN = KEY_LEFT
LEFT_DOWN = KEY_DOWN
ROOT_MENU = KEY_F13
SETUP_MENU = KEY_F14
CONTENTS_MENU = KEY_F15
FAVORITE_MENU = KEY_F16
EXIT = KEY_ESC
```
This mapping would work fine in Xorg so your favorite media applications could easily have their keybindings set up to follow this scheme.


build
=====
* Checkout the main source

```
git clone https://github.com/benklop/libcec-daemon
```

* Now we need some buildtools and libraries

```
sudo apt-get install build-essential cmake
sudo apt-get install libboost-program-options-dev libboost-thread-dev libboost-system-dev liblog4cplus-dev
```

* Also we need the libcec (version 4.x) libraries. Pulse eight provides east way to install

```
apt-get install libcec-dev libcec-platform-dev

# or manually build them:
wget http://packages.pulse-eight.net/ubuntu/install-libcec.sh
sudo bash install-libcec.sh
```

* Now build libcec-daemon
*Note that the systemd unit file expects the daemon to be in /usr/bin, not /usr/local/bin, so you need to specify the correct path if you expect it to work*

```
cd libcec-daemon
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .
make
```

* Install libcec-daemon

```
sudo make install
```

* libcec-daemon's systemd script and udev rules need the cec user and group:

```
sudo adduser --quiet --system --group --disabled-password --system --shell /bin/sh cec
```

* edit the configuration file to set up keybindings
*The config file does not yet allow setting anything other than keybindings. Any other settings still need to be set at the command line.*

```
sudo vi /etc/libcec-daemon.conf
```

Usage
====
```
Usage: libcec-daemon [options] [usb]

Allowed options:
  -h [ --help ]             show help message
  -V [ --version ]          show version (and exit)
  -d [ --daemon ]           daemon mode, run in background
  -l [ --list ]             list available CEC adapters and devices
  -v [ --verbose ]          verbose output (use -vv for more)
  -q [ --quiet ]            quiet output (print almost nothing)
  -a [ --donotactivate ]    do not activate device on startup
  --onstandby <path>        command to run on standby
  --onactivate <path>       command to run on activation
  --ondeactivate <path>     command to run on deactivation
  -p [ --port ] <a[.b.c.d]> HDMI port A or address A.B.C.D (overrides 
                            autodetected value)
  --usb <path>              USB adapter path (as shown by --list)

HDMI port A can be specified as tv.1 or av.1 for HDMI port 1 on respectively the
TV or a connected Audio System. 0 digit is optional for either port or physical
address, so that tv.0 is equivalent to just tv. Similarily, addresses such as
1, 1.0, 1.0.0 and 1.0.0.0 are also equivalent. Specifying 0 by itself is the same
as omitting the port argument, implying that the HDMI port will be autotected.
To summarize, to force libcec-daemon to manage TV HDMI port 1, the following
can be used:
      -p tv.1
      -p 1
      -p 1.0.0.0
The daemon will not work properly if it fails to detect the HDMI port, in which
case the port should be specified manually.

It is possible to run commands to react to a certain TV/AV events such as:
     - power off/standby event (--onstandby)
     - HDMI port switched in (--onactivate)
     - HDMI port switched out (--ondeactivate)
The <path> argument should specify a command or script that is executable by the
default shell for the user running libcec-daemon, usually /bin/sh for root user.
Typically, scripts would suspend/shutdown the host whenever a standby event is
received for power saving, and screensaver and/or media play/pause control could
be hooked to activation or deactivation events. Currently, The command is run
right after the event has occurred, therefore it cannot be invalidated/prevented
by the former returning an exit code other than 0 for example.

A libcec-daemon can be instantiated for each HDMI-CEC adapter available to the
host hardware, and the daemon will automatically use to the first detected one.
If more than one adapter is available, they should be specified by the usb
argument using either its sys-path or dev-path as listed by the --list argument.
```
