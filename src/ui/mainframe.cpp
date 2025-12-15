#include "mainframe.h"

#include <wx/listbook.h>

#include "gesturespage.h"
#include "settingspage.h"

MainFrame::MainFrame()
    : wxFrame{nullptr, wxID_ANY, "Slither", wxDefaultPosition,
              wxSize{600, 500}} {
  // ========
  // CONTROLS
  // ========
  auto listbook =
    new wxListbook{this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_LEFT};

  auto settings_page = new SettingsPage{listbook};
  listbook->AddPage(settings_page, "Settings", true);

  auto gestures_page = new GesturesPage{listbook};
  listbook->AddPage(gestures_page, "Gestures");

  // ======
  // LAYOUT
  // ======
  auto sizer = new wxBoxSizer{wxHORIZONTAL};
  sizer->Add(listbook, 1, wxEXPAND | wxTOP | wxBOTTOM);
  SetSizer(sizer);
}
