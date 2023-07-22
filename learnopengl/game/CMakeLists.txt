include_directories(${PROJECT_SOURCE_DIR}/render/include
                    ${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIB_DIR_PATH, ${PROJECT_SOURCE_DIR}/lib/Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(LIB_DIR_PATH, ${PROJECT_SOURCE_DIR}/lib/Release)
endif()

target_link_libraries(test_opengl PRIVATE 
    opengl32.lib
    ${PROJECT_3RD_DIR}/glfw/lib/glfw3.lib
    ${LIB_DIR_PATH}/render_lib.lib
    ${LIB_DIR_PATH}/math_lib.lib)