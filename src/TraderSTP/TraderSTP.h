/*!
 * \file TraderSTP.h
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2024/03/21
 * 
 * \brief 
 */
#pragma once

#include <string>
#include <queue>
#include <stdint.h>

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
		WS_NOTLOGIN,		//未登录
		WS_LOGINING,		//正在登录
		WS_LOGINED,			//已登录
		WS_LOGINFAILED,		//登录失败
		WS_ALLREADY			//全部就绪
	} WrapperState;

private:
	int doLogin();

	//////////////////////////////////////////////////////////////////////////
	//ITraderApi接口
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

	virtual int orderInsert(WTSEntrust* eutrust) override;

	virtual int orderAction(WTSEntrustAction* action) override;

	virtual int queryAccount() override;

	virtual int queryPositions() override;

	virtual int queryOrders() override;

	virtual int queryTrades() override;

	virtual int querySettlement(uint32_t uDate) override;

	//////////////////////////////////////////////////////////////////////////
	//StpTradeSpi接口
public:
	virtual void OnFrontDisconnected(int nReason) override;

	virtual void OnRspOperatorLogin(StpRspLoginField* pRspLogin, int count, StpAccountInfoField* pAccountInfo, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnRspLogout(StpRspInfoField* pRspInfo) override;

	virtual void OnRspError(StpRspInfoField* pRspInfo) override;

	virtual void OnRtnOrder(StpOrderField* pOrder) override;

	virtual void OnRtnTrade(StpTradeField* pTrade) override;

	virtual void OnRspErrInsertOrder(StpOrderInsertReqField* pInputOrder, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnRspErrCancelOrder(StpOrderCancelReqField* pOrderAction, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnQryAccountAsset(StpUserAccountAssetField* pAccount, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnQryPosition(StpUserComboPositionField* pPosition, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnQryPositionDetail(StpPositionDetailField* pPosition, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnQryOrder(StpOrderField* pOrder, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

	virtual void OnQryTrade(StpTradeField* pTrade, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) override;

private:
	/*
	*	检查错误信息
	*/
	bool IsErrorRspInfo(StpRspInfoField *pRspInfo);

	int wrapPriceType(WTSPriceType priceType);
	int wrapDirectionType(WTSDirectionType dirType, WTSOffsetType offType);
	int wrapOffsetType(WTSOffsetType offType);
	int	wrapTimeCondition(WTSTimeCondition timeCond);
	int wrapActionFlag(WTSActionFlag actionFlag);

	WTSPriceType		wrapPriceType(char priceType);
	WTSDirectionType	wrapDirectionType(char dirType, char offType);
	WTSDirectionType	wrapPosDirection(char dirType);
	WTSOffsetType		wrapOffsetType(char offType);
	WTSTimeCondition	wrapTimeCondition(char timeCond);
	WTSOrderState		wrapOrderState(char orderState);

	WTSOrderInfo*	makeOrderInfo(StpOrderField* orderField);
	WTSEntrust*		makeEntrust(StpOrderInsertReqField *entrustField);
	WTSEntrustAction*	makeAction(StpOrderCancelReqField *entrustField);
	WTSError*		makeError(StpRspInfoField* rspInfo, WTSErroCode ec = WEC_NONE);
	WTSTradeInfo*	makeTradeInfo(StpTradeField *tradeField);

	void			generateEntrustID(char* buffer, uint32_t orderRef);
	bool			extractEntrustID(const char* entrustid, uint32_t &orderRef);

	uint32_t		genRequestID();

protected:
	std::string		m_strBroker;
	std::vector<std::string> m_strFront;

	std::string		m_strUser;
	std::string		m_strPass;

	std::string		m_strProdInfo;

	std::string		m_strTag;

	std::string		m_strUserName;
	std::string		m_strFlowDir;

	ITraderSpi*		m_sink;
	uint64_t		m_uLastQryTime;

	uint32_t					m_lDate;
	std::atomic<uint32_t>		m_orderRef;		//报单引用

	WrapperState				m_wrapperState;

	StpTradeApi*				m_pUserAPI;
	std::atomic<uint32_t>		m_iRequestID;

	typedef WTSHashMap<std::string> PositionMap;
	PositionMap*				m_mapPosition;
	WTSArray*					m_ayTrades;
	WTSArray*					m_ayOrders;
	WTSArray*					m_ayPosDetail;

	IBaseDataMgr*				m_bdMgr;

	typedef std::queue<CommonExecuter>	QueryQue;
	QueryQue				m_queQuery;
	bool					m_bInQuery;
	StdUniqueMutex			m_mtxQuery;
	uint64_t				m_lastQryTime;

	bool					m_bStopped;
	StdThreadPtr			m_thrdWorker;

	std::string		m_strModule;
	DllHandle		m_hInstSTP;
	typedef StpTradeApi* (*STPCreator)(const char *);
	STPCreator		m_funcCreator;

	//委托单标记缓存器
	WtKVCache		m_eidCache;
	//订单标记缓存器
	WtKVCache		m_oidCache;
};
