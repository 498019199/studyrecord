include_directories(${PROJECT_SOURCE_DIR}/math/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderDevice.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/common/src/WinApp.cpp)
add_library(common STATIC ${SRC_LIST})