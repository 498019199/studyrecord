include_directories(${PROJECT_SOURCE_DIR}/3rd/glad/include)
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

# 查找GLFW库
find_package(glfw3 REQUIRED)
find_package( OpenGL REQUIRED )

add_executable(test_main 
    ${PROJECT_SOURCE_DIR}/math/test/main.cpp 
    ${PROJECT_SOURCE_DIR}/3rd/glad/src/glad.c
    ${SRC_LIST})

target_link_libraries(test_main 
    glfw
    GL
    )