#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <render/shader.h>
#include <render/index_buffer.h>
#include <render/vertex_buffer.h>

using PtrIndexs = std::shared_ptr<IndexBuffer>;
using PtrVertexs = std::shared_ptr<VertexBuffer>;
class Renderer
{
public:
    void Init();
    void BeforeRender();
    void Render(float time);
    void AfterRender();

private:
    PtrShaderobject shaderobj_;
    PtrIndexs indexs_;
    PtrVertexs vertexs_;
};

using PtrRenderer = std::shared_ptr<Renderer>;
