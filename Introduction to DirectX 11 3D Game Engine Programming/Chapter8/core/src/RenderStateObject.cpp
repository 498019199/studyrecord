#include <render/RenderStateObject.h>

namespace RenderWorker
{

SamplerStateDesc::SamplerStateDesc()
: border_clr(0, 0, 0, 0),
    addr_mode_u(TAM_Wrap), addr_mode_v(TAM_Wrap), addr_mode_w(TAM_Wrap),
    filter(TFO_Min_Mag_Mip_Point),
    max_anisotropy(16),
    min_lod(0), max_lod(std::numeric_limits<float>::max()),
    mip_map_lod_bias(0),
    cmp_func(CF_AlwaysFail)
{
}

bool operator<(SamplerStateDesc const & lhs, SamplerStateDesc const & rhs)
{
    return std::memcmp(&lhs, &rhs, sizeof(lhs)) < 0;
}

}