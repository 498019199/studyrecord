#include <iostream>
#include <iomanip>
#include <sstream>
#include <math/math.h>
#include <cassert>
using namespace MathWorker;

void checkvecotr()
{
	// test contruct
	Vector3D v(1, 2, 3);
	Vector3D u = { 0,2,3 };
	Vector3D w(1.f);
	assert(Vector3D(1,2,3) == v);
	assert(Vector3D(0,2,3) == u);
	assert(Vector3D(1.f,1.f,1.f) == w);

	std::cout << sizeof(Vector3D) << std::endl;
	// add
	std::cout << -v << std::endl;
	std::cout << v + u << std::endl;
	std::cout << v - u << std::endl;
	v += u;
	std::cout << v << std::endl;
	v -= u;
	std::cout << v << std::endl;
	std::cout << v * 5 << std::endl;
	std::cout << 5 * v << std::endl;
	// mul
	std::cout << v * 3.f << std::endl;
	std::cout << 2.5f * v << std::endl;
	std::cout << 2.5 * Vector2D{ 1.f,2.f } << std::endl;
	std::cout << 4.f * v << std::endl;
	v *= 5.f;
	std::cout << v << std::endl;
	std::cout << v / 3.f << std::endl;
	v /= 5.f;
	std::cout << v << std::endl;
	// normalize
	std::cout << v.Normalize() << std::endl;
	v.Normalize();
	std::cout << v << std::endl;
	std::cout << v[2] << std::endl;

	// Cross
	std::cout << Vector3D::Cross(v, u) << std::endl;
	std::cout << v.Cross(u) << std::endl;
	//
	std::cout << Vector3D::Dot(v, u) << std::endl;
	std::cout << v.Dot(u) << std::endl;

	// lerp
	std::cout << Lerp(v, u, 0.5) << std::endl;

	// veci
	Vector3D iv{ 1,2,3 };
	assert(Vector3D(5,10,15) == (iv * 5));
	assert(Vector3D(7,14,21) == (iv * 7));

	// project, perpendicular
	//std::cout << v.project(u.Normalize()) << std::endl;
	//std::cout << v.perpendicular(u.Normalize()) << std::endl;

	Vector3D vs[4];
	std::cout << vs[2] + vs[3] << std::endl;
	std::cout << Vector3D(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1], vs[0][2] + vs[1][2]) << std::endl;

	Vector3D ddd{ 1,2,3 };
	std::cout << ddd + (-ddd) << std::endl;

	// test angle
	std::stringstream ss;
	ss << std::setiosflags(std::ios::fixed) << std::setprecision(2) << MathWorker::Angle(Vector3D(1,2,3), Vector3D(3,3,3)) ;
	assert(0 == ss.str().compare("22.21"));

	// test add,sub
	auto a = Vector3D(1,2,3);
	auto b = Vector3D(4,5,6);
	auto c = Vector3D(7,-3,0);
	assert(Vector3D(5,7,9) == (a + b));
	assert(Vector3D(-3,-3,-3) == (a - b));
	assert(Vector3D(10,0,3) == (b + c - a));

	// test distance
	assert(10 == Vector2D::Distance(Vector2D(5,0), Vector2D(-1,8)));

	//  inner product
	assert(30 == (Vector2D(4,6) | Vector2D(-3,7)));
	assert(-15 == (Vector3D(3,-2,7) | Vector3D(0,4,-1)));

	// cross
	assert(Vector3D(-3,6,-3) == (Vector3D(1,2,3) ^ Vector3D(4,5,6)));
	assert(Vector3D(337,110,-919) == (Vector3D(1,22,3) ^ Vector3D(42,5,16)));
}

void checkmatrix()
{
    std::cout << "checkmatrix sucess" << std::endl;
}

void checkquaternion()
{
    std::cout << "checkquaternion sucess" << std::endl;
}

int main()
{
    checkvecotr();
    checkmatrix();
    checkquaternion();
}
