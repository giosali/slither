#include "gestureconverter.h"

#include <unordered_set>

#include "inputinjector.h"

GestureConverter::GestureConverter() : file_{} { file_.Watch(); }

void GestureConverter::ConvertGesture(Gesture::Direction direction,
                                      size_t finger_count) {
  const auto gestures = file_.GetGestures();
  for (size_t i = 0; i < gestures.size(); ++i) {
    auto gesture = gestures[i];
    if (gesture.GetDirection() == direction &&
        gesture.GetFingerCount() == finger_count) {
      InputInjector::Inject(gesture.GetKeyCodes());
      break;
    }
  }
}
