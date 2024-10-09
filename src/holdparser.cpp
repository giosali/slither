#include "holdparser.h"

#include <chrono>

#include "gesture.h"

HoldParser::HoldParser() : converter_{}, finger_count_{}, mtx_{}, thread_{} {}

void HoldParser::Begin(size_t finger_count) {
  auto lock = std::lock_guard<std::mutex>{mtx_};

  finger_count_ = finger_count;
  thread_ = std::jthread{&HoldParser::Do, this};
  thread_.detach();
}

void HoldParser::End() { thread_.request_stop(); }

void HoldParser::Do(std::stop_token stoken) {
  std::this_thread::sleep_for(std::chrono::milliseconds{1500});

  if (!stoken.stop_requested()) {
    auto lock = std::lock_guard<std::mutex>{mtx_};

    converter_.ConvertGesture(Gesture::Direction::kNone, finger_count_);
  }
}
