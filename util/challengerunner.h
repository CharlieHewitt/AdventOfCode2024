#pragma once
#include <optional>

namespace advent
{
   enum class ChallengePart
   {
      ONE,
      TWO
   };

   struct Challenge
   {
      int day;
      ChallengePart part;
   };

   class ChallengeRunner
   {
   public:
      explicit ChallengeRunner() = default;
      ~ChallengeRunner() = default;

      // ... = delete
      // 

      [[nodiscard]] auto promptDay() noexcept -> std::optional<int>;
      [[nodiscard]] auto promptPart(int day) noexcept -> ChallengePart;
      [[nodiscard]] auto promptChallenge() noexcept -> std::optional<Challenge>;

      //! Returns whether or not we should continue
      [[nodiscard]] auto promptAndRun() noexcept -> bool;
      auto run(Challenge challenge) noexcept -> void;

      private:
         bool m_shouldExit{ false };
    };
}