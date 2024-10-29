#include "gesturesfile.h"

#include <spdlog/spdlog.h>

#include <fstream>
#include <unordered_set>

#include "directorywatcher.h"
#include "inputinjector.h"
#include "json.hpp"
#include "paths.h"

void GesturesFile::AddGesture(const Gesture& gesture) {
  gestures_.push_back(gesture);
}

void GesturesFile::DeleteGesture(const Gesture& gesture) {
  spdlog::info("In GesturesFile::DeleteGesture(const Gesture&)");

  for (auto it = gestures_.begin(); it != gestures_.end(); ++it) {
    if (gesture == *it) {
      spdlog::info("Deleting gesture");

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
    Create();
  }

  SetGestures(ReadGestures());
}

void GesturesFile::ReplaceGesture(const Gesture& previous,
                                  const Gesture& current) {
  for (size_t i = 0, l = gestures_.size(); i < l; ++i) {
    if (auto gesture = gestures_[i]; gesture == previous) {
      gestures_[i] = current;
      break;
    }
  }
}

void GesturesFile::Save() {
  spdlog::info("In GesturesFile::Save()");

  if (!std::filesystem::exists(path_)) {
    Create();
  }

  // Must be initialized thusly to prevent the vector from appearing inside
  // another array.
  nlohmann::json j = gestures_;

  auto stream = std::ofstream{path_};
  auto dump = j.dump(2);
  spdlog::debug("dump = {}", dump);
  stream << dump;
}

void GesturesFile::Watch() {
  DirectoryWatcher::AddFile(path_.filename(),
                            [] { SetGestures(ReadGestures()); });
}

void GesturesFile::Create() {
  // Creates any missing parent directories.
  auto parent_path = path_.parent_path();
  std::filesystem::create_directories(parent_path);

  // Creates the JSON file and writes an empty array to it.
  auto stream = std::ofstream{path_};
  stream << "[]";
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

void GesturesFile::SetGestures(const std::vector<Gesture>& value) {
  gestures_ = value;

  InputInjector::Destroy();

  // Extracts all unique key codes from gestures.
  auto key_codes = std::unordered_set<uint32_t>{};
  for (const auto& gesture : value) {
    for (auto key_code : gesture.GetKeyCodes()) {
      key_codes.insert(key_code);
    }
  }

  InputInjector::Initialize(key_codes);
}

std::vector<Gesture> GesturesFile::gestures_{};

std::mutex GesturesFile::mtx_{};

std::filesystem::path GesturesFile::path_{};
