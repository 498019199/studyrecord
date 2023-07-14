#pragma once
#include <cstdint>

class index_buffer
{
public:  
    ~index_buffer();

    void bind(void* data, int size);
    void unbind();

    int get_id() const { return id_; }
private:
    uint32_t id_ = 0;
};



