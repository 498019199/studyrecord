#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
const float DEG2RAD = 0.01745329f;			// 角度化弧度因数
const float RAD2DEG = 57.29577f;			// 弧度化角度因数

inline float Deg2Rad(const float x) { return x * DEG2RAD; }
inline float Rad2Deg(const float x) {return x * RAD2DEG;}

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    // c++中三角函数是弧度制
    float fs = std::sin(Deg2Rad(rotation_angle));
    float fc = std::cos(Deg2Rad(rotation_angle));
    model(0, 0) = fc;
    model(0, 1) = -fs;
    model(1, 0) = fs;
    model(1, 1) = fc;
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
    Eigen::Matrix4f proj, ortho;
    proj << zNear, 0.f, 0.f,  0.f,
        0.f, zNear, 0.f,  0.f,
        0.f, 0.f, zNear+zFar,  -zNear*zFar,
        0.f, 0.f, 1.f,  0.f;
    float h = Deg2Rad(eye_fov*0.5f);
    float n = zNear, f=zFar;
    float t = -n * std::tan(h);
    float r = aspect_ratio * t;
    float l = -r;
    float b = -t;
    ortho << 2.f/(r-l), 0.f,        0.f,         -(r+l)/(r-l),
        0.f,            2.f/(t-b),  0.f,         -(t+b)/(t-b),
        0.f,            0.f,        2.f/(n-f),   -(n+f)/(n-f),
        0.f,            0.f,        1.f,         1.f;
    projection = proj * ortho;

    //Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f M_trans;
    Eigen::Matrix4f M_persp;
    Eigen::Matrix4f M_ortho;
    M_persp <<
        zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -zFar * zNear,
        0, 0, 1, 0;

    float alpha = 0.5 * eye_fov * MY_PI / 180.0f;
    float yTop = -zNear * std::tan(alpha); //因为这里的z给的是负数，所以加负号之后再转换
    float yBottom = -yTop;
    float xRight = yTop * aspect_ratio;
    float xLeft = -xRight;

    M_trans <<
        1, 0, 0, -(xLeft + xRight) / 2,
        0, 1, 0, -(yTop + yBottom) / 2,
        0, 0, 1, -(zNear + zFar) / 2,
        0, 0, 0, 1;
    M_ortho <<
        2 / (xRight - xLeft), 0, 0, 0,
        0, 2 / (yTop - yBottom), 0, 0,
        0, 0, 2 / (zNear - zFar), 0,
        0, 0, 0, 1;

    M_ortho = M_ortho * M_trans;
    projection = M_ortho * M_persp;
    return projection; 
}
