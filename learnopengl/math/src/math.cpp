#include <math/math.h>

namespace MathWorker
{
template bool IsEqual(float X, float Y);
template bool IsEqual(double X, double Y);
template<typename T>
bool IsEqual(T X, T Y)
{
    return std::abs(X - Y) < std::numeric_limits<T>::epsilon();
}

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

Matrix MatrixMove(float X, float Y, float Z)
{
    return Matrix(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        X, Y, Z, 1);
}

Matrix MatrixScale(float X, float Y, float Z)
{
    return Matrix(
        X, 0, 0, 0,
        0, Y, 0, 0,
        0, 0, Z, 0,
        1, 1, 1, 1 );
}

Matrix MatrixRotateX(float X)
{
    float sf, cf;
    SinCos(X, sf, cf);
    return Matrix(
        1,  0,   0,   0,
        0,  cf,  sf,  0,
        0,  -sf, cf,  0,
        1,  1,   1,   1);
}

Matrix MatrixRotateY(float Y)
{
    float sf, cf;
    SinCos(Y, sf, cf);    
    return Matrix(
        cf,  0,  -sf,  0,
        0,   1,  0,    0,
        sf,  0,  cf,   0,
        1,   1,  1,    1);
}

Matrix MatrixRotateZ(float Z)
{
    float sf, cf;
    SinCos(Z, sf, cf);   
    return Matrix(
        cf,  sf,  0,  0,
        -sf, cf,  0,  0,
        0,   0,   1,  0,
        1,   1,   1,  1);
}

Matrix Mul(const Matrix&lhs, const Matrix& rhs)
{
    return Matrix(
        lhs._11 * rhs._11 + lhs._12 * rhs._21 + lhs._13 * rhs._31 + lhs._14 * rhs._41,
        lhs._11 * rhs._12 + lhs._12 * rhs._22 + lhs._13 * rhs._32 + lhs._14 * rhs._42,
        lhs._11 * rhs._13 + lhs._12 * rhs._23 + lhs._13 * rhs._33 + lhs._14 * rhs._43,
        lhs._11 * rhs._14 + lhs._12 * rhs._24 + lhs._13 * rhs._34 + lhs._14 * rhs._44,
        lhs._21 * rhs._11 + lhs._22 * rhs._21 + lhs._23 * rhs._31 + lhs._24 * rhs._41,
        lhs._21 * rhs._12 + lhs._22 * rhs._22 + lhs._23 * rhs._32 + lhs._24 * rhs._42,
        lhs._21 * rhs._13 + lhs._22 * rhs._23 + lhs._23 * rhs._33 + lhs._24 * rhs._43,
        lhs._21 * rhs._14 + lhs._22 * rhs._24 + lhs._23 * rhs._34 + lhs._24 * rhs._44,
        lhs._31 * rhs._11 + lhs._32 * rhs._21 + lhs._33 * rhs._31 + lhs._34 * rhs._41,
        lhs._31 * rhs._12 + lhs._32 * rhs._22 + lhs._33 * rhs._32 + lhs._34 * rhs._42,
        lhs._31 * rhs._13 + lhs._32 * rhs._23 + lhs._33 * rhs._33 + lhs._34 * rhs._43,
        lhs._31 * rhs._14 + lhs._32 * rhs._24 + lhs._33 * rhs._34 + lhs._34 * rhs._44,
        lhs._41 * rhs._11 + lhs._42 * rhs._21 + lhs._43 * rhs._31 + lhs._44 * rhs._41,
        lhs._41 * rhs._12 + lhs._42 * rhs._22 + lhs._43 * rhs._32 + lhs._44 * rhs._42,
        lhs._41 * rhs._13 + lhs._42 * rhs._23 + lhs._43 * rhs._33 + lhs._44 * rhs._43,
        lhs._41 * rhs._14 + lhs._42 * rhs._24 + lhs._43 * rhs._34 + lhs._44 * rhs._44);
}

// 1*4 mul 4*4
Vector4D Mul(const Vector4D&lhs, const Matrix& rhs)
{
    return Vector4D(
        lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31 + lhs.w * rhs._41,
        lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32 + lhs.w * rhs._42,
        lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33 + lhs.w * rhs._34,
        lhs.x * rhs._14 + lhs.y * rhs._24 + lhs.z * rhs._34 + lhs.w * rhs._44);
}

Matrix Transpose(const Matrix& m)
{  
    return Matrix(
        m._11, m._21, m._31, m._41, 
        m._12, m._22, m._32, m._42,
        m._13, m._23, m._33, m._43,
        m._14, m._24, m._34, m._44);
}

}