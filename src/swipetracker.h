#ifndef SWIPETRACKER_H
#define SWIPETRACKER_H

#include <cstdint>

// https://wayland.freedesktop.org/libinput/doc/latest/normalization-of-relative-motion.html
class SwipeTracker {
 public:
  enum class Direction { Up, Right, Down, Left };

  SwipeTracker();

  void Begin();
  void End(uint32_t time);
  Direction GetDirection() const;
  bool IsGestureValid() const;
  void Update(double dx, double dy, uint32_t time);

 private:
  static constexpr double kThreshold = 125;
  static constexpr double kTimeLimit = 250;

  Direction direction_;
  bool is_gesture_valid_;
  double sx_;
  double sy_;
  uint32_t time_;
};

#endif
