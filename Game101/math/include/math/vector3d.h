#pragma once
#include <utility>
#include <cstdint>

class vector3d
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
public:
    // (0,0,0)
    static const vector3d zero_vector;
    // (1,1,1)
    static const vector3d unit_vector;
public:
    // 构造
    vector3d() 
        {}
    vector3d(float in_x, float in_y, float in_z) 
        :x(in_x), y(in_y), z(in_z) {}
    vector3d(const vector3d& vec) 
        :x(vec.x), y(vec.y), z(vec.z) {}
    explicit vector3d(float inf) 
        :x(inf), y(inf), z(inf) {}
    explicit vector3d(const vector3d&& vec)  
        :x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)) {}
    explicit vector3d(vector3d* vec) 
        :x(vec->x), y(vec->y), z(vec->z) {}

    // 复制构造
    vector3d& operator=(const vector3d& rhs); 
    vector3d& operator=(const vector3d&& rhs);

    vector3d operator-() const;
    float operator[](int32_t index) const;
    vector3d operator+(const  vector3d& rhs) const;
    vector3d operator-(const  vector3d& rhs) const;
    vector3d operator*(const  vector3d& rhs) const;
    vector3d operator/(const  vector3d& rhs) const;
    vector3d operator*(float rhs) const;
    vector3d operator/(float rhs) const;
    float operator|(const vector3d& rhs) const;
    vector3d operator^(const vector3d& rhs) const;

    vector3d operator+=(const  vector3d& rhs);
    vector3d operator-=(const  vector3d& rhs);
    vector3d operator*=(const  vector3d& rhs);
    vector3d operator/=(const  vector3d& rhs);
    vector3d operator*=(float rhs);
    vector3d operator/=(float rhs);

    bool is_zero() const;
    bool operator==(const  vector3d& rhs) const;
    bool operator!=(const  vector3d& rhs) const;

    // 向量标准化
    void normalize();
    static vector3d normalize(const vector3d& rhs);

    // 距离
    static float distance(const  vector3d& lhs, const vector3d& rhs);

    // 叉积
    static vector3d cross(const  vector3d& lhs, const vector3d& rhs);

    // 点积
    static float dot(const  vector3d& lhs, const vector3d& rhs);
};


inline bool operator==(const  vector3d& lhs, const  vector3d& rhs)
{
    return lhs.operator==(rhs);
}

inline bool operator!=(const  vector3d& lhs, const  vector3d& rhs)
{
    return lhs.operator!=(rhs);
}