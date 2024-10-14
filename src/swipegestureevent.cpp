#include "swipegestureevent.h"

#include <spdlog/spdlog.h>

#include "gesturesfile.h"
#include "inputinjector.h"

SwipeGestureEvent::SwipeGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void SwipeGestureEvent::Begin(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("In SwipeGestureEvent::Begin(libinput_event*): time = {}",
                time);

  time_ = time;
}

void SwipeGestureEvent::End(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("In SwipeGestureEvent::End(libinput_event*): time = {}", time);

  auto time_diff = time - time_;
  if (direction_ == Gesture::Direction::kNone || time_diff > kTimeLimit) {
    spdlog::info(
      "In SwipeGestureEvent::End(libinput_event*): direction_ or time_diff is "
      "invalid");
    spdlog::debug(
      "In SwipeGestureEvent::End(libinput_event*): direction_ = {}, time_diff "
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

void SwipeGestureEvent::Update(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;
  sy_ += dy;

  spdlog::debug(
    "In SwipeGestureEvent::Update(libinput_event* event): sx_ = {}, sy_ = {}",
    sx_, sy_);

  if (std::abs(sx_) >= kThreshold) {
    // Handles horizontal swipes.
    time_ = time;
    direction_ =
      sx_ < 0 ? Gesture::Direction::kLeft : Gesture::Direction::kRight;

    spdlog::info("Horizontal threshold met");
    spdlog::debug(
      "In SwipeGestureEvent::Update(libinput_event* event): direction_ = {}",
      static_cast<int>(direction_));
  } else if (std::abs(sy_) >= kThreshold) {
    // Handles vertical swipes.
    time_ = time;
    direction_ = sy_ < 0 ? Gesture::Direction::kUp : Gesture::Direction::kDown;

    spdlog::info("Vertical threshold met");
    spdlog::debug(
      "In SwipeGestureEvent::Update(libinput_event* event): direction_ = {}",
      static_cast<int>(direction_));
  }
}
