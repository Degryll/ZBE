#ifndef ZBE_CORE_IO_INPUT_H
#define ZBE_CORE_IO_INPUT_H

#include <cstdint>

namespace zbe {

typedef uint32_t ZBE_K;
typedef float ZBE_KStatus;

// Input status
const ZBE_KStatus ZBE_KEYDOWN = 1.0; //!< Key is pressed.
const ZBE_KStatus ZBE_KEYUP = 0.0;   //!< Key is released.

const ZBE_KStatus ZBE_TRIGGERED = 0.1; //!< Minimal value an analog input is considered triggered.
const ZBE_KStatus ZBE_FULL = 1.0;      //!< The analog input is fully pressed.
const ZBE_KStatus ZBE_HARD = 0.75;     //!< The analog input is almost fully pressed.
const ZBE_KStatus ZBE_SOFT = 0.25;     //!< The analog input is barely pressed.

// Printable characters keys
const ZBE_K ZBEK_UNKNOWN = 0;
const ZBE_K ZBEK_BACKSPACE = 8;
const ZBE_K ZBEK_TAB = 9;
const ZBE_K ZBEK_RETURN = 13;
const ZBE_K ZBEK_ESCAPE = 27;
const ZBE_K ZBEK_SPACE = 32;
const ZBE_K ZBEK_EXCLAIM = 33;
const ZBE_K ZBEK_QUOTEDBL = 34;
const ZBE_K ZBEK_HASH = 35;
const ZBE_K ZBEK_DOLLAR = 36;
const ZBE_K ZBEK_PERCENT = 37;
const ZBE_K ZBEK_AMPERSAND = 38;
const ZBE_K ZBEK_QUOTE = 39;
const ZBE_K ZBEK_LEFTPAREN = 40;
const ZBE_K ZBEK_RIGHTPAREN = 41;
const ZBE_K ZBEK_ASTERISK = 42;
const ZBE_K ZBEK_PLUS = 43;
const ZBE_K ZBEK_COMMA = 44;
const ZBE_K ZBEK_MINUS = 45;
const ZBE_K ZBEK_PERIOD = 46;
const ZBE_K ZBEK_SLASH = 47;
const ZBE_K ZBEK_0 = 48;
const ZBE_K ZBEK_1 = 49;
const ZBE_K ZBEK_2 = 50;
const ZBE_K ZBEK_3 = 51;
const ZBE_K ZBEK_4 = 52;
const ZBE_K ZBEK_5 = 53;
const ZBE_K ZBEK_6 = 54;
const ZBE_K ZBEK_7 = 55;
const ZBE_K ZBEK_8 = 56;
const ZBE_K ZBEK_9 = 57;
const ZBE_K ZBEK_COLON = 58;
const ZBE_K ZBEK_SEMICOLON = 59;
const ZBE_K ZBEK_LESS = 60;
const ZBE_K ZBEK_EQUALS = 61;
const ZBE_K ZBEK_GREATER = 62;
const ZBE_K ZBEK_QUESTION = 63;
const ZBE_K ZBEK_AT = 64;
const ZBE_K ZBEK_LEFTBRACKET = 91;
const ZBE_K ZBEK_BACKSLASH = 92;
const ZBE_K ZBEK_RIGHTBRACKET = 93;
const ZBE_K ZBEK_CARET = 94;
const ZBE_K ZBEK_UNDERSCORE = 95;
const ZBE_K ZBEK_BACKQUOTE = 96;
const ZBE_K ZBEK_a = 97;
const ZBE_K ZBEK_b = 98;
const ZBE_K ZBEK_c = 99;
const ZBE_K ZBEK_d = 100;
const ZBE_K ZBEK_e = 101;
const ZBE_K ZBEK_f = 102;
const ZBE_K ZBEK_g = 103;
const ZBE_K ZBEK_h = 104;
const ZBE_K ZBEK_i = 105;
const ZBE_K ZBEK_j = 106;
const ZBE_K ZBEK_k = 107;
const ZBE_K ZBEK_l = 108;
const ZBE_K ZBEK_m = 109;
const ZBE_K ZBEK_n = 110;
const ZBE_K ZBEK_o = 111;
const ZBE_K ZBEK_p = 112;
const ZBE_K ZBEK_q = 113;
const ZBE_K ZBEK_r = 114;
const ZBE_K ZBEK_s = 115;
const ZBE_K ZBEK_t = 116;
const ZBE_K ZBEK_u = 117;
const ZBE_K ZBEK_v = 118;
const ZBE_K ZBEK_w = 119;
const ZBE_K ZBEK_x = 120;
const ZBE_K ZBEK_y = 121;
const ZBE_K ZBEK_z = 122;
const ZBE_K ZBEK_DELETE = 127;

// Non printable characters keys
const ZBE_K ZBEK_CAPSLOCK = 1073741881;
const ZBE_K ZBEK_F1 = 1073741882;
const ZBE_K ZBEK_F2 = 1073741883;
const ZBE_K ZBEK_F3 = 1073741884;
const ZBE_K ZBEK_F4 = 1073741885;
const ZBE_K ZBEK_F5 = 1073741886;
const ZBE_K ZBEK_F6 = 1073741887;
const ZBE_K ZBEK_F7 = 1073741888;
const ZBE_K ZBEK_F8 = 1073741889;
const ZBE_K ZBEK_F9 = 1073741890;
const ZBE_K ZBEK_F10 = 1073741891;
const ZBE_K ZBEK_F11 = 1073741892;
const ZBE_K ZBEK_F12 = 1073741893;
const ZBE_K ZBEK_PRINTSCREEN = 1073741894;
const ZBE_K ZBEK_SCROLLLOCK = 1073741895;
const ZBE_K ZBEK_PAUSE = 1073741896;
const ZBE_K ZBEK_INSERT = 1073741897;
const ZBE_K ZBEK_HOME = 1073741898;
const ZBE_K ZBEK_PAGEUP = 1073741899;
const ZBE_K ZBEK_END = 1073741901;
const ZBE_K ZBEK_PAGEDOWN = 1073741902;
const ZBE_K ZBEK_RIGHT = 1073741903;
const ZBE_K ZBEK_LEFT = 1073741904;
const ZBE_K ZBEK_DOWN = 1073741905;
const ZBE_K ZBEK_UP = 1073741906;
const ZBE_K ZBEK_NUMLOCKCLEAR = 1073741907;
const ZBE_K ZBEK_KP_DIVIDE = 1073741908;
const ZBE_K ZBEK_KP_MULTIPLY = 1073741909;
const ZBE_K ZBEK_KP_MINUS = 1073741910;
const ZBE_K ZBEK_KP_PLUS = 1073741911;
const ZBE_K ZBEK_KP_ENTER = 1073741912;
const ZBE_K ZBEK_KP_1 = 1073741913;
const ZBE_K ZBEK_KP_2 = 1073741914;
const ZBE_K ZBEK_KP_3 = 1073741915;
const ZBE_K ZBEK_KP_4 = 1073741916;
const ZBE_K ZBEK_KP_5 = 1073741917;
const ZBE_K ZBEK_KP_6 = 1073741918;
const ZBE_K ZBEK_KP_7 = 1073741919;
const ZBE_K ZBEK_KP_8 = 1073741920;
const ZBE_K ZBEK_KP_9 = 1073741921;
const ZBE_K ZBEK_KP_0 = 1073741922;
const ZBE_K ZBEK_KP_PERIOD = 1073741923;
const ZBE_K ZBEK_APPLICATION = 1073741925;
const ZBE_K ZBEK_POWER = 1073741926;
const ZBE_K ZBEK_KP_EQUALS = 1073741927;
const ZBE_K ZBEK_F13 = 1073741928;
const ZBE_K ZBEK_F14 = 1073741929;
const ZBE_K ZBEK_F15 = 1073741930;
const ZBE_K ZBEK_F16 = 1073741931;
const ZBE_K ZBEK_F17 = 1073741932;
const ZBE_K ZBEK_F18 = 1073741933;
const ZBE_K ZBEK_F19 = 1073741934;
const ZBE_K ZBEK_F20 = 1073741935;
const ZBE_K ZBEK_F21 = 1073741936;
const ZBE_K ZBEK_F22 = 1073741937;
const ZBE_K ZBEK_F23 = 1073741938;
const ZBE_K ZBEK_F24 = 1073741939;
const ZBE_K ZBEK_EXECUTE = 1073741940;
const ZBE_K ZBEK_HELP = 1073741941;
const ZBE_K ZBEK_MENU = 1073741942;
const ZBE_K ZBEK_SELECT = 1073741943;
const ZBE_K ZBEK_STOP = 1073741944;
const ZBE_K ZBEK_AGAIN = 1073741945;
const ZBE_K ZBEK_UNDO = 1073741946;
const ZBE_K ZBEK_CUT = 1073741947;
const ZBE_K ZBEK_COPY = 1073741948;
const ZBE_K ZBEK_PASTE = 1073741949;
const ZBE_K ZBEK_FIND = 1073741950;
const ZBE_K ZBEK_MUTE = 1073741951;
const ZBE_K ZBEK_VOLUMEUP = 1073741952;
const ZBE_K ZBEK_VOLUMEDOWN = 1073741953;
const ZBE_K ZBEK_KP_COMMA = 1073741957;
const ZBE_K ZBEK_KP_EQUALSAS400 = 1073741958;
const ZBE_K ZBEK_ALTERASE = 1073741977;
const ZBE_K ZBEK_SYSREQ = 1073741978;
const ZBE_K ZBEK_CANCEL = 1073741979;
const ZBE_K ZBEK_CLEAR = 1073741980;
const ZBE_K ZBEK_PRIOR = 1073741981;
const ZBE_K ZBEK_RETURN2 = 1073741982;
const ZBE_K ZBEK_SEPARATOR = 1073741983;
const ZBE_K ZBEK_OUT = 1073741984;
const ZBE_K ZBEK_OPER = 1073741985;
const ZBE_K ZBEK_CLEARAGAIN = 1073741986;
const ZBE_K ZBEK_CRSEL = 1073741987;
const ZBE_K ZBEK_EXSEL = 1073741988;
const ZBE_K ZBEK_KP_00 = 1073742000;
const ZBE_K ZBEK_KP_000 = 1073742001;
const ZBE_K ZBEK_THOUSANDSSEPARATOR = 1073742002;
const ZBE_K ZBEK_DECIMALSEPARATOR = 1073742003;
const ZBE_K ZBEK_CURRENCYUNIT = 1073742004;
const ZBE_K ZBEK_CURRENCYSUBUNIT = 1073742005;
const ZBE_K ZBEK_KP_LEFTPAREN = 1073742006;
const ZBE_K ZBEK_KP_RIGHTPAREN = 1073742007;
const ZBE_K ZBEK_KP_LEFTBRACE = 1073742008;
const ZBE_K ZBEK_KP_RIGHTBRACE = 1073742009;
const ZBE_K ZBEK_KP_TAB = 1073742010;
const ZBE_K ZBEK_KP_BACKSPACE = 1073742011;
const ZBE_K ZBEK_KP_A = 1073742012;
const ZBE_K ZBEK_KP_B = 1073742013;
const ZBE_K ZBEK_KP_C = 1073742014;
const ZBE_K ZBEK_KP_D = 1073742015;
const ZBE_K ZBEK_KP_E = 1073742016;
const ZBE_K ZBEK_KP_F = 1073742017;
const ZBE_K ZBEK_KP_XOR = 1073742018;
const ZBE_K ZBEK_KP_POWER = 1073742019;
const ZBE_K ZBEK_KP_PERCENT = 1073742020;
const ZBE_K ZBEK_KP_LESS = 1073742021;
const ZBE_K ZBEK_KP_GREATER = 1073742022;
const ZBE_K ZBEK_KP_AMPERSAND = 1073742023;
const ZBE_K ZBEK_KP_DBLAMPERSAND = 1073742024;
const ZBE_K ZBEK_KP_VERTICALBAR = 1073742025;
const ZBE_K ZBEK_KP_DBLVERTICALBAR = 1073742026;
const ZBE_K ZBEK_KP_COLON = 1073742027;
const ZBE_K ZBEK_KP_HASH = 1073742028;
const ZBE_K ZBEK_KP_SPACE = 1073742029;
const ZBE_K ZBEK_KP_AT = 1073742030;
const ZBE_K ZBEK_KP_EXCLAM = 1073742031;
const ZBE_K ZBEK_KP_MEMSTORE = 1073742032;
const ZBE_K ZBEK_KP_MEMRECALL = 1073742033;
const ZBE_K ZBEK_KP_MEMCLEAR = 1073742034;
const ZBE_K ZBEK_KP_MEMADD = 1073742035;
const ZBE_K ZBEK_KP_MEMSUBTRACT = 1073742036;
const ZBE_K ZBEK_KP_MEMMULTIPLY = 1073742037;
const ZBE_K ZBEK_KP_MEMDIVIDE = 1073742038;
const ZBE_K ZBEK_KP_PLUSMINUS = 1073742039;
const ZBE_K ZBEK_KP_CLEAR = 1073742040;
const ZBE_K ZBEK_KP_CLEARENTRY = 1073742041;
const ZBE_K ZBEK_KP_BINARY = 1073742042;
const ZBE_K ZBEK_KP_OCTAL = 1073742043;
const ZBE_K ZBEK_KP_DECIMAL = 1073742044;
const ZBE_K ZBEK_KP_HEXADECIMAL = 1073742045;
const ZBE_K ZBEK_LCTRL = 1073742048;
const ZBE_K ZBEK_LSHIFT = 1073742049;
const ZBE_K ZBEK_LALT = 1073742050;
const ZBE_K ZBEK_LGUI = 1073742051;
const ZBE_K ZBEK_RCTRL = 1073742052;
const ZBE_K ZBEK_RSHIFT = 1073742053;
const ZBE_K ZBEK_RALT = 1073742054;
const ZBE_K ZBEK_RGUI = 1073742055;
const ZBE_K ZBEK_MODE = 1073742081;
const ZBE_K ZBEK_AUDIONEXT = 1073742082;
const ZBE_K ZBEK_AUDIOPREV = 1073742083;
const ZBE_K ZBEK_AUDIOSTOP = 1073742084;
const ZBE_K ZBEK_AUDIOPLAY = 1073742085;
const ZBE_K ZBEK_AUDIOMUTE = 1073742086;
const ZBE_K ZBEK_MEDIASELECT = 1073742087;
const ZBE_K ZBEK_WWW = 1073742088;
const ZBE_K ZBEK_MAIL = 1073742089;
const ZBE_K ZBEK_CALCULATOR = 1073742090;
const ZBE_K ZBEK_COMPUTER = 1073742091;
const ZBE_K ZBEK_AC_SEARCH = 1073742092;
const ZBE_K ZBEK_AC_HOME = 1073742093;
const ZBE_K ZBEK_AC_BACK = 1073742094;
const ZBE_K ZBEK_AC_FORWARD = 1073742095;
const ZBE_K ZBEK_AC_STOP = 1073742096;
const ZBE_K ZBEK_AC_REFRESH = 1073742097;
const ZBE_K ZBEK_AC_BOOKMARKS = 1073742098;
const ZBE_K ZBEK_BRIGHTNESSDOWN = 1073742099;
const ZBE_K ZBEK_BRIGHTNESSUP = 1073742100;
const ZBE_K ZBEK_DISPLAYSWITCH = 1073742101;
const ZBE_K ZBEK_KBDILLUMTOGGLE = 1073742102;
const ZBE_K ZBEK_KBDILLUMDOWN = 1073742103;
const ZBE_K ZBEK_KBDILLUMUP = 1073742104;
const ZBE_K ZBEK_EJECT = 1073742105;
const ZBE_K ZBEK_SLEEP = 1073742106;

// Mouse state
const ZBE_K ZBEK_MOUSE_LEFT = 2048;
const ZBE_K ZBEK_MOUSE_RIGHT = 2049;
const ZBE_K ZBEK_MOUSE_WHEEL = 2050;
const ZBE_K ZBEK_MOUSE_WHEEL_X = 2051;
const ZBE_K ZBEK_MOUSE_WHEEL_Y = 2052;
const ZBE_K ZBEK_MOUSE_OFFSET_X = 2053;
const ZBE_K ZBEK_MOUSE_OFFSET_Y = 2054;
const ZBE_K ZBEK_MOUSE_EB1 = 2055;
const ZBE_K ZBEK_MOUSE_EB2 = 2056;

}  // namespace sbe

#endif  // ZBE_CORE_IO_INPUT_H
