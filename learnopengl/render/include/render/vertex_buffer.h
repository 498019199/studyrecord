#pragma once
#include <cstdint>
namespace RenderWorker
{
//VBO对象
class VertexBuffer
{
public:  
    VertexBuffer();
    ~VertexBuffer();

    void Bind(void* data, int size);
    void UnBind();

    int GetId() const { return vbo_id_; }
private:
    uint32_t vbo_id_ = 0;
};

}