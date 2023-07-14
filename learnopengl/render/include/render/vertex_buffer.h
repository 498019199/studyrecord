#pragma once
#include <cstdint>

class vertex_buffer
{
public:  
    ~vertex_buffer();

    void bind();
    void unbind();

    int get_id() const { return id_; }
private:
    uint32_t id_ = 0;
};
