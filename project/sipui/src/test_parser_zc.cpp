/*!
 * \file test_parser_zc.cpp
 * \project	WonderTrader
 *
 * \author AI Assistant
 * \date 2025/01/17
 *
 * \brief ParserZC模块测试程序
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <signal.h>
#include <atomic>

#include "ParserZC/ParserZC.h"
#include "WTSTools/WTSLogger.h"
#include "Includes/WTSDataDef.hpp"
#include "Includes/WTSVariant.hpp"
#include "Includes/IParserApi.h"
#include "WTSUtils/WTSCfgLoader.h"

// 导入工厂函数
extern "C"
{
    IParserApi *createParser();
    void deleteParser(IParserApi *&parser);
}

USING_NS_WTP;

// 全局停止标志
std::atomic<bool> g_bStopped{false};

// 信号处理函数
void signal_handler(int signal)
{
    std::cout << "\n收到信号 " << signal << "，正在退出..." << std::endl;
    g_bStopped = true;
}

/*!
 * \brief 测试用的Parser回调接口实现
 */
class TestParserSpi : public IParserSpi
{
private:
    std::atomic<uint64_t> m_uTickCount{0};
    std::atomic<uint64_t> m_uLastTickTime{0};
    uint64_t m_uStartTime;

public:
    TestParserSpi()
    {
        m_uStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
    }

    virtual ~TestParserSpi() = default;

    // 行情数据回调
    virtual void handleQuote(WTSTickData *curTick, uint32_t procFlag) override
    {
        if (curTick == nullptr)
            return;

        m_uTickCount++;
        uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
        m_uLastTickTime = now;

        // 每100条打印一次统计信息
        if (m_uTickCount % 100 == 0)
        {
            uint64_t elapsed = now - m_uStartTime;
            double avgRate = elapsed > 0 ? (double)m_uTickCount * 1000.0 / elapsed : 0.0;

            WTSLogger::info("统计信息 - 总tick数: {}, 平均速率: {:.2f} tick/s, 最新: {} 价格: {}",
                            m_uTickCount.load(), avgRate, curTick->code(), curTick->price());
        }
        else
        {
            // 详细打印前10条数据
            if (m_uTickCount <= 10)
            {
                WTSLogger::info("收到第{}条行情: {} 最新价: {} 时间: {} 成交量: {}",
                                m_uTickCount.load(),
                                curTick->code(),
                                curTick->price(),
                                curTick->actiontime(),
                                curTick->volume());
            }
        }
    }

    virtual void handleOrderQueue(WTSOrdQueData *curOrdQue) override {}
    virtual void handleOrderDetail(WTSOrdDtlData *curOrdDtl) override {}
    virtual void handleTransaction(WTSTransData *curTrans) override {}

    virtual void handleParserLog(WTSLogLevel ll, const char *message) override
    {
        WTSLogger::log_raw(ll, message);
    }

    virtual void handleEvent(WTSParserEvent pe, int32_t ec) override
    {
        if (pe == WPE_Connect)
        {
            WTSLogger::info("=== Parser连接成功 ===");
            std::cout << "✅ 中畅行情连接建立成功！" << std::endl;
        }
        else if (pe == WPE_Close)
        {
            WTSLogger::warn("=== Parser连接断开 ===");
            std::cout << "❌ 中畅行情连接断开！" << std::endl;
        }
    }

    virtual void handleSymbolList(const WTSArray *aySymbols) override
    {
        WTSLogger::info("=== 收到合约列表 ===");
        if (aySymbols)
        {
            std::cout << "📋 收到合约列表，共 " << aySymbols->size() << " 个合约" << std::endl;
        }
    }

    virtual IBaseDataMgr *getBaseDataMgr() override { return nullptr; }

    // 获取统计信息
    uint64_t getTickCount() const { return m_uTickCount.load(); }
    uint64_t getLastTickTime() const { return m_uLastTickTime.load(); }
};

