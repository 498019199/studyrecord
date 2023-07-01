#include <cmath>
#include <cassert>

#include <math/vector4d.h>
static const vector4d zero_vector(0, 0, 0, 0);
static const vector4d unit_vector(1, 1, 1, 1);


vector4d& vector4d::operator=(const vector4d& rhs) 
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
        this->w = rhs.w;
    }
    return *this;
}

float vector4d::operator[](int32_t index) const
{
    assert(index >= 0 && index < 4);
    return (&x)[index];
}

vector4d& vector4d::operator=(const vector4d&& rhs) 
{
    if (this != &rhs)
    {
        this->x = std::move(rhs.x);
        this->y = std::move(rhs.y);
        this->z = std::move(rhs.z);
        this->w = std::move(rhs.w);
    }
    return *this;
}

vector4d vector4d::operator-() const
{
    return vector4d(-x, -y, -z, -w);
}

vector4d vector4d::operator+(const vector4d& rhs) const
{
    return vector4d(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

vector4d vector4d::operator-(const  vector4d& rhs) const
{
    return vector4d(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

vector4d vector4d::operator*(const  vector4d& rhs) const
{
    return vector4d(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

vector4d vector4d::operator/(const  vector4d& rhs) const
{
    return vector4d(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

vector4d vector4d::operator*(float rhs) const
{
    return vector4d(x * rhs, y * rhs, z * rhs, w * rhs);
}

vector4d vector4d::operator/(float rhs) const
{
    return vector4d(x / rhs, y / rhs, z / rhs, z / rhs);
}

float vector4d::operator|(const vector4d& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

vector4d vector4d::operator^(const vector4d& rhs) const
{
	return vector4d(
        (y * rhs.z - z * rhs.y),
		(z * rhs.x - x * rhs.z),
		(x * rhs.y - y * rhs.x),
		1
        );
}

vector4d vector4d::operator+=(const  vector4d& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

vector4d vector4d::operator-=(const  vector4d& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    z -= rhs.w;
    return *this;
}

vector4d vector4d::operator*=(const  vector4d& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

vector4d vector4d::operator/=(const  vector4d& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

vector4d vector4d::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

vector4d vector4d::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

bool vector4d::is_zero() const
{
    return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
}

bool vector4d::operator==(const  vector4d& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y && 
        this->z == rhs.z && this->w == rhs.w;
}

bool vector4d::operator!=(const  vector4d& rhs) const
{
    return !(this->operator==(rhs));
}

void vector4d::normalize()
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
    z = z/v;
    w = w/v;
}

vector4d normalize(const vector4d& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
    return vector4d(rhs.x / v , rhs.y / v, rhs.z / v, rhs.w / v);
}

// 距离
float vector4d::distance(const  vector4d& lhs, const vector4d& rhs)
{
    vector4d tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z + tmp.w * tmp.w);
}

vector4d vector4d::cross(const  vector4d& lhs, const vector4d& rhs)
{
    return lhs.operator^(rhs);
}

float vector4d::dot(const  vector4d& lhs, const vector4d& rhs)
{
    return lhs.operator|(rhs);
}