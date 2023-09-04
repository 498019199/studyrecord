#include <render/vertex_array.h>
#include <glad/glad.h>

namespace RenderWorker
{
VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vao_id_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vao_id_);
}

void VertexArray::Bind()
{
    // 1. 绑定VAO
    glBindVertexArray(vao_id_);
}

void VertexArray::UnBind()
{
    // 解绑VBO
    glBindVertexArray(0); 
}

}