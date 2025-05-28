#pragma once

#ifndef STP_DATA_TYPE_H
#define STP_DATA_TYPE_H

#include<stdint.h>

//namespace ctzq{ namespace stp{

enum STP_RESUME_TYPE
{
    STP_TERT_RESTART = 0,
    STP_TERT_RESUME,
    STP_TERT_QUICK
};

/////////////////////////////////////////////////////////////////////////
///网关消息相关
/////////////////////////////////////////////////////////////////////////

//  发送方代码
typedef char SendCompIDType[16];

//  接收方代码
typedef char TargetCompIDType[16];

//  资金账号
typedef char FundIDType[20];

//  网关登录
typedef char SessionCompIDType[16];

// 端口号码
typedef int32_t PortNumType;

// 成功标识
typedef bool BsuccessType;
// 许可证
typedef char LicenseType[51];

// 心跳间隔时间
typedef int32_t HeartBtType;

//  成交数量
typedef int64_t LastQty;

// 买卖方向
typedef char Side[2];

// 客户名称
typedef char ClientNameType[16];
//会话ID
typedef char SessionIDType[51];
// MD5值
typedef char MD5ValueType[51];
// 密码类型
typedef char PasswordType[41];
// Mac 地址类型
typedef char MacAddressType[21];
//  硬盘序列号
typedef char HardDiskSerialType[51];
//  协议版本
typedef char DefaultAppVerIDType[21];
//  测试请求标志
typedef char TestReqIDType[16];
//  同步类型
typedef bool SyncType;

typedef char AccountTypeType;

typedef char StockType[3];

typedef char PushType[5];

/////////////////////////////////////////////////////////////////////////
///DirectionType是一个买卖方向类型
/////////////////////////////////////////////////////////////////////////
///买
const char STP_D_Buy = '0';
///卖
const char STP_D_Sell = '1';
///债券提交质押
const char STP_D_PledgeBondIn = '2';
///债券转回质押
const char STP_D_PledgeBondOut = '3';
///配股
const char STP_D_Doublened = '4';
///债转股
const char STP_D_Exchange = '5';
///申购
const char STP_D_Purchase = '6';
///保证券锁定（股票期权）
const char STP_D_CoverStkLock = '8';
///保证券解锁（股票期权）
const char STP_D_CoverStkUnlock = '9';
///期权合并行权
const char STP_D_CombiExcute = 'a';
///组合
const char STP_CD_Comb = 'b';
///拆分
const char STP_CD_Split = 'c';
///转备兑
const char STP_CD_ToCovered = 'd';
///备兑转保证金
const char STP_CD_CoveredToBalance = 'e';
///期权认购行权
const char STP_D_ExecuteCall = 'f';
///期权认沽行权
const char STP_D_ExecutePut = 'g';
///放弃行权
const char STP_D_GiveUpExecute = 'h';
///权利对冲设置
const char STP_D_RightHedge = 'i';
///权利对冲取消
const char STP_D_CancelRightHedge = 'j';
///义务期货对冲设置
const char STP_D_DutyHedge = 'k';
///义务期货对冲取消
const char STP_D_CancelDutyHedge = 'l';
///ETF申购
const char STP_D_ETFPurchase = 'm';
///ETF赎回
const char STP_D_ETFRedemption = 'n';
     
/////////////////////////////////////////////////////////////////////////
///CoveredFlagType是一个备兑标志类型
/////////////////////////////////////////////////////////////////////////
///非备兑
const char STP_CF_Uncovered = '0';
///备兑
const char STP_CF_Covered = '1';

///业务范围BusinessFlag
//现货
const char STP_BF_Spot = '1';
//期货
const char STP_BF_Future = '2';
//期权
const char STP_BF_Option = '3';
//银行间
const char STP_BF_Inter_Bank = '4';
//票据
const char STP_BF_Bill = '5';
//黄金
const char STP_BF_Gold = '6';

