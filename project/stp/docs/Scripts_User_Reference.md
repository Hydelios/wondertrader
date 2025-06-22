# WonderTrader STP 项目脚本用户参考手册

## 📋 概述

本文档提供了 WonderTrader STP 项目中所有脚本的详细使用指南。这些脚本经过全面检查和修复，确保在目标环境中能够正常工作。

### 🎯 脚本列表

| 脚本名称        | 功能描述     | 主要用途                                     |
| --------------- | ------------ | -------------------------------------------- |
| `copy_files.sh` | 文件拷贝脚本 | 将编译后的库文件、可执行文件等拷贝到项目目录 |
| `debug_stp.sh`  | 调试助手脚本 | 编译、运行和调试 TraderSTP 测试程序          |

## 🚀 快速开始

### 环境要求

- **操作系统**: Linux/macOS
- **编译器**: GCC 8.4+ 或 Clang
- **构建工具**: CMake 3.10+, Make
- **调试工具**: GDB (可选，用于调试)
- **依赖库**: Boost, protobuf, OpenSSL

### 基本使用流程

1. **拷贝必要文件**:
   ```bash
   cd project/stp/scripts
   ./copy_files.sh all
   ```

2. **编译项目**:
   ```bash
   ./debug_stp.sh compile
   ```

3. **运行测试**:
   ```bash
   ./debug_stp.sh test
   ```

## 📁 项目目录结构

```
project/stp/
├── scripts/           # 脚本目录
│   ├── copy_files.sh  # 文件拷贝脚本
│   └── debug_stp.sh   # 调试助手脚本
├── src/               # 源代码目录
│   └── test_stp_debug.cpp
├── bin/               # 可执行文件目录
├── build/             # 构建目录
├── libs/              # 库文件目录
├── config/            # 配置文件目录
└── docs/              # 文档目录
```

## 🔧 copy_files.sh 详细说明

### 功能概述

`copy_files.sh` 脚本负责将编译后的文件拷贝到 STP 项目目录，包括动态库、可执行文件、配置文件和第三方依赖。

### 使用方法

```bash
./copy_files.sh [选项]
```

### 可用选项

| 选项       | 描述                 | 示例                       |
| ---------- | -------------------- | -------------------------- |
| `all`      | 拷贝所有文件（默认） | `./copy_files.sh all`      |
| `libs`     | 仅拷贝动态库文件     | `./copy_files.sh libs`     |
| `exes`     | 仅拷贝可执行文件     | `./copy_files.sh exes`     |
| `configs`  | 仅拷贝配置文件       | `./copy_files.sh configs`  |
| `deps`     | 仅拷贝第三方依赖     | `./copy_files.sh deps`     |
| `stp`      | 仅拷贝 STP API 库    | `./copy_files.sh stp`      |
| `stp-deps` | 仅拷贝 STP 依赖库    | `./copy_files.sh stp-deps` |
| `verify`   | 验证已拷贝的文件     | `./copy_files.sh verify`   |
| `clean`    | 清理目录             | `./copy_files.sh clean`    |
| `help`     | 显示帮助信息         | `./copy_files.sh help`     |

### 详细功能说明

#### 1. 库文件拷贝 (`libs`)

- **功能**: 拷贝编译后的动态库文件到 `libs/` 目录
- **源目录**: 自动检测多个可能的构建目录
- **目标目录**: `project/stp/libs/`
- **处理逻辑**: 
  - 优先使用本地构建目录 (`build/`)
  - 回退到全局构建目录
  - 为关键库文件创建符号链接

#### 2. 可执行文件拷贝 (`exes`)

- **功能**: 拷贝测试程序和其他可执行文件
- **目标目录**: `project/stp/bin/`
- **处理的文件**:
  - `test_stp_debug` -> `bin/`
  - `TestTraderSTP` -> `TestTraderSTP_original`

#### 3. 配置文件拷贝 (`configs`)

- **功能**: 从 `dist/` 目录拷贝配置文件模板
- **目标目录**: `project/stp/`
- **包含内容**:
  - YAML 配置文件
  - `common/` 目录（拷贝到项目根目录）

#### 4. 第三方依赖 (`deps`)

- **功能**: 拷贝第三方库文件
- **搜索目录**:
  - `3rd/mydeps_gcc8.4.0/mydeps/lib`
  - `3rd/lib`
  - `deps/lib`
  - `/usr/local/lib`

#### 5. STP API 库 (`stp`)

- **功能**: 拷贝 STP 交易 API 库
- **关键文件**: `libSTPTradeApi.so`
- **符号链接**: 创建 `stptradeapi.so` 链接

#### 6. 验证功能 (`verify`)

- **功能**: 检查已拷贝文件的完整性
- **检查项目**:
  - 关键库文件存在性
  - 库文件依赖关系
  - 文件权限设置

### 故障排除

#### 常见问题

1. **库文件未找到**
   ```
   [错误] 未找到包含库文件的目录
   ```
   **解决方案**: 先编译项目或检查构建目录

