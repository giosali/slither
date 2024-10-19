#include "utilities.h"

bool Utilities::IsModifierKey(uint32_t key_code) {
  switch (key_code) {
    case 29:
    case 42:
    case 54:
    case 56:
    case 97:
    case 100:
    case 125:
    case 126:
      return true;
    default:
      return false;
  }
}

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

/**
 * @brief Returns string representation of a key code.
 *
 * @link
 * https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
 * @link https://gitlab.gnome.org/GNOME/gtk/-/blob/main/gdk/gdkkeysyms.h
 *
 * @param key_code - The key code based on Linux input event codes.
 * @return std::string
 */
std::string Utilities::KeyCodeToString(uint32_t key_code) {
  switch (key_code) {
    case 1:
      return "Escape";
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
    case 12:  // -
      return "Minus";
    case 13:  // =
      return "Equal";
    case 14:
      return "Backspace";
    case 15:
      return "Tab";
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
      return "Enter";
    case 29:  // LEFTCTRL
      return "Ctrl";
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
    case 39:  // ;
      return "Semicolon";
    case 40:  // '
      return "Apostrophe";
    case 41:  // `
      return "Grave";
    case 42:  // LEFTSHIFT
      return "Shift";
    case 43:
      return "Backslash";
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
    case 51:  // ,
      return "Comma";
    case 52:  // .
      return "Period";
    case 53:  // /
      return "Slash";
    case 54:  // RIGHTSHIFT
      return "Shift";
    case 55:
      return "KP_ASTERISK";
    case 56:  // LEFTALT
      return "Alt";
    case 57:
      return "Space";
    case 58:
      return "Caps_Lock";
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
      return "Num_Lock";
    case 70:
      return "Scroll_Lock";
    case 71:
      return "KP_7";
    case 72:
      return "KP_8";
    case 73:
      return "KP_9";
    case 74:
      return "KP_MINUS";
    case 75:
      return "KP_4";
    case 76:
      return "KP_5";
    case 77:
      return "KP_6";
    case 78:
      return "KP_PLUS";
    case 79:
      return "KP_1";
    case 80:
      return "KP_2";
    case 81:
      return "KP_3";
    case 82:
      return "KP_0";
    case 83:
      return "KP_DOT";
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
      return "KP_JPCOMMA";
    case 96:
      return "KP_ENTER";
    case 97:  // RIGHTCTRL
      return "Ctrl";
    case 98:
      return "KP_SLASH";
    case 99:
      return "SYSRQ";
    case 100:  // RIGHTALT
      return "Alt";
    case 101:
      return "LINEFEED";
    case 102:
      return "Home";
    case 103:
      return "Up";
    case 104:
      return "Page_Up";
    case 105:
      return "Left";
    case 106:
      return "Right";
    case 107:
      return "End";
    case 108:
      return "Down";
    case 109:
      return "Page_Down";
    case 110:
      return "Insert";
    case 111:
      return "Delete";
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
      return "KP_EQUAL";
    case 118:
      return "KP_PLUSMINUS";
    case 119:
      return "Pause";
    case 120:
      return "SCALE";
    case 121:
      return "KP_COMMA";
    case 125:  // LEFTMETA
    case 126:  // RIGHTMETA
      return "Meta";
    default:
      return "";
  }
}
