#pragma once

#include <map>
#include <vector>

#include "engineDef/dataStruct.hpp"
#include "engineDef/mdBase.hpp"
#include "stockDataStruct.hpp"
#include "utils/requestManager.hpp"

#include "codeInfo.hpp"
#include "sipv2_i.h"
#include "sipui2_i.h"
#include "subcodelist.hpp"
#include "tcffexmarket.h"
#include "tshmarket.h"
#include "tshopmarket.h"
#include "tszmarket.h"
#include "tszopmarket.h"
#include "work.h"

#define SIPUI_MARKET_EXCHANGE_ID_SH "SH" // 上海证券交易所
#define SIPUI_MARKET_EXCHANGE_ID_SZ "SZ" // 深圳证券交易所
#define SIPUI_MARKET_EXCHANGE_ID_CFFEX "CFE" // 中金所期货
#define SIPUI_MARKET_EXCHANGE_ID_CZCE "CZCE" // 郑商所
#define SIPUI_MARKET_EXCHANGE_ID_DCE "DCE" // 大商所
#define SIPUI_MARKET_EXCHANGE_ID_SHFE "SHFE" // 上期所
#define SIPUI_MARKET_EXCHANGE_ID_SHOP "SHOP" // 上交所期权
#define SIPUI_MARKET_EXCHANGE_ID_SZOP "SZOP" // 深交所期权
#define SIPUI_MARKET_EXCHANGE_ID_HK "HK" // 港股
#define SIPUI_MARKET_EXCHANGE_ID_ZZZS "ZZZS" // 中证指数
#define SIPUI_MARKET_EXCHANGE_ID_CS "CS" // 测试市场
#define SIPUI_MARKET_EXCHANGE_ID_CFFEX_OP "CFEOP" // 中金所期权
#define SIPUI_MARKET_EXCHANGE_ID_CZCE_OP "CZCEOP" // 郑商所期权
#define SIPUI_MARKET_EXCHANGE_ID_DCE_OP "DCEOP" // 大商所期权
#define SIPUI_MARKET_EXCHANGE_ID_SHFE_OP "SHFEOP" // 上期所期权

#define SIPUI_DATATYPE_CS "CS" // 测试数据
#define SIPUI_DATATYPE_L1 "L1" // level1 快照
#define SIPUI_DATATYPE_L2 "L2" // level2 快照
#define SIPUI_DATATYPE_ZK "ZK" // 指数快照
#define SIPUI_DATATYPE_ZC "ZC" // 逐笔成交
#define SIPUI_DATATYPE_ZW "ZW" // 逐笔委托
#define SIPUI_DATATYPE_WD "WD" // 委托队列快照
#define SIPUI_DATATYPE_JC "JC" // 基础信息快照
#define SIPUI_DATATYPE_CJ "CJ" // 参考价格
#define SIPUI_DATATYPE_FK "FK" // 实时分钟 K 线
#define SIPUI_DATATYPE_HL "HL" // 汇率快照
#define SIPUI_DATATYPE_XJ "XJ" // 询价通知快照
#define SIPUI_DATATYPE_VM "VM" // VCN 市价调节
#define SIPUI_DATATYPE_LF "LF" // 最快行情快照
#define SIPUI_DATATYPE_MC "MC" // 买卖差额快照
#define SIPUI_DATATYPE_JY "JY" // 交易数据消息总线

