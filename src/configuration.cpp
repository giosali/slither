#include "configuration.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "json.hpp"
#include "paths.h"
#include "utils.h"

Configuration::Configuration()
    : path_{Paths::ConfigAppDirectory() / "settings.json"}, swipe_actions_{} {
  // Creates the settings file if it doesn't exist.
  if (!std::filesystem::exists(path_)) {
    // Creates any missing parent directories.
    std::filesystem::create_directories(path_.parent_path());

    auto stream = std::ofstream{path_};
    stream << "{}";
  }
}

void Configuration::UpdateSwipes() {
  auto stream = std::ifstream(path_);

  try {
    auto json = nlohmann::json::parse(stream);
    swipe_actions_ =
      json.at("actions").template get<std::vector<SwipeAction>>();
  } catch (const nlohmann::json::exception& e) {
    // Leaves swipe actions empty.
    std::cerr << e.what() << std::endl;
  }
}

std::vector<SwipeAction> Configuration::GetSwipeActions() const {
  return swipe_actions_;
}
