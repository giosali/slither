#ifndef GESTURESTRING_H
#define GESTURESTRING_H

#include <wx/wx.h>

#include "../core/gesture.h"

class GestureString final : public wxString {
 public:
  GestureString() = default;
  explicit GestureString(const Gesture& gesture);

  Gesture GetGesture() const;

 private:
  Gesture gesture_;
};

#endif  // GESTURESTRING_H
