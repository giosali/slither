#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <libevdev/libevdev-uinput.h>
#include <libevdev/libevdev.h>

#include <cstdint>
#include <unordered_set>
#include <vector>

class InputInjector {
 public:
  InputInjector();
  explicit InputInjector(const std::unordered_set<int>& key_codes);

  ~InputInjector();

  void Inject(const std::vector<uint32_t>& key_codes);

 private:
  void PressKey(uint32_t key_code);
  void ReleaseKey(uint32_t key_code);

  libevdev* dev_;
  libevdev_uinput* uinput_dev_;
};

#endif  // INPUTINJECTOR_H
