include_directories( 
    ${PROJECT_SOURCE_DIR}/Chapter8/core/include
    ${PROJECT_SOURCE_DIR}/math/include
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Include
    ${PROJECT_SOURCE_DIR}/3rd/imgui)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/Chapter8/main_texture.cpp

    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11GraphicsBuffer.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11Renderable.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11RenderLayout.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11Util.cpp 
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11Texture.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/D3D11/D3D11RenderFactory.cpp

    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/App/WinApp.cpp

    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Scene/SceneNode.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Scene/World.cpp
    
    ${PROJECT_SOURCE_DIR}/Chapter8/core/DevHelper/ImagePlane.cpp

    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/common.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Context.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Light.cpp 
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Mesh.cpp 
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/RenderableHelper.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/RenderEffect.cpp
    ${PROJECT_SOURCE_DIR}/Chapter8/core/src/Timer.cpp)
add_executable(Chapter8 ${SRC_LIST})

target_link_libraries(Chapter8 PRIVATE 
    ${LIB_DIR_PATH}/math${ZENGINE_OUTPUT_SUFFIX}${CMAKE_DEBUG_POSTFIX}.lib
    ${LIB_DIR_PATH}/imgui${ZENGINE_OUTPUT_SUFFIX}${CMAKE_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3d11.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3dx11d.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/d3dcompiler.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxerr.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/dxsdk/Lib/x64/dxguid.lib) 
