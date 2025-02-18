#pragma once
#include <core/Util.h>
#include <core/common.h>

namespace RenderWorker
{
// Sampler addressing modes - default is TAM_Wrap.
enum TexAddressingMode
{
    // Texture wraps at values over 1.0
    TAM_Wrap,
    // Texture mirrors (flips) at joins over 1.0
    TAM_Mirror,
    // Texture clamps at 1.0
    TAM_Clamp,
    // Texture coordinates outside the range [0.0, 1.0] are set to the border color.
    TAM_Border
};

enum TexFilterOp
{
    // Dont' use these enum directly
    TFOE_Mip_Point = 0x0,
    TFOE_Mip_Linear = 0x1,
    TFOE_Mag_Point = 0x0,
    TFOE_Mag_Linear = 0x2,
    TFOE_Min_Point = 0x0,
    TFOE_Min_Linear = 0x4,
    TFOE_Anisotropic = 0x08,
    TFOE_Comparison = 0x10,

    // Use these
    TFO_Min_Mag_Mip_Point				= TFOE_Min_Point  | TFOE_Mag_Point  | TFOE_Mip_Point,
    TFO_Min_Mag_Point_Mip_Linear		= TFOE_Min_Point  | TFOE_Mag_Point  | TFOE_Mip_Linear,
    TFO_Min_Point_Mag_Linear_Mip_Point	= TFOE_Min_Point  | TFOE_Mag_Linear | TFOE_Mip_Point,
    TFO_Min_Point_Mag_Mip_Linear		= TFOE_Min_Point  | TFOE_Mag_Linear | TFOE_Mip_Linear,
    TFO_Min_Linear_Mag_Mip_Point		= TFOE_Min_Linear | TFOE_Mag_Point  | TFOE_Mip_Point,
    TFO_Min_Linear_Mag_Point_Mip_Linear	= TFOE_Min_Linear | TFOE_Mag_Point  | TFOE_Mip_Linear,
    TFO_Min_Mag_Linear_Mip_Point		= TFOE_Min_Linear | TFOE_Mag_Linear | TFOE_Mip_Point,
    TFO_Min_Mag_Mip_Linear				= TFOE_Min_Linear | TFOE_Mag_Linear | TFOE_Mip_Linear,
    TFO_Anisotropic						= TFOE_Anisotropic,

    TFO_Cmp_Min_Mag_Mip_Point				= TFOE_Comparison | TFO_Min_Mag_Mip_Point,
    TFO_Cmp_Min_Mag_Point_Mip_Linear		= TFOE_Comparison | TFO_Min_Mag_Point_Mip_Linear,
    TFO_Cmp_Min_Point_Mag_Linear_Mip_Point	= TFOE_Comparison | TFO_Min_Point_Mag_Linear_Mip_Point,
    TFO_Cmp_Min_Point_Mag_Mip_Linear		= TFOE_Comparison | TFO_Min_Point_Mag_Mip_Linear,
    TFO_Cmp_Min_Linear_Mag_Mip_Point		= TFOE_Comparison | TFO_Min_Linear_Mag_Mip_Point,
    TFO_Cmp_Min_Linear_Mag_Point_Mip_Linear	= TFOE_Comparison | TFO_Min_Linear_Mag_Point_Mip_Linear,
    TFO_Cmp_Min_Mag_Linear_Mip_Point		= TFOE_Comparison | TFO_Min_Mag_Linear_Mip_Point,
    TFO_Cmp_Min_Mag_Mip_Linear				= TFOE_Comparison | TFO_Min_Mag_Mip_Linear,
    TFO_Cmp_Anisotropic						= TFOE_Comparison | TFO_Anisotropic
};

enum CompareFunction
{
    CF_AlwaysFail,
    CF_AlwaysPass,
    CF_Less,
    CF_LessEqual,
    CF_Equal,
    CF_NotEqual,
    CF_GreaterEqual,
    CF_Greater
};

struct SamplerStateDesc
{
    Color border_clr; // 边界外的颜色，使用D3D11_TEXTURE_BORDER_COLOR时需要指定

    TexAddressingMode addr_mode_u; // U方向寻址模式
    TexAddressingMode addr_mode_v; // V方向寻址模式
    TexAddressingMode addr_mode_w; // W方向寻址模式

    TexFilterOp filter; // 所选过滤器

    uint8_t max_anisotropy; // 最大各向异性等级(1-16)
    float min_lod; // 若mipmap等级低于MinLOD，则使用等级MinLOD。最小允许设为0
    float max_lod; // 若mipmap等级高于MaxLOD，则使用等级MaxLOD。必须比MinLOD大  
    float mip_map_lod_bias; // mipmap等级偏移值，最终算出的mipmap等级会加上该偏移值

    CompareFunction cmp_func;

    SamplerStateDesc();

    friend bool operator<(SamplerStateDesc const & lhs, SamplerStateDesc const & rhs);
};
//static_assert(sizeof(SamplerStateDesc) == 49);

class SamplerStateObject
{
public:
    explicit SamplerStateObject(SamplerStateDesc const & desc)
        : desc_(desc)
    {
    }

    virtual ~SamplerStateObject()
    {
    }

    SamplerStateDesc const & GetDesc() const
    {
        return desc_;
    }

protected:
    SamplerStateDesc desc_;
};
using SamplerStateObjectPtr = std::shared_ptr<SamplerStateObject>;
}
