#pragma
#include <utility>

class vector2
{
public:
    float x;
    float y;

    // 构造
    vector2() noexcept {}
    vector2(vector2* vec) noexcept :x(vec->x),y(vec->y) {}
    vector2(vector2& vec) noexcept :x(vec.x),y(vec.y) {}
    vector2(vector2&& vec) noexcept :x(vec.x),y(vec.y) {}
    vector2(const vector2* vec) noexcept :x(vec->x),y(vec->y) {}
    vector2(const vector2& vec) noexcept :x(vec.x),y(vec.y) {}

    vector2(float _x, float _y) noexcept :x(_x),y(_y) {}
    vector2(float& _x, float& _y) noexcept :x(_x),y(_y) {}
    vector2(const float& _x, const float& _y) noexcept :x(_x),y(_y) {}
    vector2(float&& _x, float&& _y) noexcept :x(std::move(_x)),y(std::move(_y)) {}

    // 复制构造
    vector2& operator=(vector2& rhs) noexcept 
    {}

    vector2& operator=(vector2&& rhs) noexcept 
    {}

    const vector2& operator+=(const  vector2& rhs) noexcept;
    const vector2& operator-=(const  vector2& rhs) noexcept;
    const vector2& operator*=(const  vector2& rhs) noexcept;
    const vector2& operator/=(const  vector2& rhs) noexcept;

    bool operator==(const  vector2& rhs) const noexcept;
    bool operator!=(const  vector2& rhs) const noexcept;

    // 向量标准化
    void normalize() noexcept;
    vector2 normalize() const noexcept;

    // 距离
    static float distance(const  vector2& lhs, const vector2& rhs) noexcept;
    static float distance(const vector2& rhs) noexcept;

    // 叉积
    static void cross(const vector2& rhs) noexcept;
    static void cross(const  vector2& lhs, const vector2& rhs) noexcept;

    // 点积
    static float dot(const vector2& rhs) noexcept;
    static float dot(const  vector2& lhs, const vector2& rhs) noexcept;
};

inline vector2& operator+(const  vector2& lhs, const  vector2& rhs) noexcept;
{
    return lhs.operator+=(rhs);
}

inline vector2& operator-(const  vector2& lhs, const  vector2& rhs) noexcept;
{
    return lhs.operator!-=(rhs);
}

inline vector2& operator*(const  vector2& lhs, const  vector2& rhs) noexcept;
{
    return lhs.operator*=(rhs);
}

inline vector2& operator/(const  vector2& lhs, const  vector2& rhs) noexcept;
{
    return lhs.operator/=(rhs);
}

inline bool operator==(const  vector2& lhs, const  vector2& rhs) noexcept;
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector2& lhs, const  vector2& rhs) noexcept
{
    return lhs.operator!=(rhs);
}