#include <render/shader.h>
#include <glad/glad.h>
#include <iostream>

shader::~shader()
{
    glDeleteShader(vertex_shader_);
}

void shader::init_shader(int type)
{
    shader_type_ = type;
    vertex_shader_ = glCreateShader(shader_type_);
}

void shader::bind_shader(const char* shader_script)
{
    glShaderSource(vertex_shader_, 1, shader_script, NULL); // 把这个着色器源码附加到着色器对象。着色器对象，源码字符串数量，VS真正的源码
    glCompileShader(vertex_shader_);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << get_shader_type() << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void shader::link_shader()
{
    int shaderProgram = glCreateProgram(); // shaderProgram 是多个着色器合并之后并最终链接完成的版本
    glAttachShader(shaderProgram, vertex_shader_); // 附加
    // glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(vertex_shader_);
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

const char* shader::get_shader_type()
{
    if (GL_FRAGMENT_SHADER == shader_type_)
    {
        return "FRAGMENT";
    }
    return "VERTEX";
}