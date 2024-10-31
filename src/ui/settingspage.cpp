#include "settingspage.h"

#include <wx/notifmsg.h>
#include <wx/statline.h>

#include <string>
#include <tuple>
#include <vector>

#include "../core/settingsfile.h"
#include "../core/utilities.h"
#include "colors.h"

SettingsPage::SettingsPage(wxListbook* parent)
    : wxPanel{parent}, settings_{SettingsFile::GetSettings()} {
  auto window = new wxScrolledWindow{this, wxID_ANY};

  auto main_sizer = new wxBoxSizer{wxVERTICAL};
  SetSizer(main_sizer);
  main_sizer->Add(window, 1, wxALL | wxEXPAND);

  // This is nothing more than a placeholder sizer.
  auto window_sizer = new wxBoxSizer{wxVERTICAL};
  window->SetSizer(window_sizer);

  // This is only necessary to cleanly apply the border inside the parent sizer.
  auto window_child_sizer = new wxBoxSizer{wxVERTICAL};
  window_sizer->Add(window_child_sizer, 1, wxALL | wxEXPAND, 10);

  SetUpSwipeControls(window, window_child_sizer);
  SetUpPinchControls(window, window_child_sizer);
  SetUpHoldControls(window, window_child_sizer);
  SetUpButtons(this, main_sizer);

  // Allows the wxScrolledWindow to actually function. This must occur at the
  // end.
  auto height = window_child_sizer->GetMinSize().GetHeight() / 10;
  window->SetScrollbars(0, 10, 0, height);
}

void SettingsPage::OnPinchRadioButtonClick(wxCommandEvent& event) {
  auto button = static_cast<wxRadioButton*>(event.GetEventObject());
  auto name = button->GetName().ToStdString();
  auto sensitivity = static_cast<Settings::PinchSensitivity>(std::stoi(name));
  settings_.SetPinchSensitivity(sensitivity);
}

void SettingsPage::OnSaveButtonClick(wxCommandEvent& event) {
  SettingsFile::SetSettings(settings_);

  auto message = wxNotificationMessage{
    "Settings Saved", "Your settings have been successfully saved.", nullptr,
    wxICON_INFORMATION};
  message.Show(2);
}

void SettingsPage::OnSpinControlUpdate(wxSpinEvent& event) {
  auto spin_ctrl = static_cast<wxSpinCtrl*>(event.GetEventObject());
  settings_.SetHoldTime(spin_ctrl->GetValue());
}

void SettingsPage::OnSwipeRadioButtonClick(wxCommandEvent& event) {
  auto button = static_cast<wxRadioButton*>(event.GetEventObject());
  auto name = button->GetName().ToStdString();
  auto sensitivity = static_cast<Settings::SwipeSensitivity>(std::stoi(name));
  settings_.SetSwipeSensitivity(sensitivity);
}

void SettingsPage::SetUpButtons(wxWindow* parent, wxBoxSizer* sizer) {
  auto internal_sizer = new wxBoxSizer{wxHORIZONTAL};

  auto save_button = new wxButton{parent, wxID_ANY, "Save Changes"};
  save_button->Bind(wxEVT_BUTTON, &SettingsPage::OnSaveButtonClick, this);
  internal_sizer->Add(save_button);

  sizer->Add(internal_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxTOP | wxBOTTOM, 5);
}

void SettingsPage::SetUpHoldControls(wxWindow* parent, wxBoxSizer* sizer) {
  auto title = new wxStaticText{parent, wxID_ANY, "Hold Time"};
  sizer->Add(title);

  auto infos = std::vector<std::tuple<std::string, bool>>{
    {"The minimum hold time threshold (in milliseconds) for action initiation.",
     true},
    {"Press Enter after typing in a number.", false}};
  for (const auto& info : infos) {
    auto description = new wxStaticText{parent, wxID_ANY, std::get<0>(info)};
    if (auto should_wrap = std::get<1>(info)) {
      description->Wrap(description->GetSize().GetWidth() * 0.85);
    }

    description->SetForegroundColour(Colors::GetSecondaryTextColor());
    sizer->Add(description);
  }

  sizer->AddSpacer(8);

  auto spin = new wxSpinCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition,
                             wxSize(200, -1), wxSP_ARROW_KEYS, 0, 10000,
                             settings_.GetHoldTime());
  spin->SetIncrement(50);
  spin->Bind(wxEVT_SPINCTRL, &SettingsPage::OnSpinControlUpdate, this);
  sizer->Add(spin);
}

void SettingsPage::SetUpPinchControls(wxWindow* parent, wxBoxSizer* sizer) {
  auto title = new wxStaticText{parent, wxID_ANY, "Pinch Sensitivity"};
  sizer->Add(title);

  auto description = new wxStaticText{
    parent, wxID_ANY, "A lower sensitivity requires larger pinches."};
  description->SetForegroundColour(Colors::GetSecondaryTextColor());
  sizer->Add(description);
  sizer->AddSpacer(8);

  auto index = size_t{0};
  auto current_sensitivity = settings_.GetPinchSensitivity();
  for (auto sensitivity : Utilities::EnumRange(
         Settings::PinchSensitivity::kHigh, Settings::PinchSensitivity::kLow)) {
    auto label = Utilities::ConvertPinchSensitivityToString(sensitivity);
    if (label.empty()) {
      continue;
    }

    auto style = index++ == 0 ? wxRB_GROUP : 0;
    auto name = std::to_string(static_cast<int>(sensitivity));

    auto button = new wxRadioButton{
      parent, wxID_ANY,           label, wxDefaultPosition, wxDefaultSize,
      style,  wxDefaultValidator, name};
    button->Bind(wxEVT_RADIOBUTTON, &SettingsPage::OnPinchRadioButtonClick,
                 this);
    if (sensitivity == current_sensitivity) {
      button->SetValue(true);
    }

    sizer->Add(button);
  }

  sizer->Add(new wxStaticLine(parent), 0, wxTOP | wxBOTTOM | wxEXPAND, 10);
}

void SettingsPage::SetUpSwipeControls(wxWindow* parent, wxBoxSizer* sizer) {
  auto title = new wxStaticText{parent, wxID_ANY, "Swipe Sensitivity"};
  sizer->Add(title);

  auto description = new wxStaticText{
    parent, wxID_ANY, "A lower sensitivity requires longer swipes."};
  description->SetForegroundColour(Colors::GetSecondaryTextColor());
  sizer->Add(description);
  sizer->AddSpacer(8);

  auto index = size_t{0};
  auto current_sensitivity = settings_.GetSwipeSensitivity();
  for (auto sensitivity :
       Utilities::EnumRange(Settings::SwipeSensitivity::kVeryHigh,
                            Settings::SwipeSensitivity::kVeryLow)) {
    auto label = Utilities::ConvertSwipeSensitivityToString(sensitivity);
    if (label.empty()) {
      continue;
    }

    auto style = index++ == 0 ? wxRB_GROUP : 0;
    auto name = std::to_string(static_cast<int>(sensitivity));

    auto button = new wxRadioButton{
      parent, wxID_ANY,           label, wxDefaultPosition, wxDefaultSize,
      style,  wxDefaultValidator, name};
    button->Bind(wxEVT_RADIOBUTTON, &SettingsPage::OnSwipeRadioButtonClick,
                 this);
    if (sensitivity == current_sensitivity) {
      button->SetValue(true);
    }

    sizer->Add(button);
  }

  sizer->Add(new wxStaticLine(parent), 0, wxTOP | wxBOTTOM | wxEXPAND, 10);
}
