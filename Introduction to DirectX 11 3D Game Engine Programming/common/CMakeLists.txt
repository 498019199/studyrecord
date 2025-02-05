include_directories(${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include
                    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/common/src/D3D11Util.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderMesh.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Context.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/common/src/WinApp.cpp)

add_library(common STATIC ${SRC_LIST})

target_link_libraries(common PRIVATE 
    ${LIB_DIR_PATH}/math.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dx11d.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3d11.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dcompiler.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxerr.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxguid.lib) 
