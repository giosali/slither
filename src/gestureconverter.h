#ifndef GESTURECONVERTER_H
#define GESTURECONVERTER_H

#include <cstddef>
#include <vector>

#include "gesture.h"
#include "gesturesfile.h"
#include "inputinjector.h"

class GestureConverter {
 public:
  GestureConverter();

  void ConvertGesture(Gesture::Direction direction, size_t finger_count);
  void UpdateInjector(const std::vector<Gesture>& gestures);

 private:
  GesturesFile file_;
  InputInjector injector_;
};

#endif  // GESTURECONVERTER_H
