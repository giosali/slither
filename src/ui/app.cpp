#include "app.h"

#include "../core/gesturesfile.h"
#include "mainframe.h"

bool App::OnInit() {
  GesturesFile::Initialize(true);

  auto frame = new MainFrame{};
  frame->Show();
  return true;
}
