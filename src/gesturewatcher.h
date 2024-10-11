#ifndef GESTUREWATCHER_H
#define GESTUREWATCHER_H

#include <libinput.h>

#include <memory>

#include "gestureevent.h"

class GestureWatcher {
 public:
  GestureWatcher();

  ~GestureWatcher();

  void Enable();

 private:
  static void CloseRestricted(int fd, void* user_data);
  static int OpenRestricted(const char* path, int flags, void* user_data);

  std::unique_ptr<GestureEvent> gesture_event_;
  libinput_interface interface_;
  libinput* li_;
};

#endif  // GESTUREWATCHER_H
