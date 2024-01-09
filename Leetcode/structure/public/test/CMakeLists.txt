include_directories(${PROJECT_SOURCE_DIR}/public/include)

add_executable(test_public 
    ${PROJECT_SOURCE_DIR}/public/test/test_data.cc)

target_link_libraries(test_public
    public_lib
)