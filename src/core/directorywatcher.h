#ifndef DIRECTORYWATCHER_H
#define DIRECTORYWATCHER_H

#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>

class DirectoryWatcher final {
 public:
  DirectoryWatcher() = delete;

  static void AddFile(const std::string& filename,
                      const std::function<void(void)>& callable);
  static void Initialize(const std::filesystem::path& path);
  static void Watch();

 private:
  static std::unordered_map<std::string, std::function<void(void)>>
    callables_map_;
  static std::filesystem::path path_;
};

#endif  // DIRECTORYWATCHER_H
