#ifndef PATHS_TEST_H
#define PATHS_TEST_H

#include "../src/paths.h"
#include "ut.hpp"

boost::ut::suite<"paths"> paths = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "ConfigAppDirectory"_test = [] {
    given("I call this function") = [] {
      auto path = Paths::ConfigAppDirectory();

      then("I expect this path to end with 'slither'") = [&path] {
        expect(path.string().ends_with("slither"));
      };

      then("I expect this path to start with ConfigDirectory") = [&path] {
        auto config = Paths::ConfigDirectory().string();
        expect(path.string().starts_with(config));
      };
    };
  };

  "ConfigDirectory"_test = [] {
    given("I call this function") = [] {
      auto path = Paths::ConfigDirectory();

      then("I expect this path to end with '/.config'") = [&path] {
        expect(path.string().ends_with("/.config"));
      };

      then("I expect this path to start with HomeDirectory") = [&path] {
        auto home = Paths::HomeDirectory().string();
        expect(path.string().starts_with(home));
      };
    };
  };

  "HomeDirectory"_test = [] {
    given("I call this function") = [] {
      auto path = Paths::HomeDirectory();

      then("I expect the path to start with either /home or /root") = [&path] {
        auto s = path.string();

        // The path will start with "/root" if the test is run with sudo.
        expect(s.starts_with("/home") || s.starts_with("/root"));
      };
    };
  };
};

#endif  // PATHS_TEST_H
