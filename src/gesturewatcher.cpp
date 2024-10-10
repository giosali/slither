#include "gesturewatcher.h"

#include <fcntl.h>
#include <libudev.h>
#include <poll.h>
#include <spdlog/spdlog.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <stdexcept>

GestureWatcher::GestureWatcher()
    : converter_{},
      hold_parser_{},
      interface_{OpenRestricted, CloseRestricted},
      pinch_parser_{},
      swipe_parser_{} {
  spdlog::info("Entering GestureWatcher::GestureWatcher");

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

  spdlog::info("Exiting GestureWatcher::GestureWatcher");
}

GestureWatcher::~GestureWatcher() { libinput_unref(li_); }

void GestureWatcher::Enable() {
  spdlog::info("Entered GestureWatcher::Enable");

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
          spdlog::info("Beginning swipe");

          swipe_parser_.Begin();
          break;
        case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE: {
          spdlog::info("Updating swipe");

          auto gesture_event = libinput_event_get_gesture_event(event);
          auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
          auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          swipe_parser_.Update(dx, dy, time);
          break;
        }
        case LIBINPUT_EVENT_GESTURE_SWIPE_END: {
          spdlog::info("Ending swipe");

          auto gesture_event = libinput_event_get_gesture_event(event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          swipe_parser_.End(time);

          if (swipe_parser_.IsGestureValid()) {
            auto direction = swipe_parser_.GetDirection();
            auto finger_count =
              libinput_event_gesture_get_finger_count(gesture_event);
            converter_.ConvertGesture(direction, finger_count);
          }

          break;
        }
        case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
          spdlog::info("Beginning pinch");

          pinch_parser_.Begin();
          break;
        case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE: {
          spdlog::info("Updating pinch");

          auto gesture_event = libinput_event_get_gesture_event(event);
          auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
          auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          pinch_parser_.Update(dx, time);
          break;
        }
        case LIBINPUT_EVENT_GESTURE_PINCH_END: {
          spdlog::info("Ending pinch");

          auto gesture_event = libinput_event_get_gesture_event(event);
          auto time = libinput_event_gesture_get_time(gesture_event);
          pinch_parser_.End(time);

          if (pinch_parser_.IsGestureValid()) {
            auto direction = pinch_parser_.GetDirection();
            auto finger_count =
              libinput_event_gesture_get_finger_count(gesture_event);
            converter_.ConvertGesture(direction, finger_count);
          }
          break;
        }
        case LIBINPUT_EVENT_GESTURE_HOLD_BEGIN: {
          spdlog::info("Beginning hold");

          auto gesture_event = libinput_event_get_gesture_event(event);
          auto finger_count =
            libinput_event_gesture_get_finger_count(gesture_event);
          hold_parser_.Begin(finger_count);
          break;
        }
        case LIBINPUT_EVENT_GESTURE_HOLD_END:
          spdlog::info("Ending hold");

          hold_parser_.End();
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
