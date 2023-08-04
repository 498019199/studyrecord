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

// From Quake III. But the magic number is from http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
float RecipSqrt(float number) noexcept
{
    float const threehalfs = 1.5f;

    float x2 = number * 0.5f;
    union FNI
    {
        float f;
        int32_t i;
    } fni;
    fni.f = number;													// evil floating point bit level hacking
    fni.i = 0x5f375a86 - (fni.i >> 1);						// what the fuck?
    fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f));		// 1st iteration
    fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f));		// 2nd iteration, this can be removed

    return fni.f;
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

Matrix MatrixMove(const Vector4D& Move)
{
    return MatrixMove(Move.x, Move.y, Move.z);
}

Matrix MatrixScale(float X, float Y, float Z)
{
    return Matrix(
        X, 0, 0, 0,
        0, Y, 0, 0,
        0, 0, Z, 0,
        1, 1, 1, 1 );
}

Matrix MatrixScale(const Vector4D& Scale)
{
    return MatrixScale(Scale.x, Scale.y, Scale.z);
}

Matrix MatrixRotateX(float Angle)
{
    float fs, fc;
    SinCos(Angle, fs, fc);
    return Matrix(
        1,  0,   0,   0,
        0,  fc,  fs,  0,
        0,  -fs, fc,  0,
        1,  1,   1,   1);
}

Matrix MatrixRotateY(float Angle)
{
    float fs, fc;
    SinCos(Angle, fs, fc);    
    return Matrix(
        fc,  0,  -fs,  0,
        0,   1,  0,    0,
        fs,  0,  fc,   0,
        1,   1,  1,    1);
}

Matrix MatrixRotateZ(float Angle)
{
    float fs, fc;
    SinCos(Angle, fs, fc);   
    return Matrix(
        fc,  fs,  0,  0,
        -fs, fc,  0,  0,
        0,   0,   1,  0,
        1,   1,   1,  1);
}

