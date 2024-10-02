#include "gesturewatcher.h"

#include <fcntl.h>
#include <libudev.h>
#include <poll.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <format>
#include <stdexcept>

#include "utils.h"

GestureWatcher::GestureWatcher()
    : interface_{OpenRestricted, CloseRestricted}, swipe_tracker_{} {
  auto udev = udev_new();
  if (udev == nullptr) {
    auto what = Utils::FormatExceptionMessage(
      "Initializing new udev context object", "udev_new returned nullptr");
    throw std::runtime_error{what};
  }

  li_ = libinput_udev_create_context(&interface_, nullptr, udev);
  if (li_ == nullptr) {
    auto what = Utils::FormatExceptionMessage(
      "Creating a new libinput context from udev",
      "Returned a nullptr libinput context",
      "The user needs permission to read /dev/input. Either run this program "
      "via 'sudo' or run the following command: 'sudo gpasswd -a $USER input'");
    throw std::runtime_error{what};
  }

  if (libinput_udev_assign_seat(li_, "seat0") == -1) {
    auto what =
      Utils::FormatExceptionMessage("Assigning a seat to the libinput context",
                                    "libinput_udev_assign_seat returned -1");
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

      // Means that no event is available.
      if (event == nullptr) {
        libinput_event_destroy(event);
        break;
      }

      auto event_type = libinput_event_get_type(event);
      switch (event_type) {
        case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
          swipe_tracker_.Begin();
          break;
        case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE: {
          auto gesture_event = libinput_event_get_gesture_event(event);
          auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
          auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          swipe_tracker_.Update(dx, dy, time);
          break;
        }
        case LIBINPUT_EVENT_GESTURE_SWIPE_END: {
          auto gesture_event = libinput_event_get_gesture_event(event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          swipe_tracker_.End(time);

          if (swipe_tracker_.IsGestureValid()) {
            auto direction = swipe_tracker_.GetDirection();
            // TODO: handle gesture based on direction.
          }

          break;
        }
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
