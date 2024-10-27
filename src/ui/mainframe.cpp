#include "mainframe.h"

#include <cstdint>
#include <format>

#include "../core/gesture.h"
#include "../core/gesturesfile.h"
#include "constants.h"
#include "gestureformdialog.h"
#include "mainstatusbar.h"

MainFrame::MainFrame()
    : wxFrame{nullptr, wxID_ANY, "Slither", wxDefaultPosition,
              wxSize{600, 500}},
      notebook_{new wxNotebook{this, wxID_ANY}} {
  // Creates the notebook pages.
  for (int32_t i = 1; i < 6; ++i) {
    auto page = new MainPage{notebook_, i};
    notebook_->AddPage(page, std::format("{} Finger{}", i, i == 1 ? "" : "s"));
  }

  UpdatePages();

  SetStatusBar(new MainStatusBar{this});

  // Listens for custom command events emitted from the main status bar.
  Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnClick, this);
}

MainPage* MainFrame::GetCurrentPage() const {
  auto page = notebook_->GetCurrentPage();
  if (page == nullptr) {
    return nullptr;
  }

  return static_cast<MainPage*>(page);
}

wxString MainFrame::GetCurrentRow() const {
  auto main_page = GetCurrentPage();
  if (main_page == nullptr) {
    return {};
  }

  return main_page->GetCurrentRow();
}

void MainFrame::OnClick(wxCommandEvent& event) {
  auto data = event.GetString();
  if (data == Constants::kAddButtonLabel) {
    auto main_page = GetCurrentPage();
    if (main_page == nullptr) {
      return;
    }

    auto form_dialog = new GestureFormDialog(this, "Create a Gesture",
                                             main_page->GetFingerCount());
    form_dialog->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnDialogClose, this);
    form_dialog->ShowModal();
  } else if (data == Constants::kDeleteButtonLabel) {
    auto main_page = GetCurrentPage();
    if (main_page == nullptr) {
      return;
    }

    // Removes the current row visually.
    main_page->DeleteCurrentRow();

    auto row = GetCurrentRow();
    if (row.IsEmpty()) {
      return;
    }

    // Removes the current row via IO.
    auto gesture = static_cast<GestureString&>(row).GetGesture();
    GesturesFile::DeleteGesture(gesture);
    GesturesFile::Save();
  } else if (data == Constants::kEditButtonLabel) {
    auto main_page = GetCurrentPage();
    if (main_page == nullptr) {
      return;
    }

    auto row = GetCurrentRow();
    if (row.IsEmpty()) {
      return;
    }

    auto gesture = static_cast<GestureString&>(row).GetGesture();
    auto form_dialog = new GestureFormDialog(
      this, "Edit a Gesture", main_page->GetFingerCount(), gesture);
    form_dialog->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnDialogClose, this);
    form_dialog->ShowModal();
  }
}

void MainFrame::OnDialogClose(wxCloseEvent& event) {
  UpdatePages();
  event.Skip();
}

void MainFrame::UpdatePages() {
  // Empties the list boxes in all pages.
  for (size_t i = 0; i < notebook_->GetPageCount(); ++i) {
    auto page = notebook_->GetPage(i);
    auto main_page = static_cast<MainPage*>(page);
    main_page->Clear();
  }

  // Repopulates those list boxes.
  for (const auto& gesture : GesturesFile::GetGestures()) {
    auto finger_count = gesture.GetFingerCount();
    auto page = notebook_->GetPage(finger_count);
    auto main_page = static_cast<MainPage*>(page);
    main_page->Append(GestureString{gesture});
  }
}
