#include <render/vertex_buffer.h>
#include <glad/glad.h>

void VertexBuffer::Bind()
{
    //创建VAO对象
    glGenVertexArrays(1, &id_);
	glBindVertexArray(id_);
    //解释顶点数据方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    glEnableVertexAttribArray(0);
}

void VertexBuffer::UnBind()
{
    //解释顶点数据方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    glEnableVertexAttribArray(0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &id_);
    glDeleteBuffers(1, &id_);
}
