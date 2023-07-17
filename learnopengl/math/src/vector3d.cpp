#include <cmath>
#include <cassert>

#include <math/vector3d.h>
namespace MathWorker
{
static const Vector3D zero_vector(0, 0, 0);
static const Vector3D unit_vector(1, 1, 1);


Vector3D& Vector3D::operator=(const Vector3D& rhs) 
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

float Vector3D::operator[](int32_t index) const
{
    assert(index >= 0 && index < 3);
    return (&x)[index];
}

Vector3D& Vector3D::operator=(const Vector3D&& rhs) 
{
    if (this != &rhs)
    {
        this->x = std::move(rhs.x);
        this->y = std::move(rhs.y);
        this->z = std::move(rhs.z);
    }
    return *this;
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
    return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3D Vector3D::operator-(const  Vector3D& rhs) const
{
    return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3D Vector3D::operator*(const  Vector3D& rhs) const
{
    return Vector3D(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector3D Vector3D::operator/(const  Vector3D& rhs) const
{
    return Vector3D(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vector3D Vector3D::operator*(float rhs) const
{
    return Vector3D(x * rhs, y * rhs, z * rhs);
}

Vector3D Vector3D::operator/(float rhs) const
{
    return Vector3D(x / rhs, y / rhs, z / rhs);
}

float Vector3D::operator|(const Vector3D& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3D Vector3D::operator^(const Vector3D& rhs) const
{
    return Vector3D(
        (y * rhs.z - z * rhs.y),
        (z * rhs.x - x * rhs.z),
        (x * rhs.y - y * rhs.x)
    );
}

Vector3D Vector3D::operator+=(const  Vector3D& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3D Vector3D::operator-=(const  Vector3D& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3D Vector3D::operator*=(const  Vector3D& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3D Vector3D::operator/=(const  Vector3D& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

Vector3D Vector3D::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3D Vector3D::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const  Vector3D& lhs) 
{
    os << lhs.x << " " << lhs.y << " " << lhs.z;
    return os;
}

bool Vector3D::is_zero() const
{
    return x == 0.f && y == 0.f && z == 0.f;
}

bool Vector3D::operator==(const  Vector3D& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

bool Vector3D::operator!=(const  Vector3D& rhs) const
{
    return !(this->operator==(rhs));
}

Vector3D Vector3D::normalize()
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
    z = z/v;
    return *this;
}

Vector3D normalize(const Vector3D& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
    return Vector3D(rhs.x / v , rhs.y / v, rhs.z / v);
}

// 距离
float Vector3D::distance(const  Vector3D& lhs, const Vector3D& rhs)
{
    Vector3D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}

Vector3D Vector3D::cross(const Vector3D& rhs)
{
    return this->operator^(rhs);
}

Vector3D Vector3D::cross(const  Vector3D& lhs, const Vector3D& rhs)
{
    return lhs.operator^(rhs);
}

float Vector3D::dot(const Vector3D& rhs)
{
    return this->operator|(rhs);
}

float Vector3D::dot(const  Vector3D& lhs, const Vector3D& rhs)
{
    return lhs.operator|(rhs);
}
}