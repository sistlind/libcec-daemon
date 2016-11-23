/*
 * Input event codes taken from the Linux kernel and trasformed with regex.
 *
 *    *** IMPORTANT ***
 * This file is not only included from C-code but also from devicetree source
 * files. As such this file MUST only contain comments and defines.
 *
 * original file:
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */

#ifndef maps
#define maps
#include "main.h"
#include <string>
#include <iostream>
#include <tr1/unordered_map>
#include <linux/input-event-codes.h>

using namespace CEC;

const std::tr1::unordered_map<std::string, int> & Main::setupKeyMap() {
 	const std::tr1::unordered_map<std::string, int> key_table;
 	if(key_table.empty()) {
		key_table["KEY_RESERVED"] = KEY_RESERVED;
		key_table["KEY_ESC"] = KEY_ESC;
		key_table["KEY_1"] = KEY_1;
		key_table["KEY_2"] = KEY_2;
		key_table["KEY_3"] = KEY_3;
		key_table["KEY_4"] = KEY_4;
		key_table["KEY_5"] = KEY_5;
		key_table["KEY_6"] = KEY_6;
		key_table["KEY_7"] = KEY_7;
		key_table["KEY_8"] = KEY_8;
		key_table["KEY_9"] = KEY_9;
		key_table["KEY_0"] = KEY_0;
		key_table["KEY_MINUS"] = KEY_MINUS;
		key_table["KEY_EQUAL"] = KEY_EQUAL;
		key_table["KEY_BACKSPACE"] = KEY_BACKSPACE;
		key_table["KEY_TAB"] = KEY_TAB;
		key_table["KEY_Q"] = KEY_Q;
		key_table["KEY_W"] = KEY_W;
		key_table["KEY_E"] = KEY_E;
		key_table["KEY_R"] = KEY_R;
		key_table["KEY_T"] = KEY_T;
		key_table["KEY_Y"] = KEY_Y;
		key_table["KEY_U"] = KEY_U;
		key_table["KEY_I"] = KEY_I;
		key_table["KEY_O"] = KEY_O;
		key_table["KEY_P"] = KEY_P;
		key_table["KEY_LEFTBRACE"] = KEY_LEFTBRACE;
		key_table["KEY_RIGHTBRACE"] = KEY_RIGHTBRACE;
		key_table["KEY_ENTER"] = KEY_ENTER;
		key_table["KEY_LEFTCTRL"] = KEY_LEFTCTRL;
		key_table["KEY_A"] = KEY_A;
		key_table["KEY_S"] = KEY_S;
		key_table["KEY_D"] = KEY_D;
		key_table["KEY_F"] = KEY_F;
		key_table["KEY_G"] = KEY_G;
		key_table["KEY_H"] = KEY_H;
		key_table["KEY_J"] = KEY_J;
		key_table["KEY_K"] = KEY_K;
		key_table["KEY_L"] = KEY_L;
		key_table["KEY_SEMICOLON"] = KEY_SEMICOLON;
		key_table["KEY_APOSTROPHE"] = KEY_APOSTROPHE;
		key_table["KEY_GRAVE"] = KEY_GRAVE;
		key_table["KEY_LEFTSHIFT"] = KEY_LEFTSHIFT;
		key_table["KEY_BACKSLASH"] = KEY_BACKSLASH;
		key_table["KEY_Z"] = KEY_Z;
		key_table["KEY_X"] = KEY_X;
		key_table["KEY_C"] = KEY_C;
		key_table["KEY_V"] = KEY_V;
		key_table["KEY_B"] = KEY_B;
		key_table["KEY_N"] = KEY_N;
		key_table["KEY_M"] = KEY_M;
		key_table["KEY_COMMA"] = KEY_COMMA;
		key_table["KEY_DOT"] = KEY_DOT;
		key_table["KEY_SLASH"] = KEY_SLASH;
		key_table["KEY_RIGHTSHIFT"] = KEY_RIGHTSHIFT;
		key_table["KEY_KPASTERISK"] = KEY_KPASTERISK;
		key_table["KEY_LEFTALT"] = KEY_LEFTALT;
		key_table["KEY_SPACE"] = KEY_SPACE;
		key_table["KEY_CAPSLOCK"] = KEY_CAPSLOCK;
		key_table["KEY_F1"] = KEY_F1;
		key_table["KEY_F2"] = KEY_F2;
		key_table["KEY_F3"] = KEY_F3;
		key_table["KEY_F4"] = KEY_F4;
		key_table["KEY_F5"] = KEY_F5;
		key_table["KEY_F6"] = KEY_F6;
		key_table["KEY_F7"] = KEY_F7;
		key_table["KEY_F8"] = KEY_F8;
		key_table["KEY_F9"] = KEY_F9;
		key_table["KEY_F10"] = KEY_F10;
		key_table["KEY_NUMLOCK"] = KEY_NUMLOCK;
		key_table["KEY_SCROLLLOCK"] = KEY_SCROLLLOCK;
		key_table["KEY_KP7"] = KEY_KP7;
		key_table["KEY_KP8"] = KEY_KP8;
		key_table["KEY_KP9"] = KEY_KP9;
		key_table["KEY_KPMINUS"] = KEY_KPMINUS;
		key_table["KEY_KP4"] = KEY_KP4;
		key_table["KEY_KP5"] = KEY_KP5;
		key_table["KEY_KP6"] = KEY_KP6;
		key_table["KEY_KPPLUS"] = KEY_KPPLUS;
		key_table["KEY_KP1"] = KEY_KP1;
		key_table["KEY_KP2"] = KEY_KP2;
		key_table["KEY_KP3"] = KEY_KP3;
		key_table["KEY_KP0"] = KEY_KP0;
		key_table["KEY_KPDOT"] = KEY_KPDOT;

		key_table["KEY_ZENKAKUHANKAKU"] = KEY_ZENKAKUHANKAKU;
		key_table["KEY_102ND"] = KEY_102ND;
		key_table["KEY_F11"] = KEY_F11;
		key_table["KEY_F12"] = KEY_F12;
		key_table["KEY_RO"] = KEY_RO;
		key_table["KEY_KATAKANA"] = KEY_KATAKANA;
		key_table["KEY_HIRAGANA"] = KEY_HIRAGANA;
		key_table["KEY_HENKAN"] = KEY_HENKAN;
		key_table["KEY_KATAKANAHIRAGANA"] = KEY_KATAKANAHIRAGANA;
		key_table["KEY_MUHENKAN"] = KEY_MUHENKAN;
		key_table["KEY_KPJPCOMMA"] = KEY_KPJPCOMMA;
		key_table["KEY_KPENTER"] = KEY_KPENTER;
		key_table["KEY_RIGHTCTRL"] = KEY_RIGHTCTRL;
		key_table["KEY_KPSLASH"] = KEY_KPSLASH;
		key_table["KEY_SYSRQ"] = KEY_SYSRQ;
		key_table["KEY_RIGHTALT"] = KEY_RIGHTALT;
		key_table["KEY_LINEFEED"] = KEY_LINEFEED;
		key_table["KEY_HOME"] = KEY_HOME;
		key_table["KEY_UP"] = KEY_UP;
		key_table["KEY_PAGEUP"] = KEY_PAGEUP;
		key_table["KEY_LEFT"] = KEY_LEFT;
		key_table["KEY_RIGHT"] = KEY_RIGHT;
		key_table["KEY_END"] = KEY_END;
		key_table["KEY_DOWN"] = KEY_DOWN;
		key_table["KEY_PAGEDOWN"] = KEY_PAGEDOWN;
		key_table["KEY_INSERT"] = KEY_INSERT;
		key_table["KEY_DELETE"] = KEY_DELETE;
		key_table["KEY_MACRO"] = KEY_MACRO;
		key_table["KEY_MUTE"] = KEY_MUTE;
		key_table["KEY_VOLUMEDOWN"] = KEY_VOLUMEDOWN;
		key_table["KEY_VOLUMEUP"] = KEY_VOLUMEUP;
		key_table["KEY_POWER"] = KEY_POWER; /* SC System Power Down */
		key_table["KEY_KPEQUAL"] = KEY_KPEQUAL;
		key_table["KEY_KPPLUSMINUS"] = KEY_KPPLUSMINUS;
		key_table["KEY_PAUSE"] = KEY_PAUSE;
		key_table["KEY_SCALE"] = KEY_SCALE; /* AL Compiz Scale (Expose) */

		key_table["KEY_KPCOMMA"] = KEY_KPCOMMA;
		key_table["KEY_HANGEUL"] = KEY_HANGEUL;
		key_table["KEY_HANGUEL"] = KEY_HANGUEL;
		key_table["KEY_HANJA"] = KEY_HANJA;
		key_table["KEY_YEN"] = KEY_YEN;
		key_table["KEY_LEFTMETA"] = KEY_LEFTMETA;
		key_table["KEY_RIGHTMETA"] = KEY_RIGHTMETA;
		key_table["KEY_COMPOSE"] = KEY_COMPOSE;

		key_table["KEY_STOP"] = KEY_STOP; /* AC Stop */
		key_table["KEY_AGAIN"] = KEY_AGAIN;
		key_table["KEY_PROPS"] = KEY_PROPS; /* AC Properties */
		key_table["KEY_UNDO"] = KEY_UNDO; /* AC Undo */
		key_table["KEY_FRONT"] = KEY_FRONT;
		key_table["KEY_COPY"] = KEY_COPY; /* AC Copy */
		key_table["KEY_OPEN"] = KEY_OPEN; /* AC Open */
		key_table["KEY_PASTE"] = KEY_PASTE; /* AC Paste */
		key_table["KEY_FIND"] = KEY_FIND; /* AC Search */
		key_table["KEY_CUT"] = KEY_CUT; /* AC Cut */
		key_table["KEY_HELP"] = KEY_HELP; /* AL Integrated Help Center */
		key_table["KEY_MENU"] = KEY_MENU; /* Menu (show menu) */
		key_table["KEY_CALC"] = KEY_CALC; /* AL Calculator */
		key_table["KEY_SETUP"] = KEY_SETUP;
		key_table["KEY_SLEEP"] = KEY_SLEEP; /* SC System Sleep */
		key_table["KEY_WAKEUP"] = KEY_WAKEUP; /* System Wake Up */
		key_table["KEY_FILE"] = KEY_FILE; /* AL Local Machine Browser */
		key_table["KEY_SENDFILE"] = KEY_SENDFILE;
		key_table["KEY_DELETEFILE"] = KEY_DELETEFILE;
		key_table["KEY_XFER"] = KEY_XFER;
		key_table["KEY_PROG1"] = KEY_PROG1;
		key_table["KEY_PROG2"] = KEY_PROG2;
		key_table["KEY_WWW"] = KEY_WWW; /* AL Internet Browser */
		key_table["KEY_MSDOS"] = KEY_MSDOS;
		key_table["KEY_COFFEE"] = KEY_COFFEE; /* AL Terminal Lock/Screensaver */
		key_table["KEY_SCREENLOCK"] = KEY_SCREENLOCK;
		key_table["KEY_ROTATE_DISPLAY"] = KEY_ROTATE_DISPLAY; /* Display orientation for e.g. key_tablets */
		key_table["KEY_DIRECTION"] = KEY_DIRECTION;
		key_table["KEY_CYCLEWINDOWS"] = KEY_CYCLEWINDOWS;
		key_table["KEY_MAIL"] = KEY_MAIL;
		key_table["KEY_BOOKMARKS"] = KEY_BOOKMARKS; /* AC Bookmarks */
		key_table["KEY_COMPUTER"] = KEY_COMPUTER;
		key_table["KEY_BACK"] = KEY_BACK; /* AC Back */
		key_table["KEY_FORWARD"] = KEY_FORWARD; /* AC Forward */
		key_table["KEY_CLOSECD"] = KEY_CLOSECD;
		key_table["KEY_EJECTCD"] = KEY_EJECTCD;
		key_table["KEY_EJECTCLOSECD"] = KEY_EJECTCLOSECD;
		key_table["KEY_NEXTSONG"] = KEY_NEXTSONG;
		key_table["KEY_PLAYPAUSE"] = KEY_PLAYPAUSE;
		key_table["KEY_PREVIOUSSONG"] = KEY_PREVIOUSSONG;
		key_table["KEY_STOPCD"] = KEY_STOPCD;
		key_table["KEY_RECORD"] = KEY_RECORD;
		key_table["KEY_REWIND"] = KEY_REWIND;
		key_table["KEY_PHONE"] = KEY_PHONE; /* Media Select Telephone */
		key_table["KEY_ISO"] = KEY_ISO;
		key_table["KEY_CONFIG"] = KEY_CONFIG; /* AL Consumer Control Configuration */
		key_table["KEY_HOMEPAGE"] = KEY_HOMEPAGE; /* AC Home */
		key_table["KEY_REFRESH"] = KEY_REFRESH; /* AC Refresh */
		key_table["KEY_EXIT"] = KEY_EXIT; /* AC Exit */
		key_table["KEY_MOVE"] = KEY_MOVE;
		key_table["KEY_EDIT"] = KEY_EDIT;
		key_table["KEY_SCROLLUP"] = KEY_SCROLLUP;
		key_table["KEY_SCROLLDOWN"] = KEY_SCROLLDOWN;
		key_table["KEY_KPLEFTPAREN"] = KEY_KPLEFTPAREN;
		key_table["KEY_KPRIGHTPAREN"] = KEY_KPRIGHTPAREN;
		key_table["KEY_NEW"] = KEY_NEW; /* AC New */
		key_table["KEY_REDO"] = KEY_REDO; /* AC Redo/Repeat */

		key_table["KEY_F13"] = KEY_F13;
		key_table["KEY_F14"] = KEY_F14;
		key_table["KEY_F15"] = KEY_F15;
		key_table["KEY_F16"] = KEY_F16;
		key_table["KEY_F17"] = KEY_F17;
		key_table["KEY_F18"] = KEY_F18;
		key_table["KEY_F19"] = KEY_F19;
		key_table["KEY_F20"] = KEY_F20;
		key_table["KEY_F21"] = KEY_F21;
		key_table["KEY_F22"] = KEY_F22;
		key_table["KEY_F23"] = KEY_F23;
		key_table["KEY_F24"] = KEY_F24;

		key_table["KEY_PLAYCD"] = KEY_PLAYCD;
		key_table["KEY_PAUSECD"] = KEY_PAUSECD;
		key_table["KEY_PROG3"] = KEY_PROG3;
		key_table["KEY_PROG4"] = KEY_PROG4;
		key_table["KEY_DASHBOARD"] = KEY_DASHBOARD; /* AL Dashboard */
		key_table["KEY_SUSPEND"] = KEY_SUSPEND;
		key_table["KEY_CLOSE"] = KEY_CLOSE; /* AC Close */
		key_table["KEY_PLAY"] = KEY_PLAY;
		key_table["KEY_FASTFORWARD"] = KEY_FASTFORWARD;
		key_table["KEY_BASSBOOST"] = KEY_BASSBOOST;
		key_table["KEY_PRINT"] = KEY_PRINT; /* AC Print */
		key_table["KEY_HP"] = KEY_HP;
		key_table["KEY_CAMERA"] = KEY_CAMERA;
		key_table["KEY_SOUND"] = KEY_SOUND;
		key_table["KEY_QUESTION"] = KEY_QUESTION;
		key_table["KEY_EMAIL"] = KEY_EMAIL;
		key_table["KEY_CHAT"] = KEY_CHAT;
		key_table["KEY_SEARCH"] = KEY_SEARCH;
		key_table["KEY_CONNECT"] = KEY_CONNECT;
		key_table["KEY_FINANCE"] = KEY_FINANCE; /* AL Checkbook/Finance */
		key_table["KEY_SPORT"] = KEY_SPORT;
		key_table["KEY_SHOP"] = KEY_SHOP;
		key_table["KEY_ALTERASE"] = KEY_ALTERASE;
		key_table["KEY_CANCEL"] = KEY_CANCEL; /* AC Cancel */
		key_table["KEY_BRIGHTNESSDOWN"] = KEY_BRIGHTNESSDOWN;
		key_table["KEY_BRIGHTNESSUP"] = KEY_BRIGHTNESSUP;
		key_table["KEY_MEDIA"] = KEY_MEDIA;

		key_table["KEY_SWITCHVIDEOMODE"] = KEY_SWITCHVIDEOMODE; /* Cycle between available video
		             outputs (Monitor/LCD/TV-out/etc) */
		key_table["KEY_KBDILLUMTOGGLE"] = KEY_KBDILLUMTOGGLE;
		key_table["KEY_KBDILLUMDOWN"] = KEY_KBDILLUMDOWN;
		key_table["KEY_KBDILLUMUP"] = KEY_KBDILLUMUP;

		key_table["KEY_SEND"] = KEY_SEND; /* AC Send */
		key_table["KEY_REPLY"] = KEY_REPLY; /* AC Reply */
		key_table["KEY_FORWARDMAIL"] = KEY_FORWARDMAIL; /* AC Forward Msg */
		key_table["KEY_SAVE"] = KEY_SAVE; /* AC Save */
		key_table["KEY_DOCUMENTS"] = KEY_DOCUMENTS;

		key_table["KEY_BATTERY"] = KEY_BATTERY;

		key_table["KEY_BLUETOOTH"] = KEY_BLUETOOTH;
		key_table["KEY_WLAN"] = KEY_WLAN;
		key_table["KEY_UWB"] = KEY_UWB;

		key_table["KEY_UNKNOWN"] = KEY_UNKNOWN;

		key_table["KEY_VIDEO_NEXT"] = KEY_VIDEO_NEXT; /* drive next video source */
		key_table["KEY_VIDEO_PREV"] = KEY_VIDEO_PREV; /* drive previous video source */
		key_table["KEY_BRIGHTNESS_CYCLE"] = KEY_BRIGHTNESS_CYCLE; /* brightness up, after max is min */
		key_table["KEY_BRIGHTNESS_AUTO"] = KEY_BRIGHTNESS_AUTO; /* Set Auto Brightness: manual
		            brightness control is off,
		            rely on ambient */
		key_table["KEY_BRIGHTNESS_ZERO"] = KEY_BRIGHTNESS_ZERO;
		key_table["KEY_DISPLAY_OFF"] = KEY_DISPLAY_OFF; /* display device to off state */

		key_table["KEY_WWAN"] = KEY_WWAN; /* Wireless WAN (LTE, UMTS, GSM, etc.) */
		key_table["KEY_WIMAX"] = KEY_WIMAX;
		key_table["KEY_RFKILL"] = KEY_RFKILL; /* Key that controls all radios */

		key_table["KEY_MICMUTE"] = KEY_MICMUTE; /* Mute / unmute the microphone */

		/* Code 255 is reserved for special needs of AT keyboard driver */

		key_table["BTN_MISC"] = BTN_MISC;
		key_table["BTN_0"] = BTN_0;
		key_table["BTN_1"] = BTN_1;
		key_table["BTN_2"] = BTN_2;
		key_table["BTN_3"] = BTN_3;
		key_table["BTN_4"] = BTN_4;
		key_table["BTN_5"] = BTN_5;
		key_table["BTN_6"] = BTN_6;
		key_table["BTN_7"] = BTN_7;
		key_table["BTN_8"] = BTN_8;
		key_table["BTN_9"] = BTN_9;

		key_table["BTN_MOUSE"] = BTN_MOUSE;
		key_table["BTN_LEFT"] = BTN_LEFT;
		key_table["BTN_RIGHT"] = BTN_RIGHT;
		key_table["BTN_MIDDLE"] = BTN_MIDDLE;
		key_table["BTN_SIDE"] = BTN_SIDE;
		key_table["BTN_EXTRA"] = BTN_EXTRA;
		key_table["BTN_FORWARD"] = BTN_FORWARD;
		key_table["BTN_BACK"] = BTN_BACK;
		key_table["BTN_TASK"] = BTN_TASK;

		key_table["BTN_JOYSTICK"] = BTN_JOYSTICK;
		key_table["BTN_TRIGGER"] = BTN_TRIGGER;
		key_table["BTN_THUMB"] = BTN_THUMB;
		key_table["BTN_THUMB2"] = BTN_THUMB2;
		key_table["BTN_TOP"] = BTN_TOP;
		key_table["BTN_TOP2"] = BTN_TOP2;
		key_table["BTN_PINKIE"] = BTN_PINKIE;
		key_table["BTN_BASE"] = BTN_BASE;
		key_table["BTN_BASE2"] = BTN_BASE2;
		key_table["BTN_BASE3"] = BTN_BASE3;
		key_table["BTN_BASE4"] = BTN_BASE4;
		key_table["BTN_BASE5"] = BTN_BASE5;
		key_table["BTN_BASE6"] = BTN_BASE6;
		key_table["BTN_DEAD"] = BTN_DEAD;

		key_table["BTN_GAMEPAD"] = BTN_GAMEPAD;
		key_table["BTN_SOUTH"] = BTN_SOUTH;
		key_table["BTN_A"] = BTN_A;
		key_table["BTN_EAST"] = BTN_EAST;
		key_table["BTN_B"] = BTN_B;
		key_table["BTN_C"] = BTN_C;
		key_table["BTN_NORTH"] = BTN_NORTH;
		key_table["BTN_X"] = BTN_X;
		key_table["BTN_WEST"] = BTN_WEST;
		key_table["BTN_Y"] = BTN_Y;
		key_table["BTN_Z"] = BTN_Z;
		key_table["BTN_TL"] = BTN_TL;
		key_table["BTN_TR"] = BTN_TR;
		key_table["BTN_TL2"] = BTN_TL2;
		key_table["BTN_TR2"] = BTN_TR2;
		key_table["BTN_SELECT"] = BTN_SELECT;
		key_table["BTN_START"] = BTN_START;
		key_table["BTN_MODE"] = BTN_MODE;
		key_table["BTN_THUMBL"] = BTN_THUMBL;
		key_table["BTN_THUMBR"] = BTN_THUMBR;

		key_table["BTN_DIGI"] = BTN_DIGI;
		key_table["BTN_TOOL_PEN"] = BTN_TOOL_PEN;
		key_table["BTN_TOOL_RUBBER"] = BTN_TOOL_RUBBER;
		key_table["BTN_TOOL_BRUSH"] = BTN_TOOL_BRUSH;
		key_table["BTN_TOOL_PENCIL"] = BTN_TOOL_PENCIL;
		key_table["BTN_TOOL_AIRBRUSH"] = BTN_TOOL_AIRBRUSH;
		key_table["BTN_TOOL_FINGER"] = BTN_TOOL_FINGER;
		key_table["BTN_TOOL_MOUSE"] = BTN_TOOL_MOUSE;
		key_table["BTN_TOOL_LENS"] = BTN_TOOL_LENS;
		key_table["BTN_TOOL_QUINTTAP"] = BTN_TOOL_QUINTTAP; /* Five fingers on trackpad */
		key_table["BTN_TOUCH"] = BTN_TOUCH;
		key_table["BTN_STYLUS"] = BTN_STYLUS;
		key_table["BTN_STYLUS2"] = BTN_STYLUS2;
		key_table["BTN_TOOL_DOUBLETAP"] = BTN_TOOL_DOUBLETAP;
		key_table["BTN_TOOL_TRIPLETAP"] = BTN_TOOL_TRIPLETAP;
		key_table["BTN_TOOL_QUADTAP"] = BTN_TOOL_QUADTAP; /* Four fingers on trackpad */

		key_table["BTN_WHEEL"] = BTN_WHEEL;
		key_table["BTN_GEAR_DOWN"] = BTN_GEAR_DOWN;
		key_table["BTN_GEAR_UP"] = BTN_GEAR_UP;

		key_table["KEY_OK"] = KEY_OK;
		key_table["KEY_SELECT"] = KEY_SELECT;
		key_table["KEY_GOTO"] = KEY_GOTO;
		key_table["KEY_CLEAR"] = KEY_CLEAR;
		key_table["KEY_POWER2"] = KEY_POWER2;
		key_table["KEY_OPTION"] = KEY_OPTION;
		key_table["KEY_INFO"] = KEY_INFO; /* AL OEM Features/Tips/Tutorial */
		key_table["KEY_TIME"] = KEY_TIME;
		key_table["KEY_VENDOR"] = KEY_VENDOR;
		key_table["KEY_ARCHIVE"] = KEY_ARCHIVE;
		key_table["KEY_PROGRAM"] = KEY_PROGRAM; /* Media Select Program Guide */
		key_table["KEY_CHANNEL"] = KEY_CHANNEL;
		key_table["KEY_FAVORITES"] = KEY_FAVORITES;
		key_table["KEY_EPG"] = KEY_EPG;
		key_table["KEY_PVR"] = KEY_PVR; /* Media Select Home */
		key_table["KEY_MHP"] = KEY_MHP;
		key_table["KEY_LANGUAGE"] = KEY_LANGUAGE;
		key_table["KEY_TITLE"] = KEY_TITLE;
		key_table["KEY_SUBTITLE"] = KEY_SUBTITLE;
		key_table["KEY_ANGLE"] = KEY_ANGLE;
		key_table["KEY_ZOOM"] = KEY_ZOOM;
		key_table["KEY_MODE"] = KEY_MODE;
		key_table["KEY_KEYBOARD"] = KEY_KEYBOARD;
		key_table["KEY_SCREEN"] = KEY_SCREEN;
		key_table["KEY_PC"] = KEY_PC; /* Media Select Computer */
		key_table["KEY_TV"] = KEY_TV; /* Media Select TV */
		key_table["KEY_TV2"] = KEY_TV2; /* Media Select Cable */
		key_table["KEY_VCR"] = KEY_VCR; /* Media Select VCR */
		key_table["KEY_VCR2"] = KEY_VCR2; /* VCR Plus */
		key_table["KEY_SAT"] = KEY_SAT; /* Media Select Satellite */
		key_table["KEY_SAT2"] = KEY_SAT2;
		key_table["KEY_CD"] = KEY_CD; /* Media Select CD */
		key_table["KEY_TAPE"] = KEY_TAPE; /* Media Select Tape */
		key_table["KEY_RADIO"] = KEY_RADIO;
		key_table["KEY_TUNER"] = KEY_TUNER; /* Media Select Tuner */
		key_table["KEY_PLAYER"] = KEY_PLAYER;
		key_table["KEY_TEXT"] = KEY_TEXT;
		key_table["KEY_DVD"] = KEY_DVD; /* Media Select DVD */
		key_table["KEY_AUX"] = KEY_AUX;
		key_table["KEY_MP3"] = KEY_MP3;
		key_table["KEY_AUDIO"] = KEY_AUDIO; /* AL Audio Browser */
		key_table["KEY_VIDEO"] = KEY_VIDEO; /* AL Movie Browser */
		key_table["KEY_DIRECTORY"] = KEY_DIRECTORY;
		key_table["KEY_LIST"] = KEY_LIST;
		key_table["KEY_MEMO"] = KEY_MEMO; /* Media Select Messages */
		key_table["KEY_CALENDAR"] = KEY_CALENDAR;
		key_table["KEY_RED"] = KEY_RED;
		key_table["KEY_GREEN"] = KEY_GREEN;
		key_table["KEY_YELLOW"] = KEY_YELLOW;
		key_table["KEY_BLUE"] = KEY_BLUE;
		key_table["KEY_CHANNELUP"] = KEY_CHANNELUP; /* Channel Increment */
		key_table["KEY_CHANNELDOWN"] = KEY_CHANNELDOWN; /* Channel Decrement */
		key_table["KEY_FIRST"] = KEY_FIRST;
		key_table["KEY_LAST"] = KEY_LAST; /* Recall Last */
		key_table["KEY_AB"] = KEY_AB;
		key_table["KEY_NEXT"] = KEY_NEXT;
		key_table["KEY_RESTART"] = KEY_RESTART;
		key_table["KEY_SLOW"] = KEY_SLOW;
		key_table["KEY_SHUFFLE"] = KEY_SHUFFLE;
		key_table["KEY_BREAK"] = KEY_BREAK;
		key_table["KEY_PREVIOUS"] = KEY_PREVIOUS;
		key_table["KEY_DIGITS"] = KEY_DIGITS;
		key_table["KEY_TEEN"] = KEY_TEEN;
		key_table["KEY_TWEN"] = KEY_TWEN;
		key_table["KEY_VIDEOPHONE"] = KEY_VIDEOPHONE; /* Media Select Video Phone */
		key_table["KEY_GAMES"] = KEY_GAMES; /* Media Select Games */
		key_table["KEY_ZOOMIN"] = KEY_ZOOMIN; /* AC Zoom In */
		key_table["KEY_ZOOMOUT"] = KEY_ZOOMOUT; /* AC Zoom Out */
		key_table["KEY_ZOOMRESET"] = KEY_ZOOMRESET; /* AC Zoom */
		key_table["KEY_WORDPROCESSOR"] = KEY_WORDPROCESSOR; /* AL Word Processor */
		key_table["KEY_EDITOR"] = KEY_EDITOR; /* AL Text Editor */
		key_table["KEY_SPREADSHEET"] = KEY_SPREADSHEET; /* AL Spreadsheet */
		key_table["KEY_GRAPHICSEDITOR"] = KEY_GRAPHICSEDITOR; /* AL Graphics Editor */
		key_table["KEY_PRESENTATION"] = KEY_PRESENTATION; /* AL Presentation App */
		key_table["KEY_DATABASE"] = KEY_DATABASE; /* AL Database App */
		key_table["KEY_NEWS"] = KEY_NEWS; /* AL Newsreader */
		key_table["KEY_VOICEMAIL"] = KEY_VOICEMAIL; /* AL Voicemail */
		key_table["KEY_ADDRESSBOOK"] = KEY_ADDRESSBOOK; /* AL Contacts/Address Book */
		key_table["KEY_MESSENGER"] = KEY_MESSENGER; /* AL Instant Messaging */
		key_table["KEY_DISPLAYTOGGLE"] = KEY_DISPLAYTOGGLE; /* Turn display (LCD) on and off */
		key_table["KEY_BRIGHTNESS_TOGGLE"] = KEY_BRIGHTNESS_TOGGLE;
		key_table["KEY_SPELLCHECK"] = KEY_SPELLCHECK;   /* AL Spell Check */
		key_table["KEY_LOGOFF"] = KEY_LOGOFF;   /* AL Logoff */

		key_table["KEY_DOLLAR"] = KEY_DOLLAR;
		key_table["KEY_EURO"] = KEY_EURO;

		key_table["KEY_FRAMEBACK"] = KEY_FRAMEBACK; /* Consumer - transport controls */
		key_table["KEY_FRAMEFORWARD"] = KEY_FRAMEFORWARD;
		key_table["KEY_CONTEXT_MENU"] = KEY_CONTEXT_MENU; /* GenDesc - system context menu */
		key_table["KEY_MEDIA_REPEAT"] = KEY_MEDIA_REPEAT; /* Consumer - transport control */
		key_table["KEY_10CHANNELSUP"] = KEY_10CHANNELSUP; /* 10 channels up (10+) */
		key_table["KEY_10CHANNELSDOWN"] = KEY_10CHANNELSDOWN; /* 10 channels down (10-) */
		key_table["KEY_IMAGES"] = KEY_IMAGES; /* AL Image Browser */

		key_table["KEY_DEL_EOL"] = KEY_DEL_EOL;
		key_table["KEY_DEL_EOS"] = KEY_DEL_EOS;
		key_table["KEY_INS_LINE"] = KEY_INS_LINE;
		key_table["KEY_DEL_LINE"] = KEY_DEL_LINE;

		key_table["KEY_FN"] = KEY_FN;
		key_table["KEY_FN_ESC"] = KEY_FN_ESC;
		key_table["KEY_FN_F1"] = KEY_FN_F1;
		key_table["KEY_FN_F2"] = KEY_FN_F2;
		key_table["KEY_FN_F3"] = KEY_FN_F3;
		key_table["KEY_FN_F4"] = KEY_FN_F4;
		key_table["KEY_FN_F5"] = KEY_FN_F5;
		key_table["KEY_FN_F6"] = KEY_FN_F6;
		key_table["KEY_FN_F7"] = KEY_FN_F7;
		key_table["KEY_FN_F8"] = KEY_FN_F8;
		key_table["KEY_FN_F9"] = KEY_FN_F9;
		key_table["KEY_FN_F10"] = KEY_FN_F10;
		key_table["KEY_FN_F11"] = KEY_FN_F11;
		key_table["KEY_FN_F12"] = KEY_FN_F12;
		key_table["KEY_FN_1"] = KEY_FN_1;
		key_table["KEY_FN_2"] = KEY_FN_2;
		key_table["KEY_FN_D"] = KEY_FN_D;
		key_table["KEY_FN_E"] = KEY_FN_E;
		key_table["KEY_FN_F"] = KEY_FN_F;
		key_table["KEY_FN_S"] = KEY_FN_S;
		key_table["KEY_FN_B"] = KEY_FN_B;

		key_table["KEY_BRL_DOT1"] = KEY_BRL_DOT1;
		key_table["KEY_BRL_DOT2"] = KEY_BRL_DOT2;
		key_table["KEY_BRL_DOT3"] = KEY_BRL_DOT3;
		key_table["KEY_BRL_DOT4"] = KEY_BRL_DOT4;
		key_table["KEY_BRL_DOT5"] = KEY_BRL_DOT5;
		key_table["KEY_BRL_DOT6"] = KEY_BRL_DOT6;
		key_table["KEY_BRL_DOT7"] = KEY_BRL_DOT7;
		key_table["KEY_BRL_DOT8"] = KEY_BRL_DOT8;
		key_table["KEY_BRL_DOT9"] = KEY_BRL_DOT9;
		key_table["KEY_BRL_DOT10"] = KEY_BRL_DOT10;

		key_table["KEY_NUMERIC_0"] = KEY_NUMERIC_0; /* used by phones, remote controls, */
		key_table["KEY_NUMERIC_1"] = KEY_NUMERIC_1; /* and other keypads */
		key_table["KEY_NUMERIC_2"] = KEY_NUMERIC_2;
		key_table["KEY_NUMERIC_3"] = KEY_NUMERIC_3;
		key_table["KEY_NUMERIC_4"] = KEY_NUMERIC_4;
		key_table["KEY_NUMERIC_5"] = KEY_NUMERIC_5;
		key_table["KEY_NUMERIC_6"] = KEY_NUMERIC_6;
		key_table["KEY_NUMERIC_7"] = KEY_NUMERIC_7;
		key_table["KEY_NUMERIC_8"] = KEY_NUMERIC_8;
		key_table["KEY_NUMERIC_9"] = KEY_NUMERIC_9;
		key_table["KEY_NUMERIC_STAR"] = KEY_NUMERIC_STAR;
		key_table["KEY_NUMERIC_POUND"] = KEY_NUMERIC_POUND;
		key_table["KEY_NUMERIC_A"] = KEY_NUMERIC_A; /* Phone key A - HUT Telephony 0xb9 */
		key_table["KEY_NUMERIC_B"] = KEY_NUMERIC_B;
		key_table["KEY_NUMERIC_C"] = KEY_NUMERIC_C;
		key_table["KEY_NUMERIC_D"] = KEY_NUMERIC_D;

		key_table["KEY_CAMERA_FOCUS"] = KEY_CAMERA_FOCUS;
		key_table["KEY_WPS_BUTTON"] = KEY_WPS_BUTTON; /* WiFi Protected Setup key */

		key_table["KEY_TOUCHPAD_TOGGLE"] = KEY_TOUCHPAD_TOGGLE; /* Request switch touchpad on or off */
		key_table["KEY_TOUCHPAD_ON"] = KEY_TOUCHPAD_ON;
		key_table["KEY_TOUCHPAD_OFF"] = KEY_TOUCHPAD_OFF;

		key_table["KEY_CAMERA_ZOOMIN"] = KEY_CAMERA_ZOOMIN;
		key_table["KEY_CAMERA_ZOOMOUT"] = KEY_CAMERA_ZOOMOUT;
		key_table["KEY_CAMERA_UP"] = KEY_CAMERA_UP;
		key_table["KEY_CAMERA_DOWN"] = KEY_CAMERA_DOWN;
		key_table["KEY_CAMERA_LEFT"] = KEY_CAMERA_LEFT;
		key_table["KEY_CAMERA_RIGHT"] = KEY_CAMERA_RIGHT;

		key_table["KEY_ATTENDANT_ON"] = KEY_ATTENDANT_ON;
		key_table["KEY_ATTENDANT_OFF"] = KEY_ATTENDANT_OFF;
		key_table["KEY_ATTENDANT_TOGGLE"] = KEY_ATTENDANT_TOGGLE; /* Attendant call on or off */
		key_table["KEY_LIGHTS_TOGGLE"] = KEY_LIGHTS_TOGGLE; /* Reading light on or off */

		key_table["BTN_DPAD_UP"] = BTN_DPAD_UP;
		key_table["BTN_DPAD_DOWN"] = BTN_DPAD_DOWN;
		key_table["BTN_DPAD_LEFT"] = BTN_DPAD_LEFT;
		key_table["BTN_DPAD_RIGHT"] = BTN_DPAD_RIGHT;

		key_table["KEY_ALS_TOGGLE"] = KEY_ALS_TOGGLE; /* Ambient light sensor */

		key_table["KEY_BUTTONCONFIG"] = KEY_BUTTONCONFIG; /* AL Button Configuration */
		key_table["KEY_TASKMANAGER"] = KEY_TASKMANAGER; /* AL Task/Project Manager */
		key_table["KEY_JOURNAL"] = KEY_JOURNAL; /* AL Log/Journal/Timecard */
		key_table["KEY_CONTROLPANEL"] = KEY_CONTROLPANEL; /* AL Control Panel */
		key_table["KEY_APPSELECT"] = KEY_APPSELECT; /* AL Select Task/Application */
		key_table["KEY_SCREENSAVER"] = KEY_SCREENSAVER; /* AL Screen Saver */
		key_table["KEY_VOICECOMMAND"] = KEY_VOICECOMMAND; /* Listening Voice Command */

		key_table["KEY_BRIGHTNESS_MIN"] = KEY_BRIGHTNESS_MIN; /* Set Brightness to Minimum */
		key_table["KEY_BRIGHTNESS_MAX"] = KEY_BRIGHTNESS_MAX; /* Set Brightness to Maximum */

		key_table["KEY_KBDINPUTASSIST_PREV"] = KEY_KBDINPUTASSIST_PREV;
		key_table["KEY_KBDINPUTASSIST_NEXT"] = KEY_KBDINPUTASSIST_NEXT;
		key_table["KEY_KBDINPUTASSIST_PREVGROUP"] = KEY_KBDINPUTASSIST_PREVGROUP;
		key_table["KEY_KBDINPUTASSIST_NEXTGROUP"] = KEY_KBDINPUTASSIST_NEXTGROUP;
		key_table["KEY_KBDINPUTASSIST_ACCEPT"] = KEY_KBDINPUTASSIST_ACCEPT;
		key_table["KEY_KBDINPUTASSIST_CANCEL"] = KEY_KBDINPUTASSIST_CANCEL;

		/* Diagonal movement keys */
		key_table["KEY_RIGHT_UP"] = KEY_RIGHT_UP;
		key_table["KEY_RIGHT_DOWN"] = KEY_RIGHT_DOWN;
		key_table["KEY_LEFT_UP"] = KEY_LEFT_UP;
		key_table["KEY_LEFT_DOWN"] = KEY_LEFT_DOWN;

		key_table["KEY_ROOT_MENU"] = KEY_ROOT_MENU; /* Show Device's Root Menu */
		/* Show Top Menu of the Media (e.g. DVD) */
		key_table["KEY_MEDIA_TOP_MENU"] = KEY_MEDIA_TOP_MENU;
		key_table["KEY_NUMERIC_11"] = KEY_NUMERIC_11;
		key_table["KEY_NUMERIC_12"] = KEY_NUMERIC_12;
		/*
		 * Toggle Audio Description: refers to an audio service that helps blind and
		 * visually impaired consumers understand the action in a program. Note: in
		 * some countries this is referred to as "Video Description".
		 */
		key_table["KEY_AUDIO_DESC"] = KEY_AUDIO_DESC;
		key_table["KEY_3D_MODE"] = KEY_3D_MODE;
		key_table["KEY_NEXT_FAVORITE"] = KEY_NEXT_FAVORITE;
		key_table["KEY_STOP_RECORD"] = KEY_STOP_RECORD;
		key_table["KEY_PAUSE_RECORD"] = KEY_PAUSE_RECORD;
		key_table["KEY_VOD"] = KEY_VOD; /* Video on Demand */
		key_table["KEY_UNMUTE"] = KEY_UNMUTE;
		key_table["KEY_FASTREVERSE"] = KEY_FASTREVERSE;
		key_table["KEY_SLOWREVERSE"] = KEY_SLOWREVERSE;
		/*
		 * Control a data application associated with the currently viewed channel,
		 * e.g. teletext or data broadcast application (MHEG, MHP, HbbTV, etc.)
		 */
		key_table["KEY_DATA"] = KEY_DATA;

		key_table["BTN_TRIGGER_HAPPY"] = BTN_TRIGGER_HAPPY;
		key_table["BTN_TRIGGER_HAPPY1"] = BTN_TRIGGER_HAPPY1;
		key_table["BTN_TRIGGER_HAPPY2"] = BTN_TRIGGER_HAPPY2;
		key_table["BTN_TRIGGER_HAPPY3"] = BTN_TRIGGER_HAPPY3;
		key_table["BTN_TRIGGER_HAPPY4"] = BTN_TRIGGER_HAPPY4;
		key_table["BTN_TRIGGER_HAPPY5"] = BTN_TRIGGER_HAPPY5;
		key_table["BTN_TRIGGER_HAPPY6"] = BTN_TRIGGER_HAPPY6;
		key_table["BTN_TRIGGER_HAPPY7"] = BTN_TRIGGER_HAPPY7;
		key_table["BTN_TRIGGER_HAPPY8"] = BTN_TRIGGER_HAPPY8;
		key_table["BTN_TRIGGER_HAPPY9"] = BTN_TRIGGER_HAPPY9;
		key_table["BTN_TRIGGER_HAPPY10"] = BTN_TRIGGER_HAPPY10;
		key_table["BTN_TRIGGER_HAPPY11"] = BTN_TRIGGER_HAPPY11;
		key_table["BTN_TRIGGER_HAPPY12"] = BTN_TRIGGER_HAPPY12;
		key_table["BTN_TRIGGER_HAPPY13"] = BTN_TRIGGER_HAPPY13;
		key_table["BTN_TRIGGER_HAPPY14"] = BTN_TRIGGER_HAPPY14;
		key_table["BTN_TRIGGER_HAPPY15"] = BTN_TRIGGER_HAPPY15;
		key_table["BTN_TRIGGER_HAPPY16"] = BTN_TRIGGER_HAPPY16;
		key_table["BTN_TRIGGER_HAPPY17"] = BTN_TRIGGER_HAPPY17;
		key_table["BTN_TRIGGER_HAPPY18"] = BTN_TRIGGER_HAPPY18;
		key_table["BTN_TRIGGER_HAPPY19"] = BTN_TRIGGER_HAPPY19;
		key_table["BTN_TRIGGER_HAPPY20"] = BTN_TRIGGER_HAPPY20;
		key_table["BTN_TRIGGER_HAPPY21"] = BTN_TRIGGER_HAPPY21;
		key_table["BTN_TRIGGER_HAPPY22"] = BTN_TRIGGER_HAPPY22;
		key_table["BTN_TRIGGER_HAPPY23"] = BTN_TRIGGER_HAPPY23;
		key_table["BTN_TRIGGER_HAPPY24"] = BTN_TRIGGER_HAPPY24;
		key_table["BTN_TRIGGER_HAPPY25"] = BTN_TRIGGER_HAPPY25;
		key_table["BTN_TRIGGER_HAPPY26"] = BTN_TRIGGER_HAPPY26;
		key_table["BTN_TRIGGER_HAPPY27"] = BTN_TRIGGER_HAPPY27;
		key_table["BTN_TRIGGER_HAPPY28"] = BTN_TRIGGER_HAPPY28;
		key_table["BTN_TRIGGER_HAPPY29"] = BTN_TRIGGER_HAPPY29;
		key_table["BTN_TRIGGER_HAPPY30"] = BTN_TRIGGER_HAPPY30;
		key_table["BTN_TRIGGER_HAPPY31"] = BTN_TRIGGER_HAPPY31;
		key_table["BTN_TRIGGER_HAPPY32"] = BTN_TRIGGER_HAPPY32;
		key_table["BTN_TRIGGER_HAPPY33"] = BTN_TRIGGER_HAPPY33;
		key_table["BTN_TRIGGER_HAPPY34"] = BTN_TRIGGER_HAPPY34;
		key_table["BTN_TRIGGER_HAPPY35"] = BTN_TRIGGER_HAPPY35;
		key_table["BTN_TRIGGER_HAPPY36"] = BTN_TRIGGER_HAPPY36;
		key_table["BTN_TRIGGER_HAPPY37"] = BTN_TRIGGER_HAPPY37;
		key_table["BTN_TRIGGER_HAPPY38"] = BTN_TRIGGER_HAPPY38;
		key_table["BTN_TRIGGER_HAPPY39"] = BTN_TRIGGER_HAPPY39;
		key_table["BTN_TRIGGER_HAPPY40"] = BTN_TRIGGER_HAPPY40;
	}
	return key_table;
}


#endif //maps
