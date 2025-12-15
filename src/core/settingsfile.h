#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#include <filesystem>
#include <mutex>

#include "settings.h"

class SettingsFile {
 public:
  SettingsFile() = delete;

  static void Initialize();
  static Settings GetSettings();
  static void Save();
  static void SetSettings(const Settings& value);
  static void Watch();

 private:
  static void Create();
  static Settings Read();

  static std::mutex mtx_;
  static std::filesystem::path path_;
  static Settings settings_;
};

#endif  // SETTINGSFILE_H
