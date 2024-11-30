#include "day1/day1.h"
#include "util/filereader.h"

#include <iostream>
#include <string_view>

using namespace advent;
using namespace std::literals;

namespace
{
   static constexpr auto INPUT_FILENAME = "day1.txt"sv;
}

auto Day1::runPartOne() noexcept -> void 
{
   std::cout << "Hi there" << std::endl;

   auto data = FileReader::parse(INPUT_FILENAME);

   for (auto& line : data)
   {
      std::cout << line << std::endl;
   }
}

auto Day1::runPartTwo() noexcept -> void 
{
   std::cout << "That time of year again." << std::endl;
}