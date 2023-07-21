#pragma once    
#include <math/math.h>

class Camera
{
public:
    Camera();
    ~Camera();

private:
    MathWorker::Matrix mvp_;
    MathWorker::Vector3D postion_;
};