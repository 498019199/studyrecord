#pragma once
#include <common/WinApp.h>
#include <common/D3D11Util.h>

class D3D11RenderEngine
{
public:
    D3D11RenderEngine(HWND hwnd, const RenderSettings& settings);
    ~D3D11RenderEngine();

private:
    typedef HRESULT(WINAPI *CreateDXGIFactory1Func)(REFIID riid, void** ppFactory);
    typedef HRESULT(WINAPI *CreateDXGIFactory2Func)(UINT flags, REFIID riid, void** ppFactory);
    typedef HRESULT(WINAPI *D3D11CreateDeviceFunc)(IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags,
        D3D_FEATURE_LEVEL const * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion,
        ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext);

    CreateDXGIFactory1Func DynamicCreateDXGIFactory1_;
    CreateDXGIFactory2Func DynamicCreateDXGIFactory2_;
    D3D11CreateDeviceFunc DynamicD3D11CreateDevice_;
    
	void* mod_dxgi_ = nullptr;
    void* mod_d3d11_ = nullptr;


    ID3D11Device* d3d_device_;
	ID3D11DeviceContext* d3d_imm_ctx_;
	IDXGISwapChain* swap_chain_;

    ID3D11Texture2D* depth_stencil_buff_;
    ID3D11DepthStencilView* depth_stencil_view_;

    ID3D11RenderTargetView* render_target_view_;
    
    D3D11_VIEWPORT screen_viewport_;
};

