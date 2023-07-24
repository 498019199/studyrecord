include_directories(${PROJECT_SOURCE_DIR}/render/include)
include_directories(${PROJECT_SOURCE_DIR}/math/include)

add_executable(test_opengl 
    ${PROJECT_SOURCE_DIR}/render/test/opengl_main.cpp)

target_link_libraries(test_opengl PRIVATE 
    opengl32.lib
    ${PROJECT_3RD_DIR}/glfw/lib/glfw3.lib
    ${LIB_DIR_PATH}/render_lib.lib)