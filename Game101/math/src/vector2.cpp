#include <cmath>
#include <cassert>

#include <math/vector2d.h>
static const vector2d zero_vector(0,0);
static const vector2d unit_vector(1,1);

// vector2d::vector2d(std::initializer_list<float> list)
// {
//     auto it = list.begin();
//     for (size_t i = 0; i < 2; i++)
//     {
//         it += i;
//         (&x)[i] = *it;
//     }
// }

vector2d& vector2d::operator=(const vector2d& rhs) 
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
    }
    return *this;
}

float vector2d::operator[](int32_t index) const
{
    assert(index >= 0 && index < 2);
    return (&x)[index];
}

vector2d& vector2d::operator=(const vector2d&& rhs) 
{
    if (this != &rhs)
    {
        this->x = std::move(rhs.x);
        this->y = std::move(rhs.y);
    }
    return *this;
}

vector2d vector2d::operator-() const
{
    return vector2d(-x, -y);
}

vector2d vector2d::operator+(const vector2d& rhs) const
{
    return vector2d(x + rhs.x, y + rhs.y);
}

vector2d vector2d::operator-(const  vector2d& rhs) const
{
    return vector2d(x - rhs.x, y - rhs.y);
}

vector2d vector2d::operator*(float rhs) const
{
    return vector2d(x * rhs, y * rhs);
}

vector2d vector2d::operator*(const  vector2d& rhs) const
{
    return vector2d(x * rhs.x, y * rhs.y);
}

vector2d vector2d::operator/(const  vector2d& rhs) const
{
    return vector2d(x / rhs.x, y / rhs.y);
}

vector2d vector2d::operator/(float rhs) const
{
    return vector2d(x / rhs, y / rhs);
}

float vector2d::operator|(const vector2d& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

float vector2d::operator^(const vector2d& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

vector2d vector2d::operator+=(const  vector2d& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

vector2d vector2d::operator-=(const  vector2d& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

vector2d vector2d::operator*=(const  vector2d& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

vector2d vector2d::operator/=(const  vector2d& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

vector2d vector2d::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    return *this;
}

vector2d vector2d::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    return *this;
}

bool vector2d::is_zero() const
{
    return x == 0.f && y == 0.f;
}

bool vector2d::operator==(const  vector2d& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool vector2d::operator!=(const  vector2d& rhs) const
{
    return !(this->operator==(rhs));
}

void vector2d::normalize()
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
}

vector2d normalize(const vector2d& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y);
    return vector2d(rhs.x / v , rhs.y / v);
}

// 距离
float vector2d::distance(const  vector2d& lhs, const vector2d& rhs)
{
    return std::sqrt((rhs.x - lhs.x) * (rhs.x - lhs.x) + 
        (rhs.y - lhs.y) * (rhs.y - lhs.y));
}

float vector2d::cross(const  vector2d& lhs, const vector2d& rhs)
{
    return lhs.operator^(rhs);
}

float vector2d::dot(const  vector2d& lhs, const vector2d& rhs)
{
    return lhs.operator|(rhs);
}