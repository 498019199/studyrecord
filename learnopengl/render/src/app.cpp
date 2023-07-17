#include <render/app.h>
#include <render/renderer.h>
#include <iostream>
extern Renderer* gRender;

void App::Init()
{
}

// key input
// ---------------------------------------------------------------------------------------------------------
void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "key " << key << "scancode " << scancode << "action " << action << "mods " << mods << std::endl;
    switch (key)
    {
    case GLFW_KEY_W:
        /* code */
        break;
    case GLFW_KEY_S:
        /* code */
        break;
    case GLFW_KEY_A:
        /* code */
        break;
    case GLFW_KEY_D:
        /* code */
        break;
    }
}

// mouse button
void mouseInput(GLFWwindow* window, int button, int action, int mods)
{
    //std::cout << "button " << button << "action  " << action << "mods " <<  mods << std::endl;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
        /* code */
        break;
    case GLFW_MOUSE_BUTTON_2:
        /* code */
        break;
    }
}

// mosue wheel
void mouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void App::CreateWindows(int width, int height, const char* title_name)
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
    glfwSetKeyCallback(window_, keyInput);
    glfwSetMouseButtonCallback(window_, mouseInput);
    glfwSetScrollCallback(window_, mouseWheel);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }
}

void App::Run()
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window_))
    {
        // input
        // -----
        //processInput(window_);
 
        // render
        Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwTerminate();
}

void App::Render()
{
    if (gRender)
    {
        gRender->Render(0.f);
    }
}

