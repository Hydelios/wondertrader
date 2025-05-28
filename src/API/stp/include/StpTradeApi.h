#ifndef STP_TRADE_API_H
#define STP_TRADE_API_H

//#ifdef WIN32
#if (defined WIN32 || defined _WIN64)
#ifndef TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT __attribute__((visibility("default")))
#endif
#include <iostream>
#include <vector>

#include "StpDataStruct.h"
using namespace std;
// namespace ctzq{
//    namespace stp{
class StpTradeSpi;
class TRADER_API_EXPORT StpTradeApi {
 public:
  ///构造函数，创建UserApi类对象
  static StpTradeApi* CreateStpTradeApi(const char* pszFlowPath);
  ///删除接口对象本身
  ///@remark 不再使用本接口对象时,调用该函数删除接口对象
  virtual void Release() = 0;
  ///初始化函数
  // ret -1: 初始化失败
  // ret -2: 配置文件解析失败
  // ret -3: 内部数据初始化异常
  virtual int Init() = 0;
  //  请求登录网关
  virtual int ReqLoginUGW(MsgLogin* pLoginUGW, int64_t nClientRequestId, uint64_t index) = 0;

  //  注销网关登录
  virtual int ReqLogoutUGW(MsgLogout* pLogoutUGW, int64_t nClientRequestId) = 0;
  ///注册SPI对象
  virtual void RegisterSpi(StpTradeSpi* pSpi) = 0;
  ///订阅私有流。
  ///@param nResumeType 私有流重传方式
  ///              TERT_RESTART:从本交易日开始重传
  ///              TERT_RESUME:从上次收到的续传
  ///              TERT_QUICK:只传送登录后私有流的内容
  ///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
  virtual void SubscribePrivateTopic(STP_RESUME_TYPE nResumeType) = 0;
  ///订阅公共流。
  ///@param nResumeType 公共流重传方式
  ///        THOST_TERT_RESTART:从本交易日开始重传
  ///        THOST_TERT_RESUME:从上次收到的续传
  ///        THOST_TERT_QUICK:只传送登录后公共流的内容
  ///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
  virtual void SubscribePublicTopic(STP_RESUME_TYPE nResumeType) = 0;
  ///注册前置机网络地址
  ///@param pszFrontAddress：前置机网络地址。
  ///@remark
  ///网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。
  ///@remark
  ///“tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
  virtual void RegisterFront(const char* pszFrontAddress, uint16_t port) = 0;
  //  注册要连接的网络地址
  virtual void RegisterInetAddress(std::vector<std::string>& InetAddVec) = 0;
  ///操作员登录请求
  // virtual int login(TFUserLoginReqField *pLogin) = 0;
  virtual int ReqOperatorlogin(StpOperatorLoginReqField* pOperatorLogin, int64_t nClientRequestId) = 0;
  ///登出请求
  virtual int Logout() = 0;
  ///操作员密码修改
  virtual int ReqChangeOperatorPwd(StpPasswordChangeReqField* pChangePwd, int64_t nClientRequestId) = 0;
  ///报单录入请求
  virtual int ReqInsertOrder(StpOrderInsertReqField* pOrderInsert, int64_t nClientRequestId) = 0;
  virtual int ReqInsertOrderBatch(StpOrderInsertReqField pOrderInsert[], int count, int64_t nClientRequestId) = 0;
  ///期权组合报单录入请求
  virtual int ReqInsertOptCombOrder(StpOptCombOrderInsertReqField* pOptCombOrderInsert, int64_t nClientRequestId) = 0;
  ///报单操作请求
  virtual int ReqCancelOrder(StpOrderCancelReqField* pOrderCancel, int64_t nClientRequestId) = 0;

