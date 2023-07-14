#pragma once
#include <render/renderer.h>

class app
{
public:
    void init();

    // 实例化GLFW窗口
    void create_windows(int width, int height, const char* title_name);

    void run();

    void render();
private:
    GLFWwindow* window_;
    ptr_renderer render_;
};




