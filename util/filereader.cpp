#include "util/filereader.h"

using namespace advent;

auto FileReader::parse(std::string_view filename) noexcept -> std::vector<std::string>
{
   auto data = std::vector<std::string>{};
   auto ifs = std::ifstream{ filename.data() };
   auto line = std::string{};

   while (std::getline(ifs, line))
      data.push_back(line);

   return data;
}