ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/Wall /W4 /EHsc /bigobj /Zc:strictStrings /Zc:rvalueCast /Gw")
    if(CMAKE_GENERATOR MATCHES "^Visual Studio")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif()
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    
    if(CMAKE_C_COMPILER_ID MATCHES Clang)
        message("Clang compiler")
        set(ZENGINE_COMPILER_NAME "clangcl")
        set(ZENGINE_COMPILER_CLANGCL TRUE)
    else()
        message("MSVC compiler")
        SET(ZENGINE_COMPILER_NAME "vc")
        SET(ZENGINE_COMPILER_MSVC TRUE)

        if(MSVC_VERSION GREATER_EQUAL 1930)
            set(ZENGINE_COMPILER_VERSION "143")
        elseif(MSVC_VERSION GREATER_EQUAL 1920)
            set(ZENGINE_COMPILER_VERSION "142")
        else()
            message(FATAL_ERROR "Unsupported compiler version. Please install VS2019 or up.")
        endif()

        if(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION VERSION_GREATER_EQUAL 10.0.22000)
            set(WIN11_SDK TRUE)
        else()
            set(WIN11_SDK FALSE)
        endif()

		if((MSVC_VERSION GREATER_EQUAL 1929) AND ((NOT ZENGINE_PLATFORM_WINDOWS) OR WIN11_SDK))
            set(CMAKE_CXX_STANDARD 20)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
        else()
            set(CMAKE_CXX_STANDARD 17)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
        endif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:throwingNew /permissive- /Zc:externConstexpr /Zc:__cplusplus")
        if((MSVC_VERSION GREATER_EQUAL 1925) AND WIN11_SDK)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
        endif()
        if(MSVC_VERSION GREATER_EQUAL 1935)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:templateScope")
        endif()
        if(ZENGINE_ARCH_NAME STREQUAL "x64")
            #SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qspectre")
        endif()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /JMC")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4061") # False positive on missing enum in switch case (This is a bad designed warning because there are "default"s to handle un-cased enums)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4255") # Allow func() to func(void) in some Windows SDK
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4365") # Ignore int to size_t
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4464") # Allow .. in include path
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514") # Allow unused inline function
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4623") # Ignore implicitly deleted default constructor
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4625") # Ignore implicitly deleted copy constructor
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4626") # Ignore implicitly deleted copy operator=
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4668") # Undefined macro as 0
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4710") # Allow function with the inline mark not be inlined
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4711") # Allow function to be inlined without the inline mark
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4820") # Ignore padding
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5026") # Ignore implicitly deleted move constructor
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5027") # Ignore implicitly deleted move operator=
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5039") # Ignore passing a throwing function to C functions
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5045") # False positive on range check
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5204") # Ignore non trivial destructor in COM interfaces and ppl
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5219") # Ignore int to uint
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5220") # Ignore non trivial constructor in ppl
		if(MSVC_VERSION GREATER_EQUAL 1934)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5262") # Ignore implicit fall-through
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5264") # Ignore unused const variable
		endif()

        # 临时处理
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100") # 屏蔽不引用
		SET(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
    endif()

    IF(ZENGINE_ARCH_NAME MATCHES "x86")
        FOREACH(flag_var
            CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_MINSIZEREL)
            SET(${flag_var} "${${flag_var}} /arch:SSE")
        ENDFOREACH()
        FOREACH(flag_var
            CMAKE_EXE_LINKER_FLAGS CMAKE_SHARED_LINKER_FLAGS)
            SET(${flag_var} "${${flag_var}} /LARGEADDRESSAWARE")
        ENDFOREACH()
    ENDIF()

    ADD_DEFINITIONS(-DWIN32 -D_WINDOWS)
    IF(ZENGINE_ARCH_NAME MATCHES "arm")
        ADD_DEFINITIONS(-D_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE=1)

        IF(ZENGINE_PLATFORM_WINDOWS_DESKTOP)
            FOREACH(flag_var
                CMAKE_C_STANDARD_LIBRARIES CMAKE_CXX_STANDARD_LIBRARIES)
                SET(${flag_var} "${${flag_var}} gdi32.lib ole32.lib oleaut32.lib comdlg32.lib advapi32.lib shell32.lib")
            ENDFOREACH()
        ENDIF()
    ENDIF()
else()
    if(CMAKE_C_COMPILER_ID MATCHES Clang)
        set(ZENGINE_COMPILER_NAME "clang")
        set(ZENGINE_COMPILER_CLANG TRUE)
    elseif(MINGW)
        set(ZENGINE_COMPILER_NAME "mgw")
        set(ZENGINE_COMPILER_GCC TRUE)
    else()
        set(ZENGINE_COMPILER_NAME "gcc")
        set(ZENGINE_COMPILER_GCC TRUE)
    endif()
endif()

SET(ZENGINE_OUTPUT_SUFFIX _${ZENGINE_COMPILER_NAME}${ZENGINE_COMPILER_VERSION})

