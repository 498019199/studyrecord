#pragma once    
#include <math/math.h>
#include <math/matrix.h>

namespace RenderWorker
{

class Camera
{
public:
    Camera();
    ~Camera();

private:
    MathWorker::float4x4 mvp_;
    MathWorker::float3 postion_;
};

}