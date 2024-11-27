include_directories(${PROJECT_SOURCE_DIR}/math/include)
include_directories(${PROJECT_SOURCE_DIR}/common/include)

add_executable(test_common test_common.cpp)

target_link_libraries(test_common PRIVATE 
    ${LIB_DIR_PATH}/common.lib
    ${LIB_DIR_PATH}/math.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/d3dx9${3RD_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/d3dx11${3RD_DEBUG_POSTFIX}.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/dxgi.lib
    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/lib/x64/DxErr.lib)