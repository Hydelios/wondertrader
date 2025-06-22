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

# 获取脚本所在目录和项目路径
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STP_DIR="$(dirname "$SCRIPT_DIR")"
PROJECT_ROOT="$(dirname "$STP_DIR")"
WONDERTRADER_ROOT="$(dirname "$PROJECT_ROOT")"
BIN_DIR="$STP_DIR/bin"
BUILD_DIR="$STP_DIR/build"
LIBS_DIR="$STP_DIR/libs"
SRC_DIR="$STP_DIR/src"

print_info "STP 项目目录: $STP_DIR"
print_info "构建目录: $BUILD_DIR"
print_info "库文件目录: $LIBS_DIR"

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

    # 进入构建目录
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    # 使用 CMake 编译
    if [ -f "$STP_DIR/CMakeLists.txt" ]; then
        print_info "使用 CMake 编译 STP 项目..."
        cmake "$STP_DIR" -DCMAKE_BUILD_TYPE=Release
        make -j$(nproc)
        if [ $? -eq 0 ]; then
            print_success "STP 项目编译成功"
        else
            print_error "STP 项目编译失败"
            return 1
        fi
    else
        print_warning "未找到 CMakeLists.txt，尝试编译主项目..."

        # 尝试编译主项目
        if [ -f "$WONDERTRADER_ROOT/src/build_release.sh" ]; then
            cd "$WONDERTRADER_ROOT/src"
            bash build_release.sh
            if [ $? -eq 0 ]; then
                print_success "主项目编译成功"
            else
                print_error "主项目编译失败"
                return 1
            fi
        else
            print_error "未找到编译脚本"
            return 1
        fi
    fi

    cd "$STP_DIR"
    return 0
}

# 编译测试程序
compile_test() {
    print_info "编译测试程序..."

    # 检查源文件是否存在
    if [ ! -f "$SRC_DIR/test_stp_debug.cpp" ]; then
        print_error "测试程序源文件不存在: $SRC_DIR/test_stp_debug.cpp"
        return 1
    fi

    # 检查是否存在必要的库文件
    local trader_lib_found=false
    local lib_paths=("$STP_DIR/libTraderSTP.so" "$LIBS_DIR/libTraderSTP.so" "$BUILD_DIR/libTraderSTP.so")
    for lib_path in "${lib_paths[@]}"; do
        if [ -f "$lib_path" ]; then
            trader_lib_found=true
            break
        fi
    done

    if [ "$trader_lib_found" = false ]; then
        print_error "libTraderSTP.so 未找到，请先编译主项目或运行拷贝脚本"
        return 1
    fi

    # 创建 bin 目录
    mkdir -p "$BIN_DIR"

    # 编译测试程序
    print_info "编译命令执行中..."
    g++ -std=c++17 -g -O0 -Wall -Wextra \
        -I"$WONDERTRADER_ROOT/src" \
        -I"$WONDERTRADER_ROOT/src/Includes" \
        -I"$WONDERTRADER_ROOT/src/Share" \
        -I"$WONDERTRADER_ROOT/src/API/stp/include" \
        -I"$WONDERTRADER_ROOT/3rd/mydeps_gcc8.4.0/mydeps/include" \
        -L"$STP_DIR" \
        -L"$LIBS_DIR" \
        -L"$BUILD_DIR" \
        -L"$WONDERTRADER_ROOT/3rd/mydeps_gcc8.4.0/mydeps/lib" \
        "$SRC_DIR/test_stp_debug.cpp" \
        -o "$BIN_DIR/test_stp_debug" \
        -lTraderSTP \
        -lWTSTools \
        -lWTSUtils \
        -lpthread \
        -lboost_filesystem \
        -ldl

    if [ $? -eq 0 ]; then
        print_success "测试程序编译成功: $BIN_DIR/test_stp_debug"
        return 0
    else
        print_error "测试程序编译失败"
        return 1
    fi
}

# 复制必要的库文件
copy_libs() {
    print_info "复制必要的库文件..."

    # 创建 libs 目录
    mkdir -p "$LIBS_DIR"

    # 可能的库文件源目录
    local lib_source_dirs=(
        "$BUILD_DIR"
        "$WONDERTRADER_ROOT/src/build_all/build_x64/Release/bin"
        "$WONDERTRADER_ROOT/src/build_debug/build_x64/Debug/bin"
    )

    local copied_count=0
    for source_dir in "${lib_source_dirs[@]}"; do
        if [ -d "$source_dir" ]; then
            for lib_file in "$source_dir"/*.so; do
                if [ -f "$lib_file" ]; then
                    cp "$lib_file" "$LIBS_DIR/" 2>/dev/null
                    ((copied_count++))
                fi
            done
        fi
    done

    if [ $copied_count -gt 0 ]; then
        print_success "库文件复制完成，共复制 $copied_count 个文件"
    else
        print_warning "未找到库文件，可能需要先编译项目"
    fi
}

# 运行测试程序
run_test() {
    print_info "运行测试程序..."

    if [ ! -f "$BIN_DIR/test_stp_debug" ]; then
        print_error "测试程序不存在，请先编译"
        return 1
    fi

    # 设置库路径
    export LD_LIBRARY_PATH="$STP_DIR:$LIBS_DIR:$BUILD_DIR:$LD_LIBRARY_PATH"

    print_info "库路径: $LD_LIBRARY_PATH"
    print_info "启动测试程序..."

    cd "$STP_DIR"
    "$BIN_DIR/test_stp_debug"
}

# 使用 GDB 调试
debug_with_gdb() {
    print_info "使用 GDB 调试..."

    if [ ! -f "$BIN_DIR/test_stp_debug" ]; then
        print_error "测试程序不存在，请先编译"
        return 1
    fi

    if ! command -v gdb &> /dev/null; then
        print_error "GDB 未安装，无法进行调试"
        print_info "请安装 GDB: sudo apt install gdb"
        return 1
    fi

    # 设置库路径
    export LD_LIBRARY_PATH="$STP_DIR:$LIBS_DIR:$BUILD_DIR:$LD_LIBRARY_PATH"

    print_info "库路径: $LD_LIBRARY_PATH"
    print_info "启动 GDB 调试器..."

    cd "$STP_DIR"
    gdb "$BIN_DIR/test_stp_debug"
}

# 清理编译文件
clean() {
    print_info "清理编译文件..."

    # 清理构建目录
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "✓ 清理构建目录"
    fi

    # 清理可执行文件
    if [ -f "$BIN_DIR/test_stp_debug" ]; then
        rm -f "$BIN_DIR/test_stp_debug"
        print_success "✓ 清理可执行文件"
    fi

    # 清理临时文件
    rm -f "$STP_DIR"/*.o "$STP_DIR"/*.so.* 2>/dev/null || true

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
