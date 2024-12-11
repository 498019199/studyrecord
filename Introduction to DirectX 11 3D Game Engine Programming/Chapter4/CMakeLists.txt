include_directories( 
    ${PROJECT_SOURCE_DIR}/common/include
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include)
    
add_executable(Chapter4 DX11_win_ini.cpp)

target_link_libraries(Chapter4 PRIVATE 
    ${LIB_DIR_PATH}/common.lib
    ${LIB_DIR_PATH}/math.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3d11.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dx11d.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/d3dcompiler.lib
    #${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/Effectslld.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxerr.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Lib/x64/dxguid.lib) 

#    D:\Project\498019199\studyrecord\Introduction to DirectX 11 3D Game Engine Programming\3rd\dxsdk\lib\x64\d3dcompiler.lib