/*!
 * \file ParserZC.h
 * \project	WonderTrader
 *
 * \author AI Assistant
 * \date 2025/01/17
 *
 * \brief 中畅行情解析器接口定义
 */
#pragma once

#include "../Includes/IParserApi.h"
#include "../Includes/WTSMarcos.h"
#include "../Share/DLLHelper.hpp"
#include "../Share/StdUtils.hpp"
#include "ParserZCDef.h"

// 包含sipsi2Api接口
#include "../API/sipsi2Api/inc/tdef.h"
#include "../API/sipsi2Api/inc/sipv2_i.h"
#include "../API/sipsi2Api/inc/sipui2_i.h"

#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <atomic>

NS_WTP_BEGIN
class WTSTickData;
class WTSVariant;
class IParserSpi;
class IBaseDataMgr;
NS_WTP_END

USING_NS_WTP;

/*!
 * \brief 中畅行情解析器
 *
 * 基于sipsi2Api实现的中畅行情数据解析器，支持多种连接模式：
 * - TCP普通模式 (LOGIN_NR)
 * - TCP LNK模式 (LOGIN_LNK)
 * - PGM组播模式 (LOGIN_PGM)
 * - Multicast模式 (LOGIN_MCB)
 */
class ParserZC : public IParserApi
{
public:
    ParserZC();
    virtual ~ParserZC();

public:
    //////////////////////////////////////////////////////////////////////////
    // IParserApi接口实现
    virtual bool init(WTSVariant *config) override;
    virtual void release() override;
    virtual bool connect() override;
    virtual bool disconnect() override;
    virtual bool isConnected() override;
    virtual void subscribe(const CodeSet &vecSymbols) override;
    virtual void unsubscribe(const CodeSet &vecSymbols) override;
    virtual void registerSpi(IParserSpi *listener) override;

private:
    //////////////////////////////////////////////////////////////////////////
    // sipsi2Api回调处理

    /*!
     * \brief sipsi2Api的通知回调函数
     * \param pPkg 数据包指针
     * \param pParam 用户参数，这里是ParserZC实例指针
     */
    static void __stdcall OnNotifyCallback(TPKG_SIP *pPkg, CBPARAM pParam);

    /*!
     * \brief 处理市场数据消息
     * \param pMsg 消息数据指针
     */
    void handleMarketData(T_SIPTAGMSG *pMsg);

    /*!
     * \brief 处理连接状态通知
     * \param pPkg 状态数据包
     */
    void handleConnectionStatus(TPKG_SIP *pPkg);

    /*!
     * \brief 处理错误通知
     * \param pErrPkg 错误数据包
     */
    void handleErrorNotify(TPKG_SIP_TAGERR *pErrPkg);

    /*!
     * \brief 获取合约列表
     * \param info_server_ip 信息服务器IP
     * \param info_server_port 信息服务器端口
     * \return 是否成功获取
     */
    bool requestSymbolList(const std::string &info_server_ip = "", uint16_t info_server_port = 0);

    /*!
     * \brief 处理服务器列表回调
     * \param svrs 服务器列表
     * \param count 服务器数量
     */
    static void _cdecl onServerListCallback(T_ONLINEUISVR svrs[], unsigned int count, void *pParam);

    /*!
     * \brief 处理合约列表回调
     * \param contracts 合约列表
     * \param count 合约数量
     */
    static void _cdecl onContractListCallback(T_SCITEMEX contracts[], unsigned int count, void *pParam);

private:
    //////////////////////////////////////////////////////////////////////////
    // 连接和订阅管理

    /*!
     * \brief 执行连接操作
     * \return 连接是否成功
     */
    bool doConnect();

    /*!
     * \brief 执行断开连接操作
     */
    void doDisconnect();

    /*!
     * \brief 执行订阅操作
     * \param codes 要订阅的合约代码集合
     * \return 订阅是否成功
     */
    bool doSubscribe(const CodeSet &codes);

    /*!
     * \brief 执行取消订阅操作
     * \param codes 要取消订阅的合约代码集合
     * \return 取消订阅是否成功
     */
    bool doUnsubscribe(const CodeSet &codes);

    /*!
     * \brief 检查并更新连接状态
     */
    void checkConnectionStatus();

private:
    //////////////////////////////////////////////////////////////////////////
    // 数据转换和处理

    /*!
     * \brief 将sipsi2的消息数据转换为WTSTickData
     * \param pMsg sipsi2消息数据
     * \return 转换后的Tick数据，需要调用者释放
     */
    WTSTickData *parseTickData(T_SIPTAGMSG *pMsg);

    /*!
     * \brief 解析合约代码，转换为标准格式
     * \param tag_name sipsi2的标签名称
     * \return 标准化的合约代码
     */
    std::string parseInstrumentCode(const char *tag_name);

    /*!
     * \brief 获取交易日期
     * \return 当前交易日期
     */
    uint32_t getTradingDate();

    /*!
     * \brief 将WonderTrader格式代码转换为sipsi2标签格式
     * \param wtCode WonderTrader格式的合约代码
     * \return sipsi2标签格式（默认使用L1数据类型）
     */
    std::string convertToSipTagName(const std::string &wtCode);

