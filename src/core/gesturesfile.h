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

  static void AddGesture(const Gesture& gesture);
  static void DeleteGesture(const Gesture& gesture);
  static std::vector<uint32_t> FindGestureKeyCodes(Gesture::Direction direction,
                                                   int32_t finger_count);
  static std::vector<Gesture> GetGestures();
  static void Initialize(bool ignore_injector);
  static void ReplaceGesture(const Gesture& previous, const Gesture& current);
  static void Save();
  static void Watch();

 private:
  static void Create();
  static std::vector<Gesture> ReadGestures();
  static void SetGestures(const std::vector<Gesture>& value);

  static std::vector<Gesture> gestures_;
  static bool ignore_injector_;
  static std::mutex mtx_;
  static std::filesystem::path path_;
};

#endif  // GESTUREFILE_H
