include_directories(${PROJECT_SOURCE_DIR}/math/include
                    ${PROJECT_SOURCE_DIR}/common/include
                    ${PROJECT_SOURCE_DIR}/3rd/dxsdk/Include)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/common/src/D3D11Util.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderEngine.cpp
    ${PROJECT_SOURCE_DIR}/common/src/D3D11RenderMesh.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Light.cpp
    ${PROJECT_SOURCE_DIR}/common/src/RenderLayout.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Context.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/common/src/WinApp.cpp)

add_library(common STATIC ${SRC_LIST})

set_target_properties(common PROPERTIES
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	OUTPUT_NAME common${ZENGINE_OUTPUT_SUFFIX}
	ARCHIVE_OUTPUT_NAME common${ZENGINE_OUTPUT_SUFFIX}
)