/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputStatus.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Ludo
 * @brief Single imput status representation.
 */

#ifndef CORE_IO_INPUTSTATUS_H
#define CORE_IO_INPUTSTATUS_H

#include <cstdint>

namespace zbe {

class InputStatus {
  public:

    InputStatus(uint32_t id,float status,uint64_t time):id(id),status(status),time(time){};

    /** \brief Returns the id of the input element.
     *  \return Id of the input element.
     */
    uint32_t getId() const { return id;} ;

    /** \brief Returns the status of the input source.
     *  \return Status of the input source.
     */
    float getStatus() const { return status;};

    /** \brief Returns the timestamp in which this state is reached.
     *  \return Timestamp in which this state is reached.
     */
    uint64_t getTime() const { return time;};

    /** \brief "Less than" operator overloading.
     *  \return true if left hand element is less than right hand one
     */
    bool operator<(const InputStatus& rhs) const {return time<rhs.getTime();}

  private:

    uint32_t id;
    float status;
    uint64_t time;
};

//Printable characters keys
const int32_t ZBEK_UNKNOWN = 0;
const int32_t ZBEK_BACKSPACE = 8;
const int32_t ZBEK_TAB = 9;
const int32_t ZBEK_RETURN = 13;
const int32_t ZBEK_ESCAPE = 27;
const int32_t ZBEK_SPACE = 32;
const int32_t ZBEK_EXCLAIM = 33;
const int32_t ZBEK_QUOTEDBL = 34;
const int32_t ZBEK_HASH = 35;
const int32_t ZBEK_DOLLAR = 36;
const int32_t ZBEK_PERCENT = 37;
const int32_t ZBEK_AMPERSAND = 38;
const int32_t ZBEK_QUOTE = 39;
const int32_t ZBEK_LEFTPAREN = 40;
const int32_t ZBEK_RIGHTPAREN = 41;
const int32_t ZBEK_ASTERISK = 42;
const int32_t ZBEK_PLUS = 43;
const int32_t ZBEK_COMMA = 44;
const int32_t ZBEK_MINUS = 45;
const int32_t ZBEK_PERIOD = 46;
const int32_t ZBEK_SLASH = 47;
const int32_t ZBEK_0 = 48;
const int32_t ZBEK_1 = 49;
const int32_t ZBEK_2 = 50;
const int32_t ZBEK_3 = 51;
const int32_t ZBEK_4 = 52;
const int32_t ZBEK_5 = 53;
const int32_t ZBEK_6 = 54;
const int32_t ZBEK_7 = 55;
const int32_t ZBEK_8 = 56;
const int32_t ZBEK_9 = 57;
const int32_t ZBEK_COLON = 58;
const int32_t ZBEK_SEMICOLON = 59;
const int32_t ZBEK_LESS = 60;
const int32_t ZBEK_EQUALS = 61;
const int32_t ZBEK_GREATER = 62;
const int32_t ZBEK_QUESTION = 63;
const int32_t ZBEK_AT = 64;
const int32_t ZBEK_LEFTBRACKET = 91;
const int32_t ZBEK_BACKSLASH = 92;
const int32_t ZBEK_RIGHTBRACKET = 93;
const int32_t ZBEK_CARET = 94;
const int32_t ZBEK_UNDERSCORE = 95;
const int32_t ZBEK_BACKQUOTE = 96;
const int32_t ZBEK_a = 97;
const int32_t ZBEK_b = 98;
const int32_t ZBEK_c = 99;
const int32_t ZBEK_d = 100;
const int32_t ZBEK_e = 101;
const int32_t ZBEK_f = 102;
const int32_t ZBEK_g = 103;
const int32_t ZBEK_h = 104;
const int32_t ZBEK_i = 105;
const int32_t ZBEK_j = 106;
const int32_t ZBEK_k = 107;
const int32_t ZBEK_l = 108;
const int32_t ZBEK_m = 109;
const int32_t ZBEK_n = 110;
const int32_t ZBEK_o = 111;
const int32_t ZBEK_p = 112;
const int32_t ZBEK_q = 113;
const int32_t ZBEK_r = 114;
const int32_t ZBEK_s = 115;
const int32_t ZBEK_t = 116;
const int32_t ZBEK_u = 117;
const int32_t ZBEK_v = 118;
const int32_t ZBEK_w = 119;
const int32_t ZBEK_x = 120;
const int32_t ZBEK_y = 121;
const int32_t ZBEK_z = 122;
const int32_t ZBEK_DELETE = 127;

//Non printable characters keys
const int32_t ZBEK_CAPSLOCK = 1073741881;
const int32_t ZBEK_F1 = 1073741882;
const int32_t ZBEK_F2 = 1073741883;
const int32_t ZBEK_F3 = 1073741884;
const int32_t ZBEK_F4 = 1073741885;
const int32_t ZBEK_F5 = 1073741886;
const int32_t ZBEK_F6 = 1073741887;
const int32_t ZBEK_F7 = 1073741888;
const int32_t ZBEK_F8 = 1073741889;
const int32_t ZBEK_F9 = 1073741890;
const int32_t ZBEK_F10 = 1073741891;
const int32_t ZBEK_F11 = 1073741892;
const int32_t ZBEK_F12 = 1073741893;
const int32_t ZBEK_PRINTSCREEN = 1073741894;
const int32_t ZBEK_SCROLLLOCK = 1073741895;
const int32_t ZBEK_PAUSE = 1073741896;
const int32_t ZBEK_INSERT = 1073741897;
const int32_t ZBEK_HOME = 1073741898;
const int32_t ZBEK_PAGEUP = 1073741899;
const int32_t ZBEK_END = 1073741901;
const int32_t ZBEK_PAGEDOWN = 1073741902;
const int32_t ZBEK_RIGHT = 1073741903;
const int32_t ZBEK_LEFT = 1073741904;
const int32_t ZBEK_DOWN = 1073741905;
const int32_t ZBEK_UP = 1073741906;
const int32_t ZBEK_NUMLOCKCLEAR = 1073741907;
const int32_t ZBEK_KP_DIVIDE = 1073741908;
const int32_t ZBEK_KP_MULTIPLY = 1073741909;
const int32_t ZBEK_KP_MINUS = 1073741910;
const int32_t ZBEK_KP_PLUS = 1073741911;
const int32_t ZBEK_KP_ENTER = 1073741912;
const int32_t ZBEK_KP_1 = 1073741913;
const int32_t ZBEK_KP_2 = 1073741914;
const int32_t ZBEK_KP_3 = 1073741915;
const int32_t ZBEK_KP_4 = 1073741916;
const int32_t ZBEK_KP_5 = 1073741917;
const int32_t ZBEK_KP_6 = 1073741918;
const int32_t ZBEK_KP_7 = 1073741919;
const int32_t ZBEK_KP_8 = 1073741920;
const int32_t ZBEK_KP_9 = 1073741921;
const int32_t ZBEK_KP_0 = 1073741922;
const int32_t ZBEK_KP_PERIOD = 1073741923;
const int32_t ZBEK_APPLICATION = 1073741925;
const int32_t ZBEK_POWER = 1073741926;
const int32_t ZBEK_KP_EQUALS = 1073741927;
const int32_t ZBEK_F13 = 1073741928;
const int32_t ZBEK_F14 = 1073741929;
const int32_t ZBEK_F15 = 1073741930;
const int32_t ZBEK_F16 = 1073741931;
const int32_t ZBEK_F17 = 1073741932;
const int32_t ZBEK_F18 = 1073741933;
const int32_t ZBEK_F19 = 1073741934;
const int32_t ZBEK_F20 = 1073741935;
const int32_t ZBEK_F21 = 1073741936;
const int32_t ZBEK_F22 = 1073741937;
const int32_t ZBEK_F23 = 1073741938;
const int32_t ZBEK_F24 = 1073741939;
const int32_t ZBEK_EXECUTE = 1073741940;
const int32_t ZBEK_HELP = 1073741941;
const int32_t ZBEK_MENU = 1073741942;
const int32_t ZBEK_SELECT = 1073741943;
const int32_t ZBEK_STOP = 1073741944;
const int32_t ZBEK_AGAIN = 1073741945;
const int32_t ZBEK_UNDO = 1073741946;
const int32_t ZBEK_CUT = 1073741947;
const int32_t ZBEK_COPY = 1073741948;
const int32_t ZBEK_PASTE = 1073741949;
const int32_t ZBEK_FIND = 1073741950;
const int32_t ZBEK_MUTE = 1073741951;
const int32_t ZBEK_VOLUMEUP = 1073741952;
const int32_t ZBEK_VOLUMEDOWN = 1073741953;
const int32_t ZBEK_KP_COMMA = 1073741957;
const int32_t ZBEK_KP_EQUALSAS400 = 1073741958;
const int32_t ZBEK_ALTERASE = 1073741977;
const int32_t ZBEK_SYSREQ = 1073741978;
const int32_t ZBEK_CANCEL = 1073741979;
const int32_t ZBEK_CLEAR = 1073741980;
const int32_t ZBEK_PRIOR = 1073741981;
const int32_t ZBEK_RETURN2 = 1073741982;
const int32_t ZBEK_SEPARATOR = 1073741983;
const int32_t ZBEK_OUT = 1073741984;
const int32_t ZBEK_OPER = 1073741985;
const int32_t ZBEK_CLEARAGAIN = 1073741986;
const int32_t ZBEK_CRSEL = 1073741987;
const int32_t ZBEK_EXSEL = 1073741988;
const int32_t ZBEK_KP_00 = 1073742000;
const int32_t ZBEK_KP_000 = 1073742001;
const int32_t ZBEK_THOUSANDSSEPARATOR = 1073742002;
const int32_t ZBEK_DECIMALSEPARATOR = 1073742003;
const int32_t ZBEK_CURRENCYUNIT = 1073742004;
const int32_t ZBEK_CURRENCYSUBUNIT = 1073742005;
const int32_t ZBEK_KP_LEFTPAREN = 1073742006;
const int32_t ZBEK_KP_RIGHTPAREN = 1073742007;
const int32_t ZBEK_KP_LEFTBRACE = 1073742008;
const int32_t ZBEK_KP_RIGHTBRACE = 1073742009;
const int32_t ZBEK_KP_TAB = 1073742010;
const int32_t ZBEK_KP_BACKSPACE = 1073742011;
const int32_t ZBEK_KP_A = 1073742012;
const int32_t ZBEK_KP_B = 1073742013;
const int32_t ZBEK_KP_C = 1073742014;
const int32_t ZBEK_KP_D = 1073742015;
const int32_t ZBEK_KP_E = 1073742016;
const int32_t ZBEK_KP_F = 1073742017;
const int32_t ZBEK_KP_XOR = 1073742018;
const int32_t ZBEK_KP_POWER = 1073742019;
const int32_t ZBEK_KP_PERCENT = 1073742020;
const int32_t ZBEK_KP_LESS = 1073742021;
const int32_t ZBEK_KP_GREATER = 1073742022;
const int32_t ZBEK_KP_AMPERSAND = 1073742023;
const int32_t ZBEK_KP_DBLAMPERSAND = 1073742024;
const int32_t ZBEK_KP_VERTICALBAR = 1073742025;
const int32_t ZBEK_KP_DBLVERTICALBAR = 1073742026;
const int32_t ZBEK_KP_COLON = 1073742027;
const int32_t ZBEK_KP_HASH = 1073742028;
const int32_t ZBEK_KP_SPACE = 1073742029;
const int32_t ZBEK_KP_AT = 1073742030;
const int32_t ZBEK_KP_EXCLAM = 1073742031;
const int32_t ZBEK_KP_MEMSTORE = 1073742032;
const int32_t ZBEK_KP_MEMRECALL = 1073742033;
const int32_t ZBEK_KP_MEMCLEAR = 1073742034;
const int32_t ZBEK_KP_MEMADD = 1073742035;
const int32_t ZBEK_KP_MEMSUBTRACT = 1073742036;
const int32_t ZBEK_KP_MEMMULTIPLY = 1073742037;
const int32_t ZBEK_KP_MEMDIVIDE = 1073742038;
const int32_t ZBEK_KP_PLUSMINUS = 1073742039;
const int32_t ZBEK_KP_CLEAR = 1073742040;
const int32_t ZBEK_KP_CLEARENTRY = 1073742041;
const int32_t ZBEK_KP_BINARY = 1073742042;
const int32_t ZBEK_KP_OCTAL = 1073742043;
const int32_t ZBEK_KP_DECIMAL = 1073742044;
const int32_t ZBEK_KP_HEXADECIMAL = 1073742045;
const int32_t ZBEK_LCTRL = 1073742048;
const int32_t ZBEK_LSHIFT = 1073742049;
const int32_t ZBEK_LALT = 1073742050;
const int32_t ZBEK_LGUI = 1073742051;
const int32_t ZBEK_RCTRL = 1073742052;
const int32_t ZBEK_RSHIFT = 1073742053;
const int32_t ZBEK_RALT = 1073742054;
const int32_t ZBEK_RGUI = 1073742055;
const int32_t ZBEK_MODE = 1073742081;
const int32_t ZBEK_AUDIONEXT = 1073742082;
const int32_t ZBEK_AUDIOPREV = 1073742083;
const int32_t ZBEK_AUDIOSTOP = 1073742084;
const int32_t ZBEK_AUDIOPLAY = 1073742085;
const int32_t ZBEK_AUDIOMUTE = 1073742086;
const int32_t ZBEK_MEDIASELECT = 1073742087;
const int32_t ZBEK_WWW = 1073742088;
const int32_t ZBEK_MAIL = 1073742089;
const int32_t ZBEK_CALCULATOR = 1073742090;
const int32_t ZBEK_COMPUTER = 1073742091;
const int32_t ZBEK_AC_SEARCH = 1073742092;
const int32_t ZBEK_AC_HOME = 1073742093;
const int32_t ZBEK_AC_BACK = 1073742094;
const int32_t ZBEK_AC_FORWARD = 1073742095;
const int32_t ZBEK_AC_STOP = 1073742096;
const int32_t ZBEK_AC_REFRESH = 1073742097;
const int32_t ZBEK_AC_BOOKMARKS = 1073742098;
const int32_t ZBEK_BRIGHTNESSDOWN = 1073742099;
const int32_t ZBEK_BRIGHTNESSUP = 1073742100;
const int32_t ZBEK_DISPLAYSWITCH = 1073742101;
const int32_t ZBEK_KBDILLUMTOGGLE = 1073742102;
const int32_t ZBEK_KBDILLUMDOWN = 1073742103;
const int32_t ZBEK_KBDILLUMUP = 1073742104;
const int32_t ZBEK_EJECT = 1073742105;
const int32_t ZBEK_SLEEP = 1073742106;

//Mouse state
const int32_t ZBEK_MOUSE_LEFT = 2048;
const int32_t ZBEK_MOUSE_RIGHT = 2049;
const int32_t ZBEK_MOUSE_WHEEL = 2050;
const int32_t ZBEK_MOUSE_WHEEL_X = 2051;
const int32_t ZBEK_MOUSE_WHEEL_Y = 2052;
const int32_t ZBEK_MOUSE_OFFSET_X = 2053;
const int32_t ZBEK_MOUSE_OFFSET_Y = 2054;
const int32_t ZBEK_MOUSE_EB1 = 2055;
const int32_t ZBEK_MOUSE_EB2 = 2056;
}

#endif //CORE_IO_INPUTSTATUS_H
