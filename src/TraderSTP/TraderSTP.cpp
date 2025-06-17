/*!
 * \file TraderSTP.cpp
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2024/03/21
 * 
 * \brief 
 */
#include "TraderSTP.h"

#include "../Includes/WTSError.hpp"
#include "../Includes/WTSContractInfo.hpp"
#include "../Includes/WTSSessionInfo.hpp"
#include "../Includes/WTSTradeDef.hpp"
#include "../Includes/WTSDataDef.hpp"
#include "../Includes/WTSVariant.hpp"
#include "../Includes/IBaseDataMgr.h"

#include "../Share/decimal.h"
#include "../Share/ModuleHelper.hpp"

#include <boost/filesystem.hpp>

//By Wesley @ 2022.01.05
#include "../Share/fmtlib.h"
template<typename... Args>
inline void write_log(ITraderSpi* sink, WTSLogLevel ll, const char* format, const Args&... args)
{
	if (sink == NULL)
		return;

	const char* buffer = fmtutil::format(format, args...);

	sink->handleTraderLog(ll, buffer);
}

extern "C"
{
	EXPORT_FLAG ITraderApi* createTrader()
	{
		TraderSTP *instance = new TraderSTP();
		return instance;
	}

	EXPORT_FLAG void deleteTrader(ITraderApi* &trader)
	{
		if (NULL != trader)
		{
			delete trader;
			trader = NULL;
		}
	}
}

TraderSTP::TraderSTP()
	: m_pUserAPI(NULL)
	, m_mapPosition(NULL)
	, m_ayOrders(NULL)
	, m_ayTrades(NULL)
	, m_ayPosDetail(NULL)
	, m_wrapperState(WS_NOTLOGIN)
	, m_uLastQryTime(0)
	, m_iRequestID(0)
	, m_bInQuery(false)
	, m_bStopped(false)
	, m_lastQryTime(0)
{
}

TraderSTP::~TraderSTP()
{
	// 确保资源被正确清理
	release();

	// 清理动态库句柄
	if (m_hInstSTP)
	{
		DLLHelper::free_library(m_hInstSTP);
		m_hInstSTP = NULL;
	}
}

bool TraderSTP::init(WTSVariant* params)
{
	auto fontItem = params->get("front");
	if (fontItem)
	{
		if (fontItem->type() == WTSVariant::VT_String)
		{
			m_strFront.push_back(fontItem->asCString());
		}
		else if (fontItem->type() == WTSVariant::VT_Array)
		{
			for (uint32_t i = 0; i < fontItem->size(); i++)
			{
				m_strFront.push_back(fontItem->get(i)->asCString());
			}
		}
	}
	m_strBroker = params->get("broker")->asCString();
	m_strUser = params->get("user")->asCString();
	m_strPass = params->get("pass")->asCString();

	m_strFlowDir = params->getCString("flowdir");

	if (m_strFlowDir.empty())
		m_strFlowDir = "STPTDFlow";

	m_strFlowDir = StrUtil::standardisePath(m_strFlowDir);

	std::string module = params->getCString("stpmodule");
	if (module.empty())
		module = "stptradeapi";

	m_strModule = getBinDir() + DLLHelper::wrap_module(module.c_str(), "");

	m_hInstSTP = DLLHelper::load_library(m_strModule.c_str());
	if (!m_hInstSTP)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Failed to load STP library: {}", m_strModule);
		return false;
	}

#ifdef _WIN32
#	ifdef _WIN64
	const char* creatorName = "CreateStpTradeApi";
#	else
	const char* creatorName = "CreateStpTradeApi";
#	endif
#else
	const char* creatorName = "CreateStpTradeApi";
#endif
	m_funcCreator = (STPCreator)DLLHelper::get_symbol(m_hInstSTP, creatorName);
	if (!m_funcCreator)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Failed to get CreateStpTradeApi function from library");
		DLLHelper::free_library(m_hInstSTP);
		m_hInstSTP = NULL;
		return false;
	}

	return true;
}

void TraderSTP::release()
{
	m_bStopped = true;

	if (m_pUserAPI)
	{
		m_pUserAPI->Release();
		m_pUserAPI = NULL;
	}

	if (m_ayOrders)
		m_ayOrders->clear();

	if (m_ayPosDetail)
		m_ayPosDetail->clear();

	if (m_mapPosition)
		m_mapPosition->clear();

	if (m_ayTrades)
		m_ayTrades->clear();
}

