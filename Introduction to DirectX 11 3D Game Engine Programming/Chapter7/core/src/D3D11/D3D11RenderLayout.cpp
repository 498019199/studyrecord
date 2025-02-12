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

const D3D11_INPUT_ELEMENT_DESC inputLayout[3] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

ID3D11InputLayout* D3D11RenderLayout::InputLayout(const RenderEffect& effect) const
{
    if (!vertex_elems_.empty())
    {
        auto blob = effect.VsCode();
        const auto& re = Context::Instance().RenderEngineInstance().D3DDevice();
        ID3D11InputLayoutPtr new_layout;
        // TIFHR(re->CreateInputLayout(&vertex_elems_[0], static_cast<UINT>(vertex_elems_.size()),
        //     blob->GetBufferPointer(), blob->GetBufferSize(), new_layout.put()));
        TIFHR(re->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout),
            blob->GetBufferPointer(), blob->GetBufferSize(), new_layout.put()));
        auto* new_layout_raw = new_layout.get();
		return new_layout_raw;
    }

    return nullptr;
}

void D3D11RenderLayout::VertexStreamFormat(uint32_t index, std::span<const VertexElement> vet)
{
    vertex_streams_[index].format.assign(vet.begin(), vet.end());
    uint32_t size = 0;
    for (size_t i = 0; i < vet.size(); ++ i)
    {
        size += vet[i].element_size();
    }
    
    vertex_streams_[index].vertex_size = size;
    streams_dirty_ = true;
}

uint32_t D3D11RenderLayout::VertexStreamNum() const
{
    return static_cast<uint32_t>(vertex_streams_.size());
}

bool D3D11RenderLayout::UseIndices() const
{
    return this->IndicesNum() != 0;
}

uint32_t D3D11RenderLayout::IndicesNum() const
{
    uint32_t n = 0;
    if (index_stream_)
    {
        if (0xFFFFFFFF == force_num_indices_)
        {
            n = index_stream_->Size() / NumFormatBytes(index_format_);
        }
        else
        {
            n = force_num_indices_;
        }
    }
    return n;
}

uint32_t D3D11RenderLayout::NumVertices() const
{
	uint32_t n;
    if (0xFFFFFFFF == force_num_vertices_)
    {
        n = vertex_streams_[0].stream->Size() / vertex_streams_[0].vertex_size;
    }
    else
    {
        n = force_num_vertices_;
    }
    return n;
}