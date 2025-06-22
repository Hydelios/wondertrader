# VSCode 调试配置指南

## 📋 概述

本文档介绍了为 WonderTrader 项目配置的 VSCode 调试环境，支持对 `project/` 目录下的不同项目进行独立调试。

## 🎯 支持的项目

### 1. 🚀 STP 项目 (`project/stp`)
- **描述**: STP 交易接口测试项目
- **可执行文件**: `project/stp/bin/test_stp_debug`
- **工作目录**: `project/stp`
- **配置文件**: `project/stp/config.yaml`

### 2. 🚀 SIPUI 项目 (`project/sipui`)
- **描述**: 中畅行情解析器项目
- **可执行文件**: `project/sipui/bin/test_parser_zc`
- **工作目录**: `project/sipui`
- **配置文件**: `project/sipui/config/config.yaml`

### 3. 🔧 传统 project 项目
- **描述**: 兼容旧版的调试环境
- **可执行文件**: `project/test_stp_debug`
- **工作目录**: `project`

### 4. 🔧 原版 TestTraderSTP
- **描述**: WonderTrader 原版测试程序
- **可执行文件**: `src/build_all/build_x64/Release/bin/TestTraderSTP/TestTraderSTP`
- **工作目录**: `project`

## 🚀 快速开始

### 方法一：使用 VSCode 调试面板

1. 在 VSCode 中打开 WonderTrader 项目
2. 按 `Ctrl+Shift+D` 打开调试面板
3. 在调试配置下拉菜单中选择要调试的项目：
   - `🚀 调试 STP 项目`
   - `🚀 调试 SIPUI 项目 (中畅解析器)`
   - `🔧 调试 TraderSTP (兼容旧版)`
   - `🔧 调试 TestTraderSTP (原版)`
4. 按 `F5` 开始调试

### 方法二：使用项目切换脚本

```bash
# 交互式选择项目
bash scripts/switch_project.sh

# 直接切换到指定项目
bash scripts/switch_project.sh stp      # STP 项目
bash scripts/switch_project.sh sipui    # SIPUI 项目
bash scripts/switch_project.sh project  # 传统项目
bash scripts/switch_project.sh original # 原版项目
```

## 🔧 调试配置详情

### 调试配置特性

- **自动编译**: 每个调试配置都会在启动前自动编译相应的项目
- **环境变量**: 自动设置 `LD_LIBRARY_PATH` 包含必要的库路径
- **GDB 增强**: 启用了 pretty-printing 和 Intel 汇编风格
- **日志记录**: 配置了详细的调试日志输出

### 编译任务

每个项目都有对应的编译任务：

- `编译 STP 项目`: 编译 STP 项目的测试程序和依赖库
- `编译 SIPUI 项目`: 编译 SIPUI 项目的中畅解析器测试程序
- `编译 TraderSTP 测试程序`: 编译传统的 TraderSTP 测试程序
- `编译所有项目`: 编译整个 WonderTrader 项目

## 📁 文件结构

```
.vscode/
├── launch.json          # 调试启动配置
├── tasks.json           # 编译任务配置
├── c_cpp_properties.json # C++ 智能感知配置
└── settings.json        # 工作区设置

project/
├── stp/                 # STP 项目
│   ├── bin/            # 可执行文件
│   ├── src/            # 源代码
│   ├── config/         # 配置文件
│   └── scripts/        # 构建脚本
└── sipui/              # SIPUI 项目
    ├── bin/            # 可执行文件
    ├── src/            # 源代码
    ├── config/         # 配置文件
    └── scripts/        # 构建脚本

scripts/
└── switch_project.sh   # 项目切换脚本
```

## 🛠️ 自定义配置

### 添加新项目

要为新项目添加调试支持：

1. **在 `launch.json` 中添加新的调试配置**:
```json
{
    "name": "🚀 调试 新项目",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/project/新项目/bin/可执行文件",
    "cwd": "${workspaceFolder}/project/新项目",
    "environment": [
        {
            "name": "LD_LIBRARY_PATH",
            "value": "${workspaceFolder}/project/新项目/libs:$LD_LIBRARY_PATH"
        }
    ],
    "preLaunchTask": "编译 新项目"
}
```

2. **在 `tasks.json` 中添加编译任务**:
```json
{
    "label": "编译 新项目",
    "type": "shell",
    "command": "bash",
    "args": ["scripts/build.sh"],
    "options": {
        "cwd": "${workspaceFolder}/project/新项目"
    }
}
```

### 修改库路径

如果需要修改库路径，更新相应调试配置中的 `LD_LIBRARY_PATH` 环境变量。

## 🐛 故障排除

### 常见问题

1. **找不到库文件**
   - 确保运行了相应的拷贝文件脚本
   - 检查 `LD_LIBRARY_PATH` 设置是否正确

2. **编译失败**
   - 确保所有依赖库都已正确安装
   - 检查编译脚本是否有执行权限

3. **调试器无法启动**
   - 确保 GDB 已安装：`sudo apt install gdb`
   - 检查可执行文件是否存在且有执行权限

### 日志查看

调试日志会显示在 VSCode 的调试控制台中。如果遇到问题，请查看：
- 编译任务的输出
- 调试控制台的错误信息
- 终端中的详细日志

## 📞 支持

如果遇到问题，请：
1. 检查本文档的故障排除部分
2. 查看项目的 README 文件
3. 检查相关脚本的帮助信息

---

**作者**: Hydelios  
**日期**: 2025-06-20  
**版本**: 1.0
