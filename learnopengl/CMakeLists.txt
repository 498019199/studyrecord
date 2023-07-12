cmake_minimum_required(VERSION 3.5)
project(opengl C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE on)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)

# if(NOT EXISTS ${PROJECT_3RD_DIR}/stb)
#     file(MAKE_DIRECTORY "${PROJECT_3RD_DIR}/stb")
#     execute_process(
#         COMMAND git clone https://github.com/glfw/glfw ${PROJECT_3RD_DIR}/glfw
#         COMMAND cd ${PROJECT_3RD_DIR}/glfw
#         COMMAND mkdir build && cd build && cmake ../glfw && make -j4 && sudo make install
#     )
# else()
#vscode cmake tool不知道为啥CMAKE_BUILD_TYPE为空
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(math)
file(COPY ${PROJECT_SOURCE_DIR}/math/include DESTINATION "${LIBRARY_OUTPUT_PATH}")
add_subdirectory(render)
file(COPY ${PROJECT_SOURCE_DIR}/render/include DESTINATION "${LIBRARY_OUTPUT_PATH}")