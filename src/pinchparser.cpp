#include "pinchparser.h"

#include <cmath>

PinchParser::PinchParser()
    : direction_{Gesture::Direction::kNone},
      is_gesture_valid_{false},
      sx_{},
      time_{} {}

void PinchParser::Begin() {
  direction_ = Gesture::Direction::kNone;
  is_gesture_valid_ = false;
  sx_ = 0;
  time_ = 0;
}

void PinchParser::End(uint32_t time) {
  is_gesture_valid_ =
    direction_ != Gesture::Direction::kNone && time - time_ <= kTimeLimit;
}

Gesture::Direction PinchParser::GetDirection() const { return direction_; }

bool PinchParser::IsGestureValid() const { return is_gesture_valid_; }

void PinchParser::Update(double dx, uint32_t time) {
  // The only thing that seems to matter when parsing the coordinates of a
  // pinch gesture is the x-coordinate. The y-coordinate will only change if
  // the user vertically moves their hand up and down while performing a pinch
  // gesture. That seems unlikely to ever happen while pinching; it's an
  // unnatural movement.
  // Even if the user has their fingers positioned perpendicular to the x-axis,
  // the gesture will be poorly detected. The y-coordinate seems useless.

  sx_ += dx;

  if (sx_ >= kPinchInThreshold) {
    time_ = time;
    direction_ = Gesture::Direction::kIn;
  } else if (sx_ <= kPinchOutThreshold) {
    time_ = time;
    direction_ = Gesture::Direction::kOut;
  }
}
