include_directories(${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include)

add_executable(test_math
    ${PROJECT_SOURCE_DIR}/math/test/main.cpp)

target_link_libraries(test_math PRIVATE 
        ${LIB_DIR_PATH}/math_lib.lib)