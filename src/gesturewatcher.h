#ifndef GESTUREWATCHER_H
#define GESTUREWATCHER_H

#include <libinput.h>

#include "swipeparser.h"

class GestureWatcher {
 public:
  GestureWatcher();

  ~GestureWatcher();

  void Enable();

 private:
  static void CloseRestricted(int fd, void* user_data);
  static int OpenRestricted(const char* path, int flags, void* user_data);

  libinput_interface interface_;
  libinput* li_;
  SwipeParser swipe_parser_;
};

#endif  // GESTUREWATCHER_H
