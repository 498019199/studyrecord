#include <cmath>
#include <cassert>

#include <math/vector4d.h>
#include <math/math.h>
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
    return IsEqual(this->x, rhs.x) && 
                IsEqual(this->y, rhs.y) && 
                    IsEqual(this->z, rhs.z) && 
                        IsEqual(this->w, rhs.w);
}

bool Vector4D::operator!=(const  Vector4D& rhs) const
{
    return !(this->operator==(rhs));
}

void Vector4D::Normalize()
{
    static float v = std::sqrt(x*x + y*y);
    x = x/v;
    y = y/v;
    z = z/v;
    w = w/v;
}

float Vector4D::Norm(const Vector4D& lhs)
{
    return std::sqrt(lhs.x * lhs.x + 
        lhs.y * lhs.y + 
        lhs.z * lhs.z + 
        lhs.w * lhs.w);
}

Vector4D Normalize(const Vector4D& rhs)
{
    static float SquareSum = (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
    static float Scale = InvSqrt(SquareSum);

    return Vector4D(rhs.x * Scale , rhs.y * Scale, rhs.z * Scale, rhs.w * Scale);
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

float Distance(const  Vector4D& lhs, const Vector4D& rhs)
{
    Vector4D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z + tmp.w * tmp.w);
}

Vector4D Min(const Vector4D& lhs, const Vector4D& rhs)
{
    return Vector4D(
        std::min<float>(lhs.x, rhs.x),
        std::min<float>(lhs.y, rhs.y),
        std::min<float>(lhs.z, rhs.z),
        std::min<float>(lhs.w, rhs.w)
    );
}

Vector4D  Max(const Vector4D& lhs, const Vector4D& rhs)
{
    return Vector4D(
        std::max<float>(lhs.x, rhs.x),
        std::max<float>(lhs.y, rhs.y),
        std::max<float>(lhs.z, rhs.z),
        std::max<float>(lhs.w, rhs.w)
    );
}
}