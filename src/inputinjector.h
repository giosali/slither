#ifndef INPUTINJECTOR_H
#define INPUTINJECTOR_H

#include <cstdint>
#include <vector>

class InputInjector {
 public:
  InputInjector() = delete;

  static void Inject(const std::vector<uint32_t>& key_codes);
};

#endif  // INPUTINJECTOR_H
