#include "gestureconverter.h"

#include <spdlog/spdlog.h>

#include <type_traits>

#include "inputinjector.h"

GestureConverter::GestureConverter() : file_{} { file_.Watch(); }

void GestureConverter::ConvertGesture(Gesture::Direction direction,
                                      size_t finger_count) {
  spdlog::info("Entering GestureConverter::ConvertGesture");
  spdlog::debug("Value of direction: {}", static_cast<int>(direction));
  spdlog::debug("Value of finger_count: {}", finger_count);

  const auto gestures = file_.GetGestures();
  for (size_t i = 0; i < gestures.size(); ++i) {
    auto gesture = gestures[i];
    if (gesture.GetDirection() == direction &&
        gesture.GetFingerCount() == finger_count) {
      spdlog::debug("Direction and finger count matched function parameters");

      InputInjector::Inject(gesture.GetKeyCodes());
      break;
    }
  }

  spdlog::info("Exiting GestureConverter::ConvertGesture");
}
