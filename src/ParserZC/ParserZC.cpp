/*!
 * \file ParserZC.cpp
 * \project	WonderTrader
 *
 * \author AI Assistant
 * \date 2025/01/17
 *
 * \brief 中畅行情解析器实现
 */

#include "ParserZC.h"
#include "../Includes/WTSDataDef.hpp"
#include "../Includes/WTSVariant.hpp"
#include "../Includes/IBaseDataMgr.h"
#include "../Includes/WTSContractInfo.hpp"
#include "../WTSTools/WTSLogger.h"
#include "../Share/TimeUtils.hpp"
#include "../Share/StrUtil.hpp"

// 包含ZhongChang市场数据结构
#include "../API/sipsi2Api/inc/tshmarket.h"
#include "../API/sipsi2Api/inc/tszmarket.h"
#include "../API/sipsi2Api/inc/tcffexmarket.h"
#include "../API/sipsi2Api/inc/tczcemarket.h"
#include "../API/sipsi2Api/inc/tdcemarket.h"
#include "../API/sipsi2Api/inc/tshfemarket.h"

#include <chrono>
#include <vector>
#include <string>

USING_NS_WTP;

//////////////////////////////////////////////////////////////////////////
// 构造函数和析构函数

ParserZC::ParserZC()
    : m_hSipHandle(INVALID_SIPHANDLE), m_connectionStatus(ZC_CS_DISCONNECTED), m_pSpi(nullptr), m_pBaseDataMgr(nullptr), m_bStopped(false), m_bInitialized(false), m_uTradingDate(0), m_uTickCount(0), m_uErrorCount(0), m_uLastHeartbeat(0)
{
    initErrorMessages();
}

ParserZC::~ParserZC()
{
    release();
}

//////////////////////////////////////////////////////////////////////////
// IParserApi接口实现

bool ParserZC::init(WTSVariant *config)
{
    if (m_bInitialized.load())
    {
        WTSLogger::warn("ParserZC already initialized");
        return true;
    }

    if (config == nullptr)
    {
        WTSLogger::error("ParserZC init failed: config is null");
        return false;
    }

    try
    {
        // 读取基本连接配置
        const char *host = config->getCString("host");
        m_configInfo.server_ip = host ? host : "";
        m_configInfo.server_port = config->has("port") ? config->getUInt32("port") : 30002;

        // 读取用户认证配置
        const char *user = config->getCString("user");
        m_configInfo.user_id = user ? user : "";
        const char *pass = config->getCString("pass");
        m_configInfo.password = pass ? pass : "";

        // 读取连接模式配置
        // 0=TCP普通模式(LOGIN_NR), 1=TCP LNK模式(LOGIN_LNK), 2=PGM组播模式(LOGIN_PGM), 3=MCB组播模式(LOGIN_MCB)
        m_configInfo.login_mode = config->has("mode") ? config->getInt32("mode") : LOGIN_NR;
        m_configInfo.async_connect = config->has("async") ? config->getBoolean("async") : false;
        m_configInfo.timeout_ms = config->has("timeout") ? config->getUInt32("timeout") : 10000;

        // 验证连接模式的有效性
        if (m_configInfo.login_mode < LOGIN_NR || m_configInfo.login_mode > LOGIN_MCB)
        {
            WTSLogger::warn("ParserZC invalid login mode {}, using default LOGIN_NR", m_configInfo.login_mode);
            m_configInfo.login_mode = LOGIN_NR;
        }

        // 代理配置(可选)
        if (config->has("proxy"))
        {
            WTSVariant *proxy_cfg = config->get("proxy");
            if (proxy_cfg != nullptr)
            {
                m_configInfo.proxy_type = proxy_cfg->has("type") ? proxy_cfg->getInt32("type") : TCPC_PROXY_NONE;
                const char *proxy_host = proxy_cfg->getCString("host");
                m_configInfo.proxy_ip = proxy_host ? proxy_host : "";
                m_configInfo.proxy_port = proxy_cfg->has("port") ? proxy_cfg->getUInt32("port") : 0;
                const char *proxy_user = proxy_cfg->getCString("user");
                m_configInfo.proxy_user = proxy_user ? proxy_user : "";
                const char *proxy_pass = proxy_cfg->getCString("pass");
                m_configInfo.proxy_pass = proxy_pass ? proxy_pass : "";

                // 验证代理配置
                if (m_configInfo.proxy_type != TCPC_PROXY_NONE)
                {
                    if (m_configInfo.proxy_ip.empty() || m_configInfo.proxy_port == 0)
                    {
                        WTSLogger::warn("ParserZC invalid proxy configuration, disabling proxy");
                        m_configInfo.proxy_type = TCPC_PROXY_NONE;
                    }
                    else
                    {
                        WTSLogger::info("ParserZC proxy enabled - Type: {}, Server: {}:{}",
                                        m_configInfo.proxy_type, m_configInfo.proxy_ip, m_configInfo.proxy_port);
                    }
                }
            }
        }

        // 验证必需配置
        if (m_configInfo.server_ip.empty())
        {
            WTSLogger::error("ParserZC init failed: server host is required");
            return false;
        }

        if (m_configInfo.server_port == 0 || m_configInfo.server_port > 65535)
        {
            WTSLogger::error("ParserZC init failed: invalid server port {}", m_configInfo.server_port);
            return false;
        }

        if (m_configInfo.user_id.empty())
        {
            WTSLogger::error("ParserZC init failed: user ID is required");
            return false;
        }

        if (m_configInfo.password.empty())
        {
            WTSLogger::error("ParserZC init failed: password is required");
            return false;
        }

        // 验证超时配置
        if (m_configInfo.timeout_ms < 1000 || m_configInfo.timeout_ms > 60000)
        {
            WTSLogger::warn("ParserZC invalid timeout {}, using default 10000ms", m_configInfo.timeout_ms);
            m_configInfo.timeout_ms = 10000;
        }

        // 初始化sipsi2接口
        m_hSipHandle = UI_Open(OnNotifyCallback, (CBPARAM)this);
        if (m_hSipHandle == INVALID_SIPHANDLE)
        {
            WTSLogger::error("ParserZC init failed: UI_Open error");
            return false;
        }

        // 设置代理(如果配置了)
        if (m_configInfo.proxy_type != TCPC_PROXY_NONE)
        {
            SIPRET ret = UI_SetPproxyInfo(m_hSipHandle,
                                          m_configInfo.proxy_type,
                                          m_configInfo.proxy_ip.c_str(),
                                          m_configInfo.proxy_port,
                                          m_configInfo.proxy_user.c_str(),
                                          m_configInfo.proxy_pass.c_str());
            if (ret != SIPE_OK)
            {
                logSipError(ret, "UI_SetPproxyInfo");
                UI_Close(m_hSipHandle);
                m_hSipHandle = INVALID_SIPHANDLE;
                return false;
            }
        }

        m_bInitialized = true;
        m_uTradingDate = getTradingDate();

        WTSLogger::info("ParserZC initialized successfully - Server: {}:{}, User: {}, Mode: {}",
                        m_configInfo.server_ip, m_configInfo.server_port,
                        m_configInfo.user_id, m_configInfo.login_mode);
        return true;
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC init failed with exception: {}", e.what());
        return false;
    }
}

