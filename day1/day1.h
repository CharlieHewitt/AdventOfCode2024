#pragma once
#include "util/iday.h"

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
   
   };
}