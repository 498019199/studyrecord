#include <render/vertex_buffer.h>
#include <glad/glad.h>

vertex_buffer::vertex_buffer(void* data, int size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer()
{
    glDeleteBuffers(1, &id_);
}
