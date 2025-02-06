#include <core/D3D11RenderLayout.h>


void D3D11RenderLayout::BindVertexStream(const GraphicsBufferPtr& buffer, VertexElement const& vet,
    stream_type type = ST_Geometry, uint32_t freq = 1)
{
    BindVertexStream(buffer, std::span<const VertexElement, 1>(val, 1),type, freq);
}

void D3D11RenderLayout::BindVertexStream(const GraphicsBufferPtr& buffer, std::span<const VertexElement> vet,
			stream_type type = ST_Geometry, uint32_t freq = 1)
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
            std::span<ElementFormat> fvet(vertex_streams_[i].format);
            if (fvet == vet)
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

void D3D11RenderLayout::BindIndexStream(const GraphicsBufferPtr& index_stream, ElementFormat format)
{
    COMMON_ASSERT((EF_R16UI == format) || (EF_R32UI == format));

    index_stream_ = buffer;
    index_format_ = format;

    streams_dirty_ = true;
}