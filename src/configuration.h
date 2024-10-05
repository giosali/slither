#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <filesystem>
#include <string_view>
#include <vector>

#include "swipeaction.h"

class Configuration {
 public:
  Configuration();

  std::vector<SwipeAction> GetSwipeActions() const;
  void UpdateSwipes();

 private:
  std::filesystem::path path_;
  std::vector<SwipeAction> swipe_actions_;
};

#endif  // CONFIGURATION_H