  /////////////////////////////////////////////////////////////////////////////////
  /// 查询接口定义
  /////////////////////////////////////////////////////////////////////////////////
  ///请求查询合约
  virtual int ReqQryInstrument(StpQryInstrumentField* qryInstrument, int64_t nClientRequestId) = 0;
  ///请求查询账户信息
  // virtual int ReqQryAccount(StpQryAccountField *qryAccount) = 0;
  ///请求查询资金账户
  virtual int ReqQryAccountAsset(StpQryAccountAssetField* qryAccountAsset, int64_t nClientRequestId) = 0;
  ///请求查询投资者持仓
  virtual int ReqQryPosition(StpQryPositionField* qryPosition, int64_t nClientRequestId) = 0;
  ///请求查询投资者期权组合保证金持仓
  virtual int ReqQryOptionCombPosition(StpQryOptionCombPositionField* qryOptionCombPosition,
                                       int64_t nClientRequestId) = 0;
  ///查询期货持仓明细
  virtual int ReqQryPositionDetail(StpQryPositionField* qryPosition, int64_t nClientRequestId) = 0;
  ///请求查询报单
  virtual int ReqQryOrder(StpQryOrderField* qryOrder, int64_t nClientRequestId) = 0;
  ///请求查询期权组合报单
  virtual int ReqQryOptCombOrder(StpQryOptCombOrderField* qryOrder, int64_t nClientRequestId) = 0;
  ///请求查询成交
  virtual int ReqQryTrade(StpQryTradeField* qryTrade, int64_t nClientRequestId) = 0;
  //请求查询资金流水
  virtual int ReqQryFundJour(StpQryFundJourField* qryFundJour, int64_t nClientRequestId) = 0;
  ///请求查询ETF申赎委托明细
  virtual int ReqQryETFOrderDetail(StpReqQryETFOrderDetailField* qryOrder, int64_t nClientRequestId) = 0;
  ///请求查询ETF申赎成交明细
  virtual int ReqQryETFTradeDetail(StpReqQryETFTradeDetailField* qryTrade, int64_t nClientRequestId) = 0;

  ///////////////////////////////////////////////////////////////////////////////////
  ///高级订单
  ///////////////////////////////////////////////////////////////////////////////////
  //高级订单录入请求
  virtual int ReqInsertSeniorOrder(StpSeniorOrderReqField* pOrderInsert, int64_t nClientRequestId) = 0;
  //高级订单操作(激活、暂停、撤销、修改)
  virtual int ReqOperateSeniorOrder(StpSeniorOrderOperateReqField* pOrderOperate, int64_t nClientRequestId) = 0;
  ///请求查询高级订单
  virtual int ReqQrySeniorOrder(StpQrySeniorOrderField* qrySeniorOrder, int64_t nClientRequestId) = 0;
  ///高级订单批量新增
  virtual int ReqInsertSeniorOrderBatch(StpSeniorOrderReqField pOrderInsert[], int count, int64_t nClientRequestId) = 0;
  ///请求查询期权代码指标
  virtual int ReqQryOptIndex(StpQryOptIndexField* qryOptIndex, int64_t nClientRequestId) = 0;
  ///请求计算期权代码指标
  virtual int ReqCalcOptIndex(StpReqCalcOptIndexField* calcOptIndex, int64_t nClientRequestId) = 0;
  ///请求订阅期权代码指标
  virtual int ReqSubscribeOptIndex(StpSubscribeOptIndexField subOptIndex[], int count, int64_t nClientRequestId) = 0;
  ///请求取消订阅期权代码指标
  virtual int ReqCancelSubOptIndex(StpCancelSubOptIndexField* cancelSubOptIndex, int64_t nClientRequestId) = 0;
  //////////////////////////////////////////////////////////////////////////////////
  ///算法模板操作
  /////////////////////////////////////////////////////////////////////////////////
  ///算法模板操作
  virtual int ReqOperateAlgoTemplate(StpOperateAlgoTemplateReqField* pAlgoTemplate, int64_t nClientRequestId) = 0;
  ///算法模板查询
  virtual int ReqQryAlgoTemplate(StpQryAlgoTemplateField* qryAlgoTemplate, int64_t nClientRequestId) = 0;
  ///获取用户token的请求
  virtual int ReqGetUserToken(StpUserTokenReqField* pGetToken, int64_t nClientRequestId) = 0;
  //////////////////////////////////////////////////////////////////////////////////
  ///融资融券
  /////////////////////////////////////////////////////////////////////////////////
  virtual int ReqCreditCashReturn(StpCreditCashRtnReqField* pCashRtn, int64_t nClientRequestId) = 0;
  //////////////////////////////////////////////////////////////////////////////////
  ///两融篮子下单相关
  /////////////////////////////////////////////////////////////////////////////////
  //两融篮子下单指令
  virtual int ReqInsertCreditComboOrder(StpCreditComboReqField* pOrderInsert, int64_t nClientRequestId) = 0;
  //查询两融篮子持仓
  virtual int ReqQryCreditComboPosition(StpQryPositionField* qryPosition, int64_t nClientRequestId) = 0;
  //查询两融篮子执行列表
  virtual int ReqQryCreditComboExecLst(StpQryCreditComboExecField* qryExec, int64_t nClientRequestId) = 0;
  //查询两融篮子客户资产信息
  virtual int ReqQryCreditComboAsset(StpQryAccountAssetField* qryAsset, int64_t nClientRequestId) = 0;
  //查询最大交易数量
  virtual int ReqQryMaxBuy(StpQryMaxBuyField* qryMaxBuy, int64_t nClientRequestId) = 0;
  //查询客户担保证券信息
  virtual int ReqQryCrdtStkInfo(StpQryCrdtStkInfoField* qryCrdtStkInfo, int64_t nClientRequestId) = 0;
  //查询标的券
  virtual int ReqQryCrdtTarStkInfo(StpQryCrdtTarStkInfoField* qryCrdtTarStkInfo, int64_t nClientRequestId) = 0;
  //可融券信息查询，专项头寸明细
  virtual int ReqQryCrdtEnsloSecy(StpQryCrdtEnsloSecyField* qryCrdtEnsloSecy, int64_t nClientRequestId) = 0;
  //客户信用资产信息获取
  virtual int ReqQryCrdtAsset(StpQryCrdtAssetField* qryCrdtAsset, int64_t nClientRequestId) = 0;
  //客户信用资产信息获取
  virtual int ReqQryCrdtCompact(StpQryCrdtCompactField* qryCrdtCompact, int64_t nClientRequestId) = 0;

