cmake_minimum_required(VERSION 3.10)
project(DX11Project)


include(${PROJECT_SOURCE_DIR}/cmake/Compiler.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/Platform.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
set(ZENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if(WIN7_SYSTEM_SUPPORT MATCHES ON)
        add_compile_definitions(_WIN32_WINNT=0x601)
    endif()
    
    # # 编译器设置 UTF-8 编码
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # windows debug or release
    if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(LIB_DIR_PATH ${LIBRARY_OUTPUT_PATH}/Debug)
        set(3RD_DEBUG_POSTFIX "d" CACHE STRING "")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(LIB_DIR_PATH ${LIBRARY_OUTPUT_PATH}/Release)
    endif()

    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif()

add_subdirectory(3rd)
add_subdirectory(math)
file(COPY ${PROJECT_SOURCE_DIR}/math/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(${PROJECT_3RD_DIR}/imgui)

#add_subdirectory(Chapter4)
#add_subdirectory(Chapter6) 
#add_subdirectory(Chapter7)
add_subdirectory(Chapter8)