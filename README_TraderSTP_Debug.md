# TraderSTP 调试环境使用指南

## 📋 概述

这是一个完整的 TraderSTP 调试环境，包含了所有必要的库文件、配置文件和调试工具。

## 🎯 主要特性

- ✅ **完整的库文件管理** - 所有依赖库统一放在 `libs` 目录
- ✅ **智能拷贝脚本** - 自动检测和拷贝所有必要文件
- ✅ **VSCode 集成** - 完整的编译和调试配置
- ✅ **STP 依赖库支持** - 包含所有 STP API 依赖库
- ✅ **参数解析测试** - 完整的参数验证功能

## 📁 目录结构

```
prj_bin/
├── libs/                          # 所有依赖库文件
│   ├── libTraderSTP.so            # TraderSTP 主库
│   ├── libSTPTradeApi.so          # STP API 库
│   ├── libprotobuf.so.12          # protobuf 库
│   └── ... (其他依赖库)
├── .vscode/                       # VSCode 配置
│   ├── launch.json                # 调试配置
│   └── tasks.json                 # 编译任务
├── copy_files_to_prj_bin.sh       # 智能文件拷贝脚本
├── debug_stp.sh                   # 调试助手脚本
├── test_stp_debug.cpp             # 测试程序源码
├── stp_config.yaml               # STP 配置文件示例
└── stptradeapi.so -> libs/libSTPTradeApi.so  # 符号链接
```

## 🚀 快速开始

### 1. 拷贝所有必要文件

```bash
cd prj_bin
./copy_files_to_prj_bin.sh
```

这会自动拷贝：
- 编译后的库文件
- 可执行文件
- 配置文件
- 第三方依赖
- STP API 库
- STP 依赖库 (32个库文件)

### 2. 编译测试程序

```bash
./debug_stp.sh compile
```

或者直接编译测试程序：

```bash
g++ -std=c++17 -g -O0 \
    -I../src/Includes \
    -I../src/Share \
    -I../3rd/mydeps_gcc8.4.0/mydeps/include \
    -L. -Llibs \
    -L../src/build_all/build_x64/Release/libs \
    -lTraderSTP -lWTSTools -lWTSUtils \
    -lpthread -ldl \
    -o test_stp_debug test_stp_debug.cpp
```

### 3. 运行测试

```bash
export LD_LIBRARY_PATH=.:libs:$LD_LIBRARY_PATH
./test_stp_debug
```

或使用脚本：

```bash
./debug_stp.sh test
```

### 4. VSCode 调试

1. 打开 VSCode 并加载 `prj_bin` 文件夹
2. 按 `F5` 启动调试
3. 设置断点在 `TraderSTP::init()` 函数
4. 开始调试

## 🔧 脚本功能

### copy_files_to_prj_bin.sh

智能文件拷贝脚本，支持以下操作：

```bash
./copy_files_to_prj_bin.sh [选项]

选项:
  all         拷贝所有文件 (默认)
  libs        仅拷贝动态库文件
  exes        仅拷贝可执行文件
  configs     仅拷贝配置文件
  deps        仅拷贝第三方依赖
  stp         仅拷贝 STP API 库
  stp-deps    仅拷贝 STP 依赖库
  verify      验证已拷贝的文件
  clean       清理目录
  help        显示帮助信息
```

### debug_stp.sh

调试助手脚本：

```bash
./debug_stp.sh [选项]

选项:
  compile     编译整个项目
  test        编译并运行测试程序
  debug       使用 GDB 调试测试程序
  clean       清理编译文件
  help        显示帮助信息
```

## 📊 STP 参数配置

### 必需参数

- `front` - 前置机地址（支持多个，用分号分隔）
- `broker` - 券商代码
- `user` - 用户名
- `pass` - 密码

### 可选参数

- `flowdir` - 流文件目录（默认: "STPTDFlow"）
- `stpmodule` - STP模块名（默认: "stptradeapi"）

### 配置文件示例 (stp_config.yaml)

```yaml
traders:
- id: stp_trader
  active: true
  module: TraderSTP
  front: "tcp://192.168.1.100:9001;tcp://192.168.1.101:9001"
  broker: "1234"
  user: "your_username"
  pass: "your_password"
  flowdir: "STPTDFlow"
  stpmodule: "stptradeapi"
```

## 🐛 调试技巧

### 1. 设置断点

在 VSCode 中，可以在以下关键位置设置断点：
- `TraderSTP::init()` - 初始化过程
- `TraderSTP::connect()` - 连接过程
- `TraderSTP::login()` - 登录过程

### 2. 查看库依赖

```bash
ldd test_stp_debug
ldd libs/libTraderSTP.so
```

### 3. 检查库文件

```bash
objdump -T libs/libTraderSTP.so | grep -i trader
nm -D libs/libTraderSTP.so | grep -i create
```

### 4. 环境变量

确保设置正确的库路径：

```bash
export LD_LIBRARY_PATH=.:libs:$LD_LIBRARY_PATH
```

## ⚠️ 常见问题

### 1. 库文件缺失

**问题**: `error while loading shared libraries`

**解决**: 运行拷贝脚本并验证

```bash
./copy_files_to_prj_bin.sh
./copy_files_to_prj_bin.sh verify
```

### 2. 编译错误

**问题**: 头文件找不到或编译失败

**解决**: 确保使用 C++17 标准和正确的头文件路径

### 3. 段错误

**问题**: 程序运行时崩溃

**解决**: 使用 GDB 调试

```bash
./debug_stp.sh debug
```

## 📈 成功指标

- [x] 编译成功无错误
- [x] 库文件全部加载
- [x] 参数解析成功
- [x] 程序稳定运行
- [x] VSCode 调试正常

## 🔮 后续扩展

1. **添加更多测试用例** - 扩展测试程序功能
2. **集成单元测试** - 添加自动化测试
3. **性能分析** - 添加性能监控工具
4. **日志系统** - 完善日志记录功能

---

**作者**: Hydelios  
**日期**: 2025-06-17  
**版本**: 1.0.0
