#include "swipegestureevent.h"

#include <spdlog/spdlog.h>

#include "gesturesfile.h"
#include "inputinjector.h"

SwipeGestureEvent::SwipeGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void SwipeGestureEvent::Begin(libinput_event* event) {
  spdlog::info("Entering SwipeGestureEvent::Begin");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("Value of time: {}", time);

  time_ = time;

  spdlog::info("Exiting SwipeGestureEvent::Begin");
}

void SwipeGestureEvent::End(libinput_event* event) {
  spdlog::info("Entering SwipeGestureEvent::End");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("Value of time: {}", time);

  auto time_diff = time - time_;
  if (direction_ == Gesture::Direction::kNone || time_diff > kTimeLimit) {
    spdlog::info("direction_ or time difference is invalid");
    spdlog::debug("Value of direction_: {}", static_cast<int>(direction_));
    spdlog::debug("Value of time_diff: {}", time_diff);
    spdlog::info("Exiting SwipeGestureEvent::End");
    return;
  }

  if (auto key_codes =
        GesturesFile::FindGestureKeyCodes(direction_, finger_count_);
      !key_codes.empty()) {
    InputInjector::Inject(key_codes);
  }

  spdlog::info("Exiting SwipeGestureEvent::End");
}

void SwipeGestureEvent::Update(libinput_event* event) {
  spdlog::info("Entering SwipeGestureEvent::Update");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;
  sy_ += dy;

  spdlog::debug("Value of sx_: {}", sx_);
  spdlog::debug("Value of sy_: {}", sy_);

  if (std::abs(sx_) >= kThreshold) {
    // Handles horizontal swipes.
    time_ = time;
    direction_ =
      sx_ < 0 ? Gesture::Direction::kLeft : Gesture::Direction::kRight;

    spdlog::info("Horizontal threshold met");
    spdlog::debug("Value of direction_: {}", static_cast<int>(direction_));
  } else if (std::abs(sy_) >= kThreshold) {
    // Handles vertical swipes.
    time_ = time;
    direction_ = sy_ < 0 ? Gesture::Direction::kDown : Gesture::Direction::kUp;

    spdlog::info("Vertical threshold met");
    spdlog::debug("Value of direction_: {}", static_cast<int>(direction_));
  }

  spdlog::info("Exiting SwipeGestureEvent::Update");
}
