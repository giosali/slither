#ifndef GESTUREEVENTFACTORY_TEST_H
#define GESTUREEVENTFACTORY_TEST_H

#include <libinput.h>

#include <vector>

#include "../src/core/gestureeventfactory.h"
#include "ut.hpp"

boost::ut::suite<"gestureeventfactory"> inline gestureeventfactory = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "CreateGestureEvent"_test = [] {
    given("I pass an invalid gesture event type") = [] {
      then("I expect an exception to be thrown") =
        [](libinput_event_type event_type) {
          expect(throws([event_type] {
            GestureEventFactory::CreateGestureEvent(nullptr, event_type);
          }));
        } |
        std::vector<libinput_event_type>{
          LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE, LIBINPUT_EVENT_GESTURE_SWIPE_END,
          LIBINPUT_EVENT_GESTURE_PINCH_UPDATE, LIBINPUT_EVENT_GESTURE_PINCH_END,
          LIBINPUT_EVENT_GESTURE_HOLD_END};
    };
  };
};

#endif  // GESTUREEVENTFACTORY_TEST_H
