#pragma once
#include <utility>

class vector2
{
public:
    float x;
    float y;

public:
    // 构造
    vector2() noexcept 
        {}
    vector2(vector2* vec) noexcept 
        :x(vec->x),y(vec->y) {}
    vector2(vector2& vec) noexcept 
        :x(vec.x),y(vec.y) {}
    vector2(vector2&& vec) noexcept 
        :x(vec.x),y(vec.y) {}
    vector2(const vector2* vec) noexcept 
        :x(vec->x),y(vec->y) {}
    vector2(const vector2& vec) noexcept 
        :x(vec.x),y(vec.y) {}
    //vector2(std::initializer_list<float> list) noexcept
    vector2(float _x, float _y) noexcept 
        :x(_x),y(_y) {}
    vector2(float& _x, float& _y) noexcept 
        :x(_x),y(_y) {}
    vector2(const float& _x, const float& _y) noexcept 
        :x(_x),y(_y) {}
    vector2(float&& _x, float&& _y) noexcept 
        :x(std::move(_x)),y(std::move(_y)) {}

    // 复制构造
    vector2& operator=(vector2* rhs) noexcept 
    {
        if (this != rhs)
        {
            this->x = rhs->x;
            this->y = rhs->y;
        }
        return *this;        
    }
    vector2& operator=(vector2& rhs) noexcept 
    {
        if (this != &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
        }
        return *this;
    }
    vector2& operator=(vector2&& rhs) noexcept 
    {
        if (this != &rhs)
        {
            this->x = std::move(rhs.x);
            this->y = std::move(rhs.y);
        }
        return *this;
    }

    const vector2& operator+=(const  vector2& rhs) noexcept;
    const vector2& operator-=(const  vector2& rhs) noexcept;
    const vector2& operator*=(const  vector2& rhs) noexcept;
    const vector2& operator*=(float rhs) noexcept;
    const vector2& operator/=(float rhs) noexcept;

    bool operator==(const  vector2& rhs) const noexcept;
    bool operator!=(const  vector2& rhs) const noexcept;

    // 向量标准化
    void normalize() noexcept;
    static const vector2& normalize(const vector2& rhs) noexcept;

    // 距离
    float distance(const vector2& rhs) noexcept;
    static float distance(const  vector2& lhs, const vector2& rhs) noexcept;

    // 叉积
    void cross(const vector2& rhs) noexcept;
    static void cross(const  vector2& lhs, const vector2& rhs) noexcept;

    // 点积
    float dot(const vector2& rhs) noexcept;
    static float dot(const  vector2& lhs, const vector2& rhs) noexcept;
};

inline vector2& operator+(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator+=(rhs);
}

inline vector2& operator-(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator-=(rhs);
}

inline vector2& operator*(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator*=(rhs);
}

inline bool operator==(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator!=(rhs);
}