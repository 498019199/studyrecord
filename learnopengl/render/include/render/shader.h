#pragma once
#include <memory>

class i_shader;
using ptr_shader = std::shared_ptr<i_shader>;

class i_shader
{
public:   
    ~i_shader();

    void init_shader(int type);
    void bind_shader(const char* shader_script);
    void link_shader();
private:
    const char* get_shader_type();

private:
    int shader_type_ = 0;
    int shader_id_ = 0;
};

// 像素着色器
class pixel_shader:public i_shader
{};

// 片元着色器
class fragment_shader:public i_shader
{};

// 着色器程序对象(Shader Program Object)
class shader_object
{
public:
    shader_object();
    ~shader_object();

    void attach_shader();
private:
    uint32_t obj_id_;
    ptr_shader pixel_;
    ptr_shader fragment_;
}


