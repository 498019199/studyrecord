#pragma once
#include <core/D3D11Util.h>

struct RenderSettings;
class D3D11RenderEngine
{
public:
    D3D11RenderEngine(HWND hwnd, const RenderSettings& settings);
    ~D3D11RenderEngine();

    void OnResize();
    void OnRender();

    ID3D11Device* D3DDevice() const;
    ID3D11DeviceContext* D3DDeviceImmContext() const;
private:
    int weight_ = 0;
    int height_ = 0;
    int sample_count_ = 0;
    int sample_quality_ = 0;
    
    ID3D11Device* d3d_device_ = nullptr;
	ID3D11DeviceContext* d3d_imm_ctx_ = nullptr;
	IDXGISwapChain* swap_chain_ = nullptr;

    int index_count_ = 0;
    ID3D11Texture2D* depth_stencil_buff_ = nullptr;
    ID3D11DepthStencilView* depth_stencil_view_ = nullptr;

    ID3D11RenderTargetView* render_target_view_ = nullptr;
    
    D3D11_VIEWPORT screen_viewport_;
};




