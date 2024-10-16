#ifndef HOLDGESTUREEVENT_H
#define HOLDGESTUREEVENT_H

#include <libinput.h>

#include <mutex>
#include <stop_token>
#include <thread>

#include "gestureevent.h"

class HoldGestureEvent : public GestureEvent {
 public:
  explicit HoldGestureEvent(libinput_event* event);

  void Begin(libinput_event* event) override;
  void End(libinput_event* event) override;
  void Update(libinput_event* event) override;

 private:
  void StartTimer(std::stop_token stoken);

  std::mutex mtx_{};
  std::jthread thread_{};
};

#endif  // HOLDGESTUREEVENT_H
