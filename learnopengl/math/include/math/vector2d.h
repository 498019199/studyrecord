#pragma once
#include <utility>
#include <cstdint>
#include <iostream>
namespace MathWorker
{
struct Vector2D
{
public:
    float x = 0.f;
    float y = 0.f;

public:
    static const Vector2D Zero;

public:
    //构造
    Vector2D() 
        {}
    Vector2D(float in_x, float in_y) 
        :x(in_x), y(in_y) {}
    Vector2D(const Vector2D& vec) 
        :x(vec.x), y(vec.y) {}
    explicit Vector2D(float inf) 
        :x(inf), y(inf) {}
    explicit Vector2D(const Vector2D&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)) {}
    explicit Vector2D(Vector2D* vec) 
        :x(vec->x), y(vec->y) {}
    //Vector2D(std::initializer_list<float> list); 

    Vector2D& operator=(const Vector2D& rhs); 
    Vector2D& operator=(const Vector2D&& rhs);

    Vector2D operator-() const;
    float operator[](int32_t index) const;
    Vector2D operator+(const  Vector2D& rhs) const;
    Vector2D operator-(const  Vector2D& rhs) const;
    Vector2D operator*(const  Vector2D& rhs) const;
    Vector2D operator/(const  Vector2D& rhs) const;
    Vector2D operator*(float rhs) const;
    Vector2D operator/(float rhs) const;
    float operator|(const Vector2D& rhs) const;
    float operator^(const Vector2D& rhs) const;

    Vector2D operator+=(const  Vector2D& rhs);
    Vector2D operator-=(const  Vector2D& rhs);
    Vector2D operator*=(const  Vector2D& rhs);
    Vector2D operator/=(const  Vector2D& rhs);
    Vector2D operator*=(float rhs);
    Vector2D operator/=(float rhs);

    friend std::ostream& operator<<(std::ostream& os, const  Vector2D& lhs); 

    bool operator==(const  Vector2D& rhs) const;
    bool operator!=(const  Vector2D& rhs) const;

    bool IsZero() const;
    void Normalize();
    float Cross(const Vector2D& rhs);
    float Dot(const Vector2D& rhs);

    // 模
    static float Norm(const Vector2D& lhs);
    // 标准化
    static Vector2D Normalize(const Vector2D& lhs);
    // 叉积
    static float Cross(const  Vector2D& lhs, const Vector2D& rhs);
    // 点积
    static float Dot(const  Vector2D& lhs, const Vector2D& rhs);
    // 距离
    static float Distance(const  Vector2D& lhs, const Vector2D& rhs);
    // 返回由两个向量的最大分量组成的向量。
    static Vector2D Min(const Vector2D& lhs, const Vector2D& rhs);
    // 返回由两个向量的最小分量组成的向量。
    static Vector2D  Max(const Vector2D& lhs, const Vector2D& rhs);
};

inline Vector2D operator/(float lhs, const Vector2D& rhs)
{
    return rhs.operator/(rhs);
}

inline Vector2D operator*(float lhs, const Vector2D& rhs)
{
    return rhs.operator*(rhs);
}

}