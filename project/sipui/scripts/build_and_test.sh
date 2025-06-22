#!/bin/bash

# ParserZC模块编译和测试脚本
# 用法: ./build_and_test.sh [clean|test|help]

set -e  # 遇到错误时退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 项目路径
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")"/../../.. && pwd)"
SRC_DIR="$PROJECT_ROOT/src"
BUILD_DIR="$SRC_DIR/build_x64"
SIPUI_DIR="$PROJECT_ROOT/project/sipui"
BIN_DIR="$SIPUI_DIR/bin"
LIB_DIR="$SIPUI_DIR/libs"

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}    ParserZC 编译和测试脚本${NC}"
echo -e "${BLUE}========================================${NC}"

# 打印使用说明
print_usage() {
    echo "用法: $0 [选项]"
    echo "选项:"
    echo "  clean    清理编译文件"
    echo "  test     编译并运行测试"
    echo "  help     显示此帮助信息"
    echo "  (无参数) 仅编译"
}

# 检查环境
check_environment() {
    echo -e "${YELLOW}🔍 检查编译环境...${NC}"
    
    # 检查必要目录
    if [ ! -d "$SRC_DIR" ]; then
        echo -e "${RED}❌ 源代码目录不存在: $SRC_DIR${NC}"
        exit 1
    fi
    
    # 检查sipsi2Api
    if [ ! -d "$SRC_DIR/API/sipsi2Api" ]; then
        echo -e "${RED}❌ sipsi2Api目录不存在${NC}"
        exit 1
    fi
    
    if [ ! -f "$SRC_DIR/API/sipsi2Api/inc/sipui2_i.h" ]; then
        echo -e "${RED}❌ sipsi2Api头文件不存在${NC}"
        exit 1
    fi
    
    # 检查ParserZC源文件
    if [ ! -f "$SRC_DIR/ParserZC/ParserZC.h" ]; then
        echo -e "${RED}❌ ParserZC.h不存在${NC}"
        exit 1
    fi
    
    if [ ! -f "$SRC_DIR/ParserZC/ParserZC.cpp" ]; then
        echo -e "${RED}❌ ParserZC.cpp不存在${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ 环境检查通过${NC}"
}

# 清理编译文件
clean_build() {
    echo -e "${YELLOW}🧹 清理编译文件...${NC}"
    
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        echo -e "${GREEN}✅ 清理完成${NC}"
    else
        echo -e "${YELLOW}ℹ️  构建目录不存在，无需清理${NC}"
    fi
}

