#include <render/camera_control.h>
#include <math/math.h>
using namespace MathWorker;
namespace RenderWorker
{

void FirstPersonCameraController::AttachCamera(Camera& cam)
{
    cam_ = &cam;
}

void FirstPersonCameraController::DetachCamera()
{
    cam_ = nullptr;
}

void FirstPersonCameraController::Move(float x, float y, float z)
{
    float3 movement(x, y, z);
    
}

void FirstPersonCameraController::Rotate(float yaw, float pitch, float roll)
{
    

}

}