enum msg_type
{
    SH_STOCK_INDEX = 1000, // 上证指数快照
    SH_STOCK_STEP_TRADE = 1001, // 上证逐笔成交
    SH_ORDER_QUEUE = 1002, // 上证委托队列快照
    SH_STOCK_MARKET_L2 = 1004, // 上证L2快照
    SH_STOCK_MARKET_L1 = 1005, // 上证L1快照
    SZ_STOCK_INDEX = 2000, // 深证指数快照
    SZ_STOCK_STEP_TRADE = 2001, // 深证逐笔成交
    SZ_ORDER_QUEUE = 2002, // 深证委托队列快照
    SZ_STEP_ORDER = 2003, // 深证逐笔委托
    SZ_STOCK_MARKET_L2 = 2004, // 深证L2快照
    SZ_STOCK_MARKET_L1 = 2005, // 深证L1快照
    CFFEX_STOCK_BASE = 3001, // 中金所期货基础信息
    CFFEX_STOCK_MARKET = 3002, // 中金所快照
    CZCE_STOCK_BASE = 4001, // 郑商所期货基础信息
    CZCE_STOCK_MARKET = 4002, // 郑商所快照
    DCE_STOCK_BASE = 5001, // 大商所期货基础信息
    DCE_STOCK_MARKET = 5002, // 大商所快照
    SHFE_STOCK_BASE = 6001, // 上期所期货基础信息
    SHFE_STOCK_MARKET = 6002, // 上期所快照
    SHOP_STOCK_BASE = 8001, // 上交所期权基础信息
    SHOP_STOCK_MARKET_L1 = 8002, // 上交所期权快照
    HK_STOCK_MARKET_L1 = 9002, // 港股L1快照
    HK_STOCK_MARKET_L2 = 9004, // 港股L2快照
    SZOP_STOCK_BASE = 11001, // 深交所期权基础信息
    SZOP_STOCK_MARKETL1 = 11002, // 深交所期权快照
    INE_STOCK_MARKET = 14002, // 能源所快照
    PT_STOCK_MARKET_L1 = 15002, // 新三板L1快照
};
enum MarketDataBitType
{
    L1 = 0b0000000000000001,
    L2 = 0b0000000000000010,
    ZK = 0b0000000000000100,
    ZC = 0b0000000000001000,
    ZW = 0b0000000000010000,
    WD = 0b0000000000100000,
    JC = 0b0000000001000000,
    CJ = 0b0000000010000000,
    FK = 0b0000000100000000,
    HL = 0b0000001000000000,
    XJ = 0b0000010000000000,
    VM = 0b0000100000000000,
    LF = 0b0001000000000000,
    MC = 0b0010000000000000,
    JY = 0b0100000000000000,
};
class sipui2MD final : public MDBase, public SubCodeList, public StaticInfo
{
public:
    explicit sipui2MD(std::string name);
    ~sipui2MD() override { UI_Close(m_uihandler_); };
    int subscribeMarketData(const std::string &instrument) override;
    //    bool codeinlist(int code, int type);
    //    bool forwardMarketData(MarketDataField &md, bool block = false);
    /**
     * @todo 行情解析目前只完成了字段的基本赋值，有些品种价格浮点数的转换精度暂未细看，需要交易该品种时再研究
     */
    static void OnNotifyMsg(TPKG_SIP *pPkg, CBPARAM pParam);
    static void DoMsg(T_SIPTAGMSG *ptag, void *pParam);
    // @todo 行情打印的级别可以调整，暂时先用info
    void GetStockDataL1(T_SIPTAGMSG *msg);
    void GetStockDataL2(T_SIPTAGMSG *msg);
    void GetOrderData(T_SIPTAGMSG *msg);
    void GetOrderQueueData(T_SIPTAGMSG *msg);
    void GetSZTransData(T_SIPTAGMSG *msg);
    void GetSHTransData(T_SIPTAGMSG *msg);
    void GetIndexData(T_SIPTAGMSG *msg);
    void GetFutureData(T_SIPTAGMSG *msg);
    void GetFutureBaseData(T_SIPTAGMSG *msg);
    void GetSZOptionData(T_SIPTAGMSG *msg);
    void GetSZOptionBaseData(T_SIPTAGMSG *msg);
    void GetSHOptionData(T_SIPTAGMSG *msg);
    void GetSHOptionBaseData(T_SIPTAGMSG *msg);

    bool connect();
    int subAll();

    int reqInstrumentInfo(std::string instrument,
                          std::function<void(InstrumentField &instrumentInfo)> callback) override;
    void handle_start() override;
    void handle_stop() override;
    static std::vector<std::string> splitString(const std::string &input, char delimiter);

protected:
    int sub(std::string &martket, const std::string &code, int type);
    // int code2list(int code, int type);

private:
    RequestManager *requestManager;
    std::set<std::string> instruments_set;
    static sipui2MD *sip;
    std::string m_ip, m_account, m_passwd;
    int m_port{};
    UIHANDLE m_uihandler_{};
    bool m_L1; // level1
    bool m_L2; // level2
    bool m_ZK; // 指数快照
    bool m_ZC;  // 逐笔成交
    bool m_ZW;  // 逐笔委托
    bool m_WD;  // 委托队列快照
    bool m_JC;  // 基础信息快照
    bool m_CJ;  // 参考价格
    bool m_FK;  // 实时分钟K线
    bool m_HL;  // 汇率快照
    bool m_XJ;  // 询价通知快照
    bool m_VM;  // VCN市价调节
    bool m_LF;  // 最快行情快照
    bool m_MC;  // 买卖差额快照
    bool debug{};
};