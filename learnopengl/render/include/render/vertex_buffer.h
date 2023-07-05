#pragma once
#include <cstdint>

class vertex_buffer
{
public:  
    vertex_buffer(void* data, int size);
    ~vertex_buffer();
private:
    uint32_t id_;
};

