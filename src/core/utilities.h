#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <string>
#include <vector>

class Utilities {
 public:
  Utilities() = delete;

  static std::string Join(const std::string& delimiter,
                          const std::vector<std::string>& elements);
  static std::string KeyCodeToString(uint32_t key_code);
};

#endif  // UTILITIES_H
