#include "configuration.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "json.hpp"
#include "utils.h"

Configuration::Configuration()
    : path_{GetConfigDirectory() / kDirectoryName / kFilename},
      swipe_actions_{} {
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

std::filesystem::path Configuration::GetConfigDirectory() const {
  auto value = std::getenv(kXdgConfigVariable.data());

  // Means that $XDG_CONFIG_HOME is defined and returns it.
  if (value != nullptr) {
    return value;
  }

  value = std::getenv(kHomeVariable.data());

  // Means that $HOME is undefined.
  if (value == nullptr) {
    auto what = Utils::FormatExceptionMessage(
      "Attempting to retrieve the base directory relative to which "
      "user-specific configuration files should be stored",
      "The user's $HOME environment variable is null", R"(¯\_(ツ)_/¯)");
    throw std::runtime_error{what};
  }

  return std::filesystem::path{value} / ".config";
}
