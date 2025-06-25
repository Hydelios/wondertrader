# SIPUI项目
cmake_minimum_required(VERSION 3.5.0)
project(SIPUI_Project)

# 生成compile_commands.json用于VSCode IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# 设置构建类型为Debug以便调试
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 包含目录 - 修正路径为相对于当前CMakeLists.txt的路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/API/sipsi2Api/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/Share
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/mydeps_gcc8.4.0/include
)

# 添加库搜索路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)

# 查找源文件
file(GLOB SIPUI_TEST_SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(test_parser_zc ${SIPUI_TEST_SOURCES})

# 链接库 - 按依赖顺序排列
target_link_libraries(test_parser_zc
    ParserZC
    sipui2x64
    WTSTools
    WTSUtils
    boost_filesystem
    boost_system
    boost_thread
    pthread
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