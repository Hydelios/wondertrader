#!/bin/bash

# TraderSTP 调试脚本
# 作者: Hydelios
# 日期: 2025-06-17

echo "=========================================="
echo "    TraderSTP 调试助手"
echo "=========================================="

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 函数：打印带颜色的消息
print_info() {
    echo -e "${BLUE}[信息]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[成功]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[警告]${NC} $1"
}

print_error() {
    echo -e "${RED}[错误]${NC} $1"
}

# 检查必要的工具
check_tools() {
    print_info "检查必要的工具..."
    
    if ! command -v g++ &> /dev/null; then
        print_error "g++ 编译器未找到，请安装 build-essential"
        exit 1
    fi
    
    if ! command -v gdb &> /dev/null; then
        print_warning "gdb 调试器未找到，建议安装以便调试"
    fi
    
    print_success "工具检查完成"
}

# 编译项目
compile_project() {
    print_info "开始编译 TraderSTP 项目..."
    
    # 首先编译主项目
    cd ../src
    if [ -f "build_release.sh" ]; then
        print_info "编译主项目..."
        bash build_release.sh
        if [ $? -eq 0 ]; then
            print_success "主项目编译成功"
        else
            print_error "主项目编译失败"
            return 1
        fi
    else
        print_warning "未找到 build_release.sh，尝试使用 CMake..."
        mkdir -p ../build_all/build_x64/Release
        cd ../build_all/build_x64/Release
        cmake ../../../src -DCMAKE_BUILD_TYPE=Release
        make -j$(nproc)
    fi
    
    cd ../../../prj_bin
    return 0
}

# 编译测试程序
compile_test() {
    print_info "编译测试程序..."
    
    # 检查是否存在必要的库文件
    if [ ! -f "libTraderSTP.so" ] && [ ! -f "../src/build_all/build_x64/Release/bin/libTraderSTP.so" ]; then
        print_error "libTraderSTP.so 未找到，请先编译主项目或运行拷贝脚本"
        return 1
    fi
    
    # 编译测试程序
    g++ -std=c++17 -g -O0 -Wall -Wextra \
        -I../../../src \
        -I../../../src/Includes \
        -I../../../src/Share \
        -I../../../src/API/stp/include \
        -I../../../3rd/mydeps_gcc8.4.0/mydeps/include \
        -L.. \
        -L../libs \
        -L../../../src/build_all/build_x64/Release/libs \
        -L../../../3rd/mydeps_gcc8.4.0/mydeps/lib \
        ../src/test_stp_debug.cpp \
        -o ../bin/test_stp_debug \
        -lTraderSTP \
        -lWTSTools \
        -lWTSUtils \
        -lpthread \
        -lboost_filesystem \
        -ldl
    
    if [ $? -eq 0 ]; then
        print_success "测试程序编译成功"
        return 0
    else
        print_error "测试程序编译失败"
        return 1
    fi
}

# 复制必要的库文件
copy_libs() {
    print_info "复制必要的库文件..."
    
    # 复制动态库
    cp ../../../src/build_all/build_x64/Release/bin/*.so ../libs/ 2>/dev/null || true
    
    print_success "库文件复制完成"
}

# 运行测试程序
run_test() {
    print_info "运行测试程序..."
    
    if [ ! -f "../bin/test_stp_debug" ]; then
        print_error "测试程序不存在，请先编译"
        return 1
    fi

    # 设置库路径
    export LD_LIBRARY_PATH=..:../libs:../../../src/build_all/build_x64/Release/bin:$LD_LIBRARY_PATH

    print_info "启动测试程序..."
    cd .. && ./bin/test_stp_debug
}

# 使用 GDB 调试
debug_with_gdb() {
    print_info "使用 GDB 调试..."
    
    if [ ! -f "../bin/test_stp_debug" ]; then
        print_error "测试程序不存在，请先编译"
        return 1
    fi

    if ! command -v gdb &> /dev/null; then
        print_error "GDB 未安装，无法进行调试"
        return 1
    fi

    # 设置库路径
    export LD_LIBRARY_PATH=..:../libs:../../../src/build_all/build_x64/Release/bin:$LD_LIBRARY_PATH

    print_info "启动 GDB 调试器..."
    cd .. && gdb ./bin/test_stp_debug
}

# 清理编译文件
clean() {
    print_info "清理编译文件..."
    rm -f ../bin/test_stp_debug ../*.o ../*.so
    print_success "清理完成"
}

# 显示帮助信息
show_help() {
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  compile     编译整个项目"
    echo "  test        编译并运行测试程序"
    echo "  debug       使用 GDB 调试测试程序"
    echo "  clean       清理编译文件"
    echo "  help        显示此帮助信息"
    echo ""
    echo "示例:"
    echo "  $0 compile  # 编译项目"
    echo "  $0 test     # 运行测试"
    echo "  $0 debug    # 开始调试"
}

# 主逻辑
main() {
    case "$1" in
        "compile")
            check_tools
            compile_project
            compile_test
            copy_libs
            ;;
        "test")
            check_tools
            compile_test
            copy_libs
            run_test
            ;;
        "debug")
            check_tools
            compile_test
            copy_libs
            debug_with_gdb
            ;;
        "clean")
            clean
            ;;
        "help"|"--help"|"-h")
            show_help
            ;;
        "")
            print_info "请选择操作:"
            echo "1. 编译项目"
            echo "2. 运行测试"
            echo "3. 开始调试"
            echo "4. 清理文件"
            echo "5. 显示帮助"
            echo -n "请输入选择 (1-5): "
            read choice
            case $choice in
                1) main "compile" ;;
                2) main "test" ;;
                3) main "debug" ;;
                4) main "clean" ;;
                5) main "help" ;;
                *) print_error "无效选择" ;;
            esac
            ;;
        *)
            print_error "未知选项: $1"
            show_help
            exit 1
            ;;
    esac
}

# 执行主函数
main "$@"
