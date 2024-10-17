#include "gesturelistboxrow.h"

#include "gtkmm/listboxrow.h"

GestureListBoxRow::GestureListBoxRow(const Gesture& gesture)
    : Gtk::ListBoxRow{}, gesture_{gesture} {}

Gesture GestureListBoxRow::GetGesture() const { return gesture_; }
