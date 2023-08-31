cmake_minimum_required(VERSION 3.5)
project(opengl C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE on)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("gcc compiler")
    add_definitions(-DPLATFORM_LINUX)

    set(CMAKE_CXX_FLAGS "-g -Wall -m64 -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-m64 -O2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Clang compiler")

    add_definitions(-DPLATFORM_MACOS)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("MSVC compiler")
    set(CMAKE_GENERATOR_PLATFORM x64)
    set(CMAKE_CXX_FLAGS "/Wall /W4 /MP /bigobj /O2  /EHsc /Zc:strictStrings /Zc:rvalueCast  /Gw")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DKLAYGE_SHIP /fp:fast /Ob2 /GL /Qpar")

    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_definitions(-DPLATFORM_WINDOS=1 -DPLATFORM_COMPILER_MSVC=1)
    set(PLATFORM_COMPILER_MSVC = true)
    add_compile_options(
        # Treat angle bracket headers as external headers.
        #/external:anglebrackets

        # Disable warnings from external headers.
        #/external:W0

        # Disable specific warnings:
        /wd4068  # warning C4068: unknown pragma
        /wd4820  # warning C4820: 'xxx': 'x' bytes padding added after data member 'xxx'
        /wd4191  # warning C4191: 'reinterpret_cast': unsafe conversion from 'x' to 'x'
        /wd4625  # copy constructor was implicitly defined as deleted
        /wd5026  # move constructor was implicitly defined as deleted
        /wd4626  # assignment operator was implicitly defined as deleted
        /wd5027  # move assignment operator was implicitly defined as deleted
        /wd4514  # warning C4514: 'x': unreferenced inline function has been removed
        /wd4711  # warning C4711: function 'x' selected for automatic inline expansion (informational)
        /wd4710  # warning C4710: 'x': function not inlined (informational)
        /wd4996  # warning C4996: 'getenv': This function or variable may be unsafe.
        /wd5045  # warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        /wd4061  # warning C4061: enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
        /wd4868  # warning C4868: compiler may not enforce left-to-right evaluation order in braced initializer list
        /wd4100
        /wd4668 #没有将“_WIN32_WINNT_WIN10_RS1”定义为预处理器宏，用“0”替换“
        )
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # windows debug or release
    if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(LIB_DIR_PATH ${LIBRARY_OUTPUT_PATH}/Debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(LIB_DIR_PATH ${LIBRARY_OUTPUT_PATH}/Release)
    endif()
endif()

# if(NOT EXISTS ${PROJECT_3RD_DIR}/stb)
#     file(MAKE_DIRECTORY "${PROJECT_3RD_DIR}/stb")
#     execute_process(
#         COMMAND git clone https://github.com/glfw/glfw ${PROJECT_3RD_DIR}/glfw
#         COMMAND cd ${PROJECT_3RD_DIR}/glfw
#         COMMAND mkdir build && cd build && cmake ../glfw && make -j4 && sudo make install
#     )
# else()

add_subdirectory(math)
file(COPY ${PROJECT_SOURCE_DIR}/math/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(render)
file(COPY ${PROJECT_SOURCE_DIR}/render/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
# add_subdirectory(common)
file(COPY ${PROJECT_SOURCE_DIR}/common/include DESTINATION "${LIBRARY_OUTPUT_PATH}")

IF(MSVC)
    # create vcproj.user file for Visual Studio to set debug working directory
    FUNCTION(CREATE_VCPROJ_USERFILE TARGETNAME)
        SET(SYSTEM_NAME $ENV{USERDOMAIN})
        SET(USER_NAME $ENV{USERNAME})

        CONFIGURE_FILE(
            ${KLAYGE_ROOT_DIR}/cmake/VisualStudio2010UserFile.vcxproj.user.in
            ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user
            @ONLY
        )
    ENDFUNCTION()
ENDIF()