void ParserZC::release()
{
    m_bStopped = true;

    // 断开连接
    disconnect();

    // 关闭sipsi2接口
    if (m_hSipHandle != INVALID_SIPHANDLE)
    {
        UI_Close(m_hSipHandle);
        m_hSipHandle = INVALID_SIPHANDLE;
    }

    // 清理资源
    {
        StdUniqueLock lock(m_mtxInstruments);
        m_mapInstruments.clear();
        m_setPendingSub.clear();
        m_setPendingUnsub.clear();
    }

    m_pSpi = nullptr;
    m_pBaseDataMgr = nullptr;
    m_bInitialized = false;

    WTSLogger::info("ParserZC released - Ticks: {}, Errors: {}",
                    m_uTickCount.load(), m_uErrorCount.load());
}

bool ParserZC::connect()
{
    if (!m_bInitialized.load())
    {
        WTSLogger::error("ParserZC connect failed: not initialized");
        return false;
    }

    if (m_connectionStatus.load() == ZC_CS_CONNECTED ||
        m_connectionStatus.load() == ZC_CS_LOGGEDIN)
    {
        WTSLogger::warn("ParserZC already connected");
        return true;
    }

    StdUniqueLock lock(m_mtxConnection);
    return doConnect();
}

bool ParserZC::disconnect()
{
    if (m_connectionStatus.load() == ZC_CS_DISCONNECTED)
        return true;

    StdUniqueLock lock(m_mtxConnection);
    doDisconnect();
    return true;
}

bool ParserZC::isConnected()
{
    ZCConnectionStatus status = m_connectionStatus.load();
    return (status == ZC_CS_CONNECTED || status == ZC_CS_LOGGEDIN);
}

void ParserZC::subscribe(const CodeSet &vecSymbols)
{
    if (vecSymbols.empty())
        return;

    if (!isConnected())
    {
        WTSLogger::warn("ParserZC subscribe failed: not connected");
        // 将待订阅合约加入待处理列表
        StdUniqueLock lock(m_mtxInstruments);
        for (const auto &symbol : vecSymbols)
        {
            m_setPendingSub.insert(symbol);
        }
        return;
    }

    doSubscribe(vecSymbols);
}

void ParserZC::unsubscribe(const CodeSet &vecSymbols)
{
    if (vecSymbols.empty())
        return;

    if (!isConnected())
    {
        WTSLogger::warn("ParserZC unsubscribe failed: not connected");
        // 将待取消订阅合约加入待处理列表
        StdUniqueLock lock(m_mtxInstruments);
        for (const auto &symbol : vecSymbols)
        {
            m_setPendingUnsub.insert(symbol);
        }
        return;
    }

    doUnsubscribe(vecSymbols);
}

void ParserZC::registerSpi(IParserSpi *listener)
{
    m_pSpi = listener;
    if (listener && m_pBaseDataMgr == nullptr)
    {
        m_pBaseDataMgr = listener->getBaseDataMgr();
    }
}

//////////////////////////////////////////////////////////////////////////
// sipsi2Api回调处理

void __stdcall ParserZC::OnNotifyCallback(TPKG_SIP *pPkg, CBPARAM pParam)
{
    ParserZC *pParser = reinterpret_cast<ParserZC *>(pParam);
    if (pParser == nullptr || pPkg == nullptr || pParser->m_bStopped.load())
        return;

    StdUniqueLock lock(pParser->m_mtxCallback);

    try
    {
        switch (pPkg->PkgCode)
        {
        case CPKG_SVRPUTMSG: // 实时行情数据
        {
            TPKG_SIP_TAGMSGS *pTagMsgs = reinterpret_cast<TPKG_SIP_TAGMSGS *>(pPkg);
            UI_ParseTagMsgs(pTagMsgs, [](T_SIPTAGMSG *pMsg, void *pParam)
                            {
                                  ParserZC* parser = reinterpret_cast<ParserZC*>(pParam);
                                  parser->handleMarketData(pMsg); }, pParser);
        }
        break;

        case CPKG_SSCTAGERRNOTIFY: // 标签错误通知
        {
            TPKG_SIP_TAGERR *pErrPkg = reinterpret_cast<TPKG_SIP_TAGERR *>(pPkg);
            pParser->handleErrorNotify(pErrPkg);
        }
        break;

        default:
            pParser->handleConnectionStatus(pPkg);
            break;
        }
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC callback exception: {}", e.what());
        pParser->m_uErrorCount++;
    }
}

void ParserZC::handleMarketData(T_SIPTAGMSG *pMsg)
{
    if (pMsg == nullptr || m_pSpi == nullptr)
        return;

    // 添加调试日志
    WTSLogger::info("ParserZC received market data - MsgType: {}, Code: {}",
                    pMsg->MsgType, pMsg->Code);

    try
    {
        WTSTickData *tick = parseTickData(pMsg);
        if (tick != nullptr)
        {
            m_uTickCount++;
            WTSLogger::info("ParserZC parsed tick data for: {}, price: {}",
                            tick->code(), tick->price());
            m_pSpi->handleQuote(tick, 1);
            tick->release();
        }
        else
        {
            WTSLogger::warn("ParserZC failed to parse tick data - MsgType: {}", pMsg->MsgType);
        }
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC handleMarketData exception: {}", e.what());
        m_uErrorCount++;
    }
}

void ParserZC::handleConnectionStatus(TPKG_SIP *pPkg)
{
    // 处理连接状态变化
    // TPKG_SIP本身没有ErrCode，需要根据PkgCode判断类型
    if (pPkg->PkgCode == CPKG_LOCAL_ERR || pPkg->PkgCode == CPKG_PKGERR)
    {
        TPKG_SIP_SST *pSstPkg = (TPKG_SIP_SST *)pPkg;
        if (pSstPkg->ErrCode == SIPE_ASYNCONNECTOK)
        {
            m_connectionStatus = ZC_CS_LOGGEDIN;
            WTSLogger::info("ParserZC async connection success");

            if (m_pSpi)
            {
                m_pSpi->handleEvent(WPE_Connect, 0);
            }

            // 处理待订阅的合约
            CodeSet pendingSub;
            {
                StdUniqueLock lock(m_mtxInstruments);
                pendingSub = m_setPendingSub;
                m_setPendingSub.clear();
            }

            if (!pendingSub.empty())
            {
                doSubscribe(pendingSub);
            }
        }
        else if (pSstPkg->ErrCode == SIPE_DISCONNECT)
        {
            m_connectionStatus = ZC_CS_DISCONNECTED;
            WTSLogger::warn("ParserZC connection lost (SIPE_DISCONNECT), attempting reconnect...");

            // 参考demo实现：自动重连和重新订阅
            if (doConnect())
            {
                WTSLogger::info("ParserZC reconnected successfully");

                // 重新订阅之前的合约
                CodeSet subscribedCodes;
                {
                    StdUniqueLock lock(m_mtxInstruments);
                    for (const auto &pair : m_mapInstruments)
                    {
                        if (pair.second.is_subscribed)
                        {
                            subscribedCodes.insert(pair.first);
                        }
                    }
                }

                if (!subscribedCodes.empty())
                {
                    WTSLogger::info("ParserZC re-subscribing {} instruments after reconnect", subscribedCodes.size());
                    doSubscribe(subscribedCodes);
                }
            }
            else
            {
                WTSLogger::error("ParserZC reconnect failed");
                if (m_pSpi)
                {
                    m_pSpi->handleEvent(WPE_Close, 0);
                }
            }
        }
        else if (pSstPkg->ErrCode == SIPE_ASYNCONNECTERR)
        {
            m_connectionStatus = ZC_CS_DISCONNECTED;
            WTSLogger::error("ParserZC async connection error");

            if (m_pSpi)
            {
                m_pSpi->handleEvent(WPE_Close, 0);
            }
        }
    }
}

