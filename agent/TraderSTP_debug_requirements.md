# TraderSTP模块调试需求文档

## 项目概述

**项目名称**: WonderTrader  
**模块名称**: TraderSTP  
**调试目标**: 在prj_bin目录中进行TraderSTP模块的编译和调试

## 环境配置

### 开发环境
- **操作系统**: 支持Windows和Linux
- **编译器**: Windows(MSVC)和Linux(GCC)
- **构建系统**: CMake
- **IDE**: Visual Studio Code
- **C++标准**: C++17

### 目录结构
- **源代码目录**: src/
- **调试目录**: prj_bin/
- **交易接口目录**: traders/
- **配置文件目录**: config/

## 调试需求

1. **编译流程**
   - 使用CMake在src目录下编译TraderSTP模块
   - 生成TraderSTP.dll(Windows)或libTraderSTP.so(Linux)

2. **文件部署**
   - 将编译生成的文件拷贝到prj_bin目录
   - 确保所有依赖库也被正确拷贝
   - 保留配置文件结构

3. **VSCode配置**
   - 配置tasks.json实现自动构建和拷贝
   - 配置launch.json实现在prj_bin目录中调试
   - 支持源代码级调试(断点、变量查看等)

4. **参数定义查找**
   - 定位TraderSTP模块的参数定义位置
   - 了解配置文件中参数的格式和含义
   - 分析参数从配置文件到实际使用的流程

## 技术细节

1. **关键文件**
   - TraderSTP.cpp/h: 主要实现文件
   - tdtraders.yaml: 交易通道配置文件
   - CMakeLists.txt: 构建配置文件

2. **配置文件格式**
   ```yaml
   traders:
   -   active: true
       id: stp_test           # STP交易通道ID
       module: TraderSTP      # 模块文件名
       savedata: true         # 是否保存数据到本地文件
       riskmon:               # 通道风控配置
           active: true       # 是否开启风控
           policy:            # 风控策略
               default:       # 默认策略
                   cancel_stat_timespan: 10    # 撤单流控统计时间窗口
                   cancel_times_boundary: 20   # 时间窗口内最大撤单次数
                   cancel_total_limits: 470    # 单日最大撤单笔数
                   order_stat_timespan: 10     # 下单流控统计时间窗口
                   order_times_boundary: 20    # 时间窗口内最大下单次数
   ```

3. **调试脚本**
   - copy_to_prj_bin.bat/sh: 将编译后文件拷贝到prj_bin目录

## 调试流程

1. **编译TraderSTP模块**
   - 在src目录执行CMake构建
   - 确保编译无错误

2. **拷贝文件到prj_bin**
   - 执行拷贝脚本将文件拷贝到prj_bin目录
   - 确保所有依赖库和配置文件都被正确拷贝

3. **设置断点**
   - 在TraderSTP.cpp中的关键函数处设置断点
   - 特别关注初始化函数和参数解析函数

4. **启动调试**
   - 使用VSCode的调试功能在prj_bin目录中启动程序
   - 观察变量值和程序执行流程

5. **参数分析**
   - 观察配置文件的加载和解析过程
   - 跟踪参数从配置文件到实际使用的完整流程

## 预期结果

1. 成功在prj_bin目录中调试TraderSTP模块
2. 找到参数定义位置并理解其含义和用法
3. 建立高效的编译-拷贝-调试工作流程
4. 能够在VSCode中方便地进行源代码级调试

## 最新需求更新 (2025-06-17)

### 新发现的问题
1. **库文件缺失错误**: 报错 "libTraderSTP.so 未找到，请先编译主项目"
2. **STP API 库位置**: 发现 stptradeapi 的 so 文件位于 `/root/trading_sys/wondertrader/src/API/stp/lib/release/libSTPTradeApi.so`
3. **编译链接问题**: 需要正确配置静态库和动态库的链接路径

### 解决方案需求
1. **完整的文件拷贝脚本**: 能够自动拷贝所有必要的库文件到 prj_bin
2. **编译错误修复**: 解决接口函数签名不匹配和 WTSVariant 创建方法问题
3. **工厂函数使用**: 使用 createTrader/deleteTrader 工厂函数而不是直接实例化
4. **VSCode 调试配置**: 完整的 launch.json 和 tasks.json 配置

### 关键文件路径
- **TraderSTP 库**: `../src/build_all/build_x64/Release/bin/libTraderSTP.so`
- **STP API 库**: `/root/trading_sys/wondertrader/src/API/stp/lib/release/libSTPTradeApi.so`
- **静态库**: `../src/build_all/build_x64/Release/libs/libWTSTools.a`, `libWTSUtils.a`

## 注意事项

1. 确保每次修改代码后都重新执行拷贝脚本
2. 检查所有依赖库是否都已正确拷贝
3. 在Linux上可能需要为脚本和可执行文件添加执行权限
4. 保持配置文件结构与源代码中的一致
5. **重要**: 需要拷贝 STP API 库文件 `libSTPTradeApi.so` 到调试目录