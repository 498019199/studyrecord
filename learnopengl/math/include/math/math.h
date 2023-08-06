#pragma once

#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>
#include <math/matrix.h>
#include <math/quaternion.h>
#include <math/rotator.h>
namespace MathWorker
{
    const float PI = 3.141592f;
	const float PI2 = 6.283185f;
	const float PIdiv2 = 1.570796f;

	const float DEG90 = 1.570796f;			// 90 度
	const float DEG270 = -1.570796f;		// 270 度
	const float DEG45 = 0.7853981f;			// 45 度
	const float DEG5 = 0.0872664f;			// 5 度
	const float DEG10 = 0.1745329f;			// 10 度
	const float DEG20 = 0.3490658f;			// 20 度
	const float DEG30 = 0.5235987f;			// 30 度
	const float DEG60 = 1.047197f;			// 60 度
	const float DEG120 = 2.094395f;			// 120 度
	const float DEG40 = 0.6981317f;			// 40 度
	const float DEG80 = 1.396263f;			// 80 度
	const float DEG140 = 2.443460f;			// 140 度
	const float DEG160 = 2.792526f;			// 160 度

	const float DEG2RAD = 0.01745329f;			// 角度化弧度因数
	const float RAD2DEG = 57.29577f;			// 弧度化角度因数

	inline float Deg2Rad(const float x)
	{
		return x * DEG2RAD;
	}
	// 弧度化角度
	inline float Rad2Deg(const float x)
	{
		return x * RAD2DEG;
	}
	
	inline void SinCos(float fAnglel, float& X, float&Y)
	{
		X = std::sin(fAnglel);
		Y = std::cos(fAnglel);
	}

	// 浮点相等
	template<typename T>
	bool IsEqual(T X, T Y);

	//  平方根倒数速算法
	float RecipSqrt(float number) noexcept;
    
    // 返回 from 与 to 之间的角度
    template<typename T>
    float Angle(const T& from, const T& to);
	
    // 	线性插值。
    template<typename T>
    T Lerp(const T& lhs, const T& rhs, float s);

	// 矩形平移
	Matrix MatrixMove(float X, float Y, float Z);
	Matrix MatrixMove(const Vector4D& Move);
	// 矩形缩放
	Matrix MatrixScale(float X, float Y, float Z);
	Matrix MatrixScale(const Vector4D& Scale);
	// 矩阵旋转
	Matrix MatrixRotateX(float Angle);
	Matrix MatrixRotateY(float Angle);
	Matrix MatrixRotateZ(float Angle);
	Matrix MatrixRotate(const Vector3D& Pos, float Angle);

	// 矩形乘法
	Matrix Mul(const Matrix&lhs, const Matrix& rhs);
	Vector4D Mul(const Vector4D&lhs, const Matrix& rhs);
	// 矩阵转置
	Matrix Transpose(const Matrix& m);
	// 矩阵的行列式
	float Determinant(const Matrix& m);
	// 矩阵的逆
	Matrix MatrixInverse(const Matrix& m);

	// // 正交投影
	// Matrix OrthogonalProjection(const Matrix& m);
	// // 透视投影
	// Matrix PerspectiveProjection(const Matrix& m);

	// 相互转换
	Matrix ToMatrix(const Quaternion& quat);
	Matrix ToMatrix(const Rotator& rot);
	Quaternion ToQuaternion(const Matrix& mat);
	Quaternion ToQuaternion(const Rotator& rot);
	Rotator ToRotator(const Matrix& mat);
	Rotator ToRotator(const Quaternion& quat);
}