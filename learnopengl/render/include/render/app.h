#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace RenderWorker
{

class App
{
public:
    void Init();

    // 实例化GLFW窗口
    void CreateWindows(int width, int height, const char* title_name);

    void Run();

    void Render();

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
private:
    int width_ = 0;
    int height_ = 0;

    GLFWwindow* window_;
};

}


