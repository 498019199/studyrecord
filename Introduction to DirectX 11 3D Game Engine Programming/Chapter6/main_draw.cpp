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
	Color color;
};
const D3D11_INPUT_ELEMENT_DESC inputLayout[2] = 
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

void Triangle()
{
	// 设置三角形顶点
    Vertex vertices[] =
    {
        { float3(0.0f, 0.5f, 0.5f), Color(0.0f, 1.0f, 0.0f, 1.0f) },
        { float3(0.5f, -0.5f, 0.5f), Color(0.0f, 0.0f, 1.0f, 1.0f) },
        { float3(-0.5f, -0.5f, 0.5f), Color(1.0f, 0.0f, 0.0f, 1.0f) }
    };

	D3D11RenderMesh Mesh;
	Mesh.CreateVertexBuffer(&vertices, sizeof(Vertex) * 3);

	auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
	currentPath += "\\Chapter6\\HLSL\\";
	Mesh.CreateVertexShader(currentPath + "Triangle_VS", inputLayout, ARRAYSIZE(inputLayout));

	Mesh.CreatePixelShader(currentPath + "Triangle_PS");
	
	uint32_t stride = sizeof(Vertex);	// 跨越字节数
	Mesh.BindShader(stride);
	g_IndexCount = 3;
}

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
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3, 
		4, 3, 7
	};
    
	D3D11RenderMesh* pMesh = new D3D11RenderMesh();
    pMesh->CreateVertexBuffer(&vertices, sizeof(Vertex) * 8);
    pMesh->CreateIndecxBuffer(&indices, sizeof(UINT) * 36);
	pMesh->CreateConstant();

	auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
	currentPath += "\\Chapter6\\HLSL\\";
	pMesh->CreateVertexShader(currentPath + "Cube_VS", inputLayout, ARRAYSIZE(inputLayout));
	pMesh->CreatePixelShader(currentPath + "Cube_PS");
	
	uint32_t stride = sizeof(Vertex);	// 跨越字节数
	pMesh->BindShader(stride);
	pMesh->D3D11SetDebug_Cube();
	
	g_IndexCount = 36;
	Context::Instance().AppInstance().AddActor(pMesh);
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
    settings.width = 1280;
    settings.height = 720;
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
	
	//Triangle();
	Box();
	
    app.Run();
    return 0;
}