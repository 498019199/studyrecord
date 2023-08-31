#pragma once
#include <memory>
#include <string_view>
#include <math/math.h>
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

    void InitShader(uint32_t type);
    void BindShader(const char* shader_script);
    void LinkShader();

    uint32_t GetShaderId() { return shader_id_; }
private:
    const char* GetShaderType();

private:
    uint32_t shader_type_ = 0;
    uint32_t shader_id_ = 0;
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
    void Uniform1i(const char*name, int value) const;   
    void Uniform1f(const char*name, float value) const;
    void Uniform3fv(const char*name, const MathWorker::float3& vec) const;
    void UniformMatrix4fv(const char*name, const MathWorker::float4x4& mat) const;

    void AttachShader();
    void UseShader();
    void DetachShader();

    uint32_t GetId() const { return obj_id_; }
private:
    uint32_t obj_id_;
    uint32_t ___;
    PtrIShader pixel_;
    PtrIShader fragment_;
};





}