/////////////////////////////////////////////////////////////////////////
///HedgeFlagType是一个投机套保标志类型
/////////////////////////////////////////////////////////////////////////
/*-----------(内部版O32相关)------------*/
///可交易 O32 现货交易投资类型
const char STP_HF_Trade = '1';
///持有到期 O32 现货交易投资类型
const char STP_HF_Hold = '2';
///可供出售 O32 现货交易投资类型
const char STP_HF_Sale = '3';
///贷款和应收款项 O32 现货交易投资类型
const char STP_HF_Loan = '4';
///做市商
const char STP_HF_MarketMaker = '5';
///投机
const char STP_HF_Speculation = 'a';
///套利
const char STP_HF_Arbitrage = 'b';
///套保
const char STP_HF_Hedge = 'c';
/*-----------(外部版-成交类型)------------*/

/////////////////////////////////////////////////////////////////////////
///OffsetFlagType是一个开平标志类型
/////////////////////////////////////////////////////////////////////////
///开仓
const char STP_OF_Open = '0';
///平仓
const char STP_OF_Close = '1';
///强平
const char STP_OF_ForceClose = '2';
///平今
const char STP_OF_CloseToday = '3';
///平昨
const char STP_OF_CloseYesterday = '4';
///强减
const char STP_OF_ForceOff = '5';
///本地强平
const char STP_OF_LocalForceClose = '6';
///自动进行平昨平今判断(暂不支持）
const char STP_OF_Auto = '7';
///认购
const char STP_OF_Call = '8';
///认沽
const char STP_OF_Put = '9';

/////////////////////////////////////////////////////////////////////////
///OrderPriceTypeType是一个报单价格条件类型
/////////////////////////////////////////////////////////////////////////

///限价 (限价类型  作用范围: 沪深  期货  )
const char STP_OPT_LimitPrice = '0';
///任意价 (市价类型 作用范围：大商所期货 郑商所期货 )
const char STP_OPT_AnyPrice = '1';
///市价剩余转限价（市价类型 作用范围：上交所股票期权）
const char STP_OPT_LastToLimit = '2';
///市价剩余撤消（市价类型 作用范围：上交所股票期权）
const char STP_OPT_LastToCancel = '3';
///FOK限价（限价类型  作用范围：上交所股票期权   上期所、中金所、能源交易所期货 ）
const char STP_OPT_FOKLimit = '4';
///FOK市价（市价类型 作用范围：上交所股票期权  大商所期货   深交所）
const char STP_OPT_FOKLast = '5';
///五档即成剩撤（市价类型 作用范围：上交所 深交所  中金所期货）
const char STP_OPT_FiveLevelCancel = '6';
///五档即成剩转限（市价类型 作用范围：上交所  中金所期货）
const char STP_OPT_FiveLevelLimit = '7';
///FAK市价（市价类型 作用范围：郑商所期货 大商所期货）
const char STP_OPT_FAKLast = '8';
///即成剩撤（市价类型 作用范围：深交所）
const char STP_OPT_FillCancel = '9';
///对手方最优（市价类型 作用范围：深交所 上交所科创板 ）
const char STP_OPT_BestPrice = 'a';
///本方最优（市价类型 作用范围： 深交所 上交所科创板业务）
const char STP_OPT_LocalBest = 'b';
///科创板盘后固定价格 （）
const char STP_OPT_KcCloseFixPrice = 'c';
///最优一档即成剩撤（市价类型 作用范围：中金所期货）
const char STP_OPT_OneLevelCancel = 'd';
///最优一档即成剩转限（市价类型 作用范围：中金所期货）
const char STP_OPT_OneLevelLimit = 'e';
///FAK限价（ 限价类型 作用范围：郑商所期货  上期所、能源交易所期货 中金所期货）
const char STP_OPT_FAKLimit = 'f';

/////////////////////////////////////////////////////////////////////////
///TimeConditionType是一个有效期类型类型
/////////////////////////////////////////////////////////////////////////
///立即完成，否则撤销
const char STP_TC_IOC = '1';
///本节有效
const char STP_TC_GFS = '2';
///当日有效
const char STP_TC_GFD = '3';
///指定日期前有效
const char STP_TC_GTD = '4';
///撤销前有效
const char STP_TC_GTC = '5';
///集合竞价有效
const char STP_TC_GFA = '6';

/////////////////////////////////////////////////////////////////////////
///VolumeConditionType是一个成交量类型类型
/////////////////////////////////////////////////////////////////////////
///任何数量
const char STP_VC_AV = '1';
///最小数量
const char STP_VC_MV = '2';
///全部数量
const char STP_VC_CV = '3';

