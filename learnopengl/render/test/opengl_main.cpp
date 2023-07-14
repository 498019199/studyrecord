#include <render/app.h>
#include <iostream>
//#include <math/math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
int main()
{
    
    app* main_app = new app();
    if (nullptr == main_app)
    {
        return 0;
    }
    main_app->create_windows(SCR_WIDTH, SCR_HEIGHT, "OpenGLLearn");
    main_app->run();
 

 

    
    return 0;
}


