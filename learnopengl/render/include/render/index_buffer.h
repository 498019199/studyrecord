#pragma once
#include <cstdint>
namespace RenderWorker
{

//EBO对象
class IndexBuffer
{
public:  
    IndexBuffer();
    ~IndexBuffer();

    void Bind(void* data, int size);
    void UnBind();

    uint32_t GetId() const { return ebo_id_; }
private:
    uint32_t ebo_id_ = 0;
};
}

