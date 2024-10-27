#ifndef DIRECTIONSTRING_H
#define DIRECTIONSTRING_H

#include <wx/wx.h>

#include "../core/gesture.h"

class DirectionString final : public wxString {
 public:
  explicit DirectionString(Gesture::Direction direction);

  Gesture::Direction GetDirection() const;

 private:
  Gesture::Direction direction_{};
};

#endif  // DIRECTIONSTRING_H