2. **权限问题**
   ```
   Permission denied
   ```
   **解决方案**: 确保脚本有执行权限
   ```bash
   chmod +x copy_files.sh
   ```

3. **符号链接失败**
   **解决方案**: 检查目标目录是否存在且可写

## 🐛 debug_stp.sh 详细说明

### 功能概述

`debug_stp.sh` 脚本提供了完整的 TraderSTP 项目编译、运行和调试功能。

### 使用方法

```bash
./debug_stp.sh [选项]
```

### 可用选项

| 选项      | 描述                  | 示例                     |
| --------- | --------------------- | ------------------------ |
| `compile` | 编译整个项目          | `./debug_stp.sh compile` |
| `test`    | 编译并运行测试程序    | `./debug_stp.sh test`    |
| `debug`   | 使用 GDB 调试测试程序 | `./debug_stp.sh debug`   |
| `clean`   | 清理编译文件          | `./debug_stp.sh clean`   |
| `help`    | 显示帮助信息          | `./debug_stp.sh help`    |
| (无参数)  | 交互式菜单            | `./debug_stp.sh`         |

### 详细功能说明

#### 1. 编译功能 (`compile`)

- **编译方式**: 优先使用 CMake，回退到主项目编译脚本
- **构建目录**: `project/stp/build/`
- **编译类型**: Release 模式
- **并行编译**: 使用 `make -j$(nproc)` 加速编译

#### 2. 测试程序编译 (`test`)

- **源文件**: `src/test_stp_debug.cpp`
- **输出文件**: `bin/test_stp_debug`
- **编译选项**:
  - C++17 标准
  - 调试信息 (`-g`)
  - 无优化 (`-O0`)
  - 警告选项 (`-Wall -Wextra`)

#### 3. 库路径配置

脚本自动配置以下库路径：
- 项目根目录: `project/stp/`
- 库文件目录: `project/stp/libs/`
- 构建目录: `project/stp/build/`

#### 4. 调试功能 (`debug`)

- **调试器**: GDB
- **前置检查**: 自动检查 GDB 是否安装
- **环境配置**: 自动设置 `LD_LIBRARY_PATH`
- **工作目录**: 自动切换到项目根目录

### 故障排除

#### 常见问题

1. **编译失败**
   ```
   [错误] STP 项目编译失败
   ```
   **解决方案**:
   - 检查依赖库是否安装
   - 确保 CMakeLists.txt 存在
   - 查看编译错误信息

2. **库文件未找到**
   ```
   [错误] libTraderSTP.so 未找到
   ```
   **解决方案**:
   - 先运行 `./copy_files.sh libs`
   - 或者先编译主项目

3. **GDB 未安装**
   ```
   [错误] GDB 未安装，无法进行调试
   ```
   **解决方案**:
   ```bash
   # Ubuntu/Debian
   sudo apt install gdb
   
   # CentOS/RHEL
   sudo yum install gdb
   
   # macOS
   brew install gdb
   ```

## 🔄 脚本之间的关系

### 执行顺序建议

1. **首次设置**:
   ```bash
   ./copy_files.sh all      # 拷贝所有必要文件
   ./debug_stp.sh compile   # 编译项目
   ./debug_stp.sh test      # 运行测试
   ```

2. **日常开发**:
   ```bash
   ./debug_stp.sh test      # 编译并测试
   ./debug_stp.sh debug     # 调试问题
   ```

3. **清理重建**:
   ```bash
   ./debug_stp.sh clean     # 清理编译文件
   ./copy_files.sh clean    # 清理拷贝文件
   ./copy_files.sh all      # 重新拷贝
   ./debug_stp.sh compile   # 重新编译
   ```

### 依赖关系

- `debug_stp.sh` 依赖于 `copy_files.sh` 拷贝的库文件
- 两个脚本都会自动创建必要的目录结构
- 脚本具有良好的错误处理和回退机制

## 📝 最佳实践

### 开发工作流

1. **环境准备**:
   - 确保所有依赖库已安装
   - 设置正确的编译环境

2. **首次运行**:
   - 使用 `copy_files.sh verify` 检查环境
   - 使用 `debug_stp.sh compile` 编译项目

3. **日常开发**:
   - 修改代码后使用 `debug_stp.sh test` 快速测试
   - 遇到问题时使用 `debug_stp.sh debug` 调试

4. **问题排查**:
   - 查看脚本输出的详细信息
   - 使用 `verify` 选项检查文件状态
   - 必要时使用 `clean` 选项重新开始

### 性能优化

- 使用并行编译 (`make -j$(nproc)`)
- 增量编译，避免不必要的清理
- 合理使用脚本选项，只执行需要的操作

## 🔍 高级用法

### 自定义编译选项

如果需要自定义编译选项，可以修改 `debug_stp.sh` 中的编译命令：