void ParserZC::handleErrorNotify(TPKG_SIP_TAGERR *pErrPkg)
{
    if (pErrPkg == nullptr)
        return;

    m_uErrorCount++;

    // 记录错误信息
    // TPKG_SIP_TAGERR包含多个SIP_TAGERR，需要遍历处理
    for (uint32_t i = 0; i < pErrPkg->TagNum && i < 255; i++)
    {
        const SIP_TAGERR &tagErr = pErrPkg->TagErr[i];
        WTSLogger::error("ParserZC tag error - Tag: {}, Code: {}, Message: {}",
                         tagErr.TagCode, tagErr.Errcode, getErrorMessage(tagErr.Errcode));
    }
}

bool ParserZC::requestSymbolList(const std::string &info_server_ip, uint16_t info_server_port)
{
    if (m_hSipHandle == INVALID_SIPHANDLE)
    {
        WTSLogger::error("ParserZC requestSymbolList failed: invalid handle");
        return false;
    }

    // 使用配置的服务器地址或者传入的地址
    std::string server_ip = info_server_ip.empty() ? m_configInfo.server_ip : info_server_ip;
    uint16_t server_port = info_server_port == 0 ? m_configInfo.server_port : info_server_port;

    WTSLogger::info("ParserZC requesting symbol list from {}:{}", server_ip, server_port);

    // 调用sipsi2Api获取合约列表
    SIPRET ret = INFO_GetCodes(m_hSipHandle,
                               server_ip.c_str(),
                               server_port,
                               m_configInfo.user_id.c_str(),
                               m_configInfo.password.c_str(),
                               "*", // 所有市场
                               "*", // 所有证券
                               onContractListCallback,
                               this);

    if (ret == SIPE_OK)
    {
        WTSLogger::info("ParserZC symbol list request sent successfully");
        return true;
    }
    else
    {
        logSipError(ret, "INFO_GetCodes");
        return false;
    }
}

void _cdecl ParserZC::onServerListCallback(T_ONLINEUISVR svrs[], unsigned int count, void *pParam)
{
    ParserZC *pParser = static_cast<ParserZC *>(pParam);
    if (pParser == nullptr)
        return;

    WTSLogger::info("ParserZC received server list with {} servers", count);

    for (unsigned int i = 0; i < count; i++)
    {
        const T_ONLINEUISVR &svr = svrs[i];
        WTSLogger::info("ParserZC server {}: {}:{} - {} (connections: {})",
                        i, svr.wanip, svr.wport, svr.svrname, svr.connum);
    }
}

void _cdecl ParserZC::onContractListCallback(T_SCITEMEX contracts[], unsigned int count, void *pParam)
{
    ParserZC *pParser = static_cast<ParserZC *>(pParam);
    if (pParser == nullptr)
        return;

    WTSLogger::info("ParserZC received contract list with {} contracts", count);

    StdUniqueLock lock(pParser->m_mtxInstruments);

    for (unsigned int i = 0; i < count; i++)
    {
        const T_SCITEMEX &contract = contracts[i];

        // 构造标签名：市场代码.证券代码.数据类型
        std::string tag_name = std::string(contract.mkcode) + "." +
                               std::string(contract.sccode) + "." +
                               std::string(contract.sctype);
        std::string instrument_code = pParser->parseInstrumentCode(tag_name.c_str());

        if (!instrument_code.empty())
        {
            ZCInstrumentInfo info;
            info.tag_name = tag_name;
            info.instrument_code = instrument_code;
            info.exchange_code = pParser->extractMarketFromTag(tag_name.c_str());
            info.is_subscribed = false;

            pParser->m_mapInstruments[instrument_code] = info;

            if (i < 10) // 只记录前10个合约的详细信息
            {
                WTSLogger::info("ParserZC contract {}: {} -> {} ({})",
                                i, tag_name, instrument_code, contract.name);
            }
        }
    }

    WTSLogger::info("ParserZC loaded {} valid contracts", pParser->m_mapInstruments.size());
}

//////////////////////////////////////////////////////////////////////////
// 订阅管理方法实现

bool ParserZC::doSubscribe(const CodeSet &codes)
{
    if (codes.empty() || m_hSipHandle == INVALID_SIPHANDLE)
        return false;

    // 构造sipsi2的订阅标签结构
    std::vector<T_SSCTAG> tags;
    tags.reserve(codes.size());

    for (const auto &code : codes)
    {
        T_SSCTAG tag;
        memset(&tag, 0, sizeof(tag));

        // 将WonderTrader格式的代码转换为sipsi2标签格式
        std::string tagName = convertToSipTagName(code);
        if (tagName.empty())
        {
            WTSLogger::warn("ParserZC invalid code format: {}", code);
            continue;
        }

        strncpy(tag.sTag, tagName.c_str(), sizeof(tag.sTag) - 1);
        tag.cMode = SSC_MODE_INC; // 增量订阅模式
        tag.uSeqNo = -1; // 参考demo设置序列号
        tags.push_back(tag);

        // 更新本地订阅状态
        {
            StdUniqueLock lock(m_mtxInstruments);
            ZCInstrumentInfo &info = m_mapInstruments[code];
            info.instrument_code = code;
            info.is_subscribed = true;
            info.sub_time = TimeUtils::getLocalTimeNow();
        }

        WTSLogger::info("ParserZC subscribing: {} -> {} (mode={}, seqno={})",
                       code, tagName, tag.cMode, tag.uSeqNo);
    }

    if (tags.empty())
    {
        WTSLogger::warn("ParserZC doSubscribe: no valid codes to subscribe");
        return false;
    }

    // 调用sipsi2Api订阅
    SIPRET ret = UI_SubscribeTags(m_hSipHandle, tags.data(), tags.size());
    if (ret == SIPE_OK)
    {
        // 更新订阅状态为已订阅
        {
            StdUniqueLock lock(m_mtxInstruments);
            for (const auto &code : codes)
            {
                auto it = m_mapInstruments.find(code);
                if (it != m_mapInstruments.end())
                {
                    it->second.is_subscribed = true;
                }
            }
        }

        WTSLogger::info("ParserZC subscribed {} instruments successfully", codes.size());
        return true;
    }
    else
    {
        logSipError(ret, "UI_SubscribeTags");

        // 更新订阅状态为失败
        {
            StdUniqueLock lock(m_mtxInstruments);
            for (const auto &code : codes)
            {
                auto it = m_mapInstruments.find(code);
                if (it != m_mapInstruments.end())
                {
                    it->second.is_subscribed = false;
                }
            }
        }
        return false;
    }
}

