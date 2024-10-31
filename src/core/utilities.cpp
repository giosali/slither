#include "utilities.h"

#include <linux/input-event-codes.h>

#include <unordered_map>

std::string Utilities::ConvertDirectionToString(Gesture::Direction direction) {
  switch (direction) {
    case Gesture::Direction::kNone:
      return kHoldText;
    case Gesture::Direction::kUp:
      return kUpText;
    case Gesture::Direction::kRight:
      return kRightText;
    case Gesture::Direction::kDown:
      return kDownText;
    case Gesture::Direction::kLeft:
      return kLeftText;
    case Gesture::Direction::kIn:
      return kInText;
    case Gesture::Direction::kOut:
      return kOutText;
    default:
      return {};
  }
}

std::string Utilities::ConvertPinchSensitivityToString(
  Settings::PinchSensitivity sensitivity) {
  switch (sensitivity) {
    case Settings::PinchSensitivity::kLow:
      return "Low";
    case Settings::PinchSensitivity::kMedium:
      return "Medium";
    case Settings::PinchSensitivity::kHigh:
      return "High";
    default:
      return {};
  }
}

Gesture::Direction Utilities::ConvertStringToDirection(const std::string& s) {
  // This is not a function that needs to be performant. This function will
  // only be called when the user is adding or editing a gesture via the GUI
  // and presses "Save."
  auto direction_map = std::unordered_map<std::string_view, Gesture::Direction>{
    {kHoldText, Gesture::Direction::kNone},
    {kUpText, Gesture::Direction::kUp},
    {kRightText, Gesture::Direction::kRight},
    {kDownText, Gesture::Direction::kDown},
    {kLeftText, Gesture::Direction::kLeft},
    {kInText, Gesture::Direction::kIn},
    {kOutText, Gesture::Direction::kOut}};

  auto it = direction_map.find(s);
  return it != direction_map.end() ? it->second : Gesture::Direction::kNone;
}

std::string Utilities::ConvertSwipeSensitivityToString(
  Settings::SwipeSensitivity sensitivity) {
  switch (sensitivity) {
    case Settings::SwipeSensitivity::kVeryLow:
      return "Very Low";
    case Settings::SwipeSensitivity::kLow:
      return "Low";
    case Settings::SwipeSensitivity::kMedium:
      return "Medium";
    case Settings::SwipeSensitivity::kHigh:
      return "High";
    case Settings::SwipeSensitivity::kVeryHigh:
      return "Very High";
    default:
      return {};
  }
}

bool Utilities::IsModifierKey(uint32_t key_code) {
  switch (key_code) {
    case KEY_LEFTCTRL:
    case KEY_RIGHTCTRL:
    case KEY_LEFTALT:
    case KEY_RIGHTALT:
    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT:
    case KEY_LEFTMETA:
    case KEY_RIGHTMETA:
      return true;
    default:
      return false;
  }
}

