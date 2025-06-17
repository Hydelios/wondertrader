CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

PROJECT(TestTraderSTP LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build_${PLATFORM}/${CMAKE_BUILD_TYPE}/bin/TestTraderSTP)

file(GLOB SRCS *.cpp)

SET(LIBS
    TraderSTP
    WTSTools
    WTSUtils
)

IF (MSVC)
ELSE(GNUCC)
    LIST(APPEND LIBS
        dl
        pthread
        boost_filesystem)
    IF(WIN32)
        LIST(APPEND LIBS
            iconv)
    ENDIF()
ENDIF()

# 设置第三方依赖路径
set(MYDEPS_ROOT "${CMAKE_SOURCE_DIR}/../../3rd/mydeps_gcc8.4.0/mydeps")
include_directories(${MYDEPS_ROOT}/include)
link_directories(${MYDEPS_ROOT}/lib)

INCLUDE_DIRECTORIES(${INCS})
LINK_DIRECTORIES(${LNKS})

# 优先链接已存在的libTraderSTP.so
set(TRADERSTP_SO "${CMAKE_SOURCE_DIR}/../../build_all/build_x64/Release/bin/libTraderSTP.so")
if(EXISTS ${TRADERSTP_SO})
    message(STATUS "Using prebuilt libTraderSTP.so: ${TRADERSTP_SO}")
    add_executable(TestTraderSTP ${SRCS})
    target_include_directories(TestTraderSTP PRIVATE ../TraderSTP)
    target_link_libraries(TestTraderSTP ${TRADERSTP_SO} ${LIBS})
else()
    add_executable(TestTraderSTP ${SRCS})
    target_include_directories(TestTraderSTP PRIVATE ../TraderSTP)
    target_link_libraries(TestTraderSTP TraderSTP ${LIBS})
endif()

IF (MSVC)
ELSE (GNUCC)
    SET_TARGET_PROPERTIES(TestTraderSTP PROPERTIES
        LINK_FLAGS_RELEASE -s)
ENDIF ()
