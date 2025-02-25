#include <core/ErrorHandling.h>
#include <format>

std::string CombineFileLine(std::string_view file, uint32_t line)
{
	return std::format("{}: {}", std::move(file), line);
}