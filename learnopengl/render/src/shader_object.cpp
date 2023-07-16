#include <common/file.h>

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

void ShaderObject::SetBool(const char*name,  bool value) const
{
    glUniform1i(glGetUniformLocation(obj_id_, name), (int)value); 
}

void ShaderObject::SetInt(const char*name, int value) const
{
    glUniform1i(glGetUniformLocation(obj_id_, name), value); 
}

void ShaderObject::SetFloat(const char*name, float value) const
{
    glUniform1f(glGetUniformLocation(obj_id_, name), value); 
}
