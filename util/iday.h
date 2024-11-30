#pragma once

namespace advent
{
   class IDay
   {
   public:
      virtual ~IDay() = default;

      virtual auto runPartOne() noexcept -> void = 0;
      virtual auto runPartTwo() noexcept -> void = 0;
   };
}