#include "day3/day3.h"
#include "util/filereader.h"
#include <iostream>
#include <string_view>
#include <regex>

using namespace advent;
using namespace std::literals;

namespace
{
   static constexpr auto INPUT_FILENAME = "day3.txt"sv;
   static constexpr auto MULTIPLY_PREFIX = "mul("sv;
   static constexpr auto ENABLING_STATEMENT = "do()";
   static constexpr auto DISABLING_STATEMENT = "don't()";

   auto multiply(std::string multiplyString) noexcept -> int
   {
      auto splitIndex = multiplyString.find(",");

      // Part 2 addition ...
      if (splitIndex == std::string::npos)
         return 0;

      auto first = std::stoi(multiplyString.substr(MULTIPLY_PREFIX.length(), splitIndex - MULTIPLY_PREFIX.length()));
      auto second = std::stoi(multiplyString.substr(splitIndex + 1, multiplyString.length()-splitIndex));

      return first * second;
   }
}

auto Day3::runPartOne() noexcept -> void
{
   loadData();

   auto total = 0;

   for (auto& multiplyStr : m_matches)
      total += multiply(multiplyStr);

   std::cout << "Puzzle result: " << std::to_string(total) << std::endl;

}

auto Day3::runPartTwo() noexcept -> void
{
   loadData();

   auto total = 0;

   for (auto& match : m_matches)
      total += processMatch(match);

   std::cout << "Puzzle result: " << std::to_string(total) << std::endl;
}

auto Day3::loadData() noexcept -> void
{
   auto data = FileReader::parse(INPUT_FILENAME);

   for (auto& line : data)
   {
      auto regExpr = std::regex{ "do\\(\\)|don't\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\)" };

      auto beginIt =
         std::sregex_iterator{ line.begin(), line.end(), regExpr  };
      auto endIt = std::sregex_iterator{};

      for (auto i = beginIt; i != endIt; ++i)
         m_matches.emplace_back(i->str());  
   }
}

auto Day3::processMatch(std::string& match) noexcept -> int
{
   if (match == ENABLING_STATEMENT)
   {
      m_isEnabled = true;
      return 0;
   }
   else if (match == DISABLING_STATEMENT)
   {
      m_isEnabled = false;
      return 0;
   }

   if (m_isEnabled)
      return multiply(match);
   
   return 0;
}






