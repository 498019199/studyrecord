#pragma once
#include <core/macro.h>
#include <core/com_ptr.h>
#include <cassert>
#include <cstdint>

#include <vector>
#include <string>
#include <map>
#include <core/span.h>



#ifdef _DEBUG
	#define COMMON_ASSERT(val) assert(val)
#else
	#define COMMON_ASSERT(val) 
#endif//_DEBUG

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
class Renderable;
using RenderablePtr = std::shared_ptr<Renderable>;
class RenderEffect;
using RenderEffectPtr = std::shared_ptr<RenderEffect>;

struct ID3D11Buffer;
using ID3D11BufferPtr = com_ptr<ID3D11Buffer>;
class D3D11GraphicsBuffer;
using GraphicsBufferPtr = std::shared_ptr<D3D11GraphicsBuffer>;
class D3D11RenderLayout;
using RenderLayoutPtr = std::shared_ptr<D3D11RenderLayout>;