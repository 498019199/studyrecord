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

void FirstPersonController::AttachCamera(const CameraPtr& camera)
{
    float3 scale;
    float3 translation;
    quater quat;
    MathWorker::Decompose(scale, quat, translation, camera->TransformToParent());

    rotator rot = MathWorker::ToRotator(quat);

    MathWorker::SinCos(rot.pitch() / 2, rot_x_.x(), rot_x_.y());
    MathWorker::SinCos(rot.yaw() / 2, rot_y_.x(), rot_y_.y());
    MathWorker::SinCos(rot.roll() / 2, rot_z_.x(), rot_z_.y());

    Controller::AttachCamera(camera);
}

void FirstPersonController::DetachCamera()
{
    Controller::DetachCamera();
}

void FirstPersonController::Move(float x, float y, float z)
{
    if (camera_)
    {
        float3 movement(x, y, z);
        movement *= moveScaler_;
        camera_->TransformToWorld(MathWorker::Translation(movement) * camera_->TransformToParent());
    }
}

void FirstPersonController::RotateRel(float yaw, float pitch, float roll)
{
    
}

void FirstPersonController::RotateAbs(const quater& quat)
{
    
}
}