bool ParserZC::doUnsubscribe(const CodeSet &codes)
{
    if (codes.empty() || m_hSipHandle == INVALID_SIPHANDLE)
        return false;

    // 构造sipsi2的取消订阅标签结构
    std::vector<T_SSCTAG> tags;
    tags.reserve(codes.size());

    for (const auto &code : codes)
    {
        // 检查是否已订阅
        {
            StdUniqueLock lock(m_mtxInstruments);
            auto it = m_mapInstruments.find(code);
            if (it == m_mapInstruments.end() || !it->second.is_subscribed)
            {
                WTSLogger::warn("ParserZC code not subscribed: {}", code);
                continue;
            }
            it->second.is_subscribed = false;
        }

        T_SSCTAG tag;
        memset(&tag, 0, sizeof(tag));

        std::string tagName = convertToSipTagName(code);
        if (tagName.empty())
            continue;

        strncpy(tag.sTag, tagName.c_str(), sizeof(tag.sTag) - 1);
        tags.push_back(tag);

        WTSLogger::debug("ParserZC unsubscribing: {} -> {}", code, tagName);
    }

    if (tags.empty())
        return true; // 没有需要取消订阅的

    // 调用sipsi2Api取消订阅
    SIPRET ret = UI_UnSubscribeTags(m_hSipHandle, tags.data(), tags.size());
    if (ret == SIPE_OK)
    {
        // 从本地映射中移除
        {
            StdUniqueLock lock(m_mtxInstruments);
            for (const auto &code : codes)
            {
                m_mapInstruments.erase(code);
            }
        }

        WTSLogger::info("ParserZC unsubscribed {} instruments successfully", codes.size());
        return true;
    }
    else
    {
        logSipError(ret, "UI_UnSubscribeTags");

        // 恢复订阅状态
        {
            StdUniqueLock lock(m_mtxInstruments);
            for (const auto &code : codes)
            {
                auto it = m_mapInstruments.find(code);
                if (it != m_mapInstruments.end())
                {
                    it->second.is_subscribed = true;
                }
            }
        }
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////
// 数据转换方法实现

WTSTickData *ParserZC::parseTickData(T_SIPTAGMSG *pMsg)
{
    if (pMsg == nullptr || pMsg->MsgDataSize == 0)
        return nullptr;

    try
    {
        // 解析合约代码
        std::string instrument = parseInstrumentCode(pMsg->Code);
        if (instrument.empty())
        {
            WTSLogger::debug("ParserZC parseTickData: invalid instrument code from {}", pMsg->Code);
            return nullptr;
        }

        // 根据消息类型分发到具体的解析方法
        uint16_t msgType = pMsg->MsgType;

        WTSLogger::debug("ParserZC parsing message type {} for {}", msgType, instrument);

        switch (msgType)
        {
        // 上海证券交易所
        case ZC_MSG_SH_INDEX:   // 1000 - 上证指数快照
        case ZC_MSG_SZ_INDEX:   // 2000 - 深证指数快照
        case ZC_MSG_ZZZS_INDEX: // 7002 - 中证指数快照
            return parseIndexData(pMsg, instrument);

        case ZC_MSG_SH_TRANSACTION: // 1001 - 上证逐笔成交
        case ZC_MSG_SZ_TRANSACTION: // 2001 - 深证逐笔成交
            return parseTransactionData(pMsg, instrument);

        case ZC_MSG_SH_ORDER_QUEUE: // 1002 - 上证委托队列快照
        case ZC_MSG_SZ_ORDER_QUEUE: // 2002 - 深证委托队列快照
            return parseOrderQueueData(pMsg, instrument);

        case ZC_MSG_SH_L2_SNAPSHOT: // 1004 - 上证L2快照
        case ZC_MSG_SZ_L2_SNAPSHOT: // 2004 - 深证L2快照
            return parseStockL2Data(pMsg, instrument);

        case ZC_MSG_SH_L1_SNAPSHOT: // 1005 - 上证L1快照
        case ZC_MSG_SZ_L1_SNAPSHOT: // 2005 - 深证L1快照
            return parseStockL1Data(pMsg, instrument);

        // 期货交易所
        case ZC_MSG_CFFEX_SNAPSHOT: // 3002 - 中金所行情快照
        case ZC_MSG_CZCE_SNAPSHOT:  // 4002 - 郑商所行情快照
        case ZC_MSG_DCE_SNAPSHOT:   // 5002 - 大商所行情快照
        case ZC_MSG_SHFE_SNAPSHOT:  // 6002 - 上期所行情快照
            return parseFutureData(pMsg, instrument);

        // 期权
        case ZC_MSG_SHOP_SNAPSHOT: // 8002 - 上交所期权行情快照
        case ZC_MSG_SZOP_SNAPSHOT: // 11002 - 深交所期权行情快照
            return parseOptionData(pMsg, instrument);

        // 港股
        case ZC_MSG_HK_L1_SNAPSHOT: // 9004 - 港股L1快照
        case ZC_MSG_HK_L2_SNAPSHOT: // 9001 - 港股L2快照
            return parseHKData(pMsg, instrument);

        default:
            WTSLogger::warn("ParserZC unsupported message type {} for {}", msgType, instrument);
            return nullptr;
        }
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC parseTickData exception: {}", e.what());
        return nullptr;
    }
}

std::string ParserZC::parseInstrumentCode(const char *tag_name)
{
    if (tag_name == nullptr || strlen(tag_name) == 0)
        return "";

    // sipsi2的标签格式通常为: 市场.代码.字段
    // 例如: SH.600000.last (上海600000的最新价)
    //       SHFE.cu2301.last (上期所铜2301合约的最新价)

    std::string tagStr(tag_name);
    std::vector<std::string> parts = StrUtil::split(tagStr, ".");

    if (parts.size() < 3)
        return "";

    std::string market = parts[0];
    std::string code = parts[1];

    // 转换为WonderTrader标准格式: 代码.市场
    if (market == "SH")
        return code + ".SSE";
    else if (market == "SZ")
        return code + ".SZSE";
    else if (market == "SHFE")
        return code + ".SHFE";
    else if (market == "DCE")
        return code + ".DCE";
    else if (market == "CZCE")
        return code + ".CZCE";
    else if (market == "CFFEX")
        return code + ".CFFEX";
    else
        return code + "." + market;
}

std::string ParserZC::convertToSipTagName(const std::string &wtCode)
{
    // 默认使用L1数据类型
    return convertWonderTraderToZCFormat(wtCode, "L1");
}

std::string ParserZC::convertWonderTraderToZCFormat(const std::string &wtCode, const std::string &dataType)
{
    // 将WonderTrader格式转换为中畅标签格式
    // WonderTrader格式: 代码.交易所 (如: 600000.SSE, cu2301.SHFE)
    // 中畅格式: 交易所.代码.数据类型 (如: SH.600000.L1, SHFE.cu2301.L1)

    std::vector<std::string> parts = StrUtil::split(wtCode, ".");
    if (parts.size() != 2)
        return "";

    std::string code = parts[0];
    std::string wtExchange = parts[1];

    // 转换交易所代码
    std::string zcExchange = convertExchangeCode(wtExchange);
    if (zcExchange.empty())
        return "";

    // 确定最终的数据类型
    std::string finalDataType = determineFinalDataType(zcExchange, dataType);

    // 构建中畅格式标签
    return zcExchange + "." + code + "." + finalDataType;
}

std::string ParserZC::convertExchangeCode(const std::string &wtExchange)
{
    // WonderTrader交易所代码 -> 中畅交易所代码映射表
    static const std::map<std::string, std::string> exchangeMap = {
        {"SSE", "SH"},      // 上海证券交易所
        {"SZSE", "SZ"},     // 深圳证券交易所
        {"SHFE", "SHFE"},   // 上期所
        {"DCE", "DCE"},     // 大商所
        {"CZCE", "CZCE"},   // 郑商所
        {"CFFEX", "CFFEX"}, // 中金所
        {"SHOP", "SHOP"},   // 上交所期权
        {"SZOP", "SZOP"},   // 深交所期权
        {"HK", "HK"},       // 港股
        {"ZZZS", "ZZZS"}    // 中证指数
    };

    auto it = exchangeMap.find(wtExchange);
    return (it != exchangeMap.end()) ? it->second : "";
}

std::string ParserZC::determineFinalDataType(const std::string &zcExchange, const std::string &requestedType)
{
    // 根据中畅接入规范文档确定各市场支持的数据类型
    if (zcExchange == "SH" || zcExchange == "SZ")
    {
        // 股票市场支持的数据类型
        if (requestedType == "L1") return "L1";      // 5档快照 (消息类型1005/2005)
        if (requestedType == "L2") return "L2";      // 10档快照 (消息类型1004/2004)
        if (requestedType == "ZC") return "ZC";      // 逐笔成交 (消息类型1001/2001)
        if (requestedType == "ZW") return "ZW";      // 逐笔委托 (消息类型2003)
        if (requestedType == "WD") return "WD";      // 委托队列 (消息类型1002/2002)
        if (requestedType == "ZK") return "ZK";      // 指数快照 (消息类型1000/2000)
        return "L1"; // 默认使用L1
    }
    else if (zcExchange == "SHFE" || zcExchange == "DCE" ||
             zcExchange == "CZCE" || zcExchange == "CFFEX")
    {
        // 期货市场支持的数据类型
        if (requestedType == "L1") return "L1";      // 期货快照 (消息类型3002/4002/5002/6002)
        if (requestedType == "JC") return "JC";      // 基础信息
        return "L1"; // 默认使用L1
    }
    else if (zcExchange == "HK")
    {
        // 港股支持的数据类型
        if (requestedType == "L1") return "L1";      // 5档快照 (消息类型9004)
        if (requestedType == "L2") return "L2";      // 10档快照 (消息类型9001)
        if (requestedType == "ZK") return "ZK";      // 指数
        return "L1"; // 默认使用L1
    }
    else if (zcExchange == "SHOP" || zcExchange == "SZOP")
    {
        // 期权支持的数据类型
        if (requestedType == "L1") return "L1";      // 期权快照 (消息类型8002/11002)
        if (requestedType == "JC") return "JC";      // 基础信息
        return "L1"; // 默认使用L1
    }
    else if (zcExchange == "ZZZS")
    {
        // 中证指数支持的数据类型
        if (requestedType == "ZK") return "ZK";      // 指数快照 (消息类型7002)
        if (requestedType == "ZJ") return "ZJ";      // 指数基金参考净值
        return "ZK"; // 默认使用指数快照
    }

    // 未知市场，返回请求的类型或L1
    return requestedType.empty() ? "L1" : requestedType;
}

double ParserZC::checkValid(double val)
{
    // 与其他Parser保持完全一致的处理方式
    if (val == DBL_MAX || val == FLT_MAX)
        return 0;
    return val;
}

std::string ParserZC::extractMarketFromTag(const char *tag_name)
{
    if (tag_name == nullptr)
        return "";

    std::string tagStr(tag_name);
    auto pos = tagStr.find('.');
    if (pos != std::string::npos)
        return tagStr.substr(0, pos);
    else
        return "";
}

uint32_t ParserZC::getTradingDate()
{
    // 获取当前交易日期
    // 这里简化实现，实际应该根据交易日历计算
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);

    // 如果是凌晨时间(0-6点)，认为还是前一个交易日
    if (tm.tm_hour < 6)
    {
        time_t -= 24 * 3600; // 减去一天
        tm = *std::localtime(&time_t);
    }

    return (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
}

//////////////////////////////////////////////////////////////////////////
// 错误处理方法实现

void ParserZC::logSipError(SIPRET ret, const char *operation)
{
    const char *errMsg = getErrorMessage(ret);
    WTSLogger::error("ParserZC {} failed: {} ({})", operation, errMsg, ret);
    m_uErrorCount++;
}

const char *ParserZC::getErrorMessage(int error_code)
{
    auto it = m_mapErrorMessages.find(error_code);
    if (it != m_mapErrorMessages.end())
        return it->second.c_str();
    else
        return "Unknown error";
}

void ParserZC::initErrorMessages()
{
    // 初始化sipsi2错误码映射表
    m_mapErrorMessages[SIPE_OK] = "成功";
    m_mapErrorMessages[SIPE_ERR] = "一般错误";
    m_mapErrorMessages[SIPE_ERRHANDLE] = "无效句柄";
    m_mapErrorMessages[SIPE_TCPCONNECTERR] = "TCP连接错误";
    m_mapErrorMessages[SIPE_PROXY_CONNECTERR] = "代理连接错误";
    m_mapErrorMessages[SIPE_PROXY_AUTHERR] = "代理认证错误";
    m_mapErrorMessages[SIPE_DISCONNECT] = "连接断开";
    m_mapErrorMessages[SIPE_TCPIOERR] = "TCP IO错误";
    m_mapErrorMessages[SIPE_TCPMSGERR] = "TCP消息错误";
    m_mapErrorMessages[SIPE_TIMEOUT] = "超时";
    m_mapErrorMessages[SIPE_PGMERR] = "PGM错误";
    m_mapErrorMessages[SIPE_MCBERR] = "MCB错误";
    m_mapErrorMessages[SIPE_ASYNCONNECTOK] = "异步连接成功";
    m_mapErrorMessages[SIPE_ASYNCONNECTERR] = "异步连接错误";
    m_mapErrorMessages[SIPE_PKGFMT] = "数据包格式错误";
    m_mapErrorMessages[SIPE_PKGCODE] = "数据包代码错误";
    m_mapErrorMessages[SIPE_PKGDATA] = "数据包数据错误";
    m_mapErrorMessages[SIPE_VERSION] = "版本错误";
    m_mapErrorMessages[SIPE_NOUSER] = "用户不存在";
    m_mapErrorMessages[SIPE_USERAUTH] = "用户认证失败";
    m_mapErrorMessages[SIPE_NOPOWER] = "权限不足";
    m_mapErrorMessages[SIPE_NOTAG] = "标签不存在";
    m_mapErrorMessages[SIPE_NODATA] = "无数据";
    m_mapErrorMessages[SIPE_MSGTYPE] = "消息类型错误";
    m_mapErrorMessages[SIPE_MSGSIZE] = "消息大小错误";
    m_mapErrorMessages[SIPE_DATALINE] = "数据线路错误";
    m_mapErrorMessages[SIPE_DSLCONFULL] = "DSL连接满";
    m_mapErrorMessages[SIPE_CONNECTFULL] = "连接数满";
    m_mapErrorMessages[SIPE_SSCFULL] = "SSC满";
    m_mapErrorMessages[SIPE_USERLOCKED] = "用户被锁定";
    m_mapErrorMessages[SIPE_ERRARGS] = "参数错误";
    m_mapErrorMessages[SIPE_DSLMAINEXIST] = "DSL主连接已存在";
    m_mapErrorMessages[SIPE_SVRMEMERR] = "服务器内存错误";
    m_mapErrorMessages[SIPE_SVREXIST] = "服务器已存在";
    m_mapErrorMessages[SIPE_TDAUSERERR] = "TDA用户错误";
    m_mapErrorMessages[SIPE_TAGNOTSUBSCRIPT] = "标签未订阅";
    m_mapErrorMessages[SIPE_TDAUSERFULL] = "TDA用户满";
    m_mapErrorMessages[SIPE_TDANOUSERID] = "TDA无用户ID";
    m_mapErrorMessages[SIPE_SYSTAG] = "系统标签";
    m_mapErrorMessages[SIPE_NOSVR] = "无服务器";
    m_mapErrorMessages[SIPE_CTRLCODE] = "控制码错误";
    m_mapErrorMessages[SIPE_CTRLOPTFULL] = "控制操作满";
    m_mapErrorMessages[SIPE_COOKIE] = "Cookie错误";
}

void ParserZC::checkConnectionStatus()
{
    if (!isConnected())
        return;

    // 更新心跳时间
    m_uLastHeartbeat = TimeUtils::getLocalTimeNow();

    // 这里可以添加连接健康检查逻辑
    // 例如发送心跳包、检查数据接收情况等
}

//////////////////////////////////////////////////////////////////////////
// 具体市场数据解析方法

WTSTickData *ParserZC::parseStockL1Data(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析股票L1快照数据 (消息类型1005, 2005)
    WTSLogger::debug("ParserZC parsing stock L1 data for {}", instrument);

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    try
    {
        // 检查消息数据有效性
        if (pMsg == nullptr || pMsg->MsgData == nullptr)
        {
            WTSLogger::error("ParserZC parseStockL1Data: invalid message data");
            tick->release();
            return nullptr;
        }

        // 将消息数据转换为股票L1结构
        T_SH_StockMarketDataL1 *pL1Data = (T_SH_StockMarketDataL1 *)pMsg->MsgData;
        WTSTickStruct &ts = tick->getTickStruct();

        // 设置时间信息
        ts.action_date = pL1Data->nActionDay;
        ts.action_time = pL1Data->nTime;
        ts.trading_date = getTradingDate();

        // 设置价格信息，使用checkValid处理异常值
        ts.price = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uMatch));           // 最新价
        ts.open = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uOpen));             // 开盘价
        ts.high = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uHigh));             // 最高价
        ts.low = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uLow));               // 最低价
        ts.pre_close = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uPreClose));    // 昨收价
        ts.upper_limit = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uHighLimited)); // 涨停价
        ts.lower_limit = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uLowLimited));  // 跌停价

        // 设置成交量信息
        ts.total_volume = (double)pL1Data->iVolume;           // 总成交量
        ts.volume = 0;                                        // 当前成交量(L1数据中没有)
        ts.total_turnover = (double)pL1Data->iTurnover / 10000.0; // 总成交额(分转元)
        ts.turn_over = 0.0;                                   // 当前成交额

        // 股票没有持仓概念
        ts.open_interest = 0;
        ts.diff_interest = 0;
        ts.pre_interest = 0;
        ts.settle_price = 0;
        ts.pre_settle = 0;

        // 设置买卖盘信息（5档）
        for (int i = 0; i < 5; i++)
        {
            ts.bid_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uBidPrice[i])); // 买价
            ts.ask_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pL1Data->uAskPrice[i])); // 卖价
            ts.bid_qty[i] = (double)pL1Data->uBidVol[i];                              // 买量
            ts.ask_qty[i] = (double)pL1Data->uAskVol[i];                              // 卖量
        }

        // 清空剩余档位
        for (int i = 5; i < 10; i++)
        {
            ts.bid_prices[i] = 0;
            ts.ask_prices[i] = 0;
            ts.bid_qty[i] = 0;
            ts.ask_qty[i] = 0;
        }

        // 增加tick计数
        m_uTickCount++;

        // 详细调试信息
        WTSLogger::debug("ParserZC parsed stock L1 tick: {} price={:.4f} volume={} time={} status={}",
                         tick->code(), ts.price, ts.total_volume, ts.action_time, pL1Data->nStatus);

        // 打印买卖盘信息用于调试
        WTSLogger::debug("ParserZC L1 bid/ask: bid1={:.4f}({}) ask1={:.4f}({})",
                         ts.bid_prices[0], (uint64_t)ts.bid_qty[0],
                         ts.ask_prices[0], (uint64_t)ts.ask_qty[0]);

        return tick;
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC parseStockL1Data exception: {}", e.what());
        tick->release();
        return nullptr;
    }
}

