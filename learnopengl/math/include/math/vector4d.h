#pragma once
#include <utility>
#include <cstdint>
#include <iostream>
namespace MathWorker
{

class Vector4D
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;
public:
    // (0, 0, 0, 0)
    static const Vector4D zero_vector;
    // (1, 1, 1, 1)
    static const Vector4D unit_vector;
    
public:
    // 构造
    Vector4D() 
        {}
    Vector4D(float in_x, float in_y, float in_z, float in_w) 
        :x(in_x), y(in_y), z(in_z), w(in_w) {}
    Vector4D(const Vector4D& vec) 
        :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    explicit Vector4D(float inf) 
        :x(inf), y(inf), z(inf), w(inf) {}
    explicit Vector4D(const Vector4D&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)), w(std::move(vec.w)) {}
    explicit Vector4D(Vector4D* vec) 
        :x(vec->x), y(vec->y), z(vec->z), w(vec->w) {}

    // 复制构造
    Vector4D& operator=(const Vector4D& rhs); 
    Vector4D& operator=(const Vector4D&& rhs);

    Vector4D operator-() const;
    float operator[](int32_t index) const;
    Vector4D operator+(const  Vector4D& rhs) const;
    Vector4D operator-(const  Vector4D& rhs) const;
    Vector4D operator*(const  Vector4D& rhs) const;
    Vector4D operator/(const  Vector4D& rhs) const;
    Vector4D operator*(float rhs) const;
    Vector4D operator/(float rhs) const;
    float operator|(const Vector4D& rhs) const;
    Vector4D operator^(const Vector4D& rhs) const;

    Vector4D operator+=(const  Vector4D& rhs);
    Vector4D operator-=(const  Vector4D& rhs);
    Vector4D operator*=(const  Vector4D& rhs);
    Vector4D operator/=(const  Vector4D& rhs);
    Vector4D operator*=(float rhs);
    Vector4D operator/=(float rhs);

    bool operator==(const  Vector4D& rhs) const;
    bool operator!=(const  Vector4D& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const  Vector4D& lhs); 

    bool IsZero() const;
    void Normalize();
    Vector4D Cross(const Vector4D& rhs);
    float Dot(const Vector4D& rhs);

    // 模
    static float Norm(const Vector4D& lhs);
    static Vector4D Normalize(const Vector4D& rhs);
    static Vector4D Cross(const  Vector4D& lhs, const Vector4D& rhs);
    static float Dot(const  Vector4D& lhs, const Vector4D& rhs);
    float Distance(const  Vector4D& lhs, const Vector4D& rhs);
    // 返回由两个向量的最大分量组成的向量。
    static Vector4D Min(const Vector4D& lhs, const Vector4D& rhs);
    // 返回由两个向量的最小分量组成的向量。
    static Vector4D  Max(const Vector4D& lhs, const Vector4D& rhs);
};

inline Vector4D operator/(float lhs, const Vector4D& rhs)
{
    return rhs.operator/(rhs);
}

inline Vector4D operator*(float lhs, const Vector4D& rhs)
{
    return rhs.operator*(rhs);
}

}