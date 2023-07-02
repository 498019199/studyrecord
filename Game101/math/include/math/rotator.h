#pragma once

struct rotator
{
public:
    float pitch = 0.f;
    float yaw = 0.f;
    float roll = 0.f;

public:
    // (0, 0, 0)
    static rotator zero_rotator;
};