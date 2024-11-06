cmake_minimum_required(VERSION 3.10)
project(DX11Project)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

find_package(DirectX 11 REQUIRED)
include_directories( 
    ${PROJECT_SOURCE_DIR}/common/include
    ${OpenCV_INCLUDE_DIRS} )
link_directories( ${DIRECTX_11_LIBRARIES} )
add_subdirectory(Chapter4)