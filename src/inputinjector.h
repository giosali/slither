#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <libevdev/libevdev-uinput.h>
#include <libevdev/libevdev.h>

class InputInjector {
 public:
  InputInjector();

  ~InputInjector();

  void Inject(unsigned int code);

 private:
  libevdev* dev_;
  libevdev_uinput* uinput_dev_;
};

#endif  // INPUTINJECTOR_H
