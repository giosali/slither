#ifndef GESTUREFILE_H
#define GESTUREFILE_H

#include <cstdint>
#include <filesystem>
#include <mutex>
#include <vector>

#include "gesture.h"

class GesturesFile {
 public:
  GesturesFile() = delete;

  static std::vector<uint32_t> FindGestureKeyCodes(Gesture::Direction direction,
                                                   int32_t finger_count);
  static std::vector<Gesture> GetGestures();
  static void Initialize();
  static void Watch();

 private:
  static void UpdateGestures();

  static std::vector<Gesture> gestures_;
  static std::mutex mtx_;
  static std::filesystem::path path_;
};

#endif  // GESTUREFILE_H
