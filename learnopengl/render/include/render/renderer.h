#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <render/shader.h>
#include <render/index_buffer.h>
#include <render/vertex_buffer.h>

class renderer
{
public:
    void init();
    void before_render();
    void render(float time);
    void after_render();

private:
    ptr_shaderobject shaderobj_;
    index_buffer indexs_;
    vertex_buffer vertexs_;
};




using ptr_renderer = std::shared_ptr<renderer>;