WTSTickData *ParserZC::parseStockL2Data(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析股票L2快照数据 (消息类型1004, 2004)
    WTSLogger::debug("ParserZC parsing stock L2 data for {}", instrument);

    if (pMsg == nullptr || pMsg->MsgData == nullptr)
    {
        WTSLogger::error("ParserZC parseStockL2Data: invalid message data");
        return nullptr;
    }

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    try
    {
        // 将消息数据转换为股票L2结构
        T_SH_StockMarketDataL2 *pL2Data = (T_SH_StockMarketDataL2 *)pMsg->MsgData;
        WTSTickStruct &ts = tick->getTickStruct();

        // 设置时间信息
        ts.action_date = pL2Data->nActionDay;
        ts.action_time = pL2Data->nTime;
        ts.trading_date = getTradingDate();

        // 设置价格信息，使用checkValid处理异常值
        ts.price = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uMatch));           // 最新价
        ts.open = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uOpen));             // 开盘价
        ts.high = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uHigh));             // 最高价
        ts.low = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uLow));               // 最低价
        ts.pre_close = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uPreClose));    // 昨收价
        ts.upper_limit = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uHighLimited)); // 涨停价
        ts.lower_limit = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uLowLimited));  // 跌停价

        // 设置成交量信息
        ts.total_volume = (double)pL2Data->iVolume;           // 总成交量
        ts.volume = 0;                                        // 当前成交量
        ts.total_turnover = (double)pL2Data->iTurnover / 10000.0; // 总成交额(分转元)
        ts.turn_over = 0.0;                                   // 当前成交额

        // 股票没有持仓概念
        ts.open_interest = 0;
        ts.diff_interest = 0;
        ts.pre_interest = 0;
        ts.settle_price = 0;
        ts.pre_settle = 0;

        // 设置买卖盘信息（10档）
        for (int i = 0; i < 10; i++)
        {
            ts.bid_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uBidPrice[i])); // 买价
            ts.ask_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pL2Data->uAskPrice[i])); // 卖价
            ts.bid_qty[i] = (double)pL2Data->uBidVol[i];                              // 买量
            ts.ask_qty[i] = (double)pL2Data->uAskVol[i];                              // 卖量
        }

        // 增加tick计数
        m_uTickCount++;

        // 详细调试信息
        WTSLogger::debug("ParserZC parsed stock L2 tick: {} price={:.4f} volume={} time={} status={}",
                         tick->code(), ts.price, ts.total_volume, ts.action_time, pL2Data->nStatus);

        // 打印买卖盘信息用于调试
        WTSLogger::debug("ParserZC L2 bid/ask: bid1={:.4f}({}) ask1={:.4f}({})",
                         ts.bid_prices[0], (uint64_t)ts.bid_qty[0],
                         ts.ask_prices[0], (uint64_t)ts.ask_qty[0]);

        return tick;
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC parseStockL2Data exception: {}", e.what());
        tick->release();
        return nullptr;
    }
}

