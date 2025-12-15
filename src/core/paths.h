#ifndef PATHS_H
#define PATHS_H

#include <filesystem>

class Paths {
 public:
  Paths() = delete;

  static std::filesystem::path ConfigAppDirectory();
  static std::filesystem::path ConfigDirectory();
  static std::filesystem::path HomeDirectory();
};

#endif  // PATHS_H
