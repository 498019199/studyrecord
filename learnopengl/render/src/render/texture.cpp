#include <render/texture.h>
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace RenderWorker
{


Texture2D::Texture2D()
{
    // 创建纹理对象
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
}

Texture2D::~Texture2D()
{
}

void Texture2D::LoadImage(const std::string_view& filename)
{
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int nrChannels;
    unsigned char *data  = stbi_load(filename.data(), &width_, &height_, &nrChannels, 0);
    if (nullptr != data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
}

void Texture2D::BindTexture()
{
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id_);
}
}