  //修改宽邦策略
  virtual int ReqUpdateBigQuantStrategy(StpReqUpdateBigQuantStrategy* reqUpdateBigQuantStrategy,
                                        int64_t nClientRequestId) = 0;

  //查询宽邦策略
  virtual int ReqQryBigQuantStrategy(const char* operatorId, int64_t nClientRequestId) = 0;
  //查询宽邦策略明细
  virtual int ReqQryBigQuantStrategyDetail(const int strategyId, int64_t nClientRequestId) = 0;
  //查询宽邦策略日志
  virtual int ReqQryBigQuantLogDetail(StpQryBigQuantLogDetailField* qryBigQuantLogDetail, int64_t nClientRequestId) = 0;

  //插入宽邦策略
  virtual int ReqInsertBigQuantStrategy(StpReqInsertBigQuantStrategy* stpReqInsertBigQuantStrategy,
                                        int64_t nClientRequestId) = 0;

  //插入宽邦策略详情
  virtual int ReqInsertBigQuantStrategyDetail(int StrategyId, int TradeDate, StpBigQuantStrategyDetail stpBigQuantStrategyDetail[],
                                              int count, int64_t nClientRequestId) = 0;

  virtual int ReqLockOpaccount(StpLockOpaccount* msg, int64_t nClientRequestId) = 0;

