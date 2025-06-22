# ParserZC - 中畅行情解析器

## 概述

ParserZC是基于sipsi2Api实现的中畅行情数据解析器，支持多种连接模式和数据类型的解析。

## 功能特性

### 支持的连接模式
- TCP普通模式 (LOGIN_NR)
- TCP LNK模式 (LOGIN_LNK) 
- PGM组播模式 (LOGIN_PGM)
- Multicast模式 (LOGIN_MCB)

### 支持的数据类型
- **股票数据**
  - L1快照数据 (上海/深圳)
  - L2快照数据 (上海/深圳) - 待实现
  - 逐笔成交数据
  - 委托队列数据

- **期货数据**
  - 中金所行情快照
  - 郑商所行情快照
  - 大商所行情快照
  - 上期所行情快照

- **指数数据**
  - 上证指数快照
  - 深证指数快照
  - 中证指数快照

- **期权数据**
  - 上交所期权行情快照
  - 深交所期权行情快照

- **港股数据**
  - 港股L1/L2快照数据

## 配置说明

### 基本配置参数

```json
{
    "host": "服务器IP地址",
    "port": 30002,
    "user": "用户名",
    "pass": "密码",
    "login_mode": 0,
    "async_connect": false,
    "timeout": 10000
}
```

### 配置参数说明

- `host`: ZhongChang服务器IP地址
- `port`: 服务器端口，默认30002
- `user`: 用户名
- `pass`: 密码
- `login_mode`: 登录模式
  - 0: LOGIN_NR (TCP普通模式)
  - 1: LOGIN_LNK (TCP LNK模式)
  - 2: LOGIN_PGM (PGM组播模式)
  - 3: LOGIN_MCB (Multicast模式)
- `async_connect`: 是否异步连接，默认false
- `timeout`: 连接超时时间(毫秒)，默认10000

### 代理配置（可选）

```json
{
    "proxy_type": 0,
    "proxy_ip": "代理服务器IP",
    "proxy_port": 8080,
    "proxy_user": "代理用户名",
    "proxy_pass": "代理密码"
}
```

## 使用示例

### C++代码示例

```cpp
#include "ParserZC.h"

// 创建解析器
ParserZC* parser = new ParserZC();

// 注册SPI回调
parser->registerSpi(yourSpiInstance);

// 创建配置
WTSVariant* config = WTSVariant::createObject();
config->append("host", WTSVariant::createString("127.0.0.1"));
config->append("port", WTSVariant::createUInt32(30002));
config->append("user", WTSVariant::createString("your_user"));
config->append("pass", WTSVariant::createString("your_pass"));

// 初始化
bool success = parser->init(config);
if(success) {
    // 连接
    if(parser->connect()) {
        // 订阅合约
        CodeSet symbols;
        symbols.insert("600000.SSE"); // 浦发银行
        symbols.insert("cu2301.SHFE"); // 铜期货
        parser->subscribe(symbols);
        
        // ... 处理数据 ...
        
        // 取消订阅
        parser->unsubscribe(symbols);
        
        // 断开连接
        parser->disconnect();
    }
    
    // 释放资源
    parser->release();
}

delete parser;
config->release();
```

## 合约代码格式

### WonderTrader标准格式
- 股票: `代码.交易所` (如: `600000.SSE`, `000001.SZSE`)
- 期货: `代码.交易所` (如: `cu2301.SHFE`, `IF2301.CFFEX`)
- 期权: `代码.交易所` (如: `10003720.SSE`)

### sipsi2标签格式
- 格式: `交易所.代码.字段` (如: `SH.600000.*`, `SHFE.cu2301.*`)
- 支持通配符订阅所有字段

## 编译说明

### 依赖项
- C++11或更高版本
- sipsi2Api库
- WonderTrader基础库
- Boost库 (Linux)

### 编译步骤

```bash
# 创建构建目录
mkdir build && cd build

# 配置CMake
cmake ..

# 编译
make -j4

# 安装
make install
```

### Windows编译
使用Visual Studio 2017或更高版本，打开CMake项目进行编译。

## 测试

### 运行测试程序

```bash
# 编译测试程序
cmake -DBUILD_PARSER_ZC_TESTS=ON ..
make test_parser_zc

# 运行测试
./bin/tests/test_parser_zc
```

### 测试内容
- 基本功能测试
- 数据转换测试
- 连接和订阅测试

## 故障排除

### 常见问题

1. **连接失败**
   - 检查服务器地址和端口
   - 验证用户名和密码
   - 确认网络连通性

2. **编译错误**
   - 检查sipsi2Api库是否正确安装
   - 验证依赖库路径配置
   - 确认C++编译器版本

3. **数据接收异常**
   - 检查合约代码格式
   - 验证订阅权限
   - 查看错误日志

### 日志级别
- DEBUG: 详细调试信息
- INFO: 一般信息
- WARN: 警告信息
- ERROR: 错误信息

## 版本历史

### v1.0.0 (2025-01-17)
- 初始版本
- 支持基本的股票L1数据解析
- 支持期货数据解析
- 实现连接和订阅管理
- 完善错误处理和日志记录

## 许可证

本项目遵循WonderTrader项目的许可证条款。

## 联系方式

如有问题或建议，请联系WonderTrader开发团队。