void TraderSTP::connect()
{
	if (!m_funcCreator)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] STP library not loaded, cannot connect");
		return;
	}

	std::stringstream ss;
	ss << m_strFlowDir << "flows/" << m_strBroker << "/" << m_strUser << "/";
	boost::filesystem::create_directories(ss.str().c_str());

	m_pUserAPI = m_funcCreator(ss.str().c_str());
	if (!m_pUserAPI)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Failed to create STP API instance");
		return;
	}

	m_pUserAPI->RegisterSpi(this);
	m_pUserAPI->SubscribePublicTopic(STP_TERT_QUICK);		// 注册公有流
	m_pUserAPI->SubscribePrivateTopic(STP_TERT_QUICK);		// 注册私有流

	for (std::string front : m_strFront)
	{
		std::string::size_type pos = front.find(":");
		if (pos != std::string::npos)
		{
			std::string addr = front.substr(0, pos);
			uint16_t port = std::stoi(front.substr(pos + 1));
			m_pUserAPI->RegisterFront(addr.c_str(), port);
			m_sink->handleTraderLog(LL_INFO, fmtutil::format("registerFront: {}:{}", addr, port));
		}
	}

	if (m_pUserAPI)
	{
		m_pUserAPI->Init();
	}

	if (m_thrdWorker == NULL)
	{
		m_thrdWorker.reset(new StdThread([this](){
			while (!m_bStopped)
			{
				if(m_queQuery.empty() || m_bInQuery)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					continue;
				}

				uint64_t curTime = TimeUtils::getLocalTimeNow();
				if (curTime - m_lastQryTime < 1000)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					continue;
				}

				m_bInQuery = true;
				CommonExecuter& handler = m_queQuery.front();
				handler();

				{
					StdUniqueLock lock(m_mtxQuery);
					m_queQuery.pop();
				}

				m_lastQryTime = TimeUtils::getLocalTimeNow();
			}
		}));
	}
}

void TraderSTP::disconnect()
{
	m_queQuery.push([this]() {
		release();
	});

	if (m_thrdWorker)
	{
		m_thrdWorker->join();
		m_thrdWorker = NULL;
	}
}

bool TraderSTP::isConnected()
{
	return (m_wrapperState == WS_ALLREADY);
}

void TraderSTP::registerSpi(ITraderSpi *listener)
{
	m_sink = listener;
	if (m_sink)
	{
		m_bdMgr = listener->getBaseDataMgr();
	}
}

uint32_t TraderSTP::genRequestID()
{
	return m_iRequestID.fetch_add(1) + 1;
}

int TraderSTP::login(const char* user, const char* pass, const char* productInfo)
{
	m_strUser = user;
	m_strPass = pass;
	m_strProdInfo = productInfo;

	if (m_pUserAPI == NULL)
	{
		return -1;
	}

	m_wrapperState = WS_LOGINING;
	doLogin();

	return 0;
}

int TraderSTP::doLogin()
{
	StpOperatorLoginReqField req;
	memset(&req, 0, sizeof(req));
	wt_strcpy(req.LoginID, m_strUser.c_str(), sizeof(req.LoginID));
	wt_strcpy(req.Password, m_strPass.c_str(), sizeof(req.Password));
	int iResult = m_pUserAPI->ReqOperatorlogin(&req, genRequestID());
	if (iResult != 0)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Sending login request failed: {}", iResult);
	}

	return 0;
}

int TraderSTP::logout()
{
	if (m_pUserAPI == NULL)
	{
		return -1;
	}

	int iResult = m_pUserAPI->Logout();
	if (iResult != 0)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Sending logout request failed: {}", iResult);
	}

	return 0;
}

