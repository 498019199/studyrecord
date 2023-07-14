#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <render/shader.h>
#include <render/index_buffer.h>
#include <render/vertex_buffer.h>

using ptr_indexs = std::shared_ptr<index_buffer>;
using ptr_vertexs = std::shared_ptr<vertex_buffer>;
class renderer
{
public:
    void init();
    void before_render();
    void render(float time);
    void after_render();

private:
    ptr_shaderobject shaderobj_;
    ptr_indexs indexs_;
    ptr_vertexs vertexs_;
};




using ptr_renderer = std::shared_ptr<renderer>;
