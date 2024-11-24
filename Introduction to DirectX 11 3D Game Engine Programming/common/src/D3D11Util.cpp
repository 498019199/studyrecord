#include <common/D3D11Util.h>

#include <format>
#include <utility>
std::string CombineFileLine(std::string_view file, uint32_t line)
{
    return std::format("{}: {}", std::move(file), line);
}