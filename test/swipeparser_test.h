#ifndef SWIPEPARSER_TEST_H
#define SWIPEPARSER_TEST_H

#include <tuple>
#include <vector>

#include "../src/swipeparser.h"
#include "ut.hpp"

boost::ut::suite<"swipeparser"> swipeparser = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "GetDirection"_test = [] {
    given("The user swipes in various directions") = [] {
      then("The swipes should match the evaluated directions") =
        [](const std::tuple<double, double, SwipeParser::Direction>& data) {
          auto dx = std::get<0>(data);
          auto dy = std::get<1>(data);
          auto direction = std::get<2>(data);

          auto swipe_parser = SwipeParser{};
          swipe_parser.Begin();
          swipe_parser.Update(dx, dy, 0);
          swipe_parser.End(1);

          expect(direction == swipe_parser.GetDirection());
        } |
        std::vector<std::tuple<double, double, SwipeParser::Direction>>{
          {0, 200, SwipeParser::Direction::Up},
          {200, 0, SwipeParser::Direction::Right},
          {0, -200, SwipeParser::Direction::Down},
          {-200, 0, SwipeParser::Direction::Left},
        };
    };
  };

  "IsGestureValid"_test = [] {
    given("The user swipes left by 50 dpi") = [] {
      then("The gesture should be invalid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(-50, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == true);
      };
    };

    given("The user swipes right by 100 dpi") = [] {
      then("The gesture should be invalid") = [] {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(100, 0, 0);
        swipe_parser.End(1);

        expect(swipe_parser.IsGestureValid() == true);
      };
    };

    given("The user ends swipe too late") = [] {
      then("The gesture should be invalid") = [](uint32_t time) {
        auto swipe_parser = SwipeParser{};
        swipe_parser.Begin();
        swipe_parser.Update(200, 0, 0);
        swipe_parser.End(time);

        expect(swipe_parser.IsGestureValid() == true);
      } | std::vector{0, 1, 50, 100, 150, 200, 250};
    };
  };
};

#endif  // SWIPEPARSER_TEST_H
