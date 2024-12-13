#pragma once
#include "util/iday.h"
#include <set>
#include <map>
#include <vector>

namespace advent
{
   class Day5 final : public IDay
   {
   public:
      explicit Day5() = default;
      ~Day5() final = default;

   private:
      // --- IDay
      auto runPartOne() noexcept -> void final;
      auto runPartTwo() noexcept -> void final;

      auto loadData() noexcept -> void;

      auto isManualValid(std::vector<int>& manual) noexcept -> bool;
      auto reorderUntilCorrect(std::vector<int> manual) -> std::vector<int>;
      auto reorder(std::vector<int>& manual) noexcept -> bool;
      std::map<int, std::set<int>> m_rules;
      std::vector<std::vector<int>> m_manuals;
   };
}