/////////////////////////////////////////////////////////////////////////
///PosiDirectionType是一个持仓多空方向类型
/////////////////////////////////////////////////////////////////////////
///多头
const char STP_PD_Long = '0';
///空头
const char STP_PD_Short = '1';
///备兑
const char STP_PD_Covered = '2';

/////////////////////////////////////////////////////////////////////////
///AccountTypeType是一个账户类型类型
/////////////////////////////////////////////////////////////////////////
///普通证券账户
const char STP_AT_STOCK = '1';
///信用账户
const char STP_AT_CREDIT = '2';
///衍生品账户
const char STP_AT_DERIVATIVE = '3';
///期货账户
const char STP_AT_FUTURES = '4';
///O32账户
const char STP_AT_O32 = '5';

/////////////////////////////////////////////////////////////////////////
///OrderStatusType是一个报单状态类型
/////////////////////////////////////////////////////////////////////////
///待报
const char STP_OST_Unknown = '0';
///正报
const char STP_OST_PendingNew = '1';
///已报
const char STP_OST_New = '2';
///部成
const char STP_OST_PartilyFilled = '3';
///已成
const char STP_OST_Filled = '4';
///部撤
const char STP_OST_PartilyCanceled = '5';
///已撤
const char STP_OST_Canceled = '6';
///废单
const char STP_OST_Rejected = '7';
///未报
const char STP_OST_UnReported = '8';
///待撤
const char STP_OST_WaitCancel = '9';

/////////////////////////////////////////////////////////////////////////
///证券类别
/////////////////////////////////////////////////////////////////////////
//股票
const StockType STP_STOCKTYPE_GP = "01";
//封闭式基金
const StockType STP_STOCKTYPE_FBJJ = "02";
//国债
const StockType STP_STOCKTYPE_GZ = "03";
//企业债
const StockType STP_STOCKTYPE_QZ = "04";
//可转债
const StockType STP_STOCKTYPE_KZZ = "05";
//政策性金融债
const StockType STP_STOCKTYPE_JRZ = "06";
//债券回购
const StockType STP_STOCKTYPE_ZQHG = "08";
//申购
const StockType STP_STOCKTYPE_SG = "0a";
//债转股
const StockType STP_STOCKTYPE_ZZG = "0B";
//开放式基金
const StockType STP_STOCKTYPE_KFJJ = "0F";
//非政策性金融债
const StockType STP_STOCKTYPE_FJRZ = "0G";
//配股
const StockType STP_STOCKTYPE_PG = "0h";
//次级债
const StockType STP_STOCKTYPE_CJZ = "0K";
//债券质押
const StockType STP_STOCKTYPE_ZQZY = "0Q";
//股指期货
const StockType STP_STOCKTYPE_GZQH = "0R";
//公司债
const StockType STP_STOCKTYPE_GSZ = "0S";
//地方债
const StockType STP_STOCKTYPE_DFZ = "0T";
//存托凭证
const StockType STP_STOCKTYPE_CTPZ = "0V";
//商品期货
const StockType STP_STOCKTYPE_SPQH = "0v";
//国债期货
const StockType STP_STOCKTYPE_GZQQH = "0W";
//指数
const StockType STP_STOCKTYPE_ZS = "0w";

/////////////////////////////////////////////////////////////////////////
///高级订单类型
/////////////////////////////////////////////////////////////////////////
//条件订单
const char STP_SOrderType_Condition = '1';
//算法订单
const char STP_SOrderType_Algor = '2';
//多腿套利订单-手工触发
const char STP_SOrderType_Arbi_Manual = '3';
//多腿套利订单-预埋触发
const char STP_SOrderType_Arbi_Embed = '4';
//价差套利监控
const char STP_SOrderType_Arbi_Monitor = '5';
//两融篮子算法下单
const char STP_SOrderType_Credit_Combo = '6';
//两融篮子模板
const char STP_SOrderType_Credit_Basket = '7';

//高级订单操作类型
//暂停
const char STP_OperateType_Suspend = '1';
//修改
const char STP_OperateType_Modify = '2';
//激活
const char STP_OperateType_Active = '3';
//撤销
const char STP_OperateType_Cancel = '4';

