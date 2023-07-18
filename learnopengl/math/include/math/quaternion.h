#pragma once

namespace MathWorker
{

struct Quaternion
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;

public:
    // (0, 0, 0, 0)
    static Quaternion ZeroQuat;

public:
    explicit Quaternion(float in_x, float in_y, float in_z, float in_w)
        :x(in_x), y(in_y), z(in_z), w(in_w) {}
};
}