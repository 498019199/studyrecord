#include <common/D3D11RenderMesh.h>
#include <common/Context.h>

D3D11RenderMesh::D3D11RenderMesh()
{
    
}

D3D11RenderMesh::~D3D11RenderMesh()
{
    
}

void D3D11RenderMesh::CreateVertexBuffer(void const * init_data, int size_in_byte)
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = size_in_byte;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = init_data;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&vbd, &vinitData, &vbs_));
}

void D3D11RenderMesh::CreateIndecxBuffer(void const * init_data, int size_in_byte)
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = size_in_byte;
    vbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = init_data;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&vbd, &vinitData, &vbs_));
}

void D3D11RenderMesh::LoadShaderFile(const char* filename)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
    shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(filename, 0, 0, 0, "fx_5_0", shaderFlags, 
		0, 0, &compiledShader, &compilationMsgs, 0);
    // compilationMsgs中包含错误或警告信息
	if( compilationMsgs != 0 )
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}
    // 就算没有compilationMsgs，也需要确保没有其他错误
	if(FAILED(hr))
	{
		//DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}

    auto const& re = Context::Instance().RenderEngineInstance();
    HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 
		0, re.D3DDevice(), &fx_));
    	// 编译完成释放资源
	ReleaseCOM(compiledShader);

	tech_    = fx_->GetTechniqueByName("ColorTech");
	mvp_ = fx_->GetVariableByName("gWorldViewProj")->AsMatrix();
}

