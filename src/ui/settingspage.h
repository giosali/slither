#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <wx/listbook.h>
#include <wx/spinctrl.h>
#include <wx/wx.h>

#include "../core/settings.h"

class SettingsPage final : public wxPanel {
 public:
  explicit SettingsPage(wxListbook* parent);

 private:
  void OnPinchRadioButtonClick(wxCommandEvent& event);
  void OnSaveButtonClick(wxCommandEvent& event);
  void OnSpinControlUpdate(wxSpinEvent& event);
  void OnSwipeRadioButtonClick(wxCommandEvent& event);
  void SetUpButtons(wxWindow* parent, wxBoxSizer* sizer);
  void SetUpHoldControls(wxWindow* parent, wxBoxSizer* sizer);
  void SetUpPinchControls(wxWindow* parent, wxBoxSizer* sizer);
  void SetUpSwipeControls(wxWindow* parent, wxBoxSizer* sizer);

  Settings settings_{};
};

#endif  // SETTINGSPAGE_H
