#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class app
{
public:
    // 实例化GLFW窗口
    void create_windows(int width, int height, const char* title_name);

    void run();

    void render();
private:
    GLFWwindow* window_;
};


