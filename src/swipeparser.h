#ifndef SWIPEPARSER_H
#define SWIPEPARSER_H

#include <cstdint>

#include "gesture.h"

// https://wayland.freedesktop.org/libinput/doc/latest/normalization-of-relative-motion.html
class SwipeParser {
 public:
  SwipeParser();

  void Begin();
  void End(uint32_t time);
  Gesture::Direction GetDirection() const;
  bool IsGestureValid() const;
  void Update(double dx, double dy, uint32_t time);

 private:
  static constexpr double kThreshold = 125;
  static constexpr double kTimeLimit = 250;

  Gesture::Direction direction_;
  bool is_gesture_valid_;
  double sx_;
  double sy_;
  uint32_t time_;
};

#endif  // SWIPEPARSER_H
