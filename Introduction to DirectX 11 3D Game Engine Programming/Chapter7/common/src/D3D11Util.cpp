#include <common/D3D11Util.h>

#include <format>
#include <utility>
std::string CombineFileLine(std::string_view file, uint32_t line)
{
    return std::format("{}: {}", std::move(file), line);
}

// 把一个wstring转化为wstring
/////////////////////////////////////////////////////////////////////////////////
std::wstring& Convert(std::wstring& dest, std::wstring_view src)
{
    dest = std::wstring(src);

    return dest;
}

// 把一个string转化为wstring
/////////////////////////////////////////////////////////////////////////////////
std::wstring& Convert(std::wstring& dest, std::string_view src)
{
    int const wcs_len = MultiByteToWideChar(CP_ACP, 0, src.data(), static_cast<int>(src.size()), nullptr, 0);
    auto tmp = std::make_unique<wchar_t[]>(wcs_len + 1);
    MultiByteToWideChar(CP_ACP, 0, src.data(), static_cast<int>(src.size()), tmp.get(), wcs_len);
	dest.assign(&tmp[0], &tmp[wcs_len]);
	return dest;
}

HRESULT CreateShaderFromFile(const std::string& filename,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut)
{
    std::wstring swcFileName;
    Convert(swcFileName, filename);
	std::wstring strOutFile = swcFileName + L".cso";
    std::wstring InputFile = swcFileName + L".hlsl";
    return CreateShaderFromFile(strOutFile.c_str(), InputFile.c_str(), entryPoint, shaderModel, ppBlobOut);
}

HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut,
	const WCHAR* hlslFileName,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    // 寻找是否有已经编译好的顶点着色器
    if (csoFileNameInOut && D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK)
    {
        return hr;
    }
    else
    {
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // 设置 D3DCOMPILE_DEBUG 标志用于获取着色器调试信息。该标志可以提升调试体验，
        // 但仍然允许着色器进行优化操作
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // 在Debug环境下禁用优化以避免出现一些不合理的情况
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
        ID3DBlob* errorBlob = nullptr;
        hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
            dwShaderFlags, 0, ppBlobOut, &errorBlob);
        if (FAILED(hr))
        {
            if (errorBlob != nullptr)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
            }
            ReleaseCOM(errorBlob);
            return hr;
        }

        // 若指定了输出文件名，则将着色器二进制信息输出
        if (csoFileNameInOut)
        {
            return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
        }
    }

    return hr;
}
