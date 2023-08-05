#pragma once
#include <iostream>
#include <common/micro.h>
namespace MathWorker
{

class Matrix
{
    enum  { row_num = 4, col_num = 4};
	enum  { elem_num = row_num * col_num };
public:
    union { 
        MS_ALIGN(16) float M[4][4]; 
    };
public:
    Matrix()
    {}
	Matrix(const Matrix& rhs) noexcept;
    Matrix(Matrix&& rhs) noexcept;
    Matrix(float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44) noexcept;

    float& operator()(uint32_t row, uint32_t col)noexcept
    {
        return M[row][col];
	}
    const float& operator()(uint32_t row, uint32_t col) const noexcept
    {
        return M[row][col];
    }

    Matrix& operator=(const Matrix& rhs) noexcept;
    Matrix& operator=(Matrix&& rhs) noexcept;
    
    Matrix& operator+(const Matrix& rhs) noexcept;
    Matrix& operator-(const Matrix& rhs) noexcept;
    Matrix& operator+=(const Matrix& rhs) noexcept;
    Matrix& operator-=(const Matrix& rhs) noexcept;
    
    Matrix& operator*=(const Matrix& rhs) noexcept;

    Matrix& operator*=(float rhs) noexcept;
    Matrix& operator/=(float rhs) noexcept;
    Matrix& operator*(float rhs) noexcept;
    Matrix& operator/(float rhs) noexcept;

    bool operator==(const Matrix& rhs) const noexcept;
    bool operator!=(const Matrix& rhs) const noexcept;


    friend std::ostream& operator<<(std::ostream& os, const  Matrix& lhs); 
};










}