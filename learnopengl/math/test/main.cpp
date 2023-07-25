#include <iostream>
#include <iomanip>
#include <sstream>
#include <math/math.h>
#include <cassert>
using namespace MathWorker;

// #define CheckAssert(op)\
//  	std::cout << ##op << std::endl;\
//  	assert(op)\

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
    //std::cout << "checkmatrix sucess" << std::endl;
	// test contruct
	float a[16]= {11, 12, 13, 14,21, 22, 23, 24,31, 32, 33, 34,41, 42, 43, 44};
	auto tmp1 = Matrix(a);
	auto tmp2 = Matrix(tmp1);
	auto tmp3 = Matrix(11, 12, 13, 14,21, 22, 23, 24,31, 32, 33, 34,41, 42, 43, 44);
	Matrix tmp4 = {11, 12, 13, 14,21, 22, 23, 24,31, 32, 33, 34,41, 42, 43, 44};
	assert(tmp1 == tmp2);
	assert(tmp1 == tmp3);
	assert(tmp1 == tmp4);
	std::cout << "test matrix contruct success" << std::endl << tmp1 << std::endl;

	// test matrix multiplication
	assert(Matrix(12,1,13,14, 12,0,12,15,  10,0,10,7, 2,0,2,2) == 
		Mul(Matrix(1,2,3,4,  0,0,5,6,  0,2,1,3,  0,1,0,0), 
		Matrix(0,1,1,1,  2,0,2,2,  0,0,0,3,  2,0,2,0)));
	// test +,-
	assert(Matrix(3,3,3,3, 3,3,3,3,  3,3,3,3, 3,3,3,3) == 
		(Matrix(1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1) + 
		Matrix(2,2,2,2, 2,2,2,2,  2,2,2,2, 2,2,2,2)));
	assert(Matrix(2,2,2,2, 2,2,2,2,  2,2,2,2, 2,2,2,2) == 
		(Matrix(3,3,3,3, 3,3,3,3,  3,3,3,3, 3,3,3,3) - 
		Matrix(1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1)));
	// test matrix scalar
	assert(Matrix(2,2,2,2, 2,2,2,2,  2,2,2,2, 2,2,2,2) == 
		Matrix(1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1) * 2);
	assert(Matrix(2,2,2,2, 2,2,2,2,  2,2,2,2, 2,2,2,2) / 2 == 
		Matrix(1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1));
}

void checkquaternion()
{
    //std::cout << "checkquaternion sucess" << std::endl;
	// test contruct
	auto q1 = Quaternion();
	auto q2 = Quaternion(1,2,3, 4);
	auto v1 = Vector3D(1.f, 2.f, 3.f);
	auto q3 = Quaternion(v1, 4.f);
	auto q4 = Quaternion(q2);
	assert(q4 == q3);
	std::cout << "test quaternion  contruct success" << q1 << std::endl;
}

void checkmath()
{
	// athmatic matrix
	auto m1 = Matrix(11, 12, 13, 14,
					21, 22, 23, 24,
					31, 32, 33, 34,
					41, 42, 43, 44);
	auto m2 = Matrix(11, 21, 31, 41,
					 12, 22, 32, 42,
					 13, 23, 33, 43,
					 14, 24, 34, 44);
	assert(Transpose(m1) == m2);

	// test rotation matrix
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixRotateX(0));
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixRotateY(0));
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixRotateZ(0));
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixRotate(Vector4D(0,0,0,0), 0));
	// move
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixMove(0,0,0));
	// Scale
	assert(Matrix(2,2,2,2,  2,2,2,2,  2,2,2,2,  2,2,2,2) == MatrixScale(0,0,0));
}

int main()
{
    checkvecotr();
    checkmatrix();
    checkquaternion();
	checkmath();
}
