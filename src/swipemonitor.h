#ifndef SWIPEMONITOR_H
#define SWIPEMONITOR_H

#include <libinput.h>

class SwipeMonitor {
 public:
  SwipeMonitor();

  ~SwipeMonitor();

  void Enable() const;

 private:
  static void CloseRestricted(int fd, void* user_data);
  static int OpenRestricted(const char* path, int flags, void* user_data);

  libinput_interface interface_;
  libinput* li_;
};

#endif  // SWIPEMONITOR_H
