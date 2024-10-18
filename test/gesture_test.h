#ifndef GESTURE_TEST_H
#define GESTURE_TEST_H

#include <cstdint>
#include <tuple>
#include <vector>

#include "../include/json.hpp"
#include "../src/core/gesture.h"
#include "ut.hpp"

boost::ut::suite<"gesture"> inline gesture = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "StringifyDirection"_test = [] {
    given(
      "I call Gesture::StringifyDirection with all possible Gesture::Direction "
      "values") = [] {
      then("I expect them to match their corresponding string values") =
        [](const auto& tuple) {
          auto direction = std::get<0>(tuple);
          auto expected = std::get<1>(tuple);
          auto actual = Gesture::StringifyDirection(direction);
          expect(actual == expected);
        } |
        std::vector<std::tuple<Gesture::Direction, std::string>>{
          {Gesture::Direction::kNone, "Hold"},
          {Gesture::Direction::kUp, "Swipe Up"},
          {Gesture::Direction::kRight, "Swipe Right"},
          {Gesture::Direction::kDown, "Swipe Down"},
          {Gesture::Direction::kLeft, "Swipe Left"},
          {Gesture::Direction::kIn, "Pinch Inward"},
          {Gesture::Direction::kOut, "Pinch Outward"},
        };
    };
  };

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

  "ToString"_test = [] {
    given("I have a Gesture object with the Up direction") = [] {
      auto gesture = Gesture{};
      gesture.SetDirection(Gesture::Direction::kUp);

      when("I call SetKeyCodes with a variety of key codes") = [&gesture] {
        then("I expect to receive the correct string representations") =
          [&gesture](const auto& tuple) {
            auto key_codes = std::get<0>(tuple);
            auto expected = "Swipe Up, " + std::get<1>(tuple);

            gesture.SetKeyCodes(key_codes);
            auto actual = gesture.ToString();

            expect(actual == expected);
          } |
          std::vector<std::tuple<std::vector<uint32_t>, std::string>>{
            {{29, 16}, "CTRL + Q"}, {{97, 2}, "CTRL + 1"}};
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
