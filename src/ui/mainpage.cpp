#include "mainpage.h"

#include <wx/sizer.h>
#include <wx/wx.h>

#include "gesturestring.h"

MainPage::MainPage(wxWindow* parent, int32_t finger_count)
    : wxPanel{parent},
      list_box_{new wxListBox{this, wxID_ANY}},
      finger_count_(finger_count) {
  // Ensures wxListBox takes full width of window.
  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(list_box_, 1, wxEXPAND);
  SetSizer(sizer);
}

void MainPage::Append(const GestureString& item) const {
  list_box_->Append(item);
}

void MainPage::Clear() const { list_box_->Clear(); }

wxString MainPage::GetCurrentRow() const {
  return list_box_->GetStringSelection();
}

int32_t MainPage::GetFingerCount() const { return finger_count_; }

void MainPage::DeleteCurrentRow() const {
  if (auto selection = list_box_->GetSelection(); selection != wxNOT_FOUND) {
    list_box_->Delete(selection);
  }
}
