#include "inputinjector.h"

#include <libevdev/libevdev-uinput.h>
#include <libevdev/libevdev.h>

#include <chrono>
#include <thread>

void InputInjector::Inject(const std::vector<uint32_t>& key_codes) {
  auto dev = libevdev_new();
  libevdev_set_name(dev, "Slither Device");
  libevdev_enable_event_type(dev, EV_KEY);

  for (size_t i = 0; i < key_codes.size(); ++i) {
    libevdev_enable_event_code(dev, EV_KEY, key_codes[i], nullptr);
  }

  libevdev_uinput* uinput_dev = nullptr;
  libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED,
                                     &uinput_dev);

  // This time delay is necessary to give enough time for the uinput device to
  // be created.
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Simulates key presses.
  for (size_t i = 0; i < key_codes.size(); ++i) {
    libevdev_uinput_write_event(uinput_dev, EV_KEY, key_codes[i], 1);
  }

  // Syncs keyboard events.
  libevdev_uinput_write_event(uinput_dev, EV_SYN, SYN_REPORT, 0);

  // This time delay is necessary to simulate the average duration between key
  // presses and key releases.
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Simulates key releases.
  for (int32_t i = key_codes.size() - 1; i >= 0; --i) {
    libevdev_uinput_write_event(uinput_dev, EV_KEY, key_codes[i], 0);
  }

  // Syncs keyboard events.
  libevdev_uinput_write_event(uinput_dev, EV_SYN, SYN_REPORT, 0);

  // This time delay seems to be necessary to allow for pinch gestures to work
  // for some reason.
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // The uinput device must be destroyed before freeing the libevdev device.
  libevdev_uinput_destroy(uinput_dev);
  libevdev_free(dev);
}
