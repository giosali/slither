#include <spdlog/spdlog.h>

#include <exception>
#include <iostream>

#include "argparse.hpp"
#include "gesturewatcher.h"

int main(int argc, char* argv[]) {
  auto program = argparse::ArgumentParser{"Slither"};

  program.add_argument("--verbose")
    .help("Print various debugging information")
    .default_value(false)
    .implicit_value(true);

  // Basic, just-in-case error handling for argument parsing.
  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    std::cerr << program;
    return 1;
  }

  auto verbose = program.get<bool>("--verbose");
  if (verbose) {
    spdlog::set_level(spdlog::level::debug);
  }

  auto gesture_watcher = GestureWatcher{};
  gesture_watcher.Enable();
}
