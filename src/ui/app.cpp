#include "app.h"

#include "mainframe.h"

bool App::OnInit() {
  auto frame = new MainFrame{};
  frame->Show();
  return true;
}
