#ifndef SWIPEMONITOR_H
#define SWIPEMONITOR_H

#include <libinput.h>

#include "swipetracker.h"

class SwipeMonitor {
 public:
  SwipeMonitor();

  ~SwipeMonitor();

  void Enable();

 private:
  static void CloseRestricted(int fd, void* user_data);
  static int OpenRestricted(const char* path, int flags, void* user_data);

  libinput_interface interface_;
  libinput* li_;
  SwipeTracker swipe_tracker_;
};

#endif  // SWIPEMONITOR_H
