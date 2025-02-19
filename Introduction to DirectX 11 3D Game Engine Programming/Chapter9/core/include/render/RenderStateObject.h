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

    friend bool operator<(const SamplerStateDesc&);
};
//static_assert(sizeof(SamplerStateDesc) == 49);

class SamplerStateObject
{
public:
    explicit SamplerStateObject(const SamplerStateDesc& lhs, const SamplerStateDesc& rhs)
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

enum PolygonMode
{
    PM_Point,
    PM_Line,
    PM_Fill
};

enum ShadeMode
{
    SM_Flat,
    SM_Gouraud
};

enum CullMode
{
    CM_None,
    CM_Front,
    CM_Back
};

struct RasterizerStateDesc
{
    PolygonMode			polygon_mode;
    ShadeMode			shade_mode;
    CullMode			cull_mode;
    bool				front_face_ccw;
    float				polygon_offset_factor;
    float				polygon_offset_units;
    bool				depth_clip_enable;
    bool				scissor_enable;
    bool				multisample_enable;
};
//static_assert(sizeof(RasterizerStateDesc) == 24);

enum BlendOperation
{
    BOP_Add		= 1,
    BOP_Sub		= 2,
    BOP_Rev_Sub	= 3,
    BOP_Min		= 4,
    BOP_Max		= 5,
};

enum AlphaBlendFactor
{
    ABF_Zero,
    ABF_One,
    ABF_Src_Alpha,
    ABF_Dst_Alpha,
    ABF_Inv_Src_Alpha,
    ABF_Inv_Dst_Alpha,
    ABF_Src_Color,
    ABF_Dst_Color,
    ABF_Inv_Src_Color,
    ABF_Inv_Dst_Color,
    ABF_Src_Alpha_Sat,
    ABF_Blend_Factor,
    ABF_Inv_Blend_Factor,
    ABF_Src1_Alpha,
    ABF_Inv_Src1_Alpha,
    ABF_Src1_Color,
    ABF_Inv_Src1_Color
};

enum LogicOperation
{
    LOP_Clear,
    LOP_Set,
    LOP_Copy,
    LOP_CopyInverted,
    LOP_Noop,
    LOP_Invert,
    LOP_And,
    LOP_NAnd,
    LOP_Or,
    LOP_NOR,
    LOP_XOR,
    LOP_Equiv,
    LOP_AndReverse,
    LOP_AndInverted,
    LOP_OrReverse,
    LOP_OrInverted
};

struct BlendStateDesc
{
    Color blend_factor;
    uint32_t sample_mask;

    bool				alpha_to_coverage_enable;
    bool				independent_blend_enable;

    std::array<bool, 8>				blend_enable;
    std::array<bool, 8>				logic_op_enable;
    std::array<BlendOperation, 8>	blend_op;
    std::array<AlphaBlendFactor, 8>	src_blend;
    std::array<AlphaBlendFactor, 8>	dest_blend;
    std::array<BlendOperation, 8>	blend_op_alpha;
    std::array<AlphaBlendFactor, 8>	src_blend_alpha;
    std::array<AlphaBlendFactor, 8>	dest_blend_alpha;
    std::array<LogicOperation, 8>	logic_op;
    std::array<uint8_t, 8>			color_write_mask;
};

struct DepthStencilStateDesc
{
    bool				depth_enable;
    bool				depth_write_mask;
};
class RenderStateObject
{
public:
    RenderStateObject(const RasterizerStateDesc& rs_desc, const DepthStencilStateDesc& dss_desc, const BlendStateDesc& bs_desc);
    virtual ~RenderStateObject() noexcept;

    const RasterizerStateDesc& GetRasterizerStateDesc() const noexcept { return rs_desc_; }
    const DepthStencilStateDesc& GetDepthStencilStateDesc() const noexcept { return dss_desc_; }
    const BlendStateDesc& GetBlendStateDesc() const noexcept { return bs_desc_; }

    virtual void Active() = 0;
protected:
    RasterizerStateDesc rs_desc_;
    DepthStencilStateDesc dss_desc_;
    BlendStateDesc bs_desc_;
};
using RenderStateObjectPtr = std::shared_ptr<RenderStateObject>;
}
