#include <render/app.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void app::create_windows(int width, int height, const char* title_name)
{
    // glfw: initialize and configure
    int errorCode  = glfwInit(); 
    if (GLFW_FALSE == errorCode)
    { 
        const char* error_msg;   
        glfwGetError(&error_msg);
        std::cout << "Failed to init GLFW: " << error_msg << std::endl;
        return ;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    window_= glfwCreateWindow(width, height, title_name, NULL, NULL);
    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }
}

void app::run()
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window_))
    {
        // input
        // -----
        //processInput(window_);
 
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        // draw our first triangle
        //glUseProgram(shaderProgram); // 激活shaderProgram，怎么画
        //glBindVertexArray(VAO); // 画什么
        //glDrawArrays(GL_TRIANGLES, 0, 3); // 开始画
 
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwTerminate();
}
