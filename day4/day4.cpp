#include "day4/day4.h"
#include "util/filereader.h"
#include <iostream>
#include <array>

using namespace advent;
using namespace std::literals;
namespace
{
   inline constexpr auto INPUT_FILENAME = "day4.txt"sv;
   inline constexpr auto XMAS = "XMAS"sv;
   inline constexpr auto DIRECTIONS = std::array<Direction,8>{Direction::FORWARDS, Direction::BACKWARDS, Direction::UP, Direction::DOWN, Direction::PLUSPLUS, Direction::PLUSMINUS, Direction::MINUSMINUS, Direction::MINUSPLUS};

   inline constexpr auto PERPENDICULAR_DIRECTIONS = std::array<std::pair<Direction, Direction>, 4>{
      std::make_pair(Direction::PLUSPLUS, Direction::MINUSPLUS),
      std::make_pair(Direction::PLUSPLUS, Direction::PLUSMINUS),
      std::make_pair(Direction::MINUSMINUS, Direction::MINUSPLUS),
      std::make_pair(Direction::MINUSMINUS, Direction::PLUSMINUS)
   };

   inline constexpr auto UPPER_BOUND = 140;
}

auto Day4::runPartOne() noexcept -> void
{
   loadData();

   auto numberOfXmas = 0;
   for (auto x = 0; x < UPPER_BOUND; x++)
   {
      for (auto y = 0; y < UPPER_BOUND; y++)
      {
         for (auto dir : DIRECTIONS)
         {
           if (checkInDirectionPart1(Coordinates{ x,y }, dir))
            {
               numberOfXmas++;
            }
         }
      }
   }

   auto total = 0;

   std::cout << "Puzzle result: " << std::to_string(numberOfXmas) << std::endl;
}

auto Day4::runPartTwo() noexcept -> void
{
   loadData();

   auto numberOfXmas = 0;
   for (auto x = 0; x < UPPER_BOUND; x++)
   {
      for (auto y = 0; y < UPPER_BOUND; y++)
      {
         if (m_content.at(x).at(y) == 'A')
         {
            for (auto directions : PERPENDICULAR_DIRECTIONS)
            {
               if (checkInDirectionsPart2(Coordinates{ x,y }, directions))
               {
                  numberOfXmas++;
                  break;
               }
            }
         }
      }
   }
   std::cout << "Puzzle result: " << std::to_string(numberOfXmas) << std::endl;
}

auto Day4::loadData() noexcept -> void
{
   auto data = FileReader::parse(INPUT_FILENAME);

   for (auto& line : data)
   {
      auto lineContent = std::vector<char>{};
      for (auto& character : line)
      {
         lineContent.push_back(character);
      }

      m_content.emplace_back(std::move(lineContent));
   }

   // hi
}

auto Day4::checkInDirectionPart1(Coordinates startingCoordinates, Direction direction) const noexcept -> bool
{
   if (m_content.at(startingCoordinates.x).at(startingCoordinates.y) != 'X')
      return false;

   auto coordinates = std::optional<Coordinates>{};
   coordinates = startingCoordinates;
   for (auto i = 1; i < XMAS.length(); i++)
   {
      coordinates = iterateInDirection(coordinates.value(), direction);
      if (!coordinates.has_value())
         return false;

      auto [x, y] = coordinates.value();
      if (m_content.at(x).at(y) != XMAS.at(i))
         return false;
   }


   return true;
}

auto Day4::iterateInDirection(Coordinates coordinates, Direction direction) noexcept -> std::optional<Coordinates>
{
   auto incrementedCoordinates = incrementCoordinates(coordinates, direction);
   
   if (!areCoordinatesValid(incrementedCoordinates))
      return std::nullopt;

   return incrementedCoordinates;
}

auto Day4::decrementCoordinates(Coordinates coordinates, Direction direction) noexcept -> Coordinates
{
   switch (direction)
   {
   case FORWARDS:
      return incrementCoordinates(coordinates, BACKWARDS);

   case BACKWARDS:
      return incrementCoordinates(coordinates, FORWARDS);

   case UP:
      return incrementCoordinates(coordinates, DOWN);

   case DOWN:
      return incrementCoordinates(coordinates, UP);

   case PLUSPLUS:
      return incrementCoordinates(coordinates, MINUSMINUS);

   case PLUSMINUS:
      return incrementCoordinates(coordinates, MINUSPLUS);

   case MINUSMINUS:
      return incrementCoordinates(coordinates, PLUSPLUS);

   case MINUSPLUS:
      return incrementCoordinates(coordinates, PLUSMINUS);

   default:
      return Coordinates{ UPPER_BOUND,UPPER_BOUND };
   }
}

auto Day4::incrementCoordinates(Coordinates coordinates, Direction direction) noexcept -> Coordinates
{
   auto [x, y] = coordinates;
   switch (direction)
   {
   case FORWARDS:
      return Coordinates{x + 1, y };

   case BACKWARDS:
      return Coordinates{x - 1, y };

   case UP:
      return Coordinates{x, y + 1};

   case DOWN:
      return Coordinates{x, y - 1};

   case PLUSPLUS:
      return Coordinates{x + 1, y + 1};

   case PLUSMINUS:
      return Coordinates{x + 1, y - 1};

   case MINUSMINUS:
      return Coordinates{x - 1, y - 1};

   case MINUSPLUS:
      return Coordinates{x - 1, y + 1};

   default: 
      return Coordinates{ UPPER_BOUND,UPPER_BOUND };
   }
}

auto Day4::checkInDirectionsPart2(Coordinates startingCoordinates, std::pair<Direction, Direction> directions) const noexcept-> bool
{
   auto [dir1, dir2] = directions;
   return matchesInDirection(startingCoordinates, dir1) && matchesInDirection(startingCoordinates, dir2);
}

auto Day4::matchesInDirection(Coordinates coordinates, Direction direction) const noexcept -> bool
{
   auto coords = decrementCoordinates(coordinates, direction);
   if (!areCoordinatesValid(coords))
      return false;

   if (m_content.at(coords.x).at(coords.y) != 'M')
      return false;

   coords = incrementCoordinates(coordinates, direction);
   if (!areCoordinatesValid(coords))
      return false;

   return m_content.at(coords.x).at(coords.y) == 'S';
}

auto Day4::areCoordinatesValid(Coordinates coordinates) noexcept -> bool
{
   auto [x, y] = coordinates;
   if (x < 0 || x >= UPPER_BOUND)
      return false;

   if (y < 0 || y >= UPPER_BOUND)
      return false;

   return true;
}
