#pragma once
#include <cstdint>
namespace MathWorker
{

struct Color
{
public:
    float A;
    float R;
    float G;
    float B;
public:
	Color() noexcept
	{}
	explicit constexpr Color(float const * rhs) noexcept;
	Color(Color const & rhs) noexcept;
	Color(Color&& rhs) noexcept;
	constexpr Color(float a, float r, float g, float b) noexcept;
	explicit Color(uint32_t dw) noexcept;
};


}