#include "pinchgestureevent.h"

#include "gesturesfile.h"
#include "inputinjector.h"

PinchGestureEvent::PinchGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void PinchGestureEvent::Begin(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  time_ = time;
}

void PinchGestureEvent::End(libinput_event* event) {
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

void PinchGestureEvent::Update(libinput_event* event) {
  // The only thing that seems to matter when parsing the coordinates of a
  // pinch gesture is the x-coordinate. The y-coordinate will only change if
  // the user vertically moves their hand up and down while performing a pinch
  // gesture. That seems unlikely to ever happen while pinching; it's an
  // unnatural movement.
  // Even if the user has their fingers positioned perpendicular to the x-axis,
  // the gesture will be poorly detected. The y-coordinate seems useless.

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;

  if (sx_ >= kPinchInThreshold) {
    time_ = time;
    direction_ = Gesture::Direction::kIn;
  } else if (sx_ <= kPinchOutThreshold) {
    time_ = time;
    direction_ = Gesture::Direction::kOut;
  }
}
