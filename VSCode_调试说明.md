# WonderTrader VSCode 调试快速指南

> 📖 **完整文档**：请参考 [`docs/VSCode_Debug_Setup.md`](docs/VSCode_Debug_Setup.md) 获取详细的调试配置指南

## 🚀 快速开始（30秒上手）

### 1. 一键调试
1. **确保 VSCode 打开的是 `wondertrader` 根目录**
2. **直接按 `F5`**
3. **选择调试配置**：
   - `� 调试 STP 项目` - STP功能开发（推荐新手）
   - `🚀 调试 SIPUI 项目` - 中畅行情解析器

### 2. 程序会自动编译并启动调试！

## 📋 可用调试配置

| 配置名称          | 用途        | 工作目录        | 适用场景              |
| ----------------- | ----------- | --------------- | --------------------- |
| 调试 STP 项目     | STP项目开发 | `project/stp`   | STP功能开发、新手入门 |
| 🚀 调试 SIPUI 项目 | 中畅解析器  | `project/sipui` | 行情解析开发          |

## ⚡ 常用快捷键

- `F5` - 开始调试/继续执行
- `F10` - 单步跳过
- `F11` - 单步进入
- `Shift+F5` - 停止调试
- `Ctrl+Shift+P` → "Tasks: Run Task" - 手动编译

## 🔧 环境准备（首次使用）

### 对于项目调试：
```bash
# STP 项目
cd project/stp/scripts && ./copy_files.sh all

# SIPUI 项目
cd project/sipui && bash scripts/build.sh
```

## 🐛 遇到问题？

### 常见问题快速解决：

1. **找不到库文件**：运行 `cd project/stp/scripts && ./copy_files.sh all`
2. **编译失败**：手动运行 `./debug_stp.sh compile`
3. **调试器无法启动**：确保安装了 GDB (`sudo apt install gdb`)
4. **配置文件找不到**：检查工作目录是否正确

### 需要详细帮助？
👉 查看完整文档：[`docs/VSCode_Debug_Setup.md`](docs/VSCode_Debug_Setup.md)

---

**💡 提示**：第一次使用建议选择 `🚀 调试 STP 项目`，这是推荐的调试环境！
