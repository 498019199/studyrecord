#include <core/common.h>

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