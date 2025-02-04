cmake_minimum_required(VERSION 3.10)
project(DX11Project)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
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

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4061")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4005")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4820")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5246")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4838")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4668")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4365")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5219")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5029")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5267")
endif()


#add_subdirectory(${PROJECT_3RD_DIR}/d3dcompiler)

add_subdirectory(math)
file(COPY ${PROJECT_SOURCE_DIR}/math/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(common)
file(COPY ${PROJECT_SOURCE_DIR}/common/include DESTINATION "${LIBRARY_OUTPUT_PATH}")

#add_subdirectory(Chapter4)
add_subdirectory(Chapter6) 