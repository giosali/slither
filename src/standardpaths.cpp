#include "standardpaths.h"

#include <cstdlib>
#include <stdexcept>

#include "utils.h"

std::filesystem::path StandardPaths::ConfigDirectory() {
  return HomeDirectory() / ".config";
}

std::filesystem::path StandardPaths::HomeDirectory() {
  auto value = std::getenv("HOME");
  if (value == nullptr) {
    value = std::getenv("XDG_CONFIG_HOME");

    // Means that $HOME is undefined.
    if (value == nullptr) {
      auto what = Utils::FormatExceptionMessage(
        "Attempting to retrieve the base directory relative to which "
        "user-specific configuration files should be stored",
        "The user's $HOME environment variable is null", R"(¯\_(ツ)_/¯)");
      throw std::runtime_error{what};
    }
  }

  return value;
}
