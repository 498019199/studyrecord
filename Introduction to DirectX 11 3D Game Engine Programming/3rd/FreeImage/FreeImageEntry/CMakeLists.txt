SET(LIB_NAME FreeImage)

SET(FREEIMAGE_LIB_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/BitmapAccess.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ColorLookup.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/FreeImage.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/FreeImageC.c
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/FreeImageIO.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/GetType.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/MemoryIO.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PixelAccess.cpp
)
IF(ZENGINE_PLATFORM_WINDOWS)
	SET(FREEIMAGE_LIB_SOURCE_FILES ${FREEIMAGE_LIB_SOURCE_FILES}
		${FREEIMAGE_PROJECT_DIR}/FreeImage.rc
	)
ENDIF()
SET(FREEIMAGE_LIB_CONVERSION_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion4.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion8.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion16_555.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion16_565.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion24.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Conversion32.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionFloat.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionRGB16.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionRGBA16.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionRGBAF.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionRGBF.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionType.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ConversionUINT16.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Halftoning.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/tmoColorConvert.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/tmoDrago03.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/tmoFattal02.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/tmoReinhard05.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ToneMapping.cpp
)
SET(FREEIMAGE_LIB_METADATA_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/Exif.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/FIRational.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/FreeImageTag.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/IPTC.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/TagConversion.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/TagLib.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/XTIFF.cpp
)
SET(FREEIMAGE_LIB_MULTI_PAGING_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/CacheFile.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/MultiPage.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/ZLibInterface.cpp
)
SET(FREEIMAGE_LIB_PLUGINS_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/J2KHelper.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/MNGHelper.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/Plugin.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginBMP.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginCUT.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginDDS.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginEXR.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginG3.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginGIF.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginHDR.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginICO.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginIFF.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginJ2K.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginJNG.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginJP2.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginJPEG.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginJXR.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginKOALA.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginMNG.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPCD.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPCX.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPFM.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPICT.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPNG.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPNM.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginPSD.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginRAS.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginRAW.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginSGI.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginTARGA.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginTIFF.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginWBMP.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginWebP.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginXBM.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PluginXPM.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PSDParser.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/TIFFLogLuv.cpp
)
SET(FREEIMAGE_LIB_QUANTIZERS_SOURCE_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/LFPQuantizer.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/NNQuantizer.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/WuQuantizer.cpp
)
SET(FREEIMAGE_LIB_TOOLKIT_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Background.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/BSplineRotate.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Channels.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/ClassicRotate.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Colors.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/CopyPaste.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Display.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Flip.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/JPEGTransform.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/MultigridPoissonSolver.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Rescale.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Resize.cpp
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageToolkit/Resize.h
)
SET(FREEIMAGE_LIB_HEADER_FILES
	${FREEIMAGE_PROJECT_DIR}/Source/CacheFile.h
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/FIRational.h
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage.h
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImageIO.h
	${FREEIMAGE_PROJECT_DIR}/Source/Metadata/FreeImageTag.h
	${FREEIMAGE_PROJECT_DIR}/Source/MapIntrospector.h
	${FREEIMAGE_PROJECT_DIR}/Source/Plugin.h
	${FREEIMAGE_PROJECT_DIR}/Source/FreeImage/PSDParser.h
	${FREEIMAGE_PROJECT_DIR}/Source/Quantizers.h
	${FREEIMAGE_PROJECT_DIR}/Source/ToneMapping.h
	${FREEIMAGE_PROJECT_DIR}/Source/Utilities.h
)
SOURCE_GROUP("Source Files" FILES ${FREEIMAGE_LIB_SOURCE_FILES})
SOURCE_GROUP("Source Files\\Conversion" FILES ${FREEIMAGE_LIB_CONVERSION_SOURCE_FILES})
SOURCE_GROUP("Source Files\\DeprecationMgr" FILES ${FREEIMAGE_LIB_DEPRECATION_MGR_SOURCE_FILES})
SOURCE_GROUP("Source Files\\Metadata" FILES ${FREEIMAGE_LIB_METADATA_SOURCE_FILES})
SOURCE_GROUP("Source Files\\MultiPaging" FILES ${FREEIMAGE_LIB_MULTI_PAGING_SOURCE_FILES})
SOURCE_GROUP("Source Files\\Plugins" FILES ${FREEIMAGE_LIB_PLUGINS_SOURCE_FILES})
SOURCE_GROUP("Source Files\\Quantizers" FILES ${FREEIMAGE_LIB_QUANTIZERS_SOURCE_FILES})
SOURCE_GROUP("Header Files" FILES ${FREEIMAGE_LIB_HEADER_FILES})
SOURCE_GROUP("Toolkit Files" FILES ${FREEIMAGE_LIB_TOOLKIT_FILES})

ADD_LIBRARY(${LIB_NAME} SHARED
	${FREEIMAGE_LIB_SOURCE_FILES} ${FREEIMAGE_LIB_CONVERSION_SOURCE_FILES} ${FREEIMAGE_LIB_DEPRECATION_MGR_SOURCE_FILES}
	${FREEIMAGE_LIB_METADATA_SOURCE_FILES} ${FREEIMAGE_LIB_MULTI_PAGING_SOURCE_FILES} ${FREEIMAGE_LIB_PLUGINS_SOURCE_FILES}
	${FREEIMAGE_LIB_QUANTIZERS_SOURCE_FILES} ${FREEIMAGE_LIB_HEADER_FILES} ${FREEIMAGE_LIB_TOOLKIT_FILES}
)

if(ZENGINE_COMPILER_CLANGCL)
	target_compile_options(${LIB_NAME}
		PRIVATE
			/Od # lld-link can't find __powidf2
	)
endif()

target_compile_definitions(${LIB_NAME}
	PRIVATE
		-DOPJ_STATIC
		-DFREEIMAGE_EXPORTS
		-DLIBRAW_NODLL
)
if(ZENGINE_PLATFORM_WINDOWS)
	target_compile_definitions(${LIB_NAME}
		PRIVATE
			-D_CRT_SECURE_NO_DEPRECATE
	)
endif()

target_include_directories(${LIB_NAME}
	PUBLIC
		${FREEIMAGE_PROJECT_DIR}/Source
	PRIVATE
		${ZLIB_INCLUDE_DIRS}
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR/Half
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR/Iex
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR/IlmImf
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR/Imath
		${FREEIMAGE_PROJECT_DIR}/Source/OpenEXR/IlmThread
		${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/jxrgluelib
		${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/image/sys
)
if(NOT ZENGINE_COMPILER_MSVC)
	target_include_directories(${LIB_NAME}
		PRIVATE
			${FREEIMAGE_PROJECT_DIR}/Source/LibJXR/common/include
	)
endif()

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES
	OUTPUT_NAME ${LIB_NAME}${ZENGINE_OUTPUT_SUFFIX}
)

target_link_libraries(${LIB_NAME}
	PRIVATE
		LibJPEG LibJXR LibOpenJPEG LibPNG LibRaw LibTIFF4 LibWebP OpenEXR
		${ZENGINE_ZLIB_NAME}
)
IF(ZENGINE_PLATFORM_WINDOWS AND (NOT ZENGINE_COMPILER_MSVC))
	target_link_libraries(${LIB_NAME}
		PRIVATE
			ws2_32
	)
ENDIF()
