#include "pinchgestureevent.h"

#include <spdlog/spdlog.h>

#include <cmath>

#include "gesturesfile.h"
#include "inputinjector.h"

PinchGestureEvent::PinchGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void PinchGestureEvent::Begin(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("In PinchGestureEvent::Begin(libinput_event*): time = {}",
                time);

  time_ = time;
}

void PinchGestureEvent::End(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("In PinchGestureEvent::End(libinput_event*): time = {}", time);

  auto time_diff = time - time_;
  if (direction_ == Gesture::Direction::kNone || time_diff > kTimeLimit) {
    spdlog::info(
      "In PinchGestureEvent::End(libinput_event*): direction_ or time_diff is "
      "invalid");
    spdlog::debug(
      "In PinchGestureEvent::End(libinput_event*): direction_ = {}, time_diff "
      "= {}",
      static_cast<int>(direction_), time_diff);
    return;
  }

  if (auto key_codes =
        GesturesFile::FindGestureKeyCodes(direction_, finger_count_);
      !key_codes.empty()) {
    InputInjector::Inject(key_codes);
  }
}

void PinchGestureEvent::Update(libinput_event* event) {
  // It's important to keep track of the y-coordinate when monitoring pinches.
  // If the user performs an inward pinch with their right hand, the
  // x-coordinate sum appears to be positive as expected.
  // However, if the user pefroms an inward pinch with their left hand, the
  // x-coordinate sum now appears to be negative. If we only tracked pinch
  // gestures' x-coordinate values, an left-handed inward pinch would be
  // interpreted as a right-handed outward pinch. Therefore, it's important to
  // keep track of the y-coordinate when monitoring pinches.
  //
  // An inward pinch, regardless of handedness, always produces a positive
  // y-coordinate sum. Likewise, an outward pinch always produces a negative
  // y-coordinate sum.

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;
  sy_ += dy;

  auto sxy = std::abs(sx_) + std::abs(sy_);
  spdlog::debug("In PinchGestureEvent::Update(libinput_event*): sxy = {}", sxy);

  if (sxy < kPinchThreshold) {
    return;
  }

  spdlog::info("Pinch threshold met");
  time_ = time;
  direction_ = sy_ < 0 ? Gesture::Direction::kOut : Gesture::Direction::kIn;
  spdlog::debug(
    "In PinchGestureEvent::Update(libinput_event*): direction_ = {}",
    static_cast<int>(direction_));
}
