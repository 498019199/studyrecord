include_directories(${PROJECT_SOURCE_DIR}/common/include
    ${PROJECT_SOURCE_DIR}/3rd/rapidjson/rapidjson/include
    ${PROJECT_SOURCE_DIR}/3rd/rapidxml/rapidxml)

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/common/src/CustomizedStreamBuf.cpp
    ${PROJECT_SOURCE_DIR}/common/src/DllLoader.cpp
    ${PROJECT_SOURCE_DIR}/common/src/ErrorHandling.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Log.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/common/src/Util.cpp
    ${PROJECT_SOURCE_DIR}/common/src/XMLDom.cpp )

add_library(common STATIC ${SRC_LIST})
set_target_properties(common PROPERTIES
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	OUTPUT_NAME common${ZENGINE_OUTPUT_SUFFIX}
	ARCHIVE_OUTPUT_NAME common${ZENGINE_OUTPUT_SUFFIX}
)
#add_subdirectory(test)