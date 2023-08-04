cmake_minimum_required(VERSION 3.5)
project(opengl C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE on)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

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
    set(CMAKE_CXX_FLAGS "-Wall /O2  /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "/OX  /EHsc")

    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options(/wd4514) 
    add_compile_options(/wd4100) 
    add_definitions(-DPLATFORM_WINDOWS)
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