#include <math/matrix.h>
#include <math/math.h>
#include <utility>

namespace MathWorker
{
Matrix::Matrix(const Matrix& rhs) noexcept
{
    M[0][0] = rhs.M[0][0]; M[0][1] = rhs.M[0][1]; M[0][2] = rhs.M[0][2]; M[0][3] = rhs.M[0][3];
    M[1][0] = rhs.M[1][0]; M[1][1] = rhs.M[1][1]; M[1][2] = rhs.M[1][2]; M[1][3] = rhs.M[1][3];
    M[2][0] = rhs.M[2][0]; M[2][1] = rhs.M[2][1]; M[2][2] = rhs.M[2][2]; M[2][3] = rhs.M[2][3];
    M[3][0] = rhs.M[3][0]; M[3][1] = rhs.M[3][1]; M[3][2] = rhs.M[3][2]; M[3][3] = rhs.M[3][3];
}

Matrix::Matrix(Matrix&& rhs) noexcept
{
    M[0][0] = rhs.M[0][0]; M[0][1] = rhs.M[0][1]; M[0][2] = rhs.M[0][2]; M[0][3] = rhs.M[0][3];
    M[1][0] = rhs.M[1][0]; M[1][1] = rhs.M[1][1]; M[1][2] = rhs.M[1][2]; M[1][3] = rhs.M[1][3];
    M[2][0] = rhs.M[2][0]; M[2][1] = rhs.M[2][1]; M[2][2] = rhs.M[2][2]; M[2][3] = rhs.M[2][3];
    M[3][0] = rhs.M[3][0]; M[3][1] = rhs.M[3][1]; M[3][2] = rhs.M[3][2]; M[3][3] = rhs.M[3][3];
}

Matrix::Matrix(float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44) noexcept
{
    M[0][0] = f11; M[0][1] = f12; M[0][2] = f13; M[0][3] = f14;
    M[1][0] = f21; M[1][1] = f22; M[1][2] = f23; M[1][3] = f24;
    M[2][0] = f31; M[2][1] = f32; M[2][2] = f33; M[2][3] = f34;
    M[3][0] = f41; M[3][1] = f42; M[3][2] = f43; M[3][3] = f44;
}

Matrix::Matrix(const Vector3D& inX, const Vector3D& inY, const Vector3D& inZ, const Vector3D& inW)
{
    M[0][0] = inX.x; M[0][1] = inX.y; M[0][2] = inX.z; M[0][3] = 0.f;
    M[1][0] = inY.x; M[1][1] = inY.y; M[1][2] = inY.z; M[1][3] = 0.f;
    M[2][0] = inZ.x; M[2][1] = inZ.y; M[2][2] = inZ.z; M[2][3] = 0.f;
    M[3][0] = inW.x; M[3][1] = inW.y; M[3][2] = inW.z; M[3][3] = 0.f;
}

Matrix& Matrix::operator=(const Matrix& rhs) noexcept
{
    if (this != &rhs)
	{
        for (size_t i = 0; i < row_num; i++)
            for (size_t j = 0; j < row_num; j++)
                M[i][j] += rhs.M[i][j];
	}
    return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs) noexcept
{
    if (this != &rhs)
	{
        for (size_t i = 0; i < row_num; i++)
            for (size_t j = 0; j < row_num; j++)
                M[i][j] += rhs.M[i][j];
	}
    return *this;
}

Matrix& Matrix::operator-(const Matrix& rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            M[i][j] -= rhs.M[i][j];
    return *this; 
}

Matrix& Matrix::operator+(const Matrix& rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            M[i][j] += rhs.M[i][j];
    return *this;         
}

Matrix& Matrix::operator+=(const Matrix& rhs) noexcept
{
    return this->operator+(rhs);
}

Matrix& Matrix::operator-=(const Matrix& rhs) noexcept
{
    return this->operator-(rhs);
}

Matrix& Matrix::operator*=(const Matrix& rhs) noexcept
{
    *this = Mul(*this, rhs);
    return *this;      
}

Matrix& Matrix::operator/(float rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            M[i][j] = M[i][j] / rhs;
    return *this;
}

Matrix& Matrix::operator*(float rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            M[i][j] = M[i][j] * rhs;
    return *this;
}

Matrix& Matrix::operator/=(float rhs) noexcept
{
    return this->operator/(rhs);
}

Matrix& Matrix::operator*=(float rhs) noexcept
{
    return this->operator*(rhs);
}

bool Matrix::operator==(const Matrix& rhs) const noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            if (!IsEqual(M[i][j], rhs.M[i][j]))
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const noexcept
{
    return !(this->operator==(rhs));
}

void Matrix::Identity()
{
	M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;    
}

std::ostream& operator<<(std::ostream& os, const  Matrix& lhs)
{
    os << lhs.M[0][0] << " " << lhs.M[0][1] << " " << lhs.M[0][2] << " " << lhs.M[0][3] << std::endl;
    os << lhs.M[1][0] << " " << lhs.M[1][1] << " " << lhs.M[1][2] << " " << lhs.M[1][3] << std::endl;
    os << lhs.M[2][0] << " " << lhs.M[2][1] << " " << lhs.M[2][2] << " " << lhs.M[2][3] << std::endl;
    os << lhs.M[3][0] << " " << lhs.M[3][1] << " " << lhs.M[3][2] << " " << lhs.M[3][3] << std::endl;
    return os;
}
}