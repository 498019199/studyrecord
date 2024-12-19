#pragma once
#include <common/D3D11RenderEngine.h>

class D3D11RenderMesh
{
public:
    D3D11RenderMesh();
    ~D3D11RenderMesh();

    void CreateVertexBuffer(void const * init_data, int size_in_byte);
    void CreateIndecxBuffer(void const * init_data, int size_in_byte);

    void LoadShaderFile(const wchar_t* filename);
private:
    ID3D11Buffer* vbs_;
	ID3D11Buffer* ibs_;

    ID3DX11Effect* fx_;
	ID3DX11EffectTechnique* tech_;
	ID3DX11EffectMatrixVariable* mvp_;
};
