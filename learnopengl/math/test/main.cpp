#include <iostream>
#include <math/math.h>
using namespace MathWorker;

void checkvecotr()
{
	Vector3D v(1, 2, 3);
	Vector3D u = { 0,2,3 };
	Vector3D w(1.f);
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

	// inner product
	std::cout << v.Dot(u) << std::endl;
	std::cout << Vector3D::Dot(v, u) << std::endl;
	
	// norm
	// std::cout << v.norm2() << std::endl;
	// std::cout << v.norm() << std::endl;
	std::cout << v.Normalize() << std::endl;
	v.Normalize();
	std::cout << v << std::endl;
	std::cout << v[2] << std::endl;

	// angle
	//std::cout << vecf3::cos_theta(v, u) << std::endl;
	//std::cout << v.cos_theta(u) << std::endl;

	// Cross
	std::cout << Vector3D::Cross(v, u) << std::endl;
	std::cout << v.Cross(u) << std::endl;
	//
	std::cout << Vector3D::Dot(v, u) << std::endl;
	std::cout << v.Dot(u) << std::endl;

	// lerp
	// std::cout << vecf3::lerp(v, u, 0.5) << std::endl;
	// std::cout << v.lerp(u, 0.5f) << std::endl;

	// veci
	Vector3D iv{ 1,2,3 };
	std::cout << iv * 5 << std::endl;
	std::cout << iv * 7 << std::endl;

	// project, perpendicular
	//std::cout << v.project(u.Normalize()) << std::endl;
	//std::cout << v.perpendicular(u.Normalize()) << std::endl;

	Vector3D vs[4];

	// for (size_t i = 0; i < 4; i++)
	// 	std::cin >> vs[i];

	std::cout << vs[2] + vs[3] << std::endl;
	std::cout << Vector3D(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1], vs[0][2] + vs[1][2]) << std::endl;

	Vector3D ddd{ 1,2,3 };
	std::cout << ddd + (-ddd) << std::endl;

	{
		Vector4D v(1, 2, 3, 0);
		Vector4D u(2, 3, 4, 1);
		//Vector4D rst = v.hadamard_div(u);
		//std::cout << rst << std::endl;
	}
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