WTSTickData *ParserZC::parseFutureData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析期货快照数据 (消息类型3002, 4002, 5002, 6002)
    WTSLogger::debug("ParserZC parsing future data for {}", instrument);

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    try
    {
        // 检查消息数据有效性
        if (pMsg == nullptr || pMsg->MsgData == nullptr)
        {
            WTSLogger::error("ParserZC parseFutureData: invalid message data");
            tick->release();
            return nullptr;
        }

        // 将消息数据转换为期货结构
        T_SHFE_FutursMarketData *pFutureData = (T_SHFE_FutursMarketData *)pMsg->MsgData;
        WTSTickStruct &ts = tick->getTickStruct();

        // 设置时间信息
        ts.action_date = pFutureData->nActionDay;
        ts.action_time = pFutureData->nTime;
        ts.trading_date = pFutureData->nTradingDay;

        // 设置价格信息，使用checkValid处理异常值
        ts.price = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uMatch));           // 最新价
        ts.open = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uOpen));             // 开盘价
        ts.high = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uHigh));             // 最高价
        ts.low = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uLow));               // 最低价
        ts.pre_close = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uPreClose));    // 昨收价
        ts.upper_limit = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uHighLimited)); // 涨停价
        ts.lower_limit = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uLowLimited));  // 跌停价

        // 设置结算价信息，与其他Parser保持一致的处理方式
        ts.settle_price = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uSettlePrice));    // 今结算价
        ts.pre_settle = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uPreSettlePrice));   // 昨结算价

        // 设置成交量信息
        ts.total_volume = (double)pFutureData->iVolume;           // 总成交量
        ts.volume = 0;                                            // 当前成交量
        ts.total_turnover = (double)pFutureData->iTurnover / 10000.0; // 总成交额(分转元)
        ts.turn_over = 0.0;                                       // 当前成交额

        // 设置持仓信息
        ts.open_interest = (double)pFutureData->iOpenInterest;    // 总持仓
        ts.pre_interest = (double)pFutureData->iPreOpenInterest;  // 昨持仓
        ts.diff_interest = ts.open_interest - ts.pre_interest;    // 增仓

        // 设置买卖盘信息（5档）
        for (int i = 0; i < 5; i++)
        {
            ts.bid_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uBidPrice[i])); // 买价
            ts.ask_prices[i] = checkValid(ZC_PRICE_TO_DOUBLE(pFutureData->uAskPrice[i])); // 卖价
            ts.bid_qty[i] = (double)pFutureData->uBidVol[i];                              // 买量
            ts.ask_qty[i] = (double)pFutureData->uAskVol[i];                              // 卖量
        }

        // 清空剩余档位
        for (int i = 5; i < 10; i++)
        {
            ts.bid_prices[i] = 0;
            ts.ask_prices[i] = 0;
            ts.bid_qty[i] = 0;
            ts.ask_qty[i] = 0;
        }

        // 增加tick计数
        m_uTickCount++;

        // 详细调试信息
        WTSLogger::debug("ParserZC parsed future tick: {} price={:.4f} volume={} oi={} time={} status={}",
                         tick->code(), ts.price, ts.total_volume, ts.open_interest,
                         ts.action_time, pFutureData->nStatus);

        // 打印买卖盘信息用于调试
        WTSLogger::debug("ParserZC Future bid/ask: bid1={:.4f}({}) ask1={:.4f}({})",
                         ts.bid_prices[0], (uint64_t)ts.bid_qty[0],
                         ts.ask_prices[0], (uint64_t)ts.ask_qty[0]);

        return tick;
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC parseFutureData exception: {}", e.what());
        tick->release();
        return nullptr;
    }
}

