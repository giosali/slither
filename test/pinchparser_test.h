#ifndef PINCHPARSER_TEST_H
#define PINCHPARSER_TEST_H

#include "../src/pinchparser.h"
#include "ut.hpp"

boost::ut::suite<"pinchparser"> pinchparser = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "GetDirection"_test = [] {
    given("The user pinches in various directions") = [] {
      then("I expect the pinches to match the evaluated directions") =
        [](const std::tuple<double, Gesture::Direction>& data) {
          auto dx = std::get<0>(data);
          auto direction = std::get<1>(data);

          auto parser = PinchParser{};
          parser.Begin();
          parser.Update(dx, 0);
          parser.End(1);

          expect(parser.GetDirection() == direction);
        } |
        std::vector<std::tuple<double, Gesture::Direction>>{
          {0, Gesture::Direction::kNone},   {20, Gesture::Direction::kNone},
          {-19, Gesture::Direction::kNone}, {39, Gesture::Direction::kNone},
          {40, Gesture::Direction::kIn},    {-20, Gesture::Direction::kOut}};
    };
  };

  "IsGestureValid"_test = [] {
    given("The user pinches inward by 40 dpi") = [] {
      then("I expect the gesture to be valid") = [] {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(40, 0);
        parser.End(1);

        expect(parser.IsGestureValid() == true);
      };
    };

    given("The user pinches inward by 20 dpi") = [] {
      then("I expect the gesture to be invalid") = [] {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(20, 0);
        parser.End(1);

        expect(parser.IsGestureValid() == false);
      };
    };

    given("The user pinches outward by 20 dpi") = [] {
      then("I expect the gesture to be valid") = [] {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(-20, 0);
        parser.End(1);

        expect(parser.IsGestureValid() == true);
      };
    };

    given("The user pinches outward by 10 dpi") = [] {
      then("I expect the gesture to be invalid") = [] {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(-10, 0);
        parser.End(1);

        expect(parser.IsGestureValid() == false);
      };
    };

    given("The user ends their pinch gesture on time") = [] {
      then("I expect the gesture to be valid") = [](uint32_t time) {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(40, 0);
        parser.End(time);

        expect(parser.IsGestureValid() == true);
      } | std::vector{0, 1, 50, 100, 150, 200, 250};
    };

    given("The user ends their pinch gesture late") = [] {
      then("I expect the gesture to be invalid") = [](uint32_t time) {
        auto parser = PinchParser{};
        parser.Begin();
        parser.Update(40, 0);
        parser.End(time);

        expect(parser.IsGestureValid() == false);
      } | std::vector{251, 300, 400, 500, 1000};
    };
  };
};

#endif  // PINCHPARSER_TEST_H
