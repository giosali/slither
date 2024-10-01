#include "utils.h"

#include <format>
#include <string_view>

std::string Utils::FormatExceptionMessage(const std::string& context,
                                          const std::string& problem,
                                          const std::string& solution) {
  if (solution.empty()) {
    constexpr auto fmt = std::string_view{"Context: {}\nProblem: {}\n"};
    return std::format(fmt, context, problem);
  } else {
    constexpr auto fmt =
      std::string_view{"Context: {}\nProblem: {}\nSolution: {}\n"};
    return std::format(fmt, context, problem, solution);
  }
}
