#include "gestureeventfactory.h"

#include "holdgestureevent.h"
#include "pinchgestureevent.h"
#include "swipegestureevent.h"

std::unique_ptr<GestureEvent> GestureEventFactory::CreateGestureEvent(
  libinput_event* event, libinput_event_type event_type) {
  switch (event_type) {
    case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
      return std::make_unique<SwipeGestureEvent>(event);
    case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
      return std::make_unique<PinchGestureEvent>(event);
    case LIBINPUT_EVENT_GESTURE_HOLD_BEGIN:
      return std::make_unique<HoldGestureEvent>(event);
    default:
      return nullptr;
  }
}