WTSTickData *ParserZC::parseTransactionData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析逐笔成交数据 (消息类型1001, 2001)
    WTSLogger::debug("ParserZC parsing transaction data for {}", instrument);

    // 逐笔成交数据通常不转换为tick，而是通过handleTransaction回调处理
    // 这里返回nullptr表示不需要生成tick数据

    // TODO: 调用handleTransaction回调处理逐笔成交数据
    // if(m_pSpi) {
    //     m_pSpi->handleTransaction(...);
    // }

    return nullptr;
}

WTSTickData *ParserZC::parseOrderQueueData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析委托队列数据 (消息类型1002, 2002)
    WTSLogger::debug("ParserZC parsing order queue data for {}", instrument);

    // 委托队列数据通常不转换为tick，而是通过handleOrderQueue回调处理
    // 这里返回nullptr表示不需要生成tick数据

    // TODO: 调用handleOrderQueue回调处理委托队列数据
    // if(m_pSpi) {
    //     m_pSpi->handleOrderQueue(...);
    // }

    return nullptr;
}

WTSTickData *ParserZC::parseIndexData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析指数数据 (消息类型1000, 2000, 7002)
    WTSLogger::debug("ParserZC parsing index data for {}", instrument);

    if (pMsg == nullptr || pMsg->MsgData == nullptr)
    {
        WTSLogger::error("ParserZC parseIndexData: invalid message data");
        return nullptr;
    }

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    try
    {
        // 将消息数据转换为指数结构
        T_SH_StockIndex *pIndexData = (T_SH_StockIndex *)pMsg->MsgData;
        WTSTickStruct &ts = tick->getTickStruct();

        // 设置时间信息
        ts.action_date = pIndexData->nActionDay;
        ts.action_time = pIndexData->nTime;
        ts.trading_date = getTradingDate();

        // 设置价格信息，使用checkValid处理异常值
        ts.price = checkValid(ZC_PRICE_TO_DOUBLE(pIndexData->nLastIndex));        // 最新指数
        ts.open = checkValid(ZC_PRICE_TO_DOUBLE(pIndexData->nOpenIndex));         // 开盘指数
        ts.high = checkValid(ZC_PRICE_TO_DOUBLE(pIndexData->nHighIndex));         // 最高指数
        ts.low = checkValid(ZC_PRICE_TO_DOUBLE(pIndexData->nLowIndex));           // 最低指数
        ts.pre_close = checkValid(ZC_PRICE_TO_DOUBLE(pIndexData->nPreCloseIndex)); // 昨收指数

        // 指数没有涨跌停概念
        ts.upper_limit = 0;
        ts.lower_limit = 0;

        // 设置成交量信息
        ts.total_volume = (double)pIndexData->iTotalVolume;      // 总成交量
        ts.volume = 0;                                           // 当前成交量
        ts.total_turnover = (double)pIndexData->iTurnover / 10000.0; // 总成交额(分转元)
        ts.turn_over = 0.0;                                      // 当前成交额

        // 指数没有持仓概念
        ts.open_interest = 0;
        ts.diff_interest = 0;
        ts.pre_interest = 0;
        ts.settle_price = 0;
        ts.pre_settle = 0;

        // 指数没有买卖盘
        for (int i = 0; i < 10; i++)
        {
            ts.bid_prices[i] = 0;
            ts.ask_prices[i] = 0;
            ts.bid_qty[i] = 0;
            ts.ask_qty[i] = 0;
        }

        // 增加tick计数
        m_uTickCount++;

        // 详细调试信息
        WTSLogger::debug("ParserZC parsed index tick: {} price={:.4f} volume={} time={}",
                         tick->code(), ts.price, ts.total_volume, ts.action_time);

        return tick;
    }
    catch (const std::exception &e)
    {
        WTSLogger::error("ParserZC parseIndexData exception: {}", e.what());
        tick->release();
        return nullptr;
    }
}

