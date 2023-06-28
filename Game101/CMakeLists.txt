cmake_minimum_required(VERSION 3.2)
project(game101)
set(CMAKE_CXX_FLASS )

add_subdirectory(math)

file(${PROJECT_SOURCE_DIR}/math/include ${PROJECT_SOURCE_DIR}/include/math)