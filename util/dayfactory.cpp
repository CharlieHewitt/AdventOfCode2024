#include "util/dayfactory.h"
#include "day1/day1.h"
#include <memory>

using namespace advent;

auto DayFactory::getDay(int day) noexcept -> std::unique_ptr<IDay>
{
   switch (day)
   {
   case 1:
      return std::make_unique<Day1>();

   default: 
      return nullptr;
   }
}