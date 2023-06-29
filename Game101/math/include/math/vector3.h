#pragma
#include <utility>

class vector3
{
public:
    float x;
    float y;
    float z;

    vector3() noexcept {}
    vector3(vector3* vec) noexcept :x(vec->x),y(vec->y),z(vec->z) {}
    vector3(vector3& vec) noexcept :x(vec.x),y(vec.y),z(vec.z) {}
    vector3(vector3&& vec) noexcept :x(vec.x),y(vec.y),z(vec.z) {}
    vector3(const vector3* vec) noexcept :x(vec->x),y(vec->y),z(vec->z) {}
    vector3(const vector3& vec) noexcept :x(vec.x),y(vec.y),z(vec.z) {}

    vector3(float _x, float _y, float _z) noexcept :x(_x),y(_y),z(_z) {}
    vector3(float& _x, float& _y, float& _z) noexcept :x(_x),y(_y),z(_z) {}
    vector3(const float& _x, const float& _y, const float& _z) noexcept :x(_x),y(_y),z(_z) {}
    vector3(float&& _x, float&& _y, float&& _z) noexcept :x(std::move(_x)),y(std::move(_y)),z(std::move(_z)) {}

    const vector3& operator+=(const  vector3& rhs) noexcept;
    const vector3& operator-=(const  vector3& rhs) noexcept;
    const vector3& operator*=(const  vector3& rhs) noexcept;
    const vector3& operator/=(const  vector3& rhs) noexcept;

    bool operator==(const  vector3& rhs) const noexcept;
    bool operator!=(const  vector3& rhs) const noexcept;

    // 向量标准化
    void normalize() noexcept;
    vector3 normalize() const noexcept;

    // 距离
    static float distance(const  vector3& lhs, const vector3& rhs) noexcept;
    static float distance(const vector3& rhs) noexcept;

    // 叉积
    static void cross(const vector3& rhs) noexcept;
    static void cross(const  vector3& lhs, const vector3& rhs) noexcept;

    // 点积
    static float dot(const vector3& rhs) noexcept;
    static float dot(const  vector3& lhs, const vector3& rhs) noexcept;
};

inline vector3& operator+(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator+=(rhs);
}

inline vector3& operator-(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator!-=(rhs);
}

inline vector3& operator*(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator*=(rhs);
}

inline vector3& operator/(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator/=(rhs);
}

inline bool operator==(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector3& lhs, const  vector3& rhs) noexcept
{
    return lhs.operator!=(rhs);
}