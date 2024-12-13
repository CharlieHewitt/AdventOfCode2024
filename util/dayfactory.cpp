#include "util/dayfactory.h"
#include "day1/day1.h"
#include "day2/day2.h"
#include "day3/day3.h"
#include "day4/day4.h"
#include "day5/day5.h"
#include <memory>

using namespace advent;

auto DayFactory::getDay(int day) noexcept -> std::unique_ptr<IDay>
{
   switch (day)
   {
   case 1:
      return std::make_unique<Day1>();

   case 2:
      return std::make_unique<Day2>();

   case 3:
      return std::make_unique<Day3>();

   case 4:
      return std::make_unique<Day4>();

   case 5:
      return std::make_unique<Day5>();

   default: 
      return nullptr;
   }
}