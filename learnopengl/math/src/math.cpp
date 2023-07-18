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

// template float Angle(const Vector2D& lsh, const Vector2D& rhs);
// template float Angle(const Vector3D& lsh, const Vector3D& rhs);
// template float Angle(const Vector4D& lsh, const Vector4D& rhs);
template<typename T>
float Angle(const T& lsh, const T& rsh)
{
    // float xn = ;
    // return Rad2Deg(
    //         std::acos(
    //             T::Dot(lsh, rhs) /
    //             ));
    return 0;
}

}