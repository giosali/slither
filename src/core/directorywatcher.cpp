#include "directorywatcher.h"

#include <spdlog/spdlog.h>
#include <sys/inotify.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

void DirectoryWatcher::AddFile(const std::string& filename,
                               const std::function<void(void)>& callable) {
  spdlog::info(
    "In DirectoryWatcher::AddFile(const std::string&, const "
    "std::function<void(void)>&)");
  spdlog::debug("filename = {}", filename);

  callables_map_.insert({filename, callable});
}

void DirectoryWatcher::Initialize(const std::filesystem::path& path) {
  path_ = path;
}

void DirectoryWatcher::Watch() {
  spdlog::info("In DirectoryWatcher::Watch(const std::filesystem::path&)");
  auto t = std::jthread{[]() {
    auto fd = inotify_init();
    if (fd == -1) {
      spdlog::error("Failed to initialize inotify: {}", strerror(errno));
      return;
    }

    auto wd = inotify_add_watch(
      fd, path_.c_str(),
      IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO | IN_CREATE | IN_DELETE);
    if (wd == -1) {
      spdlog::error("Failed to add watch: {}", strerror(errno));
      close(fd);
    }

    spdlog::info("Monitoring directory: {}", path_.string());

    auto event_size = sizeof(struct inotify_event);
    auto buffer_length = 1024 * (event_size + 16);
    char buffer[buffer_length];
    while (true) {
      auto length = read(fd, buffer, buffer_length);
      if (length == -1 && errno != EAGAIN) {
        spdlog::error("Failed to read events: {}", strerror(errno));
        break;
      }

      spdlog::info("In DirectoryWatcher::Watch(const std::filesystem::path&)");

      auto i = 0;
      while (i < length) {
        auto event = (struct inotify_event*)&buffer[i];
        spdlog::debug("event->mask = {}", event->mask);

        if (event->mask & IN_MODIFY || event->mask & IN_MOVED_FROM ||
            event->mask & IN_MOVED_TO || event->mask & IN_CREATE ||
            event->mask & IN_DELETE) {
          auto filename = std::string{event->name};
          spdlog::debug("filename = {}", filename);

          if (auto it = callables_map_.find(filename);
              it != callables_map_.end()) {
            spdlog::info("Calling callable");
            it->second();
          }
        }

        i += event_size + event->len;
      }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
  }};
  t.detach();
}

std::unordered_map<std::string, std::function<void(void)>>
  DirectoryWatcher::callables_map_{};

std::filesystem::path DirectoryWatcher::path_{};
