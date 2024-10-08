#ifndef INPUTINJECTOR_TEST_H
#define INPUTINJECTOR_TEST_H

#include <cstdint>

#include "../src/inputinjector.h"
#include "ut.hpp"

boost::ut::suite<"inputinjector"> inputinjector = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "Inject"_test = [] {
    given("I call this function") = [] {
      when("I don't have root privileges") = [] {
        then("I expect an exception to be thrown") = [] {
          auto key_1 = uint32_t{2};
          expect(throws([key_1] { InputInjector::Inject({key_1}); }));
        };
      };
    };
  };
};

#endif  // INPUTINJECTOR_TEST_H
