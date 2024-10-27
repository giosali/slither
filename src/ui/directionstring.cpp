#include "directionstring.h"

DirectionString::DirectionString(Gesture::Direction direction)
    : wxString{Gesture::StringifyDirection(direction)}, direction_{direction} {}

Gesture::Direction DirectionString::GetDirection() const { return direction_; }
