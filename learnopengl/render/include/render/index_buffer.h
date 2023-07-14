#pragma once
#include <cstdint>

class IndexBuffer
{
public:  
    IndexBuffer();
    ~IndexBuffer();

    void Bind(void* data, int size);
    void UnBind();

    int GetId() const { return id_; }
private:
    uint32_t id_ = 0;
};