int TraderSTP::orderInsert(WTSEntrust* entrust)
{
	if (m_pUserAPI == NULL || m_wrapperState != WS_ALLREADY)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Trading channel not ready");
		return -1;
	}

	StpOrderInsertReqField req;
	memset(&req, 0, sizeof(req));
	wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
	wt_strcpy(req.OperatorID, m_strUser.c_str(), sizeof(req.OperatorID));
	wt_strcpy(req.InstrumentID, entrust->getCode(), sizeof(req.InstrumentID));
	wt_strcpy(req.ExchangeID, entrust->getExchg(), sizeof(req.ExchangeID));

	if (strlen(entrust->getUserTag()) == 0)
	{
		fmt::format_to(req.OrderRef, "{}", m_orderRef.fetch_add(1));
	}
	else
	{
		uint32_t orderref;
		extractEntrustID(entrust->getEntrustID(), orderref);
		fmt::format_to(req.OrderRef, "{}", orderref);
	}

	if (strlen(entrust->getUserTag()) > 0)
	{
		m_eidCache.put(entrust->getEntrustID(), entrust->getUserTag(), 0, [this](const char* message) {
			write_log(m_sink, LL_WARN, message);
		});
	}

	req.OrderPriceType = wrapPriceType(entrust->getPriceType());
	req.Direction = wrapDirectionType(entrust->getDirection(), entrust->getOffsetType());
	memset(req.CombOffsetFlag, 0, sizeof(req.CombOffsetFlag));
	req.CombOffsetFlag[0] = wrapOffsetType(entrust->getOffsetType());
	req.LimitPrice = entrust->getPrice();
	req.VolumeTotalOriginal = (int)entrust->getVolume();

	if(entrust->getOrderFlag() == WOF_NOR)
	{
		req.TimeCondition = STP_TC_GFD;  // '3' - 当日有效
		req.VolumeCondition = STP_VC_AV; // '1' - 任何数量
	}
	else if (entrust->getOrderFlag() == WOF_FAK)
	{
		req.TimeCondition = STP_TC_IOC;  // '1' - 立即完成，否则撤销
		req.VolumeCondition = STP_VC_AV; // '1' - 任何数量
	}
	else if (entrust->getOrderFlag() == WOF_FOK)
	{
		req.TimeCondition = STP_TC_IOC;  // '1' - 立即完成，否则撤销
		req.VolumeCondition = STP_VC_CV; // '3' - 全部数量
	}

	int iResult = m_pUserAPI->ReqInsertOrder(&req, genRequestID());
	if (iResult != 0)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Order inserting failed: {}", iResult);
	}

	return 0;
}

int TraderSTP::orderAction(WTSEntrustAction* action)
{
	if (m_wrapperState != WS_ALLREADY)
		return -1;

	uint32_t orderref;
	if (!extractEntrustID(action->getEntrustID(), orderref))
		return -1;

	StpOrderCancelReqField req;
	memset(&req, 0, sizeof(req));
	wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
	wt_strcpy(req.OperatorID, m_strUser.c_str(), sizeof(req.OperatorID));

	fmt::format_to(req.OrderRef, "{}", orderref);

	// 其他字段如OrderLocalID、OrderIP等可根据需要补充
	int iResult = m_pUserAPI->ReqCancelOrder(&req, genRequestID());
	if (iResult != 0)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Sending cancel request failed: {}", iResult);
	}

	return 0;
}

int TraderSTP::queryAccount()
{
	if (m_pUserAPI == NULL || m_wrapperState != WS_ALLREADY)
	{
		return -1;
	}

	{
		StdUniqueLock lock(m_mtxQuery);
		m_queQuery.push([this]() {
			StpQryAccountAssetField req;
			memset(&req, 0, sizeof(req));
			wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
			m_pUserAPI->ReqQryAccountAsset(&req, genRequestID());
		});
	}

	return 0;
}

int TraderSTP::queryPositions()
{
	if (m_pUserAPI == NULL || m_wrapperState != WS_ALLREADY)
	{
		return -1;
	}

	{
		StdUniqueLock lock(m_mtxQuery);
		m_queQuery.push([this]() {
			StpQryPositionField req;
			memset(&req, 0, sizeof(req));
			wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
			m_pUserAPI->ReqQryPosition(&req, genRequestID());
		});
	}

	return 0;
}

int TraderSTP::queryOrders()
{
	if (m_pUserAPI == NULL || m_wrapperState != WS_ALLREADY)
	{
		return -1;
	}

	{
		StdUniqueLock lock(m_mtxQuery);
		m_queQuery.push([this]() {
			StpQryOrderField req;
			memset(&req, 0, sizeof(req));
			wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
			m_pUserAPI->ReqQryOrder(&req, genRequestID());
		});
	}

	return 0;
}

