#include <render/shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ShaderObject::ShaderObject()
{
    obj_id_ = glCreateProgram();
    pixel_ = std::make_shared<PixelShader>();
    fragment_ = std::make_shared<FragmentShader>();
}

ShaderObject::~ShaderObject()
{
    
}

void ShaderObject::InitShader(int type)
{
    if(GL_VERTEX_SHADER == type) 
        pixel_->InitShader(type); 
    else 
        fragment_->InitShader(type); 
}

void ShaderObject::AttachShader()
{
    glAttachShader(obj_id_, pixel_->GetShaderId());
    int success;
    char infoLog[512];
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
    }

    glAttachShader(obj_id_, fragment_->GetShaderId());
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
    }

    glLinkProgram(obj_id_);
}

void ShaderObject::UseShader()
{
    glUseProgram(obj_id_);
}

void ShaderObject::DetachShader()
{
    glDeleteShader(pixel_->GetShaderId());
    glDeleteShader(fragment_->GetShaderId());
}