#include "swipeaction.h"

void to_json(nlohmann::json& j, const SwipeAction& sa) {
  j = nlohmann::json{{"direction", sa.direction},
                     {"fingerCount", sa.finger_count},
                     {"keyCodes", sa.key_codes}};
}

void from_json(const nlohmann::json& j, SwipeAction& sa) {
  j.at("direction").get_to(sa.direction);
  j.at("fingerCount").get_to(sa.finger_count);
  j.at("keyCodes").get_to(sa.key_codes);
}