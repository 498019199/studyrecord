#include <math/math.h>

namespace MathWorker
{


float Distance(const  Vector2D& lhs, const Vector2D& rhs)
{
    Vector2D tmp(lhs.x - rhs.x, lhs.y - rhs.y);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
}
float Distance(const  Vector3D& lhs, const Vector3D& rhs)
{
    Vector3D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}
float Distance(const  Vector4D& lhs, const Vector4D& rhs)
{
    Vector4D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z + tmp.w * tmp.w);
}

// template float Angle(const Vector2D& lsh, const Vector2D& rhs);
// template float Angle(const Vector3D& lsh, const Vector3D& rhs);
// template float Angle(const Vector4D& lsh, const Vector4D& rhs);
template<typename T>
float Angle(const T& lsh, const T& rsh)
{
    return 0;
}

}