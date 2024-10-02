#ifndef SWIPEACTION_H
#define SWIPEACTION_H

#include <vector>

#include "json.hpp"
#include "swipe.h"

struct SwipeAction {
  Swipe::Direction direction;
  size_t finger_count;
  std::vector<int> key_codes;
};

void to_json(nlohmann::json& j, const SwipeAction& sa);

void from_json(const nlohmann::json& j, SwipeAction& sa);

#endif  // SWIPEACTION_H
