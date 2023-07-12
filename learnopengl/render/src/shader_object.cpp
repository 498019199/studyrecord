#include <render/shader.h>
#include <glad/glad.h>

shader_object::shader_object()
{
    obj_id_ = glCreateProgram();
}

shader_object::~shader_object()
{
    
}

void shader_object::attach_shader()
{
    //glAttachShader(obj_id_, vertexShader);
    //glAttachShader(obj_id_, fragmentShader);
    glLinkProgram(obj_id_);
}