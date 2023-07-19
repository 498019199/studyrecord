#include <cmath>
#include <cassert>

#include <math/vector2d.h>
#include <math/math.h>
namespace MathWorker
{
static const Vector2D Zero(0,0);

// Vector2D::Vector2D(std::initializer_list<float> list)
// {
//     auto it = list.begin();
//     for (size_t i = 0; i < 2; i++)
//     {
//         it += i;
//         (&x)[i] = *it;
//     }
// }

Vector2D& Vector2D::operator=(const Vector2D& rhs) 
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
    }
    return *this;
}

float Vector2D::operator[](int32_t index) const
{
    assert(index >= 0 && index < 2);
    return (&x)[index];
}

Vector2D& Vector2D::operator=(const Vector2D&& rhs) 
{
    if (this != &rhs)
    {
        this->x = std::move(rhs.x);
        this->y = std::move(rhs.y);
    }
    return *this;
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
    return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const  Vector2D& rhs) const
{
    return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator*(float rhs) const
{
    return Vector2D(x * rhs, y * rhs);
}

Vector2D Vector2D::operator*(const  Vector2D& rhs) const
{
    return Vector2D(x * rhs.x, y * rhs.y);
}

Vector2D Vector2D::operator/(const  Vector2D& rhs) const
{
    return Vector2D(x / rhs.x, y / rhs.y);
}

Vector2D Vector2D::operator/(float rhs) const
{
    return Vector2D(x / rhs, y / rhs);
}

float Vector2D::operator|(const Vector2D& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

float Vector2D::operator^(const Vector2D& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

Vector2D Vector2D::operator+=(const  Vector2D& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2D Vector2D::operator-=(const  Vector2D& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2D Vector2D::operator*=(const  Vector2D& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

Vector2D Vector2D::operator/=(const  Vector2D& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

Vector2D Vector2D::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    return *this;
}

Vector2D Vector2D::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const  Vector2D& lhs) 
{
    os << lhs.x << " " << lhs.y;
    return os;
}

bool Vector2D::IsZero() const
{
    return x == 0.f && y == 0.f;
}

bool Vector2D::operator==(const  Vector2D& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool Vector2D::operator!=(const  Vector2D& rhs) const
{
    return !(this->operator==(rhs));
}

float Vector2D::Norm(const Vector2D& lhs)
{
    return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
}

void Vector2D::Normalize()
{
    static float Scale = InvSqrt(x*x + y*y);
    x = x * Scale;
    y = y * Scale;
}

Vector2D Normalize(const Vector2D& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y);
    return Vector2D(rhs.x / v , rhs.y / v);
}

float Vector2D::Cross(const Vector2D& rhs)
{
    return this->operator^(rhs);
}

float Vector2D::Cross(const  Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.operator^(rhs);
}

float Vector2D::Dot(const Vector2D& rhs)
{
    return this->operator|(rhs);
}

float Vector2D::Dot(const  Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.operator|(rhs);
}

float Vector2D::Distance(const  Vector2D& lhs, const Vector2D& rhs)
{
    Vector2D tmp(lhs.x - rhs.x, lhs.y - rhs.y);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
}

Vector2D Min(const Vector2D& lhs, const Vector2D& rhs)
{
    return Vector2D(
        std::min<float>(lhs.x, rhs.x),
        std::min<float>(lhs.y, rhs.y)
    );
}

Vector2D  Max(const Vector2D& lhs, const Vector2D& rhs)
{
    return Vector2D(
        std::max<float>(lhs.x, rhs.x),
        std::max<float>(lhs.y, rhs.y)
    );
}



}