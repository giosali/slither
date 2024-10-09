#ifndef GESTUREFILE_H
#define GESTUREFILE_H

#include <filesystem>
#include <functional>
#include <vector>

#include "gesture.h"

class GesturesFile {
 public:
  GesturesFile();

  std::vector<Gesture> GetGestures() const;
  void SetCallback(const std::function<void(std::vector<Gesture>)>& value);
  void Watch();

 private:
  void UpdateGestures();

  std::function<void(std::vector<Gesture>)> callback_;
  std::vector<Gesture> gestures_;
  std::filesystem::path path_;
};

#endif  // GESTUREFILE_H
