#include "gesturestring.h"

GestureString::GestureString(const Gesture& gesture)
    : wxString{gesture.ToString()}, gesture_{gesture} {}

Gesture GestureString::GetGesture() const { return gesture_; }
