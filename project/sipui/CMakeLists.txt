# SIPUI项目
cmake_minimum_required(VERSION 3.5.0)
project(SIPUI_Project)

# 包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Includes
    ${CMAKE_SOURCE_DIR}/src/API/sipsi2Api/inc
    ${CMAKE_SOURCE_DIR}/3rd/mydeps_gcc8.4.0/mydeps/include
)

# 查找源文件
file(GLOB SIPUI_TEST_SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(test_parser_zc ${SIPUI_TEST_SOURCES})

# 链接库
target_link_libraries(test_parser_zc
    ParserZC
    sipui2x64
    WTSTools
    WTSUtils
    boost_filesystem
    boost_system
    dl
)

# 设置输出目录
set_target_properties(test_parser_zc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# 自定义目标：运行测试
add_custom_target(run_sipui_test
    COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_CURRENT_SOURCE_DIR}/libs:$ENV{LD_LIBRARY_PATH}" ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_parser_zc
    DEPENDS test_parser_zc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running SIPUI test..."
)