int TraderSTP::queryTrades()
{
	if (m_pUserAPI == NULL || m_wrapperState != WS_ALLREADY)
	{
		return -1;
	}

	{
		StdUniqueLock lock(m_mtxQuery);
		m_queQuery.push([this]() {
			StpQryTradeField req;
			memset(&req, 0, sizeof(req));
			wt_strcpy(req.AccountID, m_strUser.c_str(), sizeof(req.AccountID));
			m_pUserAPI->ReqQryTrade(&req, genRequestID());
		});
	}

	return 0;
}

int TraderSTP::querySettlement(uint32_t uDate)
{
	return 0;
}

void TraderSTP::OnFrontDisconnected(int nReason)
{
	m_wrapperState = WS_NOTLOGIN;
	if (m_sink)
		m_sink->handleEvent(WTE_Close, nReason);
}

void TraderSTP::OnRspOperatorLogin(StpRspLoginField* pRspLogin, int count, StpAccountInfoField* pAccountInfo, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (!IsErrorRspInfo(pRspInfo))
	{
		m_wrapperState = WS_LOGINED;

		// 保存会话参数
		m_orderRef = 0;
		///获取当前交易日
		m_lDate = TimeUtils::getCurDate();

		write_log(m_sink, LL_INFO, "[TraderSTP][{}-{}] Login succeed, login time: {}...",
			m_strBroker.c_str(), m_strUser.c_str(), pRspLogin->LoginTime);

		{
			//初始化委托单缓存器
			std::stringstream ss;
			ss << m_strFlowDir << "local/" << m_strBroker << "/";
			std::string path = StrUtil::standardisePath(ss.str());
			if (!StdFile::exists(path.c_str()))
				boost::filesystem::create_directories(path.c_str());
			ss << m_strUser << "_eid.sc";
			m_eidCache.init(ss.str().c_str(), m_lDate, [this](const char* message) {
				write_log(m_sink, LL_WARN, message);
			});
		}

		{
			//初始化订单标记缓存器
			std::stringstream ss;
			ss << m_strFlowDir << "local/" << m_strBroker << "/";
			std::string path = StrUtil::standardisePath(ss.str());
			if (!StdFile::exists(path.c_str()))
				boost::filesystem::create_directories(path.c_str());
			ss << m_strUser << "_oid.sc";
			m_oidCache.init(ss.str().c_str(), m_lDate, [this](const char* message) {
				write_log(m_sink, LL_WARN, message);
			});
		}

		write_log(m_sink, LL_INFO, "[TraderSTP][{}-{}] Login succeed, trading date: {}...", m_strBroker.c_str(), m_strUser.c_str(), m_lDate);

		m_wrapperState = WS_ALLREADY;
		if (m_sink)
			m_sink->onLoginResult(true, "", m_lDate);
	}
	else
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP][{}-{}] Login failed: {}", m_strBroker.c_str(), m_strUser.c_str(), pRspInfo->ErrorMsg);
		m_wrapperState = WS_LOGINFAILED;

		if (m_sink)
			m_sink->onLoginResult(false, pRspInfo->ErrorMsg, 0);
	}
}

void TraderSTP::OnRspLogout(StpRspInfoField* pRspInfo)
{
	m_wrapperState = WS_NOTLOGIN;
	if (m_sink)
		m_sink->handleEvent(WTE_Logout, 0);
}

