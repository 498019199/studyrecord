#pragma once
#include <utility>
#include <cstdint>

struct vector2d
{
public:
    float x = 0.f;
    float y = 0.f;

public:
    static const vector2d zero_vector;
    static const vector2d unit_vector;
    
public:
    // 构造
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

    // 复制构造
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

    // 向量标准化
    void normalize();
    static vector2d normalize(const vector2d& rhs);

    // 距离
    static float distance(const  vector2d& lhs, const vector2d& rhs);

    // 叉积
    static float cross(const  vector2d& lhs, const vector2d& rhs);

    // 点积
    static float dot(const  vector2d& lhs, const vector2d& rhs);
};


inline bool operator==(const  vector2d& lhs, const  vector2d& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector2d& lhs, const  vector2d& rhs)
{
    return lhs.operator!=(rhs);
}