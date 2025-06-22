#!/bin/bash

# VSCode 调试配置测试脚本
# 作者: Hydelios
# 日期: 2025-06-20

echo "=========================================="
echo "    VSCode 调试配置测试"
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
    echo -e "${GREEN}[✓]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[⚠]${NC} $1"
}

print_error() {
    echo -e "${RED}[✗]${NC} $1"
}

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WONDERTRADER_ROOT="$(dirname "$SCRIPT_DIR")"

print_info "WonderTrader 根目录: $WONDERTRADER_ROOT"
echo ""

# 测试STP项目编译
test_stp_compile() {
    print_info "测试 STP 项目编译..."
    
    cd "$WONDERTRADER_ROOT/project/stp"
    
    if [ -f "scripts/debug_stp.sh" ]; then
        print_info "运行 STP 编译脚本..."
        if bash scripts/debug_stp.sh compile; then
            print_success "STP 项目编译成功"
            
            if [ -f "bin/test_stp_debug" ]; then
                print_success "STP 可执行文件存在"
            else
                print_error "STP 可执行文件不存在"
            fi
        else
            print_error "STP 项目编译失败"
        fi
    else
        print_error "STP 编译脚本不存在"
    fi
    echo ""
}

# 测试SIPUI项目编译
test_sipui_compile() {
    print_info "测试 SIPUI 项目编译..."
    
    cd "$WONDERTRADER_ROOT/project/sipui"
    
    if [ -f "scripts/build_and_test.sh" ]; then
        print_info "运行 SIPUI 编译脚本..."
        if bash scripts/build_and_test.sh compile; then
            print_success "SIPUI 项目编译成功"
            
            if [ -f "bin/test_parser_zc" ]; then
                print_success "SIPUI 可执行文件存在"
            else
                print_error "SIPUI 可执行文件不存在"
            fi
        else
            print_error "SIPUI 项目编译失败"
        fi
    else
        print_error "SIPUI 编译脚本不存在"
    fi
    echo ""
}

# 测试调试配置文件
test_debug_configs() {
    print_info "测试调试配置文件..."
    
    cd "$WONDERTRADER_ROOT"
    
    # 检查launch.json中的程序路径
    local configs=(
        "project/stp/bin/test_stp_debug"
        "project/sipui/bin/test_parser_zc"
    )
    
    for config in "${configs[@]}"; do
        if [ -f "$config" ]; then
            if [ -x "$config" ]; then
                print_success "$config 存在且可执行"
            else
                print_warning "$config 存在但不可执行"
            fi
        else
            print_warning "$config 不存在"
        fi
    done
    echo ""
}

# 测试库文件路径
test_library_paths() {
    print_info "测试库文件路径..."
    
    local lib_dirs=(
        "$WONDERTRADER_ROOT/project/stp/libs"
        "$WONDERTRADER_ROOT/project/sipui/libs"
    )
    
    for lib_dir in "${lib_dirs[@]}"; do
        if [ -d "$lib_dir" ]; then
            local so_count=$(find "$lib_dir" -name "*.so" 2>/dev/null | wc -l)
            if [ $so_count -gt 0 ]; then
                print_success "$(basename $(dirname $lib_dir)) 库目录包含 $so_count 个 .so 文件"
            else
                print_warning "$(basename $(dirname $lib_dir)) 库目录没有 .so 文件"
            fi
        else
            print_error "$(basename $(dirname $lib_dir)) 库目录不存在"
        fi
    done
    echo ""
}

# 显示调试使用说明
show_debug_instructions() {
    print_info "VSCode 调试使用说明:"
    echo ""
    echo "1. 在 VSCode 中打开项目根目录"
    echo "2. 按 Ctrl+Shift+D 打开调试面板"
    echo "3. 选择以下调试配置之一:"
    echo "   - 🚀 调试 STP 项目"
    echo "   - 🚀 调试 SIPUI 项目 (中畅解析器)"
    echo "   - 🔧 调试 TraderSTP (兼容旧版)"
    echo "   - 🔧 调试 TestTraderSTP (原版)"
    echo "4. 按 F5 开始调试"
    echo ""
    echo "或者使用项目切换脚本:"
    echo "   bash scripts/switch_project.sh"
    echo ""
}

# 主函数
main() {
    test_stp_compile
    test_sipui_compile
    test_debug_configs
    test_library_paths
    show_debug_instructions
    
    print_info "调试配置测试完成！"
}

# 执行主函数
main "$@"
