#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>

namespace MathWorker
{
    // 距离
    float Distance(const  Vector2D& lhs, const Vector2D& rhs);
    float Distance(const  Vector3D& lhs, const Vector3D& rhs);
    float Distance(const  Vector4D& lhs, const Vector4D& rhs);

    // 返回 from 与 to 之间的角度
    template<typename T>
    float Angle(const T& from, const T& to);
    // 	在两个点之间进行线性插值。
    template<typename T>
    T Lerp(const T& lhs, const T& rhs);
    // 返回由两个向量的最大分量组成的向量。
    template<typename T>
    T Min(const T& lhs, const T& rhs);
    // 返回由两个向量的最小分量组成的向量。
    template<typename T>
    T Max(const T& lhs, const T& rhs);
}