#ifndef GESTURESFILE_TEST_H
#define GESTURESFILE_TEST_H

#include "../src/gesture.h"
#include "../src/gesturesfile.h"
#include "ut.hpp"

boost::ut::suite<"gesturesfile"> gesturesfile = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "FindGestureKeyCodes"_test = [] {
    given("GesturesFile::Initialized hasn't been called") = [] {
      auto direction = Gesture::Direction::kNone;
      auto key_codes = GesturesFile::FindGestureKeyCodes(direction, 0);

      then("I expect an empty vector to be returned") = [&key_codes] {
        expect(key_codes.empty());
      };
    };
  };

  "Watch"_test = [] {
    given("I call this function") = [] {
      then("I expect an exception to not be thrown") = [] {
        expect(nothrow([] { GesturesFile::Watch(); }));
      };
    };
  };
};

#endif  // GESTURESFILE_TEST_H
