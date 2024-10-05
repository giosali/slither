#ifndef STANDARDPATHS_H
#define STANDARDPATHS_H

#include <filesystem>
#include <string_view>

class StandardPaths {
 public:
  StandardPaths() = delete;

  static std::filesystem::path ConfigDirectory();
  static std::filesystem::path HomeDirectory();

 private:
  static constexpr std::string_view kHomeVariable = "HOME";
  static constexpr std::string_view kXdgConfigVariable = "XDG_CONFIG_HOME";
};

#endif  // STANDARDPATHS_H
