#ifndef STANDARDPATHS_TEST_H
#define STANDARDPATHS_TEST_H

#include "../src/standardpaths.h"
#include "ut.hpp"

boost::ut::suite<"standardpaths"> standardpaths = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "HomeDirectory"_test = [] {
    given("I call this function") = [] {
      auto result = StandardPaths::HomeDirectory();

      then("The path should start with either /home or /root") = [&result] {
        auto s = result.string();

        // The path will start with "/root" if the test is run with sudo.
        expect(s.starts_with("/home") || s.starts_with("/root"));
      };
    };
  };
};

#endif  // STANDARDPATHS_TEST_H
