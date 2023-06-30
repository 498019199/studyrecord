#include <cmath>

#include <math/vector2.h>

const vector2& vector2::operator+=(const  vector2& rhs) noexcept
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

const vector2& vector2::operator-=(const  vector2& rhs) noexcept
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

const vector2& vector2::operator*=(float rhs) noexcept
{
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

const vector2& vector2::operator/=(float rhs) noexcept
{
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}

const vector2& vector2::operator*=(const  vector2& rhs) noexcept
{
    this->dot(rhs);
    return *this;
}

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
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
}

const vector2& normalize(const vector2& rhs) noexcept
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y);
    return vector2(rhs.x / v , rhs.y / v);
}

// 距离
float vector2::distance(const  vector2& lhs, const vector2& rhs) noexcept
{
    return std::sqrt((rhs.x - lhs.x) * (rhs.x - lhs.x) + 
        (rhs.y - lhs.y) * (rhs.y - lhs.y));
}

float vector2::distance(const vector2& rhs) noexcept
{
    return std::sqrt((rhs.x - this->x) * (rhs.x - this->x) + 
        (rhs.y - this->y) * (rhs.y - this->y));
}

// 叉积
void vector2::cross(const vector2& rhs) noexcept
{}
void vector2::cross(const  vector2& lhs, const vector2& rhs) noexcept
{}

// 点积
float vector2::dot(const vector2& rhs) noexcept
{
    return this->x * rhs.x + this->y * rhs.y;
}

float vector2::dot(const  vector2& lhs, const vector2& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}