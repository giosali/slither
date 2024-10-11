#include "gesture.h"

Gesture::Direction Gesture::GetDirection() const { return direction_; }

int32_t Gesture::GetFingerCount() const { return finger_count_; }

std::vector<uint32_t> Gesture::GetKeyCodes() const { return key_codes_; }

void Gesture::SetDirection(Direction value) { direction_ = value; }

void Gesture::SetFingerCount(int32_t value) { finger_count_ = value; }

void Gesture::SetKeyCodes(const std::vector<uint32_t>& value) {
  key_codes_ = value;
}

bool Gesture::operator==(const Gesture& g) {
  return direction_ == g.direction_ && finger_count_ == g.finger_count_;
}

void from_json(const nlohmann::json& j, Gesture& g) {
  j.at("direction").get_to(g.direction_);
  j.at("fingerCount").get_to(g.finger_count_);
  j.at("keyCodes").get_to(g.key_codes_);
}

void to_json(nlohmann::json& j, const Gesture& g) {
  j = nlohmann::json{{"direction", g.direction_},
                     {"fingerCount", g.finger_count_},
                     {"keyCodes", g.key_codes_}};
}
