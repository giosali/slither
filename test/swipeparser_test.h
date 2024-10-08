#ifndef SWIPEPARSER_TEST_H
#define SWIPEPARSER_TEST_H

#include <tuple>
#include <vector>

#include "../src/gesture.h"
#include "../src/swipeparser.h"
#include "ut.hpp"

boost::ut::suite<"swipeparser"> swipeparser = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "GetDirection"_test = [] {
    given("The user swipes in various directions") = [] {
      then("I expect the swipes to match the evaluated directions") =
        [](const std::tuple<double, double, Gesture::Direction>& data) {
          auto dx = std::get<0>(data);
          auto dy = std::get<1>(data);
          auto direction = std::get<2>(data);

          auto swipe_parser = SwipeParser{};
          swipe_parser.Begin();
          swipe_parser.Update(dx, dy, 0);
          swipe_parser.End(1);

          expect(swipe_parser.GetDirection() == direction);
        } |
        std::vector<std::tuple<double, double, Gesture::Direction>>{
          {0, 200, Gesture::Direction::kUp},
          {200, 0, Gesture::Direction::kRight},
          {0, -200, Gesture::Direction::kDown},
          {-200, 0, Gesture::Direction::kLeft},
        };
    };
  };

  "IsGestureValid"_test = [] {
    given("The user swipes left by 125 dpi") = [] {
      then("I expect the gesture to be valid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(-125, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == true);
      };
    };

    given("The user swipes right by 125 dpi") = [] {
      then("I expect the gesture to be valid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(125, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == true);
      };
    };

    given("The user swipes left by 50 dpi") = [] {
      then("I expect the gesture to be invalid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(-50, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == false);
      };
    };

    given("The user swipes right by 50 dpi") = [] {
      then("I expect the gesture to be invalid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(50, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == false);
      };
    };

    given("The user ends their swipe gesture on time") = [] {
      then("I expect the gesture to be valid") = [](uint32_t time) {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(200, 0, 0);
        swipe_parser.End(time);

        expect(swipe_parser.IsGestureValid() == true);
      } | std::vector{0, 1, 50, 100, 150, 200, 250};
    };

    given("The user ends their swipe gesture late") = [] {
      then("I expect the gesture to be valid") = [](uint32_t time) {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(200, 0, 0);
        swipe_parser.End(time);

        expect(swipe_parser.IsGestureValid() == false);
      } | std::vector{251, 300, 400, 500, 1000};
    };
  };
};

#endif  // SWIPEPARSER_TEST_H
