#include <render/vertex_buffer.h>
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
    //创建VAO对象
    glGenVertexArrays(1, &id_);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &id_);
    glDeleteBuffers(1, &id_);
}

void VertexBuffer::Bind(void* data, int size)
{

	glBindVertexArray(id_);
    // 0. 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void VertexBuffer::UnBind()
{
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    //解释顶点数据方式
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    // glEnableVertexAttribArray(0);
}

