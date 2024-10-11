#include "inputinjector.h"

#include <spdlog/spdlog.h>

#include <chrono>
#include <cstring>
#include <thread>

void InputInjector::Inject(const std::vector<uint32_t>& key_codes) {
  spdlog::info("Entering InputInjector::Inject");

  auto dev = libevdev_new();
  libevdev_set_name(dev, "Slither Device");

  spdlog::info("Enabling event type EV_KEY");
  auto err = libevdev_enable_event_type(dev, EV_KEY);
  if (err == -1) {
    spdlog::error("Failed to enable event type EV_KEY");
    return;
  }

  for (size_t i = 0; i < key_codes.size(); ++i) {
    auto key_code = key_codes[i];
    spdlog::debug("Enabling event code {}", key_code);
    err = libevdev_enable_event_code(dev, EV_KEY, key_code, nullptr);
    if (err == -1) {
      spdlog::error("Failed to enable event key code: {}", key_code);
    }
  }

  libevdev_uinput* uinput_dev = nullptr;

  spdlog::info("Creating uinput device based on given libevdev device");
  err = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED,
                                           &uinput_dev);
  if (err != 0) {
    spdlog::error(
      "Failed to create uinput device; elevated privileges required to access "
      "/dev/uinput (errno: {}, strerror: {})",
      -err, std::strerror(-err));
    return;
  }

  // This time delay is necessary to give enough time for the uinput device to
  // be created.
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // I don't think a time delay is necessary between key presses and key
  // releases, but a rather long time delay is necessary before pressing a key
  // for some reason.
  Write(true, uinput_dev, key_codes);
  Write(false, uinput_dev, key_codes);

  // This time delay seems to be necessary to allow for pinch gestures to work
  // for some reason.
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // The uinput device must be destroyed before freeing the libevdev device.
  libevdev_uinput_destroy(uinput_dev);
  libevdev_free(dev);

  spdlog::info("Exiting InputInjector::Inject");
}

void InputInjector::Write(bool press, libevdev_uinput* uinput_dev,
                          const std::vector<uint32_t>& key_codes) {
  auto err = int32_t{0};

  if (press) {
    // Simulates key presses.
    spdlog::info("Simulating key presses");
    for (size_t i = 0; i < key_codes.size(); ++i) {
      auto key_code = key_codes[i];
      spdlog::debug("Value of key_code: {}", key_code);
      err = libevdev_uinput_write_event(uinput_dev, EV_KEY, key_code, 1);

      if (err != 0) {
        spdlog::error(
          "Failed to simulate key release for key code: {} (errno: {}, "
          "strerror: "
          "{})",
          key_code, -err, std::strerror(-err));
      }
    }
  } else {
    // Simulates key releases.
    spdlog::info("Simulating key releases");
    for (int32_t i = key_codes.size() - 1; i >= 0; --i) {
      auto key_code = key_codes[i];
      spdlog::debug("Value of key_code: {}", key_code);
      err = libevdev_uinput_write_event(uinput_dev, EV_KEY, key_code, 0);

      if (err != 0) {
        spdlog::error(
          "Failed to simulate key release for key code: {} (errno: {}, "
          "strerror: "
          "{})",
          key_code, -err, std::strerror(-err));
      }
    }
  }

  // Syncs keyboard events.
  err = libevdev_uinput_write_event(uinput_dev, EV_SYN, SYN_REPORT, 0);
  if (err != 0) {
    spdlog::error("Failed to sync key event (errno: {}, strerror: {})", -err,
                  std::strerror(-err));
  }
}
