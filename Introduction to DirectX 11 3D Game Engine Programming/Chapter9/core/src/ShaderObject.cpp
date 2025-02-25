#include <render/ShaderObject.h>

#include <core/DllLoader.h>

#ifdef ZENGINE_PLATFORM_WINDOWS
#define CALL_D3DCOMPILER_DIRECTLY
#endif

#ifdef CALL_D3DCOMPILER_DIRECTLY
#include <d3dcompiler.h>
#endif

namespace
{
using namespace RenderWorker;
class D3DCompilerLoader
{
public:
    ~D3DCompilerLoader()
    {
#ifdef CALL_D3DCOMPILER_DIRECTLY
        mod_d3dcompiler_.Free();
#endif
    }

    static D3DCompilerLoader& Instance()
    {
        static D3DCompilerLoader initer;
        return initer;
    }

    HRESULT D3DReflect(std::vector<uint8_t> const & shader_code, void** reflector)
    {
#ifdef CALL_D3DCOMPILER_DIRECTLY
        static GUID const IID_ID3D11ShaderReflection_47
            = { 0x8d536ca1, 0x0cca, 0x4956, { 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84 } };

        return DynamicD3DReflect_(&shader_code[0],  // [In]编译好的着色器二进制信息
            static_cast<UINT>(shader_code.size()),  // [In]编译好的着色器二进制信息字节数
            IID_ID3D11ShaderReflection_47,          // [In]COM组件的GUID
            reflector);                             // [Out]输出的着色器反射借口
#else
        // TODO
        KFL_UNUSED(shader_code);
        KFL_UNUSED(reflector);
        return S_OK;
#endif
    }

private:
    D3DCompilerLoader()
    {
    #ifdef CALL_D3DCOMPILER_DIRECTLY
        mod_d3dcompiler_.Load("d3dcompiler_47.dll");

        DynamicD3DCompile_ = reinterpret_cast<D3DCompileFunc>(mod_d3dcompiler_.GetProcAddress("D3DCompile"));
        DynamicD3DReflect_ = reinterpret_cast<D3DReflectFunc>(mod_d3dcompiler_.GetProcAddress("D3DReflect"));
        DynamicD3DStripShader_ = reinterpret_cast<D3DStripShaderFunc>(mod_d3dcompiler_.GetProcAddress("D3DStripShader"));
    #endif
}

private:
#ifdef CALL_D3DCOMPILER_DIRECTLY
    typedef HRESULT (WINAPI *D3DCompileFunc)(LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName,
        D3D_SHADER_MACRO const * pDefines, ID3DInclude* pInclude, LPCSTR pEntrypoint,
        LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppCode, ID3DBlob** ppErrorMsgs);
    typedef HRESULT (WINAPI *D3DReflectFunc)(LPCVOID pSrcData, SIZE_T SrcDataSize, REFIID pInterface, void** ppReflector);
    typedef HRESULT (WINAPI *D3DStripShaderFunc)(LPCVOID pShaderBytecode, SIZE_T BytecodeLength, UINT uStripFlags,
        ID3DBlob** ppStrippedBlob);

    DllLoader mod_d3dcompiler_;
    D3DCompileFunc DynamicD3DCompile_;
    D3DReflectFunc DynamicD3DReflect_;
    D3DStripShaderFunc DynamicD3DStripShader_;
#endif
};
}

namespace RenderWorker
{

bool operator!=(const ShaderDesc::StreamOutputDecl& lhs, const ShaderDesc::StreamOutputDecl& rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator==(const ShaderDesc::StreamOutputDecl& lhs, const ShaderDesc::StreamOutputDecl& rhs) noexcept
{
    return (lhs.usage == rhs.usage) && (lhs.usage_index == rhs.usage_index)
        && (lhs.start_component == rhs.start_component) && (lhs.component_count == rhs.component_count)
        && (lhs.slot == rhs.slot);
}

bool operator!=(const ShaderDesc& lhs, const ShaderDesc& rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator==(const ShaderDesc& lhs, const ShaderDesc& rhs) noexcept
{
    return (lhs.profile == rhs.profile) && (lhs.func_name == rhs.func_name)
        && (lhs.macros_hash == rhs.macros_hash) && (lhs.so_decl == rhs.so_decl);
    
}

ShaderStageObject::ShaderStageObject(ShaderStage stage) noexcept 
    :stage_(stage)
{
}

ShaderStageObject::~ShaderStageObject() noexcept = default;




ShaderObject::ShaderObject()
    : ShaderObject(MakeSharedPtr<ShaderObject::Immutable>())
{
    
}

ShaderObject::ShaderObject(std::shared_ptr<Immutable> immutable) noexcept
    : immutable_(std::move(immutable))
{
}

ShaderObject::~ShaderObject() noexcept = default;

void ShaderObject::AttachStage(ShaderStage stage, const ShaderStageObjectPtr& shader_stage)
{
    auto& curr_shader_stage = immutable_->shader_stages_[std::to_underlying(stage)];
    if (curr_shader_stage != shader_stage)
    {
        curr_shader_stage = shader_stage;
        shader_stages_dirty_ = true;
        hw_res_ready_ = false;
    }
}

const ShaderStageObjectPtr& ShaderObject::Stage(ShaderStage stage) const noexcept
{
    return immutable_->shader_stages_[std::to_underlying(stage)];
}

void ShaderObject::LinkShaders(RenderEffect& effect)
{
    if (shader_stages_dirty_)
    {
        immutable_->is_validate_ = true;
        for (uint32_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
        {
            ShaderStage const stage = static_cast<ShaderStage>(stage_index);
            const auto& shader_stage = this->Stage(stage);
            if (shader_stage)
            {
                immutable_->is_validate_ &= shader_stage->Validate();
            }
        }

        this->DoLinkShaders(effect);

        shader_stages_dirty_ = false;
        hw_res_ready_ = true;
    }
}

#if ZENGINE_IS_DEV_PLATFORM
	std::vector<uint8_t> ShaderStageObject::CompileToDXBC(ShaderStage stage, RenderEffect const& effect, RenderTechnique const& tech,
		RenderPass const& pass, std::vector<std::pair<char const*, char const*>> const& api_special_macros, char const* func_name,
		char const* shader_profile, uint32_t flags, void** reflector, bool strip)
	{
        std::vector<uint8_t> code;
        
        if (reflector != nullptr)
		{
			D3DCompilerLoader::Instance().D3DReflect(code, reflector);
		}
    }
#endif
}