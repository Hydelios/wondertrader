## 📁 完整目录树结构

```
wondertrader/
├── 📄 LICENSE                          # MIT开源协议
├── 📄 README.md                        # 项目主要说明文档
├── 📄 updatelog.md                     # 版本更新日志
├── 📁 common/                          # 公共配置文件
│   └── 📄 contract_groups.json         # 合约分组配置
├── 📁 docs/                            # 📚 项目文档目录
│   ├── 📄 README.md                    # 文档说明
│   ├── 📄 VSCode_调试完整指南.md        # VSCode调试指南
│   ├── 📄 Configuration_vs_Hardcoding_Analysis.md  # 配置vs硬编码分析
│   ├── 📄 core_modules_overview.md     # 核心模块概览
│   └── 📄 WonderTrader_Complete_Project_Structure.md  # 本文档
├── 📁 images/                          # 🖼️ 项目图片资源
│   ├── 📄 logo_qcode_noad.jpg          # 项目Logo
│   ├── 📄 prod_struture.png            # 生产架构图
│   ├── 📄 backtest.jpg                 # 回测界面图
│   ├── 📄 cta.jpg                      # CTA引擎图
│   ├── 📄 hft.jpg                      # HFT引擎图
│   ├── 📄 risk.jpg                     # 风控界面图
│   ├── 📄 monitor.png                  # 监控界面图
│   ├── 📄 schedule.jpg                 # 调度界面图
│   ├── 📄 m1n.png                      # M+1+N架构图
│   ├── 📄 bt_summary.png               # 回测汇总图
│   ├── 📄 bt_details.png               # 回测详情图
│   └── 📄 bt_signals.png               # 回测信号图
├── 📁 scripts/                         # 🔧 构建和工具脚本
│   ├── 📄 copy_bins_win.py             # Windows二进制文件复制脚本
│   ├── 📄 check_json.sh                # JSON配置检查脚本
│   ├── 📄 switch_project.sh            # 项目切换脚本
│   ├── 📄 test_debug_config.sh         # 调试配置测试脚本
│   ├── 📄 verify_debug_setup.sh        # 调试设置验证脚本
│   └── 📄 Rar.exe                      # 压缩工具
├── 📁 docker/                          # 🐳 Docker容器配置
│   ├── 📄 Dockerfile                   # Docker构建文件
│   ├── 📄 Dockerfile_ubt               # Ubuntu Docker文件
│   └── 📄 mydeps_gcc8.4.0.7z           # GCC依赖包
├── 📁 project/                         # 📋 项目特定配置
│   ├── 📁 sipui/                       # SIP UI项目
│   └── 📁 stp/                         # STP项目
├── 📄 copy_bins_linux.sh               # Linux二进制文件复制脚本
├── 📄 copy_bins_win.bat                # Windows二进制文件复制脚本
├── 📁 dist/                            # 📦 编译后的分发文件
│   ├── 📁 LoaderRunner/                # 合约加载器运行程序
│   │   ├── 📄 LoaderRunner.exe         # 合约加载器可执行文件
│   │   ├── 📄 CTPLoader.dll            # CTP加载器动态库
│   │   ├── 📄 config.ini               # 配置文件
│   │   ├── 📄 map_futopt.ini           # 期权合约映射
│   │   ├── 📄 map_future.ini           # 期货合约映射
│   │   └── 📄 map_stkopt.ini           # 股票期权映射
│   ├── 📁 QuoteFactory/                # 行情工厂程序
│   │   ├── 📄 QuoteFactory.exe         # 行情工厂可执行文件
│   │   ├── 📄 WtDataStorage.dll        # 数据存储动态库
│   │   ├── 📄 dtcfg.yaml               # 数据配置
│   │   ├── 📄 logcfgdt.yaml            # 日志配置
│   │   ├── 📄 mdparsers.yaml           # 行情解析器配置
│   │   ├── 📄 statemonitor.yaml        # 状态监控配置
│   │   └── 📁 parsers/                 # 解析器动态库目录
│   ├── 📁 WtBtRunner/                  # 回测运行程序
│   │   ├── 📄 WtBtRunner.exe           # 回测运行器可执行文件
│   │   ├── 📄 WtCtaStraFact.dll        # CTA策略工厂
│   │   ├── 📄 WtHftStraFact.dll        # HFT策略工厂
│   │   ├── 📄 WtUftStraFact.dll        # UFT策略工厂
│   │   ├── 📄 configbt.yaml            # 回测配置
│   │   ├── 📄 logcfgbt.yaml            # 日志配置
│   │   └── 📄 readme.md                # 使用说明
│   ├── 📁 WtRunnerCta/                 # CTA引擎运行程序
│   │   ├── 📄 WtRunner.exe             # 主运行器
│   │   ├── 📄 WtDataStorage.dll        # 数据存储库
│   │   ├── 📄 WtRiskMonFact.dll        # 风控工厂
│   │   ├── 📄 config.yaml              # 主配置文件
│   │   ├── 📄 actpolicy.yaml           # 行动策略配置
│   │   ├── 📄 executers.yaml           # 执行器配置
│   │   ├── 📄 filters.yaml             # 过滤器配置
│   │   ├── 📄 logcfg.yaml              # 日志配置
│   │   ├── 📄 tdparsers.yaml           # 交易解析器配置
│   │   ├── 📄 tdtraders.yaml           # 交易接口配置
│   │   ├── 📄 readme.md                # 使用说明
│   │   ├── 📁 cta/                     # CTA策略目录
│   │   ├── 📁 executer/                # 执行器目录
│   │   ├── 📁 parsers/                 # 行情解析器动态库
│   │   └── 📁 traders/                 # 交易接口动态库
│   ├── 📁 WtRunnerHft/                 # HFT引擎运行程序
│   │   ├── 📄 WtRunner.exe             # 主运行器
│   │   ├── 📄 WtDataStorage.dll        # 数据存储库
│   │   ├── 📄 config.yaml              # 主配置文件
│   │   ├── 📄 actpolicy.yaml           # 行动策略配置
│   │   ├── 📄 logcfg.yaml              # 日志配置
│   │   ├── 📄 tdparsers.yaml           # 交易解析器配置
│   │   ├── 📄 tdtraders.yaml           # 交易接口配置
│   │   ├── 📄 readme.md                # 使用说明
│   │   ├── 📁 hft/                     # HFT策略目录
│   │   ├── 📁 parsers/                 # 行情解析器动态库
│   │   └── 📁 traders/                 # 交易接口动态库
│   ├── 📁 WtRunnerUft/                 # UFT引擎运行程序
│   │   ├── 📄 WtUftRunner              # UFT运行器可执行文件
│   │   ├── 📄 config.yaml              # 主配置文件
│   │   ├── 📄 actpolicy.yaml           # 行动策略配置
│   │   ├── 📄 logcfg.yaml              # 日志配置
│   │   ├── 📄 mdparsers.yaml           # 行情解析器配置
│   │   ├── 📄 tdparsers.yaml           # 交易解析器配置
│   │   ├── 📄 tdtraders.yaml           # 交易接口配置
│   │   ├── 📁 uft/                     # UFT策略目录
│   │   ├── 📁 parsers/                 # 行情解析器动态库
│   │   └── 📁 traders/                 # 交易接口动态库
│   ├── 📁 common/                      # 公共配置文件
│   │   ├── 📄 commodities.json         # 商品配置
│   │   ├── 📄 contracts.json           # 合约配置
│   │   ├── 📄 fees.json                # 手续费配置
│   │   ├── 📄 fees_stk.json            # 股票手续费配置
│   │   ├── 📄 holidays.json            # 节假日配置
│   │   ├── 📄 hots.json                # 主力合约配置
│   │   ├── 📄 sessions.json            # 交易时段配置
│   │   ├── 📄 stk_comms.json           # 股票商品配置
│   │   └── 📄 stocks.json              # 股票配置
│   └── 📁 storage/                     # 数据存储目录
│       ├── 📁 bin/                     # 二进制数据文件
│       └── 📁 csv/                     # CSV格式数据文件
└── 📁 src/                             # 💻 源代码目录
    ├── 📄 CMakeLists.txt               # 主CMake构建配置
    ├── 📄 README.md                    # 源码说明文档
    ├── 📄 build_debug.sh               # Linux调试构建脚本
    ├── 📄 build_release.sh             # Linux发布构建脚本
    ├── 📄 *.sln                        # Visual Studio解决方案文件
    │   ├── all.sln                     # 完整解决方案
    │   ├── backtest.sln                # 回测解决方案
    │   ├── datakit.sln                 # 数据工具解决方案
    │   ├── parsers.sln                 # 解析器解决方案
    │   ├── product.sln                 # 产品解决方案
    │   ├── tools.sln                   # 工具解决方案
    │   ├── traders.sln                 # 交易器解决方案
    │   └── uft.sln                     # 超高频解决方案
    ├── 📁 API/                         # 🔌 第三方交易API接口
    │   ├── 📁 AresClt/                 # Ares客户端API
    │   ├── 📁 AtpQuantV1.3.6/          # ATP量化API v1.3.6
    │   ├── 📁 AtpTradeApi/             # ATP交易API
    │   ├── 📁 AtpTradeApiMarginV4.1.1/ # ATP融资融券API v4.1.1
    │   ├── 📁 CTP6.3.15/               # CTP API v6.3.15
    │   ├── 📁 CTPMini1.5.8/            # CTPMini API v1.5.8
    │   ├── 📁 CTPOpt3.5.8/             # CTP期权API v3.5.8
    │   ├── 📁 Femas3.02/               # 飞马API v3.02
    │   ├── 📁 FixApi/                  # FIX协议API
    │   ├── 📁 HTS5.2.43.0/             # 华泰证券API v5.2.43.0
    │   ├── 📁 HuaX4.03/                # 华鑫证券API v4.03
    │   ├── 📁 XTP2.2.32.2/             # XTP API v2.2.32.2
    │   ├── 📁 XTPXAlgo/                # XTP算法交易API
    │   ├── 📁 cmaritpdk5.1.20.0/       # 招商证券API v5.1.20.0
    │   ├── 📁 maCliApi3.9/             # 金证期权API v3.9
    │   ├── 📁 oesApi0.17.5.8/          # 宽睿OES API v0.17.5.8
    │   ├── 📁 sipsi2Api/               # SIP SI2 API
    │   ├── 📁 stp/                     # STP API
    │   ├── 📁 yd1.108.360/             # 易达API v1.108.360
    │   └── 📁 zsTradeApi1.6.0/         # 招商证券交易API v1.6.0
    ├── 📁 Common/                      # 🔧 公共组件
    │   ├── 📄 mdump.cpp                # 内存转储实现
    │   └── 📄 mdump.h                  # 内存转储头文件
    ├── 📁 FasterLibs/                  # ⚡ 高性能库
    │   ├── 📁 ankerl/                  # ankerl高性能容器库
    │   └── 📁 tsl/                     # TSL高性能容器库
    ├── 📁 Includes/                    # 📋 头文件定义
    │   ├── 📄 CtaStrategyDefs.h        # CTA策略定义
    │   ├── 📄 ExecuteDefs.h            # 执行器定义
    │   ├── 📄 FasterDefs.h             # 高性能定义
    │   ├── 📄 HftStrategyDefs.h        # HFT策略定义
    │   ├── 📄 IBaseDataMgr.h           # 基础数据管理接口
    │   ├── 📄 IBtDtReader.h            # 回测数据读取接口
    │   ├── 📄 ICtaStraCtx.h            # CTA策略上下文接口
    │   ├── 📄 IDataFactory.h           # 数据工厂接口
    │   ├── 📄 IDataManager.h           # 数据管理接口
    │   ├── 📄 IDataReader.h            # 数据读取接口
    │   ├── 📄 IDataWriter.h            # 数据写入接口
    │   ├── 📄 IExpFactory.h            # 表达式工厂接口
    │   ├── 📄 IHftStraCtx.h            # HFT策略上下文接口
    │   ├── 📄 IHotMgr.h                # 主力合约管理接口
    │   ├── 📄 ILogHandler.h            # 日志处理接口
    │   ├── 📄 IParserApi.h             # 解析器API接口
    │   ├── 📄 IRdmDtReader.h           # 随机数据读取接口
    │   ├── 📄 ISelStraCtx.h            # SEL策略上下文接口
    │   ├── 📄 ISessionMgr.h            # 会话管理接口
    │   ├── 📄 ITraderApi.h             # 交易API接口
    │   ├── 📄 IUftStraCtx.h            # UFT策略上下文接口
    │   ├── 📄 LoaderDef.hpp            # 加载器定义
    │   ├── 📄 RiskMonDefs.h            # 风控监控定义
    │   ├── 📄 SelStrategyDefs.h        # SEL策略定义
    │   ├── 📄 UftStrategyDefs.h        # UFT策略定义
    │   ├── 📄 WTSCollection.hpp        # WTS集合类
    │   ├── 📄 WTSContractInfo.hpp      # 合约信息类
    │   ├── 📄 WTSDataDef.hpp           # 数据定义
    │   ├── 📄 WTSError.hpp             # 错误定义
    │   ├── 📄 WTSExpressData.hpp       # 快速数据类
    │   ├── 📄 WTSMarcos.h              # 宏定义
    │   ├── 📄 WTSObject.hpp            # 基础对象类
    │   ├── 📄 WTSRiskDef.hpp           # 风险定义
    │   ├── 📄 WTSSessionInfo.hpp       # 会话信息类
    │   ├── 📄 WTSStruct.h              # 结构体定义
    │   ├── 📄 WTSSwitchItem.hpp        # 切换项类
    │   ├── 📄 WTSTradeDef.hpp          # 交易定义
    │   ├── 📄 WTSTypes.h               # 类型定义
    │   ├── 📄 WTSVariant.hpp           # 变量类
    │   └── 📄 WTSVersion.h             # 版本定义
    ├── 📁 Share/                       # 🔗 共享工具库
    │   ├── 📄 BoostFile.hpp            # Boost文件操作
    │   ├── 📄 BoostMappingFile.hpp     # Boost内存映射文件
    │   ├── 📄 BoostShm.hpp             # Boost共享内存
    │   ├── 📄 CodeHelper.hpp           # 代码辅助工具
    │   ├── 📄 CpuHelper.hpp            # CPU辅助工具
    │   ├── 📄 DLLHelper.hpp            # 动态库辅助工具
    │   ├── 📄 IniHelper.hpp            # INI文件辅助工具
    │   ├── 📄 ModuleHelper.hpp         # 模块辅助工具
    │   ├── 📄 ObjectPool.hpp           # 对象池
    │   ├── 📄 SpinMutex.hpp            # 自旋锁
    │   ├── 📄 StdUtils.hpp             # 标准工具
    │   ├── 📄 StrUtil.hpp              # 字符串工具
    │   ├── 📄 TimeUtils.hpp            # 时间工具
    │   ├── 📄 WtKVCache.hpp            # 键值缓存
    │   ├── 📄 charconv.hpp             # 字符转换
    │   ├── 📄 cppcli.hpp               # C++命令行接口
    │   ├── 📄 decimal.h                # 十进制数处理
    │   ├── 📄 fmtlib.h                 # 格式化库
    │   ├── 📄 threadpool.hpp           # 线程池
    │   └── 📁 threadpool/              # 线程池实现
    ├── 📁 WTSUtils/                    # 🛠️ 基础工具库
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 SignalHook.hpp           # 信号钩子
    │   ├── 📄 WTSCfgLoader.cpp         # 配置加载器实现
    │   ├── 📄 WTSCfgLoader.h           # 配置加载器头文件
    │   ├── 📄 WTSCmpHelper.hpp         # 压缩辅助工具
    │   ├── 📄 WtLMDB.hpp               # LMDB数据库封装
    │   ├── 📁 StackTracer/             # 堆栈跟踪器
    │   ├── 📁 lmdb/                    # LMDB数据库源码
    │   ├── 📁 yamlcpp/                 # YAML解析库
    │   └── 📁 zstdlib/                 # ZSTD压缩库
    ├── 📁 WTSTools/                    # 🔨 工具库
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 CsvHelper.cpp            # CSV辅助工具实现
    │   ├── 📄 CsvHelper.h              # CSV辅助工具头文件
    │   ├── 📄 WTSBaseDataMgr.cpp       # 基础数据管理实现
    │   ├── 📄 WTSBaseDataMgr.h         # 基础数据管理头文件
    │   ├── 📄 WTSDataFactory.cpp       # 数据工厂实现
    │   ├── 📄 WTSDataFactory.h         # 数据工厂头文件
    │   ├── 📄 WTSHotMgr.cpp            # 主力合约管理实现
    │   ├── 📄 WTSHotMgr.h              # 主力合约管理头文件
    │   ├── 📄 WTSLogger.cpp            # 日志模块实现
    │   └── 📄 WTSLogger.h              # 日志模块头文件
    ├── 📁 WtCore/                      # 🎯 核心交易引擎
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ActionPolicyMgr.cpp      # 行动策略管理器实现
    │   ├── 📄 ActionPolicyMgr.h        # 行动策略管理器头文件
    │   ├── 📄 CtaStraBaseCtx.cpp       # CTA策略基础上下文实现
    │   ├── 📄 CtaStraBaseCtx.h         # CTA策略基础上下文头文件
    │   ├── 📄 CtaStraContext.cpp       # CTA策略上下文实现
    │   ├── 📄 CtaStraContext.h         # CTA策略上下文头文件
    │   ├── 📄 CtaStrategyMgr.cpp       # CTA策略管理器实现
    │   ├── 📄 CtaStrategyMgr.h         # CTA策略管理器头文件
    │   ├── 📄 EventNotifier.cpp        # 事件通知器实现
    │   ├── 📄 EventNotifier.h          # 事件通知器头文件
    │   ├── 📄 HftStraBaseCtx.cpp       # HFT策略基础上下文实现
    │   ├── 📄 HftStraBaseCtx.h         # HFT策略基础上下文头文件
    │   ├── 📄 HftStraContext.cpp       # HFT策略上下文实现
    │   ├── 📄 HftStraContext.h         # HFT策略上下文头文件
    │   ├── 📄 HftStrategyMgr.cpp       # HFT策略管理器实现
    │   ├── 📄 HftStrategyMgr.h         # HFT策略管理器头文件
    │   ├── 📄 IExecCommand.h           # 执行命令接口
    │   ├── 📄 ITrdNotifySink.h         # 交易通知接收器接口
    │   ├── 📄 ParserAdapter.cpp        # 解析器适配器实现
    │   ├── 📄 ParserAdapter.h          # 解析器适配器头文件
    │   ├── 📄 SelStraBaseCtx.cpp       # SEL策略基础上下文实现
    │   ├── 📄 SelStraBaseCtx.h         # SEL策略基础上下文头文件
    │   ├── 📄 SelStraContext.cpp       # SEL策略上下文实现
    │   ├── 📄 SelStraContext.h         # SEL策略上下文头文件
    │   ├── 📄 SelStrategyMgr.cpp       # SEL策略管理器实现
    │   ├── 📄 SelStrategyMgr.h         # SEL策略管理器头文件
    │   ├── 📄 TraderAdapter.cpp        # 交易适配器实现
    │   ├── 📄 TraderAdapter.h          # 交易适配器头文件
    │   ├── 📄 WtArbiExecuter.cpp       # 套利执行器实现
    │   ├── 📄 WtArbiExecuter.h         # 套利执行器头文件
    │   ├── 📄 WtCtaEngine.cpp          # CTA引擎实现
    │   ├── 📄 WtCtaEngine.h            # CTA引擎头文件
    │   ├── 📄 WtCtaTicker.cpp          # CTA时钟实现
    │   ├── 📄 WtCtaTicker.h            # CTA时钟头文件
    │   ├── 📄 WtDiffExecuter.cpp       # 差量执行器实现
    │   ├── 📄 WtDiffExecuter.h         # 差量执行器头文件
    │   ├── 📄 WtDistExecuter.cpp       # 分布式执行器实现
    │   ├── 📄 WtDistExecuter.h         # 分布式执行器头文件
    │   ├── 📄 WtDtMgr.cpp              # 数据管理器实现
    │   ├── 📄 WtDtMgr.h                # 数据管理器头文件
    │   ├── 📄 WtEngine.cpp             # 引擎基类实现
    │   ├── 📄 WtEngine.h               # 引擎基类头文件
    │   ├── 📄 WtExecMgr.cpp            # 执行管理器实现
    │   ├── 📄 WtExecMgr.h              # 执行管理器头文件
    │   ├── 📄 WtExecuterFactory.cpp    # 执行器工厂实现
    │   ├── 📄 WtExecuterFactory.h      # 执行器工厂头文件
    │   ├── 📄 WtFilterMgr.cpp          # 过滤器管理器实现
    │   ├── 📄 WtFilterMgr.h            # 过滤器管理器头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   ├── 📄 WtHelper.h               # 辅助工具头文件
    │   ├── 📄 WtHftEngine.cpp          # HFT引擎实现
    │   ├── 📄 WtHftEngine.h            # HFT引擎头文件
    │   ├── 📄 WtHftTicker.cpp          # HFT时钟实现
    │   ├── 📄 WtHftTicker.h            # HFT时钟头文件
    │   ├── 📄 WtLocalExecuter.cpp      # 本地执行器实现
    │   ├── 📄 WtLocalExecuter.h        # 本地执行器头文件
    │   ├── 📄 WtSelEngine.cpp          # SEL引擎实现
    │   ├── 📄 WtSelEngine.h            # SEL引擎头文件
    │   ├── 📄 WtSelTicker.cpp          # SEL时钟实现
    │   └── 📄 WtSelTicker.h            # SEL时钟头文件
    ├── 📁 WtBtCore/                    # 🔄 回测核心引擎
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 CtaMocker.cpp            # CTA策略模拟器实现
    │   ├── 📄 CtaMocker.h              # CTA策略模拟器头文件
    │   ├── 📄 EventNotifier.cpp        # 事件通知器实现
    │   ├── 📄 EventNotifier.h          # 事件通知器头文件
    │   ├── 📄 ExecMocker.cpp           # 执行模拟器实现
    │   ├── 📄 ExecMocker.h             # 执行模拟器头文件
    │   ├── 📄 HftMocker.cpp            # HFT策略模拟器实现
    │   ├── 📄 HftMocker.h              # HFT策略模拟器头文件
    │   ├── 📄 HisDataMgr.cpp           # 历史数据管理器实现
    │   ├── 📄 HisDataMgr.h             # 历史数据管理器头文件
    │   ├── 📄 HisDataReplayer.cpp      # 历史数据回放器实现
    │   ├── 📄 HisDataReplayer.h        # 历史数据回放器头文件
    │   ├── 📄 MatchEngine.cpp          # 撮合引擎实现
    │   ├── 📄 MatchEngine.h            # 撮合引擎头文件
    │   ├── 📄 SelMocker.cpp            # SEL策略模拟器实现
    │   ├── 📄 SelMocker.h              # SEL策略模拟器头文件
    │   ├── 📄 UftMocker.cpp            # UFT策略模拟器实现
    │   ├── 📄 UftMocker.h              # UFT策略模拟器头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   └── 📄 WtHelper.h               # 辅助工具头文件
    ├── 📁 WtUftCore/                   # ⚡ 超高频核心引擎
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ActionPolicyMgr.cpp      # 行动策略管理器实现
    │   ├── 📄 ActionPolicyMgr.h        # 行动策略管理器头文件
    │   ├── 📄 EventNotifier.cpp        # 事件通知器实现
    │   ├── 📄 EventNotifier.h          # 事件通知器头文件
    │   ├── 📄 ITrdNotifySink.h         # 交易通知接收器接口
    │   ├── 📄 ParserAdapter.cpp        # 解析器适配器实现
    │   ├── 📄 ParserAdapter.h          # 解析器适配器头文件
    │   ├── 📄 ShareManager.cpp         # 共享管理器实现
    │   ├── 📄 ShareManager.h           # 共享管理器头文件
    │   ├── 📄 TraderAdapter.cpp        # 交易适配器实现
    │   ├── 📄 TraderAdapter.h          # 交易适配器头文件
    │   ├── 📄 UftDataDefs.h            # UFT数据定义
    │   ├── 📄 UftStraContext.cpp       # UFT策略上下文实现
    │   ├── 📄 UftStraContext.h         # UFT策略上下文头文件
    │   ├── 📄 UftStrategyMgr.cpp       # UFT策略管理器实现
    │   ├── 📄 UftStrategyMgr.h         # UFT策略管理器头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   ├── 📄 WtHelper.h               # 辅助工具头文件
    │   ├── 📄 WtUftDtMgr.cpp           # UFT数据管理器实现
    │   ├── 📄 WtUftDtMgr.h             # UFT数据管理器头文件
    │   ├── 📄 WtUftEngine.cpp          # UFT引擎实现
    │   ├── 📄 WtUftEngine.h            # UFT引擎头文件
    │   ├── 📄 WtUftTicker.cpp          # UFT时钟实现
    │   └── 📄 WtUftTicker.h            # UFT时钟头文件
    ├── 📁 WtDtCore/                    # 📊 数据核心
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 DataManager.cpp          # 数据管理器实现
    │   ├── 📄 DataManager.h            # 数据管理器头文件
    │   ├── 📄 IDataCaster.h            # 数据广播器接口
    │   ├── 📄 IndexFactory.cpp         # 索引工厂实现
    │   ├── 📄 IndexFactory.h           # 索引工厂头文件
    │   ├── 📄 IndexWorker.cpp          # 索引工作器实现
    │   ├── 📄 IndexWorker.h            # 索引工作器头文件
    │   ├── 📄 ParserAdapter.cpp        # 解析器适配器实现
    │   ├── 📄 ParserAdapter.h          # 解析器适配器头文件
    │   ├── 📄 ShmCaster.cpp            # 共享内存广播器实现
    │   ├── 📄 ShmCaster.h              # 共享内存广播器头文件
    │   ├── 📄 StatHelper.hpp           # 统计辅助工具
    │   ├── 📄 StateMonitor.cpp         # 状态监控器实现
    │   ├── 📄 StateMonitor.h           # 状态监控器头文件
    │   ├── 📄 UDPCaster.cpp            # UDP广播器实现
    │   ├── 📄 UDPCaster.h              # UDP广播器头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   └── 📄 WtHelper.h               # 辅助工具头文件
    ├── 📁 WtDataStorage/               # 💾 标准数据存储引擎
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 DataDefine.h             # 数据定义
    │   ├── 📄 WtBtDtReader.cpp         # 回测数据读取器实现
    │   ├── 📄 WtBtDtReader.h           # 回测数据读取器头文件
    │   ├── 📄 WtDataReader.cpp         # 数据读取器实现
    │   ├── 📄 WtDataReader.h           # 数据读取器头文件
    │   ├── 📄 WtDataWriter.cpp         # 数据写入器实现
    │   ├── 📄 WtDataWriter.h           # 数据写入器头文件
    │   ├── 📄 WtRdmDtReader.cpp        # 随机数据读取器实现
    │   └── 📄 WtRdmDtReader.h          # 随机数据读取器头文件
    ├── 📁 WtDataStorageAD/             # 💾 高级数据存储引擎
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 DataDefineAD.h           # 高级数据定义
    │   ├── 📄 LMDBKeys.h               # LMDB数据库键定义
    │   ├── 📄 WtBtDtReaderAD.cpp       # 高级回测数据读取器实现
    │   ├── 📄 WtBtDtReaderAD.h         # 高级回测数据读取器头文件
    │   ├── 📄 WtDataReaderAD.cpp       # 高级数据读取器实现
    │   ├── 📄 WtDataReaderAD.h         # 高级数据读取器头文件
    │   ├── 📄 WtDataWriterAD.cpp       # 高级数据写入器实现
    │   ├── 📄 WtDataWriterAD.h         # 高级数据写入器头文件
    │   ├── 📄 WtRdmDtReaderAD.cpp      # 高级随机数据读取器实现
    │   └── 📄 WtRdmDtReaderAD.h        # 高级随机数据读取器头文件
    ├── 📁 WtDtHelper/                  # 🔧 数据辅助工具
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtDtHelper.cpp           # 数据辅助工具实现
    │   └── 📄 WtDtHelper.h             # 数据辅助工具头文件
    ├── 📁 WtDtPorter/                  # 🔌 数据接口导出
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ExpDumper.cpp            # 导出转储器实现
    │   ├── 📄 ExpDumper.h              # 导出转储器头文件
    │   ├── 📄 ExpParser.cpp            # 导出解析器实现
    │   ├── 📄 ExpParser.h              # 导出解析器头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 WtDtPorter.cpp           # 数据Porter实现
    │   ├── 📄 WtDtPorter.h             # 数据Porter头文件
    │   ├── 📄 WtDtRunner.cpp           # 数据运行器实现
    │   ├── 📄 WtDtRunner.h             # 数据运行器头文件
    │   └── 📄 copyfiles.bat            # 文件复制脚本
    ├── 📁 WtDtServo/                   # 🌐 数据服务器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserAdapter.cpp        # 解析器适配器实现
    │   ├── 📄 ParserAdapter.h          # 解析器适配器头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 WtDataManager.cpp        # 数据管理器实现
    │   ├── 📄 WtDataManager.h          # 数据管理器头文件
    │   ├── 📄 WtDtRunner.cpp           # 数据运行器实现
    │   ├── 📄 WtDtRunner.h             # 数据运行器头文件
    │   ├── 📄 WtDtServo.cpp            # 数据服务实现
    │   ├── 📄 WtDtServo.h              # 数据服务头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   └── 📄 WtHelper.h               # 辅助工具头文件
    ├── 📁 QuoteFactory/                # 🏭 行情工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 main.cpp                 # 主程序入口
    │   └── 📄 copyfiles.bat            # 文件复制脚本
    ├── 📁 ParserCTP/                   # 📈 CTP期货行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserCTP.cpp            # CTP解析器实现
    │   └── 📄 ParserCTP.h              # CTP解析器头文件
    ├── 📁 ParserCTPMini/               # 📈 CTPMini行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserCTPMini.cpp        # CTPMini解析器实现
    │   └── 📄 ParserCTPMini.h          # CTPMini解析器头文件
    ├── 📁 ParserCTPOpt/                # 📈 CTP期权行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserCTPOpt.cpp         # CTP期权解析器实现
    │   └── 📄 ParserCTPOpt.h           # CTP期权解析器头文件
    ├── 📁 ParserFemas/                 # 📈 飞马期货行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserFemas.cpp          # 飞马解析器实现
    │   └── 📄 ParserFemas.h            # 飞马解析器头文件
    ├── 📁 ParserHuaX/                  # 📈 华鑫证券行情解析器
    │   ├── 📄 ParserHuaX.cpp           # 华鑫解析器实现
    │   └── 📄 ParserHuaX.h             # 华鑫解析器头文件
    ├── 📁 ParserOES/                   # 📈 宽睿OES行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserOES.cpp            # OES解析器实现
    │   └── 📄 ParserOES.h              # OES解析器头文件
    ├── 📁 ParserShm/                   # 📈 共享内存行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserShm.cpp            # 共享内存解析器实现
    │   └── 📄 ParserShm.h              # 共享内存解析器头文件
    ├── 📁 ParserUDP/                   # 📈 UDP行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserUDP.cpp            # UDP解析器实现
    │   └── 📄 ParserUDP.h              # UDP解析器头文件
    ├── 📁 ParserXTP/                   # 📈 XTP股票行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserXTP.cpp            # XTP解析器实现
    │   └── 📄 ParserXTP.h              # XTP解析器头文件
    ├── 📁 ParserXeleSkt/               # 📈 艾克朗科组播行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserXeleSkt.cpp        # 艾克朗科解析器实现
    │   ├── 📄 ParserXeleSkt.h          # 艾克朗科解析器头文件
    │   └── 📄 md_struct.h              # 行情数据结构定义
    ├── 📁 ParserYD/                    # 📈 易达期货行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserYD.cpp             # 易达解析器实现
    │   └── 📄 ParserYD.h               # 易达解析器头文件
    ├── 📁 ParserZC/                    # 📈 中诚期货行情解析器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ParserZC.cpp             # 中诚解析器实现
    │   ├── 📄 ParserZC.h               # 中诚解析器头文件
    │   ├── 📄 ParserZCDef.h            # 中诚解析器定义
    │   ├── 📄 README.md                # 说明文档
    │   ├── 📄 IMPLEMENTATION_SUMMARY.md # 实现总结
    │   └── 📄 test_parser_zc.cpp       # 测试程序
    ├── 📁 TraderCTP/                   # 💼 CTP期货交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderCTP.cpp            # CTP交易接口实现
    │   └── 📄 TraderCTP.h              # CTP交易接口头文件
    ├── 📁 TraderCTPMini/               # 💼 CTPMini交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderCTPMini.cpp        # CTPMini交易接口实现
    │   └── 📄 TraderCTPMini.h          # CTPMini交易接口头文件
    ├── 📁 TraderCTPOpt/                # 💼 CTP期权交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderCTPOpt.cpp         # CTP期权交易接口实现
    │   └── 📄 TraderCTPOpt.h           # CTP期权交易接口头文件
    ├── 📁 TraderFemas/                 # 💼 飞马期货交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderFemas.cpp          # 飞马交易接口实现
    │   └── 📄 TraderFemas.h            # 飞马交易接口头文件
    ├── 📁 TraderATP/                   # 💼 华锐ATP交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderATP.cpp            # ATP交易接口实现
    │   └── 📄 TraderATP.h              # ATP交易接口头文件
    ├── 📁 TraderDD/                    # 💼 DD交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderDD.cpp             # DD交易接口实现
    │   └── 📄 TraderDD.h               # DD交易接口头文件
    ├── 📁 TraderHTS/                   # 💼 华泰证券交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderHTS.cpp            # 华泰交易接口实现
    │   └── 📄 TraderHTS.h              # 华泰交易接口头文件
    ├── 📁 TraderHuaX/                  # 💼 华鑫证券交易接口
    │   ├── 📄 TraderHuaX.cpp           # 华鑫交易接口实现
    │   └── 📄 TraderHuaX.h             # 华鑫交易接口头文件
    ├── 📁 TraderMocker/                # 💼 本地仿真撮合模块
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderMocker.cpp         # 仿真交易接口实现
    │   └── 📄 TraderMocker.h           # 仿真交易接口头文件
    ├── 📁 TraderOES/                   # 💼 宽睿OES交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderOES.cpp            # OES交易接口实现
    │   └── 📄 TraderOES.h              # OES交易接口头文件
    ├── 📁 TraderSTP/                   # 💼 STP交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderSTP.cpp            # STP交易接口实现
    │   └── 📄 TraderSTP.h              # STP交易接口头文件
    ├── 📁 TraderXTP/                   # 💼 XTP股票交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderXTP.cpp            # XTP交易接口实现
    │   └── 📄 TraderXTP.h              # XTP交易接口头文件
    ├── 📁 TraderXTPXAlgo/              # 💼 XTP算法交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderXTPXAlgo.cpp       # XTP算法交易接口实现
    │   └── 📄 TraderXTPXAlgo.h         # XTP算法交易接口头文件
    ├── 📁 TraderYD/                    # 💼 易达期货交易接口
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 TraderYD.cpp             # 易达交易接口实现
    │   └── 📄 TraderYD.h               # 易达交易接口头文件
    ├── 📁 TraderDumper/                # 💼 交易数据转储模块
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 Dumper.cpp               # 转储器实现
    │   ├── 📄 Dumper.h                 # 转储器头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 TraderAdapter.cpp        # 交易适配器实现
    │   ├── 📄 TraderAdapter.h          # 交易适配器头文件
    │   ├── 📄 TraderDumper.cpp         # 交易转储器实现
    │   ├── 📄 TraderDumper.h           # 交易转储器头文件
    │   ├── 📄 WtHelper.cpp             # 辅助工具实现
    │   ├── 📄 WtHelper.h               # 辅助工具头文件
    │   └── 📄 config.yaml              # 配置文件
    ├── 📁 WtPorter/                    # 🔌 主接口导出
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ExpCtaContext.cpp        # CTA上下文导出实现
    │   ├── 📄 ExpCtaContext.h          # CTA上下文导出头文件
    │   ├── 📄 ExpExecuter.cpp          # 执行器导出实现
    │   ├── 📄 ExpExecuter.h            # 执行器导出头文件
    │   ├── 📄 ExpHftContext.cpp        # HFT上下文导出实现
    │   ├── 📄 ExpHftContext.h          # HFT上下文导出头文件
    │   ├── 📄 ExpParser.cpp            # 解析器导出实现
    │   ├── 📄 ExpParser.h              # 解析器导出头文件
    │   ├── 📄 ExpSelContext.cpp        # SEL上下文导出实现
    │   ├── 📄 ExpSelContext.h          # SEL上下文导出头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 WtPorter.cpp             # 主Porter实现
    │   ├── 📄 WtPorter.h               # 主Porter头文件
    │   ├── 📄 WtRtRunner.cpp           # 实时运行器实现
    │   ├── 📄 WtRtRunner.h             # 实时运行器头文件
    │   └── 📄 copyfiles.bat            # 文件复制脚本
    ├── 📁 WtBtPorter/                  # 🔌 回测接口导出
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ExpCtaMocker.cpp         # CTA模拟器导出实现
    │   ├── 📄 ExpCtaMocker.h           # CTA模拟器导出头文件
    │   ├── 📄 ExpHftMocker.cpp         # HFT模拟器导出实现
    │   ├── 📄 ExpHftMocker.h           # HFT模拟器导出头文件
    │   ├── 📄 ExpSelMocker.cpp         # SEL模拟器导出实现
    │   ├── 📄 ExpSelMocker.h           # SEL模拟器导出头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 WtBtPorter.cpp           # 回测Porter实现
    │   ├── 📄 WtBtPorter.h             # 回测Porter头文件
    │   ├── 📄 WtBtRunner.cpp           # 回测运行器实现
    │   └── 📄 WtBtRunner.h             # 回测运行器头文件
    ├── 📁 WtExecMon/                   # 🔍 执行监控
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtExecPorter.cpp         # 执行Porter实现
    │   ├── 📄 WtExecPorter.h           # 执行Porter头文件
    │   ├── 📄 WtExecRunner.cpp         # 执行运行器实现
    │   ├── 📄 WtExecRunner.h           # 执行运行器头文件
    │   ├── 📄 WtSimpDataMgr.cpp        # 简单数据管理器实现
    │   └── 📄 WtSimpDataMgr.h          # 简单数据管理器头文件
    ├── 📁 WtRunner/                    # 🏃‍♂️ 主运行器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtRunner.cpp             # 主运行器实现
    │   ├── 📄 WtRunner.h               # 主运行器头文件
    │   ├── 📄 main.cpp                 # 程序入口
    │   └── 📄 copyfiles.bat            # 文件复制脚本
    ├── 📁 WtBtRunner/                  # 🔄 回测运行器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   └── 📄 WtBtRunner.cpp           # 回测运行器实现
    ├── 📁 WtUftRunner/                 # ⚡ 超高频运行器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtUftRunner.cpp          # UFT运行器实现
    │   ├── 📄 WtUftRunner.h            # UFT运行器头文件
    │   ├── 📄 main.cpp                 # 程序入口
    │   └── 📄 copyfiles.bat            # 文件复制脚本
    ├── 📁 WtExeFact/                   # 🔧 执行器工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtExeFact.cpp            # 执行器工厂实现
    │   ├── 📄 WtExeFact.h              # 执行器工厂头文件
    │   ├── 📄 WtMinImpactExeUnit.cpp   # 最小冲击执行单元实现
    │   ├── 📄 WtMinImpactExeUnit.h     # 最小冲击执行单元头文件
    │   ├── 📄 WtTWapExeUnit.cpp        # TWAP执行单元实现
    │   ├── 📄 WtTWapExeUnit.h          # TWAP执行单元头文件
    │   ├── 📄 WtVWapExeUnit.cpp        # VWAP执行单元实现
    │   ├── 📄 WtVWapExeUnit.h          # VWAP执行单元头文件
    │   ├── 📄 WtDiffMinImpactExeUnit.cpp # 差量最小冲击执行单元实现
    │   ├── 📄 WtDiffMinImpactExeUnit.h # 差量最小冲击执行单元头文件
    │   ├── 📄 WtStockMinImpactExeUnit.cpp # 股票最小冲击执行单元实现
    │   ├── 📄 WtStockMinImpactExeUnit.h # 股票最小冲击执行单元头文件
    │   ├── 📄 WtStockVWapExeUnit.cpp   # 股票VWAP执行单元实现
    │   ├── 📄 WtStockVWapExeUnit.h     # 股票VWAP执行单元头文件
    │   ├── 📄 WtOrdMon.cpp             # 订单监控器实现
    │   ├── 📄 WtOrdMon.h               # 订单监控器头文件
    │   └── 📄 Vwap_name.txt            # VWAP名称配置
    ├── 📁 WtRiskMonFact/               # 🛡️ 风控工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtRiskMonFact.cpp        # 风控工厂实现
    │   ├── 📄 WtRiskMonFact.h          # 风控工厂头文件
    │   ├── 📄 WtSimpRiskMon.cpp        # 简单风控监控器实现
    │   └── 📄 WtSimpRiskMon.h          # 简单风控监控器头文件
    ├── 📁 WtCtaStraFact/               # 🎯 CTA策略工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtCtaStraFact.cpp        # CTA策略工厂实现
    │   ├── 📄 WtCtaStraFact.h          # CTA策略工厂头文件
    │   ├── 📄 WtStraDualThrust.cpp     # DualThrust策略实现
    │   └── 📄 WtStraDualThrust.h       # DualThrust策略头文件
    ├── 📁 WtHftStraFact/               # ⚡ HFT策略工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtHftStraFact.cpp        # HFT策略工厂实现
    │   ├── 📄 WtHftStraFact.h          # HFT策略工厂头文件
    │   ├── 📄 WtHftStraDemo.cpp        # HFT策略演示实现
    │   └── 📄 WtHftStraDemo.h          # HFT策略演示头文件
    ├── 📁 WtSelStraFact/               # 📊 SEL策略工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtSelStraFact.cpp        # SEL策略工厂实现
    │   ├── 📄 WtSelStraFact.h          # SEL策略工厂头文件
    │   ├── 📄 WtStraDtSel.cpp          # 数据选股策略实现
    │   └── 📄 WtStraDtSel.h            # 数据选股策略头文件
    ├── 📁 WtUftStraFact/               # ⚡ UFT策略工厂
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 WtUftStraFact.cpp        # UFT策略工厂实现
    │   ├── 📄 WtUftStraFact.h          # UFT策略工厂头文件
    │   ├── 📄 WtUftStraDemo.cpp        # UFT策略演示实现
    │   └── 📄 WtUftStraDemo.h          # UFT策略演示头文件
    ├── 📁 WtMsgQue/                    # 📡 消息队列
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 MQClient.cpp             # 消息队列客户端实现
    │   ├── 📄 MQClient.h               # 消息队列客户端头文件
    │   ├── 📄 MQManager.cpp            # 消息队列管理器实现
    │   ├── 📄 MQManager.h              # 消息队列管理器头文件
    │   ├── 📄 MQServer.cpp             # 消息队列服务器实现
    │   ├── 📄 MQServer.h               # 消息队列服务器头文件
    │   ├── 📄 PorterDefs.h             # Porter定义
    │   ├── 📄 WtMsgQue.cpp             # 消息队列实现
    │   └── 📄 WtMsgQue.h               # 消息队列头文件
    ├── 📁 WtShareHelper/               # 🔗 共享内存辅助
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 ShareBlocks.cpp          # 共享内存块实现
    │   ├── 📄 ShareBlocks.h            # 共享内存块头文件
    │   ├── 📄 WtShareHelper.cpp        # 共享内存辅助实现
    │   └── 📄 WtShareHelper.h          # 共享内存辅助头文件
    ├── 📁 WtLatencyHFT/                # 📊 HFT延迟测试工具
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 HftLatencyTool.cpp       # HFT延迟工具实现
    │   ├── 📄 HftLatencyTool.h         # HFT延迟工具头文件
    │   └── 📄 main.cpp                 # 程序入口
    ├── 📁 WtLatencyUFT/                # 📊 UFT延迟测试工具
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 UftLatencyTool.cpp       # UFT延迟工具实现
    │   ├── 📄 UftLatencyTool.h         # UFT延迟工具头文件
    │   └── 📄 main.cpp                 # 程序入口
    ├── 📁 CTPLoader/                   # 📥 CTP合约加载器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 CTPLoader.cpp            # CTP加载器实现
    │   ├── 📄 TraderSpi.cpp            # 交易SPI实现
    │   └── 📄 TraderSpi.h              # 交易SPI头文件
    ├── 📁 CTPOptLoader/                # 📥 CTP期权合约加载器
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   ├── 📄 CTPOptLoader.cpp         # CTP期权加载器实现
    │   ├── 📄 TraderSpi.cpp            # 交易SPI实现
    │   └── 📄 TraderSpi.h              # 交易SPI头文件
    ├── 📁 LoaderRunner/                # 🏃‍♂️ 加载器运行程序
    │   ├── 📄 CMakeLists.txt           # CMake配置
    │   └── 📄 LoaderRunner.cpp         # 加载器运行器实现
    └── 📁 TestXXX/                     # 🧪 测试程序系列
        ├── 📁 TestBtPorter/            # 回测接口测试
        ├── 📁 TestDtPorter/            # 数据接口测试
        ├── 📁 TestExecPorter/          # 执行接口测试
        ├── 📁 TestPorter/              # 主接口测试
        ├── 📁 TestTrader/              # 交易接口测试
        ├── 📁 TestTraderSTP/           # STP交易接口测试
        ├── 📁 TestParser/              # 解析器测试
        └── 📁 TestUnits/               # 单元测试（基于gtest）
            ├── 📄 CMakeLists.txt       # CMake配置
            ├── 📄 main.cpp             # 测试主程序
            ├── 📄 test_codehelper.cpp  # 代码辅助测试
            ├── 📄 test_fastestmap.cpp  # 高速映射测试
            ├── 📄 test_fmt.cpp         # 格式化测试
            ├── 📄 test_kvcache.cpp     # 键值缓存测试
            ├── 📄 test_lmdb.cpp        # LMDB测试
            ├── 📄 test_object_pool.cpp # 对象池测试
            ├── 📄 test_session.cpp     # 会话测试
            ├── 📄 test_shm.cpp         # 共享内存测试
            ├── 📄 test_utils.cpp       # 工具测试
            └── 📁 gtest/               # Google Test框架