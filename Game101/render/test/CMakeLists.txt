include_directories(${PROJECT_SOURCE_DIR}/render/include)
include_directories(${PROJECT_SOURCE_DIR}/math/include)

add_executable(test_opengl 
    ${PROJECT_SOURCE_DIR}/render/test/opengl_main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(test_opengl PRIVATE 
        ${PROJECT_SOURCE_DIR}/lib/Debug/render_lib.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(test_opengl PRIVATE 
        ${PROJECT_SOURCE_DIR}/lib/Release/render_lib.lib)
endif()

target_link_libraries(test_opengl PRIVATE 
    ${PROJECT_3RD_DIR}/glfw/lib/glfw3.lib 
    opengl32.lib)