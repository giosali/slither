#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>

#include "json.hpp"

class Settings {
 public:
  enum class PinchSensitivity { kLow = 10, kMedium = 20, kHigh = 40 };
  enum class SwipeSensitivity {
    kVeryLow = 35,
    kLow = 50,
    kMedium = 70,
    kHigh = 90,
    kVeryHigh = 105
  };

  Settings() = default;

  int64_t GetHoldTime() const;
  PinchSensitivity GetPinchSensitivity() const;
  SwipeSensitivity GetSwipeSensitivity() const;
  void SetHoldTime(int64_t value);
  void SetPinchSensitivity(PinchSensitivity value);
  void SetSwipeSensitivity(SwipeSensitivity value);

 private:
  int64_t hold_time_{500};
  PinchSensitivity pinch_sensitivity_{PinchSensitivity::kMedium};
  SwipeSensitivity swipe_sensitivity_{SwipeSensitivity::kMedium};

  friend void from_json(const nlohmann::json& j, Settings& s);
  friend void to_json(nlohmann::json& j, const Settings& s);
};

#endif  // SETTINGS_H
