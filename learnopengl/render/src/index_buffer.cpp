#include <render/index_buffer.h>
#include <glad/glad.h>

void IndexBuffer::Bind(void* data, int size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_); //缓冲绑定到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// 顶点数据复制到缓冲的内存中
}

void IndexBuffer::UnBind()
{
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id_);
}
