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
  static constexpr std::string_view kDirectoryName = "slither";
  static constexpr std::string_view kFilename = "settings.json";
  static constexpr std::string_view kHomeVariable = "HOME";
  static constexpr std::string_view kXdgConfigVariable = "XDG_CONFIG_HOME";

  std::filesystem::path GetConfigDirectory() const;

  std::filesystem::path path_;
  std::vector<SwipeAction> swipe_actions_;
};

#endif  // CONFIGURATION_H
