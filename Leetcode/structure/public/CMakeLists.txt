include_directories(${PROJECT_SOURCE_DIR}/public/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/public/src SRCS_LIST)

add_library(public_lib STATIC ${SRCS_LIST})

add_subdirectory(test)

