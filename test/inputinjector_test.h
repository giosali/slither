#ifndef INPUTINJECTOR_TEST_H
#define INPUTINJECTOR_TEST_H

#include "../src/core/inputinjector.h"
#include "ut.hpp"

boost::ut::suite<"inputinjector"> inputinjector = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "Inject"_test = [] {
    given("I call this function") = [] {
      when("I don't have root privileges") = [] {
        then("I expect an exception to not be thrown") = [] {
          expect(nothrow([] { InputInjector::Inject({}); }));
        };
      };
    };
  };
};

#endif  // INPUTINJECTOR_TEST_H
