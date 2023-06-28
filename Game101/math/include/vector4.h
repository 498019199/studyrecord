#pragma

#pragma
#include <utility>

class vector4
{
public:
    float x;
    float y;
    float z;
    float o;

    vector4() noexcept
        {}
    vector4(vector4* vec) noexcept 
        :x(vec->x),y(vec->y),z(vec->z),o(vec->o) {}
    vector4(vector4& vec) noexcept 
        :x(vec.x),y(vec.y),z(vec.z),z(vec.o) {}
    vector4(vector4&& vec) noexcept 
        :x(vec.x),y(vec.y),z(vec.z),o(vec.o) {}
    vector4(const vector4* vec) noexcept 
        :x(vec->x),y(vec->y),z(vec->z),o(vec->o) {}
    vector4(const vector4& vec) noexcept 
        :x(vec.x),y(vec.y),z(vec.z),o(vec.o) {}

    vector4(float _x, float _y) noexcept 
        :x(_x),y(_y),z(_z),o(_o) {}
    vector4(float& _x, float& _y) noexcept 
        :x(_x),y(_y),z(_z),o(_o) {}
    vector4(const float& _x, const float& _y) noexcept 
        :x(_x),y(_y),z(_z),o(_o) {}
    vector4(float&& _x, float&& _y) noexcept 
        :x(std::move(_x)),y(std::move(_y)),z(std::move(_z)),o(std::move(_o)) {}

    const vector4& operator+=(const  vector4& rhs) noexcept;
    const vector4& operator-=(const  vector4& rhs) noexcept;
    const vector4& operator*=(const  vector4& rhs) noexcept;
    const vector4& operator/=(const  vector4& rhs) noexcept;

    bool operator==(const  vector4& rhs) const noexcept;
    bool operator!=(const  vector4& rhs) const noexcept;

    // 向量标准化
    void normalize() noexcept;
    vector4 normalize() const noexcept;

    // 距离
    static float distance(const  vector4& lhs, const vector4& rhs) noexcept;
    static float distance(const vector4& rhs) noexcept;

    // 叉积
    static void cross(const vector4& rhs) noexcept;
    static void cross(const  vector4& lhs, const vector4& rhs) noexcept;

    // 点积
    static float dot(const vector4& rhs) noexcept;
    static float dot(const  vector4& lhs, const vector4& rhs) noexcept;
};

inline vector4& operator+(const  vector4& lhs, const  vector4& rhs) noexcept;
{
    return lhs.operator+=(rhs);
}

inline vector4& operator-(const  vector4& lhs, const  vector4& rhs) noexcept;
{
    return lhs.operator!-=(rhs);
}

inline vector4& operator*(const  vector4& lhs, const  vector4& rhs) noexcept;
{
    return lhs.operator*=(rhs);
}

inline vector4& operator/(const  vector4& lhs, const  vector4& rhs) noexcept;
{
    return lhs.operator/=(rhs);
}

inline bool operator==(const  vector4& lhs, const  vector4& rhs) noexcept;
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector4& lhs, const  vector4& rhs) noexcept
{
    return lhs.operator!=(rhs);
}