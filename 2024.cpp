
#include "util/challengerunner.h"

#include <iostream>

using namespace advent;

int main()
{
   std::cout << "Advent of code!" << std::endl;

   auto challengeRunner = ChallengeRunner{};
   auto shouldContinue = true;
   while (shouldContinue)
   {
      shouldContinue = challengeRunner.promptAndRun();
   }
}