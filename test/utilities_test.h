#ifndef UTILITIES_TEST_H
#define UTILITIES_TEST_H

#include <array>
#include <cstdint>

#include "../src/core/gesture.h"
#include "../src/core/utilities.h"
#include "ut.hpp"

boost::ut::suite<"utilities"> utilities = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "EnumRange"_test = [] {
    given("I iterate over all Gesture::Direction values") = [] {
      auto values = std::array<int32_t, 7>{0, 1, 2, 3, 4, 5, 6};

      then("I expect them to match their integral values") = [&values] {
        size_t index = 0;
        for (const auto direction : Utilities::EnumRange(
               Gesture::Direction::kNone, Gesture::Direction::kOut)) {
          auto expected = values[index++];
          auto actual = static_cast<int32_t>(direction);
          expect(actual == expected);
        }
      };
    };
  };
};

#endif  // UTILITIES_TEST_H
