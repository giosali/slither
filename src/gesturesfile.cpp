#include "gesturesfile.h"

#include <sys/inotify.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "json.hpp"
#include "paths.h"

GesturesFile::GesturesFile()
    : gestures_{}, path_{Paths::ConfigAppDirectory() / "gestures.json"} {
  if (!std::filesystem::exists(path_)) {
    // Creates any missing parent directories.
    auto parent_path = path_.parent_path();
    std::filesystem::create_directories(parent_path);

    // Creates the JSON file and writes an empty array to it.
    auto stream = std::ofstream{path_};
    stream << "[]";

    // TODO: an alternative needs to be found to running the program with sudo.
    //
    // Prevents this file and its parent directory from having the owner be
    // assigned to Super User. This is ne necessary if the user invokes the
    // program with sudo.
    std::filesystem::permissions(parent_path, std::filesystem::perms::all);
    std::filesystem::permissions(path_, std::filesystem::perms::all);
  }

  UpdateGestures();
}

std::vector<Gesture> GesturesFile::GetGestures() const { return gestures_; }

void GesturesFile::Watch() {
  auto t = std::thread{[this]() {
    auto fd = inotify_init();
    if (fd == -1) {
      std::cerr << "Error initializing inotify: " << strerror(errno) << "\n";
      return;
    }

    auto wd = inotify_add_watch(fd, path_.c_str(), IN_MODIFY);
    if (wd == -1) {
      std::cerr << "Error adding watch: " << strerror(errno) << "\n";
      close(fd);
    }

    auto event_size = sizeof(struct inotify_event);
    auto buffer_length = 1024 * (event_size + 16);
    char buffer[buffer_length];
    while (true) {
      auto length = read(fd, buffer, buffer_length);
      if (length == -1 && errno != EAGAIN) {
        std::cerr << "Error reading events: " << strerror(errno) << "\n";
        break;
      }

      auto i = 0;
      while (i < length) {
        auto event = (struct inotify_event*)&buffer[i];
        if (event->mask & IN_MODIFY) {
          UpdateGestures();
        }

        i += event_size + event->len;
      }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
  }};
  t.detach();
}

void GesturesFile::UpdateGestures() {
  auto stream = std::ifstream{path_};

  // Reads the gestures file and transforms its contents to Gesture objects.
  try {
    auto json = nlohmann::json::parse(stream);
    gestures_ = json.template get<std::vector<Gesture>>();
  } catch (const nlohmann::json::exception& e) {
    std::cerr << e.what() << "\n";
  }
}
