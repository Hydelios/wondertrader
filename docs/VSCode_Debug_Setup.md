# WonderTrader VSCode 调试完整指南

## 📋 概述

本文档是 WonderTrader 项目的 VSCode 调试配置指南，基于 `project/` 目录结构的调试支持，为开发者提供完整的调试环境配置。

## 🎯 支持的调试项目

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

### 3. 🔧 原版 TestTraderSTP
- **描述**: WonderTrader 原版测试程序
- **可执行文件**: `src/build_all/build_x64/Release/bin/TestTraderSTP/TestTraderSTP`
- **工作目录**: `project/stp`

## 🚀 快速开始

### 方法一：一键调试（推荐）

1. **确保 VSCode 打开的是 `wondertrader` 根目录**
2. **直接按 `F5`**
3. **选择调试配置**：
   - `🚀 调试 STP 项目` - STP 交易接口测试项目调试
   - `🚀 调试 SIPUI 项目 (中畅解析器)` - 中畅行情解析器调试
   - `🔧 调试 TestTraderSTP (原版)` - 原版测试程序
4. **程序会自动编译并启动调试**

### 方法二：使用调试面板

1. 按 `Ctrl+Shift+D` 打开调试面板
2. 在调试配置下拉菜单中选择要调试的项目
3. 按 `F5` 开始调试

### 方法三：手动编译后调试

1. 按 `Ctrl+Shift+P` 打开命令面板
2. 输入 "Tasks: Run Task"
3. 选择相应的编译任务：
   - `编译 STP 项目`
   - `编译 SIPUI 项目`
4. 编译完成后按 `F5` 调试

### 方法四：使用项目切换脚本

```bash
# 交互式选择项目
bash scripts/switch_project.sh

# 直接切换到指定项目
bash scripts/switch_project.sh stp      # STP 项目
bash scripts/switch_project.sh sipui    # SIPUI 项目
bash scripts/switch_project.sh original # 原版项目
```

## 🎯 推荐调试流程

### 新手推荐流程

1. **选择调试环境**：
   - 🆕 **项目开发**：使用 `🚀 调试 STP 项目` 或 `🚀 调试 SIPUI 项目`
   - 🔧 **原版测试**：使用 `🔧 调试 TestTraderSTP (原版)`

2. **设置断点**：
   - 在 `src/TraderSTP/TraderSTP.cpp` 的 `init()` 函数设置断点
   - 在测试程序的关键位置设置断点

3. **启动调试**：
   - 按 `F5` 启动调试
   - 程序会自动停在断点处

4. **调试操作**：
   - `F10` - 单步跳过
   - `F11` - 单步进入
   - `F5` - 继续执行
   - 查看变量值、调用栈等

### 环境准备检查清单

#### 对于 project 环境：
- [ ] 确保项目已编译：运行相应的编译任务
- [ ] 检查配置文件：`project/stp/config.yaml` 或 `project/sipui/config/config.yaml`

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

### 常见问题及解决方案

#### 1. **找不到库文件**
**症状**：程序启动时提示找不到 `.so` 文件
**解决方案**：
```bash
# 对于 project 环境
cd project/stp  # 或 project/sipui
bash scripts/copy_libs.sh
```
- 检查 `LD_LIBRARY_PATH` 设置是否正确

#### 2. **编译失败**
**症状**：编译任务报错
**解决方案**：
```bash
# 手动编译检查错误
cd project/stp
bash scripts/build.sh
```
- 确保所有依赖库都已正确安装
- 检查编译脚本是否有执行权限：`chmod +x scripts/*.sh`

#### 3. **调试器无法启动**
**症状**：VSCode 提示调试器启动失败
**解决方案**：
- 确保 GDB 已安装：`sudo apt install gdb`
- 检查可执行文件是否存在且有执行权限
- 确保 VSCode 打开的是 `wondertrader` 根目录

#### 4. **配置文件找不到**
**症状**：程序提示无法加载配置文件
**解决方案**：
- 检查工作目录设置是否正确
- 确保配置文件路径相对于工作目录是正确的
- 检查配置文件格式是否正确（YAML 语法）

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
