#include <math/matrix.h>
#include <utility>

namespace MathWorker
{

Matrix::Matrix(const float* rhs) noexcept
{
    _11 = rhs[ 0];	_12 = rhs[ 1];	_13 = rhs[ 2];	_14 = rhs[ 3];	
	_21 = rhs[ 4];	_22 = rhs[ 5];	_23 = rhs[ 6];	_24 = rhs[ 7];	
	_31 = rhs[ 8];	_32 = rhs[ 9];	_33 = rhs[10];	_34 = rhs[11];	
	_41 = rhs[12];	_42 = rhs[13];	_43 = rhs[14];	_44 = rhs[15];
}

Matrix::Matrix(const Matrix& rhs) noexcept
    :_11(rhs._11), _12(rhs._12), _13(rhs._13), _14(rhs._14),
    _21(rhs._21), _22(rhs._22), _23(rhs._23), _24(rhs._24), 
    _31(rhs._31), _32(rhs._32), _33(rhs._33), _34(rhs._34), 
    _41(rhs._41), _42(rhs._42), _43(rhs._43), _44(rhs._44)
{
}

Matrix::Matrix(Matrix&& rhs) noexcept
    :_11(rhs._11), _12(rhs._12), _13(rhs._13), _14(rhs._14),
    _21(rhs._21), _22(rhs._22), _23(rhs._23), _24(rhs._24), 
    _31(rhs._31), _32(rhs._32), _33(rhs._33), _34(rhs._34), 
    _41(rhs._41), _42(rhs._42), _43(rhs._43), _44(rhs._44)
{
}

Matrix::Matrix(float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44) noexcept
                :_11(f11),_12(f12),_13(f13),_14(f14),
                _21(f21),_22(f22),_23(f23),_24(f24),
                _31(f31),_32(f32),_33(f33),_34(f34),
                _41(f41),_42(f42),_43(f43),_44(f44)
{
}

Matrix& Matrix::operator=(const Matrix& rhs) noexcept
{
    if (this != &rhs)
	{
        for (size_t i = 0; i < row_num; i++)
            for (size_t j = 0; j < row_num; j++)
                m[i][j] += rhs.m[i][j];
	}
    return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs) noexcept
{
    if (this != &rhs)
	{
        for (size_t i = 0; i < row_num; i++)
            for (size_t j = 0; j < row_num; j++)
                m[i][j] += rhs.m[i][j];
	}
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            m[i][j] += rhs.m[i][j];
    return *this;    
}

Matrix& Matrix::operator-=(const Matrix& rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            m[i][j] -= rhs.m[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            m[i][j] *= rhs.m[i][j];
    return *this;      
}

Matrix& Matrix::operator/=(float rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            m[i][j] = m[i][j] / rhs;
    return *this;
}

Matrix& Matrix::operator*=(float rhs) noexcept
{
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            m[i][j] = m[i][j] * rhs;
    return *this;
}

Matrix Matrix::operator-() const noexcept
{
    auto tmp = Matrix(*this);
    for (size_t i = 0; i < row_num; i++)
        for (size_t j = 0; j < row_num; j++)
            tmp.m[i][j] = -m[i][j];
    return tmp;
}
}