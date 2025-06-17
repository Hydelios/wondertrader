# VSCode 调试 TraderSTP 说明

## 🎯 问题解决

你遇到的问题是因为 VSCode 打开的是整个 `wondertrader` 项目文件夹，而不是 `prj_bin` 文件夹。

## ✅ 已解决方案

我已经在 **wondertrader 根目录** 创建了完整的 VSCode 配置：

- `/root/trading_sys/wondertrader/.vscode/launch.json` - 调试配置
- `/root/trading_sys/wondertrader/.vscode/tasks.json` - 编译任务

## 🚀 现在可以直接使用

### 方法1：按 F5 调试（推荐）

1. 确保 VSCode 打开的是 `wondertrader` 文件夹
2. 直接按 `F5` 
3. 选择 "调试 TraderSTP" 配置
4. 程序会自动编译并启动调试

### 方法2：手动编译后调试

1. 按 `Ctrl+Shift+P` 打开命令面板
2. 输入 "Tasks: Run Task"
3. 选择 "编译 TraderSTP 测试程序"
4. 编译完成后按 `F5` 调试

## 📋 可用的调试配置

在调试面板中，你可以选择：

1. **调试 TraderSTP** - 调试我们创建的测试程序
2. **调试 TestTraderSTP (原版)** - 调试原始的测试程序

## 📋 可用的编译任务

按 `Ctrl+Shift+P` → "Tasks: Run Task" 可以选择：

1. **编译 TraderSTP 测试程序** - 编译调试测试程序
2. **编译所有项目** - 编译整个 WonderTrader 项目
3. **拷贝库文件到 prj_bin** - 拷贝所有必要的库文件
4. **清理 TraderSTP 调试文件** - 清理编译文件

## 🔧 调试设置

调试配置已经自动设置了：

- **工作目录**: `${workspaceFolder}/prj_bin`
- **库路径**: 包含 `prj_bin/libs` 目录
- **断点**: 可以在 TraderSTP 相关代码中设置
- **预编译任务**: 自动编译测试程序

## 🎯 推荐调试流程

1. **设置断点**：
   - 在 `src/TraderSTP/TraderSTP.cpp` 的 `init()` 函数设置断点
   - 在 `prj_bin/test_stp_debug.cpp` 的关键位置设置断点

2. **启动调试**：
   - 按 `F5` 启动调试
   - 程序会自动停在断点处

3. **调试操作**：
   - `F10` - 单步跳过
   - `F11` - 单步进入
   - `F5` - 继续执行
   - 查看变量值、调用栈等

## ⚠️ 注意事项

1. **确保库文件已拷贝**：
   ```bash
   cd prj_bin
   ./copy_files_to_prj_bin.sh
   ```

2. **如果编译失败**，手动编译一次：
   ```bash
   cd prj_bin
   ./debug_stp.sh compile
   ```

3. **如果还有问题**，可以查看终端输出的错误信息

## 🎉 现在就试试吧！

直接按 `F5`，应该就能正常调试了！
