#ifndef GESTURECONVERTER_H
#define GESTURECONVERTER_H

#include <cstddef>
#include <vector>

#include "gesture.h"
#include "gesturesfile.h"

class GestureConverter {
 public:
  GestureConverter();

  void ConvertGesture(Gesture::Direction direction, size_t finger_count);

 private:
  GesturesFile file_;
};

#endif  // GESTURECONVERTER_H
