#ifndef GESTUREFORMDIALOG_H
#define GESTUREFORMDIALOG_H

#include <wx/wx.h>

#include <cstdint>
#include <vector>

#include "../core/gesture.h"

class GestureFormDialog final : public wxDialog {
 public:
  explicit GestureFormDialog(wxWindow* parent, const wxString& title,
                             int32_t finger_count);
  explicit GestureFormDialog(wxWindow* parent, const wxString& title,
                             const Gesture& gesture);

  virtual ~GestureFormDialog() = default;

 private:
  static uint32_t GtkKeyvalToLinuxInputEventCode(uint32_t keyval);
  void OnCancelButtonClick(wxCommandEvent& event);
  void OnClearButtonClick(wxCommandEvent& event);
  void OnSaveButtonClick(wxCommandEvent& event);
  void OnKeyDown(wxKeyEvent& event);
  void OnTextEnter(wxCommandEvent& event);

  wxChoice* direction_choice_{nullptr};
  int32_t finger_count_;
  wxBoxSizer* inner_{nullptr};
  std::vector<uint32_t> key_codes_{};
  wxStaticText* key_combination_text_{nullptr};
};

#endif  // GESTUREFORMDIALOG_H