void TraderSTP::OnRspError(StpRspInfoField* pRspInfo)
{
	m_sink->handleTraderLog(LL_ERROR, fmtutil::format("Error: {} : {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg));
}

void TraderSTP::OnRtnOrder(StpOrderField* pOrder)
{
	WTSOrderInfo *orderInfo = makeOrderInfo(pOrder);
	if (orderInfo)
	{
		if (m_sink)
			m_sink->onPushOrder(orderInfo);

		orderInfo->release();
	}
}

void TraderSTP::OnRtnTrade(StpTradeField* pTrade)
{
	WTSTradeInfo *tRecord = makeTradeInfo(pTrade);
	if (tRecord)
	{
		if (m_sink)
			m_sink->onPushTrade(tRecord);

		tRecord->release();
	}
}

void TraderSTP::OnRspErrInsertOrder(StpOrderInsertReqField* pInputOrder, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	WTSEntrust* entrust = makeEntrust(pInputOrder);
	if (entrust)
	{
		WTSError *err = makeError(pRspInfo, WEC_ORDERINSERT);
		if (m_sink)
			m_sink->onRspEntrust(entrust, err);
		entrust->release();
		err->release();
	}
	else if(IsErrorRspInfo(pRspInfo))
	{
		WTSError *err = makeError(pRspInfo, WEC_ORDERINSERT);
		if (m_sink)
			m_sink->onTraderError(err);
		err->release();
	}
}

void TraderSTP::OnRspErrCancelOrder(StpOrderCancelReqField* pOrderAction, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (IsErrorRspInfo(pRspInfo))
	{
		WTSError* error = WTSError::create(WEC_ORDERCANCEL, pRspInfo->ErrorMsg);
		WTSEntrustAction* action = makeAction(pOrderAction);
		if (m_sink)
			m_sink->onTraderError(error, action);

		if (error)
			error->release();

		if (action)
			action->release();
	}
}

void TraderSTP::OnQryAccountAsset(StpUserAccountAssetField* pAccount, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (!IsErrorRspInfo(pRspInfo) && pAccount)
	{
		WTSAccountInfo* accountInfo = WTSAccountInfo::create();
		accountInfo->setBalance(pAccount->Balance);
		accountInfo->setAvailable(pAccount->EnableBalance);
		accountInfo->setCurrency("CNY");
		accountInfo->setDynProfit(pAccount->PositionProfit);
		accountInfo->setCloseProfit(pAccount->CloseProfit);
		accountInfo->setMargin(pAccount->OccupyMargin);
		accountInfo->setFrozenMargin(0);
		accountInfo->setFrozenCommission(0);
		accountInfo->setCommission(0);
		accountInfo->setDeposit(0);
		accountInfo->setWithdraw(0);

		WTSArray * ay = WTSArray::create();
		ay->append(accountInfo, false);
		if (m_sink)
			m_sink->onRspAccount(ay);

		ay->release();
	}
	else if (IsErrorRspInfo(pRspInfo))
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] Query account failed: {}", pRspInfo->ErrorMsg);
	}

	m_bInQuery = false;
}

void TraderSTP::OnQryPosition(StpUserComboPositionField* pPosition, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (!IsErrorRspInfo(pRspInfo) && pPosition)
	{
		if (NULL == m_mapPosition)
			m_mapPosition = PositionMap::create();

		WTSContractInfo* contract = m_bdMgr->getContract(pPosition->InstrumentID, pPosition->ExchangeID);
		if (contract)
		{
			WTSCommodityInfo* commInfo = contract->getCommInfo();
			std::string key = fmt::format("{}-{}", pPosition->InstrumentID, pPosition->PosiDirection);
			WTSPositionItem* pos = (WTSPositionItem*)m_mapPosition->get(key);
			if(pos == NULL)
			{
				pos = WTSPositionItem::create(pPosition->InstrumentID, commInfo->getCurrency(), commInfo->getExchg());
				pos->setContractInfo(contract);
				m_mapPosition->add(key, pos, false);
			}
			pos->setDirection(wrapPosDirection(pPosition->PosiDirection));
			pos->setNewPosition(pPosition->TodayPosition);
			pos->setPrePosition(pPosition->YdPosition);
			pos->setMargin(pos->getMargin() + pPosition->UseMargin);
			pos->setDynProfit(pos->getDynProfit() + pPosition->FloatProfit);
			pos->setPositionCost(pos->getPositionCost() + pPosition->PositionCost);

			if (pos->getTotalPosition() != 0)
			{
				pos->setAvgPrice(pos->getPositionCost() / pos->getTotalPosition() / commInfo->getVolScale());
			}
			else
			{
				pos->setAvgPrice(0);
			}

			// 可用数量直接用 EnableVolume 字段
			pos->setAvailNewPos(pPosition->EnableVolume);
			pos->setAvailPrePos(0);
		}
	}

	if (count == 0)
	{
		WTSArray* ayPos = WTSArray::create();

		if(m_mapPosition && m_mapPosition->size() > 0)
		{
			for (auto it = m_mapPosition->begin(); it != m_mapPosition->end(); it++)
			{
				ayPos->append(it->second, true);
			}
		}

		if (m_sink)
			m_sink->onRspPosition(ayPos);

		if (m_mapPosition)
		{
			m_mapPosition->release();
			m_mapPosition = NULL;
		}

		ayPos->release();
	}

	m_bInQuery = false;
}

