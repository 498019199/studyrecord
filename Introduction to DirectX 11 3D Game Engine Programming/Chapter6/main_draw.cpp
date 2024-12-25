#include <common/WinApp.h>
#include <common/D3D11Util.h>
#include <common/D3D11RenderMesh.h>

#include <common/macro.h>
#include <math/math.h>

#include <filesystem>
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


void Box()
{
	// 创建顶点缓冲
    Vertex vertices[] =
    {
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), (const float*)&Colors::White   },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), (const float*)&Colors::Black   },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), (const float*)&Colors::Red     },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), (const float*)&Colors::Green   },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), (const float*)&Colors::Blue    },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), (const float*)&Colors::Yellow  },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), (const float*)&Colors::Cyan    },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), (const float*)&Colors::Magenta }
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

	std::filesystem::path currentPath = std::filesystem::current_path();
	std::string filename = "example.txt";
	std::filesystem::path filePath = currentPath / filename;
    Mesh.LoadShaderFile(filePath.string().c_str());
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
    app.Run();
    return 0;
}