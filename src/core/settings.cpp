#include "settings.h"

int64_t Settings::GetHoldTime() const { return hold_time_; }

Settings::PinchSensitivity Settings::GetPinchSensitivity() const {
  return pinch_sensitivity_;
}

Settings::SwipeSensitivity Settings::GetSwipeSensitivity() const {
  return swipe_sensitivity_;
}

void Settings::SetHoldTime(int64_t value) { hold_time_ = value; }

void Settings::SetPinchSensitivity(Settings::PinchSensitivity value) {
  pinch_sensitivity_ = value;
}

void Settings::SetSwipeSensitivity(Settings::SwipeSensitivity value) {
  swipe_sensitivity_ = value;
}

void from_json(const nlohmann::json& j, Settings& s) {
  auto value = "holdTime";
  if (j.contains(value)) {
    j.at(value).get_to(s.hold_time_);
  }

  value = "pinchSensitivity";
  if (j.contains(value)) {
    j.at(value).get_to(s.pinch_sensitivity_);
  }

  value = "swipeSensitivity";
  if (j.contains(value)) {
    j.at(value).get_to(s.pinch_sensitivity_);
  }
}

void to_json(nlohmann::json& j, const Settings& s) {
  j = nlohmann::json{{"holdTime", s.hold_time_},
                     {"pinchSensitivity", s.pinch_sensitivity_},
                     {"swipeSensitivity", s.swipe_sensitivity_}};
}
