#include <render/index_buffer.h>
#include <glad/glad.h>

void index_buffer::bind(void* data, int size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_); //缓冲绑定到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// 顶点数据复制到缓冲的内存中
}

void index_buffer::unbind()
{
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

index_buffer::~index_buffer()
{
    glDeleteBuffers(1, &id_);
}
