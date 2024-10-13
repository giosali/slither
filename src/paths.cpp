#include "paths.h"

#include <spdlog/spdlog.h>

#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string_view>

std::filesystem::path Paths::ConfigAppDirectory() {
  return ConfigDirectory() / "slither";
}

std::filesystem::path Paths::ConfigDirectory() {
  return HomeDirectory() / ".config";
}

std::filesystem::path Paths::HomeDirectory() {
  spdlog::info("Retrieving the home directory via environment variables");
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

  auto home_directory = std::string{value};

  // Means the user is running the application through sudo.
  // If the user runs the application through sudo, $HOME evaluates to /root.
  // However, we need $HOME to evaluate to /home/<user> instead.
  if (home_directory == "/root") {
    spdlog::info("Program is being run as root");

    auto sudo_user = std::getenv("SUDO_USER");
    if (sudo_user != nullptr) {
      constexpr auto fmt = std::string_view{"/home/{}"};
      home_directory = std::format(fmt, sudo_user);
    } else {
      spdlog::warn("$SUDO_USER is undefined");
    }
  }

  spdlog::debug("Value of home_directory: {}", home_directory);
  return home_directory;
}
