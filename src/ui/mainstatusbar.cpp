#include "mainstatusbar.h"

#include <array>

#include "constants.h"

MainStatusBar::MainStatusBar(wxWindow* parent) : wxStatusBar{parent, wxID_ANY} {
  add_button_ = new wxButton{this, wxID_ANY, Constants::kAddButtonLabel};
  delete_button_ = new wxButton{this, wxID_ANY, Constants::kDeleteButtonLabel};
  edit_button_ = new wxButton{this, wxID_ANY, Constants::kEditButtonLabel};

  // The first -1 width is a variable width. This will push the buttons to the
  // right.
  auto widths = std::array<int, 4 + 1>{-1, add_button_->GetSize().GetWidth(),
                                       delete_button_->GetSize().GetWidth(),
                                       edit_button_->GetSize().GetWidth()};
  SetFieldsCount(widths.size());
  SetStatusWidths(widths.size(), widths.data());

  Bind(wxEVT_SIZE, &MainStatusBar::OnSize, this);
  Bind(wxEVT_BUTTON, &MainStatusBar::OnButtonClick, this);

  PositionButtons();
}

void MainStatusBar::OnButtonClick(wxCommandEvent& event) {
  auto custom_event = wxCommandEvent{wxEVT_COMMAND_BUTTON_CLICKED};

  auto button = static_cast<wxButton*>(event.GetEventObject());
  if (button == add_button_) {
    custom_event.SetString(Constants::kAddButtonLabel);
  } else if (button == delete_button_) {
    custom_event.SetString(Constants::kDeleteButtonLabel);
  } else if (button == edit_button_) {
    custom_event.SetString(Constants::kEditButtonLabel);
  }

  wxPostEvent(GetParent(), custom_event);
}

void MainStatusBar::OnSize(wxSizeEvent& event) {
  event.Skip();
  PositionButtons();
}

void MainStatusBar::PositionButtons() {
  // Determines the order in which the buttons appear from left to right.
  const auto buttons =
    std::array<wxButton*, 3>{delete_button_, edit_button_, add_button_};
  auto rect = wxRect{};

  // j is set to 1 to ignore the non-button element in the status bar.
  for (size_t i = 0, j = 1; i < buttons.size(); ++i, ++j) {
    GetFieldRect(j, rect);

    auto button = buttons[i];
    button->SetSize(rect.GetX(), rect.GetY(), rect.GetWidth(),
                    rect.GetHeight());
  }
}
