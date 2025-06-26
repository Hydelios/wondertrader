/*!
 * \file ParserZCDef.h
 * \project	WonderTrader
 *
 * \author AI Assistant
 * \date 2025/01/17
 *
 * \brief ParserZC模块内部定义
 */
#pragma once

#include <string>
#include <set>
#include <atomic>
#include <mutex>
#include "../API/sipsi2Api/inc/tdef.h"
#include "../API/sipsi2Api/inc/sipv2_i.h"

NS_WTP_BEGIN

//////////////////////////////////////////////////////////////////////////
// ZhongChang消息类型定义（根据接入规范文档）

// 上海证券交易所消息类型
#define ZC_MSG_SH_INDEX         1000    // 上证指数快照
#define ZC_MSG_SH_TRANSACTION   1001    // 上证逐笔成交
#define ZC_MSG_SH_ORDER_QUEUE   1002    // 上证委托队列快照
#define ZC_MSG_SH_L2_SNAPSHOT   1004    // 上证L2快照
#define ZC_MSG_SH_L1_SNAPSHOT   1005    // 上证L1快照

// 深圳证券交易所消息类型
#define ZC_MSG_SZ_INDEX         2000    // 深证指数快照
#define ZC_MSG_SZ_TRANSACTION   2001    // 深证逐笔成交
#define ZC_MSG_SZ_ORDER_QUEUE   2002    // 深证委托队列快照
#define ZC_MSG_SZ_ORDER_DETAIL  2003    // 深证逐笔委托
#define ZC_MSG_SZ_L2_SNAPSHOT   2004    // 深证L2快照
#define ZC_MSG_SZ_L1_SNAPSHOT   2005    // 深证L1快照

// 期货交易所消息类型
#define ZC_MSG_CFFEX_SNAPSHOT   3002    // 中金所行情快照
#define ZC_MSG_CZCE_SNAPSHOT    4002    // 郑商所行情快照
#define ZC_MSG_DCE_SNAPSHOT     5002    // 大商所行情快照
#define ZC_MSG_SHFE_SNAPSHOT    6002    // 上期所行情快照
#define ZC_MSG_ZZZS_INDEX       7002    // 中证指数快照

// 期权消息类型
#define ZC_MSG_SHOP_SNAPSHOT    8002    // 上交所期权行情快照
#define ZC_MSG_HK_L2_SNAPSHOT   9001    // 港股L2快照
#define ZC_MSG_HK_L1_SNAPSHOT   9004    // 港股L1快照
#define ZC_MSG_SZOP_SNAPSHOT    11002   // 深交所期权行情快照

//////////////////////////////////////////////////////////////////////////
// 数据转换辅助常量

#define ZC_PRICE_SCALE          10000   // 价格精度：4位小数
#define ZC_TIME_SCALE           1000    // 时间精度：毫秒
#define ZC_MAX_BID_ASK_LEVELS   10      // 最大买卖档位数
#define ZC_MAX_ORDER_QUEUE_SIZE 200     // 最大委托队列大小

//////////////////////////////////////////////////////////////////////////
// 时间和价格转换宏

// 将LOCALTIME格式(HHMMSSmmm)转换为时间戳
#define ZC_LOCALTIME_TO_TIMESTAMP(localtime) \
    ((((localtime) / 10000000) * 3600 + \
      (((localtime) / 100000) % 100) * 60 + \
      (((localtime) / 1000) % 100)) * 1000 + \
     ((localtime) % 1000))

// 将PRICE格式转换为double
#define ZC_PRICE_TO_DOUBLE(price) ((double)(price) / ZC_PRICE_SCALE)

// 检查价格是否有效（非零且非最大值）
#define ZC_IS_VALID_PRICE(price) ((price) > 0 && (price) != 0xFFFFFFFF)

// 中畅行情连接状态
enum ZCConnectionStatus
{
    ZC_CS_DISCONNECTED = 0,    // 未连接
    ZC_CS_CONNECTING,          // 连接中
    ZC_CS_CONNECTED,           // 已连接
    ZC_CS_LOGGEDIN,           // 已登录
    ZC_CS_ERROR               // 错误状态
};

