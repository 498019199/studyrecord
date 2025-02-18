#include <core/Control.h>

namespace RenderWorker
{
FirstPersonController::FirstPersonController()
    : rotationScaler_(0.05f), moveScaler_(1), camera_(nullptr)
{
}

FirstPersonController::~FirstPersonController() noexcept  = default;

void FirstPersonController::AttachCamera(const CameraPtr&  camera)
{
    camera_ = camera;
}

void FirstPersonController::DetachCamera()
{
    camera_ = nullptr;
}

void FirstPersonController::Move(float x, float y, float z)
{
    if (camera_)
    {
        float3 movement(x, y, z);
        movement *= moveScaler_;
    }
}

void FirstPersonController::RotateRel(float yaw, float pitch, float roll)
{
    
}

void FirstPersonController::RotateAbs(const quater& quat)
{
    
}
}