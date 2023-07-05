
add_executable(test_math
    ${PROJECT_SOURCE_DIR}/math/test/main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(test_math
        ${PROJECT_SOURCE_DIR}/lib/Debug/math_lib.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(test_math
        ${PROJECT_SOURCE_DIR}/lib/Release/math_lib.lib)
endif()