int main(int argc, char *argv[])
{
    // 注册信号处理
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "ParserZC 中畅行情解析器测试程序" << std::endl;

    try
    {
        WTSLogger::init("config/logcfg.yaml", true);
        WTSLogger::info("ParserZC测试程序启动");

        // 创建ParserZC实例
        IParserApi *parser = createParser();
        TestParserSpi *spi = new TestParserSpi();
        parser->registerSpi(spi);

        // 从配置文件加载配置
        WTSVariant *root = WTSCfgLoader::load_from_file("config/config.yaml");
        if (root == nullptr)
        {
            std::cerr << "❌ 无法加载配置文件 config/config.yaml" << std::endl;
            return -1;
        }

        WTSVariant *parsers = root->get("parsers");
        if (parsers == nullptr || !parsers->isArray() || parsers->size() == 0)
        {
            std::cerr << "❌ 配置文件中没有找到parsers配置" << std::endl;
            root->release();
            return -1;
        }

        // 获取第一个parser配置
        WTSVariant *config = parsers->get((uint32_t)0);
        if (config == nullptr)
        {
            std::cerr << "❌ 无法获取parser配置" << std::endl;
            root->release();
            return -1;
        }

        std::cout << "📋 配置信息:" << std::endl;
        std::cout << "   服务器: " << config->getCString("host") << ":" << config->getUInt32("port") << std::endl;
        std::cout << "   用户: " << config->getCString("user") << std::endl;
        std::cout << "   模式: " << config->getInt32("mode") << std::endl;

        std::cout << "正在初始化Parser..." << std::endl;
        if (!parser->init(config))
        {
            std::cerr << "❌ Parser初始化失败" << std::endl;
            return 1;
        }
        std::cout << "✅ Parser初始化成功" << std::endl;

        std::cout << "正在连接到中畅服务器 60.12.4.70:30002..." << std::endl;
        if (!parser->connect())
        {
            std::cerr << "❌ 连接服务器失败，请检查网络连接和服务器状态" << std::endl;
            parser->release();
            delete spi;
            deleteParser(parser);
            config->release();
            return 1;
        }

        // 从配置文件读取订阅合约
        CodeSet codes;

        // 方法1: 从配置文件的codes字段读取
        WTSVariant *codesConfig = config->get("codes");
        if (codesConfig && codesConfig->isArray())
        {
            std::cout << "从配置文件读取订阅合约..." << std::endl;
            for (uint32_t i = 0; i < codesConfig->size(); i++)
            {
                std::string contract = codesConfig->get(i)->asCString();
                codes.insert(contract);
                std::cout << "  - " << contract << std::endl;
            }
        }
        else
        {
            // 方法2: 从合约组配置文件读取（fallback）
            std::cout << "配置文件中未找到codes，尝试从合约组配置读取..." << std::endl;
            WTSVariant *contractGroups = WTSCfgLoader::load_from_file("../../common/contract_groups.json");
            if (contractGroups)
            {
                WTSVariant *testGroup = contractGroups->get("specific_contracts_2024");
                if (testGroup)
                {
                    WTSVariant *contracts = testGroup->get("contracts");
                    if (contracts && contracts->isArray())
                    {
                        std::cout << "从合约组 'specific_contracts_2024' 读取合约:" << std::endl;
                        for (uint32_t i = 0; i < contracts->size(); i++)
                        {
                            std::string contract = contracts->get(i)->asCString();
                            codes.insert(contract);
                            std::cout << "  - " << contract << std::endl;
                        }
                    }
                }
                contractGroups->release();
            }
            else
            {
                // 方法3: 使用默认合约（最后的fallback）
                std::cout << "无法读取配置文件，使用默认测试合约..." << std::endl;
                codes.insert("SHFE.cu2412");  // 沪铜主力
                codes.insert("SHFE.au2412");  // 沪金主力
                codes.insert("DCE.i2405");    // 铁矿石主力
                codes.insert("CZCE.MA405");   // 甲醇主力
                codes.insert("CFFEX.IF2412"); // 沪深300股指期货主力
            }
        }

        if (codes.empty())
        {
            std::cerr << "❌ 没有找到要订阅的合约" << std::endl;
            return 1;
        }

        std::cout << "开始订阅 " << codes.size() << " 个合约..." << std::endl;

        // 打印转换后的订阅标签格式
        std::cout << "订阅标签转换:" << std::endl;
        for (const auto &code : codes)
        {
            // 手动转换显示格式
            std::vector<std::string> parts;
            size_t pos = code.find('.');
            if (pos != std::string::npos)
            {
                std::string symbol = code.substr(0, pos);
                std::string exchange = code.substr(pos + 1);

                std::string sipExchange;
                if (exchange == "SSE")
                    sipExchange = "SH";
                else if (exchange == "SZSE")
                    sipExchange = "SZ";
                else if (exchange == "SHFE")
                    sipExchange = "SHFE";
                else if (exchange == "DCE")
                    sipExchange = "DCE";
                else if (exchange == "CZCE")
                    sipExchange = "CZCE";
                else if (exchange == "CFFEX")
                    sipExchange = "CFFEX";
                else
                    sipExchange = exchange;

                // 根据中畅接入规范，所有市场都使用L1格式（基础权限）
                std::string sipTag = sipExchange + "." + symbol + ".L1";
                std::cout << "  " << code << " -> " << sipTag << std::endl;
            }
        }

        parser->subscribe(codes);

        std::cout << "开始接收行情数据，按Ctrl+C退出..." << std::endl;
        std::cout << "注意：如果5秒内没有收到数据，可能是以下原因：" << std::endl;
        std::cout << "1. 当前不在交易时间内" << std::endl;
        std::cout << "2. 合约代码格式不正确" << std::endl;
        std::cout << "3. 用户权限不足" << std::endl;
        std::cout << "4. 网络连接问题" << std::endl;

        while (!g_bStopped)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        parser->release();
        delete spi;
        deleteParser(parser);
        root->release();

        std::cout << "程序正常退出" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "程序异常: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}