#ifndef GESTURE_H
#define GESTURE_H

#include <cstdint>
#include <string>
#include <vector>

#include "json.hpp"

class Gesture {
 public:
  enum class Type { kNone, kUp, kRight, kDown, kLeft, kIn, kOut, kHold };

  Gesture() = default;
  Gesture(Type type, int32_t finger_count,
          const std::vector<uint32_t>& key_codes);

  int32_t GetFingerCount() const;
  std::vector<uint32_t> GetKeyCodes() const;
  Type GetType() const;
  void SetFingerCount(int32_t value);
  void SetKeyCodes(const std::vector<uint32_t>& value);
  void SetType(Type value);
  std::string ToString() const;
  bool operator==(const Gesture& gesture) const;

 private:
  friend void from_json(const nlohmann::json& j, Gesture& g);
  friend void to_json(nlohmann::json& j, const Gesture& g);

  Type type_{};
  int32_t finger_count_{};
  std::vector<uint32_t> key_codes_{};
};

#endif  // GESTURE_H
