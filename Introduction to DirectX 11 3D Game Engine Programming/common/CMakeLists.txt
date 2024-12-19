include_directories(${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include
                    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include)

find_package(effects11 CONFIG REQUIRED)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/common/src/D3D11Util.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderMesh.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/common/src/WinApp.cpp)

add_library(common STATIC ${SRC_LIST})
target_link_libraries(common PRIVATE Microsoft::Effects11)