#ifndef SWIPEGESTUREEVENT_H
#define SWIPEGESTUREEVENT_H

#include <libinput.h>

#include "gesture.h"
#include "gestureevent.h"

class SwipeGestureEvent : public GestureEvent {
 public:
  explicit SwipeGestureEvent(libinput_event* event);

  void Begin(libinput_event* event) override;
  void End(libinput_event* event) override;
  void Update(libinput_event* event) override;

 private:
  static constexpr double kThreshold = 125;
  static constexpr uint32_t kTimeLimit = 200;

  Gesture::Direction direction_{};
  double sx_{};
  double sy_{};
  uint32_t time_{};
};

#endif  // SWIPEGESTUREEVENT_H
