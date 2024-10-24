#ifndef MAINSTATUSBAR_H
#define MAINSTATUSBAR_H

#include <wx/event.h>
#include <wx/wx.h>

class MainStatusBar final : public wxStatusBar {
 public:
  MainStatusBar(wxWindow* parent);

  virtual ~MainStatusBar() = default;

 private:
  void OnButtonClick(wxCommandEvent& event);
  void OnSize(wxSizeEvent& event);
  void PositionButtons();

  wxButton* add_button_{nullptr};
  wxButton* delete_button_{nullptr};
  wxButton* edit_button_{nullptr};
};

#endif  // MAINSTATUSBAR_H
