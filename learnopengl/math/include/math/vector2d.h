#pragma once
#include <utility>
#include <cstdint>
#include <iostream>

struct vector2d
{
public:
    float x = 0.f;
    float y = 0.f;

public:
    static const vector2d zero_vector;
    static const vector2d unit_vector;
    
public:
    //构造
    vector2d() 
        {}
    vector2d(float in_x, float in_y) 
        :x(in_x), y(in_y) {}
    vector2d(const vector2d& vec) 
        :x(vec.x), y(vec.y) {}
    explicit vector2d(float inf) 
        :x(inf), y(inf) {}
    explicit vector2d(const vector2d&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)) {}
    explicit vector2d(vector2d* vec) 
        :x(vec->x), y(vec->y) {}
    //vector2d(std::initializer_list<float> list); 

    vector2d& operator=(const vector2d& rhs); 
    vector2d& operator=(const vector2d&& rhs);

    vector2d operator-() const;
    float operator[](int32_t index) const;
    vector2d operator+(const  vector2d& rhs) const;
    vector2d operator-(const  vector2d& rhs) const;
    vector2d operator*(const  vector2d& rhs) const;
    vector2d operator/(const  vector2d& rhs) const;
    vector2d operator*(float rhs) const;
    vector2d operator/(float rhs) const;
    float operator|(const vector2d& rhs) const;
    float operator^(const vector2d& rhs) const;

    vector2d operator+=(const  vector2d& rhs);
    vector2d operator-=(const  vector2d& rhs);
    vector2d operator*=(const  vector2d& rhs);
    vector2d operator/=(const  vector2d& rhs);
    vector2d operator*=(float rhs);
    vector2d operator/=(float rhs);

    bool is_zero() const;
    bool operator==(const  vector2d& rhs) const;
    bool operator!=(const  vector2d& rhs) const;

    void normalize();
    static vector2d normalize(const vector2d& rhs);

    static float distance(const  vector2d& lhs, const vector2d& rhs);

    float cross(const vector2d& rhs);
    static float cross(const  vector2d& lhs, const vector2d& rhs);

    float dot(const vector2d& rhs);
    static float dot(const  vector2d& lhs, const vector2d& rhs);

    friend std::ostream& operator<<(std::ostream& os, const  vector2d& lhs) 
    {
        os << lhs.x << " " << lhs.y;
        return os;
    }
};

inline vector2d operator/(float lhs, const vector2d& rhs)
{
    return rhs.operator/(rhs);
}

inline vector2d operator*(float lhs, const vector2d& rhs)
{
    return rhs.operator*(rhs);
}

inline bool operator==(const  vector2d& lhs, const  vector2d& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector2d& lhs, const  vector2d& rhs)
{
    return lhs.operator!=(rhs);
}

