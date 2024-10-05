#include "gesturesfile.h"

#include <fstream>
#include <iostream>

#include "json.hpp"

GesturesFile::GesturesFile() : gestures_{}, path_{} {}

GesturesFile::GesturesFile(const std::filesystem::path& path) : path_{path} {
  auto stream = std::ifstream{path};

  try {
    auto json = nlohmann::json::parse(stream);
    gestures_ = json.template get<std::vector<Gesture>>();
  } catch (const nlohmann::json::exception& e) {
    std::cerr << e.what() << "\n";
  }
}

std::vector<Gesture> GesturesFile::GetGestures() const { return gestures_; }
