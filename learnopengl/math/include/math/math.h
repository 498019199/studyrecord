#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>

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
	
    // 平方根倒数算法
    float InvSqrt(float x);
    
    // 返回 from 与 to 之间的角度
    template<typename T>
    float Angle(const T& from, const T& to);
	
    // 	在两个点之间进行线性插值。
    template<typename T>
    T Lerp(const T& lhs, const T& rhs, float s);
}