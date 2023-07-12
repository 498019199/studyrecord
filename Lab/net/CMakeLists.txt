include_directories(${PROJECT_SOURCE_DIR}/net/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/net/src SRCS_LIST)

add_library(net_lib STATIC ${SRCS_LIST})
