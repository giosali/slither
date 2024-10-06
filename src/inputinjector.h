#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <libevdev/libevdev-uinput.h>
#include <libevdev/libevdev.h>

#include <unordered_set>

class InputInjector {
 public:
  InputInjector();
  explicit InputInjector(const std::unordered_set<int>& key_codes);

  ~InputInjector();

  void Inject(unsigned int code);

 private:
  libevdev* dev_;
  libevdev_uinput* uinput_dev_;
};

#endif  // INPUTINJECTOR_H
