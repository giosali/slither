#ifndef GESTUREPAGE_H
#define GESTUREPAGE_H

#include <wx/notebook.h>
#include <wx/wx.h>

#include <cstdint>
#include <optional>
#include <vector>

#include "../core/gesture.h"

class GesturePage final : public wxPanel {
 public:
  explicit GesturePage(wxNotebook* parent, int32_t finger_count);

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

#endif  // GESTUREPAGE_H
