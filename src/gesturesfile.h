#ifndef GESTUREFILE_H
#define GESTUREFILE_H

#include <filesystem>
#include <vector>

#include "gesture.h"

class GesturesFile {
 public:
  GesturesFile();

  std::vector<Gesture> GetGestures() const;
  void Watch();

 private:
  void UpdateGestures();

  std::vector<Gesture> gestures_;
  std::filesystem::path path_;
};

#endif  // GESTUREFILE_H
