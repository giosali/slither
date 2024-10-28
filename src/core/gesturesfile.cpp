#include "gesturesfile.h"

#include <spdlog/spdlog.h>

#include <fstream>

#include "directorywatcher.h"
#include "json.hpp"
#include "paths.h"

void GesturesFile::AddGesture(const Gesture& gesture) {
  gestures_.push_back(gesture);
}

void GesturesFile::DeleteGesture(const Gesture& gesture) {
  for (auto it = gestures_.begin(); it != gestures_.end(); ++it) {
    if (gesture == *it) {
      it = gestures_.erase(it);
      break;
    }
  }
}

std::vector<uint32_t> GesturesFile::FindGestureKeyCodes(
  Gesture::Direction direction, int32_t finger_count) {
  spdlog::debug(
    "In GesturesFile::FindGestureKeyCodes(Gesture::Direction, int32_t): "
    "direction = {}, finger_count = {}",
    static_cast<int>(direction), finger_count);

  auto lock = std::lock_guard(mtx_);

  for (size_t i = 0, l = gestures_.size(); i < l; ++i) {
    if (auto g = gestures_[i];
        g.GetDirection() == direction && g.GetFingerCount() == finger_count) {
      return g.GetKeyCodes();
    }
  }

  return {};
}

std::vector<Gesture> GesturesFile::GetGestures() { return gestures_; }

void GesturesFile::Initialize() {
  path_ = Paths::ConfigAppDirectory() / "gestures.json";
  spdlog::debug("In GesturesFile::Initialize(): path_ = {}", path_.string());

  if (!std::filesystem::exists(path_)) {
    // Creates any missing parent directories.
    auto parent_path = path_.parent_path();
    std::filesystem::create_directories(parent_path);

    // Creates the JSON file and writes an empty array to it.
    auto stream = std::ofstream{path_};
    stream << "[]";
  }

  gestures_ = ReadGestures();
}

std::vector<Gesture> GesturesFile::ReadGestures() {
  auto stream = std::ifstream{path_};

  // Reads the gestures file and transforms its contents to Gesture objects.
  try {
    auto json = nlohmann::json::parse(stream);
    auto lock = std::lock_guard(mtx_);
    return json.template get<std::vector<Gesture>>();
  } catch (const nlohmann::json::exception& e) {
    spdlog::error(e.what());
  }

  return {};
}

void GesturesFile::Save() {
  auto j = nlohmann::json{gestures_};
  auto stream = std::ofstream{path_};
  stream << j.dump(2);
}

void GesturesFile::Watch() {
  DirectoryWatcher::AddFile(path_.filename(),
                            [] { gestures_ = ReadGestures(); });
}

std::vector<Gesture> GesturesFile::gestures_{};

std::mutex GesturesFile::mtx_{};

std::filesystem::path GesturesFile::path_{};
