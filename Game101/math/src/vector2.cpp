#include <math/vector2.h>

const vector2& operator+=(const  vector2& rhs) noexcept
{}

const vector2& operator-=(const  vector2& rhs) noexcept
{}

const vector2& operator*=(const  vector2& rhs) noexcept
{}

const vector2& operator/=(const  vector2& rhs) noexcept
{}

bool vector2::operator==(const  vector2& rhs) const noexcept
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool vector2::operator!=(const  vector2& rhs) const noexcept
{
    return !(this->operator==(rhs));
}

// 向量标准化
void vector2::normalize() noexcept
{}

vector2 vector2::normalize() const noexcept
{}

// 距离
float vector2::distance(const  vector2& lhs, const vector2& rhs) noexcept
{}

float vector2::distance(const vector2& rhs) noexcept
{}

// 叉积
void vector2::cross(const vector2& rhs) noexcept
{}
void vector2::cross(const  vector2& lhs, const vector2& rhs) noexcept
{}

// 点积
float vector2::dot(const vector2& rhs) noexcept
{}

float vector2::dot(const  vector2& lhs, const vector2& rhs) noexcept
{}