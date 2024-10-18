#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

class Utilities {
 public:
  Utilities() = delete;

  static inline auto EnumRange = [](auto front, auto back) {
    return std::views::iota(std::to_underlying(front),
                            std::to_underlying(back) + 1) |
           std::views::transform([](auto e) { return decltype(front)(e); });
  };
  static std::string Join(const std::string& delimiter,
                          const std::vector<std::string>& elements);
  static std::string KeyCodeToString(uint32_t key_code);
};

#endif  // UTILITIES_H
