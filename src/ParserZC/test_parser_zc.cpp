/*!
 * \file test_parser_zc.cpp
 * \project	WonderTrader
 *
 * \author AI Assistant
 * \date 2025/01/17
 * 
 * \brief ParserZC测试程序
 */

#include "ParserZC.h"
#include "../Includes/WTSVariant.hpp"
#include "../Share/TimeUtils.hpp"
#include <iostream>
#include <thread>
#include <chrono>

USING_NS_WTP;

// 测试用的SPI实现
class TestParserSpi : public IParserSpi
{
public:
    TestParserSpi() : m_tickCount(0) {}
    
    virtual void handleSymbols(WTSArray* aySymbols) override
    {
        std::cout << "TestSpi: Received symbols count: " << (aySymbols ? aySymbols->size() : 0) << std::endl;
    }
    
    virtual void handleQuote(WTSTickData* curTick, uint32_t hotFlag) override
    {
        if(curTick)
        {
            m_tickCount++;
            std::cout << "TestSpi: Received tick #" << m_tickCount 
                     << " - " << curTick->code() 
                     << " price=" << curTick->price()
                     << " volume=" << curTick->volumn()
                     << std::endl;
        }
    }
    
    virtual void handleOrderQueue(WTSOrdQueData* curOrdQue) override
    {
        std::cout << "TestSpi: Received order queue data" << std::endl;
    }
    
    virtual void handleOrderDetail(WTSOrdDtlData* curOrdDtl) override
    {
        std::cout << "TestSpi: Received order detail data" << std::endl;
    }
    
    virtual void handleTransaction(WTSTransData* curTrans) override
    {
        std::cout << "TestSpi: Received transaction data" << std::endl;
    }
    
    virtual void handleEvent(WTSParserEvent evt, int32_t ec) override
    {
        const char* eventName = "Unknown";
        switch(evt)
        {
        case WPE_Connect: eventName = "Connect"; break;
        case WPE_Close: eventName = "Close"; break;
        case WPE_Login: eventName = "Login"; break;
        case WPE_Logout: eventName = "Logout"; break;
        }
        std::cout << "TestSpi: Event " << eventName << " (code=" << ec << ")" << std::endl;
    }
    
    virtual IBaseDataMgr* getBaseDataMgr() override
    {
        return nullptr; // 测试中不需要基础数据管理器
    }
    
private:
    int m_tickCount;
};

// 创建测试配置
WTSVariant* createTestConfig()
{
    WTSVariant* config = WTSVariant::createObject();
    
    // 基本连接配置
    config->append("host", WTSVariant::createString("127.0.0.1"));
    config->append("port", WTSVariant::createUInt32(30002));
    
    // 用户认证配置
    config->append("user", WTSVariant::createString("test_user"));
    config->append("pass", WTSVariant::createString("test_pass"));
    
    // 连接模式配置
    config->append("login_mode", WTSVariant::createInt32(0)); // LOGIN_NR
    config->append("async_connect", WTSVariant::createBoolean(false));
    config->append("timeout", WTSVariant::createUInt32(10000));
    
    return config;
}

// 测试基本功能
void testBasicFunctionality()
{
    std::cout << "\n=== Testing Basic Functionality ===" << std::endl;
    
    // 创建解析器
    ParserZC parser;
    TestParserSpi spi;
    
    // 注册SPI
    parser.registerSpi(&spi);
    
    // 创建配置
    WTSVariant* config = createTestConfig();
    
    // 初始化
    std::cout << "Initializing parser..." << std::endl;
    bool initResult = parser.init(config);
    std::cout << "Init result: " << (initResult ? "SUCCESS" : "FAILED") << std::endl;
    
    if(initResult)
    {
        // 测试连接（注意：这里可能会失败，因为没有真实的ZhongChang服务器）
        std::cout << "Testing connection..." << std::endl;
        bool connectResult = parser.connect();
        std::cout << "Connect result: " << (connectResult ? "SUCCESS" : "FAILED") << std::endl;
        
        if(connectResult)
        {
            // 测试订阅
            std::cout << "Testing subscription..." << std::endl;
            CodeSet symbols;
            symbols.insert("600000.SSE"); // 浦发银行
            symbols.insert("000001.SZSE"); // 平安银行
            symbols.insert("cu2301.SHFE"); // 铜期货
            
            parser.subscribe(symbols);
            
            // 等待一段时间接收数据
            std::cout << "Waiting for data..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            
            // 测试取消订阅
            std::cout << "Testing unsubscription..." << std::endl;
            parser.unsubscribe(symbols);
            
            // 断开连接
            std::cout << "Disconnecting..." << std::endl;
            parser.disconnect();
        }
        
        // 释放资源
        std::cout << "Releasing parser..." << std::endl;
        parser.release();
    }
    
    config->release();
    std::cout << "Basic functionality test completed." << std::endl;
}

// 测试数据转换功能
void testDataConversion()
{
    std::cout << "\n=== Testing Data Conversion ===" << std::endl;
    
    ParserZC parser;
    
    // 测试合约代码转换
    std::cout << "Testing instrument code parsing..." << std::endl;
    
    std::string result1 = parser.parseInstrumentCode("SH.600000.last");
    std::cout << "SH.600000.last -> " << result1 << std::endl;
    
    std::string result2 = parser.parseInstrumentCode("SHFE.cu2301.last");
    std::cout << "SHFE.cu2301.last -> " << result2 << std::endl;
    
    // 测试标签名转换
    std::cout << "Testing tag name conversion..." << std::endl;
    
    std::string tag1 = parser.convertToSipTagName("600000.SSE");
    std::cout << "600000.SSE -> " << tag1 << std::endl;
    
    std::string tag2 = parser.convertToSipTagName("cu2301.SHFE");
    std::cout << "cu2301.SHFE -> " << tag2 << std::endl;
    
    // 测试价格转换
    std::cout << "Testing price conversion..." << std::endl;
    
    ZCPriceInfo price1 = parser.convertZCPrice(100000); // 10.0000
    std::cout << "100000 -> " << price1.price << " (valid: " << price1.is_valid << ")" << std::endl;
    
    ZCPriceInfo price2 = parser.convertZCPrice(0xFFFFFFFF); // 无效价格
    std::cout << "0xFFFFFFFF -> " << price2.price << " (valid: " << price2.is_valid << ")" << std::endl;
    
    // 测试时间转换
    std::cout << "Testing time conversion..." << std::endl;
    
    ZCTimeInfo time1 = parser.convertZCTime(20250117, 93000000); // 2025-01-17 09:30:00.000
    std::cout << "20250117, 93000000 -> date=" << time1.action_date 
              << " time=" << time1.action_time 
              << " trading_date=" << time1.trading_date << std::endl;
    
    std::cout << "Data conversion test completed." << std::endl;
}

// 主函数
int main()
{
    std::cout << "ParserZC Test Program" << std::endl;
    std::cout << "=====================" << std::endl;
    
    try
    {
        // 测试数据转换功能
        testDataConversion();
        
        // 测试基本功能（注意：需要真实的ZhongChang服务器才能完全测试）
        testBasicFunctionality();
        
        std::cout << "\nAll tests completed." << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
