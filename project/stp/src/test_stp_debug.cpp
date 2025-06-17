/**
 * @file test_stp_debug.cpp
 * @brief TraderSTP 调试测试程序
 * @author Hydelios
 * @date 2025-06-17
 */

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

// 包含必要的头文件
#include "WTSVariant.hpp"
#include "ITraderApi.h"

// 使用命名空间
using namespace wtp;

// 声明工厂函数
extern "C" {
    ITraderApi* createTrader();
    void deleteTrader(ITraderApi*& trader);
}

// 测试用的交易回调类
class TestTraderSpi : public ITraderSpi
{
public:
    TestTraderSpi() = default;
    virtual ~TestTraderSpi() = default;

    // 实现必要的回调接口
    virtual void handleEvent(WTSTraderEvent evt, int32_t ec) override {
        std::cout << "[事件回调] 事件类型: " << evt << ", 错误码: " << ec << std::endl;
    }

    virtual void handleTraderLog(WTSLogLevel ll, const char* message) override {
        std::cout << "[日志回调] 级别: " << ll << ", 消息: " << message << std::endl;
    }

    virtual void onLoginResult(bool bSucc, const char* msg, uint32_t tradingdate) override {
        std::cout << "[登录结果] 成功: " << (bSucc ? "是" : "否") 
                  << ", 消息: " << (msg ? msg : "无") 
                  << ", 交易日: " << tradingdate << std::endl;
    }

    virtual void onLogout() override {
        std::cout << "[登出回调] 已登出" << std::endl;
    }

    virtual IBaseDataMgr* getBaseDataMgr() override {
        return nullptr; // 简化测试，返回空指针
    }

    // 其他必要的虚函数实现（简化版本）
    virtual void onRspEntrust(WTSEntrust* entrust, WTSError* err) override {}
    virtual void onRspAccount(WTSArray* ayAccounts) override {}
    virtual void onRspPosition(const WTSArray* ayPositions) override {}
    virtual void onRspOrders(const WTSArray* ayOrders) override {}
    virtual void onRspTrades(const WTSArray* ayTrades) override {}
    virtual void onPushOrder(WTSOrderInfo* orderInfo) override {}
    virtual void onPushTrade(WTSTradeInfo* tradeRecord) override {}
    virtual void onTraderError(WTSError* err, void* pData = NULL) override {}
};

// 创建测试参数
WTSVariant* createTestParams() {
    WTSVariant* params = WTSVariant::createObject();

    // 设置基本参数
    params->append("broker", "STP_TEST_BROKER");
    params->append("user", "test_user");
    params->append("pass", "test_pass");

    // 设置前置机地址（支持多个）
    WTSVariant* frontArray = WTSVariant::createArray();
    frontArray->append("tcp://127.0.0.1:9999");
    frontArray->append("tcp://127.0.0.1:9998");
    params->append("front", frontArray);

    // 设置可选参数
    params->append("flowdir", "STPTDFlow_Debug");
    params->append("stpmodule", "stptradeapi");

    return params;
}

// 测试参数解析
void testParameterParsing() {
    std::cout << "\n=== 测试参数解析 ===" << std::endl;

    // 创建 TraderSTP 实例
    ITraderApi* trader = createTrader();
    if (!trader) {
        std::cout << "创建 TraderSTP 实例失败" << std::endl;
        return;
    }

    // 创建测试参数
    WTSVariant* params = createTestParams();

    // 测试初始化
    bool initResult = trader->init(params);
    std::cout << "初始化结果: " << (initResult ? "成功" : "失败") << std::endl;

    // 释放参数对象
    params->release();

    // 释放交易器实例
    deleteTrader(trader);

    std::cout << "参数解析测试完成" << std::endl;
}

// 测试连接功能
void testConnection() {
    std::cout << "\n=== 测试连接功能 ===" << std::endl;

    // 创建 TraderSTP 实例
    ITraderApi* trader = createTrader();
    if (!trader) {
        std::cout << "创建 TraderSTP 实例失败" << std::endl;
        return;
    }

    // 创建回调处理器
    std::unique_ptr<TestTraderSpi> spi(new TestTraderSpi());
    trader->registerSpi(spi.get());

    // 创建测试参数并初始化
    WTSVariant* params = createTestParams();
    trader->init(params);
    params->release();

    // 测试连接
    std::cout << "开始连接..." << std::endl;
    trader->connect();

    // 检查连接状态
    std::this_thread::sleep_for(std::chrono::seconds(2));
    bool connected = trader->isConnected();
    std::cout << "连接状态: " << (connected ? "已连接" : "未连接") << std::endl;

    // 断开连接
    trader->disconnect();

    // 释放交易器实例
    deleteTrader(trader);

    std::cout << "连接测试完成" << std::endl;
}

// 主函数
int main() {
    std::cout << "TraderSTP 调试测试程序启动" << std::endl;
    std::cout << "作者: Hydelios" << std::endl;
    std::cout << "日期: 2025-06-17" << std::endl;
    
    int choice = 0;
    while (true) {
        std::cout << "\n请选择测试项目:" << std::endl;
        std::cout << "1. 测试参数解析" << std::endl;
        std::cout << "2. 测试连接功能" << std::endl;
        std::cout << "0. 退出程序" << std::endl;
        std::cout << "请输入选择: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                testParameterParsing();
                break;
            case 2:
                testConnection();
                break;
            case 0:
                std::cout << "程序退出" << std::endl;
                return 0;
            default:
                std::cout << "无效选择，请重试" << std::endl;
                break;
        }
    }
    
    return 0;
}
