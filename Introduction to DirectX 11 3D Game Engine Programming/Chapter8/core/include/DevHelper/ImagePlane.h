#pragma once
#include <core/common.h>
#include <core/Texture.h>

class ImagePlane
{
public:
    bool Load(std::string_view name);
};


class TexConverter final
{
static void GetImageInfo(std::string_view input_name, Texture::TextureType& type, uint32_t& width, uint32_t& height,
    uint32_t& depth, uint32_t& num_mipmaps, uint32_t& array_size, ElementFormat& format, uint32_t& row_pitch,
    uint32_t& slice_pitch);
};