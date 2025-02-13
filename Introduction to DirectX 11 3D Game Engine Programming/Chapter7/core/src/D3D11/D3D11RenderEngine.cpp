#include <core/D3D11RenderEngine.h>
#include <core/D3D11RenderLayout.h>
#include <core/D3D11Util.h>
#include <core/D3D11GraphicsBuffer.h>
#include <core/RenderEffect.h>

D3D11RenderEngine::D3D11RenderEngine(HWND hwnd, const RenderSettings& settings)
{
    // Create the device and device context.
    D3D_DRIVER_TYPE dev_type = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
			0,                 // default adapter
			dev_type,
			0,                 // no software device
			createDeviceFlags, 
			0, 0,              // default feature level array
			D3D11_SDK_VERSION,
			&d3d_device_,
			&featureLevel,
			&d3d_imm_ctx_);

	if( FAILED(hr) )
	{
		::MessageBoxW(0, L"D3D11CreateDevice Failed.", 0, 0);
		return ;
	}

	if( featureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		::MessageBoxW(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return ;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	// TIFHR(d3d_device_->CheckMultisampleQualityLevels(
	// 	DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
	// assert( m4xMsaaQuality > 0 );

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = settings.width;

	sd.BufferDesc.Height = settings.height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    sd.SampleDesc.Count   = settings.sample_count;
    sd.SampleDesc.Quality = settings.sample_quality;

	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	TIFHR(d3d_device_->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	      
	IDXGIAdapter* dxgiAdapter = 0;
	TIFHR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	TIFHR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	TIFHR(dxgiFactory->CreateSwapChain(d3d_device_, &sd, &swap_chain_));
	
    ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);
	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	
	weight_ = settings.width;
    height_ = settings.height;
    sample_count_ = settings.sample_count;
    sample_quality_ = settings.sample_quality;
	OnResize();
	return ;
}

D3D11RenderEngine::~D3D11RenderEngine()
{
	ReleaseCOM(render_target_view_);
	ReleaseCOM(depth_stencil_view_);
	ReleaseCOM(swap_chain_);
	ReleaseCOM(depth_stencil_buff_);

	if( d3d_imm_ctx_ )
		d3d_imm_ctx_->ClearState();

	ReleaseCOM(d3d_imm_ctx_);
	ReleaseCOM(d3d_device_);
}

void D3D11RenderEngine::OnResize()
{
	assert(d3d_imm_ctx_);
	assert(d3d_device_);
	assert(swap_chain_);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM(render_target_view_);
	ReleaseCOM(depth_stencil_view_);
	ReleaseCOM(depth_stencil_buff_);

	// Resize the swap chain and recreate the render target view.
	TIFHR(swap_chain_->ResizeBuffers(1, weight_, height_, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	TIFHR(swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	TIFHR(d3d_device_->CreateRenderTargetView(backBuffer, 0, &render_target_view_));
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width     = weight_;
	depthStencilDesc.Height    = height_;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// Use 4X MSAA? --must match swap chain MSAA values.
	depthStencilDesc.SampleDesc.Count   = sample_count_;
	depthStencilDesc.SampleDesc.Quality = sample_quality_;

	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	TIFHR(d3d_device_->CreateTexture2D(&depthStencilDesc, 0, &depth_stencil_buff_));
	TIFHR(d3d_device_->CreateDepthStencilView(depth_stencil_buff_, 0, &depth_stencil_view_));

	// Bind the render target view and depth/stencil view to the pipeline.
	d3d_imm_ctx_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);

	// Set the viewport transform.
	screen_viewport_.TopLeftX = 0;
	screen_viewport_.TopLeftY = 0;
	screen_viewport_.Width    = static_cast<float>(weight_);
	screen_viewport_.Height   = static_cast<float>(height_);
	screen_viewport_.MinDepth = 0.0f;
	screen_viewport_.MaxDepth = 1.0f;
	d3d_imm_ctx_->RSSetViewports(1, &screen_viewport_);
}

void D3D11RenderEngine::EndRender() const
{
	assert(d3d_imm_ctx_);
	assert(swap_chain_);

	Color blackColor(0.0, 0.0, 0.0f, 1.0f);
	d3d_imm_ctx_->ClearRenderTargetView(render_target_view_, &blackColor.r());
	d3d_imm_ctx_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	d3d_imm_ctx_->DrawIndexed(num_vertices_just_rendered_, 0, 0);
	TIFHR(swap_chain_->Present(0, 0));
}

ID3D11Device* D3D11RenderEngine::D3DDevice() const
{
	return d3d_device_;
}

ID3D11DeviceContext* D3D11RenderEngine::D3DDeviceImmContext() const
{
    return d3d_imm_ctx_;
}

void D3D11RenderEngine::DoRender(const RenderEffect& effect, const D3D11RenderLayout& rl)
{
	
	uint32_t vertex_stream_num = rl.VertexStreamNum();
	rl.Active();

	const auto& vbs = rl.VBs();
	const auto& strides = rl.Strides();
	const auto& offsets = rl.Offsets();
	if(0 != vertex_stream_num)
	{
		if ((vb_cache_.size() != vertex_stream_num) || (vb_cache_ != vbs)
			|| (vb_stride_cache_ != strides) || (vb_offset_cache_ != offsets))
		{
			d3d_imm_ctx_->IASetVertexBuffers(0, vertex_stream_num, &vbs[0], &strides[0], &offsets[0]);
			vb_cache_ = vbs;
			vb_stride_cache_ = strides;
			vb_offset_cache_ = offsets;
		}

		// auto blob = effect.VsCode();
        // ID3D11InputLayoutPtr new_layout;
        // TIFHR(d3d_device_->CreateInputLayout(&rl.vertex_elems_[0], static_cast<UINT>(rl.vertex_elems_.size()),
        //      blob->GetBufferPointer(), blob->GetBufferSize(), new_layout.put()));
        // auto layout = new_layout.get();

		auto layout = rl.InputLayout(effect);
		if (layout != input_layout_cache_)
		{
			d3d_imm_ctx_->IASetInputLayout(layout);
			input_layout_cache_ = layout;
		}
	}
	else
	{
		if (!vb_cache_.empty())
		{
			vb_cache_.assign(vb_cache_.size(), nullptr);
			vb_stride_cache_.assign(vb_stride_cache_.size(), 0);
			vb_offset_cache_.assign(vb_offset_cache_.size(), 0);
			d3d_imm_ctx_->IASetVertexBuffers(0, static_cast<UINT>(vb_cache_.size()),
				&vb_cache_[0], &vb_stride_cache_[0], &vb_offset_cache_[0]);
			vb_cache_.clear();
			vb_stride_cache_.clear();
			vb_offset_cache_.clear();
		}
		input_layout_cache_ = nullptr;
		d3d_imm_ctx_->IASetInputLayout(input_layout_cache_);
	}

    // 设置图元类型，设定输入布局
	uint32_t const vertex_count = static_cast<uint32_t>(rl.UseIndices() ? rl.IndicesNum() : rl.NumVertices());
	D3D11RenderLayout::topology_type tt = rl.TopologyType();
	if (topology_type_cache_ != tt)
	{
		d3d_imm_ctx_->IASetPrimitiveTopology(D3D11Mapping::Mapping(tt));
		topology_type_cache_ = tt;
	}

	uint32_t prim_count;
	switch (tt)
	{
	case D3D11RenderLayout::TT_PointList:
		prim_count = vertex_count;
		break;

	case D3D11RenderLayout::TT_LineList:
	case D3D11RenderLayout::TT_LineList_Adj:
		prim_count = vertex_count / 2;
		break;

	case D3D11RenderLayout::TT_LineStrip:
	case D3D11RenderLayout::TT_LineStrip_Adj:
		prim_count = vertex_count - 1;
		break;

	case D3D11RenderLayout::TT_TriangleList:
	case D3D11RenderLayout::TT_TriangleList_Adj:
		prim_count = vertex_count / 3;
		break;

	case D3D11RenderLayout::TT_TriangleStrip:
	case D3D11RenderLayout::TT_TriangleStrip_Adj:
		prim_count = vertex_count - 2;
		break;

	default:
		if ((tt >= D3D11RenderLayout::TT_1_Ctrl_Pt_PatchList)
			&& (tt <= D3D11RenderLayout::TT_32_Ctrl_Pt_PatchList))
		{
			prim_count = vertex_count / (tt - D3D11RenderLayout::TT_1_Ctrl_Pt_PatchList + 1);
		}
		else
		{
			//KFL_UNREACHABLE("Invalid topology type");
		}
		break;
	}
	num_primitives_just_rendered_ = prim_count;
	num_vertices_just_rendered_ = vertex_count;

    // 将更新好的常量缓冲区绑定到顶点着色器
	if(rl.UseIndices())
	{
		ID3D11Buffer* d3dib = rl.GetIndexStream()->D3DBuffer();
		if (ib_cache_ != d3dib)
		{
			ib_cache_ = d3dib;
			d3d_imm_ctx_->IASetIndexBuffer(d3dib, D3D11Mapping::MappingFormat(rl.IndexStreamFormat()), 0);
		}
	}
	else
	{
		if (ib_cache_)
		{
			d3d_imm_ctx_->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);
			ib_cache_ = nullptr;
		}
	}

    // 将着色器绑定到渲染管线
	ID3D11Buffer* d3d11_cbuffs = effect.HWBuff()->D3DBuffer();
    d3d_imm_ctx_->VSSetConstantBuffers(0, 1, &d3d11_cbuffs);

    d3d_imm_ctx_->VSSetShader(effect.GetVertexShader(), nullptr, 0);
    d3d_imm_ctx_->PSSetShader(effect.GetPixelShader(), nullptr, 0);
}
