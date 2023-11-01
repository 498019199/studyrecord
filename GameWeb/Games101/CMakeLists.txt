cmake_minimum_required(VERSION 3.10)
project(Rasterizer)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV  REQUIRED)
include_directories( 
    ${PROJECT_SOURCE_DIR}/common/include
    ${OpenCV_INCLUDE_DIRS} )
link_directories( ${OpenCV_LIB_DIR} )

#add_subdirectory(PA01)
add_subdirectory(PA02)
