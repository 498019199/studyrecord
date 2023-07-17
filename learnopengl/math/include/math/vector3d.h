#pragma once
#include <utility>
#include <cstdint>
#include <iostream>
namespace MathWorker
{

struct Vector3D
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
public:
    // (0,0,0)
    static const Vector3D zero_vector;
    // (1,1,1)
    static const Vector3D unit_vector;
    
public:
    // 构造
    Vector3D() 
        {}
    Vector3D(float in_x, float in_y, float in_z) 
        :x(in_x), y(in_y), z(in_z) {}
    Vector3D(const Vector3D& vec) 
        :x(vec.x), y(vec.y), z(vec.z) {}
    explicit Vector3D(float inf) 
        :x(inf), y(inf), z(inf) {}
    explicit Vector3D(const Vector3D&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)) {}
    explicit Vector3D(Vector3D* vec) 
        :x(vec->x), y(vec->y), z(vec->z) {}

    // 复制构造
    Vector3D& operator=(const Vector3D& rhs); 
    Vector3D& operator=(const Vector3D&& rhs);

    Vector3D operator-() const;
    float operator[](int32_t index) const;
    Vector3D operator+(const  Vector3D& rhs) const;
    Vector3D operator-(const  Vector3D& rhs) const;
    Vector3D operator*(const  Vector3D& rhs) const;
    Vector3D operator/(const  Vector3D& rhs) const;
    Vector3D operator*(float rhs) const;
    Vector3D operator/(float rhs) const;
    float operator|(const Vector3D& rhs) const;
    Vector3D operator^(const Vector3D& rhs) const;

    Vector3D operator+=(const  Vector3D& rhs);
    Vector3D operator-=(const  Vector3D& rhs);
    Vector3D operator*=(const  Vector3D& rhs);
    Vector3D operator/=(const  Vector3D& rhs);
    Vector3D operator*=(float rhs);
    Vector3D operator/=(float rhs);

    bool is_zero() const;
    bool operator==(const  Vector3D& rhs) const;
    bool operator!=(const  Vector3D& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const  Vector3D& lhs);

    // 向量标准化
    Vector3D normalize();
    static Vector3D normalize(const Vector3D& rhs);

    // 叉积
    Vector3D cross(const Vector3D& rhs);
    static Vector3D cross(const  Vector3D& lhs, const Vector3D& rhs);

    // 点积
    float dot(const Vector3D& rhs);
    static float dot(const  Vector3D& lhs, const Vector3D& rhs);
};

inline Vector3D operator/(float lhs, const Vector3D& rhs)
{
    return rhs.operator/(rhs);
}

inline Vector3D operator*(float lhs, const Vector3D& rhs)
{
    return rhs.operator*(rhs);
}

inline bool operator==(const  Vector3D& lhs, const  Vector3D& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  Vector3D& lhs, const  Vector3D& rhs)
{
    return lhs.operator!=(rhs);
}


}