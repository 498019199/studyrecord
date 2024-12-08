#include <common/D3D11Util.h>
#include <common/WinApp.h>
#include <common/macro.h>
#include <math/math.h>

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace MathWorker;

void checkvecotr()
{
	// test contruct
	float3 v(1, 2, 3);
	float3 u = { 0,2,3 };
	float3 w = {1.f, 1.f, 1.f};
	COMMON_ASSERT(float3(1,2,3) == v);
	COMMON_ASSERT(float3(0,2,3) == u);
	COMMON_ASSERT(float3(1.f,1.f,1.f) == w);

	std::cout << sizeof(float3) << std::endl;
	// add
	std::cout << (-v) << std::endl;
	std::cout << (v + u) << std::endl;
	std::cout << (v - u) << std::endl;
	v += u;
	std::cout << v << std::endl;
	v -= u;
	std::cout << v << std::endl;
	std::cout << (v * 5) << std::endl;
	std::cout << (5 * v) << std::endl;
	// mul
	std::cout << (v * 3.f) << std::endl;
	std::cout << (2.5f * v) << std::endl;
	std::cout << (2.5 * float2{ 1.f,2.f }) << std::endl;
	std::cout << (4.f * v) << std::endl;
	v *= 5.f;
	std::cout << v << std::endl;
	std::cout << (v / 3.f) << std::endl;
	v /= 5.f;
	std::cout << v << std::endl;
	// normalize
	std::cout << Normalize(v) << std::endl;
	v = Normalize(v);
	std::cout << v << std::endl;
	std::cout << v[2] << std::endl;

	// Cross
	std::cout << Cross(v, u) << std::endl;
	// dot
	std::cout << Dot(v, u) << std::endl;

	// lerp
	std::cout << Lerp(v, u, 0.5) << std::endl;

	// veci
	int3 iv{ 1,2,3 };
	COMMON_ASSERT(int3(5,10,15) == (iv * 5));
	COMMON_ASSERT(int3(7,14,21) == (iv * 7));

	// project, perpendicular
	//std::cout << v.project(u.Normalize()) << std::endl;
	//std::cout << v.perpendicular(u.Normalize()) << std::endl;

	Vector_T<float, 3> vs[4];
	std::cout << vs[2] + vs[3] << std::endl;
	std::cout << float3(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1], vs[0][2] + vs[1][2]) << std::endl;

	float3 ddd{ 1,2,3 };
	std::cout << (ddd + (-ddd)) << std::endl;

	// test angle
	std::stringstream ss;
	ss << std::setiosflags(std::ios::fixed) << std::setprecision(2) << Angle(float3(1,2,3), float3(3,3,3)) ;
	COMMON_ASSERT(0 == ss.str().compare("22.21"));

	// test add,sub
	auto a = float3(1,2,3);
	auto b = float3(4,5,6);
	auto c = float3(7,-3,0);
	COMMON_ASSERT(float3(5,7,9) == (a + b));
	COMMON_ASSERT(float3(-3,-3,-3) == (a - b));
	COMMON_ASSERT(float3(10,0,3) == (b + c - a));

	// test distance
	COMMON_ASSERT(10 == Distance(int2(5,0), int2(-1,8)));

	//  inner product
	COMMON_ASSERT(30 == (int2(4,6) | int2(-3,7)));
	COMMON_ASSERT(-15 == (int3(3,-2,7) | int3(0,4,-1)));

	// cross
	COMMON_ASSERT(int3(-3,6,-3) == (int3(1,2,3) ^ int3(4,5,6)));
	COMMON_ASSERT(int3(337,110,-919) == (int3(1,22,3) ^ int3(42,5,16)));
}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1920;
    settings.height = 1080;
    app.CreateAppWindow(settings);
    app.InitDevice(app.GetHWND(), settings);
    app.Run();
    return 0;
}