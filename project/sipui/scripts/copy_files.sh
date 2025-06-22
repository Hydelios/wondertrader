#!/bin/bash

# 文件拷贝脚本 - 将编译后的文件拷贝到项目目录
# 作者: Hydelios
# 日期: 2025-06-17

echo "=========================================="
echo "    文件拷贝脚本"
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

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STP_DIR="$(dirname "$SCRIPT_DIR")"
PROJECT_ROOT="$(dirname "$STP_DIR")"
WONDERTRADER_ROOT="$(dirname "$PROJECT_ROOT")"
LIBS_DIR="$STP_DIR/libs"

# 定义项目目录变量
PROJECT_BIN_DIR="$STP_DIR"

print_info "WonderTrader 根目录: $WONDERTRADER_ROOT"
print_info "项目根目录: $PROJECT_ROOT"
print_info "STP 目录: $STP_DIR"
print_info "库文件目录: $LIBS_DIR"

# 创建 libs 目录
mkdir -p "$LIBS_DIR"

# 定义源目录路径
RELEASE_BIN_DIR="$WONDERTRADER_ROOT/src/build_all/build_x64/Release/bin"
DEBUG_BIN_DIR="$WONDERTRADER_ROOT/src/build_debug/build_x64/Debug/bin"
DIST_DIR="$WONDERTRADER_ROOT/dist"

