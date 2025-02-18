#include <render/Camera.h>

namespace RenderWorker
{
class FirstPersonController
{
public:
    FirstPersonController();
    ~FirstPersonController() noexcept;
    
    void AttachCamera(const CameraPtr& camera);
    void DetachCamera();

    void Move(float x, float y, float z);
    void RotateRel(float yaw, float pitch, float roll);
    void RotateAbs(const quater& quat);
private:
    CameraPtr   camera_;

    float		rotationScaler_;	// Scaler for rotation
    float		moveScaler_;		// Scaler for movement

    float2		rot_x_;
    float2		rot_y_;
    float2		rot_z_;
};

}