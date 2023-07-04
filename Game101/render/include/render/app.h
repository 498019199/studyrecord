#pragma

class GLFWwindow;
class app
{
public:
    // 实例化GLFW窗口
    void create_windows(int width, int height, const char* title_name);

    void run();

private:
    GLFWwindow* window_;
};

