include_directories(${PROJECT_SOURCE_DIR}/3rd/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd/stb/include)
include_directories(${PROJECT_SOURCE_DIR}/render/include)
include_directories(${PROJECT_SOURCE_DIR}/math/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/math/src SRC_LIST)

add_library(render_lib ${SRC_LIST})


add_subdirectory(test)