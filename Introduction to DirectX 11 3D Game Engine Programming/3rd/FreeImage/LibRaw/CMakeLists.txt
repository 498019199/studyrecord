SET(LIB_NAME LibRaw)

SET(LIBRAW_INTERNAL_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/dcraw_common.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/dcraw_fileio.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/demosaic_packs.cpp
)
SET(LIBRAW_LIBRAW_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/src/libraw_c_api.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/src/libraw_cxx.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/src/libraw_datastream.cpp
)
SET(LIBRAW_INTERNAL_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/defines.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/libraw_internal_funcs.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/internal/var_defines.h
)
SET(LIBRAW_LIBRAW_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_alloc.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_const.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_datastream.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_internal.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_types.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite/libraw/libraw_version.h
)
SOURCE_GROUP("Source Files\\internal" FILES ${LIBRAW_INTERNAL_SOURCE_FILES})
SOURCE_GROUP("Source Files\\libraw" FILES ${LIBRAW_LIBRAW_SOURCE_FILES})
SOURCE_GROUP("Header Files\\internal" FILES ${LIBRAW_INTERNAL_HEADER_FILES})
SOURCE_GROUP("Header Files\\libraw" FILES ${LIBRAW_LIBRAW_HEADER_FILES})

ADD_LIBRARY(${LIB_NAME} STATIC
	${LIBRAW_INTERNAL_SOURCE_FILES} ${LIBRAW_LIBRAW_SOURCE_FILES}
	${LIBRAW_INTERNAL_HEADER_FILES} ${LIBRAW_LIBRAW_HEADER_FILES}
)

if(ZENGINE_COMPILER_CLANGCL)
	target_compile_options(${LIB_NAME}
		PRIVATE
			/Od # lld-link can't find __powidf2
	)
endif()

target_compile_definitions(${LIB_NAME}
	PRIVATE
		-DLIBRAW_NODLL
		-D_USE_MATH_DEFINES
)
if(ZENGINE_PLATFORM_WINDOWS)
	target_compile_definitions(${LIB_NAME}
		PRIVATE
			-D_CRT_SECURE_NO_DEPRECATE
	)
endif()

target_include_directories(${LIB_NAME}
	PRIVATE
		${FREEIMAGE_PROJECT_DIR}/Source/LibRawLite
		${ZLIB_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(${LIB_NAME}
	PRIVATE
		${ZENGINE_ZLIB_NAME}
)
