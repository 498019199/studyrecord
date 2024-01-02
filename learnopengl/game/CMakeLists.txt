include_directories(${PROJECT_SOURCE_DIR}/render/include
                    ${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include)



target_link_libraries(test_opengl PRIVATE 
    opengl32.lib
    ${PROJECT_3RD_DIR}/glfw/lib/glfw3.lib
    ${LIB_DIR_PATH}/render_lib.lib
    ${LIB_DIR_PATH}/math_lib.lib)