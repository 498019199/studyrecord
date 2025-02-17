#include <render/RenderStateObject.h>
#include "D3D11Util.h"

namespace RenderWorker
{
class D3D11SamplerStateObject: public SamplerStateObject
{
public:
    explicit D3D11SamplerStateObject(SamplerStateDesc const & desc);

    ID3D11SamplerState* D3DSamplerState() const
    {
        return sampler_state_.get();
    }

private:
    ID3D11SamplerStatePtr sampler_state_;
};
}
