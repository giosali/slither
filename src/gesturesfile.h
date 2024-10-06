#ifndef GESTUREFILE_H
#define GESTUREFILE_H

#include <filesystem>
#include <vector>

#include "gesture.h"

class GesturesFile {
 public:
  GesturesFile();
  explicit GesturesFile(const std::filesystem::path& path);

  std::vector<Gesture> GetGestures() const;
  void Watch();

 private:
  std::vector<Gesture> gestures_;
  std::filesystem::path path_;
};

#endif  // GESTUREFILE_H
