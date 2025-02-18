#include <core/common.h>
#include <core/SceneNode.h>

namespace RenderWorker
{
class Camera:public SceneNode
{
public:
    Camera();
    
    const float3& EyePos() const;
    float3 LookAt() const;
    const float3& RightVec() const;
    const float3& UpVec() const;
    const float3& ForwardVec() const;

    float FOV() const
    { 
        return fov_; 
    }
    float Aspect() const
    { 
        return aspect_; 
    }
    float NearPlane() const
    { 
        return near_plane_; 
    }
    float FarPlane() const
    { 
        return far_plane_; 
    
    }
    // 设置摄像机的投射矩阵
	//////////////////////////////////////////////////////////////////////////////////
	void ProjParams(float fov, float aspect, float near_plane, float far_plane);
    void ProjOrthoParams(float w, float h, float near_plane, float far_plane);
private:
    float		fov_;
    float		aspect_;
    float		near_plane_;
    float		far_plane_;

    float4x4	proj_mat_;    // 透视矩阵
    float4x4    inv_proj_mat_;
    // 视口矩阵
};
using CameraPtr = std::shared_ptr<Camera>;

}