# 拷贝动态库文件
copy_libraries() {
    print_info "拷贝动态库文件..."

    # 优先使用 Release 版本，如果不存在则使用 Debug 版本
    if [ -d "$RELEASE_BIN_DIR" ]; then
        SOURCE_DIR="$RELEASE_BIN_DIR"
        print_info "使用 Release 版本库文件"
    elif [ -d "$DEBUG_BIN_DIR" ]; then
        SOURCE_DIR="$DEBUG_BIN_DIR"
        print_warning "使用 Debug 版本库文件"
    else
        print_error "未找到编译后的库文件目录"
        return 1
    fi

    # 拷贝所有 .so 文件到 libs 目录
    if [ -d "$SOURCE_DIR" ]; then
        print_info "从 $SOURCE_DIR 拷贝库文件到 libs 目录..."
        cp "$SOURCE_DIR"/*.so "$LIBS_DIR/" 2>/dev/null

        # 为主要库文件在 STP 目录创建符号链接
        local key_libs=("libTraderSTP.so")
        for lib in "${key_libs[@]}"; do
            if [ -f "$LIBS_DIR/$lib" ]; then
                cd "$STP_DIR"
                ln -sf "libs/$lib" "$lib"
                print_success "✓ $lib (符号链接)"
            else
                print_warning "✗ $lib 未找到"
            fi
        done

        # 检查其他库文件
        local other_libs=("libWTSTools.so" "libWTSUtils.so")
        for lib in "${other_libs[@]}"; do
            if [ -f "$LIBS_DIR/$lib" ]; then
                print_success "✓ $lib (在 libs 目录)"
            else
                print_warning "✗ $lib 未找到"
            fi
        done
    fi
}

# 拷贝可执行文件
copy_executables() {
    print_info "拷贝可执行文件..."
    
    # 拷贝 TestTraderSTP
    local test_exe_paths=(
        "$RELEASE_BIN_DIR/TestTraderSTP/TestTraderSTP"
        "$DEBUG_BIN_DIR/TestTraderSTP/TestTraderSTP"
        "$PROJECT_ROOT/src/build_all/build_x64/Release/bin/TestTraderSTP"
        "$PROJECT_ROOT/src/build_debug/build_x64/Debug/bin/TestTraderSTP"
    )
    
    for exe_path in "${test_exe_paths[@]}"; do
        if [ -f "$exe_path" ]; then
            cp "$exe_path" "$PROJECT_BIN_DIR/TestTraderSTP_original"
            print_success "✓ TestTraderSTP 拷贝完成"
            break
        fi
    done
}

# 拷贝配置文件
copy_configs() {
    print_info "拷贝配置文件..."
    
    # 如果 dist 目录存在且项目中没有配置文件，则拷贝
    if [ -d "$DIST_DIR" ] && [ ! -f "$PROJECT_BIN_DIR/config.yaml" ]; then
        print_info "拷贝 dist 目录配置文件..."

        # 拷贝 WtRunnerCta 的配置作为参考
        if [ -d "$DIST_DIR/WtRunnerCta" ]; then
            cp "$DIST_DIR/WtRunnerCta"/*.yaml "$PROJECT_BIN_DIR/" 2>/dev/null
            print_success "✓ 配置文件拷贝完成"
        fi

        # 拷贝 common 目录
        if [ -d "$DIST_DIR/common" ]; then
            cp -r "$DIST_DIR/common" "$PROJECT_BIN_DIR/" 2>/dev/null
            print_success "✓ common 目录拷贝完成"
        fi
    else
        print_info "配置文件已存在，跳过拷贝"
    fi
}

# 拷贝第三方依赖
copy_third_party() {
    print_info "检查第三方依赖..."

    local deps_dir="$WONDERTRADER_ROOT/3rd/mydeps_gcc8.4.0/mydeps/lib"
    if [ -d "$deps_dir" ]; then
        print_info "拷贝第三方依赖库到 libs 目录..."
        cp "$deps_dir"/*.so* "$LIBS_DIR/" 2>/dev/null || true
        print_success "✓ 第三方依赖拷贝完成"
    else
        print_warning "第三方依赖目录不存在: $deps_dir"
    fi
}

# 拷贝 STP API 库
copy_stp_api() {
    print_info "拷贝 STP API 库..."

    local stp_lib="$WONDERTRADER_ROOT/src/API/stp/lib/release/libSTPTradeApi.so"
    if [ -f "$stp_lib" ]; then
        cp "$stp_lib" "$LIBS_DIR/"
        # 创建符号链接，因为 TraderSTP 期望的文件名是 stptradeapi.so
        cd "$STP_DIR"
        ln -sf libs/libSTPTradeApi.so stptradeapi.so
        print_success "✓ libSTPTradeApi.so 拷贝到 libs 目录"
        print_success "✓ 创建符号链接 stptradeapi.so"
    else
        print_warning "STP API 库不存在: $stp_lib"
    fi
}

# 拷贝 STP 依赖库
copy_stp_dependencies() {
    print_info "拷贝 STP 依赖库..."

    local stp_deps_dir="$WONDERTRADER_ROOT/3rd/stp_lib_linux"
    if [ -d "$stp_deps_dir" ]; then
        print_info "从 $stp_deps_dir 拷贝 STP 依赖库到 libs 目录..."

        local copied_count=0

        # 递归查找并拷贝所有 .so 文件
        while IFS= read -r -d '' lib_file; do
            if [ -f "$lib_file" ]; then
                cp "$lib_file" "$LIBS_DIR/"
                local lib_name=$(basename "$lib_file")
                print_success "✓ $lib_name"
                ((copied_count++))
            fi
        done < <(find "$stp_deps_dir" -name "*.so*" -type f -print0)

        # 特别处理一些常见的库文件模式
        local lib_patterns=("libprotobuf*" "libboost*" "libssl*" "libcrypto*")
        for pattern in "${lib_patterns[@]}"; do
            while IFS= read -r -d '' lib_file; do
                if [ -f "$lib_file" ] && [[ ! "$lib_file" =~ \.so ]]; then
                    # 检查是否是库文件（通过 file 命令）
                    if file "$lib_file" | grep -q "shared object\|dynamic lib"; then
                        cp "$lib_file" "$LIBS_DIR/"
                        local lib_name=$(basename "$lib_file")
                        print_success "✓ $lib_name (动态库)"
                        ((copied_count++))
                    fi
                fi
            done < <(find "$stp_deps_dir" -name "$pattern" -type f -print0)
        done

        if [ $copied_count -gt 0 ]; then
            print_success "✓ 成功拷贝 $copied_count 个 STP 依赖库文件到 libs 目录"
        else
            print_warning "STP 依赖库目录中没有找到库文件"
        fi
    else
        print_warning "STP 依赖库目录不存在: $stp_deps_dir"
    fi
}

# 设置权限
set_permissions() {
    print_info "设置文件权限..."
    
    # 设置可执行文件权限
    chmod +x "$PROJECT_BIN_DIR"/*.sh 2>/dev/null || true
    chmod +x "$PROJECT_BIN_DIR"/TestTraderSTP* 2>/dev/null || true
    chmod +x "$PROJECT_BIN_DIR"/test_stp_debug 2>/dev/null || true
    
    print_success "✓ 权限设置完成"
}

# 验证拷贝结果
verify_copy() {
    print_info "验证拷贝结果..."
    
    local error_count=0
    
    # 检查关键库文件
    local key_libs=("libTraderSTP.so" "libSTPTradeApi.so")
    local optional_libs=("libWTSTools.so" "libWTSUtils.so")
    local stp_deps=("libprotobuf.so.12" "libprotobuf.so" "libssl.so" "libcrypto.so")

    print_info "检查关键库文件..."
    for lib in "${key_libs[@]}"; do
        if [ -f "$PROJECT_BIN_DIR/$lib" ] || [ -f "$LIBS_DIR/$lib" ]; then
            print_success "✓ $lib 存在"
        else
            print_error "✗ $lib 缺失"
            ((error_count++))
        fi
    done

    print_info "检查可选库文件..."
    for lib in "${optional_libs[@]}"; do
        if [ -f "$PROJECT_BIN_DIR/$lib" ] || [ -f "$LIBS_DIR/$lib" ]; then
            print_success "✓ $lib 存在"
        else
            print_warning "⚠ $lib 缺失 (可能是静态库)"
        fi
    done

    print_info "检查 STP 依赖库..."
    local stp_deps_found=0
    for lib in "${stp_deps[@]}"; do
        if [ -f "$LIBS_DIR/$lib" ] || [ -f "$LIBS_DIR/${lib}."* ]; then
            print_success "✓ $lib 存在 (在 libs 目录)"
            ((stp_deps_found++))
        else
            print_warning "⚠ $lib 缺失"
        fi
    done

    if [ $stp_deps_found -gt 0 ]; then
        print_success "找到 $stp_deps_found 个 STP 依赖库"
    else
        print_warning "未找到 STP 依赖库，可能影响程序运行"
    fi
    
    # 检查库文件依赖
    local trader_lib=""
    if [ -f "$PROJECT_BIN_DIR/libTraderSTP.so" ]; then
        trader_lib="$PROJECT_BIN_DIR/libTraderSTP.so"
    elif [ -f "$LIBS_DIR/libTraderSTP.so" ]; then
        trader_lib="$LIBS_DIR/libTraderSTP.so"
    fi

    if command -v ldd &> /dev/null && [ -n "$trader_lib" ]; then
        print_info "检查 libTraderSTP.so 依赖..."
        ldd "$trader_lib" | grep "not found" && ((error_count++))
    fi
    
    if [ $error_count -eq 0 ]; then
        print_success "所有文件拷贝验证通过！"
        return 0
    else
        print_error "发现 $error_count 个问题"
        return 1
    fi
}

# 显示帮助信息
show_help() {
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  all         拷贝所有文件（默认）"
    echo "  libs        仅拷贝动态库文件"
    echo "  exes        仅拷贝可执行文件"
    echo "  configs     仅拷贝配置文件"
    echo "  deps        仅拷贝第三方依赖"
    echo "  stp         仅拷贝 STP API 库"
    echo "  stp-deps    仅拷贝 STP 依赖库"
    echo "  verify      验证已拷贝的文件"
    echo "  clean       清理项目目录"
    echo "  help        显示此帮助信息"
    echo ""
    echo "示例:"
    echo "  $0          # 拷贝所有文件"
    echo "  $0 libs     # 仅拷贝库文件"
    echo "  $0 verify   # 验证文件"
}

# 清理目录
clean_directory() {
    print_warning "清理项目目录..."
    read -p "确定要清理项目目录吗？(y/N): " confirm
    if [[ $confirm =~ ^[Yy]$ ]]; then
        rm -f "$PROJECT_BIN_DIR"/*.so
        rm -f "$PROJECT_BIN_DIR"/TestTraderSTP*
        rm -f "$PROJECT_BIN_DIR"/test_stp_debug
        rm -rf "$PROJECT_BIN_DIR"/common
        rm -rf "$LIBS_DIR"
        print_success "清理完成"
    else
        print_info "取消清理"
    fi
}

# 主函数
main() {
    case "$1" in
        "libs")
            copy_libraries
            ;;
        "exes")
            copy_executables
            ;;
        "configs")
            copy_configs
            ;;
        "deps")
            copy_third_party
            ;;
        "stp")
            copy_stp_api
            ;;
        "stp-deps")
            copy_stp_dependencies
            ;;
        "verify")
            verify_copy
            ;;
        "clean")
            clean_directory
            ;;
        "help"|"--help"|"-h")
            show_help
            ;;
        "all"|"")
            copy_libraries
            copy_executables
            copy_configs
            copy_third_party
            copy_stp_api
            copy_stp_dependencies
            set_permissions
            verify_copy
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
