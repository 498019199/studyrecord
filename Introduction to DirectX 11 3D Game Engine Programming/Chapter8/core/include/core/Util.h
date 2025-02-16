#pragma once
#include <string>
#include <string_view>
#include <bit>
#include <utility>
#include <utility>
#include <memory>
#include <core/macro.h>

#if defined(ZENGINE_CXX23_LIBRARY_UNREACHABLE_SUPPORT)
    #include <utility>
#else
    namespace std
    {
        [[noreturn]] inline void unreachable()
        {
    #if defined(ZENGINE_COMPILER_MSVC)
            __assume(false);
    #else
            __builtin_unreachable();
    #endif
        }
    } // namespace std
#endif

#ifdef _DEBUG
	#define COMMON_ASSERT(val) assert(val)
#else
	#define COMMON_ASSERT(val) 
#endif//_DEBUG

#define KFL_UNREACHABLE(msg) std::unreachable()

std::string& Convert(std::string& dest, std::wstring_view src);
std::wstring& Convert(std::wstring& dest, std::string_view src);

// 产生FourCC常量
template <unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3>
struct MakeFourCC
{
	static uint32_t constexpr value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24);
};

// Endian的转换
template <int size>
void EndianSwitch(void* p) noexcept;

template <typename T>
T Native2BE(T x) noexcept
{
    if constexpr (std::endian::native == std::endian::little)
    {
        EndianSwitch<sizeof(T)>(&x);
    }
    return x;
}
template <typename T>
T Native2LE(T x) noexcept
{
    if constexpr (std::endian::native == std::endian::big)
    {
        EndianSwitch<sizeof(T)>(&x);
    }
    return x;
}

template <typename T>
T BE2Native(T x) noexcept
{
    return Native2BE(x);
}
template <typename T>
T LE2Native(T x) noexcept
{
    return Native2LE(x);
}

template <typename T, typename... Args>
inline std::shared_ptr<T> MakeSharedPtr(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUniquePtrHelper(std::false_type, Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUniquePtrHelper(std::true_type, size_t size)
{
    static_assert(0 == std::extent<T>::value,
        "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

    return std::make_unique<T>(size);
}

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUniquePtr(Args&&... args)
{
    return MakeUniquePtrHelper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}