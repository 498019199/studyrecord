#pragma once
#include <cstdint>

//EBO对象
class IndexBuffer
{
public:  
    IndexBuffer();
    ~IndexBuffer();

    void Bind(void* data, int size);
    void UnBind();

    int GetId() const { return ebo_id_; }
private:
    uint32_t ebo_id_ = 0;
};


