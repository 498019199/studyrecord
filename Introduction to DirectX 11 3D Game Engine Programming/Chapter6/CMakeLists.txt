include_directories( 
    ${PROJECT_SOURCE_DIR}/Chapter6/common/include
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/Chapter6/main_draw.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/D3D11Util.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/D3D11RenderMesh.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/Context.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/Chapter6/common/src/WinApp.cpp)
add_executable(Chapter6 ${SRC_LIST})

target_link_libraries(Chapter6 PRIVATE 
    ${LIB_DIR_PATH}/math${ZENGINE_OUTPUT_SUFFIX}${CMAKE_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3d11.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3dx11d.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3dcompiler.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxerr.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxguid.lib) 
