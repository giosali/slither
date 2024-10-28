#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/notebook.h>
#include <wx/wx.h>

#include "mainpage.h"

class MainFrame : public wxFrame {
 public:
  MainFrame();

 private:
  MainPage* GetCurrentPage() const;
  void OnClick(wxCommandEvent& event);
  void OnDialogClose(wxCloseEvent& event);
  void UpdatePages();

  wxNotebook* notebook_{nullptr};
};

#endif  // MAINFRAME_H
