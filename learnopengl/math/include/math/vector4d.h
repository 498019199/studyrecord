#pragma once
#include <utility>
#include <cstdint>
#include <iostream>

struct vector4d
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;
public:
    // (0, 0, 0, 0)
    static const vector4d zero_vector;
    // (1, 1, 1, 1)
    static const vector4d unit_vector;
    
public:
    // 构造
    vector4d() 
        {}
    vector4d(float in_x, float in_y, float in_z, float in_w) 
        :x(in_x), y(in_y), z(in_z), w(in_w) {}
    vector4d(const vector4d& vec) 
        :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    explicit vector4d(float inf) 
        :x(inf), y(inf), z(inf), w(inf) {}
    explicit vector4d(const vector4d&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)), w(std::move(vec.w)) {}
    explicit vector4d(vector4d* vec) 
        :x(vec->x), y(vec->y), z(vec->z), w(vec->w) {}

    // 复制构造
    vector4d& operator=(const vector4d& rhs); 
    vector4d& operator=(const vector4d&& rhs);

    vector4d operator-() const;
    float operator[](int32_t index) const;
    vector4d operator+(const  vector4d& rhs) const;
    vector4d operator-(const  vector4d& rhs) const;
    vector4d operator*(const  vector4d& rhs) const;
    vector4d operator/(const  vector4d& rhs) const;
    vector4d operator*(float rhs) const;
    vector4d operator/(float rhs) const;
    float operator|(const vector4d& rhs) const;
    vector4d operator^(const vector4d& rhs) const;

    vector4d operator+=(const  vector4d& rhs);
    vector4d operator-=(const  vector4d& rhs);
    vector4d operator*=(const  vector4d& rhs);
    vector4d operator/=(const  vector4d& rhs);
    vector4d operator*=(float rhs);
    vector4d operator/=(float rhs);

    bool is_zero() const;
    bool operator==(const  vector4d& rhs) const;
    bool operator!=(const  vector4d& rhs) const;

    // 向量标准化
    void normalize();
    static vector4d normalize(const vector4d& rhs);

    // 距离
    static float distance(const  vector4d& lhs, const vector4d& rhs);

    // 叉积
    vector4d cross(const vector4d& rhs);
    static vector4d cross(const  vector4d& lhs, const vector4d& rhs);

    // 点积
    float dot(const vector4d& rhs);
    static float dot(const  vector4d& lhs, const vector4d& rhs);

    friend std::ostream& operator<<(std::ostream& os, const  vector4d& lhs) 
    {
        os << lhs.x << " " << lhs.y << " " << lhs.z << " " << lhs.w;
        return os;
    }
};

inline vector4d operator/(float lhs, const vector4d& rhs)
{
    return rhs.operator/(rhs);
}

inline vector4d operator*(float lhs, const vector4d& rhs)
{
    return rhs.operator*(rhs);
}

inline bool operator==(const  vector4d& lhs, const  vector4d& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector4d& lhs, const  vector4d& rhs)
{
    return lhs.operator!=(rhs);
}


