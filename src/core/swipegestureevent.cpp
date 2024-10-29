#include "swipegestureevent.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstdlib>

#include "gesturesfile.h"
#include "inputinjector.h"

SwipeGestureEvent::SwipeGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void SwipeGestureEvent::Begin(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::Begin(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("time = {}", time);

  time_ = time;
}

void SwipeGestureEvent::End(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::End(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("time = {}", time);

  auto time_diff = time - time_;
  if (direction_ == Gesture::Direction::kNone || time_diff > kTimeLimit) {
    spdlog::info("direction_ or time_diff is invalid");
    spdlog::debug("direction_ = {}, time_diff = {}",
                  static_cast<int>(direction_), time_diff);
    return;
  }

  if (auto key_codes =
        GesturesFile::FindGestureKeyCodes(direction_, finger_count_);
      !key_codes.empty()) {
    InputInjector::Inject(key_codes);
  }
}

void SwipeGestureEvent::Update(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::Update(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;
  sy_ += dy;
  auto x_mag = std::abs(sx_);
  auto y_mag = std::abs(sy_);
  auto max = std::max(x_mag, y_mag);
  spdlog::debug("sx_ = {}, sy_ = {}, max = {}", sx_, sy_, max);

  if (max < kThreshold) {
    return;
  }

  time_ = time;
  if (max == x_mag) {
    direction_ =
      sx_ < 0 ? Gesture::Direction::kLeft : Gesture::Direction::kRight;
    spdlog::debug("direction_ = {}", static_cast<int>(direction_));
  } else {
    direction_ = sy_ < 0 ? Gesture::Direction::kUp : Gesture::Direction::kDown;
    spdlog::debug("direction_ = {}", static_cast<int>(direction_));
  }
}
