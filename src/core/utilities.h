#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "gesture.h"
#include "settings.h"

class Utilities {
 public:
  Utilities() = delete;

  static std::string ConvertDirectionToString(Gesture::Direction direction);
  static std::string ConvertPinchSensitivityToString(
    Settings::PinchSensitivity sensitivity);
  static Gesture::Direction ConvertStringToDirection(const std::string& s);
  static std::string ConvertSwipeSensitivityToString(
    Settings::SwipeSensitivity sensitivity);
  static inline auto EnumRange = [](auto front, auto back) {
    return std::views::iota(std::to_underlying(front),
                            std::to_underlying(back) + 1) |
           std::views::transform([](auto e) { return decltype(front)(e); });
  };
  static bool IsModifierKey(uint32_t key_code);
  static bool IsShiftKey(uint32_t key_code);
  static std::string Join(const std::string& delimiter,
                          const std::vector<std::string>& elements);
  static std::string KeyCodeToString(uint32_t key_code);

 private:
  static constexpr std::string kHoldText{"Hold"};
  static constexpr std::string kUpText{"Swipe Up"};
  static constexpr std::string kRightText{"Swipe Right"};
  static constexpr std::string kDownText{"Swipe Down"};
  static constexpr std::string kLeftText{"Swipe Left"};
  static constexpr std::string kInText{"Pinch In"};
  static constexpr std::string kOutText{"Pinch Out"};
};

#endif  // UTILITIES_H
