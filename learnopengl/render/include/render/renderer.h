#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <render/shader.h>
#include <render/vertex_array.h>
#include <render/vertex_buffer.h>

using PtrVertexs = std::shared_ptr<VertexArray>;
using PtrVertexBuf = std::shared_ptr<VertexBuffer>;
class Renderer
{
public:
    void Init();
    void BeforeRender();
    void Render(float time);
    void AfterRender();

private:
    PtrShaderobject shaderobj_;
    PtrVertexs vertexs_;
    PtrVertexBuf vertex_buf_;
};

using PtrRenderer = std::shared_ptr<Renderer>;
