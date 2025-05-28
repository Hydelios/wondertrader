/*!
 * \file TraderSTP.h
 * \project	WonderTrader
 *
 * \author YourName
 * \date 2025/05/27
 *
 * \brief STP交易接口头文件，实现ITraderApi标准接口
 */
#pragma once

#include <string>
#include <queue>
#include <atomic>

#include "../Includes/WTSTypes.h"
#include "../Includes/ITraderApi.h"
#include "../Includes/WTSCollection.hpp"

#include "../API/stp/include/StpTradeApi.h"

#include "../Share/StdUtils.hpp"
#include "../Share/DLLHelper.hpp"
#include "../Share/WtKVCache.hpp"

USING_NS_WTP;

class TraderSTP : public ITraderApi, public StpTradeSpi
{
public:
	TraderSTP();
	virtual ~TraderSTP();

public:
	typedef enum
	{
		WS_NOTLOGIN,
		WS_LOGINING,
		WS_LOGINED,
		WS_LOGINFAILED,
		WS_CONFIRMED,
		WS_ALLREADY
	} WrapperState;

private:
	int authenticate();
	int doLogin();

	//////////////////////////////////////////////////////////////////////////
	// ITraderApi 接口实现
public:
	virtual bool init(WTSVariant* params) override;

	virtual void release() override;

	virtual void registerSpi(ITraderSpi *listener) override;

	virtual bool makeEntrustID(char* buffer, int length) override;

	virtual void connect() override;

	virtual void disconnect() override;

	virtual bool isConnected() override;

	virtual int login(const char* user, const char* pass, const char* productInfo) override;

	virtual int logout() override;

	virtual int orderInsert(WTSEntrust* entrust) override;

	virtual int orderAction(WTSEntrustAction* action) override;

	virtual int queryAccount() override;

	virtual int queryPositions() override;

	virtual int queryOrders() override;

	virtual int queryTrades() override;

	//////////////////////////////////////////////////////////////////////////
	// STP 协议事件回调接口（按你的 STP SDK 替换或填充）
public:
	void onSTPConnected();
	void onSTPDisconnected(int reason);
	void onLoginResponse(bool success, const std::string& msg);
	void onLogoutResponse(bool success, const std::string& msg);

	void onAccountInfo(const WTSVariant* account);
	void onPositionInfo(const WTSVariant* position);
	void onOrderInfo(const WTSVariant* order);
	void onTradeInfo(const WTSVariant* trade);

	void onOrderAccepted(const std::string& localid);
	void onOrderRejected(const std::string& localid, const std::string& reason);
	void onOrderCanceled(const std::string& localid);
	void onTradeExecuted(const std::string& localid, const WTSVariant* trade);

protected:
	// 私有工具函数
	uint32_t genRequestID();
	void generateEntrustID(char* buffer, uint32_t uniqueID);
	bool extractEntrustID(const char* entrustid, uint32_t &uniqueID);

	WTSError* makeError(const std::string& msg);
	WTSOrderInfo* makeOrderInfoFromSTP(const WTSVariant* raw);
	WTSTradeInfo* makeTradeInfoFromSTP(const WTSVariant* raw);

protected:
	std::string		m_strServer;
	std::string		m_strUser;
	std::string		m_strPass;
	std::string		m_strProductInfo;
	std::string		m_strTag;

	ITraderSpi*		m_sink;

	WrapperState	m_wrapperState;
	std::atomic<uint32_t> m_requestID;
	std::atomic<uint32_t> m_localOrderID;

	bool			m_bConnected;
	bool			m_bLoggedIn;

	typedef std::queue<CommonExecuter> QueryQueue;
	QueryQueue		m_queQuery;
	bool			m_bInQuery;
	StdUniqueMutex	m_mtxQuery;
	uint64_t		m_lastQryTime;

	bool			m_bStopped;
	StdThreadPtr	m_thrdWorker;

	std::string		m_strModule;
	DllHandle		m_hInstSTP;

	// 标记缓存器
	WtKVCache		m_eidCache;
	WtKVCache		m_oidCache;
};
