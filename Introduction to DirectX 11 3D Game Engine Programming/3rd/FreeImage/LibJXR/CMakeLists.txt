SET(LIB_NAME LibJXR)

SET(LIBJXR_IMAGE_DECODE_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/decode.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/JXRTranscode.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/postprocess.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/segdec.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/strdec.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/strdec_x86.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/strInvTransform.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/strPredQuantDec.c
)
SET(LIBJXR_IMAGE_ENCODE_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/encode.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/segenc.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/strenc.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/strenc_x86.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/strFwdTransform.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/strPredQuantEnc.c
)
SET(LIBJXR_IMAGE_SYS_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/adapthuff.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/image.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/strcodec.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/strPredQuant.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/strTransform.c
)
SET(LIBJXR_JXRGLUELIB_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib/JXRGlue.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib/JXRGlueJxr.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib/JXRGluePFC.c
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib/JXRMeta.c
)
SET(LIBJXR_COMMON_INCLUDE_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include/wmsal.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include/wmspecstring.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include/wmspecstrings_adt.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include/wmspecstrings_strict.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include/wmspecstrings_undef.h
)
SET(LIBJXR_IMAGE_DECODE_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/decode/decode.h
)
SET(LIBJXR_IMAGE_ENCODE_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/encode/encode.h
)
SET(LIBJXR_IMAGE_SYS_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/ansi.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/common.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/perfTimer.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/strcodec.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/strTransform.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/windowsmediaphoto.h
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys/xplatform_image.h
)
SET(LIBJXR_IMAGE_X86_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/x86/x86.h
)

SOURCE_GROUP("Source Files\\image\\decode" FILES ${LIBJXR_IMAGE_DECODE_SOURCE_FILES})
SOURCE_GROUP("Source Files\\image\\encode" FILES ${LIBJXR_IMAGE_ENCODE_SOURCE_FILES})
SOURCE_GROUP("Source Files\\image\\sys" FILES ${LIBJXR_IMAGE_SYS_SOURCE_FILES})
SOURCE_GROUP("Source Files\\jxrgluelib" FILES ${LIBJXR_JXRGLUELIB_SOURCE_FILES})
SOURCE_GROUP("Header Files\\image\\decode" FILES ${LIBJXR_IMAGE_DECODE_HEADER_FILES})
SOURCE_GROUP("Header Files\\image\\encode" FILES ${LIBJXR_IMAGE_ENCODE_HEADER_FILES})
SOURCE_GROUP("Header Files\\image\\sys" FILES ${LIBJXR_IMAGE_SYS_HEADER_FILES})
SOURCE_GROUP("Header Files\\image\\x86" FILES ${LIBJXR_IMAGE_X86_HEADER_FILES})
SOURCE_GROUP("Header Files\\jxrgluelib" FILES ${LIBJXR_JXRGLUELIB_HEADER_FILES})
SOURCE_GROUP("Header Files\\common" FILES ${LIBJXR_COMMON_INCLUDE_HEADER_FILES})

ADD_LIBRARY(${LIB_NAME} STATIC
	${LIBJXR_IMAGE_DECODE_SOURCE_FILES} ${LIBJXR_IMAGE_ENCODE_SOURCE_FILES} ${LIBJXR_IMAGE_SYS_SOURCE_FILES}
	${LIBJXR_JXRGLUELIB_SOURCE_FILES}
	${LIBJXR_IMAGE_DECODE_HEADER_FILES} ${LIBJXR_IMAGE_ENCODE_HEADER_FILES} ${LIBJXR_IMAGE_SYS_HEADER_FILES} ${LIBJXR_IMAGE_X86_HEADER_FILES}
	${LIBJXR_JXRGLUELIB_HEADER_FILES} ${LIBJXR_COMMON_INCLUDE_HEADER_FILES}
)

target_compile_definitions(${LIB_NAME}
	PRIVATE
		-DDISABLE_PERF_MEASUREMENT
)

target_include_directories(${LIB_NAME}
	PRIVATE
		${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys
		${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib
)
if(NOT ZENGINE_COMPILER_MSVC)
	target_include_directories(${LIB_NAME}
		PRIVATE
			${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include
	)
endif()

TARGET_LINK_LIBRARIES(${LIB_NAME})
