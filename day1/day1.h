#pragma once
#include "util/iday.h"
#include <vector>

namespace advent
{
   class Day1 final : public IDay
   {
   public:
      explicit Day1() = default;
      ~Day1() = default;

   private:
      // --- IDay
      auto runPartOne() noexcept -> void final;
      auto runPartTwo() noexcept -> void final;

      auto loadData() noexcept -> void;
      

      std::vector<int> m_firstLocationIds{};
      std::vector<int> m_secondLocationIds{};
   };
}