#1. 确定CMake的最低版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

#2. 确定工程名
PROJECT(ParserZC LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 17)

# 设置依赖库路径（与主项目保持一致）
IF (MSVC)
	# Windows配置保持不变
ELSE (GNUCC)
	IF(WIN32)
		SET (MyDeps $ENV{MyDependsGcc})
	ELSE(UNIX)
		SET (MyDeps "/root/trading_sys/wondertrader/3rd/mydeps_gcc8.4.0")
	ENDIF()

	SET(INCS ${MyDeps}/include)
	SET(LNKS ${MyDeps}/lib)
	
	MESSAGE(STATUS "MyDepends is at ${MyDeps}")
	MESSAGE(STATUS "Platform is x64")
	SET(PLATFORM x64)
ENDIF()

# 设置源文件
SET(SRC  
	${PROJECT_SOURCE_DIR}/ParserZC.cpp
	${PROJECT_SOURCE_DIR}/ParserZC.h
	${PROJECT_SOURCE_DIR}/ParserZCDef.h
)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build_${PLATFORM}/${CMAKE_BUILD_TYPE}/bin)

# 包含目录
INCLUDE_DIRECTORIES(${INCS})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Includes)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Share)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../API/sipsi2Api/inc)
INCLUDE_DIRECTORIES(/root/trading_sys/wondertrader/3rd/mydeps_gcc8.4.0/include)
LINK_DIRECTORIES(${LNKS})

# 创建动态库
ADD_LIBRARY(ParserZC SHARED ${SRC})

# 平台特定配置
IF (MSVC)
	# Windows MSVC配置
	# 链接sipsi2Api库 (Windows)
	IF(EXISTS "${PROJECT_SOURCE_DIR}/../API/sipsi2Api/win64")
		TARGET_LINK_LIBRARIES(ParserZC 
			${PROJECT_SOURCE_DIR}/../API/sipsi2Api/win64/sipsi2.lib)
	ENDIF()
ELSE (GNUCC)
	# Linux GCC配置
	SET(LIBS
		boost_thread
		boost_filesystem
		dl
		pthread
	)
	TARGET_LINK_LIBRARIES(ParserZC ${LIBS})
	
	# 链接sipsi2Api库 (Linux)
	IF(EXISTS "${PROJECT_SOURCE_DIR}/../API/sipsi2Api/linux64")
		# 查找sipsi2动态库
		FIND_LIBRARY(SIPSI2_LIB
			NAMES sipui2x64 libsipui2x64
			PATHS ${PROJECT_SOURCE_DIR}/../API/sipsi2Api/linux64
			NO_DEFAULT_PATH)

		IF(SIPSI2_LIB)
			TARGET_LINK_LIBRARIES(ParserZC ${SIPSI2_LIB})
			MESSAGE(STATUS "Found sipsi2 library: ${SIPSI2_LIB}")
		ELSE()
			MESSAGE(WARNING "sipsi2 library not found in ${PROJECT_SOURCE_DIR}/../API/sipsi2Api/linux64")
		ENDIF()
	ENDIF()
	
	# 设置Linux特定的链接选项
	SET_TARGET_PROPERTIES(ParserZC PROPERTIES
		CXX_VISIBILITY_PRESET hidden
		C_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN 1)

	# 只在Release模式下strip符号，Debug模式保留调试符号
	IF(CMAKE_BUILD_TYPE STREQUAL "Release")
		SET_TARGET_PROPERTIES(ParserZC PROPERTIES LINK_FLAGS -s)
	ENDIF()
ENDIF()

# 编译选项
IF (MSVC)
	TARGET_COMPILE_DEFINITIONS(ParserZC PRIVATE 
		_CRT_SECURE_NO_WARNINGS
		WIN32_LEAN_AND_MEAN)
ELSE()
	TARGET_COMPILE_OPTIONS(ParserZC PRIVATE 
		-Wall -Wextra -Wno-unused-parameter
		-fPIC)
	
	# Debug模式下启用调试信息
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		TARGET_COMPILE_OPTIONS(ParserZC PRIVATE -g -O0)
	ELSE()
		TARGET_COMPILE_OPTIONS(ParserZC PRIVATE -O2)
	ENDIF()
ENDIF()

# 定义宏
TARGET_COMPILE_DEFINITIONS(ParserZC PRIVATE 
	BUILDING_PARSER_ZC
	_PARSER_ZC_EXPORTS)

# 安装规则
INSTALL(TARGETS ParserZC
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

# 调试信息
MESSAGE(STATUS "ParserZC Configuration:")
MESSAGE(STATUS "  Source files: ${SRC}")
MESSAGE(STATUS "  Include directories: ${INCS}")
MESSAGE(STATUS "  Link directories: ${LNKS}")
MESSAGE(STATUS "  Platform: ${PLATFORM}")
MESSAGE(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")

# 检查sipsi2Api文件是否存在
IF(EXISTS "${PROJECT_SOURCE_DIR}/../API/sipsi2Api/inc/sipui2_i.h")
    MESSAGE(STATUS "  sipsi2Api headers found")
ELSE()
    MESSAGE(WARNING "  sipsi2Api headers NOT found at ${PROJECT_SOURCE_DIR}/../API/sipsi2Api/inc/")
ENDIF() 