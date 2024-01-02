include_directories(${PROJECT_SOURCE_DIR}/math/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/math/src/math.cpp
    ${PROJECT_SOURCE_DIR}/math/src/matrix.cpp
    ${PROJECT_SOURCE_DIR}/math/src/quaternion.cpp
    ${PROJECT_SOURCE_DIR}/math/src/rotator.cpp
    ${PROJECT_SOURCE_DIR}/math/src/color.cpp)
add_library(math_lib STATIC ${SRC_LIST})

add_subdirectory(test)