# 编译项目
build_project() {
    echo -e "${YELLOW}🔨 开始编译...${NC}"
    
    # 创建构建目录
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    # 运行CMake配置
    echo -e "${YELLOW}⚙️  配置CMake...${NC}"
    cmake -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_STANDARD=17 \
          "$SRC_DIR"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ CMake配置失败${NC}"
        exit 1
    fi
    
    # 编译ParserZC
    echo -e "${YELLOW}🔧 编译ParserZC模块...${NC}"
    make ParserZC -j$(nproc)
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ 编译失败${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ 编译成功${NC}"
}

# 拷贝文件到sipui目录
copy_files() {
    echo -e "${YELLOW}📂 拷贝文件到测试目录...${NC}"
    
    # 创建目标目录
    mkdir -p "$BIN_DIR" "$LIB_DIR"
    
    # 查找ParserZC库文件
    PARSER_LIB=$(find "$BUILD_DIR" -name "libParserZC.so" -type f | head -1)
    if [ -z "$PARSER_LIB" ]; then
        echo -e "${RED}❌ 找不到libParserZC.so${NC}"
        exit 1
    fi
    
    # 拷贝ParserZC库
    cp "$PARSER_LIB" "$LIB_DIR/"
    echo -e "${GREEN}✅ 拷贝 libParserZC.so${NC}"
    
    # 拷贝sipsi2Api库(如果存在)
    SIPSI2_LIB_DIR="$SRC_DIR/API/sipsi2Api/linux64"
    if [ -d "$SIPSI2_LIB_DIR" ]; then
        for lib in "$SIPSI2_LIB_DIR"/*.so; do
            if [ -f "$lib" ]; then
                cp "$lib" "$LIB_DIR/"
                echo -e "${GREEN}✅ 拷贝 $(basename "$lib")${NC}"
            fi
        done
    fi
    
    # 拷贝依赖库(如果需要)
    DEPS_LIB_DIR="$BUILD_DIR/build_x64/Release/libs"
    if [ -d "$DEPS_LIB_DIR" ]; then
        cp "$DEPS_LIB_DIR"/*.a "$LIB_DIR/" 2>/dev/null || true
    fi
    
    echo -e "${GREEN}✅ 文件拷贝完成${NC}"
}

# 编译测试程序
compile_test() {
    echo -e "${YELLOW}🔧 编译测试程序...${NC}"
    
    cd "$SIPUI_DIR"
    
    # 编译测试程序
    g++ -std=c++17 -O2 -pthread \
        -I"$SRC_DIR" \
        -I"$SRC_DIR/Includes" \
        -I"$SRC_DIR/API/sipsi2Api/inc" \
        -I"$SRC_DIR/../3rd/mydeps_gcc8.4.0/mydeps/include" \
        -L"$LIB_DIR" \
        -L"$SRC_DIR/../3rd/mydeps_gcc8.4.0/mydeps/lib" \
        -L"$SRC_DIR/build_x64/build_x64/Release/libs" \
        src/test_parser_zc.cpp \
        -lParserZC \
        -lsipui2x64 \
        -lWTSTools \
        -lWTSUtils \
        -lboost_filesystem \
        -lboost_system \
        -ldl \
        -o bin/test_parser_zc
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ 测试程序编译失败${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ 测试程序编译成功${NC}"
}

# 运行测试
run_test() {
    echo -e "${YELLOW}🧪 运行测试程序...${NC}"
    
    cd "$SIPUI_DIR"
    
    if [ ! -f "bin/test_parser_zc" ]; then
        echo -e "${RED}❌ 测试程序不存在${NC}"
        exit 1
    fi
    
    # 设置库路径
    export LD_LIBRARY_PATH="$LIB_DIR:$LD_LIBRARY_PATH"
    
    echo -e "${BLUE}💡 测试程序启动中...${NC}"
    echo -e "${BLUE}💡 按 Ctrl+C 可退出测试${NC}"
    echo -e "${BLUE}----------------------------------------${NC}"
    
    ./bin/test_parser_zc
}

# 显示状态信息
show_status() {
    echo -e "${BLUE}📊 编译状态:${NC}"
    
    # 检查ParserZC库
    if [ -f "$LIB_DIR/libParserZC.so" ]; then
        echo -e "${GREEN}✅ libParserZC.so${NC}"
    else
        echo -e "${RED}❌ libParserZC.so${NC}"
    fi
    
    # 检查测试程序
    if [ -f "$BIN_DIR/test_parser_zc" ]; then
        echo -e "${GREEN}✅ test_parser_zc${NC}"
    else
        echo -e "${RED}❌ test_parser_zc${NC}"
    fi
    
    # 检查配置文件
    if [ -f "$SIPUI_DIR/config/config.yaml" ]; then
        echo -e "${GREEN}✅ config.yaml${NC}"
    else
        echo -e "${YELLOW}⚠️  config.yaml (可选)${NC}"
    fi
}

# 主函数
main() {
    case "${1:-build}" in
        "clean")
            check_environment
            clean_build
            ;;
        "test")
            check_environment
            build_project
            copy_files
            compile_test
            show_status
            echo ""
            run_test
            ;;
        "build")
            check_environment
            build_project
            copy_files
            compile_test
            show_status
            ;;
        "help"|"-h"|"--help")
            print_usage
            ;;
        *)
            echo -e "${RED}❌ 未知选项: $1${NC}"
            print_usage
            exit 1
            ;;
    esac
}

# 检查是否有参数
if [ $# -gt 1 ]; then
    echo -e "${RED}❌ 太多参数${NC}"
    print_usage
    exit 1
fi

# 执行主函数
main "$1" 