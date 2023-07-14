#pragma once
#include <cstdint>

class VertexBuffer
{
public:  
    ~VertexBuffer();

    void Bind();
    void UnBind();

    int GetId() const { return id_; }
private:
    uint32_t id_ = 0;
};
