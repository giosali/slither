#ifndef HOLDPARSER_H
#define HOLDPARSER_H

#include <cstdint>
#include <thread>

#include "gestureconverter.h"

class HoldParser {
 public:
  HoldParser();

  void Begin(size_t finger_count);
  void End();

 private:
  void Do(std::stop_token stoken);

  GestureConverter converter_;
  size_t finger_count_;
  std::mutex mtx_;
  std::jthread thread_;
};

#endif  // HOLDPARSER_H
