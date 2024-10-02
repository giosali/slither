#include "swipetracker.h"

#include <cmath>

SwipeTracker::SwipeTracker()
    : is_gesture_valid_{false}, sx_{0}, sy_{0}, time_{0} {}

void SwipeTracker::Begin() {
  is_gesture_valid_ = false;
  sx_ = 0;
  sy_ = 0;
  time_ = 0;
}

void SwipeTracker::End(uint32_t time) {
  is_gesture_valid_ = time - time_ <= kTimeLimit;
}

SwipeTracker::Direction SwipeTracker::GetDirection() const {
  return direction_;
}

bool SwipeTracker::IsGestureValid() const { return is_gesture_valid_; }

void SwipeTracker::Update(double dx, double dy, uint32_t time) {
  sx_ += dx;
  sy_ += dy;

  // Handles horizontal swipes.
  if (std::abs(sx_) >= kThreshold) {
    time_ = time;
    direction_ = sx_ < 0 ? Direction::Left : Direction::Right;
    return;
  }

  // Handles vertical swipes.
  if (std::abs(sy_) >= kThreshold) {
    time_ = time;
    direction_ = sy_ < 0 ? Direction::Down : Direction::Up;
    return;
  }
}
