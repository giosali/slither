#include "swipegestureevent.h"

#include "gesturesfile.h"
#include "inputinjector.h"

SwipeGestureEvent::SwipeGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void SwipeGestureEvent::Begin(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  time_ = time;
}

void SwipeGestureEvent::End(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  if (direction_ == Gesture::Direction::kNone || time - time_ > kTimeLimit) {
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

  if (std::abs(sx_) >= kThreshold) {
    // Handles horizontal swipes.
    time_ = time;
    direction_ =
      sx_ < 0 ? Gesture::Direction::kLeft : Gesture::Direction::kRight;
  } else if (std::abs(sy_) >= kThreshold) {
    // Handles vertical swipes.
    time_ = time;
    direction_ = sy_ < 0 ? Gesture::Direction::kDown : Gesture::Direction::kUp;
  }
}