void TraderSTP::OnQryPositionDetail(StpPositionDetailField* pPosition, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	m_bInQuery = false;
}

void TraderSTP::OnQryOrder(StpOrderField* pOrder, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (!IsErrorRspInfo(pRspInfo) && pOrder)
	{
		if (NULL == m_ayOrders)
			m_ayOrders = WTSArray::create();

		WTSOrderInfo* orderInfo = makeOrderInfo(pOrder);
		if (orderInfo)
		{
			m_ayOrders->append(orderInfo, false);
		}
	}

	if (count == 0)
	{
		if (m_sink)
			m_sink->onRspOrders(m_ayOrders);

		if (m_ayOrders)
			m_ayOrders->clear();
	}

	m_bInQuery = false;
}

void TraderSTP::OnQryTrade(StpTradeField* pTrade, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId)
{
	if (!IsErrorRspInfo(pRspInfo) && pTrade)
	{
		if (NULL == m_ayTrades)
			m_ayTrades = WTSArray::create();

		WTSTradeInfo* trade = makeTradeInfo(pTrade);
		if (trade)
		{
			m_ayTrades->append(trade, false);
		}
	}

	if (count == 0)
	{
		if (m_sink)
			m_sink->onRspTrades(m_ayTrades);

		if (NULL != m_ayTrades)
			m_ayTrades->clear();
	}

	m_bInQuery = false;
}

bool TraderSTP::IsErrorRspInfo(StpRspInfoField *pRspInfo)
{
	if (pRspInfo && pRspInfo->ErrorID != 0)
		return true;

	return false;
}

void TraderSTP::generateEntrustID(char* buffer, uint32_t orderRef)
{
	fmtutil::format_to(buffer, "{:06d}", orderRef);
}

bool TraderSTP::extractEntrustID(const char* entrustid, uint32_t &orderRef)
{
	orderRef = strtoul(entrustid, NULL, 10);
	return true;
}

bool TraderSTP::makeEntrustID(char* buffer, int length)
{
	if (buffer == NULL || length == 0)
		return false;

	try
	{
		memset(buffer, 0, length);
		uint32_t orderref = m_orderRef.fetch_add(1) + 1;
		fmt::format_to(buffer, "{:06d}", orderref);
		return true;
	}
	catch (const std::exception& e)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] makeEntrustID failed: {}", e.what());
	}
	catch (...)
	{
		write_log(m_sink, LL_ERROR, "[TraderSTP] makeEntrustID failed with unknown exception");
	}

	return false;
}

WTSOrderInfo* TraderSTP::makeOrderInfo(StpOrderField* orderField)
{
	WTSContractInfo* contract = m_bdMgr->getContract(orderField->InstrumentID, orderField->ExchangeID);
	if (contract == NULL)
		return NULL;

	WTSOrderInfo* pRet = WTSOrderInfo::create();
	pRet->setContractInfo(contract);
	pRet->setPrice(orderField->LimitPrice);
	pRet->setVolume(orderField->VolumeTotalOriginal);
	pRet->setDirection(wrapDirectionType(orderField->Direction, orderField->CombOffsetFlag[0]));
	pRet->setPriceType(wrapPriceType(orderField->OrderPriceType));
	pRet->setOffsetType(wrapOffsetType(orderField->CombOffsetFlag[0]));

	if (orderField->TimeCondition == STP_TC_GFD)
	{
		pRet->setOrderFlag(WOF_NOR);
	}
	else if (orderField->TimeCondition == STP_TC_IOC)
	{
		if (orderField->VolumeCondition == STP_VC_AV || orderField->VolumeCondition == STP_VC_MV)
			pRet->setOrderFlag(WOF_FAK);
		else
			pRet->setOrderFlag(WOF_FOK);
	}

	pRet->setVolTraded(orderField->VolumeTraded);
	pRet->setVolLeft(orderField->VolumeTotalOriginal - orderField->VolumeTraded);

	pRet->setCode(orderField->InstrumentID);
	pRet->setExchange(contract->getExchg());

	// STP 没有 InsertTime，直接用当前时间
	uint32_t uDate = TimeUtils::getCurDate();
	pRet->setOrderDate(uDate);
	pRet->setOrderTime(TimeUtils::getLocalTimeNow());

	pRet->setOrderState(wrapOrderState(orderField->OrderStatus));
	// STP 没有 OrderSubmitStatus，直接不做错误标记

	generateEntrustID(pRet->getEntrustID(), atoi(orderField->OrderRef));
	pRet->setOrderID(orderField->OrderSysID);

	pRet->setStateMsg(orderField->StatusMsg);

	const char* usertag = m_eidCache.get(pRet->getEntrustID());
	if(strlen(usertag) == 0)
	{
		pRet->setUserTag(pRet->getEntrustID());
	}
	else
	{
		pRet->setUserTag(usertag);

		if (strlen(pRet->getOrderID()) > 0)
		{
			m_oidCache.put(StrUtil::trim(pRet->getOrderID()).c_str(), usertag, 0, [this](const char* message) {
				write_log(m_sink, LL_ERROR, message);
			});
		}
	}

	return pRet;
}

