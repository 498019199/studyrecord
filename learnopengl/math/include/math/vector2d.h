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
    static const Vector2D zero_vector;
    static const Vector2D unit_vector;
    
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

    bool IsZero() const;
    bool operator==(const  Vector2D& rhs) const;
    bool operator!=(const  Vector2D& rhs) const;

    void Normalize();
    static Vector2D Normalize(const Vector2D& rhs);

    float Cross(const Vector2D& rhs);
    static float Cross(const  Vector2D& lhs, const Vector2D& rhs);

    float Dot(const Vector2D& rhs);
    static float Dot(const  Vector2D& lhs, const Vector2D& rhs);
};

inline Vector2D operator/(float lhs, const Vector2D& rhs)
{
    return rhs.operator/(rhs);
}

inline Vector2D operator*(float lhs, const Vector2D& rhs)
{
    return rhs.operator*(rhs);
}

inline bool operator==(const  Vector2D& lhs, const  Vector2D& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  Vector2D& lhs, const  Vector2D& rhs)
{
    return lhs.operator!=(rhs);
}

}