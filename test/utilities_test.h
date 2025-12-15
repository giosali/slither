#ifndef UTILITIES_TEST_H
#define UTILITIES_TEST_H

#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

#include "../src/core/gesture.h"
#include "../src/core/utilities.h"
#include "ut.hpp"

boost::ut::suite<"utilities"> inline utilities = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "ConvertGestureTypeToString"_test = [] {
    given("I provide all possible Type values") = [] {
      then("I expect them to match their corresponding string values") =
        [](const auto& tuple) {
          auto type = std::get<0>(tuple);
          auto expected = std::get<1>(tuple);
          auto actual = Utilities::ConvertGestureTypeToString(type);
          expect(actual == expected);
        } |
        std::vector<std::tuple<Gesture::Type, std::string>>{
          {Gesture::Type::kNone, ""},
          {Gesture::Type::kUp, "Swipe Up"},
          {Gesture::Type::kRight, "Swipe Right"},
          {Gesture::Type::kDown, "Swipe Down"},
          {Gesture::Type::kLeft, "Swipe Left"},
          {Gesture::Type::kIn, "Pinch In"},
          {Gesture::Type::kOut, "Pinch Out"},
          {Gesture::Type::kHold, "Hold"},
        };
    };
  };

  "EnumRange"_test = [] {
    given("I iterate over all Gesture::Type values") = [] {
      auto values = std::array<int32_t, 7>{0, 1, 2, 3, 4, 5, 6};

      then("I expect them to match their integral values") = [&values] {
        size_t index = 0;
        for (const auto type :
             Utilities::EnumRange(Gesture::Type::kNone, Gesture::Type::kOut)) {
          auto expected = values[index++];
          auto actual = static_cast<int32_t>(type);
          expect(actual == expected);
        }
      };
    };
  };
};

#endif  // UTILITIES_TEST_H
