#pragma once
#include <utility>
#include <cstdint>
#include <iostream>
namespace MathWorker
{

class Vector3D
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
public:
    // static const Vector3D ForwardVector(0.f, 0.f, 1.f);
    // static const Vector3D BackVector(0, 0.f, -1.f);
    // static const Vector3D UpVector(0.f, 1.f, 0.f);
    // static const Vector3D DownVector(0.f,-1.f, 0.f);
    // static const Vector3D LeftVector(-1.f, 0.f, 0.f);
    // static const Vector3D RightVector(1.f, 0.f, 0.f);
    // static const Vector3D ZeroVector(0.f, 0.f, 0.f);
    
public:
    // 构造
    constexpr Vector3D() noexcept
    {
    }
    constexpr Vector3D(float in_x, float in_y, float in_z) noexcept
        :x(in_x), y(in_y), z(in_z) {}
    Vector3D(const Vector3D& vec) noexcept
        :x(vec.x), y(vec.y), z(vec.z) {}
    constexpr explicit Vector3D(float inf) noexcept
        :x(inf), y(inf), z(inf) {}
    explicit Vector3D(const Vector3D&& vec) noexcept
        :x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)) {}
    explicit Vector3D(Vector3D* vec) noexcept
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

    bool operator==(const  Vector3D& rhs) const;
    bool operator!=(const  Vector3D& rhs) const;

    // show info x y z
    friend std::ostream& operator<<(std::ostream& os, const  Vector3D& lhs);

    bool IsZero() const;
    Vector3D Normalize();
    Vector3D Cross(const Vector3D& rhs);
    float Dot(const Vector3D& rhs);
    
    // 模
    static float Norm(const Vector3D& lsh);
    static Vector3D Normalize(const Vector3D& rhs);
    static Vector3D Cross(const  Vector3D& lhs, const Vector3D& rhs);
    static float Dot(const  Vector3D& lhs, const Vector3D& rhs);
    float Distance(const  Vector3D& lhs, const Vector3D& rhs);
    // 返回由两个向量的最大分量组成的向量。
    static Vector3D Min(const Vector3D& lhs, const Vector3D& rhs);
    // 返回由两个向量的最小分量组成的向量。
    static Vector3D  Max(const Vector3D& lhs, const Vector3D& rhs);
};

inline Vector3D operator/(float lhs, const Vector3D& rhs)
{
    return rhs.operator/(lhs);
}

inline Vector3D operator*(float lhs, const Vector3D& rhs)
{
    return rhs.operator*(lhs);
}
}