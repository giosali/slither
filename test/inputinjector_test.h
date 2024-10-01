#ifndef INPUTINJECTOR_TEST_H
#define INPUTINJECTOR_TEST_H

#include "../src/inputinjector.h"
#include "ut.hpp"

boost::ut::suite<"inputinjector"> inputinjector = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "Constructor"_test = [] {
    given("I initialize an InputInjector object") = [] {
      when("I don't have root access or access to /dev/uinput") = [] {
        then("The constructor should throw an exception") = [] {
          expect(throws([] { InputInjector(); }));
        };
      };
    };
  };
};

#endif  // INPUTINJECTOR_TEST_H
