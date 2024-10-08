#include "swipeparser.h"

#include <cmath>

SwipeParser::SwipeParser()
    : direction_{Gesture::Direction::kNone},
      is_gesture_valid_{false},
      sx_{0},
      sy_{0},
      time_{0} {}

void SwipeParser::Begin() {
  direction_ = Gesture::Direction::kNone;
  is_gesture_valid_ = false;
  sx_ = 0;
  sy_ = 0;
  time_ = 0;
}

void SwipeParser::End(uint32_t time) {
  is_gesture_valid_ =
    direction_ != Gesture::Direction::kNone && time - time_ <= kTimeLimit;
}

Gesture::Direction SwipeParser::GetDirection() const { return direction_; }

bool SwipeParser::IsGestureValid() const { return is_gesture_valid_; }

void SwipeParser::Update(double dx, double dy, uint32_t time) {
  sx_ += dx;
  sy_ += dy;

  // Handles horizontal swipes.
  if (std::abs(sx_) >= kThreshold) {
    time_ = time;
    direction_ =
      sx_ < 0 ? Gesture::Direction::kLeft : Gesture::Direction::kRight;
    return;
  }

  // Handles vertical swipes.
  if (std::abs(sy_) >= kThreshold) {
    time_ = time;
    direction_ = sy_ < 0 ? Gesture::Direction::kDown : Gesture::Direction::kUp;
    return;
  }
}
