#include "day5/day5.h"
#include "util/filereader.h"
#include <string_view>
#include <iostream>
#include <algorithm>

using namespace advent;
using namespace std::literals;

namespace
{
   constexpr inline auto RULES_INPUT_FILE = "day5_rules.txt"sv;
   constexpr inline auto MANUALS_INPUT_FILE = "day5_manuals.txt"sv;

}

auto Day5::runPartOne() noexcept -> void
{
   loadData();
   auto total = 0;

   for (auto& manual : m_manuals)
   {
      if (!isManualValid(manual))
         continue;

      auto middleIndex = (manual.size() - 1) / 2;
      total += manual.at(middleIndex);

   }

   std::cout << "Total: " << std::to_string(total) << std::endl;

}

auto Day5::runPartTwo() noexcept -> void
{
   loadData();
   auto total = 0;

   for (auto& manual : m_manuals)
   {
      if (isManualValid(manual))
         continue;

      auto validManual = reorderUntilCorrect(manual);

      auto middleIndex = (validManual.size() - 1) / 2;
      total += validManual.at(middleIndex);
   }

   std::cout << "Total: " << std::to_string(total) << std::endl;


}

auto Day5::loadData() noexcept -> void
{
   auto rulesContent = FileReader::parse(RULES_INPUT_FILE);

   for (auto& rule : rulesContent)
   {
      auto splitIndex = rule.find('|');
      auto preReqPageNr = std::stoi(rule.substr(0, splitIndex));
      auto pageNr = std::stoi(rule.substr(splitIndex + 1, std::string::npos));

      if (!m_rules.count(pageNr))
         m_rules.emplace(std::make_pair(pageNr, std::set<int>{preReqPageNr}));
      else
         m_rules.at(pageNr).insert(preReqPageNr);
   }

   auto manualsContent = FileReader::parse(MANUALS_INPUT_FILE);

   for (auto& manual : manualsContent)
   {
      auto pageNrs = std::vector<int>{};
      auto remainingManual = manual;
      auto index = remainingManual.find(',');
      while (index != std::string::npos)
      {
         pageNrs.push_back(std::stoi(remainingManual.substr(0, index)));
         remainingManual = remainingManual.substr(index + 1, std::string::npos);
         index = remainingManual.find(',');
      }
      pageNrs.push_back(std::stoi(remainingManual));
      m_manuals.push_back(std::move(pageNrs));
   }
}

auto Day5::isManualValid(std::vector<int>& manual) noexcept -> bool
{
   // for each page in manual
   for (auto it = manual.begin(); it != manual.end(); it++)
   {
      // if there are pre-requisite pages
      auto pageNr = *it;
      if (!m_rules.contains(pageNr))
         continue;

      // check that no pre-requisite pages appear after page in the manual
      for (auto prereqPageNr : m_rules.at(pageNr))
      {
         if (std::find(it,manual.end(), prereqPageNr) != manual.end())
         {
            return false;
         }
      }
   }
   return true;
}

auto Day5::reorderUntilCorrect(std::vector<int> manual) -> std::vector<int>
{
   auto ordered = false;
   while (!ordered)
   {
      ordered = reorder(manual);
   }

   return manual;
}

auto Day5::reorder(std::vector<int>& manual) noexcept -> bool
{
   for (auto it = manual.begin(); it != manual.end(); it++)
   {
      auto pageNr = *it;
      if (!m_rules.contains(pageNr))
         continue;

      for (auto prereqPageNr : m_rules.at(pageNr))
      {
         if (auto it2 = std::find(it, manual.end(), prereqPageNr); it2 != manual.end())
         {
            std::iter_swap(it, it2);
            return false;
         }
      }
   }
   return true;
}