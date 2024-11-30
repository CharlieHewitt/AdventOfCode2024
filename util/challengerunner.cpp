#include "util/challengerunner.h"
#include "util/dayfactory.h"
#include "util/iday.h"

#include <iostream>
#include <string>

using namespace advent;

namespace
{
   [[nodiscard]] auto toString(Challenge challenge) noexcept -> std::string
   {
      auto output = std::string{"day "};

      output += std::to_string(challenge.day);
      output += " part ";

      switch (challenge.part)
      {
      case ChallengePart::ONE:
         output+= "one";
         break;

      case ChallengePart::TWO:
         output += "two";
         break;

      default:
         output += "invalid? ";
      }

      return output;

   }
}

auto ChallengeRunner::promptDay() noexcept -> std::optional<int>
{
   std::cin.clear();
   std::cout << "Please provide the day of the challenge you want to run (or 'exit' to exit):" << std::endl;

   auto input = std::string{};
   std::cin >> input;

   if (input == "exit")
   {
      return std::nullopt;
   }

   try
   {
      auto day = std::stoi(input);
      return day;
   }
   catch (std::invalid_argument e)
   {
      std::cout << "Invalid input: '" << input << "'. Please try again." << std::endl;
      return promptDay();
   }
}

auto ChallengeRunner::promptPart(int day) noexcept -> ChallengePart
{
   std::cin.clear();
   std::cout << "Would you like to run part 1 or 2 of day " << day << "?" << std::endl;

   auto input = std::string{};
   std::cin >> input;

   if (input == "1")
      return ChallengePart::ONE;

   if (input == "2")
      return ChallengePart::TWO;

   std::cout << "Invalid input: '" << input << "'. Please try again." << std::endl;
   return promptPart(day);
}

auto ChallengeRunner::promptChallenge() noexcept -> std::optional<Challenge>
{
   auto day = promptDay();
   if (!day.has_value())
      return std::nullopt;

   auto part = promptPart(day.value());

   return Challenge{ day.value(), part};
}

//! Returns whether or not we should continue
auto ChallengeRunner::promptAndRun() noexcept -> bool
{
   auto challenge = promptChallenge();

   if (!challenge.has_value())
      return false;

   run(challenge.value());
   return true;

}

auto ChallengeRunner::run(Challenge challenge) noexcept -> void
{
   std::cout << "running " << toString(challenge) << "." << std::endl;

   auto day = DayFactory::getDay(challenge.day);

   if (!day)
      return;

   switch (challenge.part)
   {
   case ChallengePart::ONE:
      day->runPartOne();
      break;

   case ChallengePart::TWO:
      day->runPartTwo();
      break;

   default:
      break;
   }
}