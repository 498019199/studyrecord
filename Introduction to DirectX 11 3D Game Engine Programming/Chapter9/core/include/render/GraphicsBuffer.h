#pragma once

#include <core/common.h>
#include <render/ElementFormat.h>

namespace RenderWorker
{

enum BufferUsage
{
    BU_Static,
    BU_Dynamic
};

enum BufferAccess
{
    BA_Read_Only,
    BA_Write_Only,
    BA_Read_Write,
    BA_Write_No_Overwrite
};

class GraphicsBuffer
{
public:
	GraphicsBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, uint32_t structure_byte_stride);
	virtual ~GraphicsBuffer() noexcept;
    
    uint32_t Size() const noexcept
    {
        return size_in_byte_;
    }

    BufferUsage Usage() const noexcept
    {
        return usage_;
    }

    uint32_t AccessHint() const noexcept
    {
        return access_hint_;
    }

    uint32_t StructureByteStride() const noexcept
    {
        return structure_byte_stride_;
    }
    
protected:
    BufferUsage usage_;
    uint32_t access_hint_;

    uint32_t size_in_byte_;
    uint32_t structure_byte_stride_;
};

using GraphicsBufferPtr = std::shared_ptr<GraphicsBuffer>;
}