#pragma once
#include <cstdint>

//VAO
class VertexBuffer
{
public:  
    VertexBuffer();
    ~VertexBuffer();

    void Bind(void* data, int size);
    void UnBind();

    int GetId() const { return id_; }
private:
    uint32_t id_ = 0;
};

