include_directories( 
    ${PROJECT_SOURCE_DIR}/common/include
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Include)

add_executable(Chapter6 main_draw.cpp)

target_link_libraries(Chapter6 PRIVATE 
    ${LIB_DIR_PATH}/common.lib
    ${LIB_DIR_PATH}/math.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3d11.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dx11d.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dcompiler.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxerr.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxguid.lib
    d3dcompiler.lib) 
