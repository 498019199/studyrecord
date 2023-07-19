#include <math/math.h>

namespace MathWorker
{
float InvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x; // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = *(float*)&i; // convert bits BACK to float
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    return x;
}

template Vector2D Lerp(const Vector2D& lsh, const Vector2D& rhs, float s);
template Vector3D Lerp(const Vector3D& lsh, const Vector3D& rhs, float s);
template Vector4D Lerp(const Vector4D& lsh, const Vector4D& rhs, float s);
template<typename T>
T Lerp(const T& lhs, const T& rhs, float s)
{
    return (lhs + (rhs - lhs) * s);
}

template float Angle(const Vector2D& lsh, const Vector2D& rhs);
template float Angle(const Vector3D& lsh, const Vector3D& rhs);
template float Angle(const Vector4D& lsh, const Vector4D& rhs);
template<typename T>
float Angle(const T& lsh, const T& rsh)
{
    float xn = T::Norm(lsh);
    float yn = T::Norm(rsh);
    float xyn = xn * yn;
    float angle = std::acos((lsh | rsh) / xyn);
    return Rad2Deg(angle);
}

}