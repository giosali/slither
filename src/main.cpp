#include <gtkmm-4.0/gtkmm.h>
#include <spdlog/spdlog.h>

#include <exception>
#include <iostream>

#include "argparse.hpp"
#include "core/gesturesfile.h"
#include "core/gesturewatcher.h"
#include "ui/mainwindow.h"

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
    auto app = Gtk::Application::create("io.github.giosali.slither");
    return app->make_window_and_run<MainWindow>(0, nullptr);
  }

  // Core portion of the program.
  GesturesFile::Initialize();

  auto gesture_watcher = GestureWatcher{};
  gesture_watcher.Enable();
}
