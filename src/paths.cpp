#include "paths.h"

#include <spdlog/spdlog.h>

#include <cstdlib>
#include <stdexcept>

std::filesystem::path Paths::ConfigAppDirectory() {
  return ConfigDirectory() / "slither";
}

std::filesystem::path Paths::ConfigDirectory() {
  return HomeDirectory() / ".config";
}

std::filesystem::path Paths::HomeDirectory() {
  spdlog::info("Retrieving home directory via environment variables");
  auto value = std::getenv("HOME");
  if (value == nullptr) {
    value = std::getenv("XDG_CONFIG_HOME");

    // Means that $HOME is undefined.
    if (value == nullptr) {
      auto what = "Unable to retrieve home directory; $HOME is undefined";
      spdlog::critical(what);
      throw std::runtime_error{what};
    }
  }

  return value;
}
