#pragma once

namespace MathWorker
{

struct Rotator
{
public:
    float pitch = 0.f;
    float yaw = 0.f;
    float roll = 0.f;

public:
    // (0, 0, 0)
    static Rotator ZeroRotator;

public:
    explicit Rotator(float in_x, float in_y, float in_z)
        :pitch(in_x), yaw(in_y), roll(in_z) {}
};
}