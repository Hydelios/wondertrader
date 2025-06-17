# TraderSTP 调试项目 CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(TraderSTP_Debug LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译类型为 Debug
set(CMAKE_BUILD_TYPE Debug)

# 添加编译选项
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 包含目录
include_directories(
    ../src
    ../src/Includes
    ../src/Share
    ../src/API/stp/include
    ../3rd/mydeps_gcc8.4.0/mydeps/include
)

# 链接目录
link_directories(
    ../build_all/build_x64/Release/bin
    ../3rd/mydeps_gcc8.4.0/mydeps/lib
)

# 源文件
set(SOURCES
    test_stp_debug.cpp
)

# 创建可执行文件
add_executable(test_stp_debug ${SOURCES})

# 链接库
target_link_libraries(test_stp_debug
    TraderSTP
    WTSTools
    WTSUtils
    pthread
    boost_filesystem
    dl
)

# 设置运行时库路径
set_target_properties(test_stp_debug PROPERTIES
    INSTALL_RPATH "../build_all/build_x64/Release/bin"
    BUILD_WITH_INSTALL_RPATH TRUE
)

# 添加自定义目标用于复制库文件
add_custom_target(copy_libs ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ../build_all/build_x64/Release/bin/libTraderSTP.so
        ${CMAKE_BINARY_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ../build_all/build_x64/Release/bin/libWTSTools.so
        ${CMAKE_BINARY_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ../build_all/build_x64/Release/bin/libWTSUtils.so
        ${CMAKE_BINARY_DIR}/
    COMMENT "复制必要的动态库文件"
)

# 确保在编译可执行文件之前复制库文件
add_dependencies(test_stp_debug copy_libs)
