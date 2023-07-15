#include <render/vertex_buffer.h>
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vbo_id_);
}

void VertexBuffer::Bind(void* data, int size)
{
    //创建VBO对象
    glGenBuffers(1, &vbo_id_);
    // 0. 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void VertexBuffer::UnBind()
{
}

