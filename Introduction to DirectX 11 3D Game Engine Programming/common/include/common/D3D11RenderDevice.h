#pragma once
#include <common/WinApp.h>
#include <common/D3D11Util.h>

class D3D11RenderDevice
{
public:
    D3D11RenderDevice();
    ~D3D11RenderDevice();
    
    bool CreateRenderWindow(HWND hwnd, const RenderSettings& settings);

private:

    ID3D11Device* d3d_device_;
	ID3D11DeviceContext* d3d_imm_ctx_;
	IDXGISwapChain* swap_chain_;

    ID3D11Texture2D* depth_stencil_buff_;
    ID3D11DepthStencilView* depth_stencil_view_;

    ID3D11RenderTargetView* render_target_view_;
    
    D3D11_VIEWPORT screen_viewport_;
};