    /*!
     * \brief 将WonderTrader格式代码转换为指定数据类型的中畅格式
     * \param wtCode WonderTrader格式的合约代码 (如: 600000.SSE)
     * \param dataType 数据类型 (如: L1, L2, ZC, WD等)
     * \return 中畅格式标签 (如: SH.600000.L1)
     */
    std::string convertWonderTraderToZCFormat(const std::string &wtCode, const std::string &dataType);

    /*!
     * \brief 转换交易所代码从WonderTrader格式到中畅格式
     * \param wtExchange WonderTrader交易所代码 (如: SSE, SZSE, SHFE等)
     * \return 中畅交易所代码 (如: SH, SZ, SHFE等)
     */
    std::string convertExchangeCode(const std::string &wtExchange);

    /*!
     * \brief 根据交易所确定支持的数据类型
     * \param zcExchange 中畅交易所代码
     * \param requestedType 请求的数据类型
     * \return 实际支持的数据类型
     */
    std::string determineFinalDataType(const std::string &zcExchange, const std::string &requestedType);

    /*!
     * \brief 从标签名中提取市场代码
     * \param tag_name sipsi2标签名
     * \return 市场代码
     */
    std::string extractMarketFromTag(const char *tag_name);

    /*!
     * \brief 解析股票L1数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseStockL1Data(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析股票L2数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseStockL2Data(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析期货数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseFutureData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析逐笔成交数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseTransactionData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析委托队列数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseOrderQueueData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析指数数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseIndexData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析期权数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseOptionData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 解析港股数据
     * \param pMsg sipsi2消息数据
     * \param instrument 合约代码
     * \return 解析后的Tick数据
     */
    WTSTickData *parseHKData(T_SIPTAGMSG *pMsg, const std::string &instrument);

    /*!
     * \brief 转换ZhongChang时间格式
     * \param action_day 行情日期 YYYYMMDD
     * \param time_stamp 时间戳 HHMMSSmmm
     * \return ZCTimeInfo结构
     */
    ZCTimeInfo convertZCTime(T_I32 action_day, T_I32 time_stamp);

    /*!
     * \brief 转换ZhongChang价格格式
     * \param raw_price 原始价格(4位小数)
     * \return ZCPriceInfo结构
     */
    ZCPriceInfo convertZCPrice(T_U32 raw_price);

    /*!
     * \brief 设置Tick数据的基本信息
     * \param tick Tick对象
     * \param time_info 时间信息
     * \param instrument 合约代码
     */
    void setTickBasicInfo(WTSTickData *tick, const ZCTimeInfo &time_info, const std::string &instrument);

private:
    //////////////////////////////////////////////////////////////////////////
    // 错误处理和日志

    /*!
     * \brief 记录sipsi2Api错误信息
     * \param ret 错误返回码
     * \param operation 操作名称
     */
    void logSipError(SIPRET ret, const char *operation);

    /*!
     * \brief 获取错误信息描述
     * \param error_code 错误码
     * \return 错误描述字符串
     */
    const char *getErrorMessage(int error_code);

    /*!
     * \brief 初始化错误信息映射表
     */
    void initErrorMessages();

private:
    //////////////////////////////////////////////////////////////////////////
    // 成员变量

    // sipsi2Api相关
    UIHANDLE m_hSipHandle;                              // sipsi2接口句柄
    ZCConfigInfo m_configInfo;                          // 配置信息
    std::atomic<ZCConnectionStatus> m_connectionStatus; // 连接状态

    // 订阅管理
    typedef std::unordered_map<std::string, ZCInstrumentInfo> InstrumentMap;
    InstrumentMap m_mapInstruments;  // 合约信息映射
    StdUniqueMutex m_mtxInstruments; // 合约映射锁
    CodeSet m_setPendingSub;         // 待订阅合约集合
    CodeSet m_setPendingUnsub;       // 待取消订阅合约集合

    // 回调接口
    IParserSpi *m_pSpi;           // 数据回调接口
    IBaseDataMgr *m_pBaseDataMgr; // 基础数据管理器

    // 状态管理
    std::atomic<bool> m_bStopped;     // 停止标志
    std::atomic<bool> m_bInitialized; // 初始化标志
    uint32_t m_uTradingDate;          // 交易日期

    // 统计信息
    std::atomic<uint64_t> m_uTickCount;  // 接收到的tick数量
    std::atomic<uint64_t> m_uErrorCount; // 错误数量
    uint64_t m_uLastHeartbeat;           // 最后心跳时间

    // 错误信息映射
    std::map<int, std::string> m_mapErrorMessages; // 错误码到描述的映射

    // 线程安全
    StdUniqueMutex m_mtxCallback;   // 回调处理锁
    StdUniqueMutex m_mtxConnection; // 连接操作锁
};

//////////////////////////////////////////////////////////////////////////
// 导出函数声明
extern "C"
{
    EXPORT_FLAG IParserApi *createParser();
    EXPORT_FLAG void deleteParser(IParserApi *&parser);
}