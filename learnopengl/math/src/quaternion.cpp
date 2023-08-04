#include <math/quaternion.h>
#include <math/math.h>

namespace MathWorker
{

Quaternion Quaternion::ZeroQuat(0.f , 0.f, 0.f, 0.f);

constexpr Quaternion::Quaternion(const float * rhs) noexcept
{
    x = rhs[0];
    y = rhs[1];
    z = rhs[2];
    w = rhs[3];
}

Quaternion::Quaternion(const Vector3D& vec, float s) noexcept
    :x(vec.x),y(vec.y),z(vec.z),w(s)
{
	
}

Quaternion::Quaternion(const Quaternion & rhs) noexcept
    :x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w)
{
    
}

Quaternion::Quaternion(Quaternion&& rhs) noexcept
    :x(std::move(rhs.x)),y(std::move(rhs.y)),z(std::move(rhs.z)),w(std::move(rhs.w))
{
    
}

constexpr Quaternion::Quaternion(float x1, float y1, float z1, float w1) noexcept
    :x(x1),y(y1),z(z1),w(w1)
{
    
}

Quaternion& Quaternion::operator=(const Quaternion & rhs) noexcept
{
	if (this != &rhs)
    {
        x = rhs.x; y = rhs.y; z = rhs.z, w = rhs.w;
    }
    return *this;
}

Quaternion& Quaternion::operator=(Quaternion&& rhs) noexcept
{
	if (this != &rhs)
    {
        x = rhs.x; y = rhs.y; z = rhs.z, w = rhs.w;
    }
    return *this;
}

const Quaternion& Quaternion::operator+=(const Quaternion & rhs) noexcept
{
	x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

const Quaternion& Quaternion::operator-=(const Quaternion & rhs) noexcept
{
	x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

const Quaternion& Quaternion::operator*=(const Quaternion & rhs) noexcept
{
	x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

const Quaternion& Quaternion::operator*=(float rhs) noexcept
{
	x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

const Quaternion& Quaternion::operator/=(float rhs) noexcept
{
	x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

const Vector3D Quaternion::GetV() const noexcept
{
	return Vector3D(this->x, this->y, this->z);
}

void Quaternion::SetV(const Vector3D& rhs) noexcept
{
	x = rhs.x; y = rhs.y; z = rhs.z;
}

bool Quaternion::operator==(const Quaternion& rhs) const noexcept
{
    return IsEqual(this->x, rhs.x) && 
                IsEqual(this->y, rhs.y) && 
                    IsEqual(this->z, rhs.z) && 
                        IsEqual(this->w, rhs.w);
}

bool Quaternion::operator!=(const Quaternion& rhs) const noexcept
{
	return !(this->operator==(rhs));
}

std::ostream& operator<<(std::ostream& os, const  Quaternion& lhs)
{
	os << lhs.x << " " << lhs.y << " " << lhs.z << " " << lhs.w;
    return os;
}

}