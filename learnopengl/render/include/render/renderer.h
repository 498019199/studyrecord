#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <render/shader.h>
#include <render/vertex_array.h>
#include <render/vertex_buffer.h>
#include <render/index_buffer.h>
#include <render/texture.h>

namespace RenderWorker
{
using PtrVertexs = std::shared_ptr<VertexArray>;
using PtrVertexBuf = std::shared_ptr<VertexBuffer>;
using PtrIndexs = std::shared_ptr<IndexBuffer>;
using PtrTexture2D = std::shared_ptr<Texture2D>;

class Renderer
{
public:
    void Init(int width, int height);
    void BeforeRender();
    void Render(float time);
    void AfterRender();

private:
    int width_ = 0;
    int height_ = 0;

    PtrShaderobject shaderobj_;
    PtrVertexs vertexs_;
    PtrVertexBuf vertex_buf_;
    PtrIndexs indexs_;
    PtrTexture2D texture2d_;
};

using PtrRenderer = std::shared_ptr<Renderer>;
}