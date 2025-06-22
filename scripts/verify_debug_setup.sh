#!/bin/bash

# VSCode 调试配置验证脚本
# 作者: Hydelios
# 日期: 2025-06-20

echo "=========================================="
echo "    VSCode 调试配置验证"
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

# 检查 VSCode 配置文件
check_vscode_files() {
    print_info "检查 VSCode 配置文件..."
    
    local files=(
        ".vscode/launch.json"
        ".vscode/tasks.json"
        ".vscode/c_cpp_properties.json"
        ".vscode/settings.json"
    )
    
    for file in "${files[@]}"; do
        if [ -f "$WONDERTRADER_ROOT/$file" ]; then
            print_success "$file 存在"
        else
            print_error "$file 不存在"
        fi
    done
    echo ""
}

# 检查项目目录结构
check_project_structure() {
    print_info "检查项目目录结构..."
    
    local projects=(
        "project/stp"
        "project/sipui"
    )
    
    for project in "${projects[@]}"; do
        if [ -d "$WONDERTRADER_ROOT/$project" ]; then
            print_success "$project 目录存在"
        else
            print_error "$project 目录不存在"
        fi
    done
    echo ""
}

# 检查可执行文件
check_executables() {
    print_info "检查可执行文件..."
    
    local executables=(
        "project/stp/bin/test_stp_debug"
        "project/sipui/bin/test_parser_zc"
    )
    
    for exe in "${executables[@]}"; do
        if [ -f "$WONDERTRADER_ROOT/$exe" ]; then
            if [ -x "$WONDERTRADER_ROOT/$exe" ]; then
                print_success "$exe 存在且可执行"
            else
                print_warning "$exe 存在但不可执行"
            fi
        else
            print_warning "$exe 不存在（可能需要编译）"
        fi
    done
    echo ""
}

# 检查构建脚本
check_build_scripts() {
    print_info "检查构建脚本..."
    
    local scripts=(
        "project/stp/scripts/debug_stp.sh"
        "project/sipui/scripts/build_and_test.sh"
        "scripts/switch_project.sh"
    )
    
    for script in "${scripts[@]}"; do
        if [ -f "$WONDERTRADER_ROOT/$script" ]; then
            if [ -x "$WONDERTRADER_ROOT/$script" ]; then
                print_success "$script 存在且可执行"
            else
                print_warning "$script 存在但不可执行"
                chmod +x "$WONDERTRADER_ROOT/$script"
                print_info "已设置 $script 为可执行"
            fi
        else
            print_error "$script 不存在"
        fi
    done
    echo ""
}

# 检查必要的工具
check_tools() {
    print_info "检查必要的工具..."
    
    local tools=("g++" "gdb" "make" "cmake")
    
    for tool in "${tools[@]}"; do
        if command -v "$tool" >/dev/null 2>&1; then
            local version=$(${tool} --version 2>/dev/null | head -n1)
            print_success "$tool 已安装: $version"
        else
            print_error "$tool 未安装"
        fi
    done
    echo ""
}

# 检查库文件
check_libraries() {
    print_info "检查库文件..."
    
    local lib_dirs=(
        "project/stp/libs"
        "project/sipui/libs"
    )
    
    for lib_dir in "${lib_dirs[@]}"; do
        if [ -d "$WONDERTRADER_ROOT/$lib_dir" ]; then
            local lib_count=$(find "$WONDERTRADER_ROOT/$lib_dir" -name "*.so" 2>/dev/null | wc -l)
            if [ $lib_count -gt 0 ]; then
                print_success "$lib_dir 存在，包含 $lib_count 个 .so 文件"
            else
                print_warning "$lib_dir 存在但没有 .so 文件"
            fi
        else
            print_warning "$lib_dir 不存在"
        fi
    done
    echo ""
}

# 验证 JSON 文件格式
check_json_syntax() {
    print_info "验证 JSON 文件格式..."

    local json_files=(
        ".vscode/launch.json"
        ".vscode/tasks.json"
        ".vscode/c_cpp_properties.json"
        ".vscode/settings.json"
    )

    for json_file in "${json_files[@]}"; do
        if [ -f "$WONDERTRADER_ROOT/$json_file" ]; then
            # 简单检查：确保文件以 { 开头，以 } 结尾，并且包含基本的JSON结构
            local first_char=$(head -c 1 "$WONDERTRADER_ROOT/$json_file" | tr -d '[:space:]')
            local last_char=$(tail -c 2 "$WONDERTRADER_ROOT/$json_file" | tr -d '[:space:]' | tail -c 1)

            if [[ "$first_char" == "{" && "$last_char" == "}" ]]; then
                # 检查是否包含基本的JSON元素
                if grep -q '"version"' "$WONDERTRADER_ROOT/$json_file" || grep -q '"configurations"' "$WONDERTRADER_ROOT/$json_file" || grep -q '"tasks"' "$WONDERTRADER_ROOT/$json_file"; then
                    print_success "$json_file JSON 格式看起来正确"
                else
                    print_warning "$json_file 可能缺少必要的JSON字段"
                fi
            else
                print_error "$json_file JSON 格式可能有问题（不是以{}包围）"
            fi
        fi
    done
    echo ""
}

# 显示调试配置摘要
show_debug_summary() {
    print_info "调试配置摘要:"
    echo ""
    echo "🚀 可用的调试配置:"
    echo "   1. 调试 STP 项目"
    echo "   2. 调试 SIPUI 项目 (中畅解析器)"
    echo "   3. 调试 TraderSTP (兼容旧版)"
    echo "   4. 调试 TestTraderSTP (原版)"
    echo ""
    echo "📁 项目切换:"
    echo "   bash scripts/switch_project.sh"
    echo ""
    echo "🔧 编译任务:"
    echo "   - 编译 STP 项目"
    echo "   - 编译 SIPUI 项目"
    echo "   - 编译 TraderSTP 测试程序"
    echo "   - 编译所有项目"
    echo ""
}

# 主函数
main() {
    cd "$WONDERTRADER_ROOT"
    
    check_vscode_files
    check_project_structure
    check_executables
    check_build_scripts
    check_tools
    check_libraries
    check_json_syntax
    show_debug_summary
    
    print_info "验证完成！"
    print_info "在 VSCode 中按 Ctrl+Shift+D 打开调试面板，选择相应的配置开始调试。"
}

# 执行主函数
main "$@"
