#include <render/shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
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
    glAttachShader(obj_id_, fragment_->GetShaderId());
    glLinkProgram(obj_id_);

    int success;
    char infoLog[512];
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }   

    glDeleteShader(pixel_->GetShaderId());
    glDeleteShader(fragment_->GetShaderId());
}

void ShaderObject::UseShader()
{
    glUseProgram(obj_id_);
    int success;
    char infoLog[512];
    glGetProgramiv(obj_id_, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(obj_id_, 512, NULL, infoLog);
    }

}

void ShaderObject::DetachShader()
{
    glDeleteShader(pixel_->GetShaderId());
    glDeleteShader(fragment_->GetShaderId());
    glDeleteProgram(obj_id_);
}