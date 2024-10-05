#include "gesturesfile.h"

#include <fstream>
#include <iostream>

#include "json.hpp"

GesturesFile::GesturesFile() : gestures_{}, path_{} {}

GesturesFile::GesturesFile(const std::filesystem::path& path) : path_{path} {
  // Creates the gestures file if it doesn't exist.
  if (!std::filesystem::exists(path)) {
    // Creates any missing parent directories.
    std::filesystem::create_directories(path.parent_path());

    auto stream = std::ofstream{path_};
    stream << "[]";
  }

  auto stream = std::ifstream{path};

  // Reads the gestures file and transforms its contents to Gesture objects.
  try {
    auto json = nlohmann::json::parse(stream);
    gestures_ = json.template get<std::vector<Gesture>>();
  } catch (const nlohmann::json::exception& e) {
    std::cerr << e.what() << "\n";
  }
}

std::vector<Gesture> GesturesFile::GetGestures() const { return gestures_; }
