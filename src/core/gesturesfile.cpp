#include "gesturesfile.h"

#include <spdlog/spdlog.h>
#include <sys/inotify.h>

#include <fstream>
#include <iostream>
#include <thread>

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
    std::cerr << e.what() << "\n";
  }

  return {};
}

void GesturesFile::Save() {
  auto j = nlohmann::json{gestures_};
  auto stream = std::ofstream{path_};
  stream << j.dump(2);
}

void GesturesFile::Watch() {
  // TODO: this thread is seemingly run twice; investigate.
  auto t = std::jthread{[]() {
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
          gestures_ = ReadGestures();
        }

        i += event_size + event->len;
      }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
  }};
  t.detach();
}

std::vector<Gesture> GesturesFile::gestures_{};

std::mutex GesturesFile::mtx_{};

std::filesystem::path GesturesFile::path_{};
