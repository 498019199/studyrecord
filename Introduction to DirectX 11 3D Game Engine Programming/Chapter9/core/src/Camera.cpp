#include <render/Camera.h>

namespace RenderWorker
{
Camera::Camera()
{
    ProjParams(MathWorker::PI / 4, 1, 1, 1000);
}

const float3& Camera::EyePos() const
{
    return float3(0, 0, 0);
}

float3 Camera::LookAt() const
{
    return float3(0, 0, 0);
}

const float3& Camera::RightVec() const
{
    return float3(0, 0, 0);
}

const float3& Camera::UpVec() const
{
    return float3(0, 0, 0);
}

const float3& Camera::ForwardVec() const
{
    return float3(0, 0, 0);
}

void Camera::ProjParams(float fov, float aspect, float near_plane, float far_plane)
{
    fov_		= fov;
    aspect_		= aspect;
    near_plane_	= near_plane;
    far_plane_	= far_plane;

    proj_mat_ = MathWorker::PerspectiveFovLH(fov, aspect, near_plane, far_plane);
    inv_proj_mat_ = MathWorker::Inverse(proj_mat_);
}

void Camera::ProjOrthoParams(float w, float h, float near_plane, float far_plane)
{
    fov_		= 0;
    aspect_		= w / h;
    near_plane_	= near_plane;
    far_plane_	= far_plane;

    proj_mat_ = MathWorker::OrthoLH(w, h, near_plane, far_plane);
    inv_proj_mat_ = MathWorker::Inverse(proj_mat_);
}

}