  //查询操作员菜单权限
  virtual int ReqQryMenuAuth(StpReqQryMenuAuthField* qryMenuAuth, int64_t nClientRequestId) = 0;
  //////////////////////////////////////////////////////////////////////////////
  /// DMA
  // virtual int ReqInsertOrderBatch(StpOrderInsertReqField pOrderInsert[], int count, int64_t nClientRequestId) = 0;
  ////////////////////////////////////////////////////////////////////////////////
  //查询可交易标的（白名单）
  virtual int ReqQryBctTradableInstruments(int64_t nClientRequestId) = 0;
  //查询合约名义本金
  virtual int ReqQryContractUsableNotionAmt(StpReqQryContractUsableNotionAmtField qryContractUsableNotionAmt[],
                                            int count, int64_t nClientRequestId) = 0;
  //查询合约持仓
  virtual int ReqQryContractPosition(StpReqQryContractPositionField* qryContractPosition, int64_t nClientRequestId) = 0;
  //合约委托指令
  virtual int ReqInsertContractOrder(StpReqInsertContractOrderField* insertContractOrder, int64_t nClientRequestId) = 0;
  //查询合约指令
  virtual int ReqQryContractCommands(StpReqQryContractCommandField* qryContractCommands, int64_t nClientRequestId) = 0;
  //查询合约委托
  virtual int ReqQryContractOrders(StpQryOrderField* qryContractOrders, int64_t nClientRequestId) = 0;
  //撤销委托指令
  virtual int ReqCancelContractOrder(StpReqCancelContractOrderField* cancelContractOrder, int64_t nClientRequestId) = 0;
  //审核指令
  virtual int ReqAuditContractOrder(StpReqAuditContractOrderField* auditContractOrderField,
                                    int64_t nClientRequestId) = 0;
  //合约成交明细查询
  virtual int ReqQryContractDeal(StpQryTradeField* qryContractDealField, int64_t nClientRequestId) = 0;
  //批量合约指令
  virtual int ReqInsertContractOrderBatch(StpReqInsertContractOrderField insertContractOrder[], int count,
                                          int64_t nClientRequestId) = 0;
  //批量撤单
  virtual int ReqCancelContractOrderBatch(StpReqCancelContractOrderField cancelContractOrder[], int count,
                                          int64_t nClientRequestId) = 0;
  //查询风险数据
  virtual int ReqQryDmaRiskData(StpReqQryDmaRiskDataField* qryDmaRiskData, int64_t nClientRequestId) = 0;
  //计算多空收益相关性
  virtual int ReqCalcLongShortCorrelation(StpReqCalcLongShortCorrelationField* calcCalcLongShortCorrel, int64_t nClientRequestId) = 0;
  //同步数据
  virtual int ReqSyncBctData(StpSyncBctDataField* syncBctData, int64_t nClientRequestId) = 0;
  //查询风控参数
  virtual int ReqQryDmaRiskParam(StpReqQryDmaRiskParamField* qryDmaRiskParam, int64_t nClientRequestId) = 0;
  //设置风控参数
  virtual int ReqSetDmaRiskParam(StpReqSetDmaRiskParamField* setDmaRiskParam, int64_t nClientRequestId) = 0;
  //系统运维
  virtual int ReqDmaSystemMaintenanceOp(StpDmaSystemMaintenanceOpField* dmaSystemMaintence, int64_t nClientRequestId) = 0;
  //系统状态查询
  virtual int ReqQryDmaSystemStatus(int64_t nClientRequestId) = 0;
  //查询费用模板
  virtual int ReqQryDmaFareModel(StpReqQryDmaFareModelField* qryDmaFareModel, int64_t nClientRequestId) = 0;
  //设置费用模板
  virtual int ReqSetDmaFareModel(StpReqSetDmaFareModelField* setDmaFareModel, int64_t nClientRequestId) = 0;

 protected:
  virtual ~StpTradeApi(){};
};

// class TRADER_API_EXPORT TFHelperApi
// {
// public:
// 	static TFLoginReqField getLoginInfo();
// };

class StpTradeSpi {
 public:
  ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
  virtual void OnFrontConnected(){};

  //  响应网关登录请求
  virtual void OnRspUGWLogin(MsgLogin* pLoginUGW, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};

  //  响应网关登出请求
  virtual void OnRspUGWLogout(MsgLogout* pLogoutUGW, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};

