#pragma once
#include <core/common.h>
#include <render/RenderLayout.h>
#include <render/RenderEngine.h>
#include "D3D11Util.h"

namespace RenderWorker
{

struct RenderSettings;
class D3D11RenderEngine :public RenderEngine
{
public:
    D3D11RenderEngine(HWND hwnd, const RenderSettings& settings);
    ~D3D11RenderEngine();

    void OnResize();

    ID3D11Device* D3DDevice() const;
    ID3D11DeviceContext* D3DDeviceImmContext() const;

    void DoRender(const RenderEffect& effect, const RenderLayout& rl);
    void EndRender() const override;
    void SwitchChain() const; 

    void RSSetState(ID3D11RasterizerState* ras);
    
    // 将着色器绑定到渲染管线
    void VSSetShader(ID3D11VertexShader* shader);
	void PSSetShader(ID3D11PixelShader* shader);
    // 将更新好的常量缓冲区绑定到顶点着色器和像素着色器
    void SetConstantBuffers(ShaderStage stage, int index, ID3D11Buffer* cb);
private:
    int weight_{0};
    int height_{0};
    int sample_count_{0};
    int sample_quality_{0};
    
    ID3D11DevicePtr d3d_device_;
	ID3D11DeviceContextPtr d3d_imm_ctx_;
	IDXGISwapChainPtr swap_chain_;

    uint32_t num_primitives_just_rendered_{0};
	uint32_t num_vertices_just_rendered_{0};

    int index_count_{0};
    ID3D11Texture2DPtr depth_stencil_buff_;
    ID3D11DepthStencilViewPtr depth_stencil_view_;

    ID3D11RenderTargetViewPtr render_target_view_;
    
    D3D11_VIEWPORT screen_viewport_;

    ID3D11RasterizerState* rasterizer_state_cache_{nullptr};
    
    ID3D11VertexShader* vertex_shader_cache_{nullptr};
    ID3D11PixelShader* pixel_shader_cache_{nullptr};
    std::array<ID3D11Buffer*, ShaderStageNum> shader_cb_ptr_cache_;

    ID3D11InputLayout* input_layout_cache_{nullptr};
    std::vector<ID3D11Buffer*> vb_cache_;
    std::vector<UINT> vb_stride_cache_;
    std::vector<UINT> vb_offset_cache_;
    ID3D11Buffer* ib_cache_{nullptr};
    RenderLayout::topology_type topology_type_cache_ {RenderLayout::TT_PointList};
};
}








