#pragma once
#include <core/macro.h>
#include <core/com_ptr.h>
#include <core/ElementFormat.h>
#include <cassert>
#include <cstdint>

#include <d3d11_1.h>

#include <vector>
#include <string>
#include <map>
#include <core/span.h>
#include <string>
#include <string_view>


#ifdef _DEBUG
	#define COMMON_ASSERT(val) assert(val)
#else
	#define COMMON_ASSERT(val) 
#endif//_DEBUG

using ID3D11BufferPtr = com_ptr<ID3D11Buffer>;
using ID3D11InputLayoutPtr = com_ptr<ID3D11InputLayout>;
using ID3D11RasterizerStatePtr = com_ptr<ID3D11RasterizerState>;
using ID3D11VertexShaderPtr = com_ptr<ID3D11VertexShader>;
using ID3D11PixelShaderPtr = com_ptr<ID3D11PixelShader>;
using ID3D11ResourcePtr = com_ptr<ID3D11Resource>;
using ID3D11Texture2DPtr = com_ptr<ID3D11Texture2D>;

#include <math/math.h>
using int1 = MathWorker::int1;
using int2 = MathWorker::int2;
using int3 = MathWorker::int3;
using int4 = MathWorker::int4;
using uint1 = MathWorker::uint1;
using uint2 = MathWorker::uint2;
using uint3 = MathWorker::uint3;
using uint4 = MathWorker::uint4;
using float1 = MathWorker::float1;
using float2 = MathWorker::float2;
using float3 = MathWorker::float3;
using float4 = MathWorker::float4;
using quater = MathWorker::quater;
using rotator = MathWorker::rotator;
using float4x4 = MathWorker::float4x4;
using Color = MathWorker::Color;

class SceneNode;
using SceneNodePtr = std::shared_ptr<SceneNode>;
class D3D11Renderable;
using RenderablePtr = std::shared_ptr<D3D11Renderable>;
class RenderEffect;
using RenderEffectPtr = std::shared_ptr<RenderEffect>;

class D3D11GraphicsBuffer;
using GraphicsBufferPtr = std::shared_ptr<D3D11GraphicsBuffer>;
class D3D11RenderLayout;
using RenderLayoutPtr = std::shared_ptr<D3D11RenderLayout>;
class D3D11RenderFactory;
using RenderFactoryPtr = std::shared_ptr<D3D11RenderFactory>;
class WinAPP;
class D3D11RenderEngine;
using RenderEnginePtr = std::shared_ptr<D3D11RenderEngine>;
class D3D11RenderEngine;
using RenderEnginePtr = std::shared_ptr<D3D11RenderEngine>;
class World;
using WorldPtr = std::shared_ptr<World>;

std::string& Convert(std::string& dest, std::wstring_view src);
std::wstring& Convert(std::wstring& dest, std::string_view src);