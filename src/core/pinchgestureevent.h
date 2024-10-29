#ifndef PINCHGESTUREEVENT_H
#define PINCHGESTUREEVENT_H

#include <libinput.h>

#include <cstdint>

#include "gesture.h"
#include "gestureevent.h"

class PinchGestureEvent : public GestureEvent {
 public:
  explicit PinchGestureEvent(libinput_event* event);

  void Begin(libinput_event* event) override;
  void End(libinput_event* event) override;
  void Update(libinput_event* event) override;

 private:
  static constexpr double kPinchThreshold = 20;
  static constexpr uint32_t kTimeLimit = 200;

  Gesture::Direction direction_{};
  double sx_{};
  double sy_{};
  uint32_t time_{};
};

#endif  // PINCHGESTUREEVENT_H
