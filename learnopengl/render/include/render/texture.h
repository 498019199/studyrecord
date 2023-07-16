#pragma once
#include <memory>
#include <string_view>

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();

    void LoadImage(const std::string_view& filename);

private:
    uint32_t id_;
    int width_;
    int height_;
};