// 中畅行情订阅状态
enum ZCSubscribeStatus
{
    ZC_SS_NONE = 0,           // 未订阅
    ZC_SS_SUBSCRIBING,        // 订阅中
    ZC_SS_SUBSCRIBED,         // 已订阅
    ZC_SS_UNSUBSCRIBING       // 取消订阅中
};

// 合约订阅信息
struct ZCInstrumentInfo
{
    std::string tag_name;        // sipsi2标签名
    std::string instrument_code; // WonderTrader合约代码
    std::string exchange_code;   // 交易所代码
    bool is_subscribed;         // 是否已订阅
    uint64_t sub_time;          // 订阅时间

    ZCInstrumentInfo() : is_subscribed(false), sub_time(0) {}
};

// 中畅行情配置信息
struct ZCConfigInfo
{
    std::string server_ip;     // 服务器IP
    uint16_t server_port;      // 服务器端口
    std::string user_id;       // 用户名
    std::string password;      // 密码
    int login_mode;           // 登录模式
    int proxy_type;           // 代理类型
    std::string proxy_ip;      // 代理IP
    uint16_t proxy_port;       // 代理端口
    std::string proxy_user;    // 代理用户名
    std::string proxy_pass;    // 代理密码
    bool async_connect;       // 是否异步连接
    uint32_t timeout_ms;      // 超时时间(毫秒)
    
    ZCConfigInfo()
    {
        server_port = 0;
        login_mode = 0;  // LOGIN_NR
        proxy_type = 0;  // TCPC_PROXY_NONE
        proxy_port = 0;
        async_connect = false;
        timeout_ms = 10000;
    }
};

// 错误信息映射
struct ZCErrorInfo
{
    int error_code;
    std::string error_msg;

    ZCErrorInfo(int code, const std::string& msg) : error_code(code), error_msg(msg) {}
};

//////////////////////////////////////////////////////////////////////////
// 数据解析辅助结构

// 时间转换结果
struct ZCTimeInfo
{
    uint32_t action_date;   // 行情日期 YYYYMMDD
    uint32_t action_time;   // 行情时间 HHMMSSmmm
    uint32_t trading_date;  // 交易日期 YYYYMMDD

    ZCTimeInfo() : action_date(0), action_time(0), trading_date(0) {}
};



// 市场类型枚举
enum ZCMarketType
{
    ZC_MARKET_UNKNOWN = 0,
    ZC_MARKET_SH,       // 上海证券交易所
    ZC_MARKET_SZ,       // 深圳证券交易所
    ZC_MARKET_CFFEX,    // 中金所
    ZC_MARKET_CZCE,     // 郑商所
    ZC_MARKET_DCE,      // 大商所
    ZC_MARKET_SHFE,     // 上期所
    ZC_MARKET_SHOP,     // 上交所期权
    ZC_MARKET_SZOP,     // 深交所期权
    ZC_MARKET_HK,       // 港股
    ZC_MARKET_ZZZS      // 中证指数
};

// 数据类型枚举
enum ZCDataType
{
    ZC_DATA_UNKNOWN = 0,
    ZC_DATA_L1_SNAPSHOT,    // L1快照
    ZC_DATA_L2_SNAPSHOT,    // L2快照
    ZC_DATA_TRANSACTION,    // 逐笔成交
    ZC_DATA_ORDER_QUEUE,    // 委托队列
    ZC_DATA_ORDER_DETAIL,   // 逐笔委托
    ZC_DATA_INDEX,          // 指数
    ZC_DATA_FUTURE,         // 期货
    ZC_DATA_OPTION          // 期权
};

// 消息解析上下文
struct ZCParseContext
{
    ZCMarketType market_type;
    ZCDataType data_type;
    uint16_t msg_type;
    std::string instrument_code;
    std::string exchange_code;

    ZCParseContext() : market_type(ZC_MARKET_UNKNOWN), data_type(ZC_DATA_UNKNOWN), msg_type(0) {}
};

NS_WTP_END