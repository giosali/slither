#include "swipemonitor.h"

#include <fcntl.h>
#include <libudev.h>
#include <poll.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <iostream>
#include <stdexcept>

#include "utils.h"

SwipeMonitor::SwipeMonitor() : interface_{OpenRestricted, CloseRestricted} {
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

SwipeMonitor::~SwipeMonitor() { libinput_unref(li_); }

void SwipeMonitor::Enable() const {
  auto fd = libinput_get_fd(li_);
  auto fds = std::array<pollfd, 1>{{fd, POLLIN, 0}};
  while (poll(fds.data(), fds.size(), -1) != -1) {
    do {
      libinput_dispatch(li_);
      auto event = libinput_get_event(li_);
      if (event == nullptr) {
        libinput_event_destroy(event);
        break;
      }

      auto libinput_event_type = libinput_event_get_type(event);
      switch (libinput_event_type) {
        case LIBINPUT_EVENT_KEYBOARD_KEY:
          auto keyboard_event = libinput_event_get_keyboard_event(event);
          auto key = libinput_event_keyboard_get_key(keyboard_event);
          std::cout << "key = " << key << std::endl;
          break;
      }

      libinput_event_destroy(event);
    } while (true);
  }
}

void SwipeMonitor::CloseRestricted(int fd, void* user_data) { close(fd); }

int SwipeMonitor::OpenRestricted(const char* path, int flags, void* user_data) {
  auto fd = open(path, flags);
  return fd < 0 ? -errno : fd;
}
