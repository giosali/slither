#include "gesture.h"

#include <format>

#include "utilities.h"

Gesture::Gesture(Direction direction, int32_t finger_count,
                 const std::vector<uint32_t>& key_codes)
    : direction_{direction},
      finger_count_{finger_count},
      key_codes_{key_codes} {}

std::string Gesture::StringifyDirection(Direction direction) {
  switch (direction) {
    case Direction::kNone:
      return "Hold";
    case Direction::kUp:
      return "Swipe Up";
    case Direction::kRight:
      return "Swipe Right";
    case Direction::kDown:
      return "Swipe Down";
    case Direction::kLeft:
      return "Swipe Left";
    case Direction::kIn:
      return "Pinch Inward";
    case Direction::kOut:
      return "Pinch Outward";
    default:
      return "";
  }
}

Gesture::Direction Gesture::GetDirection() const { return direction_; }

int32_t Gesture::GetFingerCount() const { return finger_count_; }

std::vector<uint32_t> Gesture::GetKeyCodes() const { return key_codes_; }

void Gesture::SetDirection(Direction value) { direction_ = value; }

void Gesture::SetFingerCount(int32_t value) { finger_count_ = value; }

void Gesture::SetKeyCodes(const std::vector<uint32_t>& value) {
  key_codes_ = value;
}

std::string Gesture::ToString() const {
  auto direction = StringifyDirection(direction_);

  auto representations = std::vector<std::string>{};
  for (auto key_code : key_codes_) {
    representations.push_back(Utilities::KeyCodeToString(key_code));
  }

  auto representation = Utilities::Join(" + ", representations);

  return std::format("{}: {}", direction, representation);
}

bool Gesture::operator==(const Gesture& gesture) const {
  return direction_ == gesture.direction_ &&
         finger_count_ == gesture.finger_count_;
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
