#ifndef GESTURESPAGE_H
#define GESTURESPAGE_H

#include <wx/listbook.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include "gesturepage.h"

class GesturesPage final : public wxPanel {
 public:
  explicit GesturesPage(wxListbook* parent);

 private:
  GesturePage* GetCurrentPage() const;
  void OnAddButtonClick(wxCommandEvent& event);
  void OnDeleteButtonClick(wxCommandEvent& event);
  void OnDialogClose(wxCloseEvent& event);
  void OnEditButtonClick(wxCommandEvent& event);
  void UpdatePages();

  wxNotebook* notebook_{nullptr};
};

#endif  // GESTURESPAGE_H