//高级订单状态
//执行中
const char STP_SeniorStatus_Executing = '1';
//暂停
const char STP_SeniorStatus_Suspended = '2';
//触发成功(执行一次的高级订单)
const char STP_SeniorStatus_Touch_Successed = '3';
//触发失败(执行一次的高级订单)
const char STP_SeniorStatus_Touch_Failed = '4';
//已撤销
const char STP_SeniorStatus_Canceled = '5';
//已完成（需要执行多次的高级订单）
const char STP_SeniorStatus_Done = '6';
//执行失败（需要执行多次的高级订单）
const char STP_SeniorStatus_Execute_Failed = '7';
//已过期
const char STP_SeniorStatus_Expired = '8';

//价格模式 PriceMode
//最新价
const char STP_LastPrice = '1';
//指定价
const char STP_BidPrice = '2';
//对手价1
const char STP_RivalPrice1 = '3';
//对手价2
const char STP_RivalPrice2 = '4';
//对手价3
const char STP_RivalPrice3 = '5';
//对手价4
const char STP_RivalPrice4 = '6';
//对手价5
const char STP_RivalPrice5 = '7';
//本方价1
const char STP_OwnPrice1 = '8';

//算法类型
const char STP_Order_Algo_Condition = '1';
const char STP_Order_Algo_Auto = '2';
//多腿套利订单-手工触发
const char STP_Order_Algo_Arbi_Manual = '3';
//多腿套利订单-预埋触发
const char STP_Order_Algo_Arbi_Embed = '4';
//价差套利监控
const char STP_Order_Algo_Arbi_Monitor = '5';

//算法模板操作类型
const char STP_Algo_Template_Insert = '1';
const char STP_Algo_Template_Modify = '2';
const char STP_Algo_Template_Delete = '3';

//推送类型PushType
//篮子执行列表状态推送
const PushType STP_PushType_Execute = "1";
//篮子持仓列表推送
const PushType STP_PushType_Hold = "2";
//共享内存指标推送
const PushType STP_PushType_Memory = "3";
//篮子资产相关数据推送
const PushType STP_PushType_Asset = "4";
//错误日志推送
const PushType STP_PushType_Err = "5";
//期权代码指标推送
const PushType STP_PushType_OptIndex = "6";
//dma风险指标推送
const PushType STP_PushType_DMA_RiskIndex = "7";
//dma风控检查结果推送
const PushType STP_PushType_DMA_RiskCheck = "8";
//dma多空收益相关性
const PushType STP_PushType_DMA_LongShortCorrel = "9";


//----------两融篮子下单指令类型-------------//
//自有资金买入
const char STP_CreditCombo_OwnFundBuy = '1';
//融资优先买入
const char STP_CreditCombo_MarginPrioBuy = '2';
//组合卖出
const char STP_CreditCombo_CollateralSell = '3';
//融券优先卖出
const char STP_CreditCombo_SloPrioSell = '4';
//补短仓差
const char STP_CreditCombo_ShortDiff = '5';
//补长仓差
const char STP_CreditCombo_LongDiff = '6';
//篮子还券
const char STP_CreditCombo_Return = '7';

/////////////////////////////////////////////////////////////////////////
//----------------EntrustType类型--------------------------//
/////////////////////////////////////////////////////////////////////////
const char STP_EntrustType_FinancingBuy = '6';        //融资买入
const char STP_EntrustType_VoucherRepayment = '6';    //卖券还款
const char STP_EntrustType_ShortSelling = '7';        //融券卖出
const char STP_EntrustType_BuyAndReturnTickets = '7'; //买券还券

/////////////////////////////////////////////////////////////////////////
///OptHoldType是期权持仓类型
/////////////////////////////////////////////////////////////////////////
///期权权利仓
const char STP_OH_Right = '0';
///期权义务仓
const char STP_OH_Duty = '1';
///期权备兑仓
const char STP_OH_Covered = '2';

