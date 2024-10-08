#include "paths.h"

#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string_view>

#include "utils.h"

std::filesystem::path Paths::ConfigAppDirectory() {
  return ConfigDirectory() / "slither";
}

std::filesystem::path Paths::ConfigDirectory() {
  return HomeDirectory() / ".config";
}

std::filesystem::path Paths::HomeDirectory() {
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

  auto home_directory = std::string{value};

  // Means the user is running the application through sudo.
  // If the user runs the application through sudo, $HOME evaluates to /root.
  // However, we need $HOME to evaluate to /home/<user> instead.
  if (home_directory == "/root") {
    auto sudo_user = std::getenv("SUDO_USER");
    if (sudo_user != nullptr) {
      constexpr auto fmt = std::string_view{"/home/{}"};
      home_directory = std::format(fmt, sudo_user);
    }
  }

  return home_directory;
}
