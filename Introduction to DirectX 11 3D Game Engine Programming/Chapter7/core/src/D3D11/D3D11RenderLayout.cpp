#include <core/D3D11GraphicsBuffer.h>
#include <core/D3D11RenderLayout.h>
#include <core/D3D11RenderEngine.h>
#include <core/D3D11Util.h>
#include <core/RenderEffect.h>
#include <core/Context.h>

void D3D11RenderLayout::BindVertexStream(const GraphicsBufferPtr& buffer, VertexElement const& vet,
    stream_type type /*= ST_Geometry*/, uint32_t freq/* = 1*/)
{
    BindVertexStream(buffer, MakeSpan<1>(vet), type, freq);
}

void D3D11RenderLayout::BindVertexStream(const GraphicsBufferPtr& buffer, std::span<const VertexElement> vet,
			stream_type type /*= ST_Geometry*/, uint32_t freq/* = 1*/)
{
    COMMON_ASSERT(buffer);

    uint32_t size = 0;
    for (size_t i = 0; i < vet.size(); ++i)
    {
        size += vet[i].element_size();
    }

    if (ST_Geometry == type)
    {
        for (size_t i = 0; i < vertex_streams_.size(); ++ i)
        {
            if (MakeSpan(vertex_streams_[i].format) == vet)
            {
                vertex_streams_[i].stream = buffer;
                vertex_streams_[i].vertex_size = size;
                vertex_streams_[i].type = type;
                vertex_streams_[i].freq = freq;

                streams_dirty_ = true;
                return;
            }
        }

        auto& vs = vertex_streams_.emplace_back();
        vs.stream = buffer;
        vs.format.assign(vet.begin(), vet.end());
        vs.vertex_size = size;
        vs.type = type;
        vs.freq = freq;
    }
}

void D3D11RenderLayout::BindIndexStream(const GraphicsBufferPtr& buffer, ElementFormat format)
{
    COMMON_ASSERT((EF_R16UI == format) || (EF_R32UI == format));

    index_stream_ = buffer;
    index_format_ = format;

    streams_dirty_ = true;
}

void D3D11RenderLayout::Active() const
{
    if (streams_dirty_)
    {
        uint32_t const num_vertex_streams = VertexStreamNum();
        vertex_elems_.clear();
        vertex_elems_.reserve(num_vertex_streams);

        vbs_.resize(num_vertex_streams);
        strides_.resize(num_vertex_streams);
        offsets_.resize(num_vertex_streams);
        for (uint32_t i = 0; i < num_vertex_streams; ++ i)
        {
            std::vector<D3D11_INPUT_ELEMENT_DESC> stream_elems;
            D3D11Mapping::Mapping(stream_elems, i, VertexStreamFormat(i), vertex_streams_[i].type, vertex_streams_[i].freq);
            vertex_elems_.insert(vertex_elems_.end(), stream_elems.begin(), stream_elems.end());

            const D3D11GraphicsBuffer& d3dvb = *GetVertexStream(i);
            vbs_[i] = d3dvb.D3DBuffer();
            strides_[i] = VertexSize(i);
            offsets_[i] = 0;
        }
    }
}

ID3D11InputLayout* D3D11RenderLayout::InputLayout(const RenderEffect& effect) const
{
    auto blob = effect.VsCode();
    const auto& re = Context::Instance().RenderEngineInstance().D3DDevice();
    ID3D11InputLayoutPtr new_layout;
    TIFHR(re->CreateInputLayout(&vertex_elems_[0], static_cast<UINT>(vertex_elems_.size()),
        blob->GetBufferPointer(), blob->GetBufferSize(), new_layout.put()));
}