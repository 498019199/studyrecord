#include <render/Camere.h>

namespace RenderWorker
{
Camere::Camere()
{
    ProjParams(MathWorker::PI / 4, 1, 1, 1000);
}

const float3& Camere::EyePos() const
{
    
}

float3 Camere::LookAt() const
{
    
}

const float3& Camere::RightVec() const
{
    
}

const float3& Camere::UpVec() const
{
    
}

const float3& Camere::ForwardVec() const
{
    
}

void Camere::ProjParams(float fov, float aspect, float near_plane, float far_plane)
{
    fov_		= fov;
    aspect_		= aspect;
    near_plane_	= near_plane;
    far_plane_	= far_plane;

    proj_mat_ = MathWorker::PerspectiveFovLH(fov, aspect, near_plane, far_plane);
    inv_proj_mat_ = MathWorker::MatrixInverse(proj_mat_);
}

void Camere::ProjOrthoParams(float w, float h, float near_plane, float far_plane)
{
    fov_		= 0;
    aspect_		= w / h;
    near_plane_	= near_plane;
    far_plane_	= far_plane;

    proj_mat_ = MathWorker::OrthoLH(w, h, near_plane, far_plane);
    inv_proj_mat_ = MathWorker::MatrixInverse(proj_mat_);
}

}