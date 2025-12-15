#include "app.h"

#include "../core/gesturesfile.h"
#include "../core/settingsfile.h"
#include "mainframe.h"

bool App::OnInit() {
  SettingsFile::Initialize();
  GesturesFile::Initialize(true);

  auto frame = new MainFrame{};
  frame->Show();
  return true;
}
