#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <libevdev/libevdev-uinput.h>
#include <libevdev/libevdev.h>

#include <vector>

class InputInjector {
 public:
  explicit InputInjector(const std::vector<std::vector<int>>& key_code_groups);

  ~InputInjector();

  void Inject(unsigned int code);

 private:
  libevdev* dev_;
  libevdev_uinput* uinput_dev_;
};

#endif  // INPUTINJECTOR_H
