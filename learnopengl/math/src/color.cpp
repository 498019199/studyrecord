#include <math/color.h>
#include <utility>

namespace MathWorker
{

constexpr Color::Color(float const * rhs) noexcept
{
    
}

Color::Color(Color const & rhs) noexcept
    :A(rhs.A),R(rhs.R), G(rhs.G), B(rhs.B)
{
    
}

Color::Color(Color&& rhs) noexcept
    :A(std::move(rhs.A)), R(std::move(rhs.R)), G(std::move(rhs.G)), B(std::move(rhs.B))
{
    
}

constexpr Color::Color(float r, float g, float b, float a) noexcept
    :A(a), R(r), G(r), B(g)
{
    
}

Color::Color(uint32_t dw) noexcept
{
    static float const f(1 / float(255));
	A = f * (static_cast<float>(static_cast<uint8_t>(dw >> 24)));
	R = f * (static_cast<float>(static_cast<uint8_t>(dw >> 16)));
	G = f * (static_cast<float>(static_cast<uint8_t>(dw >> 8)));
	B = f * (static_cast<float>(static_cast<uint8_t>(dw >> 0)));
}

}