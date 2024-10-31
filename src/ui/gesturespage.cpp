#include "gesturespage.h"

#include <wx/listbook.h>

#include "../core/gesturesfile.h"
#include "gestureformdialog.h"

GesturesPage::GesturesPage(wxListbook* parent)
    : wxPanel{parent}, notebook_{new wxNotebook{this, wxID_ANY}} {
  // ========
  // CONTROLS
  // ========
  // Section: PAGES
  for (int32_t i = 1; i < 6; ++i) {
    auto page = new GesturePage{notebook_, i};
    notebook_->AddPage(page, std::format("{} Finger{}", i, i == 1 ? "" : "s"));
  }

  UpdatePages();

  // Section: BUTTONS
  auto delete_button = new wxButton{this, wxID_ANY, "Delete"};
  delete_button->Bind(wxEVT_BUTTON, &GesturesPage::OnDeleteButtonClick, this);

  auto edit_button = new wxButton{this, wxID_ANY, "Edit"};
  edit_button->Bind(wxEVT_BUTTON, &GesturesPage::OnEditButtonClick, this);

  auto add_button = new wxButton{this, wxID_ANY, "Add"};
  add_button->Bind(wxEVT_BUTTON, &GesturesPage::OnAddButtonClick, this);

  // ======
  // LAYOUT
  // ======
  // Handles layout for section: PAGES.
  auto sizer = new wxBoxSizer{wxVERTICAL};
  sizer->Add(notebook_, 1, wxEXPAND | wxALL);
  SetSizerAndFit(sizer);

  // Handles layout for section: BUTTONS.
  auto buttons_sizer = new wxBoxSizer{wxHORIZONTAL};
  buttons_sizer->Add(delete_button);
  buttons_sizer->AddSpacer(5);
  buttons_sizer->Add(edit_button);
  buttons_sizer->AddSpacer(5);
  buttons_sizer->Add(add_button);
  sizer->Add(buttons_sizer, 0, wxRIGHT | wxTOP | wxBOTTOM | wxALIGN_RIGHT, 5);
}

GesturePage* GesturesPage::GetCurrentPage() const {
  auto page = notebook_->GetCurrentPage();
  return page != nullptr ? static_cast<GesturePage*>(page) : nullptr;
}

void GesturesPage::OnAddButtonClick(wxCommandEvent& event) {
  if (auto page = GetCurrentPage(); page != nullptr) {
    auto form_dialog =
      new GestureFormDialog(this, "Create a Gesture", page->GetFingerCount());
    form_dialog->Bind(wxEVT_CLOSE_WINDOW, &GesturesPage::OnDialogClose, this);
    form_dialog->ShowModal();
  }
}

void GesturesPage::OnDeleteButtonClick(wxCommandEvent& event) {
  auto page = GetCurrentPage();
  if (page == nullptr) {
    return;
  }

  if (auto gesture = page->GetCurrentGesture(); gesture.has_value()) {
    // Removes the current row visually.
    page->DeleteCurrentRow();

    // Removes the current row via IO.
    GesturesFile::DeleteGesture(gesture.value());
    GesturesFile::Save();
  }
}

void GesturesPage::OnDialogClose(wxCloseEvent& event) {
  UpdatePages();
  event.Skip();
}

void GesturesPage::OnEditButtonClick(wxCommandEvent& event) {
  auto page = GetCurrentPage();
  if (page == nullptr) {
    return;
  }

  if (auto gesture = page->GetCurrentGesture(); gesture.has_value()) {
    auto dialog =
      new GestureFormDialog{this, "Edit a Gesture", gesture.value()};
    dialog->Bind(wxEVT_CLOSE_WINDOW, &GesturesPage::OnDialogClose, this);
    dialog->ShowModal();
  }
}

void GesturesPage::UpdatePages() {
  // Empties the list boxes in all pages.
  for (size_t i = 0, l = notebook_->GetPageCount(); i < l; ++i) {
    auto page = static_cast<GesturePage*>(notebook_->GetPage(i));
    page->Clear();
  }

  // Repopulates those list boxes.
  for (const auto& gesture : GesturesFile::GetGestures()) {
    auto finger_count = gesture.GetFingerCount();

    // Subtracts 1 from finger count since the pages used zero-based indexing.
    auto page = static_cast<GesturePage*>(notebook_->GetPage(finger_count - 1));
    page->Append(gesture);
  }
}
