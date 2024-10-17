#include "gesture.h"

#include <format>
#include <string_view>

#include "utilities.h"

Gesture::Direction Gesture::GetDirection() const { return direction_; }

int32_t Gesture::GetFingerCount() const { return finger_count_; }

std::vector<uint32_t> Gesture::GetKeyCodes() const { return key_codes_; }

void Gesture::SetDirection(Direction value) { direction_ = value; }

void Gesture::SetFingerCount(int32_t value) { finger_count_ = value; }

void Gesture::SetKeyCodes(const std::vector<uint32_t>& value) {
  key_codes_ = value;
}

std::string Gesture::ToString() const {
  auto direction = std::string{};
  switch (direction_) {
    case Direction::kNone:
      direction = "Hold";
      break;
    case Gesture::Direction::kUp:
      direction = "Up";
      break;
    case Direction::kRight:
      direction = "Right";
      break;
    case Direction::kDown:
      direction = "Down";
      break;
    case Direction::kLeft:
      direction = "Left";
      break;
    case Direction::kIn:
      direction = "In";
      break;
    case Direction::kOut:
      direction = "Out";
      break;
  }

  auto representations = std::vector<std::string>{};
  for (auto key_code : key_codes_) {
    representations.push_back(Utilities::KeyCodeToString(key_code));
  }

  auto representation = Utilities::Join(" + ", representations);

  constexpr auto final_fmt = std::string_view{"{}, {}"};
  return std::format(final_fmt, direction, representation);
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
