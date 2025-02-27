#include <core/Control.h>

namespace RenderWorker
{
Controller::Controller()
    :rotationScaler_(0.05f), moveScaler_(1), camera_(nullptr)
{
    
}

void Controller::Scalers(float rotationScaler, float moveScaler)
{
    rotationScaler_ = rotationScaler;
    moveScaler_ = moveScaler;
}

void Controller::AttachCamera(const CameraPtr&  camera)
{
    camera_ = camera;
}

void Controller::DetachCamera()
{
    camera_ = nullptr;
}

    


FirstPersonController::FirstPersonController()
{
}

FirstPersonController::~FirstPersonController() noexcept  = default;

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