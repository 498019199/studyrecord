#include <render/vertex_buffer.h>
#include <glad/glad.h>

vertex_buffer::vertex_buffer()
{
    //创建VAO对象
    glGenVertexArrays(1, &id_);
	glBindVertexArray(id_);

}

void vertex_buffer::bind()
{
    //解释顶点数据方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    glEnableVertexAttribArray(0);
}

void vertex_buffer::unbind()
{
    //解释顶点数据方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    glEnableVertexAttribArray(0);
}

vertex_buffer::~vertex_buffer()
{
    glDeleteVertexArrays(1, &id_);
    glDeleteBuffers(1, &id_);
}
