cmake_minimum_required(VERSION 3.10)
project(DX11Project)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)

add_subdirectory(math)
file(COPY ${PROJECT_SOURCE_DIR}/math/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(common)
file(COPY ${PROJECT_SOURCE_DIR}/common/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(Chapter4)