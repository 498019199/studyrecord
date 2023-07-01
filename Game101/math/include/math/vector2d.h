#pragma once
#include <utility>

class vector2d
{
public:
    float x = 0.f;
    float y = 0.f;

public:
    static const vector2d zero_vector;
    static const vector2d unit_vector;
public:
    // 构造
    vector2d() noexcept 
        {}
    vector2d(float in_x, float in_y) noexcept 
        :x(in_x),y(in_y) {}
    explicit vector2d(float inf) noexcept 
        :x(inf),y(inf) {}
    explicit vector2d(const vector2d& vec) noexcept 
        :x(vec.x),y(vec.y) {}
    explicit vector2d(const vector2d&& vec) noexcept 
        :x(vec.x),y(vec.y) {}
    explicit vector2d(vector2d* vec) noexcept 
        :x(vec->x),y(vec->y) {}
    //vector2d(std::initializer_list<float> list) noexcept

    // 复制构造
    vector2d& operator=(vector2d* rhs) noexcept 
    {
        if (this != rhs)
        {
            this->x = rhs->x;
            this->y = rhs->y;
        }
        return *this;        
    }
    vector2d& operator=(vector2d& rhs) noexcept 
    {
        if (this != &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
        }
        return *this;
    }
    vector2d& operator=(vector2d&& rhs) noexcept 
    {
        if (this != &rhs)
        {
            this->x = std::move(rhs.x);
            this->y = std::move(rhs.y);
        }
        return *this;
    }

    vector2d operator+(const  vector2d& rhs) const noexcept;
    vector2d operator-(const  vector2d& rhs) const noexcept;
    vector2d operator*(float rhs) const noexcept;
    vector2d operator/(float rhs) const noexcept;

    bool operator==(const  vector2d& rhs) const noexcept;
    bool operator!=(const  vector2d& rhs) const noexcept;

    // 向量标准化
    void normalize() noexcept;
    static vector2d normalize(const vector2d& rhs) noexcept;

    // 距离
    float distance(const vector2d& rhs) noexcept;
    static float distance(const  vector2d& lhs, const vector2d& rhs) noexcept;

    // 叉积
    void cross(const vector2d& rhs) noexcept;
    static void cross(const  vector2d& lhs, const vector2d& rhs) noexcept;

    // 点积
    float dot(const vector2d& rhs) noexcept;
    static float dot(const  vector2d& lhs, const vector2d& rhs) noexcept;
};


inline bool operator==(const  vector2d& lhs, const  vector2d& rhs) noexcept
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector2d& lhs, const  vector2d& rhs) noexcept
{
    return lhs.operator!=(rhs);
}