bool Utilities::IsShiftKey(uint32_t key_code) {
  switch (key_code) {
    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT:
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
    case KEY_ESC:
      return "Escape";
    case KEY_1:
      return "1";
    case KEY_2:
      return "2";
    case KEY_3:
      return "3";
    case KEY_4:
      return "4";
    case KEY_5:
      return "5";
    case KEY_6:
      return "6";
    case KEY_7:
      return "7";
    case KEY_8:
      return "8";
    case KEY_9:
      return "9";
    case KEY_0:
      return "0";
    case KEY_MINUS:
      return "-";
    case KEY_EQUAL:
      return "=";
    case KEY_BACKSPACE:
      return "Backspace";
    case KEY_TAB:
      return "Tab";
    case KEY_Q:
      return "Q";
    case KEY_W:
      return "W";
    case KEY_E:
      return "E";
    case KEY_R:
      return "R";
    case KEY_T:
      return "T";
    case KEY_Y:
      return "Y";
    case KEY_U:
      return "U";
    case KEY_I:
      return "I";
    case KEY_O:
      return "O";
    case KEY_P:
      return "P";
    case KEY_LEFTBRACE:
      return "[";
    case KEY_RIGHTBRACE:
      return "]";
    case KEY_ENTER:
      return "Enter";
    case KEY_LEFTCTRL:
      return "Ctrl";
    case KEY_A:
      return "A";
    case KEY_S:
      return "S";
    case KEY_D:
      return "D";
    case KEY_F:
      return "F";
    case KEY_G:
      return "G";
    case KEY_H:
      return "H";
    case KEY_J:
      return "J";
    case KEY_K:
      return "K";
    case KEY_L:
      return "L";
    case KEY_SEMICOLON:
      return ";";
    case KEY_APOSTROPHE:
      return "'";
    case KEY_GRAVE:
      return "`";
    case KEY_LEFTSHIFT:
      return "Shift";
    case KEY_BACKSLASH:
      return "Backslash";
    case KEY_Z:
      return "Z";
    case KEY_X:
      return "X";
    case KEY_C:
      return "C";
    case KEY_V:
      return "V";
    case KEY_B:
      return "B";
    case KEY_N:
      return "N";
    case KEY_M:
      return "M";
    case KEY_COMMA:
      return ",";
    case KEY_DOT:
      return ".";
    case KEY_SLASH:
      return "/";
    case KEY_RIGHTSHIFT:
      return "Shift";
    case KEY_KPASTERISK:
      return "KP_ASTERISK";
    case KEY_LEFTALT:
      return "Alt";
    case KEY_SPACE:
      return "Space";
    case KEY_CAPSLOCK:
      return "Caps Lock";
    case KEY_F1:
      return "F1";
    case KEY_F2:
      return "F2";
    case KEY_F3:
      return "F3";
    case KEY_F4:
      return "F4";
    case KEY_F5:
      return "F5";
    case KEY_F6:
      return "F6";
    case KEY_F7:
      return "F7";
    case KEY_F8:
      return "F8";
    case KEY_F9:
      return "F9";
    case KEY_F10:
      return "F10";
    case KEY_NUMLOCK:
      return "Num Lock";
    case KEY_SCROLLLOCK:
      return "Scroll Lock";
    case KEY_KP7:
      return "KP_7";
    case KEY_KP8:
      return "KP_8";
    case KEY_KP9:
      return "KP_9";
    case KEY_KPMINUS:
      return "KP_MINUS";
    case KEY_KP4:
      return "KP_4";
    case KEY_KP5:
      return "KP_5";
    case KEY_KP6:
      return "KP_6";
    case KEY_KPPLUS:
      return "KP_PLUS";
    case KEY_KP1:
      return "KP_1";
    case KEY_KP2:
      return "KP_2";
    case KEY_KP3:
      return "KP_3";
    case KEY_KP0:
      return "KP_0";
    case KEY_KPDOT:
      return "KP_DOT";
    case KEY_ZENKAKUHANKAKU:
      return "ZENKAKUHANKAKU";
    case KEY_102ND:
      return "102ND";
    case KEY_F11:
      return "F11";
    case KEY_F12:
      return "F12";
    case KEY_RO:
      return "RO";
    case KEY_KATAKANA:
      return "KATAKANA";
    case KEY_HIRAGANA:
      return "HIRAGANA";
    case KEY_HENKAN:
      return "HENKAN";
    case KEY_KATAKANAHIRAGANA:
      return "KATAKANAHIRAGANA";
    case KEY_MUHENKAN:
      return "MUHENKAN";
    case KEY_KPJPCOMMA:
      return "KP_JPCOMMA";
    case KEY_KPENTER:
      return "KP_ENTER";
    case KEY_RIGHTCTRL:
      return "Ctrl";
    case KEY_KPSLASH:
      return "KP_SLASH";
    case KEY_SYSRQ:
      return "SYSRQ";
    case KEY_RIGHTALT:
      return "Alt";
    case KEY_LINEFEED:
      return "LINEFEED";
    case KEY_HOME:
      return "Home";
    case KEY_UP:
      return "Up";
    case KEY_PAGEUP:
      return "Page Up";
    case KEY_LEFT:
      return "Left";
    case KEY_RIGHT:
      return "Right";
    case KEY_END:
      return "End";
    case KEY_DOWN:
      return "Down";
    case KEY_PAGEDOWN:
      return "Page Down";
    case KEY_INSERT:
      return "Insert";
    case KEY_DELETE:
      return "Delete";
    case KEY_MACRO:
      return "MACRO";
    case KEY_MUTE:
      return "MUTE";
    case KEY_VOLUMEDOWN:
      return "VOLUMEDOWN";
    case KEY_VOLUMEUP:
      return "VOLUMEUP";
    case KEY_POWER:
      return "POWER";
    case KEY_KPEQUAL:
      return "KP_EQUAL";
    case KEY_KPPLUSMINUS:
      return "KP_PLUSMINUS";
    case KEY_PAUSE:
      return "Pause";
    case KEY_SCALE:
      return "SCALE";
    case KEY_KPCOMMA:
      return "KP_COMMA";
    case KEY_LEFTMETA:
    case KEY_RIGHTMETA:
      return "Super";
    default:
      return "";
  }
}