WTSTickData *ParserZC::parseOptionData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析期权数据 (消息类型8002, 11002)
    WTSLogger::debug("ParserZC parsing option data for {}", instrument);

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    // TODO: 根据ZhongChang接入规范实现具体的期权数据解析

    // 设置基本信息
    tick->getTickStruct().trading_date = getTradingDate();

    WTSLogger::debug("ParserZC parsed option tick: {}", tick->code());
    return tick;
}

WTSTickData *ParserZC::parseHKData(T_SIPTAGMSG *pMsg, const std::string &instrument)
{
    // 解析港股数据 (消息类型9001, 9004)
    WTSLogger::debug("ParserZC parsing HK data for {}", instrument);

    // 创建WTSTickData对象
    WTSTickData *tick = WTSTickData::create(instrument.c_str());
    if (tick == nullptr)
        return nullptr;

    // TODO: 根据ZhongChang接入规范实现具体的港股数据解析

    // 设置基本信息
    tick->getTickStruct().trading_date = getTradingDate();

    WTSLogger::debug("ParserZC parsed HK tick: {}", tick->code());
    return tick;
}

//////////////////////////////////////////////////////////////////////////
// 辅助方法实现

ZCTimeInfo ParserZC::convertZCTime(T_I32 action_day, T_I32 time_stamp)
{
    ZCTimeInfo timeInfo;

    // 转换日期格式 YYYYMMDD
    timeInfo.action_date = static_cast<uint32_t>(action_day);

    // 转换时间格式 HHMMSSmmm
    timeInfo.action_time = static_cast<uint32_t>(time_stamp);

    // 设置交易日期
    timeInfo.trading_date = getTradingDate();

    return timeInfo;
}



void ParserZC::setTickBasicInfo(WTSTickData *tick, const ZCTimeInfo &time_info, const std::string &instrument)
{
    if (tick == nullptr)
        return;

    WTSTickStruct &ts = tick->getTickStruct();

    // 设置时间信息
    ts.action_date = time_info.action_date;
    ts.action_time = time_info.action_time;
    ts.trading_date = time_info.trading_date;

    // 增加tick计数
    m_uTickCount++;

    WTSLogger::debug("ParserZC setTickBasicInfo: {} date={} time={}",
                     instrument, ts.action_date, ts.action_time);
}

bool ParserZC::doConnect()
{
    if (m_hSipHandle == INVALID_SIPHANDLE)
    {
        WTSLogger::error("ParserZC doConnect failed: invalid handle");
        return false;
    }

    m_connectionStatus = ZC_CS_CONNECTING;

    SIPRET ret = UI_Connect(m_hSipHandle,
                            m_configInfo.server_ip.c_str(),
                            m_configInfo.server_port,
                            m_configInfo.user_id.c_str(),
                            m_configInfo.password.c_str(),
                            m_configInfo.login_mode,
                            m_configInfo.async_connect);

    if (ret == SIPE_OK)
    {
        // 验证连接状态（参考demo实现）
        if (!UI_IsConnect(m_hSipHandle))
        {
            WTSLogger::error("ParserZC doConnect: UI_IsConnect verification failed");
            m_connectionStatus = ZC_CS_ERROR;
            return false;
        }

        if (!m_configInfo.async_connect)
        {
            m_connectionStatus = ZC_CS_LOGGEDIN;
            WTSLogger::info("ParserZC connected successfully (sync mode)");

            if (m_pSpi)
            {
                m_pSpi->handleEvent(WPE_Connect, 0);
            }
        }
        else
        {
            WTSLogger::info("ParserZC connecting (async mode)...");
        }
        return true;
    }
    else
    {
        m_connectionStatus = ZC_CS_ERROR;
        logSipError(ret, "UI_Connect");
        return false;
    }
}

void ParserZC::doDisconnect()
{
    if (m_hSipHandle != INVALID_SIPHANDLE)
    {
        // 取消所有订阅
        UI_UnSubscribeAll(m_hSipHandle);

        // 断开连接
        UI_Disconnect(m_hSipHandle);

        m_connectionStatus = ZC_CS_DISCONNECTED;
        WTSLogger::info("ParserZC disconnected");

        if (m_pSpi)
        {
            m_pSpi->handleEvent(WPE_Close, 0);
        }
    }
}

// 导出函数实现
extern "C"
{
    EXPORT_FLAG IParserApi *createParser()
    {
        ParserZC *parser = new ParserZC();
        return parser;
    }

    EXPORT_FLAG void deleteParser(IParserApi *&parser)
    {
        if (parser != nullptr)
        {
            parser->release();
            delete parser;
            parser = nullptr;
        }
    }
}