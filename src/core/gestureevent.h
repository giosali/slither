#ifndef GESTUREEVENT_H
#define GESTUREEVENT_H

#include <libinput.h>

#include <cstdint>

class GestureEvent {
 public:
  explicit GestureEvent(libinput_event* event);

  virtual ~GestureEvent() = default;

  virtual void Begin(libinput_event* event) = 0;
  virtual void End(libinput_event* event) = 0;
  virtual void Update(libinput_event* event) = 0;

 protected:
  int32_t finger_count_{};
};

#endif  // GESTUREEVENT_H
