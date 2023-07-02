# if(NOT EXISTS ${PROJECT_3RD_DIR}/glfw)
#     file(MAKE_DIRECTORY "${PROJECT_3RD_DIR}/glfw")
#     execute_process(
#         COMMAND git clone https://github.com/glfw/glfw ${PROJECT_3RD_DIR}/glfw
#         COMMAND cd ${PROJECT_3RD_DIR}/glfw
#         COMMAND mkdir build && cd build && cmake ../glfw && make -j4 && sudo make install
#     )
# else()
#     message(STATUS "found glfw")
# endif()
set(CMAKE_CXX_FLAGS "-lglfw -lGLU -lGL")

add_executable(test_main 
    ${PROJECT_SOURCE_DIR}/math/test/main.cpp 
    ${SRC_LIST})

target_link_libraries(test_main
glut 
GL
GLU 
GLEW
)