#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

class Constants final {
 public:
  static constexpr std::string kAddButtonLabel{"Add"};
  static constexpr std::string kDeleteButtonLabel{"Delete"};
  static constexpr std::string kEditButtonLabel{"Edit"};

  Constants() = delete;
};

#endif  // CONSTANTS_H
