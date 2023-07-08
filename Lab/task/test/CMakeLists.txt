include_directories(${PROJECT_SOURCE_DIR}/task/include)

add_executable(test_task 
    ${PROJECT_SOURCE_DIR}/task/test/main.cpp)

target_link_libraries(
    task_lib
)