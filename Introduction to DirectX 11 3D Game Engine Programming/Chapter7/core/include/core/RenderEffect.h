#pragma once
#include <core/common.h>

class RenderEffect
{
public:
    struct VSConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };
private:
};