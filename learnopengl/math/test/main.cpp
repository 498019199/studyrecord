#include <iostream>
#include <math/math.h>

void checkvecotr()
{
	vector3d v(1, 2, 3);
	vector3d u = { 0,2,3 };
	vector3d w(1.f);
	std::cout << sizeof(vector3d) << std::endl;

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
	std::cout << 2.5 * vector2d{ 1.f,2.f } << std::endl;
	std::cout << 4.f * v << std::endl;
	v *= 5.f;
	std::cout << v << std::endl;
	std::cout << v / 3.f << std::endl;
	v /= 5.f;
	std::cout << v << std::endl;

	// inner product
	std::cout << v.dot(u) << std::endl;
	std::cout << vector3d::dot(v, u) << std::endl;
	
	// norm
	// std::cout << v.norm2() << std::endl;
	// std::cout << v.norm() << std::endl;
	std::cout << v.normalize() << std::endl;
	v.normalize();
	std::cout << v << std::endl;
	std::cout << v[2] << std::endl;

	// angle
	//std::cout << vecf3::cos_theta(v, u) << std::endl;
	//std::cout << v.cos_theta(u) << std::endl;

	// cross
	std::cout << vector3d::cross(v, u) << std::endl;
	std::cout << v.cross(u) << std::endl;
	//
	std::cout << vector3d::dot(v, u) << std::endl;
	std::cout << v.dot(u) << std::endl;

	// lerp
	// std::cout << vecf3::lerp(v, u, 0.5) << std::endl;
	// std::cout << v.lerp(u, 0.5f) << std::endl;

	// veci
	vector3d iv{ 1,2,3 };
	std::cout << iv * 5 << std::endl;
	std::cout << iv * 7 << std::endl;

	// project, perpendicular
	//std::cout << v.project(u.normalize()) << std::endl;
	//std::cout << v.perpendicular(u.normalize()) << std::endl;

	vector3d vs[4];

	// for (size_t i = 0; i < 4; i++)
	// 	std::cin >> vs[i];

	std::cout << vs[2] + vs[3] << std::endl;
	std::cout << vector3d(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1], vs[0][2] + vs[1][2]) << std::endl;

	vector3d ddd{ 1,2,3 };
	std::cout << ddd + (-ddd) << std::endl;

	{
		vector4d v(1, 2, 3, 0);
		vector4d u(2, 3, 4, 1);
		//vector4d rst = v.hadamard_div(u);
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
