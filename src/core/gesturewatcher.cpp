#include "gesturewatcher.h"

#include <fcntl.h>
#include <libudev.h>
#include <poll.h>
#include <spdlog/spdlog.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <stdexcept>

#include "directorywatcher.h"
#include "gestureeventfactory.h"
#include "gesturesfile.h"
#include "paths.h"
#include "settingsfile.h"

GestureWatcher::GestureWatcher() {
  // Watches for changes to files in the app config directory.
  DirectoryWatcher::Initialize(Paths::ConfigAppDirectory());
  DirectoryWatcher::Watch();

  // Specifically watches for changes to the settings file.
  SettingsFile::Initialize();
  SettingsFile::Watch();

  // Specifically watches for changes to the gestures file.
  GesturesFile::Initialize(false);
  GesturesFile::Watch();

  spdlog::info("Initializing new udev context object");
  auto udev = udev_new();
  if (udev == nullptr) {
    auto what = "udev_new returned nullptr";
    spdlog::critical(what);
    throw std::runtime_error{what};
  }

  spdlog::info("Creating a new libinput context from udev");
  li_ = libinput_udev_create_context(&interface_, nullptr, udev);
  if (li_ == nullptr) {
    auto what =
      "Returned a nullptr libinput context while creating a new libinput; "
      "elevated privileges are required to read /dev/input";
    spdlog::critical(what);
    throw std::runtime_error{what};
  }

  spdlog::info("Assigning a seat to the libinput context");
  if (libinput_udev_assign_seat(li_, "seat0") == -1) {
    auto what = "libinput_udev_assign_seat returned -1";
    spdlog::critical(what);
    throw std::runtime_error{what};
  }
}

GestureWatcher::~GestureWatcher() { libinput_unref(li_); }

void GestureWatcher::Enable() {
  auto fd = libinput_get_fd(li_);
  auto fds = std::array<pollfd, 1>{{fd, POLLIN, 0}};
  while (poll(fds.data(), fds.size(), -1) != -1) {
    while (true) {
      libinput_dispatch(li_);
      auto event = libinput_get_event(li_);

      // Indicates that no event is available.
      if (event == nullptr) {
        libinput_event_destroy(event);
        break;
      }

      auto event_type = libinput_event_get_type(event);
      switch (event_type) {
        case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
        case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
        case LIBINPUT_EVENT_GESTURE_HOLD_BEGIN:
          gesture_event_ =
            GestureEventFactory::CreateGestureEvent(event, event_type);
          gesture_event_->Begin(event);
          break;
        case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
        case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
          gesture_event_->Update(event);
          break;
        case LIBINPUT_EVENT_GESTURE_SWIPE_END:
        case LIBINPUT_EVENT_GESTURE_PINCH_END:
        case LIBINPUT_EVENT_GESTURE_HOLD_END:
          gesture_event_->End(event);
          break;
        default:
          break;
      }

      libinput_event_destroy(event);
    }
  }
}

void GestureWatcher::CloseRestricted(int fd, void* user_data) { close(fd); }

int GestureWatcher::OpenRestricted(const char* path, int flags,
                                   void* user_data) {
  auto fd = open(path, flags);
  return fd < 0 ? -errno : fd;
}
