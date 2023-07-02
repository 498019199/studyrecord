#pragma once

struct quaternion
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;

public:
    // (0, 0, 0, 0)
    static quaternion zero_quat;
};