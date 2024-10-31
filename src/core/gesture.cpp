#include "gesture.h"

#include <format>

#include "utilities.h"

Gesture::Gesture(Type type, int32_t finger_count,
                 const std::vector<uint32_t>& key_codes)
    : type_{type}, finger_count_{finger_count}, key_codes_{key_codes} {}

int32_t Gesture::GetFingerCount() const { return finger_count_; }

std::vector<uint32_t> Gesture::GetKeyCodes() const { return key_codes_; }

Gesture::Type Gesture::GetType() const { return type_; }

void Gesture::SetFingerCount(int32_t value) { finger_count_ = value; }

void Gesture::SetKeyCodes(const std::vector<uint32_t>& value) {
  key_codes_ = value;
}

void Gesture::SetType(Type value) { type_ = value; }

std::string Gesture::ToString() const {
  auto type_rep = Utilities::ConvertGestureTypeToString(type_);

  auto key_code_reps = std::vector<std::string>{};
  for (auto key_code : key_codes_) {
    key_code_reps.push_back(Utilities::KeyCodeToString(key_code));
  }

  auto representation = Utilities::Join(" + ", key_code_reps);

  return std::format("{}: {}", type_rep, representation);
}

bool Gesture::operator==(const Gesture& gesture) const {
  return type_ == gesture.type_ && finger_count_ == gesture.finger_count_;
}

void from_json(const nlohmann::json& j, Gesture& g) {
  j.at("type").get_to(g.type_);
  j.at("fingerCount").get_to(g.finger_count_);
  j.at("keyCodes").get_to(g.key_codes_);
}

void to_json(nlohmann::json& j, const Gesture& g) {
  j = nlohmann::json{{"type", g.type_},
                     {"fingerCount", g.finger_count_},
                     {"keyCodes", g.key_codes_}};
}
