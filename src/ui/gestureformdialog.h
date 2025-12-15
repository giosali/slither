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
  void SetKeyCombinationText();

  wxChoice* type_choice_{nullptr};
  int32_t finger_count_{};
  wxBoxSizer* inner_{nullptr};
  bool is_editing_{false};
  std::vector<uint32_t> key_codes_{};
  wxStaticText* key_combination_text_{nullptr};
  Gesture previous_gesture_{};
};

#endif  // GESTUREFORMDIALOG_H
