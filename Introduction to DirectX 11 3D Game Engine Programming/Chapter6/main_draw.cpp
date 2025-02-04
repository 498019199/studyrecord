#include <common/WinApp.h>
#include <common/D3D11Util.h>
#include <common/D3D11RenderMesh.h>
#include <common/Context.h>
#include <math/math.h>

#include <filesystem>
struct Vertex
{
	float3 pos;
	Color color;
};
const D3D11_INPUT_ELEMENT_DESC inputLayout[2] = 
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


void Box()
{
	// 创建顶点缓冲
    Vertex vertices[] =
    {
		{ float3(-1.0f, -1.0f, -1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f)   },
		{ float3(-1.0f, +1.0f, -1.0f), Color(0.0f, 0.0f, 0.0f, 1.0f)   },
		{ float3(+1.0f, +1.0f, -1.0f), Color(1.0f, 0.0f, 0.0f, 1.0f)     },
		{ float3(+1.0f, -1.0f, -1.0f), Color(0.0f, 1.0f, 0.0f, 1.0f)  },
		{ float3(-1.0f, -1.0f, +1.0f), Color(0.0f, 0.0f, 1.0f, 1.0f)    },
		{ float3(-1.0f, +1.0f, +1.0f), Color(1.0f, 1.0f, 0.0f, 1.0f)  },
		{ float3(+1.0f, +1.0f, +1.0f), Color(0.0f, 1.0f, 1.0f, 1.0f)    },
		{ float3(+1.0f, -1.0f, +1.0f), Color(1.0f, 0.0f, 1.0f, 1.0f) }
    };

    // 创建索引缓冲
	UINT indices[] = {
		// 前表面
		0, 1, 2,
		0, 2, 3,

		// 后表面
		4, 6, 5,
		4, 7, 6,

		// 左表面
		4, 5, 1,
		4, 1, 0,

		// 右表面
		3, 2, 6,
		3, 6, 7,

		// 上表面
		1, 5, 6,
		1, 6, 2,

		// 下表面
		4, 0, 3, 
		4, 3, 7
	};
    
	D3D11RenderMesh Mesh;
    Mesh.CreateVertexBuffer(&vertices, sizeof(Vertex) * 8);
    Mesh.CreateIndecxBuffer(&indices, sizeof(UINT) * 36);

	auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
	currentPath += "\\Chapter6\\HLSL\\";
	Mesh.CreateVertexShader(currentPath + "Cube_VS");
	Mesh.CreatePixelShader(currentPath + "Cube_PS");
	
	Mesh.BindShader();
}

void Hills()
{
    
}

void Shapes()
{

}

void Skull()
{

}

void Waves()
{

}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1920;
    settings.height = 1080;
    app.CreateAppWindow(settings);
    app.InitDevice(app.GetHWND(), settings);

	Box();
	
    app.Run();
    return 0;
}