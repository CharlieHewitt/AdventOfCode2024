#include "day1/day1.h"
#include "util/filereader.h"

#include <algorithm>
#include <iostream>
#include <string_view>
#include <ranges>
#include <cmath>
#include <numeric>

using namespace advent;
using namespace std::literals;

namespace
{
   static constexpr auto INPUT_FILENAME = "day1.txt"sv;
}

auto Day1::runPartOne() noexcept -> void 
{
   std::cout << "Hi there" << std::endl;

   loadData();

   auto sortedFirstLocations = std::ranges::sort(m_firstLocationIds);
   auto sortedSecondLocations = std::ranges::sort(m_secondLocationIds);

   auto val = std::transform_reduce(
      m_firstLocationIds.begin(),
      m_firstLocationIds.end(),
      m_secondLocationIds.begin(),
      0,
      std::plus<>{},
      [](int firstLocation, int secondLocation) 
      {
         return std::abs(firstLocation - secondLocation);
      }
   );

   std::cout << "Puzzle answer: " << val << "." << std::endl;
}

auto Day1::runPartTwo() noexcept -> void
{
   std::cout << "That time of year again." << std::endl;

   loadData();

   auto sortedFirstLocations = std::ranges::sort(m_firstLocationIds);
   auto sortedSecondLocations = std::ranges::sort(m_secondLocationIds);

   auto view = m_firstLocationIds | std::views::transform([this](auto const i) { return i * std::ranges::count(m_secondLocationIds, i); });

   // This had to be an int64 to avoid some conversion compiler warnings
   auto initialValue = uint64_t{ 0 };

   auto sum = std::accumulate(view.begin(), view.end(), initialValue);

   std::cout << "Puzzle answer: " << sum << "." << std::endl;

}

auto Day1::loadData() noexcept -> void
{
   auto data = FileReader::parse(INPUT_FILENAME);
   
   for (auto& line : data)
   {
      auto firstLocationIndex = line.find_first_of(" ");
      m_firstLocationIds.emplace_back(std::stoi(line.substr(0, firstLocationIndex)));
      
      // there are three spaces between the numbers ...
      m_secondLocationIds.emplace_back(std::stoi(line.substr(firstLocationIndex + 3)));
   }

}