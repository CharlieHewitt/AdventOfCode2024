#pragma once
#include <memory>

namespace advent
{
   class IDay;
}

namespace advent
{
   class DayFactory final
   {
   public:
      explicit DayFactory() = delete;
      ~DayFactory() = delete;

      [[nodiscard]] static auto getDay(int day) noexcept -> std::unique_ptr<IDay>;
   };

}