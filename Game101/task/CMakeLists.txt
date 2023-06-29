include_directories(${PROJECT_SOURCE_DIR}/task/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/task/src SRC_LIST)

add_library(task_lib ${SRC_LIST})

add_subdirectory(test)