```bash
# 在 debug_stp.sh 中找到编译命令并修改
g++ -std=c++17 -g -O0 -Wall -Wextra \
    -DCUSTOM_DEFINE \              # 添加自定义宏定义
    -I"$CUSTOM_INCLUDE_DIR" \      # 添加自定义包含目录
    # ... 其他选项
```

### 环境变量配置

脚本支持以下环境变量：

| 环境变量           | 描述           | 默认值       |
| ------------------ | -------------- | ------------ |
| `LD_LIBRARY_PATH`  | 库文件搜索路径 | 自动设置     |
| `CMAKE_BUILD_TYPE` | CMake 构建类型 | Release      |
| `MAKEFLAGS`        | Make 编译选项  | `-j$(nproc)` |

### 批量操作

```bash
# 批量清理和重建
for action in clean all compile test; do
    if [[ "$action" == "clean" || "$action" == "all" ]]; then
        ./copy_files.sh $action
    else
        ./debug_stp.sh $action
    fi
done
```

## 🧪 测试和验证

### 功能测试

1. **脚本语法测试**:
   ```bash
   bash -n copy_files.sh
   bash -n debug_stp.sh
   ```

2. **功能完整性测试**:
   ```bash
   ./copy_files.sh verify
   ./debug_stp.sh compile
   ```

3. **集成测试**:
   ```bash
   # 完整的构建和测试流程
   ./copy_files.sh clean
   ./copy_files.sh all
   ./debug_stp.sh clean
   ./debug_stp.sh compile
   ./debug_stp.sh test
   ```

### 性能基准

在标准开发环境中的预期执行时间：

| 操作                   | 预期时间 | 说明              |
| ---------------------- | -------- | ----------------- |
| `copy_files.sh all`    | 10-30秒  | 取决于文件数量    |
| `debug_stp.sh compile` | 1-5分钟  | 取决于代码量和CPU |
| `debug_stp.sh test`    | 5-10秒   | 包含编译测试程序  |

## 🚨 常见错误和解决方案

### 错误代码对照表

| 错误代码 | 错误描述         | 解决方案                     |
| -------- | ---------------- | ---------------------------- |
| 1        | 文件或目录不存在 | 检查路径，确保文件存在       |
| 2        | 权限不足         | 使用 `chmod +x` 设置执行权限 |
| 126      | 脚本无法执行     | 检查脚本格式和权限           |
| 127      | 命令未找到       | 安装缺失的依赖工具           |

### 详细故障排除

#### 1. 库文件链接错误

**症状**:
```
error while loading shared libraries: libTraderSTP.so: cannot open shared object file
```

**解决方案**:
```bash
# 检查库文件是否存在
ls -la project/stp/libs/libTraderSTP.so

# 检查库路径设置
echo $LD_LIBRARY_PATH

# 重新拷贝库文件
./copy_files.sh libs
```

#### 2. 编译依赖缺失

**症状**:
```
fatal error: boost/filesystem.hpp: No such file or directory
```

**解决方案**:
```bash
# Ubuntu/Debian
sudo apt install libboost-all-dev

# CentOS/RHEL
sudo yum install boost-devel

# macOS
brew install boost
```

#### 3. CMake 版本过低

**症状**:
```
CMake Error: CMake 3.10 or higher is required
```

**解决方案**:
```bash
# 升级 CMake
sudo apt update
sudo apt install cmake

# 或者从源码编译最新版本
```

## 📚 参考资料

### 相关文档

- [WonderTrader 官方文档](https://wondertrader.github.io/)
- [VSCode 调试配置指南](../../../docs/VSCode_Debug_Setup.md)
- [配置vs硬编码问题分析](../../../docs/Configuration_vs_Hardcoding_Analysis.md)

### 外部依赖

- [CMake 官方文档](https://cmake.org/documentation/)
- [GDB 调试指南](https://www.gnu.org/software/gdb/documentation/)
- [Boost 库文档](https://www.boost.org/doc/)

### 社区资源

- [WonderTrader GitHub](https://github.com/wondertrader/wondertrader)
- [问题反馈](https://github.com/wondertrader/wondertrader/issues)

## 📋 更新日志

### v1.0 (2025-06-22)

- ✅ 修复了 `copy_files.sh` 中项目目录变量的问题
- ✅ 修正了所有脚本中的路径假设问题
- ✅ 改进了错误处理和用户反馈
- ✅ 添加了完整的验证功能
- ✅ 优化了库文件搜索逻辑
- ✅ 增强了脚本的健壮性和容错性

### 已知问题

- 在某些环境中，第三方依赖路径可能需要手动调整
- macOS 上的 GDB 可能需要额外的权限配置
- 部分静态库可能不会被自动检测

### 计划改进

- [ ] 添加自动依赖检测和安装功能
- [ ] 支持多种编译器配置
- [ ] 添加性能分析工具集成
- [ ] 改进跨平台兼容性

---

**作者**: AI Assistant
**日期**: 2025-06-22
**版本**: 1.0
**状态**: 已验证可用
**最后更新**: 2025-06-22
