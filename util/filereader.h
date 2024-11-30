#pragma once
#include <string_view>
#include <vector>
#include <string>
#include <fstream>

namespace advent
{
   class FileReader
   {
   public:
      explicit FileReader() = delete;
      ~FileReader() = delete;

      [[nodiscard]] static auto parse(std::string_view filename) noexcept -> std::vector<std::string>;
   };
}