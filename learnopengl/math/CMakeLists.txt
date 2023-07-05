include_directories(${PROJECT_SOURCE_DIR}/math/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/math/src SRC_LIST)

add_library(math_lib STATIC ${SRC_LIST})

add_subdirectory(test)