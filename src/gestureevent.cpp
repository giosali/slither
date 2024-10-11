#include "gestureevent.h"

GestureEvent::GestureEvent(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  finger_count_ = libinput_event_gesture_get_finger_count(gesture_event);
}