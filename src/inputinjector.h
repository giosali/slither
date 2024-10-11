#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include <cstdint>
#include <vector>

class InputInjector {
 public:
  InputInjector() = delete;

  static void Inject(const std::vector<uint32_t>& key_codes);

 private:
  static void Write(bool press, libevdev_uinput* uinput_dev,
                    const std::vector<uint32_t>& key_codes);
};

#endif  // INPUTINJECTOR_H
