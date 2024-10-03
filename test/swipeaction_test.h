#ifndef SWIPEACTION_TEST_H
#define SWIPEACTION_TEST_H

#include <string>
#include <vector>

#include "../src/swipe.h"
#include "../src/swipeaction.h"
#include "ut.hpp"

boost::ut::suite<"swipeaction"> swipeaction = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "to_json"_test = [] {
    given("I initialize a valid SwipeAction object") = [] {
      auto action = SwipeAction{.direction = Swipe::Direction::Up,
                                .finger_count = 3,
                                .key_codes = {1, 2}};

      when("I convert it to a nlohmann::json object") = [&action] {
        // Don't use brace initialization with nlohmann::json.
        // https://json.nlohmann.me/home/faq/#brace-initialization-yields-arrays
        auto json = nlohmann::json(action);

        then("I expect it to return a valid JSON object") = [&json] {
          expect(json.is_object()) << json;
        };
      };
    };
  };

  "from_json"_test = [] {
    given("I have a valid string of JSON") = [] {
      auto json_string =
        "{\"direction\":0,\"fingerCount\":3,\"keyCodes\":[1,2]}";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then("I expect to be able to convert it to its corresponding struct") =
          [&json] {
            auto action = json.template get<SwipeAction>();
            expect(action.direction == Swipe::Direction::Up);
            expect(action.finger_count == 3);
            expect(action.key_codes == std::vector<int>{1, 2});
          };
      };
    };

    given("I have a valid string of JSON of an array of objects") = [] {
      auto json_string =
        "[{\"direction\":0,\"fingerCount\":3,\"keyCodes\":[1,2]},{"
        "\"direction\":1,\"fingerCount\":4,\"keyCodes\":[3,4]}]";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then(
          "I expect to be able to convert it to a std::vector of corresponding "
          "structs") = [&json] {
          expect(json.is_array() == true);

          auto actions = json.template get<std::vector<SwipeAction>>();
          expect(actions.size() == 2);
        };
      };
    };

    given(
      "I have a valid string of JSON of an object with an array of objects "
      "within") = [] {
      auto json_string =
        "{\"actions\":[{\"direction\":0,\"fingerCount\":3,\"keyCodes\":[1,2]},{"
        "\"direction\":1,\"fingerCount\":4,\"keyCodes\":[3,4]}]}";

      when("I convert it to a nlohmann::json object") = [&json_string] {
        auto json = nlohmann::json::parse(json_string);

        then(
          "I expect to be able to index it to retrieve a std::vector of "
          "corresponding structs") = [&json] {
          expect(json.is_object() == true);

          auto actions =
            json.at("actions").template get<std::vector<SwipeAction>>();
          expect(actions.size() == 2);
        };
      };
    };
  };
};

#endif  // SWIPEACTION_TEST_H
