#include <render/app.h>
#include <render/renderer.h>
#include <iostream>
//#include <math/math.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
namespace RenderWorker
{
    App* gMainApp = nullptr;
    Renderer* gRender = nullptr;
}
using namespace RenderWorker;

int main()
{
    
    gMainApp = new RenderWorker::App();
    gRender = new RenderWorker::Renderer();
    if (nullptr == gMainApp || nullptr == gRender)
    {
        return 0;
    }
    gMainApp->CreateWindows(SCR_WIDTH, SCR_HEIGHT, "OpenGLLearn");
    gMainApp->Init();
    gRender->Init(SCR_WIDTH, SCR_HEIGHT);
    
    gRender->BeforeRender();
    gMainApp->Run();
    gRender->AfterRender();

    delete gMainApp;
    delete gRender;
    return 0;
}


