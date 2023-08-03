#pragma once
#include <memory>
#include <string_view>
namespace RenderWorker
{
class IShader;
using PtrIShader = std::shared_ptr<IShader>;
class ShaderObject;
using PtrShaderobject = std::shared_ptr<ShaderObject>;

class IShader
{
public:   
    ~IShader();

    void InitShader(int type);
    void BindShader(const char* shader_script);
    void LinkShader();

    int GetShaderId() { return shader_id_; }
private:
    const char* GetShaderType();

private:
    int shader_type_ = 0;
    int shader_id_ = 0;
};

// 像素着色器
class PixelShader:public IShader
{};

// 片元着色器
class FragmentShader:public IShader
{};

// 着色器程序对象(Shader Program Object)
class ShaderObject
{
public:
    ShaderObject();
    ~ShaderObject();

    void LoadShader(const std::string_view& vertexPath, const std::string_view& fragmentPath);

    // uniform工具函数
    void SetBool(const char*name,  bool value) const;  
    void SetInt(const char*name, int value) const;   
    void SetFloat(const char*name, float value) const;

    void AttachShader();
    void UseShader();
    void DetachShader();
private:
    uint32_t obj_id_;
    PtrIShader pixel_;
    PtrIShader fragment_;
};




}


