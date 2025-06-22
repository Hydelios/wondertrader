#!/bin/bash

# 项目切换脚本 - 快速切换到不同的项目目录进行调试
# 作者: Hydelios
# 日期: 2025-06-20

echo "=========================================="
echo "    WonderTrader 项目切换器"
echo "=========================================="

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
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

print_project() {
    echo -e "${PURPLE}[项目]${NC} $1"
}

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WONDERTRADER_ROOT="$(dirname "$SCRIPT_DIR")"
PROJECT_DIR="$WONDERTRADER_ROOT/project"

print_info "WonderTrader 根目录: $WONDERTRADER_ROOT"
print_info "项目目录: $PROJECT_DIR"

# 显示可用项目
show_projects() {
    echo ""
    echo -e "${CYAN}可用的项目:${NC}"
    echo "1. 🚀 STP 项目 (project/stp)"
    echo "   - 描述: STP 交易接口测试项目"
    echo "   - 可执行文件: bin/test_stp_debug"
    echo "   - 配置文件: config.yaml"
    echo ""
    echo "2. 🚀 SIPUI 项目 (project/sipui)"
    echo "   - 描述: 中畅行情解析器项目"
    echo "   - 可执行文件: bin/test_parser_zc"
    echo "   - 配置文件: config/config.yaml"
    echo ""

    echo "3. 🔧 原版 TestTraderSTP"
    echo "   - 描述: WonderTrader 原版测试程序"
    echo "   - 位置: src/build_all/build_x64/Release/bin/TestTraderSTP/"
    echo ""
}

# 切换到指定项目
switch_to_project() {
    local project_choice=$1
    
    case $project_choice in
        1|"stp")
            print_project "切换到 STP 项目"
            cd "$PROJECT_DIR/stp"
            print_success "当前目录: $(pwd)"
            print_info "可用命令:"
            echo "  - bash scripts/debug_stp.sh compile  # 编译项目"
            echo "  - bash scripts/debug_stp.sh test     # 运行测试"
            echo "  - bash scripts/debug_stp.sh debug    # 启动调试"
            echo "  - bash scripts/copy_files.sh all     # 拷贝文件"
            ;;
        2|"sipui")
            print_project "切换到 SIPUI 项目"
            cd "$PROJECT_DIR/sipui"
            print_success "当前目录: $(pwd)"
            print_info "可用命令:"
            echo "  - bash scripts/build_and_test.sh compile  # 编译项目"
            echo "  - bash scripts/build_and_test.sh test     # 运行测试"
            echo "  - bash scripts/copy_files.sh all          # 拷贝文件"
            echo "  - ./bin/test_parser_zc                    # 直接运行"
            ;;
        3|"original")
            print_project "切换到原版 TestTraderSTP"
            cd "$WONDERTRADER_ROOT/src"
            print_success "当前目录: $(pwd)"
            print_info "可用命令:"
            echo "  - bash build_release.sh          # 编译所有项目"
            echo "  - cd build_all/build_x64/Release/bin/TestTraderSTP && ./TestTraderSTP"
            ;;
        *)
            print_error "无效的项目选择: $project_choice"
            return 1
            ;;
    esac
}

# 显示VSCode调试配置信息
show_vscode_info() {
    echo ""
    echo -e "${CYAN}VSCode 调试配置:${NC}"
    echo "在 VSCode 中，您可以使用以下调试配置:"
    echo ""
    echo "🚀 调试 STP 项目"
    echo "   - 自动编译并调试 project/stp/bin/test_stp_debug"
    echo "   - 工作目录: project/stp"
    echo ""
    echo "🚀 调试 SIPUI 项目 (中畅解析器)"
    echo "   - 自动编译并调试 project/sipui/bin/test_parser_zc"
    echo "   - 工作目录: project/sipui"
    echo ""

    echo "🔧 调试 TestTraderSTP (原版)"
    echo "   - 调试原版 WonderTrader 测试程序"
    echo ""
    print_info "在 VSCode 中按 F5 或使用调试面板选择相应的配置即可开始调试"
}

# 主函数
main() {
    if [ $# -eq 0 ]; then
        show_projects
        show_vscode_info
        echo ""
        echo -n "请选择项目 (1-3) 或输入项目名称: "
        read choice
        switch_to_project "$choice"
    else
        switch_to_project "$1"
    fi
}

# 显示帮助信息
show_help() {
    echo "用法: $0 [项目选择]"
    echo ""
    echo "项目选择:"
    echo "  1, stp       切换到 STP 项目"
    echo "  2, sipui     切换到 SIPUI 项目"
    echo "  3, original  切换到原版 TestTraderSTP"
    echo "  help         显示此帮助信息"
    echo ""
    echo "示例:"
    echo "  $0           # 交互式选择"
    echo "  $0 stp       # 直接切换到 STP 项目"
    echo "  $0 3         # 切换到原版 TestTraderSTP"
}

# 处理命令行参数
case "$1" in
    "help"|"--help"|"-h")
        show_help
        ;;
    *)
        main "$@"
        ;;
esac
