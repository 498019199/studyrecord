#pragma once

namespace MathWorker
{

struct Matrix
{
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
};


}