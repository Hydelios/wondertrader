# STP项目
project(STP_Project)

# 包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Includes
    ${CMAKE_SOURCE_DIR}/src/Share
    ${CMAKE_SOURCE_DIR}/src/API/stp/include
    ${CMAKE_SOURCE_DIR}/3rd/mydeps_gcc8.4.0/mydeps/include
)

# 查找源文件
file(GLOB STP_TEST_SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(test_stp_debug ${STP_TEST_SOURCES})

# 链接库
target_link_libraries(test_stp_debug
    TraderSTP
    WTSTools
    WTSUtils
    pthread
    boost_filesystem
    dl
)

# 设置输出目录
set_target_properties(test_stp_debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# 自定义目标：运行测试
add_custom_target(run_stp_test
    COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_CURRENT_SOURCE_DIR}/libs:${CMAKE_CURRENT_SOURCE_DIR}:$ENV{LD_LIBRARY_PATH}" ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_stp_debug
    DEPENDS test_stp_debug
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running STP test..."
)
