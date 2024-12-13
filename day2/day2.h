#pragma once
#include "util/iday.h"
#include <vector>

namespace advent
{
   class Day2 final : public IDay
   {
   public: 
      explicit Day2() = default;
      ~Day2() final = default;

   private:
      // --- IDay
      auto runPartOne() noexcept -> void final;
      auto runPartTwo() noexcept -> void final;

      auto loadData() noexcept -> void;

      std::vector<std::vector<int>> m_values{};

   };
}