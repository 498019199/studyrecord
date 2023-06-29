#include <math/vector4.h>

const vector4& operator+=(const  vector4& rhs) noexcept
{}

const vector4& operator-=(const  vector4& rhs) noexcept
{}

const vector4& operator*=(const  vector4& rhs) noexcept
{}

const vector4& operator/=(const  vector4& rhs) noexcept
{}

bool vector4::operator==(const  vector4& rhs) const noexcept
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool vector4::operator!=(const  vector4& rhs) const noexcept
{
    return !(this->operator==(rhs));
}

// 向量标准化
void vector4::normalize() noexcept
{
    
}

vector4 vector4::normalize() const noexcept
{}

// 距离
float vector4::distance(const  vector4& lhs, const vector4& rhs) noexcept
{}

float vector4::distance(const vector4& rhs) noexcept
{}

// 叉积
void vector4::cross(const vector4& rhs) noexcept
{}
void vector4::cross(const  vector4& lhs, const vector4& rhs) noexcept
{}

// 点积
float vector4::dot(const vector4& rhs) noexcept
{}

float vector4::dot(const  vector4& lhs, const vector4& rhs) noexcept
{}