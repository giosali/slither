#include "../src/utils.cpp"

#include <format>
#include <string>
#include <string_view>

#include "ut.hpp"

boost::ut::suite<"utils"> utils = [] {
  using namespace boost::ut;
  using namespace boost::ut::bdd;
  using namespace boost::ut::literals;

  "FormatExceptionMessage"_test = [] {
    given("I provide a context and a problem") = [] {
      auto context =
        std::string{"Saving connection pooling configuration changes to disk."};
      auto problem = std::string{"Write permission denied on file '/xxx/yyy'."};

      then("The returned message should not contain a solution") = [=] {
        constexpr auto fmt = std::string_view{"Context: {}\nProblem: {}\n"};
        auto expected = std::format(fmt, context, problem);
        auto actual = Utils::FormatExceptionMessage(context, problem);
        expect(expected == actual);
      };
    };

    given("I provide a context, a problem, and a solution") = [] {
      auto context =
        std::string{"Sending email to 'abc@xyz.com' regarding 'Blah'."};
      auto problem =
        std::string{"SMTP connection refused by server 'mail.xyz.com'."};
      auto solution = std::string{
        "Contact the mail server administrator to report a service problem.  "
        "The email will be sent later. You may want to tell 'abc@xyz.com' "
        "about this problem."};

      then("The returned message should contain a solution") = [=] {
        constexpr auto fmt =
          std::string_view{"Context: {}\nProblem: {}\nSolution: {}\n"};
        auto expected = std::format(fmt, context, problem, solution);
        auto actual = Utils::FormatExceptionMessage(context, problem, solution);
        expect(expected == actual);
      };
    };
  };
};