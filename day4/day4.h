#pragma once

#include "util/iday.h"
#include <string>
#include <vector>
#include <optional>

namespace advent
{
   enum Direction
   {
      FORWARDS,
      BACKWARDS,
      UP,
      DOWN,
      PLUSPLUS,
      PLUSMINUS,
      MINUSMINUS,
      MINUSPLUS
   };

   struct Coordinates
   {
      int x;
      int y;
   };

   class Day4 final : public IDay
   {
   public:
      explicit Day4() = default;
      ~Day4() final = default;

   private:
      // --- IDay
      auto runPartOne() noexcept -> void final;
      auto runPartTwo() noexcept -> void final;

      auto loadData() noexcept -> void;

      // -- COMMON
      [[nodiscard]] static auto iterateInDirection(Coordinates coordinates, Direction direction) noexcept -> std::optional<Coordinates>;
      [[nodiscard]] static auto incrementCoordinates(Coordinates coordinates, Direction direction)  noexcept -> Coordinates;
      [[nodiscard]] static auto areCoordinatesValid(Coordinates coordinates) noexcept -> bool;
      
      // -- PART 1
      [[nodiscard]] auto checkInDirectionPart1(Coordinates coordinates, Direction direction) const noexcept-> bool;

      // -- PART 2
      [[nodiscard]] auto checkInDirectionsPart2(Coordinates coordinates, std::pair<Direction,Direction> direction) const noexcept-> bool;
      [[nodiscard]] auto matchesInDirection(Coordinates coordinates, Direction direction) const noexcept -> bool;
      [[nodiscard]] static auto decrementCoordinates(Coordinates coordinates, Direction direction) noexcept -> Coordinates;

      std::vector<std::vector<char>> m_content{};
   };
}