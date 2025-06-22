#!/bin/bash

# 简单的JSON格式检查脚本
# 使用node.js来验证JSON格式

check_json_file() {
    local file="$1"
    if [ -f "$file" ]; then
        if node -e "JSON.parse(require('fs').readFileSync('$file', 'utf8'))" 2>/dev/null; then
            echo "✓ $file JSON 格式正确"
        else
            echo "✗ $file JSON 格式错误"
        fi
    else
        echo "✗ $file 文件不存在"
    fi
}

echo "检查 VSCode 配置文件的 JSON 格式..."
check_json_file ".vscode/launch.json"
check_json_file ".vscode/tasks.json"
check_json_file ".vscode/c_cpp_properties.json"
check_json_file ".vscode/settings.json"
