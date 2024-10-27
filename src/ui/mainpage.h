#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <wx/string.h>
#include <wx/wx.h>

#include <cstdint>

#include "gesturestring.h"

class MainPage final : public wxPanel {
 public:
  explicit MainPage(wxWindow* parent, int32_t finger_count);

  void Append(const GestureString& item) const;
  void Clear() const;
  wxString GetCurrentRow() const;
  int32_t GetFingerCount() const;
  void DeleteCurrentRow() const;

 private:
  int32_t finger_count_{};
  wxListBox* list_box_{nullptr};
};

#endif  // MAINPAGE_H
