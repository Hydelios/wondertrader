# TraderSTP 参数定义文档

## 📋 概述

本文档详细说明了 TraderSTP 模块的所有参数定义位置、类型和用途，帮助开发者进行调试和配置。

## 🔍 参数定义位置

### 1. 初始化参数 (init 函数)

**文件位置**: `src/TraderSTP/TraderSTP.cpp` 第 75-122 行

```cpp
bool TraderSTP::init(WTSVariant* params)
```

#### 必需参数

| 参数名 | 类型 | 说明 | 示例值 |
|--------|------|------|--------|
| `front` | String/Array | STP前置机地址，支持单个或多个 | `"tcp://127.0.0.1:9999"` |
| `broker` | String | 券商代码 | `"STP_BROKER"` |
| `user` | String | 用户名 | `"your_username"` |
| `pass` | String | 密码 | `"your_password"` |

#### 可选参数

| 参数名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| `flowdir` | String | `"STPTDFlow"` | 数据流存储目录 |
| `stpmodule` | String | `"stptradeapi"` | STP模块名称 |

### 2. 类成员变量定义

**文件位置**: `src/TraderSTP/TraderSTP.h` 第 142-192 行

```cpp
protected:
    std::string m_strBroker;        // 券商代码
    std::vector<std::string> m_strFront;  // 前置机地址列表
    std::string m_strUser;          // 用户名
    std::string m_strPass;          // 密码
    std::string m_strFlowDir;       // 流文件目录
    std::string m_strModule;        // STP模块路径
    // ... 其他成员变量
```

## 🛠️ 参数解析逻辑

### 前置机地址解析

```cpp
auto fontItem = params->get("front");
if (fontItem)
{
    if (fontItem->type() == WTSVariant::VT_String)
    {
        // 单个前置机地址
        m_strFront.push_back(fontItem->asCString());
    }
    else if (fontItem->type() == WTSVariant::VT_Array)
    {
        // 多个前置机地址
        for (uint32_t i = 0; i < fontItem->size(); i++)
        {
            m_strFront.push_back(fontItem->get(i)->asCString());
        }
    }
}
```

### 模块路径构建

```cpp
std::string module = params->getCString("stpmodule");
if (module.empty())
    module = "stptradeapi";

m_strModule = getBinDir() + DLLHelper::wrap_module(module.c_str(), "");
```

## 📝 配置文件示例

### YAML 配置格式

```yaml
traders:
-   active: true
    id: stp_test
    module: TraderSTP
    
    # STP 特有参数
    front: 
        - "tcp://127.0.0.1:9999"
        - "tcp://127.0.0.1:9998"
    broker: "STP_BROKER"
    user: "your_username"
    pass: "your_password"
    stpmodule: "stptradeapi"
    flowdir: "STPTDFlow"
```

### 代码中的参数创建

```cpp
WTSVariant* createParams() {
    WTSVariant* params = WTSVariant::createObject();
    
    params->append("broker", WTSVariant::createString("STP_BROKER"));
    params->append("user", WTSVariant::createString("username"));
    params->append("pass", WTSVariant::createString("password"));
    
    // 多个前置机地址
    WTSVariant* frontArray = WTSVariant::createArray();
    frontArray->append(WTSVariant::createString("tcp://127.0.0.1:9999"));
    frontArray->append(WTSVariant::createString("tcp://127.0.0.1:9998"));
    params->append("front", frontArray);
    
    return params;
}
```

## 🔧 调试要点

### 1. 参数验证

在 `init` 函数中添加参数验证：

```cpp
// 验证必需参数
if (m_strBroker.empty()) {
    write_log(m_sink, LL_ERROR, "broker 参数不能为空");
    return false;
}

if (m_strUser.empty()) {
    write_log(m_sink, LL_ERROR, "user 参数不能为空");
    return false;
}
```

### 2. 断点设置建议

- `TraderSTP::init()` 函数入口
- 参数解析完成后 (第 122 行)
- `TraderSTP::connect()` 函数入口
- `TraderSTP::doLogin()` 函数入口

### 3. 变量观察

在调试时重点观察以下变量：

- `m_strBroker` - 券商代码
- `m_strFront` - 前置机地址列表
- `m_strUser` - 用户名
- `m_strModule` - 模块路径
- `m_wrapperState` - 连接状态

## 🚀 快速调试步骤

1. **编译项目**
   ```bash
   cd prj_bin
   ./debug_stp.sh compile
   ```

2. **运行测试**
   ```bash
   ./debug_stp.sh test
   ```

3. **开始调试**
   ```bash
   ./debug_stp.sh debug
   ```

## 📚 相关文件

- **头文件**: `src/TraderSTP/TraderSTP.h`
- **实现文件**: `src/TraderSTP/TraderSTP.cpp`
- **测试文件**: `src/TestTraderSTP/main.cpp`
- **配置示例**: `prj_bin/stp_config.yaml`
- **调试程序**: `prj_bin/test_stp_debug.cpp`

## ⚠️ 注意事项

1. 确保 STP 动态库 (`stptradeapi.so`) 在正确的路径下
2. 前置机地址格式必须为 `tcp://ip:port`
3. 流文件目录会自动创建，确保有写权限
4. 调试时注意观察日志输出，特别是错误信息

---

**作者**: Hydelios  
**日期**: 2025-06-17  
**版本**: 1.0
