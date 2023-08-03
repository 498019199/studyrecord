#pragma once
#include <cstdint>
namespace RenderWorker
{
//VAO对象
class VertexArray
{
public:  
    VertexArray();
    ~VertexArray();

    void Bind();
    void UnBind();

    int GetId() const { return vao_id_; }
private:
    uint32_t vao_id_ = 0;
};


}


