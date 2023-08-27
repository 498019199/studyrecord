#include <common/file.h>
#include <math/vectorxd.h>
#include <math/matrix.h>

#include <render/shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace RenderWorker
{

ShaderObject::ShaderObject()
{
    obj_id_ = glCreateProgram();
    pixel_ = std::make_shared<PixelShader>();
    fragment_ = std::make_shared<FragmentShader>();
}

ShaderObject::~ShaderObject()
{
    DetachShader();
}

void ShaderObject::LoadShader(const std::string_view& vertexPath, const std::string_view& fragmentPath)
{
    std::string vertexShader = CommonWorker::GetFileContents(vertexPath.data());
    pixel_->InitShader(GL_VERTEX_SHADER);
    pixel_->BindShader(vertexShader.c_str());

    std::string fragmentShader = CommonWorker::GetFileContents(fragmentPath.data());
    fragment_->InitShader(GL_FRAGMENT_SHADER);
    fragment_->BindShader(fragmentShader.c_str());
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


void ShaderObject::Uniform1i(const char*name, int value) const
{
    glUniform1i(glGetUniformLocation(obj_id_, name), value); 
}

void ShaderObject::Uniform1f(const char*name, float value) const
{
    glUniform1f(glGetUniformLocation(obj_id_, name), value); 
}

void ShaderObject::Uniform3fv(const char*name, const MathWorker::float3& vec) const
{
    glUniform3fv(glGetUniformLocation(obj_id_, name), 1, vec.data()); 
}

void ShaderObject::UniformMatrix4fv(const char*name, const MathWorker::float4x4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(obj_id_, name), 1, GL_FALSE, mat.data());  
}

}