#include "day2/day2.h"
#include "util/filereader.h"
#include <string_view>
#include <vector>
#include <ranges>
#include <algorithm>
#include <optional>
#include <iostream>
#include <chrono>

using namespace advent;
using namespace std::literals;

namespace
{
   static constexpr auto INPUT_FILENAME = "day2.txt"sv;

   auto isInRange(int current, int next) noexcept -> bool
   {
      auto delta = std::abs(current - next);
      return delta > 0 && delta < 4;
   }

   auto isDirectionConsistent(int current, int next, bool isIncreasing) noexcept -> bool
   {
      return (next > current) == isIncreasing;
   }

   auto isValid(int current, int next, std::optional<bool>& isIncreasing) noexcept -> bool
   {
      if (!isIncreasing.has_value())
      {
         isIncreasing = (next > current);
      }

      return isDirectionConsistent(current, next, isIncreasing.value()) && isInRange(current, next);
   }

   auto isSeriesValid(std::vector<int>& numbers) noexcept -> bool
   {
      auto currentIt = numbers.begin();
      auto nextIt = numbers.begin();
      auto isIncreasing = std::optional<bool>{};

      auto valid = true;
      while (valid)
      {
         currentIt = nextIt;
         nextIt++;

         if (nextIt == numbers.end())
            break;

         valid = isValid(*currentIt, *nextIt, isIncreasing);
      }

      std::cout << "----" << std::endl;
      return valid;
   }
}

auto Day2::runPartOne() noexcept -> void
{
   loadData();

   auto numberOfValidSeries = 0;
   for (auto& series : m_values)
   {
      if (isSeriesValid(series))
         numberOfValidSeries++;
   }
  
   std::cout << "Puzzle result: " << std::to_string(numberOfValidSeries) << std::endl;
}

auto Day2::runPartTwo() noexcept -> void
{
   loadData();

   auto numberOfValidSeries = 0;
   for (auto& series : m_values)
   {
      if (isSeriesValid(series))
         numberOfValidSeries++;
      else
      {
         for (auto i = 0; i < series.size(); i++)
         {
            auto tempSeries = series;
            tempSeries.erase(tempSeries.begin() + i);
            if (isSeriesValid(tempSeries))
            {
               numberOfValidSeries++;
               break;
            }
         }
      }
   }

   std::cout << "Puzzle result: " << std::to_string(numberOfValidSeries) << std::endl;
}

auto Day2::loadData() noexcept -> void
{
   auto data = FileReader::parse(INPUT_FILENAME);

   for (auto& line : data)
   {
      auto lineContent = std::vector<int>{};
      auto remainingLineContent = line;
      auto index = size_t{ };

      while ((index = remainingLineContent.find(" ")) != std::string::npos)
      {
         lineContent.emplace_back(std::stoi(remainingLineContent.substr(0, index)));
         remainingLineContent = remainingLineContent.substr(index+1);
      }

      lineContent.emplace_back(std::stoi(remainingLineContent));

      m_values.emplace_back(std::move(lineContent));
   }
}





