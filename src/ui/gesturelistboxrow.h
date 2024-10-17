#ifndef GESTURELISTBOXROW_H
#define GESTURELISTBOXROW_H

#include <gtkmm-4.0/gtkmm/listboxrow.h>

#include "../core/gesture.h"

class GestureListBoxRow : public Gtk::ListBoxRow {
 public:
  GestureListBoxRow(const Gesture& gesture);

  Gesture GetGesture() const;

  virtual ~GestureListBoxRow() = default;

 private:
  Gesture gesture_{};
};

#endif  // GESTURELISTBOXROW_H
