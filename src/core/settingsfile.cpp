#include "settingsfile.h"

#include <spdlog/spdlog.h>

#include <fstream>

#include "directorywatcher.h"
#include "paths.h"

void SettingsFile::Initialize() {
  spdlog::info("In SettingsFile::Initialize()");

  path_ = Paths::ConfigAppDirectory() / "settings.json";
  spdlog::debug("path_ = {}", path_.string());

  if (!std::filesystem::exists(path_)) {
    Save();
  }
}

Settings SettingsFile::GetSettings() { return settings_; }

void SettingsFile::Save() {
  spdlog::info("In SettingsFile::Save()");

  if (!std::filesystem::exists(path_)) {
    Create();
  }

  // Must be initialized thusly to prevent the vector from appearing inside
  // another array.
  nlohmann::json j = settings_;

  auto stream = std::ofstream{path_};
  auto dump = j.dump(2);
  spdlog::debug("dump = {}", dump);
  stream << dump;
}

void SettingsFile::SetSettings(const Settings& value) {
  settings_ = value;
  Save();
}

void SettingsFile::Watch() {
  DirectoryWatcher::AddFile(path_.filename(), [] { settings_ = Read(); });
}

void SettingsFile::Create() {
  // Creates any missing parent directories.
  auto parent_path = path_.parent_path();
  std::filesystem::create_directories(parent_path);

  // Creates the JSON file and writes an empty array to it.
  auto stream = std::ofstream{path_};
  stream << "{}";
}

Settings SettingsFile::Read() {
  auto stream = std::ifstream{path_};

  // Reads the gestures file and transforms its contents to Gesture objects.
  try {
    auto json = nlohmann::json::parse(stream);
    auto lock = std::lock_guard(mtx_);
    return json.template get<Settings>();
  } catch (const nlohmann::json::exception& e) {
    spdlog::error(e.what());
  }

  return settings_;
}

std::mutex SettingsFile::mtx_{};

std::filesystem::path SettingsFile::path_{};

Settings SettingsFile::settings_{};
