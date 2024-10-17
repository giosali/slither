#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm-4.0/gtkmm/button.h>
#include <gtkmm-4.0/gtkmm/listbox.h>
#include <gtkmm-4.0/gtkmm/stackswitcher.h>
#include <gtkmm-4.0/gtkmm/window.h>

#include <array>

#include "gtkmm/stackswitcher.h"

class MainWindow : public Gtk::Window {
 public:
  MainWindow();

 private:
  Gtk::Button add_button_{};
  std::array<Gtk::ListBox, 5> list_boxes_{};
  Gtk::StackSwitcher stack_switcher_{};
};

#endif  // MAINWINDOW_H
