#ifndef STANDARDPATHS_H
#define STANDARDPATHS_H

#include <filesystem>

class StandardPaths {
 public:
  StandardPaths() = delete;

  static std::filesystem::path ConfigAppDirectory();
  static std::filesystem::path ConfigDirectory();
  static std::filesystem::path HomeDirectory();
};

#endif  // STANDARDPATHS_H
