include_directories( 
    ${PROJECT_SOURCE_DIR}/common/include
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include)
    
add_executable(Chapter4 DX11_win_ini.cpp)

target_link_libraries(Chapter4 PRIVATE 
    ${LIB_DIR_PATH}/common.lib
    ${LIB_DIR_PATH}/math.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/d3dx9${3RD_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/d3dx11${3RD_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/DxErr.lib)