#include "gesturepage.h"

#include <wx/wx.h>

GesturePage::GesturePage(wxNotebook* parent, int32_t finger_count)
    : wxPanel{parent},
      list_box_{new wxListBox{this, wxID_ANY}},
      finger_count_(finger_count) {
  // Ensures wxListBox takes full width of window.
  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(list_box_, 1, wxEXPAND);
  SetSizer(sizer);
}

void GesturePage::Append(const Gesture& gesture) {
  list_box_->Append(gesture.ToString());
  gestures_.push_back(gesture);
}

void GesturePage::Clear() {
  list_box_->Clear();
  gestures_.clear();
}

std::optional<Gesture> GesturePage::GetCurrentGesture() const {
  auto selection = list_box_->GetSelection();
  return selection != wxNOT_FOUND ? std::make_optional(gestures_[selection])
                                  : std::nullopt;
}

int32_t GesturePage::GetFingerCount() const { return finger_count_; }

void GesturePage::DeleteCurrentRow() const {
  if (auto selection = list_box_->GetSelection(); selection != wxNOT_FOUND) {
    list_box_->Delete(selection);
  }
}
