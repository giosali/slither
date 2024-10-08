#ifndef GESTURE_H
#define GESTURE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "json.hpp"

class Gesture {
 public:
  enum class Direction { kNone, kUp, kRight, kDown, kLeft, kIn, kOut };

  Gesture() = default;

  Direction GetDirection() const;
  size_t GetFingerCount() const;
  std::vector<uint32_t> GetKeyCodes() const;
  void SetDirection(Direction value);
  void SetFingerCount(size_t value);
  void SetKeyCodes(const std::vector<uint32_t>& value);

 private:
  friend void from_json(const nlohmann::json& j, Gesture& g);
  friend void to_json(nlohmann::json& j, const Gesture& g);

  Direction direction_;
  size_t finger_count_;
  std::vector<uint32_t> key_codes_;
};

// void from_json(const nlohmann::json& j, Gesture& g);
// void to_json(nlohmann::json& j, const Gesture& g);

#endif  // GESTURE_H
