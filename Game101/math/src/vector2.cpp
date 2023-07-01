#include <cmath>

#include <math/vector2d.h>
static const vector2d zero_vector;
static const vector2d unit_vector;

vector2d vector2d::operator+(const vector2d& rhs) const noexcept
{
    return vector2d(x + rhs.x, y + rhs.y);
}

vector2d vector2d::operator-(const  vector2d& rhs) const noexcept
{
    return vector2d(x - rhs.x, y - rhs.y);
}

vector2d vector2d::operator*(float rhs) const noexcept
{
    return vector2d(x * rhs, y * rhs);
}

vector2d vector2d::operator/(float rhs) const noexcept
{
    return vector2d(x / rhs, y / rhs);
}

bool vector2d::operator==(const  vector2d& rhs) const noexcept
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool vector2d::operator!=(const  vector2d& rhs) const noexcept
{
    return !(this->operator==(rhs));
}

// 向量标准化
void vector2d::normalize() noexcept
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
}

 vector2d normalize(const vector2d& rhs) noexcept
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y);
    return vector2d(rhs.x / v , rhs.y / v);
}

// 距离
float vector2d::distance(const  vector2d& lhs, const vector2d& rhs) noexcept
{
    return std::sqrt((rhs.x - lhs.x) * (rhs.x - lhs.x) + 
        (rhs.y - lhs.y) * (rhs.y - lhs.y));
}

float vector2d::distance(const vector2d& rhs) noexcept
{
    return std::sqrt((rhs.x - this->x) * (rhs.x - this->x) + 
        (rhs.y - this->y) * (rhs.y - this->y));
}

// 叉积
void vector2d::cross(const vector2d& rhs) noexcept
{}
void vector2d::cross(const  vector2d& lhs, const vector2d& rhs) noexcept
{}

// 点积
float vector2d::dot(const vector2d& rhs) noexcept
{
    return this->x * rhs.x + this->y * rhs.y;
}

float vector2d::dot(const  vector2d& lhs, const vector2d& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}