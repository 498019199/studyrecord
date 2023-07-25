#pragma once
#include <iostream>

namespace MathWorker
{

class Matrix
{
    enum  { row_num = 4, col_num = 4};
	enum  { elem_num = row_num * col_num };
public:
    union 
    {
        struct 
        {
            float _11; float _12; float _13; float _14;
            float _21; float _22; float _23; float _24;
            float _31; float _32; float _33; float _34;
            float _41; float _42; float _43; float _44;
        };
        
        float m[4][4];
    };
    
public:
    Matrix()
    {}
	explicit Matrix(const float* rhs) noexcept;
	Matrix(const Matrix& rhs) noexcept;
    Matrix(Matrix&& rhs) noexcept;
    Matrix(float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44) noexcept;

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