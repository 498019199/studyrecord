include_directories(${PROJECT_3RD_DIR}/glad/include)
include_directories(${PROJECT_3RD_DIR}/glfw/include)
include_directories(${PROJECT_3RD_DIR}/stb/include)
include_directories(${PROJECT_SOURCE_DIR}/render/include)
include_directories(${PROJECT_SOURCE_DIR}/math/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/render/src SRC_LIST)
list(APPEND SRC_LIST 
    ${PROJECT_3RD_DIR}/glad/src/glad.c)

add_library(render_lib STATIC ${SRC_LIST})

target_link_libraries(render_lib PRIVATE 
    ${PROJECT_3RD_DIR}/glfw/lib/glfw3.lib
    opengl32.lib)

add_subdirectory(test)