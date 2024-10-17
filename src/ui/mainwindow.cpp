#include "mainwindow.h"

#include <gtkmm-4.0/gtkmm/actionbar.h>
#include <gtkmm-4.0/gtkmm/box.h>
#include <gtkmm-4.0/gtkmm/button.h>
#include <gtkmm-4.0/gtkmm/enums.h>
#include <gtkmm-4.0/gtkmm/frame.h>
#include <gtkmm-4.0/gtkmm/grid.h>
#include <gtkmm-4.0/gtkmm/label.h>
#include <gtkmm-4.0/gtkmm/scrolledwindow.h>
#include <gtkmm-4.0/gtkmm/stack.h>

#include <cstdint>
#include <unordered_map>

#include "../core/gesturesfile.h"

MainWindow::MainWindow() {
  GesturesFile::Initialize();
  auto gestures = GesturesFile::GetGestures();
  auto gesture_map = std::unordered_map<int32_t, std::vector<Gesture>>{};
  for (const auto& gesture : gestures) {
    auto finger_count = gesture.GetFingerCount();
    gesture_map[finger_count].push_back(gesture);
  }

  set_title("Slither");
  set_default_size(600, 400);

  auto box = Gtk::Box{};
  box.set_orientation(Gtk::Orientation::VERTICAL);

  auto stack = Gtk::Stack{};

  for (size_t i = 0, j = 1; i < list_boxes_.size(); ++i, ++j) {
    auto& list_box = list_boxes_[i];

    auto scrolled_window = Gtk::ScrolledWindow{};
    scrolled_window.set_expand(true);

    auto frame = Gtk::Frame{"Your Gestures and Actions"};
    frame.set_child(list_box);
    frame.set_margin(12);
    scrolled_window.set_child(frame);

    auto gestures = gesture_map[j];
    for (const auto& gesture : gestures) {
      auto row = Gtk::ListBoxRow{};
      auto label = Gtk::Label{gesture.ToString()};
      row.set_child(label);
      label.set_halign(Gtk::Align::START);
      label.set_hexpand(true);
      list_box.append(row);
    }

    auto finger_count = std::to_string(j);
    auto title = std::string{finger_count + (j == 1 ? " Finger" : " Fingers")};
    stack.add(scrolled_window, finger_count, title);
  }

  stack_switcher_.set_stack(stack);

  box.append(stack_switcher_);
  box.append(stack);

  auto action_bar = Gtk::ActionBar{};
  box.append(action_bar);

  // Dialog
  // Save: document-save
  // Cancel: window-close
  add_button_.set_icon_name("list-add");
  add_button_.set_tooltip_text("Add gesture");
  add_button_.set_margin_end(6);

  delete_button_.set_icon_name("list-remove");
  delete_button_.set_tooltip_text("Delete gesture");

  edit_button_.set_icon_name("document-properties");
  edit_button_.set_tooltip_text("Edit gesture");

  // The order in which the buttons are added matters.
  action_bar.pack_end(add_button_);  // This should always be added first.
  action_bar.pack_end(delete_button_);
  action_bar.pack_end(edit_button_);

  set_child(box);
}
