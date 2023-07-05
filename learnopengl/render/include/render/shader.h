#pragma once

class shader
{
public:   
    ~shader();

    void init_shader(int type);
    void bind_shader(const char* shader_script);
    void link_shader();
private:
    const char* get_shader_type();

private:
    int shader_type_ = 0;
    int vertex_shader_ = 0;
};





