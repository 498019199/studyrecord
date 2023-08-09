#include <math/math.h>
#include "math_helper.h"

namespace MathWorker
{
    void SinCos(float fAnglel, float& X, float&Y)
	{
		X = std::sin(fAnglel);
		Y = std::cos(fAnglel);
	}

    template bool IsEqual(float X, float Y);
    template bool IsEqual(double X, double Y);
    template <typename T>
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
        fni.f = number;                                      // evil floating point bit level hacking
        fni.i = 0x5f375a86 - (fni.i >> 1);                   // what the fuck?
        fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f)); // 1st iteration
        fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f)); // 2nd iteration, this can be removed

        return fni.f;
    }

	template int32_t Cross(const int2 & lhs, const int2 & rhs) noexcept;
    template uint32_t Cross(const uint2 & lhs, const uint2 & rhs) noexcept;
    template float Cross(const float2 & lhs, const float2 & rhs) noexcept;
	template<typename T>
	T Cross(const Vector_T<T, 2> & lhs, const Vector_T<T, 2> & rhs) noexcept
	{
		return lhs.x() * rhs.y() - lhs.y() * rhs.x();
	}

    template int3 Cross(const int3 & lhs, const int3 & rhs) noexcept;
    template uint3 Cross(const uint3 & lhs, const uint3 & rhs) noexcept;
    template float3 Cross(const float3 & lhs, const float3 & rhs) noexcept;
    template<typename T>
    Vector_T<T, 3> Cross(const Vector_T<T, 3>& lhs, const Vector_T<T, 3>& rhs) noexcept
    {
        return Vector_T<T, 3>((lhs.y() * rhs.z() - lhs.z() * rhs.y()),
        (lhs.z() * rhs.x() - lhs.x() * rhs.z()),
        (lhs.x() * rhs.y() - lhs.y() * rhs.x()));
    }

	template int4 Cross(const int4 & lhs, const int4 & rhs) noexcept;
	template uint4 Cross(const uint4 & lhs, const uint4 & rhs) noexcept;
	template float4 Cross(const float4 & lhs, const float4 & rhs) noexcept;
	template<typename T>
	Vector_T<T, 4>
		Cross(const Vector_T<T, 4> & lhs, const Vector_T<T, 4> & rhs) noexcept
	{
		return Vector_T<T, 4>((lhs.y() * rhs.z() - lhs.z() * rhs.y()),
			(lhs.z() * rhs.x() - lhs.x() * rhs.z()),
			(lhs.x() * rhs.y() - lhs.y() * rhs.x()),
			1);
	}

    template int32_t Dot(const int1 & lhs, const int1 & rhs) noexcept;
    template int32_t Dot(const int2 & lhs, const int2 & rhs) noexcept;
    template int32_t Dot(const int3 & lhs, const int3 & rhs) noexcept;
    template int32_t Dot(const int4 & lhs, const int4 & rhs) noexcept;
    template uint32_t Dot(const uint1 & lhs, const uint1 & rhs) noexcept;
    template uint32_t Dot(const uint2 & lhs, const uint2 & rhs) noexcept;
    template uint32_t Dot(const uint3 & lhs, const uint3 & rhs) noexcept;
    template uint32_t Dot(const uint4 & lhs, const uint4 & rhs) noexcept;
    template float Dot(const float1 & lhs, const float1 & rhs) noexcept;
    template float Dot(const float2 & lhs, const float2 & rhs) noexcept;
    template float Dot(const float3 & lhs, const float3 & rhs) noexcept;
    template float Dot(const float4 & lhs, const float4 & rhs) noexcept;
	template float Dot(const quat & lhs, const quat & rhs) noexcept;
    template<typename T>
    typename T::value_type Dot(const T & lhs, const T & rhs) noexcept
    {
        return MathHelper::dot_helper < typename T::value_type,
            T::elem_num> ::Do(&lhs[0], &rhs[0]);
    }

    template int32_t LengthSq(const int1 & rhs) noexcept;
    template int32_t LengthSq(const int2 & rhs) noexcept;
    template int32_t LengthSq(const int3 & rhs) noexcept;
    template int32_t LengthSq(const int4 & rhs) noexcept;
    template uint32_t LengthSq(const uint1 & rhs) noexcept;
    template uint32_t LengthSq(const uint2 & rhs) noexcept;
    template uint32_t LengthSq(const uint3 & rhs) noexcept;
    template uint32_t LengthSq(const uint4 & rhs) noexcept;
    template float LengthSq(const float1 & rhs) noexcept;
    template float LengthSq(const float2 & rhs) noexcept;
    template float LengthSq(const float3 & rhs) noexcept;
    template float LengthSq(const float4 & rhs) noexcept;
	template float LengthSq(const quat & rhs) noexcept;
    template<typename T>
    typename T::value_type LengthSq(const T & rhs) noexcept
    {
        return Dot(rhs, rhs);
    }

    template float Length(const float1 & rhs) noexcept;
    template float Length(const float2 & rhs) noexcept;
    template float Length(const float3 & rhs) noexcept;
    template float Length(const float4 & rhs) noexcept;
	template float Length(const quat & rhs) noexcept;
    template<typename T>
    typename T::value_type Length(const T & rhs) noexcept
    {
        return std::sqrt(LengthSq(rhs));
    }

	template float1 Normalize(const float1 & rhs) noexcept;
	template float2 Normalize(const float2 & rhs) noexcept;
	template float3 Normalize(const float3 & rhs) noexcept;
	template float4 Normalize(const float4 & rhs) noexcept;
	template quat Normalize(const quat & rhs) noexcept;
	template<typename T>
	T Normalize(const T & rhs) noexcept
	{
		typename T::value_type tmp = 
            RecipSqrt(
                LengthSq(rhs));
		return rhs * tmp;
	}

    template int2 Lerp(const int2 &lsh, const int2 &rhs, float s);
    template int3 Lerp(const int3 &lsh, const int3 &rhs, float s);
    template int4 Lerp(const int4 &lsh, const int4 &rhs, float s);
    template uint2 Lerp(const uint2 &lsh, const uint2 &rhs, float s);
    template uint3 Lerp(const uint3 &lsh, const uint3 &rhs, float s);
    template uint4 Lerp(const uint4 &lsh, const uint4 &rhs, float s);
    template float2 Lerp(const float2 &lsh, const float2 &rhs, float s);
    template float3 Lerp(const float3 &lsh, const float3 &rhs, float s);
    template float4 Lerp(const float4 &lsh, const float4 &rhs, float s);
    template <typename T>
    T Lerp(const T &lhs, const T &rhs, float s)
    {
        return (lhs + (rhs - lhs) * s);
    }

    template float Angle(const float2 &lsh, const float2 &rhs);
    template float Angle(const float3 &lsh, const float3 &rhs);
    template float Angle(const float4 &lsh, const float4 &rhs);
    template <typename T>
    typename T::value_type Angle(const T &lsh, const T &rsh)
    {
        typename T::value_type xn = Length(lsh);
        typename T::value_type yn = Length(rsh);
        typename T::value_type xyn = xn * yn;
        typename T::value_type angle = std::acos((lsh | rsh) / xyn);
        return Rad2Deg(angle);
    }

    template float4x4 MatrixMove(float X, float Y, float Z);
    template<typename T>
    Matrix4_T<T> MatrixMove(T X, T Y, T Z)
    {
        return Matrix4_T<T>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            X, Y, Z, 1);
    }

    template<float> float4x4 MatrixMove(const float3& Move);
    template<typename T>
    Matrix4_T<T> MatrixMove(const Vector_T<T, 3> &Move)
    {
        return MatrixMove(Move.x()(), Move.y(), Move.z());
    }

    template float4x4 MatrixScale(float X, float Y, float Z);
    template<typename T>
    Matrix4_T<T> MatrixScale(T X, T Y, T Z)
    {
        return Matrix4_T<T>(
            X, 0, 0, 0,
            0, Y, 0, 0,
            0, 0, Z, 0,
            1, 1, 1, 1);
    }

    template float4x4 MatrixScale(const float3& Scale);
    template<typename T>
    Matrix4_T<T> MatrixScale(const Vector_T<T, 3> &Scale)
    {
        return MatrixScale(Scale.x(), Scale.y(), Scale.z());
    }

    template float4x4 MatrixRotateX(float Angle);
    template<typename T>
    Matrix4_T<T> MatrixRotateX(T Angle)
    {
        float fs, fc;
        SinCos(Angle, fs, fc);
        return Matrix4_T<T>(
            1, 0,   0,  0,
            0, fc,  fs, 0,
            0, -fs, fc, 0,
            0, 0,   0,  1);
    }

    template float4x4 MatrixRotateY(float Angle);
    template<typename T>
    Matrix4_T<T> MatrixRotateY(T Angle)
    {
        float fs, fc;
        SinCos(Angle, fs, fc);
        return Matrix4_T<T>(
            fc, 0, -fs, 0,
            0, 1, 0, 0,
            fs, 0, fc, 0,
            0, 0, 0, 1);
    }

    template float4x4 MatrixRotateZ(float Angle);
    template<typename T>
    Matrix4_T<T> MatrixRotateZ(T Angle)
    {
        float fs, fc;
        SinCos(Angle, fs, fc);
        return Matrix4_T<T>(
            fc, fs, 0, 0,
            -fs, fc, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    template float4x4 MatrixRotate(const float3& n, float Angle);
    template<typename T>
    Matrix4_T<T> MatrixRotate(const Vector_T<T, 3>& n, T Angle)
    {
        float fs = 0.0f, fc = 0.0f;
        SinCos(Angle, fs, fc);
        Vector_T<T, 4> v(n.x(), n.y(), n.z(), 1.0f);
        v = Normalize(v);

        float a = 1.0f - fc;
        float ax = a * v.x();
        float ay = a * v.y();
        float az = a * v.z();

        Matrix4_T<T> matrix;
        matrix(0, 0) = v.x() * ax + fc;
        matrix(0, 1) = v.x() * ay + v.z() * fs;
        matrix(0, 2) = v.x() * az - v.y() * fs;
        matrix(1, 0) = v.x() * ay - v.z() * fs;
        matrix(1, 1) = v.y() * ay + fc;
        matrix(1, 2) = v.y() * az + v.x() * fs;
        matrix(2, 0) = v.x() * az + v.y() * fs;
        matrix(2, 1) = v.y() * az - v.x() * fs;
        matrix(2, 2) = v.z() * az + fc;
        return matrix;
    }

    template float4x4 Mul(const float4x4& lhs, const float4x4& rhs);
    template<typename T>
    Matrix4_T<T> Mul(const Matrix4_T<T> &lhs, const Matrix4_T<T> &rhs)
    {
        return Matrix4_T<T>(
            lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0),
            lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1),
            lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2),
            lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3),
            lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0),
            lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1),
            lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2),
            lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3),
            lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0),
            lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1),
            lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2),
            lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3),
            lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0) + lhs(3, 3) * rhs(3, 0),
            lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1),
            lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2) + lhs(3, 3) * rhs(3, 2),
            lhs(3, 0) * rhs(0, 3) + lhs(3, 1) * rhs(1, 3) + lhs(3, 2) * rhs(2, 3) + lhs(3, 3) * rhs(3, 3));
    }

    // 1*4 mul 4*4
    template float4 Mul(const float4& a, const float4x4& mat);
    template<typename T>
    Vector_T<T, 4> Mul(const Vector_T<T, 4> &a, const Matrix4_T<T> &mat)
    {
		return Vector_T<T, 4>(a.x() * mat(0, 0) + a.y() * mat(1, 0) + a.z() * mat(2, 0) + a.w() * mat(3, 0),
                                a.x() * mat(0, 1) + a.y() * mat(1, 1) + a.z() * mat(2, 1) + a.w() * mat(3, 1),
                                a.x() * mat(0, 2) + a.y() * mat(1, 2) + a.z() * mat(2, 2) + a.w() * mat(3, 2),
                                a.x() * mat(0, 3) + a.y() * mat(1, 3) + a.z() * mat(2, 3) + a.w() * mat(3, 3));
    }

    template float4x4 Transpose(const float4x4& mat);
    template<typename T>
    Matrix4_T<T> Transpose(const Matrix4_T<T> &mat)
    {
        return Matrix4_T<T>(mat(0, 0), mat(1, 0), mat(2, 0), mat(3, 0),
                      mat(0, 1), mat(1, 1), mat(2, 1), mat(3, 1),
                      mat(0, 2), mat(1, 2), mat(2, 2), mat(3, 2),
                      mat(0, 3), mat(1, 3), mat(2, 3), mat(3, 3));
    }

    // 矩阵的行列式
    template float Determinant(const float4x4& mat);
    template<typename T>
    float Determinant(const Matrix4_T<T> &mat)
    {
        const float _3142_3241(mat(2, 0) * mat(3, 1) - mat(2, 1) * mat(3, 0));
        const float _3143_3341(mat(2, 0) * mat(3, 2) - mat(2, 2) * mat(3, 0));
        const float _3144_3441(mat(2, 0) * mat(3, 3) - mat(2, 3) * mat(3, 0));
        const float _3243_3342(mat(2, 1) * mat(3, 2) - mat(2, 2) * mat(3, 1));
        const float _3244_3442(mat(2, 1) * mat(3, 3) - mat(2, 3) * mat(3, 1));
        const float _3344_3443(mat(2, 2) * mat(3, 3) - mat(2, 3) * mat(3, 2));

        return mat(0, 0) * (mat(1, 1) * _3344_3443 - mat(1, 2) * _3244_3442 + mat(1, 3) * _3243_3342) - 
        mat(0, 1) * (mat(1, 0) * _3344_3443 - mat(1, 2) * _3144_3441 + mat(1, 3) * _3143_3341) + 
        mat(0, 2) * (mat(1, 0) * _3244_3442 - mat(1, 1) * _3144_3441 + mat(1, 3) * _3142_3241) - 
        mat(0, 3) * (mat(1, 0) * _3243_3342 - mat(1, 1) * _3143_3341 + mat(1, 2) * _3142_3241);
    }

    // 矩阵的逆
    template float4x4 MatrixInverse(const float4x4& mat);
    template<typename T>
    Matrix4_T<T> MatrixInverse(const Matrix4_T<T>& mat)
    {
        const float _2132_2231(mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));
        const float _2133_2331(mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0));
        const float _2134_2431(mat(1, 0) * mat(2, 3) - mat(1, 3) * mat(2, 0));
        const float _2142_2241(mat(1, 0) * mat(3, 1) - mat(1, 1) * mat(3, 0));
        const float _2143_2341(mat(1, 0) * mat(3, 2) - mat(1, 2) * mat(3, 0));
        const float _2144_2441(mat(1, 0) * mat(3, 3) - mat(1, 3) * mat(3, 0));
        const float _2233_2332(mat(1, 1) * mat(2, 2) - mat(1, 2) * mat(2, 1));
        const float _2234_2432(mat(1, 1) * mat(2, 3) - mat(1, 3) * mat(2, 1));
        const float _2243_2342(mat(1, 1) * mat(3, 2) - mat(1, 2) * mat(3, 1));
        const float _2244_2442(mat(1, 1) * mat(3, 3) - mat(1, 3) * mat(3, 1));
        const float _2334_2433(mat(1, 2) * mat(2, 3) - mat(1, 3) * mat(2, 2));
        const float _2344_2443(mat(1, 2) * mat(3, 3) - mat(1, 3) * mat(3, 2));
        const float _3142_3241(mat(2, 0) * mat(3, 1) - mat(2, 1) * mat(3, 0));
        const float _3143_3341(mat(2, 0) * mat(3, 2) - mat(2, 2) * mat(3, 0));
        const float _3144_3441(mat(2, 0) * mat(3, 3) - mat(2, 3) * mat(3, 0));
        const float _3243_3342(mat(2, 1) * mat(3, 2) - mat(2, 2) * mat(3, 1));
        const float _3244_3442(mat(2, 1) * mat(3, 3) - mat(2, 3) * mat(3, 1));
        const float _3344_3443(mat(2, 2) * mat(3, 3) - mat(2, 3) * mat(3, 2));

        // 行列式的值
        const float det(Determinant(mat));
        if (IsEqual<float>(det, 0))
        {
            return mat;
        }
        else
        {
            // 标准伴随矩阵的转置 / 行列式的值
            float invDet(float(1) / det);
            return Matrix4_T<T>(
                +invDet * (mat(1, 1) * _3344_3443 - mat(1, 2) * _3244_3442 + mat(1, 3) * _3243_3342), // c11
                -invDet * (mat(0, 1) * _3344_3443 - mat(0, 2) * _3244_3442 + mat(0, 3) * _3243_3342), // c21
                +invDet * (mat(0, 1) * _2344_2443 - mat(0, 2) * _2244_2442 + mat(0, 3) * _2243_2342), // c31
                -invDet * (mat(0, 1) * _2334_2433 - mat(0, 2) * _2234_2432 + mat(0, 3) * _2233_2332), // c41

                -invDet * (mat(1, 0) * _3344_3443 - mat(1, 2) * _3144_3441 + mat(1, 3) * _3143_3341), // c12
                +invDet * (mat(0, 0) * _3344_3443 - mat(0, 2) * _3144_3441 + mat(0, 3) * _3143_3341), // c22
                -invDet * (mat(0, 0) * _2344_2443 - mat(0, 2) * _2144_2441 + mat(0, 3) * _2143_2341), // c32
                +invDet * (mat(0, 0) * _2334_2433 - mat(0, 2) * _2134_2431 + mat(0, 3) * _2133_2331), // c42

                +invDet * (mat(1, 0) * _3244_3442 - mat(1, 1) * _3144_3441 + mat(1, 3) * _3142_3241), // c13
                -invDet * (mat(0, 0) * _3244_3442 - mat(0, 1) * _3144_3441 + mat(0, 3) * _3142_3241), // c23
                +invDet * (mat(0, 0) * _2244_2442 - mat(0, 1) * _2144_2441 + mat(0, 3) * _2142_2241), // c33
                -invDet * (mat(0, 0) * _2234_2432 - mat(0, 1) * _2134_2431 + mat(0, 3) * _2132_2231), // c43

                -invDet * (mat(1, 0) * _3243_3342 - mat(1, 1) * _3143_3341 + mat(1, 2) * _3142_3241),  // c14
                +invDet * (mat(0, 0) * _3243_3342 - mat(0, 1) * _3143_3341 + mat(0, 2) * _3142_3241),  // c24
                -invDet * (mat(0, 0) * _2243_2342 - mat(0, 1) * _2143_2341 + mat(0, 2) * _2142_2241),  // c34
                +invDet * (mat(0, 0) * _2233_2332 - mat(0, 1) * _2133_2331 + mat(0, 2) * _2132_2231)); // c44
        }
    }

    template<typename T>
	Matrix4_T<T> OrthoLH(float w, float h, float Near, float Far)
    {
        return Matrix4_T<T>();        
    }

    template<typename T>
	Matrix4_T<T> OrthoOffCenterLH(float l, float r, float b, float t, float n, float f)
    {
        float rsl = r - l;
        float ral = r + l;
        float nsf = n - f;
        float tsb = t - b;
        return Matrix4_T<T>(
            2/rsl,      0,          0,              0,
            0,          2/tsb,      0,              0,
            0,          0,          2/nsf,          0,
            -ral/rsl,   -(t+b)/tsb, (n + f)/nsf,    1);        
    }

    template float4x4 LookAtLH(const float3& Eys, const float3& At, const float3& Up);
    template<typename T>
	Matrix4_T<T> LookAtLH(const Vector_T<float, 3>& Eye, const Vector_T<float, 3>& At, const Vector_T<float, 3>& Up)
    {
        Vector_T<float, 3> zaxis = Normalize(Eye - At);
        Vector_T<float, 3> xaxis = Normalize(Up ^ zaxis);
        Vector_T<float, 3> yaxis = zaxis ^ xaxis;
        return Matrix4_T<T>(
            xaxis.x(), yaxis.x(), zaxis.x(), 0,
            xaxis.y(), yaxis.y(), zaxis.y(), 0,
            xaxis.z(), yaxis.z(), zaxis.z(), 0,
            xaxis | Eye, yaxis | Eye, zaxis | Eye, 1);        
    }

    template<typename T>
	Matrix4_T<T> PerspectiveLH(float w, float h, float Near, float Far)
    {
        return Matrix4_T<T>();        
    }

    template<typename T>
	Matrix4_T<T> PerspectiveFovLH(float Fov, float Aspect, float Near, float Far)
    {
        return Matrix4_T<T>();        
    }



    template<typename T>
	Quaternion_T<T> Mul(const Quaternion_T<T>& lhs, const Quaternion_T<T>& rhs) noexcept
	{
		return Quaternion_T<T>(
			lhs.x() * rhs.w() - lhs.y() * rhs.z() + lhs.z() * rhs.y() + lhs.w() * rhs.x(),
			lhs.x() * rhs.z() + lhs.y() * rhs.w() - lhs.z() * rhs.x() + lhs.w() * rhs.y(),
			lhs.y() * rhs.x() - lhs.x() * rhs.y() + lhs.z() * rhs.w() + lhs.w() * rhs.z(),
			lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z());
	}


    template<typename T>
    Matrix4_T<T> ToMatrix(const Quaternion_T<T> &quat)
    {
        return Matrix4_T<T>();
    }

    template<typename T>
    Matrix4_T<T> ToMatrix(const Rotator &rot)
    {
        return Matrix4_T<T>();
    }

    template<typename T>
    Quaternion_T<T> ToQuaternion(const Matrix4_T<T> &mat)
    {
        return Quaternion_T<T>();
    }

    template<typename T>
    Quaternion_T<T> ToQuaternion(const Rotator &rot)
    {
        return Quaternion_T<T>();
    }

    template<typename T>
    Rotator ToRotator(const Matrix4_T<T> &mat)
    {
        return Rotator();
    }

    template<typename T>
    Rotator ToRotator(const Quaternion_T<T> &quat)
    {
        return Rotator();
    }

}