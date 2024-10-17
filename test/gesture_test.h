#ifndef GESTURE_TEST_H
#define GESTURE_TEST_H

#include "../include/json.hpp"
#include "../src/core/gesture.h"
#include "ut.hpp"

boost::ut::suite<"gesture"> gesture = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  feature("Getters/Setters") = [] {
    given("I have a Gesture object") = [] {
      auto gesture = Gesture{};

      when("I set a value via SetDirection") = [&gesture] {
        auto value = Gesture::Direction::kUp;
        gesture.SetDirection(value);

        then("I expect to retrieve it through GetDirection") =
          [&gesture, value] { expect(gesture.GetDirection() == value); };
      };

      when("I set a value via SetFingerCount") = [&gesture] {
        auto value = 4;
        gesture.SetFingerCount(value);

        then("I expect to retrieve it through GetFingerCount") =
          [&gesture, value] { expect(gesture.GetFingerCount() == value); };
      };

      when("I set a value via SetKeyCodes") = [&gesture] {
        auto value = std::vector<uint32_t>{1, 2};
        gesture.SetKeyCodes(value);

        then("I expect to retrieve it through GetFingerCount") =
          [&gesture, &value] { expect(gesture.GetKeyCodes() == value); };
      };
    };
  };

  "from_json"_test = [] {
    given("I have a valid string of JSON") = [] {
      auto json_string =
        "{\"direction\":1,\"fingerCount\":3,\"keyCodes\":[1,2]}";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then("I expect to be able to convert it to its corresponding object") =
          [&json] {
            auto gesture = json.template get<Gesture>();
            expect(gesture.GetDirection() == Gesture::Direction::kUp);
            expect(gesture.GetFingerCount() == 3);
            expect(gesture.GetKeyCodes() == std::vector<uint32_t>{1, 2});
          };
      };
    };

    given("I have a valid string of JSON of an array of objects") = [] {
      auto json_string =
        "[{\"direction\":1,\"fingerCount\":3,\"keyCodes\":[1,2]},{"
        "\"direction\":1,\"fingerCount\":4,\"keyCodes\":[3,4]}]";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then(
          "I expect to be able to convert it to a std::vector of corresponding "
          "objects") = [&json] {
          auto gestures = json.template get<std::vector<Gesture>>();

          expect(json.is_array() == true);
          expect(gestures.size() == 2);
        };
      };
    };

    given(
      "I have a valid string of JSON of an object with an array of objects "
      "within") = [] {
      auto json_string =
        "{\"gestures\":[{\"direction\":1,\"fingerCount\":3,\"keyCodes\":[1,2]},"
        "{"
        "\"direction\":2,\"fingerCount\":4,\"keyCodes\":[3,4]}]}";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then(
          "I expect to be able to index it to retrieve a std::vector of "
          "corresponding objects") = [&json] {
          expect(json.is_object() == true);

          auto gestures =
            json.at("gestures").template get<std::vector<Gesture>>();
          expect(gestures.size() == 2);
        };
      };
    };
  };

  "to_json"_test = [] {
    given("I initialize a valid Gesture object") = [] {
      auto gesture = Gesture{};
      gesture.SetDirection(Gesture::Direction::kUp);
      gesture.SetFingerCount(3);
      gesture.SetKeyCodes({1, 2});

      when("I convert it to a nlohmann::json object") = [&gesture] {
        // Don't use brace initialization with nlohmann::json.
        // https://json.nlohmann.me/home/faq/#brace-initialization-yields-arrays
        auto json = nlohmann::json(gesture);

        then("I expect it to return a valid JSON object") = [&json] {
          expect(json.is_object()) << json;
        };
      };
    };
  };
};

#endif  // GESTURE_TEST_H
