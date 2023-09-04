#include <render/index_buffer.h>
#include <glad/glad.h>
namespace RenderWorker
{
IndexBuffer::IndexBuffer()
{
    
}

IndexBuffer::~IndexBuffer()
{
    
}

void IndexBuffer::Bind(void* indices, int size)
{
    glGenBuffers(1, &ebo_id_);
    // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void IndexBuffer::UnBind()
{
    // 解绑VBO
    glDeleteBuffers(1, &ebo_id_);
}
}