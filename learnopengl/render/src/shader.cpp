#include <render/shader.h>
#include <glad/glad.h>
#include <iostream>

i_shader::~i_shader()
{
    glDeleteShader(shader_id_);
}

void i_shader::init_shader(int type)
{
    shader_type_ = type;
    shader_id_ = glCreateShader(shader_type_);
}

void i_shader::bind_shader(const char* shader_script)
{
    glShaderSource(shader_id_, 1, shader_script, NULL); // 把这个着色器源码附加到着色器对象。着色器对象，源码字符串数量，VS真正的源码
    glCompileShader(shader_id_);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << get_shader_type() << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void i_shader::link_shader()
{
    int shaderProgram = glCreateProgram(); // shaderProgram 是多个着色器合并之后并最终链接完成的版本
    glAttachShader(shaderProgram, shader_id_); // 附加
    // glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shader_id_);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

const char* i_shader::get_shader_type()
{
    if (GL_FRAGMENT_SHADER == shader_type_)
    {
        return "FRAGMENT";
    }
    return "VERTEX";
}