#ifndef GESTURESFILE_TEST_H
#define GESTURESFILE_TEST_H

#include "../src/gesture.h"
#include "../src/gesturesfile.h"
#include "ut.hpp"

boost::ut::suite<"gesturesfile"> gesturesfile = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "GetGestures"_test = [] {
    given("I have a default-initialized GesturesFile object") = [] {
      auto file = GesturesFile{};

      then("I expect GetGestures to return an empty vector") = [&file] {
        expect(file.GetGestures().empty() == true);
      };
    };
  };
};

#endif  // GESTURESFILE_TEST_H
