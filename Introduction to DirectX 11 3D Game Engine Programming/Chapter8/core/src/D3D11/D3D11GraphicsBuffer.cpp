#include <core/D3D11GraphicsBuffer.h>
#include <core/D3D11RenderEngine.h>
#include <core/Context.h>
#include <core/Util.h>

D3D11GraphicsBuffer::D3D11GraphicsBuffer(BufferUsage usage, uint32_t access_hint, uint32_t bind_flags,
            uint32_t size_in_byte, uint32_t structure_byte_stride)
            :usage_(usage), access_hint_(access_hint), size_in_byte_(size_in_byte), structure_byte_stride_(structure_byte_stride),
            bind_flags_(bind_flags)
{
    const auto& re = Context::Instance().RenderEngineInstance();
    d3d_device_ = re.D3DDevice();
    d3d_imm_ctx_ = re.D3DDeviceImmContext();
}

void D3D11GraphicsBuffer::GetD3DFlags(D3D11_USAGE& usage, UINT& cpu_access_flags, UINT& bind_flags, UINT& misc_flags)
{
    if (access_hint_ & EAH_Immutable)
    {
        usage = D3D11_USAGE_IMMUTABLE;
    }
    else
    {
        if ((EAH_CPU_Write == access_hint_) || ((EAH_CPU_Write | EAH_GPU_Read) == access_hint_))
        {
            usage = D3D11_USAGE_DYNAMIC;
        }
        else
        {
            if (!(access_hint_ & EAH_CPU_Read) && !(access_hint_ & EAH_CPU_Write))
            {
                usage = D3D11_USAGE_DEFAULT;
            }
            else
            {
                usage = D3D11_USAGE_STAGING;
            }
        }
    }

    cpu_access_flags = 0;
    if (access_hint_ & EAH_CPU_Read)
    {
        cpu_access_flags |= D3D11_CPU_ACCESS_READ;
    }
    if (access_hint_ & EAH_CPU_Write)
    {
        cpu_access_flags |= D3D11_CPU_ACCESS_WRITE;
    }

    if (D3D11_USAGE_STAGING == usage)
    {
        bind_flags = 0;
    }
    else
    {
        bind_flags = bind_flags_;
    }
    if (bind_flags != D3D11_BIND_CONSTANT_BUFFER)
    {
        if ((access_hint_ & EAH_GPU_Read) && !(access_hint_ & EAH_CPU_Write))
        {
            bind_flags |= D3D11_BIND_SHADER_RESOURCE;
        }
        if (access_hint_ & EAH_GPU_Write)
        {
            if (!((access_hint_ & EAH_GPU_Structured) || (access_hint_ & EAH_GPU_Unordered)))
            {
                bind_flags |= D3D11_BIND_STREAM_OUTPUT;
            }
        }
        if (access_hint_ & EAH_GPU_Unordered)
        {
            bind_flags |= D3D11_BIND_UNORDERED_ACCESS;
        }
    }

    misc_flags = 0;
    if (access_hint_ & EAH_GPU_Unordered)
    {
        misc_flags |= (access_hint_ & EAH_GPU_Structured)
            ? D3D11_RESOURCE_MISC_BUFFER_STRUCTURED : D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    }
    if (access_hint_ & EAH_DrawIndirectArgs)
    {
        misc_flags |= D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
    }
}

void D3D11GraphicsBuffer::CreateHWResource(void const * init_data)
{
    D3D11_SUBRESOURCE_DATA subres_init;
    D3D11_SUBRESOURCE_DATA* p_subres = nullptr;
    if (init_data != nullptr)
    {
        subres_init.pSysMem = init_data;
        subres_init.SysMemPitch = size_in_byte_;
        subres_init.SysMemSlicePitch = size_in_byte_;

        p_subres = &subres_init;
    }

    D3D11_BUFFER_DESC desc = {};
    this->GetD3DFlags(desc.Usage, desc.CPUAccessFlags, desc.BindFlags, desc.MiscFlags);
    desc.ByteWidth = size_in_byte_;
    desc.StructureByteStride = structure_byte_stride_;

    TIFHR(d3d_device_->CreateBuffer(&desc, p_subres, d3d_buffer_.put()));
}

void D3D11GraphicsBuffer::DeleteHWResource()
{
    d3d_buffer_.reset();
}

void* D3D11GraphicsBuffer::Map(BufferAccess ba)
{
    COMMON_ASSERT(d3d_buffer_);

    D3D11_MAP type;
    switch (ba)
    {
    case BA_Read_Only:
        type = D3D11_MAP_READ;
        break;

    case BA_Write_Only:
        if ((EAH_CPU_Write == access_hint_) || ((EAH_CPU_Write | EAH_GPU_Read) == access_hint_))
        {
            type = D3D11_MAP_WRITE_DISCARD;
        }
        else
        {
            type = D3D11_MAP_WRITE;
        }
        break;

    case BA_Read_Write:
        type = D3D11_MAP_READ_WRITE;
        break;

    case BA_Write_No_Overwrite:
        type = D3D11_MAP_WRITE_NO_OVERWRITE;
        break;
    }

    D3D11_MAPPED_SUBRESOURCE mapped;
    TIFHR(d3d_imm_ctx_->Map(d3d_buffer_.get(), 0, type, 0, &mapped));
    return mapped.pData;
}

void D3D11GraphicsBuffer::Unmap()
{
    COMMON_ASSERT(d3d_buffer_);

    d3d_imm_ctx_->Unmap(d3d_buffer_.get(), 0);
}
