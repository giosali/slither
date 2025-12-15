#include <spdlog/spdlog.h>
#include <wx/app.h>
#include <wx/init.h>

#include <exception>
#include <iostream>

#include "argparse.hpp"
#include "core/gesturewatcher.h"
#include "ui/app.h"

int main(int argc, char* argv[]) {
  auto program = argparse::ArgumentParser{"Slither"};
  program.add_argument("--gui")
    .help("Open the GUI to configure touchpad gestures")
    .default_value(false)
    .implicit_value(true);
  program.add_argument("--verbose")
    .help("Print various debugging information")
    .default_value(false)
    .implicit_value(true);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    std::cerr << program;
    return 1;
  }

  auto verbose = program.get<bool>("--verbose");
  spdlog::set_level(verbose ? spdlog::level::debug : spdlog::level::off);

  // GUI portion of the program.
  auto gui = program.get<bool>("--gui");
  if (gui) {
    wxApp::SetInstance(new App{});
    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxEntryCleanup();
    return 0;
  }

  // Core portion of the program.
  auto gesture_watcher = GestureWatcher{};
  gesture_watcher.Enable();
}