  //  响应是否重传结束
  virtual void OnRspUGWMsgSync(MsgSync* pMsgSync, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //登录请求响应
  virtual void OnRspOperatorLogin(StpRspLoginField* pRspLogin, int count, StpAccountInfoField* pAccountInfo,
                                  StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //注销请求响应
  virtual void OnRspLogout(StpRspInfoField* pRspInfo){};
  //修改密码响应
  virtual void OnRspChangeOperatorPwd(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
  virtual void OnFrontDisconnected(int nReason){};
  ///错误应答
  virtual void OnRspError(StpRspInfoField* pRspInfo){};
  ///报单通知
  virtual void OnRtnOrder(StpOrderField* pOrder){};
  ///期权组合报单通知
  virtual void OnRtnOptCombOrder(StpOptCombOrderField* pOrder){};
  ///成交通知
  virtual void OnRtnTrade(StpTradeField* pTrade){};
  ///报单错误回报
  virtual void OnRspErrInsertOrder(StpOrderInsertReqField* pInputOrder, StpRspInfoField* pRspInfo,
                                   int64_t nClientRequestId){};
  ///期权组合报单错误回报
  virtual void OnRspErrInsertOptCombOrder(StpOptCombOrderInsertReqField* pInputOrder, StpRspInfoField* pRspInfo,
                                          int64_t nClientRequestId){};
  ///撤单错误回报
  virtual void OnRspErrCancelOrder(StpOrderCancelReqField* pOrderAction, StpRspInfoField* pRspInfo,
                                   int64_t nClientRequestId){};
  ///持仓推送
  // virtual void OnRtnPositionChanged(StpUserComboPositionField *pPosition) {};

  /////////////////////////////////////////////////////////////////////////////////
  /// 查询接口定义
  /////////////////////////////////////////////////////////////////////////////////
  ///请求查询合约响应
  virtual void OnQryInstrument(StpInstrumentField* pInstrument, int count, int totalNum, StpRspInfoField* pRspInfo,
                               int64_t nClientRequestId){};
  ///请求查询账户信息响应
  // virtual void OnQryAccount(StpAccountField *pAccount, StpRspInfoField
  // *pRspInfo){};
  ///请求查询资金账户响应
  virtual void OnQryAccountAsset(StpUserAccountAssetField* pAccount, int count, StpRspInfoField* pRspInfo,
                                 int64_t nClientRequestId){};
  ///请求查询投资者持仓响应
  virtual void OnQryPosition(StpUserComboPositionField* pPosition, int count, StpRspInfoField* pRspInfo,
                             int64_t nClientRequestId){};
  ///请求查询投资者持仓响应
  virtual void OnQryOptCombPosition(StpOptionCombPositionField* pPosition, int count, StpRspInfoField* pRspInfo,
                                    int64_t nClientRequestId){};
  //请求查询投资者持仓明细响应
  virtual void OnQryPositionDetail(StpPositionDetailField* pPosition, int count, StpRspInfoField* pRspInfo,
                                   int64_t nClientRequestId){};
  ///请求查询报单响应
  virtual void OnQryOrder(StpOrderField* pOrder, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///请求查询报单响应
  virtual void OnQryOptCombOrder(StpOptCombOrderField* pOrder, int count, StpRspInfoField* pRspInfo,
                                 int64_t nClientRequestId){};
  ///请求查询成交响应
  virtual void OnQryTrade(StpTradeField* pTrade, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //批量下单委托应答
  virtual void OnRspInserOrderBatch(StpOrderBatchField* pOrders, int count, StpRspInfoField* pRspInfo,
                                    int64_t nClientRequestId){};
  //请求查询资金流水响应
  virtual void OnQryFundJour(StpFundJourField* pFundJour, int count, StpRspInfoField* pRspInfo,
                             int64_t nClientRequestId){};
  //最大交易数量响应
  virtual void OnRspQryMaxBuy(StpMaxBuyField* pMaxBuy, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {}
  //客户担保证券信息响应
  virtual void OnRspQryCrdtStkInfo(StpCrdtStkInfoField* pStkInfo, int count, StpRspInfoField* pRspInfo,
                                   int64_t nClientRequestId) {}
  //标的券查询响应
  virtual void OnRspQryCrdtTarStkInfo(StpCrdtTarStkInfoField* pStkInfo, int count, StpRspInfoField* pRspInfo,
                                      int64_t nClientRequestId) {}
  //可融券查询响应
  virtual void OnRspQryCrdtEnsloSecy(StpCrdtEnsloSecyField* pStkInfo, int count, StpRspInfoField* pRspInfo,
                                     int64_t nClientRequestId) {}
  virtual void OnRspQryCrdtAsset(StpCrdtAssetField* pStkInfo, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {}
  virtual void OnRspQryCrdtCompact(StpCrdtCompactField* pStkInfo, int count, StpRspInfoField* pRspInfo,
                                   int64_t nClientRequestId) {}
  ///请求查询ETF申赎委托明细响应
  virtual void OnQryETFOrderDetail(StpQryETFOrderDetailField* pOrder, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///请求查询ETF申赎成交明细响应
  virtual void OnQryETFTradeDetail(StpQryETFTradeDetailField* pTrade, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///////////////////////////////////////////////////////////////////////////////////
  ///高级订单
  ///////////////////////////////////////////////////////////////////////////////////
  ///高级订单报单通知
  virtual void OnRtnSeniorOrder(StpSeniorOrderField* pSeniorOrder){};
  //高级订单报单错误应答
  virtual void OnRspErrInsertSeniorOrder(StpSeniorOrderReqField* pInputOrder, StpRspInfoField* pRspInfo,
                                         int64_t nClientRequestId){};
  //高级订单操作(修改、激活、暂停、撤销)错误应答
  virtual void OnRspErrOperateSeniorOrder(StpSeniorOrderOperateReqField* pOperateOrder, StpRspInfoField* pRspInfo,
                                          int64_t nClientRequestId){};
  ///请求查询高级订单响应
  virtual void OnQrySeniorOrder(StpSeniorOrderField* pSeniorOrder, int count, StpRspInfoField* pRspInfo,
                                int64_t nClientRequestId){};
  //批量高级订单新增应答
  virtual void OnRspInserSeniorOrderBatch(StpSeniorOrderBatchField* pOrders, int count, StpRspInfoField* pRspInfo,
                                          int64_t nClientRequestId){};
  ///请求查询期权代码指标响应
  virtual void OnRspQryOptIndex(StpOptIndexField* pOptIndex, int count, StpRspInfoField* pRspInfo,
                                int64_t nClientRequestId){};
  ///请求计算期权指标响应
  virtual void OnRspCalcOptIndex(StpCalcOptIndexField* pCalcOptIndex, StpRspInfoField* pRspInfo,
                                 int64_t nClientRequestId){};
  ///请求订阅期权指标响应
  virtual void OnRspSubscribeOptIndex(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///请求取消订阅期权指标响应
  virtual void OnRspCancelSubOptIndex(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //////////////////////////////////////////////////////////////////////////////////
  ///算法模板操作
  /////////////////////////////////////////////////////////////////////////////////
  //算法模板操作应答
  virtual void OnRspOperateAlgoTemplate(StpOperateAlgoTemplateField* pAlgoTemplateRsp, StpRspInfoField* pRspInfo,
                                        int64_t nClientRequestId){};
  //算法模板查询
  virtual void OnQryAlgoTemplate(StpAlgoTemplateField* pAlgoTemplates, int count, StpRspInfoField* pRspInfo,
                                 int64_t nClientRequestId){};
  ///获取用户token响应
  virtual void OnRspGetUserToken(StpUserTokenField* pToken, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //////////////////////////////////////////////////////////////////////////////////
  ///融资融券
  /////////////////////////////////////////////////////////////////////////////////
  virtual void OnRspCashReturn(StpCreditCashRtnField* pCashRtn, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //////////////////////////////////////////////////////////////////////////////////
  ///两融篮子下单相关
  /////////////////////////////////////////////////////////////////////////////////
  //两融篮子指令下单异步应答
  virtual void OnRspInsertCreditComboOrder(StpCreditComboField* pCreditCombo, StpRspInfoField* pRspInfo,
                                           int64_t nClientRequestId){};
  //两融篮子持仓查询应答
  virtual void OnQryCreditComboPosition(StpCreditComboPosition* pPosition, int count, StpRspInfoField* pRspInfo,
                                        int64_t nClientRequestId){};
  //两融篮子执行列表查询应答
  virtual void OnQryCreditComboExecLst(StpCreditComboExecField* pExec, int count, StpRspInfoField* pRspInfo,
                                       int64_t nClientRequestId){};
  //两融篮子客户资产信息应答
  virtual void OnQryCreditComboAsset(StpCreditComboAsset* pAsset, int count, StpRspInfoField* pRspInfo,
                                     int64_t nClientRequestId){};

  virtual void OnLockOpaccount(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};

  //查询操作员菜单权限应答
  virtual void OnRspQryMenuAuth(StpQryMenuAuthField* pAuthInfo, StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //////////////////////////////////////////////////////////////////////////////////
  ///宽邦接口
  //////////////////////////////////////////////////////////////////////////////////
  //修改宽邦策略
  virtual void OnRspUpdateBigQuantStrategy(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //查询宽邦策略
  virtual void OnQryBigQuantStrategy(StpBigQuantStrategy* stpBigQuantStrategy, int count, StpRspInfoField* pRspInfo,
                                     int64_t nClientRequestId){};
  //查询宽邦策略明细
  virtual void OnQryBigQuantStrategyDetail(StpBigQuantStrategyDetail* stpBigQuantStrategyDetail, int count,
                                           StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //查询宽邦策略日志
  virtual void OnQryBigQuantLogDetail(StpBigQuantLogDetail* stpBigQuantLogDetail, int count, StpRspInfoField* pRspInfo,
                                      int64_t nClientRequestId){};

  //插入宽邦策略响应
  virtual void OnRspInsertBigQuantStrategy(StpRspInsertBigQuantStrategy* stpRspInsertBigQuantStrategy,
                                           StpRspInfoField* pRspInfo, int64_t nClientRequestId){};

  //插入宽邦策略详情响应
  virtual void OnRspInsertBigQuantStrategyDetail(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};

  ///////////////////////////////////////////////////////////////////////////////////
  /// DMA
  ///////////////////////////////////////////////////////////////////////////////////
  ///报单应答
  virtual void OnRspInsertContractOrder(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///撤单应答
  virtual void OnRspCancelContractOrder(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //查询可交易标的（白名单）应答
  virtual void OnRspQryBctTradableInstruments(StpQryBctTradableInstrumentsField* pInstruments, int count,
                                              StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///查询合约名义本金接口应答
  virtual void OnRspQryContractUsableNotionAmt(StpQryContractUsableNotionAmtField* pContractUsableNotionAmt, int count,
                                               StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///查询合约持仓应答
  virtual void OnRspQryContractPosition(StpQryContractPositionField* pContractPosition, int count,
                                        StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///查询合约委托记录应答
  virtual void OnRspQryContractOrders(StpOrderField* pContractOrder, int count, StpRspInfoField* pRspInfo,
                                      int64_t nClientRequestId){};
  ///审核指令应答
  virtual void OnRspAuditContractOrder(StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///合约成交明细查询应答
  virtual void OnRspQryContractDeal(StpTradeField* pContractDeal, int count, StpRspInfoField* pRspInfo,
                                    int64_t nClientRequestId){};
  ///合约指令报单通知
  virtual void OnRtnContractCommand(StpContractCommandField* pContractCommand){};
  //批量合约委托应答
  virtual void OnRspInsertContractOrderBatch(StpRspInsertContractOrderBatchField* pInsertOrders, int count,
                                            StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  //批量撤单应答
  virtual void OnRspCancelContractOrderBatch(StpRspCancelContractOrderBatchField* pCancelOrders, int count,
                                             StpRspInfoField* pRspInfo, int64_t nClientRequestId){};
  ///查询合约指令应答
  virtual void OnRspQryContractCommands(StpContractCommandField* pContractCommand, int count, StpRspInfoField* pRspInfo,
                                        int64_t nClientRequestId){};
  ///查询风险数据
  virtual void OnRspQryDmaRiskData(StpQryDmaRiskDataField* pDmaRiskData, int count,
      StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///计算多空收益相关性
  virtual void OnRspCalcLongShortCorrelation(StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///同步数据
  virtual void OnRspSyncBctData(StpSyncBctDataField* pSyncBctData, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///查询风控参数
  virtual void OnRspQryDmaRiskParam(StpQryDmaRiskParamField* pDmaRiskParam, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///设置风控参数
  virtual void OnRspSetDmaRiskParam(StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///系统运维
  virtual void OnRspDmaSystemMaintenanceOp(StpDmaSystemMaintenanceOpField* dmaSystemMaintence,  StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///系统状态查询
  virtual void OnRspQryDmaSystemStatus(StpQryDmaSystemStatusField* qryDmaSystemStatus, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///查询费用模板
  virtual void OnRspQryDmaFareModel(StpQryDmaFareModelField* pDmaFareModel, int count, StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};
  ///设置费用模板
  virtual void OnRspSetDmaFareModel(StpRspInfoField* pRspInfo, int64_t nClientRequestId) {};

  //////////////////////////////////////////////////////////////////////////////////
  ///数据推送通用接口
  //////////////////////////////////////////////////////////////////////////////////
  virtual void OnCommonPush(StpCommonPushField* pCommon){};
};
//    }
//}
#endif