/////////////////////////////////////////////////////////////////////////
///常量定义
/////////////////////////////////////////////////////////////////////////
///登录ID长度
const int STP_LOGINID_LEN = (255 + 1);
///定位串长度定义
const int STP_POSITIONSTR_LEN = (128 + 1);
///操作员 ID长度定义
const int STP_OPERATORID_LEN = (15 + 1);
//AccountID的长度定义
const int STP_ACCOUNTID_LEN = (15 + 1);
///证券代码长度的定义
const int STP_INSTRUMENTID_LEN = (30 + 1);
///交易所代码长度的定义
const int STP_EXCHANGEID_LEN = (8 + 1);
///合约名称长度的定义
const int STP_INSTRUMENTNAME_LEN = (128 + 1);
///产品代码长度的定义
const int STP_PRODUCTID_LEN = (30 + 1);
///经纪公司代码长度的定义
const int STP_BROKERID_LEN = (10 + 1);
///柜台代码长度的定义
const int STP_PROVIDERID_LEN = (10 + 1);
///母账户代码长度的定义
const int STP_BROKERINVESTORID_LEN = (32 + 1);
///母账户名称长度的定义
const int STP_BROKERINVESTORNAME_LEN = (80 + 1);
///密码长度的定义
const int STP_PASSWORD_LEN = (40 + 1);
///期权子账户编码长度的定义
const int STP_OPTSUBINVESTORID_LEN = (8 + 1);
///席位号长度的定义
const int STP_BUSINESSUNIT_LEN = (5 + 1);
///营业部代码长度的定义
const int STP_BRANCHID_LEN = (5 + 1);
///投资者名称长度的定义
const int STP_INVESTORNAME_LEN = (80 + 1);
///用户代码长度的定义
const int STP_USERID_LEN = (14 + 1);
///网关登录用户代码长度的定义
const int STP_GATEWAYUSERID_LEN = (14 + 1);
///用户名称长度的定义
const int STP_USERNAME_LEN = (80 + 1);
///组合名称长度的定义
const int STP_COMBONAME_LEN = (80 + 1);
///资产单元编号（UFX Only）长度的定义
const int STP_ASSETNO_LEN = (16 + 1);
///备注长度的定义
const int STP_MEMO_LEN = (80 + 1);
///成交编号长度的定义
const int STP_TRADEID_LEN = (20 + 1);
///报单编号长度的定义
const int STP_ORDERSYSID_LEN = (16 + 1);
///本地报单编号长度的定义
const int STP_ORDERLOCALID_LEN = (12 + 1);
///报单引用长度的定义
const int STP_ORDERREF_LEN = (50 + 1);
///取消报单引用长度的定义
const int STP_ORDERCANCELREF_LEN = (10 + 1);
///交易所交易员代码长度的定义
const int STP_BRANCHPBU_LEN = (20 + 1);
///资金账户代码长度的定义
const int STP_ACCOUNTCODE_LEN = (30 + 1);
///开平标志长度的定义
const int STP_COMBOFFSETFLAG_LEN = (4 + 1);
///投机套保标志长度的定义
const int STP_COMBHEDGEFLAG_LEN = (4 + 1);
///被撤单引用长度的定义
const int STP_ORDERACTIONREF_LEN = (10 + 1);
///状态信息长度的定义
const int STP_STATUSMSG_LEN = (1023 + 1);
///错误信息长度的定义
const int STP_ERRORMSG_LEN = (256 + 1);
///可用组合列表（以|分割）长度的定义
const int STP_COMBOIDLIST_LEN = (512 + 1);
///证券交易代码长度的定义
const int STP_INSTRUMENTCODE_LEN = (20 + 1);
///交易所名称长度的定义
const int STP_EXCHANGENAME_LEN = (50 + 1);
///席位名称长度的定义
const int STP_SEATNAME_LEN = (50 + 1);
///证件号长度的定义
const int STP_IDCARDNO_LEN = (100 + 1);
///投资者账户子编码长度的定义
const int STP_OPTCLIENTID_LEN = (10 + 1);
///分组编号长度的定义
const int STP_GROUPID_LEN = (14 + 1);
///分组名称长度的定义
const int STP_GROUPNAME_LEN = (50 + 1);
///组织架构代码长度的定义
const int STP_DEPARTMENTID_LEN = (14 + 1);
///组织架构名称长度的定义
const int STP_DEPTNAME_LEN = (50 + 1);
///操作员名称长度的定义
const int STP_OPERATORNAME_LEN = (20 + 1);
///产品名称长度的定义
const int STP_PRODUCTNAME_LEN = (50 + 1);
///投资单元代码长度的定义
const int STP_INVESTUNITID_LEN = (14 + 1);
///席位号长度的定义
const int STP_SEATID_LEN = (10 + 1);
///资金账户名称长度的定义
const int STP_ACCOUNTNAME_LEN = (50 + 1);
///币种代码长度的定义
const int STP_CURRENCYID_LEN = (3 + 1);
///投资单元名称长度的定义
const int STP_INVESTUNITNAME_LEN = (50 + 1);
///投资组合代码长度的定义
const int STP_PORTFOLIOID_LEN = (14 + 1);
///交易编码长度的定义
const int STP_TRADECODE_LEN = (18 + 1);
///规则代码长度的定义
const int STP_RULECODE_LEN = (128 + 1);
///规则名称长度的定义
const int STP_RULENAME_LEN = (50 + 1);
///修改内容明细（json字符串）长度的定义
const int STP_VALUE_LEN = (768 + 1);
///预留字段1长度的定义
const int STP_THIRDREFF1_LEN = (20 + 1);
///预留字段2长度的定义
const int STP_THIRDREFF2_LEN = (50 + 1);
///前置地址长度的定义
const int STP_FRONTADDRESS_LEN = (31 + 1);
///流文件路径长度的定义
const int STP_FLOWPATH_LEN = (127 + 1);
///指令代码长度的定义
const int STP_ADMINCODE_LEN = (32 + 1);
///基础商品代码长度的定义
const int STP_UNDERLYINGINSTRUMENTID_LEN = (30 + 1);
///投资组合对应的合约代码长度的定义
const int STP_KEYINSTRUMENTID_LEN = (30 + 1);
///公司名称长度的定义
const int STP_COMPANYNAME_LEN = (50 + 1);
///操作员角色长度的定义
const int STP_OPROLES_LEN = (100 + 1);
///(已废除)操作员可以查询的账户集合长度的定义
const int STP_QRYACCOUNTIDS_LEN = (500 + 1);
///(已废除)操作员可以操作的账户集合长度的定义
const int STP_OPACCOUNTIDS_LEN = (500 + 1);
///操作员可以查询的组合集合长度的定义
const int STP_QRYCOMBOIDS_LEN = (500 + 1);
///操作员可以操作的组合集合长度的定义
const int STP_OPCOMBOIDS_LEN = (500 + 1);
///联系人长度的定义
const int STP_LINKMAN_LEN = (40 + 1);
///联系地址长度的定义
const int STP_ADDRESS_LEN = (50 + 1);
///联系电话长度的定义
const int STP_TEL_LEN = (40 + 1);
///电子邮箱长度的定义
const int STP_EMAIL_LEN = (40 + 1);
///操作员电话长度的定义
const int STP_OPTEL_LEN = (40 + 1);
///操作员邮箱长度的定义
const int STP_OPEMAIL_LEN = (40 + 1);
///注册时间长度的定义
const int STP_REGIDATE_LEN = (14 + 1);
///修改时间长度的定义
const int STP_UPTTIME_LEN = (14 + 1);
///登录时间长度的定义
const int STP_LOGTIME_LEN = (14 + 1);
///密码修改时间长度的定义
const int STP_PWDUPTTIME_LEN = (14 + 1);
///登录错误时间长度的定义
const int STP_LOGERRTIME_LEN = (14 + 1);
///权限ID长度的定义
const int STP_AUTHID_LEN = (8 + 1);
///权限描述长度的定义
const int STP_AUTHDESC_LEN = (30 + 1);
///父权限长度的定义
const int STP_PARENTID_LEN = (8 + 1);
///动作长度的定义
const int STP_ACTION_LEN = (60 + 1);
///动作描述长度的定义
const int STP_ACTIONDESC_LEN = (3000 + 1);
///保留长度的定义
const int STP_RESV_LEN = (300 + 1);
///创建时间长度的定义
const int STP_CRTTIME_LEN = (14 + 1);
///最近一次更新时间长度的定义
const int STP_LASTUPTTIME_LEN = (14 + 1);
///最近一次使用时间长度的定义
const int STP_LASTUSRTIME_LEN = (14 + 1);
///接口标识长度的定义
const int STP_CMDID_LEN = (100 + 1);
///系统流水长度的定义
const int STP_SYSSEQID_LEN = (10 + 1);
///后缀文件类型长度的定义
const int STP_FILEPOSTFIX_LEN = (10 + 1);
///角色号长度的定义
const int STP_ROLEID_LEN = (3 + 1);
///角色名称长度的定义
const int STP_ROLENAME_LEN = (20 + 1);
///文件名称长度的定义
const int STP_FILENAME_LEN = (120 + 1);
///文件存储路径长度的定义
const int STP_FILEURL_LEN = (120 + 1);
///文件查询条件长度的定义
const int STP_FILEINFO_LEN = (120 + 1);
///序列名称长度的定义
const int STP_SEQNAME_LEN = (50 + 1);
///连接IP地址白名单长度的定义
const int STP_IPADDRESS_LEN = (500 + 1);
///最近缴费时间长度的定义
const int STP_LASTPAYTIME_LEN = (14 + 1);
///缴费时间长度的定义
const int STP_PAYTIME_LEN = (14 + 1);
///客户号长度的定义
const int STP_CLIENTID_LEN = (50 + 1);
///通道名称长度的定义
const int STP_CHANNELNAME_LEN = (50 + 1);
///分仓接口IP长度的定义
const int STP_SYSIP_LEN = (20 + 1);
///分仓接口端口长度的定义
const int STP_SYSPORT_LEN = (10 + 1);
///分仓其他配置长度的定义
const int STP_CHANNELCONFIG_LEN = (256 + 1);
///备注长度的定义
const int STP_REMARK_LEN = (200 + 1);
///订单IP长度的定义
const int STP_ORDERIP_LEN = (20 + 1);
///订单MAC长度的定义
const int STP_ORDERMAC_LEN = (20 + 1);
///订单硬盘序列号长度的定义
const int STP_ORDERHDNUM_LEN = (50 + 1);
///订单机器码长度的定义
const int STP_ORDERMACCODE_LEN = (50 + 1);
///订单操作系统长度的定义
const int STP_ORDEROS_LEN = (50 + 1);
///交易所代码长度的定义
const int STP_EXCHANGEIDS_LEN = (256 + 1);
///账户集合长度的定义
const int STP_ACCOUNTIDS_LEN = (512 + 1);
///证券代码集合长度的定义
const int STP_INSTRUMENTIDS_LEN = (512 + 1);
///O32操作员代码长度的定义
const int STP_O32OPERATORNO_LEN = (15 + 1);
///O32操作员密码长度的定义
const int STP_O32OPERATORPWD_LEN = (15 + 1);
///O32基金代码长度的定义
const int STP_O32ACCOUNTCODE_LEN = (31 + 1);
///O32组合编号长度的定义
const int STP_O32COMBINO_LEN = (15 + 1);
///O32资产单元编号长度的定义
const int STP_O32ASSETNO_LEN = (15 + 1);
///客户端特征码长度的定义
const int STP_FEATURETOKEN_LEN = (500 + 1);
///终端版本号长度的定义
const int STP_TERMINALVERESION_LEN = (32 + 1);
///终端特征码长度的定义
const int STP_FEATURECODE_LEN = (100 + 1);
///MAC地址列表长度的定义
const int STP_MACADDRESSES_LEN = (200 + 1);
///参数标识长度的定义
const int STP_SYSTEMCONFIGKEY_LEN = (64 + 1);
///参数项名称长度的定义
const int STP_SYSTEMCONFIGNAME_LEN = (64 + 1);
///参数类型长度的定义
const int STP_SYSTEMCONFIGTYPE_LEN = (64 + 1);
///参数值长度的定义
const int STP_SYSTEMCONFIGVALUE_LEN = (64 + 1);
///证券类别
const int STP_PRODUCTCLASS_LEN = (3 + 1);
///成交编号长度
const int STP_DEALNO_LEN = (64 + 1);
///高级订单条件(内容)长度
const int STP_SENIOR_ORDER_LEN = 102400;
///高级订单主推序号长度
const int STP_SENIOR_ORDER_PUSHNO_LEN = 11;
///方案名称长度
const int STP_NICKNAME_LEN = 100 + 1;
///算法ID长度
const int STP_ALGOID_LEN = 100 + 1;
//用户token长度
const int STP_USERTOKEN_LEN = 128 + 1;
//组合篮子ID长度
const int STP_COMBOID_LEN = 10 + 1;
const int STP_TYPE_LENGTH = 4 + 1;
const int STP_COMPACT_ID_STR_LEN = 2000 + 1;