WTSEntrust* TraderSTP::makeEntrust(StpOrderInsertReqField *entrustField)
{
	WTSContractInfo* ct = m_bdMgr->getContract(entrustField->InstrumentID, entrustField->ExchangeID);
	if (ct == NULL)
		return NULL;

	WTSEntrust* pRet = WTSEntrust::create(
		entrustField->InstrumentID,
		entrustField->VolumeTotalOriginal,
		entrustField->LimitPrice,
		ct->getExchg());

	pRet->setContractInfo(ct);

	pRet->setDirection(wrapDirectionType(entrustField->Direction, entrustField->CombOffsetFlag[0]));
	pRet->setPriceType(wrapPriceType(entrustField->OrderPriceType));
	pRet->setOffsetType(wrapOffsetType(entrustField->CombOffsetFlag[0]));

	if (entrustField->TimeCondition == STP_TC_GFD)
	{
		pRet->setOrderFlag(WOF_NOR);
	}
	else if (entrustField->TimeCondition == STP_TC_IOC)
	{
		if (entrustField->VolumeCondition == STP_VC_AV || entrustField->VolumeCondition == STP_VC_MV)
			pRet->setOrderFlag(WOF_FAK);
		else
			pRet->setOrderFlag(WOF_FOK);
	}

	generateEntrustID(pRet->getEntrustID(), atoi(entrustField->OrderRef));

	const char* usertag = m_eidCache.get(pRet->getEntrustID());
	if (strlen(usertag) > 0)
		pRet->setUserTag(usertag);

	return pRet;
}

WTSEntrustAction* TraderSTP::makeAction(StpOrderCancelReqField *actionField)
{
	// STP 撤单只需 AccountID、OperatorID、OrderRef，无法直接获取合约信息，需外部补充
	WTSEntrustAction* pRet = WTSEntrustAction::create("", "");
	pRet->setOrderID(actionField->OrderRef); // 用 OrderRef 作为唯一标识
	generateEntrustID(pRet->getEntrustID(), atoi(actionField->OrderRef));

	const char* usertag = m_eidCache.get(pRet->getEntrustID());
	if (strlen(usertag) > 0)
		pRet->setUserTag(usertag);

	return pRet;
}

WTSError* TraderSTP::makeError(StpRspInfoField* rspInfo, WTSErroCode ec /* = WEC_NONE */)
{
	WTSError* pRet = WTSError::create(ec, fmtutil::format("{}({})", rspInfo->ErrorMsg, rspInfo->ErrorID));
	return pRet;
}

WTSTradeInfo* TraderSTP::makeTradeInfo(StpTradeField *tradeField)
{
	WTSContractInfo* contract = m_bdMgr->getContract(tradeField->InstrumentID, tradeField->ExchangeID);
	if (contract == NULL)
		return NULL;

	WTSTradeInfo *pRet = WTSTradeInfo::create(tradeField->InstrumentID, contract->getExchg());
	pRet->setVolume(tradeField->Volume);
	pRet->setPrice(tradeField->Price);
	pRet->setTradeID(tradeField->TradeID);
	pRet->setContractInfo(contract);

	uint32_t uDate = TimeUtils::getCurDate();
	pRet->setTradeDate(uDate);
	pRet->setTradeTime(TimeUtils::getLocalTimeNow());

	WTSDirectionType dType = wrapDirectionType(tradeField->Direction, tradeField->OffsetFlag);

	pRet->setDirection(dType);
	pRet->setOffsetType(wrapOffsetType(tradeField->OffsetFlag));
	pRet->setRefOrder(tradeField->OrderSysID);
	pRet->setTradeType(WTT_Common);

	double amount = contract->getCommInfo()->getVolScale()*tradeField->Volume*pRet->getPrice();
	pRet->setAmount(amount);

	const char* usertag = m_oidCache.get(StrUtil::trim(pRet->getRefOrder()).c_str());
	if (strlen(usertag))
		pRet->setUserTag(usertag);

	return pRet;
}

