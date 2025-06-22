# WonderTrader STP 脚本快速参考卡片

## 🚀 一键命令

```bash
# 进入脚本目录
cd project/stp/scripts

# 完整设置流程（首次使用）
./copy_files.sh all && ./debug_stp.sh compile && ./debug_stp.sh test

# 日常开发流程
./debug_stp.sh test    # 编译并运行测试

# 调试问题
./debug_stp.sh debug   # 启动 GDB 调试器
```

## 📋 命令速查表

### copy_files.sh

| 命令 | 功能 | 用途 |
|------|------|------|
| `./copy_files.sh all` | 拷贝所有文件 | 首次设置 |
| `./copy_files.sh libs` | 拷贝库文件 | 更新库文件 |
| `./copy_files.sh verify` | 验证文件 | 检查状态 |
| `./copy_files.sh clean` | 清理文件 | 重置环境 |

### debug_stp.sh

| 命令 | 功能 | 用途 |
|------|------|------|
| `./debug_stp.sh compile` | 编译项目 | 构建项目 |
| `./debug_stp.sh test` | 运行测试 | 快速测试 |
| `./debug_stp.sh debug` | GDB调试 | 问题调试 |
| `./debug_stp.sh clean` | 清理构建 | 重新开始 |

## 🔧 常用工作流

### 首次设置
```bash
cd project/stp/scripts
./copy_files.sh all      # 拷贝所有必要文件
./debug_stp.sh compile   # 编译项目
./debug_stp.sh test      # 运行测试验证
```

### 日常开发
```bash
# 修改代码后
./debug_stp.sh test      # 快速编译测试

# 遇到问题时
./debug_stp.sh debug     # 启动调试器
```

### 清理重建
```bash
./debug_stp.sh clean     # 清理构建文件
./copy_files.sh clean    # 清理拷贝文件
./copy_files.sh all      # 重新拷贝
./debug_stp.sh compile   # 重新编译
```

### 问题排查
```bash
./copy_files.sh verify   # 检查文件状态
bash -n *.sh            # 检查脚本语法
./debug_stp.sh help     # 查看帮助信息
```

## 🚨 常见问题快速解决

### 库文件问题
```bash
# 症状：找不到 .so 文件
./copy_files.sh libs     # 重新拷贝库文件
./copy_files.sh verify   # 验证库文件状态
```

### 编译问题
```bash
# 症状：编译失败
./debug_stp.sh clean     # 清理构建文件
./debug_stp.sh compile   # 重新编译
```

### 权限问题
```bash
# 症状：Permission denied
chmod +x *.sh           # 设置执行权限
```

### 依赖问题
```bash
# 症状：找不到头文件或库
# Ubuntu/Debian
sudo apt install libboost-all-dev cmake gdb

# macOS
brew install boost cmake gdb
```

## 📁 目录结构速览

```
project/stp/
├── scripts/           # 🔧 脚本目录
│   ├── copy_files.sh  # 文件拷贝脚本
│   └── debug_stp.sh   # 调试助手脚本
├── src/               # 📝 源代码
├── bin/               # 🚀 可执行文件
├── build/             # 🔨 构建目录
├── libs/              # 📚 库文件
└── docs/              # 📖 文档
```

## 🎯 脚本选项速记

### copy_files.sh 选项
- `all` - 拷贝所有（默认）
- `libs` - 仅库文件
- `exes` - 仅可执行文件
- `configs` - 仅配置文件
- `deps` - 仅第三方依赖
- `stp` - 仅STP API库
- `verify` - 验证文件
- `clean` - 清理文件

### debug_stp.sh 选项
- `compile` - 编译项目
- `test` - 编译并运行测试
- `debug` - GDB调试
- `clean` - 清理构建文件
- `help` - 显示帮助

## 🔍 状态检查命令

```bash
# 检查脚本语法
bash -n copy_files.sh
bash -n debug_stp.sh

# 检查文件状态
./copy_files.sh verify

# 检查库文件
ls -la libs/
ldd bin/test_stp_debug  # 检查动态库依赖

# 检查环境
echo $LD_LIBRARY_PATH
which gdb
which cmake
```

## 📞 获取帮助

```bash
# 脚本帮助
./copy_files.sh help
./debug_stp.sh help

# 详细文档
cat docs/Scripts_User_Reference.md

# 在线资源
# - WonderTrader GitHub: https://github.com/wondertrader/wondertrader
# - 问题反馈: https://github.com/wondertrader/wondertrader/issues
```

## ⚡ 性能提示

- 使用 `make -j$(nproc)` 并行编译
- 增量编译，避免不必要的 `clean`
- 合理使用脚本选项，只执行需要的操作
- 定期使用 `verify` 检查文件状态

---

**💡 提示**: 将此文件保存为书签，随时查阅常用命令！
