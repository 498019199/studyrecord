include_directories(${PROJECT_SOURCE_DIR}/task/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/task/src SRCS_LIST)

add_library(task_lib STATIC ${SRCS_LIST})

add_subdirectory(test)
