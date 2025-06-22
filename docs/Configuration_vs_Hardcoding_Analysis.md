# WonderTrader 配置vs硬编码问题分析与解决方案

## 🔍 问题概述

WonderTrader项目虽然有完善的配置文件体系，但在代码中仍存在大量硬编码的合约代码，这违背了良好的配置管理实践。

## 📋 硬编码问题汇总

### 1. 测试代码中的硬编码

**问题文件**: `project/sipui/src/test_parser_zc.cpp`
```cpp
// 硬编码的合约订阅
codes.insert("SHFE.cu2412");  // 沪铜主力
codes.insert("SHFE.au2412");  // 沪金主力
codes.insert("DCE.i2405");    // 铁矿石主力
codes.insert("CZCE.MA405");   // 甲醇主力
codes.insert("CFFEX.IF2412"); // 沪深300股指期货主力
```

**问题**: 合约代码直接写在源代码中，难以维护和更新

### 2. 配置文件中的硬编码

**问题文件**: `project/stp/executers.yaml`
```yaml
excludes:           #排除列表
- CFFEX.IF
- CFFEX.IC
includes:           #包含列表  
- SHFE.rb
```

**问题**: 品种代码硬编码在配置文件中，缺乏灵活性

### 3. 策略配置中的硬编码

**问题文件**: `project/stp/config.yaml`
```yaml
params:
    code: CFFEX.rb.HOT  # 硬编码的合约代码
```

**问题**: 策略参数中直接指定合约代码，不便于批量管理

## 🎯 配置化解决方案

### 方案1: 创建合约组配置文件

#### 1.1 创建合约组定义文件
**文件**: `common/contract_groups.json`
```json
{
    "test_contracts": {
        "description": "测试用合约组",
        "contracts": [
            "SHFE.cu.HOT",
            "SHFE.au.HOT", 
            "DCE.i.HOT",
            "CZCE.MA.HOT",
            "CFFEX.IF.HOT"
        ]
    },
    "main_futures": {
        "description": "主要期货品种",
        "contracts": [
            "SHFE.cu.HOT",
            "SHFE.rb.HOT",
            "SHFE.au.HOT",
            "DCE.i.HOT",
            "DCE.j.HOT",
            "CZCE.MA.HOT",
            "CZCE.CF.HOT",
            "CFFEX.IF.HOT",
            "CFFEX.IC.HOT"
        ]
    },
    "stock_index": {
        "description": "股指期货",
        "contracts": [
            "CFFEX.IF.HOT",
            "CFFEX.IC.HOT",
            "CFFEX.IH.HOT"
        ]
    }
}
```

#### 1.2 修改测试代码使用配置
**修改**: `project/sipui/src/test_parser_zc.cpp`
```cpp
// 从配置文件读取合约组
WTSVariant* contractGroups = WTSCfgLoader::load_from_file("../common/contract_groups.json");
WTSVariant* testContracts = contractGroups->get("test_contracts");
WTSVariant* contracts = testContracts->get("contracts");

CodeSet codes;
for(uint32_t i = 0; i < contracts->size(); i++)
{
    std::string contract = contracts->get(i)->asCString();
    codes.insert(contract);
    std::cout << "订阅合约: " << contract << std::endl;
}
```

### 方案2: 增强现有配置文件

#### 2.1 修改解析器配置
**文件**: `project/sipui/config/config.yaml`
```yaml
parsers:
- active: true
  id: zc_parser
  module: ParserZC
  host: "60.12.4.70"
  port: 30002
  user: "your_username"
  pass: "your_password"
  mode: 0
  
  # 使用合约组配置
  contract_groups:
    - "test_contracts"
    - "main_futures"
  
  # 或者直接配置合约列表
  codes:
    - "SHFE.cu.HOT"
    - "SHFE.au.HOT"
    - "DCE.i.HOT"
    - "CZCE.MA.HOT"
    - "CFFEX.IF.HOT"
```

#### 2.2 修改执行器配置
**文件**: `project/stp/executers.yaml`
```yaml
executers:
-   active: false
    id: exec
    trader: simnow
    scale: 1
    
    policy:
        default:
            name: WtExeFact.WtMinImpactExeUnit
            # ... 其他配置
    
    clear:
        active: false
        # 使用合约组而不是硬编码
        exclude_groups:
            - "stock_index"
        include_groups:
            - "main_futures"
        # 或者保持原有方式但从配置文件读取
        excludes_from_config: "common/exclude_contracts.json"
        includes_from_config: "common/include_contracts.json"
```

### 方案3: 动态合约管理

#### 3.1 创建合约管理器类
```cpp
class ContractManager {
public:
    bool loadContractGroups(const char* configFile);
    std::vector<std::string> getContractGroup(const char* groupName);
    std::vector<std::string> getActiveContracts(const char* pattern);
    bool isContractActive(const char* contract);
    
private:
    std::map<std::string, std::vector<std::string>> m_contractGroups;
    std::map<std::string, bool> m_activeContracts;
};
```

#### 3.2 集成到现有框架
```cpp
// 在策略初始化时使用
void Strategy::onInit() {
    ContractManager* contractMgr = getContractManager();
    auto contracts = contractMgr->getContractGroup("test_contracts");
    
    for(const auto& contract : contracts) {
        subscribeContract(contract.c_str());
    }
}
```

## 🔧 实施建议

### 阶段1: 立即改进（低风险）
1. **修改测试代码**: 将硬编码的合约列表移到配置文件
2. **创建合约组配置**: 建立 `contract_groups.json` 文件
3. **更新文档**: 说明新的配置方式

### 阶段2: 中期改进（中等风险）
1. **增强配置解析**: 修改配置加载逻辑支持合约组
2. **重构执行器配置**: 支持从配置文件读取包含/排除列表
3. **添加验证机制**: 确保配置的合约代码有效

### 阶段3: 长期改进（高收益）
1. **实现动态合约管理**: 支持运行时更新合约配置
2. **添加合约生命周期管理**: 自动处理合约到期和主力切换
3. **集成到监控系统**: 提供合约配置的可视化管理界面

## 📊 收益分析

### 配置化的优势
- ✅ **易于维护**: 合约变更只需修改配置文件
- ✅ **环境隔离**: 不同环境可使用不同的合约配置
- ✅ **批量管理**: 支持合约组的批量操作
- ✅ **版本控制**: 配置变更可追踪和回滚
- ✅ **降低错误**: 减少因硬编码导致的错误

### 实施成本
- 🔧 **开发成本**: 中等（需要修改配置加载逻辑）
- 🔧 **测试成本**: 低（主要是配置验证）
- 🔧 **维护成本**: 低（配置化后维护更简单）

## 🎯 推荐行动

1. **立即行动**: 修改 `test_parser_zc.cpp` 使用配置文件
2. **短期目标**: 创建合约组配置体系
3. **长期目标**: 实现完整的动态合约管理系统

---

**作者**: AI Assistant  
**日期**: 2025-06-22  
**版本**: 1.0
