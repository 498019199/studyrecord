include_directories( 
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/Chapter4/common/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Include)
set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/Chapter4/DX11_win_ini.cpp
    ${PROJECT_SOURCE_DIR}/Chapter4/common/src/D3D11Util.cpp
    ${PROJECT_SOURCE_DIR}/Chapter4/common/src/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/Chapter4/common/src/D3D11RenderMesh.cpp
    ${PROJECT_SOURCE_DIR}/Chapter4/common/src/Context.cpp
    ${PROJECT_SOURCE_DIR}/Chapter4/common/src/WinApp.cpp)
    
add_executable(Chapter4 ${SRC_LIST})

target_link_libraries(Chapter4 PRIVATE 
    ${LIB_DIR_PATH}/math${ZENGINE_OUTPUT_SUFFIX}${CMAKE_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dx11${CMAKE_DEBUG_POSTFIX}.lib)
    #${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dcompiler.lib
    #${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxerr.lib
    #${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/DxErr.lib)
    #${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxguid.lib) 