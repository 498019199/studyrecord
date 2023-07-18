#include <cmath>
#include <cassert>

#include <math/vector4d.h>
namespace MathWorker
{

static const Vector4D zero_vector(0, 0, 0, 0);
static const Vector4D unit_vector(1, 1, 1, 1);


Vector4D& Vector4D::operator=(const Vector4D& rhs) 
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

float Vector4D::operator[](int32_t index) const
{
    assert(index >= 0 && index < 4);
    return (&x)[index];
}

Vector4D& Vector4D::operator=(const Vector4D&& rhs) 
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

Vector4D Vector4D::operator-() const
{
    return Vector4D(-x, -y, -z, -w);
}

Vector4D Vector4D::operator+(const Vector4D& rhs) const
{
    return Vector4D(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4D Vector4D::operator-(const  Vector4D& rhs) const
{
    return Vector4D(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4D Vector4D::operator*(const  Vector4D& rhs) const
{
    return Vector4D(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

Vector4D Vector4D::operator/(const  Vector4D& rhs) const
{
    return Vector4D(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

Vector4D Vector4D::operator*(float rhs) const
{
    return Vector4D(x * rhs, y * rhs, z * rhs, w * rhs);
}

Vector4D Vector4D::operator/(float rhs) const
{
    return Vector4D(x / rhs, y / rhs, z / rhs, z / rhs);
}

float Vector4D::operator|(const Vector4D& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

Vector4D Vector4D::operator^(const Vector4D& rhs) const
{
	return Vector4D(
        (y * rhs.z - z * rhs.y),
		(z * rhs.x - x * rhs.z),
		(x * rhs.y - y * rhs.x),
		1
        );
}

Vector4D Vector4D::operator+=(const  Vector4D& rhs) 
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

Vector4D Vector4D::operator-=(const  Vector4D& rhs) 
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    z -= rhs.w;
    return *this;
}

Vector4D Vector4D::operator*=(const  Vector4D& rhs) 
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

Vector4D Vector4D::operator/=(const  Vector4D& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

Vector4D Vector4D::operator*=(float rhs) 
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

Vector4D Vector4D::operator/=(float rhs) 
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const  Vector4D& lhs)
{
    os << lhs.x << " " << lhs.y << " " << lhs.z << " " << lhs.w;
    return os;
}

bool Vector4D::IsZero() const
{
    return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
}

bool Vector4D::operator==(const  Vector4D& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y && 
        this->z == rhs.z && this->w == rhs.w;
}

bool Vector4D::operator!=(const  Vector4D& rhs) const
{
    return !(this->operator==(rhs));
}

void Vector4D::Normalize()
{
    float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
    z = z/v;
    w = w/v;
}

Vector4D Normalize(const Vector4D& rhs)
{
    float v = std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
    return Vector4D(rhs.x / v , rhs.y / v, rhs.z / v, rhs.w / v);
}

Vector4D Vector4D::Cross(const Vector4D& rhs)
{
    return this->operator^(rhs);
}

Vector4D Vector4D::Cross(const  Vector4D& lhs, const Vector4D& rhs)
{
    return lhs.operator^(rhs);
}

float Vector4D::Dot(const Vector4D& rhs)
{
    return this->operator|(rhs);
}

float Vector4D::Dot(const  Vector4D& lhs, const Vector4D& rhs)
{
    return lhs.operator|(rhs);
}
}