#include "inputinjector.h"

#include <list>
#include <stdexcept>

#include "utils.h"

InputInjector::InputInjector() : dev_{nullptr}, uinput_dev_{nullptr} {}

InputInjector::InputInjector(const std::unordered_set<uint32_t>& key_codes)
    : dev_{libevdev_new()}, uinput_dev_{nullptr} {
  libevdev_set_name(dev_, "slither device");

  auto err = libevdev_enable_event_type(dev_, EV_KEY);
  if (err != 0) {
    auto what = Utils::FormatExceptionMessage(
      "Enabling event type on new libevdev device",
      "Unable to enable EV_KEY event");
    throw std::runtime_error{what};
  }

  // Enables key codes to be programmatically pressed/released.
  for (auto key_code : key_codes) {
    libevdev_enable_event_code(dev_, EV_KEY, key_code, nullptr);
  }

  err = libevdev_uinput_create_from_device(dev_, LIBEVDEV_UINPUT_OPEN_MANAGED,
                                           &uinput_dev_);
  if (err != 0) {
    auto what = Utils::FormatExceptionMessage(
      "Creating a uinput device from the newly created libevdev device",
      "The program does not have permission to open /dev/uinput in read/write "
      "mode",
      "The program must either be run with 'sudo' or the user must be a member "
      "of the input group");
    throw std::runtime_error{what};
  }
}

InputInjector::~InputInjector() {
  // The uinput device must be destroyed before freeing the libevdev device.
  libevdev_uinput_destroy(uinput_dev_);
  libevdev_free(dev_);
}

void InputInjector::Inject(const std::vector<uint32_t>& key_codes) {
  // TODO: rework this entire block of logic, This can be made much more
  // efficient.

  auto modifier_key_codes = std::list<uint32_t>{};

  for (size_t i = 0; i < key_codes.size(); ++i) {
    auto key_code = key_codes[i];
    switch (key_code) {
      case KEY_LEFTCTRL:
      case KEY_RIGHTCTRL:
      case KEY_LEFTSHIFT:
      case KEY_RIGHTSHIFT:
      case KEY_LEFTALT:
      case KEY_RIGHTALT:
      case KEY_LEFTMETA:
      case KEY_RIGHTMETA:
        PressKey(key_code);
        modifier_key_codes.push_front(key_code);
        break;
      default:
        PressKey(key_code);
        ReleaseKey(key_code);
        break;
    }
  }

  for (auto modifier_key_code : modifier_key_codes) {
    ReleaseKey(modifier_key_code);
  }
}

void InputInjector::PressKey(uint32_t key_code) {
  libevdev_uinput_write_event(uinput_dev_, EV_KEY, key_code, 1);
  libevdev_uinput_write_event(uinput_dev_, EV_SYN, SYN_REPORT, 0);
}

void InputInjector::ReleaseKey(uint32_t key_code) {
  libevdev_uinput_write_event(uinput_dev_, EV_KEY, key_code, 0);
  libevdev_uinput_write_event(uinput_dev_, EV_SYN, SYN_REPORT, 0);
}
