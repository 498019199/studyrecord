#pragma once    
#include <render/camera.h>

namespace RenderWorker
{

class FirstPersonCameraController
{
public:
    void AttachCamera(Camera& cam);
    void DetachCamera();

    void Move(float x, float y, float z);
    void Rotate(float yaw, float pitch, float roll);
private:
    Camera* cam_;
};



}