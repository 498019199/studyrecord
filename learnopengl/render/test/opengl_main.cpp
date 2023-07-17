#include <render/app.h>
#include <render/renderer.h>
#include <iostream>
//#include <math/math.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
App* gMainApp = nullptr;
Renderer* gRender = nullptr;

int main()
{
    
    gMainApp = new App();
    gRender = new Renderer();
    if (nullptr == gMainApp || nullptr == gRender)
    {
        return 0;
    }
    gMainApp->CreateWindows(SCR_WIDTH, SCR_HEIGHT, "OpenGLLearn");
    gMainApp->Init();
    gRender->Init();
    
    gRender->BeforeRender();
    gMainApp->Run();
    gRender->AfterRender();

    delete gMainApp;
    delete gRender;
    return 0;
}


