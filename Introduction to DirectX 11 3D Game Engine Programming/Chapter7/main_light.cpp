#include <common/WinApp.h>
#include <common/D3D11Util.h>
#include <common/D3D11RenderMesh.h>
#include <common/Context.h>
#include <math/math.h>

#include <filesystem>
extern int g_IndexCount = 0;
struct Vertex
{
	float3 pos;
	float3 normal;
	Color color;
};
const D3D11_INPUT_ELEMENT_DESC inputLayout[3] = 
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

void Light()
{}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1280;
    settings.height = 720;
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
	
	Light();

    app.Run();
    return 0;
}