#include "gestureconverter.h"

#include <unordered_set>

GestureConverter::GestureConverter() : file_{}, injector_{} {
  auto callback = [this](const std::vector<Gesture>& gestures) {
    UpdateInjector(gestures);
  };
  file_.SetCallback(callback);

  UpdateInjector(file_.GetGestures());
}

void GestureConverter::ConvertGesture(Gesture::Direction direction,
                                      size_t finger_count) {
  const auto gestures = file_.GetGestures();
  for (size_t i = 0; i < gestures.size(); ++i) {
    auto gesture = gestures[i];
    if (gesture.GetDirection() == direction &&
        gesture.GetFingerCount() == finger_count) {
      injector_.Inject(gesture.GetKeyCodes());
      break;
    }
  }
}

void GestureConverter::UpdateInjector(const std::vector<Gesture>& gestures) {
  auto key_codes = std::unordered_set<int>{};

  for (const auto& gesture : gestures) {
    auto gesture_key_codes = gesture.GetKeyCodes();
    for (auto key_code : gesture_key_codes) {
      key_codes.insert(key_code);
    }
  }

  injector_ = InputInjector{key_codes};
}