Matrix MatrixRotate(const Vector4D& n, float Angle)
{
    float fs = 0.0f, fc = 0.0f;
	SinCos(Angle, fs, fc);
	Vector4D v(n.x, n.y, n.z, 1.0f);
	v.Normalize();
		
	float a = 1.0f - fc;
	float ax = a * v.x;
	float ay = a * v.y;
	float az = a * v.z;

	Matrix m;
	m._11 = v.x * ax + fc;
	m._12 = v.x * ay + v.z * fs;
	m._13 = v.x * az - v.y * fs;
	m._21 = v.x * ay - v.z * fs;
	m._22 = v.y * ay + fc;
	m._23 = v.y * az + v.x * fs;
	m._31 = v.x * az + v.y *fs;
	m._32 = v.y * az - v.x * fs;
	m._33= v.z * az + fc;
    return m;
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

Matrix Transpose(const Matrix& mat)
{  
    return Matrix(
        mat._11, mat._21, mat._31, mat._41, 
        mat._12, mat._22, mat._32, mat._42,
        mat._13, mat._23, mat._33, mat._43,
        mat._14, mat._24, mat._34, mat._44);
}

// 矩阵的行列式
float Determinant(const Matrix& mat)
{
    const float  _3142_3241(mat(2, 0) * mat(3, 1) - mat(2, 1) * mat(3, 0));
	const float  _3143_3341(mat(2, 0) * mat(3, 2) - mat(2, 2) * mat(3, 0));
	const float  _3144_3441(mat(2, 0) * mat(3, 3) - mat(2, 3) * mat(3, 0));
	const float  _3243_3342(mat(2, 1) * mat(3, 2) - mat(2, 2) * mat(3, 1));
	const float  _3244_3442(mat(2, 1) * mat(3, 3) - mat(2, 3) * mat(3, 1));
	const float  _3344_3443(mat(2, 2) * mat(3, 3) - mat(2, 3) * mat(3, 2));

    return mat(0, 0) * (mat(1, 1) * _3344_3443 - mat(1, 2) * _3244_3442 + mat(1, 3) * _3243_3342)
        - mat(0, 1) * (mat(1, 0) * _3344_3443 - mat(1, 2) * _3144_3441 + mat(1, 3) * _3143_3341)
        + mat(0, 2) * (mat(1, 0) * _3244_3442 - mat(1, 1) * _3144_3441 + mat(1, 3) * _3142_3241)
        - mat(0, 3) * (mat(1, 0) * _3243_3342 - mat(1, 1) * _3143_3341 + mat(1, 2) * _3142_3241);
}

// 矩阵的逆
Matrix MatrixInverse(const Matrix& mat)
{
    const float  _2132_2231(mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));
    const float  _2133_2331(mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0));
    const float  _2134_2431(mat(1, 0) * mat(2, 3) - mat(1, 3) * mat(2, 0));
    const float  _2142_2241(mat(1, 0) * mat(3, 1) - mat(1, 1) * mat(3, 0));
    const float  _2143_2341(mat(1, 0) * mat(3, 2) - mat(1, 2) * mat(3, 0));
    const float  _2144_2441(mat(1, 0) * mat(3, 3) - mat(1, 3) * mat(3, 0));
    const float  _2233_2332(mat(1, 1) * mat(2, 2) - mat(1, 2) * mat(2, 1));
    const float  _2234_2432(mat(1, 1) * mat(2, 3) - mat(1, 3) * mat(2, 1));
    const float  _2243_2342(mat(1, 1) * mat(3, 2) - mat(1, 2) * mat(3, 1));
    const float  _2244_2442(mat(1, 1) * mat(3, 3) - mat(1, 3) * mat(3, 1));
    const float  _2334_2433(mat(1, 2) * mat(2, 3) - mat(1, 3) * mat(2, 2));
    const float  _2344_2443(mat(1, 2) * mat(3, 3) - mat(1, 3) * mat(3, 2));
    const float  _3142_3241(mat(2, 0) * mat(3, 1) - mat(2, 1) * mat(3, 0));
    const float  _3143_3341(mat(2, 0) * mat(3, 2) - mat(2, 2) * mat(3, 0));
    const float  _3144_3441(mat(2, 0) * mat(3, 3) - mat(2, 3) * mat(3, 0));
    const float  _3243_3342(mat(2, 1) * mat(3, 2) - mat(2, 2) * mat(3, 1));
    const float  _3244_3442(mat(2, 1) * mat(3, 3) - mat(2, 3) * mat(3, 1));
    const float  _3344_3443(mat(2, 2) * mat(3, 3) - mat(2, 3) * mat(3, 2));
    
    // 行列式的值
    const float  det(Determinant(mat));
    if (IsEqual<float>(det, 0))
    {
        return mat;
    }
    else
    {
        // 标准伴随矩阵的转置 / 行列式的值
        float invDet(float(1) / det);
        return Matrix(
            +invDet * (mat(1, 1) * _3344_3443 - mat(1, 2) * _3244_3442 + mat(1, 3) * _3243_3342),//c11
            -invDet * (mat(0, 1) * _3344_3443 - mat(0, 2) * _3244_3442 + mat(0, 3) * _3243_3342),//c21
            +invDet * (mat(0, 1) * _2344_2443 - mat(0, 2) * _2244_2442 + mat(0, 3) * _2243_2342),//c31
            -invDet * (mat(0, 1) * _2334_2433 - mat(0, 2) * _2234_2432 + mat(0, 3) * _2233_2332),//c41
            
            -invDet * (mat(1, 0) * _3344_3443 - mat(1, 2) * _3144_3441 + mat(1, 3) * _3143_3341),//c12
            +invDet * (mat(0, 0) * _3344_3443 - mat(0, 2) * _3144_3441 + mat(0, 3) * _3143_3341),//c22
            -invDet * (mat(0, 0) * _2344_2443 - mat(0, 2) * _2144_2441 + mat(0, 3) * _2143_2341),//32
            +invDet * (mat(0, 0) * _2334_2433 - mat(0, 2) * _2134_2431 + mat(0, 3) * _2133_2331),//c42
            
            +invDet * (mat(1, 0) * _3244_3442 - mat(1, 1) * _3144_3441 + mat(1, 3) * _3142_3241),//c13
            -invDet * (mat(0, 0) * _3244_3442 - mat(0, 1) * _3144_3441 + mat(0, 3) * _3142_3241),//c23
            +invDet * (mat(0, 0) * _2244_2442 - mat(0, 1) * _2144_2441 + mat(0, 3) * _2142_2241),//c33
            -invDet * (mat(0, 0) * _2234_2432 - mat(0, 1) * _2134_2431 + mat(0, 3) * _2132_2231),//c43
            
            -invDet * (mat(1, 0) * _3243_3342 - mat(1, 1) * _3143_3341 + mat(1, 2) * _3142_3241),//c14
            +invDet * (mat(0, 0) * _3243_3342 - mat(0, 1) * _3143_3341 + mat(0, 2) * _3142_3241),//c24
            -invDet * (mat(0, 0) * _2243_2342 - mat(0, 1) * _2143_2341 + mat(0, 2) * _2142_2241),//c34
            +invDet * (mat(0, 0) * _2233_2332 - mat(0, 1) * _2133_2331 + mat(0, 2) * _2132_2231));//c44
    }

    return mat;
}
}