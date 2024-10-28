#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <wx/wx.h>

#include <cstdint>
#include <optional>
#include <vector>

#include "../core/gesture.h"

class MainPage final : public wxPanel {
 public:
  explicit MainPage(wxWindow* parent, int32_t finger_count);

  void Append(const Gesture& gesture);
  void Clear();
  std::optional<Gesture> GetCurrentGesture() const;
  int32_t GetFingerCount() const;
  void DeleteCurrentRow() const;

 private:
  int32_t finger_count_{};
  std::vector<Gesture> gestures_{};
  wxListBox* list_box_{nullptr};
};

#endif  // MAINPAGE_H
