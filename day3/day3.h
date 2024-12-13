#pragma once

#include "util/iday.h"
#include <string>
#include <vector>

namespace advent
{
   class Day3 final : public IDay
   {
   public:
      explicit Day3() = default;
      ~Day3() final = default;

   private:
      // --- IDay
      auto runPartOne() noexcept -> void final;
      auto runPartTwo() noexcept -> void final;

      [[nodiscard]] auto processMatch(std::string& match) noexcept -> int;

      auto loadData() noexcept -> void;

      std::vector<std::string> m_matches{};
      bool m_isEnabled{true};
   };
}