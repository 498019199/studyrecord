#include <render/shader.h>
#include <glad/glad.h>

shader_object::shader_object()
{
    //obj_id_ = glCreateProgram();
}

shader_object::~shader_object()
{
    
}

void shader_object::init()
{
    obj_id_ = glCreateProgram();
}

void shader_object::attach_shader()
{
    glAttachShader(obj_id_, pixel_->get_shader_id());
    int success;
    char infoLog[512];
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
    }

    glAttachShader(obj_id_, fragment_->get_shader_id());
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
    }

    glLinkProgram(obj_id_);
}

void shader_object::use_shader()
{
    glUseProgram(obj_id_);
}

void shader_object::detach_shader()
{
    glDeleteShader(pixel_->get_shader_id());
    glDeleteShader(fragment_->get_shader_id());
}