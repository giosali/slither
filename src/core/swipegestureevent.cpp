#include "swipegestureevent.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstdlib>

#include "gesturesfile.h"
#include "inputinjector.h"
#include "settingsfile.h"

SwipeGestureEvent::SwipeGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void SwipeGestureEvent::Begin(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::Begin(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("time = {}", time);

  time_ = time;
}

void SwipeGestureEvent::End(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::End(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto time = libinput_event_gesture_get_time(gesture_event);
  spdlog::debug("time = {}", time);

  auto time_diff = time - time_;
  if (type_ == Gesture::Type::kNone || time_diff > kTimeLimit) {
    spdlog::info("type_ or time_diff is invalid");
    spdlog::debug("type_ = {}, time_diff = {}", static_cast<int>(type_),
                  time_diff);
    return;
  }

  if (auto key_codes = GesturesFile::FindGestureKeyCodes(type_, finger_count_);
      !key_codes.empty()) {
    InputInjector::Inject(key_codes);
  }
}

void SwipeGestureEvent::Update(libinput_event* event) {
  spdlog::info("In SwipeGestureEvent::Update(libinput_event*)");

  auto gesture_event = libinput_event_get_gesture_event(event);
  auto dx = libinput_event_gesture_get_dx_unaccelerated(gesture_event);
  auto dy = libinput_event_gesture_get_dy_unaccelerated(gesture_event);
  auto time = libinput_event_gesture_get_time(gesture_event);

  sx_ += dx;
  sy_ += dy;
  auto x_mag = std::abs(sx_);
  auto y_mag = std::abs(sy_);
  auto max = std::max(x_mag, y_mag);
  spdlog::debug("sx_ = {}, sy_ = {}, max = {}", sx_, sy_, max);

  auto sensitivity =
    static_cast<int>(SettingsFile::GetSettings().GetSwipeSensitivity());
  if (max < sensitivity) {
    return;
  }

  time_ = time;
  if (max == x_mag) {
    type_ = sx_ < 0 ? Gesture::Type::kLeft : Gesture::Type::kRight;
    spdlog::debug("type_ = {}", static_cast<int>(type_));
  } else {
    type_ = sy_ < 0 ? Gesture::Type::kUp : Gesture::Type::kDown;
    spdlog::debug("type_ = {}", static_cast<int>(type_));
  }
}
