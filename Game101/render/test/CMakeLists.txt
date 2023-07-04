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
add_executable(test_opengl 
    ${PROJECT_SOURCE_DIR}/render/test/opengl_main.cpp 
    ${PROJECT_SOURCE_DIR}/3rd/glad/src/glad.c)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(test_opengl
        ${PROJECT_SOURCE_DIR}/lib/Debug/render_lib.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(test_opengl
        ${PROJECT_SOURCE_DIR}/lib/Release/render_lib.lib)
endif()
