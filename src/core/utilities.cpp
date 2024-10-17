#include "utilities.h"

std::string Utilities::Join(const std::string& delimiter,
                            const std::vector<std::string>& elements) {
  if (elements.empty()) {
    return "";
  }

  std::string result = elements[0];
  for (size_t i = 1; i < elements.size(); ++i) {
    result += delimiter + elements[i];
  }
  return result;
}

std::string Utilities::KeyCodeToString(uint32_t key_code) {
  switch (key_code) {
    case 1:
      return "ESC";
    case 2:
      return "1";
    case 3:
      return "2";
    case 4:
      return "3";
    case 5:
      return "4";
    case 6:
      return "5";
    case 7:
      return "6";
    case 8:
      return "7";
    case 9:
      return "8";
    case 10:
      return "9";
    case 11:
      return "0";
    case 12:  // MINUS
      return "-";
    case 13:  // EQUAL
      return "=";
    case 14:
      return "BACKSPACE";
    case 15:
      return "TAB";
    case 16:
      return "Q";
    case 17:
      return "W";
    case 18:
      return "E";
    case 19:
      return "R";
    case 20:
      return "T";
    case 21:
      return "Y";
    case 22:
      return "U";
    case 23:
      return "I";
    case 24:
      return "O";
    case 25:
      return "P";
    case 26:
      return "[";
    case 27:
      return "]";
    case 28:
      return "ENTER";
    case 29:  // LEFTCTRL
      return "CTRL";
    case 30:
      return "A";
    case 31:
      return "S";
    case 32:
      return "D";
    case 33:
      return "F";
    case 34:
      return "G";
    case 35:
      return "H";
    case 36:
      return "J";
    case 37:
      return "K";
    case 38:
      return "L";
    case 39:  // SEMICOLON
      return ";";
    case 40:  // APOSTROPHE
      return "'";
    case 41:  // GRAVE
      return "`";
    case 42:  // LEFTSHIFT
      return "SHIFT";
    case 43:  // BACKSLASH
      return "\\";
    case 44:
      return "Z";
    case 45:
      return "X";
    case 46:
      return "C";
    case 47:
      return "V";
    case 48:
      return "B";
    case 49:
      return "N";
    case 50:
      return "M";
    case 51:  // COMMA
      return ",";
    case 52:  // DOT
      return ".";
    case 53:  // SLASH
      return "/";
    case 54:  // RIGHTSHIFT
      return "SHIFT";
    case 55:
      return "KPASTERISK";
    case 56:  // LEFTALT
      return "ALT";
    case 57:
      return "SPACE";
    case 58:
      return "CAPSLOCK";
    case 59:
      return "F1";
    case 60:
      return "F2";
    case 61:
      return "F3";
    case 62:
      return "F4";
    case 63:
      return "F5";
    case 64:
      return "F6";
    case 65:
      return "F7";
    case 66:
      return "F8";
    case 67:
      return "F9";
    case 68:
      return "F10";
    case 69:
      return "NUMLOCK";
    case 70:
      return "SCROLLLOCK";
    case 71:
      return "KP7";
    case 72:
      return "KP8";
    case 73:
      return "KP9";
    case 74:
      return "KPMINUS";
    case 75:
      return "KP4";
    case 76:
      return "KP5";
    case 77:
      return "KP6";
    case 78:
      return "KPPLUS";
    case 79:
      return "KP1";
    case 80:
      return "KP2";
    case 81:
      return "KP3";
    case 82:
      return "KP0";
    case 83:
      return "KPDOT";
    case 85:
      return "ZENKAKUHANKAKU";
    case 86:
      return "102ND";
    case 87:
      return "F11";
    case 88:
      return "F12";
    case 89:
      return "RO";
    case 90:
      return "KATAKANA";
    case 91:
      return "HIRAGANA";
    case 92:
      return "HENKAN";
    case 93:
      return "KATAKANAHIRAGANA";
    case 94:
      return "MUHENKAN";
    case 95:
      return "KPJPCOMMA";
    case 96:
      return "KPENTER";
    case 97:  // RIGHTCTRL
      return "CTRL";
    case 98:
      return "KPSLASH";
    case 99:
      return "SYSRQ";
    case 100:  // RIGHTALT
      return "ALT";
    case 101:
      return "LINEFEED";
    case 102:
      return "HOME";
    case 103:
      return "UP";
    case 104:
      return "PAGEUP";
    case 105:
      return "LEFT";
    case 106:
      return "RIGHT";
    case 107:
      return "END";
    case 108:
      return "DOWN";
    case 109:
      return "PAGEDOWN";
    case 110:
      return "INSERT";
    case 111:
      return "DELETE";
    case 112:
      return "MACRO";
    case 113:
      return "MUTE";
    case 114:
      return "VOLUMEDOWN";
    case 115:
      return "VOLUMEUP";
    case 116:
      return "POWER";
    case 117:
      return "KPEQUAL";
    case 118:
      return "KPPLUSMINUS";
    case 119:
      return "PAUSE";
    case 120:
      return "SCALE";
    case 121:
      return "KPCOMMA";
    default:
      return "";
  }
}