const int STP_ENTRUST_PROP_LEN = 4;
const int STP_EN_ASSURE_STATUS_LEN = 21;
const int STP_EXCHANGE_TYPE_LEN = 5;
const int STP_STOCK_TYPE_LEN = 5;
const int STP_EN_COMPACT_POSTPONE_STATUS_LEN = 33;
const int STP_RETURNBUSIN_KIND_LEN = 5;
const int STP_STOCK_GROUP_NAME_LEN = 65;
const int STP_BUSINESS_FLAG_LEN = 7;
const int STP_BANK_NO_LEN = 5;
const int STP_BANK_NAME_LEN = 65;
const int STP_TRANS_NAME_LEN = 65;
const int STP_CANCEL_INFO_LEN = 21;
const int STP_BANK_ERROR_INFO_LEN = 2001;
const int STP_OP_STATION_LEN = 256;
/// 期权类型
const int STP_OPTION_TYPE_LEN = (1 + 1);
/// 期权定价模型
const int STP_OPTPRICE_MODEL_LEN = (4 + 1);
///期权组合持仓编码
const int STP_COMBISTRATEGY_ID_LEN = (32 + 1);
///期权组合策略代码
const int STP_COMBISTRATEGY_CODE_LEN = (32 + 1);
///期权持仓类别
const int STP_OPTHOLD_TYPE_LEN = (2 + 1);
///波动率计算周期
const int STP_VOLITILITY_COMPUTE_PERIOD_LEN = (4 + 1);
///合约编码
const int STP_CONTRACT_CODE_LEN = (32 + 1);
///合约委托编号
const int STP_CONTRACT_ORDER_ID_LEN = (32 + 1);
///拒绝理由
const int STP_REJECT_REASON_LEN = (200 + 1);
///菜单权限
const int STP_AUTH_INFO_LEN = (10240 + 1);
///集中度超限股票串
const int STP_OVER_CONCENTRATION_STK_STR_LEN = (1024 + 1);
///dma委托主推编号长度
const int STP_DMA_ORDER_PUSHNO_LEN = (64 + 1);
///dma客户编号长度
const int STP_PARTY_CODE_LEN = (255 + 1);
///dm客户名称长度
const int STP_PARTY_NAME_LEN = (255 + 1);
///账号串长度
const int STP_ACCOUNT_ID_STR_LEN = (1024 + 1);
///交易状态长度
const int STP_TRADE_STATUS_LEN = (4 + 1);
///审核方式长度
const int STP_AUDIT_WAY_LEN = (4 + 1);
///操作类型长度
const int STP_OPERATE_TYPE_LEN = (2 + 1);
///模板编号长度
const int STP_MODEL_ID_LEN = (64 + 1);
///模板名称长度
const int STP_MODEL_NAME_LEN = (64 + 1);
///开平方向长度
const int STP_OC_DIRECTION_LEN = (4 + 1);
///费用模板串长度
const int STP_FARE_MODEL_STR_LEN = (2048 + 1);
///证券二级类别长度
const int STP_SUB_PRODUCTCLASS_LEN = (16 + 1);
///期货品种长度
const int STP_FUTURES_KIND_LEN = (16 + 1);


///////////////////////////错误号定义////////////////////////////

////////////////OnFrontDisConnect关联的错误号//////////////////
const int ERR_READ_RTN_NO = 4;     //网络读取失败导致关闭连接
const int ERR_WRITE_RTN_NO = 5;    //网络异步写入异常导致关闭连接
const int WAR_NORMAL_CLOSE_NO = 6; //正常退出关闭连接
const int ERR_CONNECT_TIMEOUT = 7; //超时导致关闭连接

static const char* STP_EXCHANGE_SSE = "SH";
static const char* STP_EXCHANGE_SZSE = "SZ";
static const char* STP_EXCHANGE_CFFEX = "CFFEX";
static const char* STP_EXCHANGE_SHFE = "SHFE";
static const char* STP_EXCHANGE_DCE = "DCE";
static const char* STP_EXCHANGE_CZCE = "CZCE";
static const char* STP_EXCHANGE_INE = "INE";
//}}

#endif
