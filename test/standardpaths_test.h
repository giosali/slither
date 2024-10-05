#ifndef STANDARDPATHS_TEST_H
#define STANDARDPATHS_TEST_H

#include "../src/standardpaths.h"
#include "ut.hpp"

boost::ut::suite<"standardpaths"> standardpaths = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "ConfigDirectory"_test = [] {
    given("I call this function") = [] {
      auto path = StandardPaths::ConfigDirectory();

      then("I expect this path to end with '/.config'") = [&path] {
        expect(path.string().ends_with("/.config"));
      };

      then("I expect this path to start with HomeDirectory") = [&path] {
        auto home = StandardPaths::HomeDirectory().string();
        expect(path.string().starts_with(home));
      };
    };
  };

  "HomeDirectory"_test = [] {
    given("I call this function") = [] {
      auto path = StandardPaths::HomeDirectory();

      then("I expect the path to start with either /home or /root") = [&path] {
        auto s = path.string();

        // The path will start with "/root" if the test is run with sudo.
        expect(s.starts_with("/home") || s.starts_with("/root"));
      };
    };
  };
};

#endif  // STANDARDPATHS_TEST_H
