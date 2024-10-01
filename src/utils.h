#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
 public:
  Utils() = delete;

  static std::string FormatExceptionMessage(const std::string& context,
                                            const std::string& problem,
                                            const std::string& solution = {});
};

#endif  // UTILS_H
