#ifndef SWIPETRACKER_TEST_H
#define SWIPETRACKER_TEST_H

#include <tuple>
#include <vector>

#include "../src/swipetracker.h"
#include "ut.hpp"

boost::ut::suite<"swipetracker"> swipetracker = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "GetDirection"_test = [] {
    given("The user swipes in various directions") = [] {
      then("The swipes should match the evaluated directions") =
        [](const std::tuple<double, double, SwipeTracker::Direction>& data) {
          auto dx = std::get<0>(data);
          auto dy = std::get<1>(data);
          auto direction = std::get<2>(data);

          auto swipe_tracker = SwipeTracker{};
          swipe_tracker.Begin();
          swipe_tracker.Update(dx, dy, 0);
          swipe_tracker.End(1);

          expect(direction == swipe_tracker.GetDirection());
        } |
        std::vector<std::tuple<double, double, SwipeTracker::Direction>>{
          {0, 200, SwipeTracker::Direction::Up},
          {200, 0, SwipeTracker::Direction::Right},
          {0, -200, SwipeTracker::Direction::Down},
          {-200, 0, SwipeTracker::Direction::Left},
        };
    };
  };

  "IsGestureValid"_test = [] {
    given("The user swipes left by 50 dpi") = [] {
      then("The gesture should be invalid") = [] {
        auto swipe_tracker = SwipeTracker{};
        swipe_tracker.Begin();
        swipe_tracker.Update(-50, 0, 0);
        swipe_tracker.End(1);

        expect(swipe_tracker.IsGestureValid() == true);
      };
    };

    given("The user swipes right by 100 dpi") = [] {
      then("The gesture should be invalid") = [] {
        auto swipe_tracker = SwipeTracker{};
        swipe_tracker.Begin();
        swipe_tracker.Update(100, 0, 0);
        swipe_tracker.End(1);

        expect(swipe_tracker.IsGestureValid() == true);
      };
    };

    given("The user ends swipe too late") = [] {
      then("The gesture should be invalid") = [](uint32_t time) {
        auto swipe_tracker = SwipeTracker{};
        swipe_tracker.Begin();
        swipe_tracker.Update(200, 0, 0);
        swipe_tracker.End(time);

        expect(swipe_tracker.IsGestureValid() == true);
      } | std::vector{0, 1, 50, 100, 150, 200, 250};
    };
  };
};

#endif  // SWIPETRACKER_TEST_H
