#ifndef PINCHPARSER_H
#define PINCHPARSER_H

#include <cstdint>

#include "gesture.h"

class PinchParser {
 public:
  PinchParser();

  void Begin();
  void End(uint32_t time);
  Gesture::Direction GetDirection() const;
  bool IsGestureValid() const;
  void Update(double dx, uint32_t time);

 private:
  static constexpr double kPinchInThreshold = 40;
  static constexpr double kPinchOutThreshold = -20;
  static constexpr uint32_t kTimeLimit = 250;

  Gesture::Direction direction_;
  bool is_gesture_valid_;
  double sx_;
  uint32_t time_;
};

#endif  // PINCHPARSER_H
