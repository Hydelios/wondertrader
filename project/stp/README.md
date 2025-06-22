# WonderTrader STP 项目

## 📋 项目概述

WonderTrader STP 项目是 WonderTrader 量化交易框架的 STP (Straight Through Processing) 交易接口实现，提供了完整的交易功能和调试工具。

## 🚀 快速开始

### 环境要求

- **操作系统**: Linux/macOS
- **编译器**: GCC 8.4+ 或 Clang
- **构建工具**: CMake 3.10+, Make
- **调试工具**: GDB (可选)
- **依赖库**: Boost, protobuf, OpenSSL

### 一键设置

```bash
# 进入脚本目录
cd scripts

# 完整设置流程
./copy_files.sh all && ./debug_stp.sh compile && ./debug_stp.sh test
```

## 📁 项目结构

```
project/stp/
├── README.md              # 项目说明文档
├── scripts/               # 🔧 自动化脚本
│   ├── copy_files.sh      # 文件拷贝脚本
│   └── debug_stp.sh       # 调试助手脚本
├── src/                   # 📝 源代码目录
│   └── test_stp_debug.cpp # 测试程序源码
├── bin/                   # 🚀 可执行文件目录
├── build/                 # 🔨 构建目录
├── libs/                  # 📚 库文件目录
├── config/                # ⚙️ 配置文件目录
└── docs/                  # 📖 文档目录
    ├── Scripts_User_Reference.md     # 脚本详细使用手册
    └── Scripts_Quick_Reference.md    # 脚本快速参考卡片
```

## 🔧 核心脚本

### copy_files.sh - 文件拷贝脚本

负责将编译后的库文件、可执行文件等拷贝到项目目录。

**常用命令**:
```bash
./copy_files.sh all      # 拷贝所有文件
./copy_files.sh libs     # 仅拷贝库文件
./copy_files.sh verify   # 验证拷贝结果
./copy_files.sh help     # 显示帮助
```

### debug_stp.sh - 调试助手脚本

提供完整的编译、运行和调试功能。

**常用命令**:
```bash
./debug_stp.sh compile   # 编译项目
./debug_stp.sh test      # 运行测试
./debug_stp.sh debug     # GDB调试
./debug_stp.sh help      # 显示帮助
```

## 📖 文档指南

### 📚 详细文档
- **[脚本用户参考手册](docs/Scripts_User_Reference.md)** - 完整的脚本使用指南
  - 详细的功能说明
  - 使用方法和参数
  - 故障排除指南
  - 最佳实践建议

### ⚡ 快速参考
- **[脚本快速参考卡片](docs/Scripts_Quick_Reference.md)** - 常用命令速查
  - 一键命令
  - 命令速查表
  - 常用工作流
  - 问题快速解决

## 🔄 典型工作流

### 首次使用
1. **环境准备**: 安装必要的依赖库
2. **文件拷贝**: `./copy_files.sh all`
3. **项目编译**: `./debug_stp.sh compile`
4. **运行测试**: `./debug_stp.sh test`

### 日常开发
1. **修改代码**: 编辑源文件
2. **快速测试**: `./debug_stp.sh test`
3. **问题调试**: `./debug_stp.sh debug`

### 问题排查
1. **检查状态**: `./copy_files.sh verify`
2. **清理重建**: `./debug_stp.sh clean && ./debug_stp.sh compile`
3. **查看日志**: 检查编译和运行输出

## 🚨 常见问题

### 库文件问题
```bash
# 症状：找不到 .so 文件
./copy_files.sh libs     # 重新拷贝库文件
```

### 编译问题
```bash
# 症状：编译失败
./debug_stp.sh clean     # 清理后重新编译
./debug_stp.sh compile
```

### 权限问题
```bash
# 症状：Permission denied
chmod +x scripts/*.sh   # 设置执行权限
```

## 🛠️ 依赖安装

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake gdb
sudo apt install libboost-all-dev libprotobuf-dev libssl-dev
```

### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install cmake gdb
sudo yum install boost-devel protobuf-devel openssl-devel
```

### macOS
```bash
brew install cmake gdb
brew install boost protobuf openssl
```

## 📞 获取帮助

### 脚本帮助
```bash
./copy_files.sh help     # 拷贝脚本帮助
./debug_stp.sh help      # 调试脚本帮助
```

### 文档资源
- 📖 [详细使用手册](docs/Scripts_User_Reference.md)
- ⚡ [快速参考卡片](docs/Scripts_Quick_Reference.md)
- 🔧 [VSCode调试配置](../../docs/VSCode_Debug_Setup.md)

### 在线资源
- [WonderTrader GitHub](https://github.com/wondertrader/wondertrader)
- [问题反馈](https://github.com/wondertrader/wondertrader/issues)
- [官方文档](https://wondertrader.github.io/)

## 🎯 性能优化

- 使用并行编译: `make -j$(nproc)`
- 增量编译: 避免不必要的 `clean` 操作
- 合理使用脚本选项: 只执行需要的操作
- 定期验证: 使用 `verify` 检查文件状态

## 📋 版本信息

- **版本**: 1.0
- **状态**: 已验证可用
- **最后更新**: 2025-06-22
- **兼容性**: Linux/macOS

## 🤝 贡献指南

1. Fork 项目
2. 创建功能分支
3. 提交更改
4. 推送到分支
5. 创建 Pull Request

---

**💡 提示**: 建议先阅读 [快速参考卡片](docs/Scripts_Quick_Reference.md) 了解常用命令，然后查阅 [详细使用手册](docs/Scripts_User_Reference.md) 获取完整信息。
