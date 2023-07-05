#include <cmath>
#include <cassert>

#include <math/vector3d.h>
static const vector3d zero_vector(0, 0, 0);
static const vector3d unit_vector(1, 1, 1);


vector3d& vector3d::operator=(const vector3d& rhs) 
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

float vector3d::operator[](int32_t index) const
{
    assert(index >= 0 && index < 3);
    return (&x)[index];
}

vector3d& vector3d::operator=(const vector3d&& rhs) 
{
    if (this != &rhs)
    {
        this->x = std::move(rhs.x);
        this->y = std::move(rhs.y);
        this->z = std::move(rhs.z);
    }
    return *this;
}

vector3d vector3d::operator-() const
{
    return vector3d(-x, -y, -z);
}

vector3d vector3d::operator+(const vector3d& rhs) const
{
    return vector3d(x + rhs.x, y + rhs.y, z + rhs.z);
}

vector3d vector3d::operator-(const  vector3d& rhs) const
{
    return vector3d(x - rhs.x, y - rhs.y, z - rhs.z);
}

vector3d vector3d::operator*(const  vector3d& rhs) const
{
    return vector3d(x * rhs.x, y * rhs.y, z * rhs.z);
}

vector3d vector3d::operator/(const  vector3d& rhs) const
{
    return vector3d(x / rhs.x, y / rhs.y, z / rhs.z);
}

vector3d vector3d::operator*(float rhs) const
{
    return vector3d(x * rhs, y * rhs, z * rhs);
}

vector3d vector3d::operator/(float rhs) const
{
    return vector3d(x / rhs, y / rhs, z / rhs);
}

float vector3d::operator|(const vector3d& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

vector3d vector3d::operator^(const vector3d& rhs) const
{
    return vector3d(
        (y * rhs.z - z * rhs.y),
        (z * rhs.x - x * rhs.z),
        (x * rhs.y - y * rhs.x)
    );
}

vector3d vector3d::operator+=(const  vector3d& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

vector3d vector3d::operator-=(const  vector3d& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

vector3d vector3d::operator*=(const  vector3d& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

vector3d vector3d::operator/=(const  vector3d& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

vector3d vector3d::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

vector3d vector3d::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

bool vector3d::is_zero() const
{
    return x == 0.f && y == 0.f && z == 0.f;
}

bool vector3d::operator==(const  vector3d& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

bool vector3d::operator!=(const  vector3d& rhs) const
{
    return !(this->operator==(rhs));
}

void vector3d::normalize()
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
    z = z/v;
}

vector3d normalize(const vector3d& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
    return vector3d(rhs.x / v , rhs.y / v, rhs.z / v);
}

// 距离
float vector3d::distance(const  vector3d& lhs, const vector3d& rhs)
{
    vector3d tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}

vector3d vector3d::cross(const  vector3d& lhs, const vector3d& rhs)
{
    return lhs.operator^(rhs);
}

float vector3d::dot(const  vector3d& lhs, const vector3d& rhs)
{
    return lhs.operator|(rhs);
}