int TraderSTP::wrapPriceType(WTSPriceType priceType)
{
	if (WPT_ANYPRICE == priceType)
		return STP_OPT_AnyPrice;
	else if (WPT_LIMITPRICE == priceType)
		return STP_OPT_LimitPrice;
	else if (WPT_BESTPRICE == priceType)
		return STP_OPT_BestPrice;
	else
		return STP_OPT_LimitPrice;
}

WTSPriceType TraderSTP::wrapPriceType(char priceType)
{
	if (STP_OPT_AnyPrice == priceType)
		return WPT_ANYPRICE;
	else if (STP_OPT_LimitPrice == priceType)
		return WPT_LIMITPRICE;
	else if (STP_OPT_BestPrice == priceType)
		return WPT_BESTPRICE;
	else
		return WPT_LIMITPRICE;
}

// STP方向/开平辅助函数，参数类型全部为 char
int TraderSTP::wrapDirectionType(WTSDirectionType dirType, WTSOffsetType offType)
{
	if (WDT_LONG == dirType)
		if (offType == WOT_OPEN)
			return STP_D_Buy;
		else
			return STP_D_Sell;
	else
		if (offType == WOT_OPEN)
			return STP_D_Sell;
		else
			return STP_D_Buy;
}

WTSDirectionType TraderSTP::wrapDirectionType(char dirType, char offType)
{
	// 根据STP的方向字段正确映射到WTS方向
	if (dirType == STP_D_Buy)
	{
		// 买入：如果是开仓则为多头，如果是平仓则为空头平仓
		return (offType == STP_OF_Open) ? WDT_LONG : WDT_SHORT;
	}
	else if (dirType == STP_D_Sell)
	{
		// 卖出：如果是开仓则为空头，如果是平仓则为多头平仓
		return (offType == STP_OF_Open) ? WDT_SHORT : WDT_LONG;
	}

	// 默认返回多头
	return WDT_LONG;
}

int TraderSTP::wrapOffsetType(WTSOffsetType offType)
{
	if (WOT_OPEN == offType)
		return STP_OF_Open;
	else if (WOT_CLOSE == offType)
		return STP_OF_Close;
	else if (WOT_CLOSETODAY == offType)
		return STP_OF_CloseToday;
	else if (WOT_CLOSEYESTERDAY == offType)
		return STP_OF_Close;
	else
		return STP_OF_ForceClose;
}

WTSOffsetType TraderSTP::wrapOffsetType(char offType)
{
	// 根据STP的开平标志映射到WTS开平类型
	switch (offType)
	{
	case STP_OF_Open:
		return WOT_OPEN;
	case STP_OF_Close:
		return WOT_CLOSE;
	case STP_OF_CloseToday:
		return WOT_CLOSETODAY;
	case STP_OF_CloseYesterday:
		return WOT_CLOSEYESTERDAY;
	case STP_OF_ForceClose:
		return WOT_FORCECLOSE;
	default:
		return WOT_OPEN;
	}
}

WTSDirectionType TraderSTP::wrapPosDirection(char dirType)
{
	if (STP_PD_Long == dirType)
		return WDT_LONG;
	else
		return WDT_SHORT;
}

WTSTimeCondition TraderSTP::wrapTimeCondition(char timeCond)
{
	if (STP_TC_IOC == timeCond)
		return WTC_IOC;
	else if (STP_TC_GFD == timeCond)
		return WTC_GFD;
	else
		return WTC_GFS;
}

WTSOrderState TraderSTP::wrapOrderState(char orderState)
{
	return (WTSOrderState)orderState;
}

int TraderSTP::wrapActionFlag(WTSActionFlag actionFlag)
{
	return actionFlag;
}

// 注意：STP常量已在StpDataType.h中定义，无需重复定义
