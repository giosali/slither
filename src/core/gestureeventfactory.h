#ifndef GESTUREEVENTFACTORY_H
#define GESTUREEVENTFACTORY_H

#include <libinput.h>

#include <memory>

#include "gestureevent.h"

class GestureEventFactory {
 public:
  GestureEventFactory() = delete;

  static std::unique_ptr<GestureEvent> CreateGestureEvent(
    libinput_event* event, libinput_event_type event_type);
};

#endif  // GESTUREEVENTFACTORY_H
