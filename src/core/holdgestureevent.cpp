#include "holdgestureevent.h"

#include <chrono>

#include "gesturesfile.h"
#include "inputinjector.h"
#include "settingsfile.h"

HoldGestureEvent::HoldGestureEvent(libinput_event* event)
    : GestureEvent{event} {}

void HoldGestureEvent::Begin(libinput_event* event) {
  auto gesture_event = libinput_event_get_gesture_event(event);
  auto finger_count = libinput_event_gesture_get_finger_count(gesture_event);

  auto lock = std::lock_guard<std::mutex>{mtx_};

  finger_count_ = finger_count;
  thread_ = std::jthread{&HoldGestureEvent::StartTimer, this};
  thread_.detach();
}

void HoldGestureEvent::End(libinput_event* event) { thread_.request_stop(); }

void HoldGestureEvent::Update(libinput_event* event) {}

void HoldGestureEvent::StartTimer(std::stop_token stoken) {
  auto time = SettingsFile::GetSettings().GetHoldTime();
  std::this_thread::sleep_for(std::chrono::milliseconds{time});

  if (!stoken.stop_requested()) {
    auto lock = std::lock_guard<std::mutex>{mtx_};

    if (auto key_codes = GesturesFile::FindGestureKeyCodes(
          Gesture::Direction::kNone, finger_count_);
        !key_codes.empty()) {
      InputInjector::Inject(key_codes);
    }
  }
}
