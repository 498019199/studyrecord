#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>

namespace MathWorker
{
    // 距离
    static float distance(const  Vector2D& lhs, const Vector2D& rhs)
    {
        Vector2D tmp(lhs.x - rhs.x, lhs.y - rhs.y);
        return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
    }
    static float distance(const  Vector3D& lhs, const Vector3D& rhs)
    {
        Vector3D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
    }
    static float distance(const  Vector4D& lhs, const Vector4D& rhs)
    {
        Vector4D tmp(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z + tmp.w * tmp.w);
    }
}