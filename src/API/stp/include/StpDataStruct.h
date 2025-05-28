#pragma once

#ifndef STP_DATA_STRUCT_H
#define STP_DATA_STRUCT_H

#include "string.h"
#include "StpDataType.h"
#pragma warning (disable : 4996 4200)
#pragma pack(push,1)
//namespace ctzq{ namespace stp{

//  网关登录
struct MsgLogin
{
    SendCompIDType GwLoginUserName; //  发送方代码
    TargetCompIDType TargetCompId;  //  接收方代码
    HeartBtType HeartBtInt;         //  心跳时间间隔
    PasswordType Password;          //  密码
    MacAddressType MacAddress;
    HardDiskSerialType DiskSerial;
    LicenseType License;
    DefaultAppVerIDType DefaultAppVerId; //  协议版本
    ClientNameType ClientCode;
    MD5ValueType Md5Value;
    BsuccessType Bsuccess;
    SessionIDType SessionID; //会话ID
};

//  网关注销
struct MsgLogout
{
    SessionIDType SessionID; //会话ID
    SendCompIDType GwLoginUserName;
    TargetCompIDType TargetCompId;
};

//  心跳消息
struct MsgHeartBeat
{
    SessionIDType SessionID; //会话ID
    TestReqIDType TestReqId; // 测试请求标志
};

//  同步消息
struct MsgSync
{
    SyncType Bcomplete;
};

///报单
struct StpOrderField
{
    ///交易日
    int TradingDay;
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///组合编号
    // int ComboID;
    ///会话编号
    SessionIDType SessionID;
    ///前置编号
    int FrontID;
    ///报单引用
    char OrderRef[STP_ORDERREF_LEN];
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///席位号
    char SeatID[STP_SEATID_LEN];
    ///本地报单编号
    char OrderLocalID[STP_ORDERLOCALID_LEN];
    ///买卖方向
    char Direction;
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///交易编码
    char TradeCode[STP_TRADECODE_LEN];
    ///营业部代码
    char BranchID[STP_BRANCHID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///报单价格条件
    char OrderPriceType;
    ///开平标志
    char CombOffsetFlag[STP_COMBOFFSETFLAG_LEN];
    ///投机套保标志
    char CombHedgeFlag[STP_COMBHEDGEFLAG_LEN];
    ///备兑标志
    char CoveredFlag;
    ///价格
    double LimitPrice;
    ///原始数量
    int VolumeTotalOriginal;
    ///有效期类型
    char TimeCondition;
    ///成交量类型
    char VolumeCondition;
    ///最小成交量
    int MinVolume;
    ///触发条件
    char ContingentCondition;
    ///止损价
    double StopPrice;
    ///请求编号
    int ORRequestID;
    ///报单编号
    char OrderSysID[STP_ORDERSYSID_LEN];
    ///报单状态
    char OrderStatus;
    ///报单类型
    char OrderType;
    ///今成交数量
    int VolumeTraded;
    ///今成交金额
    double AmountTraded;
    ///剩余数量
    int VolumeRemain;
    ///报单日期
    int InsertDate;
    ///委托时间
    int InsertTime;
    ///最后修改时间
    int UpdateTime;
    ///撤销时间
    int CancelTime;
    ///被撤单引用
    // char OrderActionRef[STP_ORDERACTIONREF_LEN]; 
    ///状态信息
    char StatusMsg[STP_STATUSMSG_LEN]; //可能存在中文需要转码
    ///发起标志
    char OwnerType;
    ///预留字段1
    char ThirdReff1[STP_THIRDREFF1_LEN]; //可能存在中文需要转码
    ///预留字段2
    char ThirdReff2[STP_THIRDREFF2_LEN]; //可能存在中文需要转码
    ///撤成\废单数量
    int VolumeCanceled;
    ///备注
    char Remark[STP_REMARK_LEN]; //可能存在中文需要转码
    ///撤单标志
    char CancelFlag;
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];
    ///当前资金
    double Balance;
    ///手续费
    double Commission;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///订单类型
    char SeniorOrderType;
    ///高级订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///委托属性
    char EntrustProp[3];
    ///委托批号
    int BatchNo;
    ///委托类型
    char EntrustType; 
    ///合约ID
    int64_t ContractID;                                       
    ///合约编码
    char ContractCode[STP_CONTRACT_CODE_LEN];               
    ///合约委托编号
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];       
    ///initialized to zero
    StpOrderField()
    {
        memset(this, 0, sizeof(StpOrderField));
    }
};

///成交
struct StpTradeField
{
    ///交易日
    int TradingDay;
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///组合编号
    // int ComboID;
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///成交编号
    char TradeID[STP_TRADEID_LEN];
    ///买卖方向
    char Direction;
    ///交易编码
    char TradeCode[STP_TRADECODE_LEN];
    ///席位号
    char SeatID[STP_SEATID_LEN];
    ///营业部代码
    char BranchID[STP_BRANCHID_LEN];
    ///证券交易代码
    // char InstrumentCode[STP_INSTRUMENTCODE_LEN]; 
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///请求编号
    int ORRequestID;
    ///报单编号
    char OrderSysID[STP_ORDERSYSID_LEN];
    ///本地报单编号
    char OrderLocalID[STP_ORDERLOCALID_LEN];
    ///报单引用
    char OrderRef[STP_ORDERREF_LEN];
    ///开平标志、成交类型
    char OffsetFlag;
    ///备兑标志
    char CoveredFlag;
    ///投机套保标志
    char HedgeFlag;
    ///价格
    double Price;
    ///成交量
    int Volume;
    ///成交金额
    double TradeAmount;
    ///交易日
    int TradeDate;
    ///成交时间
    int TradeTime;
    ///手续费
    // double Commission;
    ///序号
    char SequenceNo[STP_TRADEID_LEN];
    ///发起标志
    char OwnerType;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///订单类型
    char SeniorOrderType;
    ///高级订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///委托属性
    char EntrustProp[3];
    char EntrustType; //委托类型
    ///合约ID
    int64_t ContractID;
    ///合约编码
    char ContractCode[STP_CONTRACT_CODE_LEN];
    ///合约委托编号
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];

    ///initialized to zero
    StpTradeField()
    {
        memset(this, 0, sizeof(StpTradeField));
    }
};

///返回信息
struct StpRspInfoField
{
    ///错误代码
    int ErrorID;
    ///结束标志
    int IsLast;
    ///错误信息
    char ErrorMsg[STP_ERRORMSG_LEN]; //可能存在中文需要转码
    int TradeNodeType;               //交易中心类型

    ///initialized to zero
    StpRspInfoField()
    {
        memset(this, 0, sizeof(StpRspInfoField));
    }
};

///登录请求
struct StpOperatorLoginReqField
{
    ///登录ID
    char LoginID[STP_LOGINID_LEN];
    ///密码
    char Password[STP_PASSWORD_LEN];
    ///客户端特征码
    char FeatureToken[STP_FEATURETOKEN_LEN];

    char OpStation[256]; //站点地址

    ///initialized to zero
    StpOperatorLoginReqField()
    {
        memset(this, 0, sizeof(StpOperatorLoginReqField));
    }
};

///资金账号信息
struct StpAccountInfoField
{
    ///账户ID
    //char AccountID[32];
    char AccountID[STP_ACCOUNTID_LEN];
    ///账户名称
    char AccountName[STP_ACCOUNTNAME_LEN]; //可能存在中文需要转码
    ///账户类型
    AccountTypeType AccountType;
    ///业务范围
    char TradeRight[STP_AUTHDESC_LEN];
    ///投机套保标志(投资权限范围)
    char InvestType[STP_AUTHDESC_LEN];
    /// <summary>
    /// 账户所在交易中心ID
    /// </summary>
    int NodeId;
    ///initialized to zero
    StpAccountInfoField()
    {
        memset(this, 0, sizeof(StpAccountInfoField));
    }
};

///登入请求响应
struct StpRspLoginField
{
    ///交易日
    int TradingDay;
    ///登录成功时间
    int LoginTime;
    ///登陆ID
    char LoginID[STP_LOGINID_LEN];
    //操作员ID
    char OperatorID[STP_OPERATORID_LEN];
    ///前置编号
    int FrontID;
    ///会话编号
    SessionIDType SessionID; //会话ID 
    ///最大报单引用
    int MaxOrderRef;

    ///initialized to zero
    StpRspLoginField()
    {
        memset(this, 0, sizeof(StpRspLoginField));
    }
};

///操作员修改登录密码请求
struct StpPasswordChangeReqField
{
    //操作员ID
    char OperatorID[STP_OPERATORID_LEN];
    ///原密码
    char OldPassword[STP_PASSWORD_LEN];
    ///新密码
    char NewPassword[STP_PASSWORD_LEN];

    StpPasswordChangeReqField()
    {
        memset(this, 0, sizeof(StpPasswordChangeReqField));
    }
};

///报单录入请求
struct StpOrderInsertReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///组合编号
    // int ComboID;
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///报单引用
    char OrderRef[STP_ORDERREF_LEN];
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///报单价格条件
    char OrderPriceType;
    ///买卖方向
    char Direction;
    ///开平标志
    char CombOffsetFlag[STP_COMBOFFSETFLAG_LEN];
    ///投机套保标志
    char CombHedgeFlag[STP_COMBHEDGEFLAG_LEN];
    ///备兑标志
    char CoveredFlag;
    ///价格
    double LimitPrice;
    ///原始数量
    int VolumeTotalOriginal;
    ///有效期类型
    char TimeCondition;
    ///成交量类型
    char VolumeCondition;
    ///最小成交量
    int MinVolume;
    ///预留字段1
    char ThirdReff1[STP_THIRDREFF1_LEN]; //可能存在中文需要转码
    ///预留字段2
    char ThirdReff2[STP_THIRDREFF2_LEN]; //可能存在中文需要转码
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];
    //委托类型
    char EntrustType;
    //合约编号串
    char CompactIdStr[STP_COMPACT_ID_STR_LEN];
    //委托属性
    char EntrustProp[STP_ENTRUST_PROP_LEN];
    ///initialized to zero
    StpOrderInsertReqField()
    {
        memset(this, 0, sizeof(StpOrderInsertReqField));
    }
};

///取消报单请求
struct StpOrderCancelReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///组合编号
    // int ComboID;
    ///被撤单引用
    char OrderRef[STP_ORDERREF_LEN];
    ///本地报单编号
    char OrderLocalID[STP_ORDERLOCALID_LEN];
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];
    //备注
    char Remark[STP_REMARK_LEN];
    ///委托类型  0-普通委托；1-dma委托
    int OrderType;
    ///高级订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///initialized to zero
    StpOrderCancelReqField()
    {
        memset(this, 0, sizeof(StpOrderCancelReqField));
    }
};

///查询合约信息
struct StpQryInstrumentField
{
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///initialized to zero
    StpQryInstrumentField()
    {
        memset(this, 0, sizeof(StpQryInstrumentField));
    }
};

///合约信息
struct StpInstrumentField
{
    ///交易日
    char TradingDate[100];

    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///产品代码
    // char ProductID[STP_PRODUCTID_LEN]; 
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///证券交易代码
    char InstrumentCode[STP_INSTRUMENTCODE_LEN];
    ///合约名称
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //可能存在中文需要转码
    ///证券类别
    char ProductClass[STP_PRODUCTCLASS_LEN];
    ///证券二级类别
    char SubProductClass[100];
    ///期货品种
    char FuturesKind[100];
    ///合约数量乘数
    double VolumeMultiple;
    ///最小变动价位
    double PriceTick;
    ///当前是否交易
    char IsTrading[100];
    ///期权执行价格
    double ExecPrice;
    ///期权单手保证金
    double UnitMargin;
    ///上市日
    char OpenDate[100];
    ///到期日
    char ExpireDate[100];
    ///行权日
    char ExerciseDay[100];
    ///开始交割日
    char StartDeliveryDay[100];
    ///结束交割日
    char EndDeliveryDay[100];
    ///市价最大下单量
    double MaxMarketOrderVolume;
    ///市价最小下单量
    double MinMarketOrderVolume;
    ///限价最大下单量
    double MaxLimitOrderVolume;
    ///限价最小下单量
    double MinLimitOrderVolume;
    ///涨停板价
    double UpperLimitPrice;
    ///跌停板价
    double LowerLimitPrice;
    ///昨收盘价
    double PreClosePrice;
    ///上次结算价
    double PreSettlementPrice;
    ///期权类型
    char OptionType[100];
    ///最小买入变动手数
    double BuyVolumeTick;
    ///最小卖出变动手数
    double SellVolumeTick;
    ///合约标的市场
    char UnderlyingExchangeId[100];
    ///合约标的代码
    char UnderlyingInstrumentId[STP_UNDERLYINGINSTRUMENTID_LEN];
    ///回报证券标志
    char StockRealBack[100];
    ///回报资金标志
    char FundRealBack[100];
    ///期权执行方式
    char UnderlyingType[100];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///更新时间戳
    char UpdateTm[100];
    ///数据类型说明
    char DataCategory[100];
    ///证券全称
    char InstrumentAllname[512];
    ///期货品种名称
    char FuturesKindName[128];
    ///initialized to zero
    StpInstrumentField()
    {
        memset(this, 0, sizeof(StpInstrumentField));
    }
};

///查询账户资金
struct StpQryAccountAssetField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    //备注
    char Remark[STP_REMARK_LEN];
    //币种类别
    char MoneyType;
    //交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///initialized to zero
    StpQryAccountAssetField()
    {
        memset(this, 0, sizeof(StpQryAccountAssetField));
    }
};

///查询投资者持仓
struct StpQryPositionField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];

    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    //备注
    char Remark[STP_REMARK_LEN];
    ///initialized to zero
    StpQryPositionField()
    {
        memset(this, 0, sizeof(StpQryPositionField));
    }
};

///账户资金信息
struct StpUserAccountAssetField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///资金账户名称
    char AccountName[STP_ACCOUNTNAME_LEN]; //可能存在中文需要转码
    ///当前资金 映射 现金余额  O32现货现金余额
    double Balance;
    ///可用资金  映射 O32现货T+1可用资金  证券柜台的可用资金  期货柜台的可用保证金
    double EnableBalance;
    ///映射O32 T+0可用资金
    double T0EnableBalance;
    //期货保证金余额
    double FuBalance;
    ///映射O32 期货可用保证金
    double O32FuEnableBalance;
    ///期货持仓盈亏  
    double PositionProfit;
    ///期货平仓盈亏
    double CloseProfit;;
    ///保证金占用，add by fengrx 20200702
    double OccupyMargin;
    //可取资金
    double FetchBalance;
    //期权占用保证金
    double OptMarginBalance; 
    //期权可用保证金
    double OptUsableBalance;
    //期权保证金账户余额
    double OptEnableBalance; 
    //期权挂单占用保证金
    double OptTempOccupyMargin; 

    ///initialized to zero
    StpUserAccountAssetField()
    {
        memset(this, 0, sizeof(StpUserAccountAssetField));
    }
};

///组合持仓信息
struct StpUserComboPositionField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///账户名称
    char AccountName[STP_ACCOUNTNAME_LEN]; //可能存在中文需要转码

    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///合约名称
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //可能存在中文需要转码
    ///昨持仓               //期权当前数量
    double YdPosition;    
    ///今持仓
    double TodayPosition;
    ///总持仓
    double TotalPosition;

    ///今仓可用数量
    double TodayEnableVolume;
    ///昨仓可用数量
    double YdEnableVolume;
    ///可用数量
    double EnableVolume;
    ///持仓成本            //期权当前成本
    double PositionCost;
    ///成本价              //期权期初成本
    double CostPrice;
    ///最新价
    double LastPrice;
    ///持仓市值
    double OpenMarketValue;
    ///浮动盈亏
    double FloatProfit;

    ///持仓多空方向
    char PosiDirection;
    ///投机套保标志
    char HedgeFlag;
    ///平仓盈亏
    double CloseProfit;
    ///仓位占用保证金
    double UseMargin;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    //期权类型
    char OptionType[STP_OPTION_TYPE_LEN]; 
    //期权持仓类型
    char OptholdType[STP_OPTHOLD_TYPE_LEN]; 
    // 期权当日开仓数量
    double TodayOpenVolume;
    // 期权当日平仓数量
    double TodayDropVolume;
    // 期权当日买入金额
    double TodayBuyBalance;
    // 期权当日卖出金额
    double TodaySellBalance;

    ///initialized to zero
    StpUserComboPositionField()
    {
        memset(this, 0, sizeof(StpUserComboPositionField));
    }
};

///持仓明细
struct StpPositionDetailField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///账户名称
    char AccountName[STP_ACCOUNTNAME_LEN];
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///合约代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///合约名称
    char InstrumentName[STP_INSTRUMENTNAME_LEN];
    ///多空标志
    char PosiDirection;
    ///投机套保标志
    char HedgeFlag;
    //开仓日期
    int OpenDate;
    //成交编号
    char DealNo[STP_DEALNO_LEN];
    //开仓数量
    int OpenVolume;
    //当前数量
    int CurrentVolume;
    //平仓数量
    int DropVolume;
    //占用保证金
    double UseMargin;
    //开仓价
    double OpenPrice;
    //平仓收益
    double CloseProfit;
    //总费用
    double TotalFee;
    //前结算价
    double LastSettlePrice;
    //合约乘数
    int Multiply;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];

    StpPositionDetailField()
    {
        memset(this, 0, sizeof(StpPositionDetailField));
    }
};

///查询报单
struct StpQryOrderField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char OrderLocalID[STP_ORDERLOCALID_LEN]; //本地报单编号
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串
    int BeginDate;                           //起始日期
    int EndDate;                             //到期日期
    char EntrustProp[STP_ENTRUST_PROP_LEN];  //委托属性
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号

    StpQryOrderField()
    {
        memset(this, 0, sizeof(StpQryOrderField));
    }
};

///查询成交
struct StpQryTradeField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char TradeID[STP_TRADEID_LEN];           //成交编号
    char OrderLocalID[STP_ORDERLOCALID_LEN]; //本地报单编号
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串
    int BeginDate;                           //起始日期
    int EndDate;                             //到期日期
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号

    StpQryTradeField()
    {
        memset(this, 0, sizeof(StpQryTradeField));
    }
};

///查询资金流水
struct StpQryFundJourField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///币种类型
    char MoneyType[4];
    //当前日期
    int CurrentDate;
    //回溯量，>0表示向后追溯，=0表示当前，<0表示向前追溯
    int Range;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];

    int EndDate;
    ///initialized to zero
    StpQryFundJourField()
    {
        memset(this, 0, sizeof(StpQryFundJourField));
    }
};

///资金流水
struct StpFundJourField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///流水序号
    char SerialNo[10];
    ///成交日期
    int BusinessDate;
    ///业务标志
    int BusinessFlag;
    ///业务名称
    char BusinessName[17];
    ///发生金额
    double OccurBalance;
    ///后资金额
    double PostBalance;
    ///币种类别
    char MoneyType[4];
    ///交易类别
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///证券账号
    char StockAccount[12];
    ///合约代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///合约名称
    char InstrumentName[STP_INSTRUMENTNAME_LEN];
    ///买卖方向
    char Direction;
    ///成交价格
    double BusinessPrice;
    ///发生数量
    int OccurAmount;
    ///备注
    char Remark[STP_REMARK_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///银行代码
    char BankNo[5];
    ///银行名称
    char BankName[65];
    ///initialized to zero
    StpFundJourField()
    {
        memset(this, 0, sizeof(StpFundJourField));
    }
};

//批量委托应答
struct StpOrderBatchField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///报单引用
    char OrderRef[STP_ORDERREF_LEN];
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///预留字段1
    char ThirdReff1[STP_THIRDREFF1_LEN]; //可能存在中文需要转码
    ///预留字段2
    char ThirdReff2[STP_THIRDREFF2_LEN]; //可能存在中文需要转码
    ///本地报单编号
    char OrderLocalID[STP_ORDERLOCALID_LEN];
    ///错误代码
    int ErrorID;
    ///错误信息
    char ErrorMsg[STP_ERRORMSG_LEN]; //可能存在中文需要转码
    StpOrderBatchField()
    {
        memset(this, 0, sizeof(StpOrderBatchField));
    }
};

//新股申购信息查询
struct StpQryNewStkInfoField
{
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    int IssueDate;                           //发行日期
    char ExchangeID[STP_EXCHANGEID_LEN];     //市场
    char SubProductClass[100];               //证券子类
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串

    StpQryNewStkInfoField()
    {
        memset(this, 0, sizeof(StpQryNewStkInfoField));
    }
};

struct StpNewStkInfoField
{
    char InstrumentID[STP_INSTRUMENTID_LEN];     //证券代码
    char ExchangeID[STP_EXCHANGEID_LEN];         //市场
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //证券名称
    char MoneyType[STP_TYPE_LENGTH];             //币种类别
    char ProductClass[STP_PRODUCTCLASS_LEN];     //证券类别
    int BuyUnit;                                 //买入单位
    int PriceStep;                               //最小价差
    int StoreUnit;                               //存放单位
    double ParValue;                             //面值
    char StkcodeStatus;                          //证券状态
    double UpPrice;                              //上限价
    double DownPrice;                            //下限价
    int HighAmount;                              //交易最高数量
    int LowAmount;                               //交易最低数量
    int IssueDate;                               //发行日期
    double LastPrice;                            //最新价
    char SubProductClass[100];                   //证券子类
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串
    char AccountID[STP_ACCOUNTID_LEN];           //账户编号
    char StkCodeCtrlStr[257];                    // 代码业务控制串
    StpNewStkInfoField()
    {
        memset(this, 0, sizeof(StpNewStkInfoField));
    }
};

// 历史配号信息查询
struct StpQryHisMatchInfoField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    int BeginDate;                           //开始日期
    int EndDate;                             //结束日期
    char ExchangeID[STP_EXCHANGEID_LEN];     //市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char StockType[STP_STOCK_TYPE_LEN]; ;    //证券类别
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串

    StpQryHisMatchInfoField()
    {
        memset(this, 0, sizeof(StpQryHisMatchInfoField));
    }
};

struct StpHisMatchInfoField
{
    int SerialNo;                                //流水序号
    int OccurAmount;                             //发生数量
    char ExchangeID[STP_EXCHANGEID_LEN];         //交易类别
    char InstrumentID[STP_INSTRUMENTID_LEN];     //证券代码
    char StockType[STP_STOCK_TYPE_LEN];          //证券类别
    char Remark[STP_REMARK_LEN];                 //备注
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串
    char AccountID[STP_ACCOUNTID_LEN];           //资产账户
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //证券名称
    int ReportTime;                              //申报时间
    int InitDate;                                //交易日期
    int BusinessTime;                            //成交时间
    int BusinessAmount;                          //成交数量
    double BusinessBalance;                      //成交金额
    double BusinessPrice;                        //成交价格
    char BusinessFlag[STP_BUSINESS_FLAG_LEN];    //业务标志
    char EntrustWay;                             //委托方式
    char TradeID[STP_TRADEID_LEN];               //成交编号
    double ClearBalance;                         //清算金额
    char Direction;                              //买卖方向
    char BusinessType;                           //业务类型
    double OccurBalance;                         //发生金额
    int EntrustNo;                               //委托编号
    char BusinessStatus;                         //业务状态
    char MoneyType[STP_TYPE_LENGTH];             //币种类别

    StpHisMatchInfoField()
    {
        memset(this, 0, sizeof(StpHisMatchInfoField));
    }
};

//历史中签信息查询
struct StpQryHisLuckyInfoField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    int BeginDate;                           //开始日期
    int EndDate;                             //结束日期
    char ExchangeID[STP_EXCHANGEID_LEN];     //市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char StockType[STP_STOCK_TYPE_LEN]; ;    //证券类别
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串

    StpQryHisLuckyInfoField()
    {
        memset(this, 0, sizeof(StpQryHisLuckyInfoField));
    }
};

struct StpHisLuckyInfoField
{
    char ExchangeID[STP_EXCHANGEID_LEN];         //市场
    char InstrumentID[STP_INSTRUMENTID_LEN];     //证券代码
    double BusinessPrice;                        //交易价格
    int OccurAmount;                             //发生数量
    int InitDate;                                //交易日期
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串
    char StockType[STP_STOCK_TYPE_LEN];          //证券类别
    char AccountID[STP_ACCOUNTID_LEN];           //账户编号
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //证券名称

    StpHisLuckyInfoField()
    {
        memset(this, 0, sizeof(StpHisLuckyInfoField));
    }
};

//新股额度查询
struct StpQryNewStkQuotaField
{
    char AccountID[STP_ACCOUNTID_LEN];   //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN]; //市场

    StpQryNewStkQuotaField()
    {
        memset(this, 0, sizeof(StpQryNewStkQuotaField));
    }
};

struct StpNewStkQuotaField
{
    char AccountID[STP_ACCOUNTID_LEN];   //账户
    int InitDate;                        //交易日期
    int BranchNo;                        //营业部号
    char ExchangeID[STP_EXCHANGEID_LEN]; //市场类别
    int EnableAmount;                    //可用数量
    int RegisterDate;                    //登记日期
    int StibEnableQuota;                 //科创板可申购额度
    char StockAccount[12];               //证券账号

    StpNewStkQuotaField()
    {
        memset(this, 0, sizeof(StpNewStkQuotaField));
    }
};

//存管资金账户转账日志查询
struct StpQryBankTransferField
{
    char AccountID[STP_ACCOUNTID_LEN];     //账户
    char BankNo[STP_BANK_NO_LEN];          //银行代码
    int EntrustNo;                         //委托编号
    char PositionStr[STP_POSITIONSTR_LEN]; //定位串
    int BeginDate;                         //开始日期
    int EndDate;                           //结束日期

    StpQryBankTransferField()
    {
        memset(this, 0, sizeof(StpQryBankTransferField));
    }
};

struct StpBankTransferField
{
    char AccountID[STP_ACCOUNTID_LEN];           //账户
    int BranchNo;                                //分支机构
    char BankNo[STP_BANK_NO_LEN];                //银行代码
    char BankName[STP_BANK_NAME_LEN];            //银行名称
    char TransName[STP_TRANS_NAME_LEN];          //转换机名字
    int EntrustNo;                               //委托编号
    char SourceFlag;                             //发起方
    char MoneyType[STP_TYPE_LENGTH];             //币种类别
    double OccurBalance;                         //发生金额
    int EntrustTime;                             //委托时间
    char BktransStatus;                          //请求状态
    int ErrorNoT;                                //错误代码
    char CancelInfo[STP_CANCEL_INFO_LEN];        //废单原因
    char BankErrorInfo[STP_BANK_ERROR_INFO_LEN]; //银行错误信息
    char Remark[STP_BANK_ERROR_INFO_LEN];        //备注
    char AssetProp;                              //资产属性
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串
    char OpStation[STP_OP_STATION_LEN];          //站点地址
    char ExtTransType[3];                        //周边银行业务类别
    char EntrustOccasion[33];                    //委托场景
    int EntrustDate;                             //委托日期
    double PostBalance;                          //后资金额
    int InitDate;                                //交易日期
    int CurrentDate;                             //当前日期

    StpBankTransferField()
    {
        memset(this, 0, sizeof(StpBankTransferField));
    }
};

//客户银行账户查询
struct StpQryBankAccountField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    char BankNo[STP_BANK_NO_LEN];      //银行代码
    char MoneyType[STP_TYPE_LENGTH];   //币种类别

    StpQryBankAccountField()
    {
        memset(this, 0, sizeof(StpQryBankAccountField));
    }
};

struct StpBankAccountField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    int OpenDate;                      //开户日期
    char MoneyType[STP_TYPE_LENGTH];   //币种类别
    char BankNo[STP_BANK_NO_LEN];      //银行代码
    char BankName[STP_BANK_NAME_LEN];  //银行名称
    char BankAccount[33];              //银行账户
    char BkaccountStatus;              //银行账户状态

    StpBankAccountField()
    {
        memset(this, 0, sizeof(StpBankAccountField));
    }
};

//银行余额查询
struct StpQryBankBalanceField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    char BankNo[STP_BANK_NO_LEN];      //银行代码
    char MoneyType[STP_TYPE_LENGTH];   //币种类别
    char FundPwd[16];                  //资金密码
    char BankPwd[16];                  //银行密码

    StpQryBankBalanceField()
    {
        memset(this, 0, sizeof(StpQryBankBalanceField));
    }
};

struct StpBankBalanceField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    int SerialNo;                      //流水号

    StpBankBalanceField()
    {
        memset(this, 0, sizeof(StpBankBalanceField));
    }
};

//银行转账
struct StpReqBankTransferField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    char MoneyType[STP_TYPE_LENGTH];   //币种类别
    char BankNo[STP_BANK_NO_LEN];      //银行代码
    char Direction;                    //交易方向
    double OccurBalance;               //发生金额
    char OrderRef[65];                 //外部订单编号
    char FundPwd[16];                  //资金密码
    char BankPwd[16];                  //银行密码

    StpReqBankTransferField()
    {
        memset(this, 0, sizeof(StpReqBankTransferField));
    }
};

struct StpRspBankTransferField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户
    int EntrustNo;                     //委托编号
    char BankNo[STP_BANK_NO_LEN];      //银行代码
    char Direction;                    //交易方向
    double OccurBalance;               //发生金额
    char MoneyType[STP_TYPE_LENGTH];   //币种类别

    StpRspBankTransferField()
    {
        memset(this, 0, sizeof(StpRspBankTransferField));
    }
};

//高级订单下单
struct StpSeniorOrderReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///订单类型
    char SeniorOrderType;
    //订单执行条件
    char OrderCondition[STP_SENIOR_ORDER_LEN];
    //订单执行内容
    char OrderContents[STP_SENIOR_ORDER_LEN];
    //到期日期
    int ExpiryDate;
    ///报单引用
    char SeniorOrderRef[STP_ORDERREF_LEN];
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];
    ///方案名称
    char NickName[STP_NICKNAME_LEN];
    ///委托总量
    int Volume;
    ///算法ID
    char OrderAlgoID[STP_ALGOID_LEN];

    StpSeniorOrderReqField()
    {
        memset(this, 0, sizeof(StpSeniorOrderReqField));
    }
};

//高级订单操作(暂停、激活、修改、撤销)
struct StpSeniorOrderOperateReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    //订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    //操作类型
    char OperateType;
    //订单执行条件
    char OrderCondition[STP_SENIOR_ORDER_LEN];
    //订单执行内容
    char OrderContents[STP_SENIOR_ORDER_LEN];
    ///方案名称
    char NickName[STP_NICKNAME_LEN];
    ///委托总量
    int Volume;
    ///算法ID
    char OrderAlgoID[STP_ALGOID_LEN];

    StpSeniorOrderOperateReqField()
    {
        memset(this, 0, sizeof(StpSeniorOrderOperateReqField));
    }
};

//高级订单
struct StpSeniorOrderField
{
    //订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///订单类型
    char SeniorOrderType;
    ///会话编号
    SessionIDType SessionID;
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///报单引用
    char SeniorOrderRef[STP_ORDERREF_LEN];
    //订单执行条件
    char OrderCondition[STP_SENIOR_ORDER_LEN];
    //订单执行内容
    char OrderContents[STP_SENIOR_ORDER_LEN];
    //高级订单状态
    char SeniorOrderStatus;
    //创建日期
    int CreateDate;
    //创建时间
    int CreateTime;
    //到期日期
    int ExpiryDate;
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];
    //初始委托总量
    int InitOrderVolume;
    //成交数量
    int TradeVolume;
    //成交金额
    double TradeBalance;
    //委撤比
    double CancelRatio;
    //成交比
    double TradeRatio;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    ///备注
    char Remark[STP_REMARK_LEN]; //可能存在中文需要转码
    //高级订单主推序号
    char SeniorOrderPushNo[STP_SENIOR_ORDER_PUSHNO_LEN];
    ///本地报单编号
    char OrderLocalID[STP_ORDERLOCALID_LEN];
    ///方案名称
    char NickName[STP_NICKNAME_LEN];
    ///委托总量
    int Volume;
    ///算法ID
    char OrderAlgoID[STP_ALGOID_LEN];

    StpSeniorOrderField()
    {
        memset(this, 0, sizeof(StpSeniorOrderField));
    }
};

//高级订单查询请求
struct StpQrySeniorOrderField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///订单类型
    char SeniorOrderType;
    //订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    //操作员编号
    char OperatorID[STP_OPERATORID_LEN];

    StpQrySeniorOrderField()
    {
        memset(this, 0, sizeof(StpQrySeniorOrderField));
    }
};

//算法模板操作请求
struct StpOperateAlgoTemplateReqField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///算法模板id
    char AlgorithTemplateID[STP_ORDERLOCALID_LEN];
    ///算法类型
    char SeniorOrderType;
    ///算法模板名称
    char AlgoTemplateName[STP_NICKNAME_LEN];
    ///算法模板内容
    char AlgorithTemplate[STP_SENIOR_ORDER_LEN];
    ///操作类型
    char AlgoOperateType;

    StpOperateAlgoTemplateReqField()
    {
        memset(this, 0, sizeof(StpOperateAlgoTemplateReqField));
    }
};

//算法模板操作应答
struct StpOperateAlgoTemplateField
{
    ///算法模板id
    char AlgorithTemplateID[STP_ORDERLOCALID_LEN];
    ///操作类型
    char AlgoOperateType;

    StpOperateAlgoTemplateField()
    {
        memset(this, 0, sizeof(StpOperateAlgoTemplateField));
    }
};

//算法模板
struct StpAlgoTemplateField
{
    ///算法模板id
    char AlgorithTemplateID[STP_ORDERLOCALID_LEN];
    ///算法模板名称
    char AlgoTemplateName[STP_NICKNAME_LEN];
    ///算法类型
    char SeniorOrderType;
    ///算法模板
    char AlgorithTemplate[STP_SENIOR_ORDER_LEN];
    //创建日期
    int CreateDate;
    //创建时间
    int CreateTime;
    ///修改日期
    int ModifyDate;
    ///修改时间
    int ModifyTime;

    StpAlgoTemplateField()
    {
        memset(this, 0, sizeof(StpAlgoTemplateField));
    }
};

//算法模板查询
struct StpQryAlgoTemplateField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///算法类型
    char SeniorOrderType;

    StpQryAlgoTemplateField()
    {
        memset(this, 0, sizeof(StpQryAlgoTemplateField));
    }
};

//批量高级订单新增应答
struct StpSeniorOrderBatchField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///算法类型
    char SeniorOrderType;
    ///报单引用
    char SeniorOrderRef[STP_ORDERREF_LEN];
    ///高级订单编号
    char SeniorOrderID[STP_ORDERLOCALID_LEN];
    ///错误代码
    int ErrorID;
    ///错误信息
    char ErrorMsg[STP_ERRORMSG_LEN]; //可能存在中文需要转码
    StpSeniorOrderBatchField()
    {
        memset(this, 0, sizeof(StpSeniorOrderBatchField));
    }
};

//获取用户中心token请求
struct StpUserTokenReqField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///密码
    char Password[STP_PASSWORD_LEN];

    StpUserTokenReqField()
    {
        memset(this, 0, sizeof(StpUserTokenReqField));
    }
};

//获取用户中心token响应
struct StpUserTokenField
{
    //用户token
    char UserToken[STP_USERTOKEN_LEN];

    StpUserTokenField()
    {
        memset(this, 0, sizeof(StpUserTokenField));
    }
};

/*-------------------------------- 融资融券-------------------------------------*/
//现金还款请求
struct StpCreditCashRtnReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    //币种类别
    char MoneyType[STP_TYPE_LENGTH];
    //还款方式
    char PayType;
    //还款金额
    double OccurBalance;
    //合约编号
    char CompactId[STP_ADMINCODE_LEN];
    //头寸性质
    char CashGroupProp;
    //合约编号串
    char CompactIdStr[STP_ACTIONDESC_LEN];

    StpCreditCashRtnReqField()
    {
        memset(this, 0, sizeof(StpCreditCashRtnReqField));
    }
};

struct StpCreditCashRtnField
{
    //发生金额
    double OccurBalance;

    StpCreditCashRtnField()
    {
        memset(this, 0, sizeof(StpCreditCashRtnField));
    }
};

/*--------------------------------两融篮子下单----------------------------------*/
struct StpCreditComboReqField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///篮子编号
    char BasketID[STP_COMBOID_LEN];
    ///组合报单引用
    char ComboOrderRef[STP_ORDERREF_LEN];
    ///指令类型,1=自有资金买入，2=融资优先买入，3=组合卖出，4=融券优先卖出，5=补短仓差,6=补长仓差,7=篮子还券
    char ComboOrderType;
    ///下单篮子个数
    int ComboAmount;
    ///委托时间
    int EntrustTime;
    ///预留字段1
    char ThirdReff1[STP_THIRDREFF1_LEN]; //可能存在中文需要转码
    ///预留字段2
    char ThirdReff2[STP_THIRDREFF2_LEN]; //可能存在中文需要转码
    ///订单IP
    char OrderIP[STP_ORDERIP_LEN];
    ///订单MAC
    char OrderMAC[STP_ORDERMAC_LEN];
    ///订单硬盘序列号
    char OrderHDNum[STP_ORDERHDNUM_LEN];
    ///订单机器码
    char OrderMacCode[STP_ORDERMACCODE_LEN];
    ///订单操作系统
    char OrderOS[STP_ORDEROS_LEN];

    StpCreditComboReqField()
    {
        memset(this, 0, sizeof(StpCreditComboReqField));
    }
};

//两融篮子下单应答
struct StpCreditComboField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///指令类型,1=自有资金买入，2=融资优先买入，3=组合卖出，4=融券优先卖出，5=补短仓差,6=补长仓差,7=篮子还券
    char ComboOrderType;
    ///组合下单编号
    char ComboOrderID[STP_COMBOID_LEN];
    ///组合报单引用
    char ComboOrderRef[STP_ORDERREF_LEN];
    //委托时间
    int EntrustTime;
    //委托成分股数量
    int EntrustAmount;
    //篮子委托金额
    double EntrustBalance;

    StpCreditComboField()
    {
        memset(this, 0, sizeof(StpCreditComboField));
    }
};

//执行列表查询
struct StpQryCreditComboExecField
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///指令类型,指令类型,1=自有资金买入，2=融资优先买入，3=组合卖出，4=融券优先卖出，5=补短仓差,6=补长仓差,7=篮子还券
    char ComboOrderType;
    ///组合下单编号
    char ComboOrderID[STP_COMBOID_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];

    StpQryCreditComboExecField()
    {
        memset(this, 0, sizeof(StpQryCreditComboExecField));
    }
};

//两融篮子执行单
struct StpCreditComboExecField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///指令类型,指令类型,1=自有资金买入，2=融资优先买入，3=组合卖出，4=融券优先卖出，5=补短仓差,6=补长仓差,7=篮子还券
    char ComboOrderType;
    ///组合下单编号
    char ComboOrderID[STP_COMBOID_LEN];
    ///组合报单引用
    char ComboOrderRef[STP_ORDERREF_LEN];
    //委托方向
    char Direction;
    //委托成分股数量
    int EntrustAmount;
    //篮子委托金额
    double EntrustBalance;
    //成交数量
    int TradeAmount;
    //成交金额
    double TradeBalance;
    //成交进度
    double TradePercent;
    //浮动盈亏
    double Profit;
    //委托时间
    int EntrustTime;
    //委托耗时
    int OrderConsumingTime;
    //成交耗时
    int TradeConsumingTime;
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];
    //备注
    char Remark[STP_REMARK_LEN];

    StpCreditComboExecField()
    {
        memset(this, 0, sizeof(StpCreditComboExecField));
    }
};

//两融篮子持仓，查询请求用StpQryPositionField
struct StpCreditComboPosition
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    ///序号
    int SeqNo;
    ///交易所代码
    char ExchangeID[STP_EXCHANGEID_LEN];
    ///证券代码
    char InstrumentID[STP_INSTRUMENTID_LEN];
    ///合约名称
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //可能存在中文需要转码
    ///权重
    double Weight;
    ///样本数量
    int SampleAmount;
    ///alpha数量
    int AlphaAmount;
    ///样本差
    int SampleDiff;
    ///持仓当前数量
    int CurrentAmount;
    ///持仓可用数量
    int EnableAmount;
    ///已融数量
    int UsedLoanAmount;
    ///可融数量
    int EnableLoanAmount;
    ///短仓差
    int ShortDiff;
    ///长仓差
    int LongDiff;
    ///可融资标志
    char MarginF;
    ///可融资状态
    char FinStatus;
    ///可融券标志
    char MarginS;
    ///可融券状态
    char SloStatus;
    ///篮子名称
    char BasketName[STP_NICKNAME_LEN];
    ///定位串
    char PositionStr[STP_POSITIONSTR_LEN];

    StpCreditComboPosition()
    {
        memset(this, 0, sizeof(StpCreditComboPosition));
    }
};

//两融篮子资产信息，查询请求使用StpQryAccountAssetField
struct StpCreditComboAsset
{
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    //总市值
    double MarketValue;
    //总资产
    double AssetValue;
    //长短市值差
    double AssetDiff;
    //废单数量
    int ScrapAmount;
    //撤单数量
    int CancelAmount;
    //短篮子数量
    int ShortBasketNum;
    //长篮子数量
    int LongBasketNum;
    //融资负债
    double FinDebit;
    //融券负债
    double SloDebit;
    //自有资金可用
    double AvailFund;
    //自有资金可买篮子数量
    int OwnFundBuy;
    //融资可用金额
    double AvailMargin;
    //融资优先可买篮子数量
    int MarginPrioBuy;
    //自有可用市值
    double AvailAsset;
    //自有持仓可用可卖篮子数量
    int OwnAssetSell;
    //融券可用金额(融券保证金的金额)
    double AvailSlo;
    //融券可卖篮子数量
    int SloSell;
    //总负债
    double TotalDebit;
    //融资合约金额
    double FinCompactBalance;
    //融资合约费用
    double FinCompactFare;
    //融资合约利息
    double FinCompactInterest;
    //个人维持担保比例
    double PerAssureScaleValue;
    //现金还款可用资金
    double FinEnrepaidBalance;

    StpCreditComboAsset()
    {
        memset(this, 0, sizeof(StpCreditComboAsset));
    }
};

/*----------------------------------------------------------------------*/
//通用回报主推

struct StpCommonPushField
{
    ///操作员代码
    char OperatorID[STP_OPERATORID_LEN];
    ///账户编号
    char AccountID[STP_ACCOUNTID_LEN];
    //推送类型
    char PushType[STP_TYPE_LENGTH];
    //推送序号
    char CommonPushNo[STP_SENIOR_ORDER_PUSHNO_LEN];
    //推送内容
    char CommonPushContent[STP_SENIOR_ORDER_LEN];
    ///会话编号
    SessionIDType SessionID;
    //前置编号
    int FrontID;

    StpCommonPushField()
    {
        memset(this, 0, sizeof(StpCommonPushField));
    }
};

//最大交易数量获取
struct StpQryMaxBuyField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    double EntrustPrice;                     //委托价格
    char EntrustProp[STP_ENTRUST_PROP_LEN];  //委托属性
    char Direction;                          //买卖方向
    char EntrustType;                        //委托类别

    StpQryMaxBuyField()
    {
        memset(this, 0, sizeof(StpQryMaxBuyField));
    }
};

struct StpMaxBuyField
{
    int32_t EnableAmount;                           //可用数量
    int32_t StoreUnit;                              //存放单位
    int32_t EnableBuyAmount;                        //可买数量
    int32_t HighAmount;                             //交易最高数量
    double BusinessAmount2;                         //成交数量2
    int32_t ConfirmAmount;                          //确认数量
    char ReturnbusinKind[STP_RETURNBUSIN_KIND_LEN]; //回报业务类别

    StpMaxBuyField()
    {
        memset(this, 0, sizeof(StpMaxBuyField));
    }
};

struct StpQryCrdtStkInfoField
{
    char AccountID[STP_ACCOUNTID_LEN];             //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN];           //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];       //证券代码
    char PositionStr[STP_POSITIONSTR_LEN];         //定位串
    char EnAssureStatus[STP_EN_ASSURE_STATUS_LEN]; //允许担保状态

    StpQryCrdtStkInfoField()
    {
        memset(this, 0, sizeof(StpQryCrdtStkInfoField));
    }
};

struct StpCrdtStkInfoField
{
    char ExchangeID[STP_EXCHANGEID_LEN];           //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];       //证券代码
    char InstrumentName[STP_INSTRUMENTNAME_LEN];   //证券名称
    double AssureRatio;                            //担保折算率
    double FloatRatio;                             //浮动利率
    char AssureStatus;                             //担保状态
    double AssetPrice;                             //市值价
    char PositionStr[STP_POSITIONSTR_LEN];         //定位串
    char SloSellbuyStatus;                         //融券卖出所得可买状态
    double FairPrice;                              //公允价格
    char FairPriceFlag;                            //公允价格启用标志
    char StockNameLong[STP_INSTRUMENTNAME_LEN];    //证券名称（长）
    char Remark[STP_REMARK_LEN];                   //备注
    double StaticPeRatio;                          //静态市盈率
    int32_t StockGroupNo;                          //证券分组编号
    char StockGroupName[STP_STOCK_GROUP_NAME_LEN]; //证券分组名称

    StpCrdtStkInfoField()
    {
        memset(this, 0, sizeof(StpCrdtStkInfoField));
    }
};

//标的券查询
struct StpQryCrdtTarStkInfoField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char StockType[STP_STOCK_TYPE_LEN];      //证券类别

    StpQryCrdtTarStkInfoField()
    {
        memset(this, 0, sizeof(StpQryCrdtTarStkInfoField));
    }
};

struct StpCrdtTarStkInfoField
{
    char ExchangeID[STP_EXCHANGEID_LEN];         //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN];     //证券代码
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //证券名称
    double FinRatio;                             //融资保证金比例
    double FinFloatRatio;                        //融资浮动比率
    char FinStatus;                              //融资状态
    double SloRatio;                             //融券保证金比例
    double SloFloatRatio;                        //融券浮动比率
    char SloStatus;                              //融券状态
    double AssetPrice;                           //市值价
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串
    int32_t FinEndDate;                          //有效到期日

    StpCrdtTarStkInfoField()
    {
        memset(this, 0, sizeof(StpCrdtTarStkInfoField));
    }
};

//可融券信息查询，专项头寸明细
struct StpQryCrdtEnsloSecyField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char PositionStr[STP_POSITIONSTR_LEN];   //定位串
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char StockType[STP_STOCK_TYPE_LEN];      //证券类别
    char QueryMode;                          //查询模式

    StpQryCrdtEnsloSecyField()
    {
        memset(this, 0, sizeof(StpQryCrdtEnsloSecyField));
    }
};

struct StpCrdtEnsloSecyField
{
    char ExchangeID[STP_EXCHANGEID_LEN];         //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN];     //证券代码
    char InstrumentName[STP_INSTRUMENTNAME_LEN]; //证券名称
    double SloRatio;                             //融券保证金比例
    char SloStatus;                              //融券状态
    int32_t EnableAmount;                        //可用数量
    int32_t RealBuyAmount;                       //回报买入数量
    int32_t RealSellAmount;                      //回报卖出数量
    char CashGroupProp;                          //头寸性质
    char StockType[STP_STOCK_TYPE_LEN];          //证券类别
    char PositionStr[STP_POSITIONSTR_LEN];       //定位串

    StpCrdtEnsloSecyField()
    {
        memset(this, 0, sizeof(StpCrdtEnsloSecyField));
    }
};

//客户信用资产信息获取
struct StpQryCrdtAssetField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    char MoneyType;                    //币种类别

    StpQryCrdtAssetField()
    {
        memset(this, 0, sizeof(StpQryCrdtAssetField));
    }
};

struct StpCrdtAssetField
{
    double MarketValue;          //证券市值
    double AssureAsset;          //担保资产
    double TotalDebit;           //负债总额
    double PerAssurescaleValue;  //个人维持担保比例
    double EnableBailBalance;    //可用保证金
    double UsedBailBalance;      //已用保证金
    double AssureEnbuyBalance;   //买担保品可用资金
    double FinEnbuyBalance;      //买融资标的可用资金
    double SloEnrepaidBalance;   //买券还券可用资金
    double FinEnrepaidBalance;   //现金还款可用资金
    double FinMaxQuota;          //融资额度上限
    double FinEnableQuota;       //融资可用额度
    double FinUsedQuota;         //融资已用额度
    double FinUsedBail;          //融资已用保证金
    double FinCompactBalance;    //融资合约金额
    double FinCompactFare;       //融资合约费用
    double FinCompactInterest;   //融资合约利息
    double FinMarketValue;       //融资市值
    double FinIncome;            //融资合约盈亏
    double SloMaxQuota;          //融券额度上限
    double SloEnableQuota;       //融券可用额度
    double SloUsedQuota;         //融券已用额度
    double SloUsedBail;          //融券已用保证金
    double SloCompactBalance;    //融券合约金额
    double SloCompactFare;       //融券合约费用
    double SloCompactInterest;   //融券合约利息
    double SloMarketValue;       //融券市值
    double SloIncome;            //融券合约盈亏
    double OtherFare;            //其他费用
    double UnderlyMarketValue;   //标的证券市值
    double FinUnbusiBalance;     //融资未成交金额
    double SloUnbusiBalance;     //融券未成交金额
    double EnableOutAsset;       //可转出资产
    double FinRatio;             //融资保证金比例
    double OtherCompactBalance;  //其他合约金额
    double OtherCompactInterest; //其他合约利息
    double AssureSecudisBalance; //证券担保折算资产
    double SloSellBalance;       //融券卖出所得总额
    double SumCompactInterest;   //合约总利息
    double FinMaxBalance;        //最高融资金额
    double CorrectBalance;       //资产修正金额
    char CrdtLevel[5];           //信用级别
    double NetAsset;             //净资产
    double RefcostFare;          //转融通成本费用
    double CashAsset;            //现金资产
    double IpoLuckyBalance;      //中签缴款可用资金
    double AssureProdBalance;    //担保理财资产
    double AssureProddisBalance; //担保理财折算资产
    double AssureUnfairAsset;    //担保资产（非公允价）
    double NetUnfairAsset;       //净资产（非公允价）
    double SloUsedBalance;       //融券卖出所得已使用金额
    double SloSurplusBalance;    //融券卖出所得剩余金额
    double TotalMaxQuota;        //最大总额度
};

//查询融资融券负债
struct StpQryCrdtCompactField
{
    char AccountID[STP_ACCOUNTID_LEN];                                //账户编号
    char PositionStr[STP_POSITIONSTR_LEN];                            //定位串
    char InstrumentID[STP_INSTRUMENTID_LEN];                          //证券代码
    int32_t BeginDate;                                                //起始日期
    int32_t EndData;                                                  //到期日期
    char CompactId[STP_ADMINCODE_LEN];                                //合约编号
    char CompactType;                                                 //合约类别
    char CompactSource;                                               //合约来源
    char QueryType;                                                   //查询类别
    char QueryMode;                                                   //查询模式
    char SortDirection;                                               //返回排序方式
    char CompactPostponeStatus;                                       //展期状态
    char EnCompactPostponeStatus[STP_EN_COMPACT_POSTPONE_STATUS_LEN]; //允许展期状态
    char ExchangeId[STP_EXCHANGEID_LEN];                              //市场

    StpQryCrdtCompactField()
    {
        memset(this, 0, sizeof(StpQryCrdtCompactField));
    }
};

struct StpCrdtCompactField
{
    int32_t OpenDate;                         //开户日期
    char CompactId[STP_ADMINCODE_LEN];        //合约编号
    char FundAccount[19];                     //资产账户
    char MoneyType[4];                        //币种类别
    char ExchangeType[STP_EXCHANGE_TYPE_LEN]; //交易类别
    char StockAccount[12];                    //证券账号
    char StockCode[7];                        //证券代码
    double CrdtRatio;                         //保证金比率
    int32_t OrderLocalId;                     //委托编号
    double EntrustPrice;                      //委托价格
    int32_t EntrustAmount;                    //委托数量
    int32_t BusinessAmount;                   //成交数量
    double BusinessBalance;                   //成交金额
    double BusinessFare;                      //成交手续费金额
    char CompactType;                         //合约类别
    char CompactStatus;                       //合约状态
    int32_t BeginCompactAmount;               //期初合约数量
    double BeginCompactBalance;               //期初合约金额
    double BeginCompactFare;                  //期初合约交易手续费
    double RealCompactBalance;                //日间实时合约金额
    int32_t RealCompactAmount;                //日间实时合约数量
    double RealCompactFare;                   //日间实时合约交易手续费
    double RealCompactInterest;               //日间实时利息金额
    double RepaidInterest;                    //已还利息
    int32_t RepaidAmount;                     //已还数量
    double RepaidBalance;                     //已还金额
    double CompactInterest;                   //合约利息金额
    double UsedBailBalance;                   //已用保证金
    double YearRate;                          //年利率
    int32_t RetEndDate;                       //归还截止日
    int32_t DateClear;                        //清算日期
    int32_t CashgroupNo;                      //头寸编号
    char CompactSource;                       //合约来源
    double FinIncome;                         //融资合约盈亏
    double SloIncome;                         //融券合约盈亏
    int32_t PostponeEndDate;                  //续签到期日期
    char PositionStr[101];                    //定位串
    double BusinessPrice;                     //成交价格
    char StockName[33];                       //证券名称
    double TotalDebit;                        //负债总额
    int32_t CompactPostponeTimes;             //展期次数
    char CompactPostponeStatus;               //展期状态
    int32_t FineIntegral;                     //罚息积数
    double FineRate;                          //罚息利率
    double RealCompactPreInterest;            //实时合约预计利息（包含当日利息）
};

struct StpQryFjyAmount
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char EntrustBs;                          //买卖方向
    char EntrustProp[3];                     //委托属性
    StpQryFjyAmount()
    {
        memset(this, 0, sizeof(StpQryFjyAmount));
    }
};

struct StpFjyAmountField
{
    char AccountID[STP_ACCOUNTID_LEN];       //账户编号
    int32_t EnableAmount;                    //可用数量
    int32_t EnableReturnAmount;              //可以还券数量
    char ExchangeID[STP_EXCHANGEID_LEN];     //交易市场
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    StpFjyAmountField()
    {
        memset(this, 0, sizeof(StpFjyAmountField));
    }
};

//现券还券
struct StpReqSecuRtn
{
    char AccountID[STP_ACCOUNTID_LEN];         //账户编号
    char InstrumentID[STP_INSTRUMENTID_LEN];   //证券代码
    int32_t EntrustAmount;                     //委托数量
    char ExchangeID[STP_EXCHANGEID_LEN];       //交易市场
    char CompactId[STP_ADMINCODE_LEN];         //合约编号
    char CompactIdStr[STP_COMPACT_ID_STR_LEN]; //合约编号串
    char WithdrawFlag;                         //允许撤单标志
    StpReqSecuRtn()
    {
        memset(this, 0, sizeof(StpReqSecuRtn));
    }
};

struct StpSecuRtnField
{
    int32_t EntrustNo;    //委托编号
    char OrderId[11];     //客户订单编号
    char OrigOrderId[11]; //原客户订单编号
};

//期权组合委托报单请求
struct StpOptCombOrderInsertReqField
{
    char AccountID[STP_ACCOUNTID_LEN];
    char OperatorID[STP_OPERATORID_LEN];
    ///报单引用
    char OrderRef[STP_ORDERREF_LEN];
    char CombistrategyId[STP_COMBISTRATEGY_ID_LEN]; //组合持仓编号
    char CombistrategyCode[STP_COMBISTRATEGY_CODE_LEN]; //组合策略代码
    char Direction; //委托方向
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char InstrumentID1[STP_INSTRUMENTID_LEN]; //证券代码1
    char InstrumentID2[STP_INSTRUMENTID_LEN]; //证券代码2
    char InstrumentID3[STP_INSTRUMENTID_LEN]; //证券代码3
    char InstrumentID4[STP_INSTRUMENTID_LEN]; //证券代码4
    char CombHedgeFlag[STP_COMBHEDGEFLAG_LEN]; //投机套保标志
    int32_t VolumeTotalOriginal; //原始数量
    char TimeCondition; //有效期类型
    char VolumeCondition; //成交量类型
    char ThirdReff1[STP_THIRDREFF1_LEN]; //预留字段1
    char ThirdReff2[STP_THIRDREFF2_LEN]; //预留字段2
    char OrderIp[STP_ORDERIP_LEN]; //订单IP
    char OrderMac[STP_ORDERMAC_LEN]; //订单MAC
    char OrderHDNum[STP_ORDERHDNUM_LEN]; //订单硬盘序列号
    char OrderMacCode[STP_ORDERMACCODE_LEN]; //订单机器码
    char OrderOS[STP_ORDEROS_LEN]; //订单操作系统
    int32_t MinVolume; //最小成交量
    StpOptCombOrderInsertReqField()
    {
        memset(this, 0, sizeof(StpOptCombOrderInsertReqField));
    }
};

//期权组合保证金持仓查询请求
struct StpQryOptionCombPositionField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char CombistrategyId[STP_COMBISTRATEGY_ID_LEN]; //组合持仓编号
    char PositionStr[STP_POSITIONSTR_LEN];
    char Remark[STP_REMARK_LEN];
    StpQryOptionCombPositionField()
    {
        memset(this, 0, sizeof(StpQryOptionCombPositionField));
    }
};

//期权组合保证金持仓查询应答
struct StpOptionCombPositionField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    char AccountName[STP_ACCOUNTNAME_LEN]; //账户名称
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char CombistrategyId[STP_COMBISTRATEGY_ID_LEN]; //组合持仓编号
    char CombistrategyCode[STP_COMBISTRATEGY_CODE_LEN]; //组合策略代码
    char InstrumentID1[STP_INSTRUMENTID_LEN]; //证券代码1
    char PosiDirection1; //多空标志1
    char InstrumentID2[STP_INSTRUMENTID_LEN]; //证券代码2
    char PosiDirection2; //多空标志2
    char InstrumentID3[STP_INSTRUMENTID_LEN]; //证券代码3
    char PosiDirection3; //多空标志3
    char InstrumentID4[STP_INSTRUMENTID_LEN]; //证券代码4
    char PosiDirection4; //多空标志4
    int32_t CurrentVolume; //当前数量
    int32_t FrozenVolume; //冻结数量
    double CombBalancePre; //组合前占用保证金
    double CombBalanceNow; //组合后占用保证金
    char PositionStr[STP_POSITIONSTR_LEN];
    StpOptionCombPositionField()
    {
        memset(this, 0, sizeof(StpOptionCombPositionField));
    }
};

//期权组合委托查询请求
struct StpQryOptCombOrderField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    char OrderLocalID[STP_ORDERLOCALID_LEN]; //本地报单编号
    char PositionStr[STP_POSITIONSTR_LEN];
    char Remark[STP_REMARK_LEN];
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char Direction; //委托方向
    StpQryOptCombOrderField()
    {
        memset(this, 0, sizeof(StpQryOptCombOrderField));
    }
};

//期权组合委托
struct StpOptCombOrderField
{
    int32_t TradingDay; //交易日
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    SessionIDType SessionID; //会话编号
    int32_t FrontID; //前置编号
    char OrderRef[STP_ORDERREF_LEN]; //报单引用
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char SeatID[STP_SEATID_LEN]; //席位号
    char OrderLocalID[STP_ORDERLOCALID_LEN]; //本地报单编号
    char Direction; //委托方向
    char OperatorID[STP_OPERATORID_LEN]; //操作员代码
    char TradeCode[STP_TRADECODE_LEN]; //交易编码
    char BranchID[STP_BRANCHID_LEN]; //营业部代码
    char InstrumentID1[STP_INSTRUMENTID_LEN]; //证券代码
    char InstrumentID2[STP_INSTRUMENTID_LEN]; //证券代码
    char InstrumentID3[STP_INSTRUMENTID_LEN]; //证券代码
    char InstrumentID4[STP_INSTRUMENTID_LEN]; //证券代码
    char CombistrategyCode[STP_COMBISTRATEGY_CODE_LEN]; //组合策略代码
    char CombistrategyId[STP_COMBISTRATEGY_ID_LEN]; //组合持仓编号
    int32_t VolumeTotalOriginal; //原始数量
    int32_t ORRequestID; //请求编号
    char OrderSysID[STP_ORDERSYSID_LEN]; //报单编号
    char OrderStatus; //报单状态
    char OrderType; //报单类型
    int32_t VolumeTraded; //今成交数量
    double AmountTraded; //今成交金额
    int32_t VolumeRemain; //剩余数量
    int32_t InsertDate; //报单日期
    int32_t InsertTime; //委托时间
    int32_t UpdateTime; //最后修改时间
    int32_t CancelTime; //撤销时间
    char StatusMsg[STP_STATUSMSG_LEN]; //状态信息
    char OwnerType; //发起标志
    char ThirdReff1[STP_THIRDREFF1_LEN]; //预留字段1
    char ThirdReff2[STP_THIRDREFF2_LEN]; //预留字段2
    int32_t VolumeCanceled; //撤成\废单数量
    char Remark[STP_REMARK_LEN]; //备注
    char CancelFlag; //撤单标志
    char OrderIp[STP_ORDERIP_LEN]; //订单IP
    char OrderMac[STP_ORDERMAC_LEN]; //订单MAC
    char OrderHDNum[STP_ORDERHDNUM_LEN]; //订单硬盘序列号
    char OrderMacCode[STP_ORDERMACCODE_LEN]; //订单机器码
    char OrderOS[STP_ORDEROS_LEN]; //订单操作系统
    char SeniorOrderType; //高级订单类型
    char SeniorOrderId[STP_ORDERLOCALID_LEN]; //高级订单编号
    char PositionStr[STP_POSITIONSTR_LEN];
    int32_t BatchNo;	//委托批号
    char CombHedgeFlag; //投机套保标志
    StpOptCombOrderField()
    {
        memset(this, 0, sizeof(StpOptCombOrderField));
    }
};

/* 禁用/解禁账户 */
struct StpLockOpaccount
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    bool is_lock;

    StpLockOpaccount()
    {
        memset(this, 0, sizeof(*this));
    }
};

//期权代码指标查询请求
struct StpQryOptIndexField
{
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char PositionStr[STP_POSITIONSTR_LEN];
    char UnderlyingInstrumentId[STP_UNDERLYINGINSTRUMENTID_LEN];//合约标的代码
    StpQryOptIndexField()
    {
        memset(this, 0, sizeof(StpQryOptIndexField));
    }
};

//期权代码指标
struct StpOptIndexField
{
    char ExchangeID[STP_EXCHANGEID_LEN];            //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];        //证券代码
    char InstrumentName[STP_INSTRUMENTNAME_LEN];    //证券名称
    double InnerValue;                              //内在价值
    double TimeValue;                               //时间价值
    double HisVolatility1M;                         //近一个月历史波动率
    double HisVolatility3M;                         //近三个月历史波动率
    double HisVolatility6M;                         //近六个月历史波动率
    double HisVolatility1Y;                         //近一年历史波动率
    double ImpliedVolatility;                       //隐含波动率
    double Delta;                                   
    double Gamma;
    double Vega;
    double Theta;
    double Rho;
    char PositionStr[STP_POSITIONSTR_LEN];
    char UnderlyingInstrumentId[STP_UNDERLYINGINSTRUMENTID_LEN];//合约标的代码
    int32_t NearDays;                               // 临近到期天数
    StpOptIndexField()
    {
        memset(this, 0, sizeof(StpOptIndexField));
    }
};

//期权代码指标计算请求
struct StpReqCalcOptIndexField
{
    char ExchangeID[STP_EXCHANGEID_LEN]; //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN]; //证券代码
    char PricingModel[STP_OPTPRICE_MODEL_LEN];       //定价模型
    double StockPrice;       //标的价格
    double RiskFreeRate;      //无风险利率
    double OptPrice;           //期权价格
    char ComputePeriod[STP_VOLITILITY_COMPUTE_PERIOD_LEN];      //波动率计算周期

    StpReqCalcOptIndexField()
    {
        memset(this, 0, sizeof(StpReqCalcOptIndexField));
    }
};

//计算期权代码指标
struct StpCalcOptIndexField
{
    char ExchangeID[STP_EXCHANGEID_LEN];            //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];        //证券代码
    double HisVolatility;                           //历史波动率
    double Delta;
    double Gamma;
    double Vega;
    double Theta;
    double Rho;
    double ImpliedVolatility;                       //隐含波动率
    StpCalcOptIndexField()
    {
        memset(this, 0, sizeof(StpCalcOptIndexField));
    }
};

//期权代码指标订阅请求
struct StpSubscribeOptIndexField
{
    char OperatorID[STP_OPERATORID_LEN];       //操作员编号
    char ExchangeID[STP_EXCHANGEID_LEN];       //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];   //证券代码
    StpSubscribeOptIndexField()
    {
        memset(this, 0, sizeof(StpSubscribeOptIndexField));
    }
};

//期权代码指标取消订阅请求
struct StpCancelSubOptIndexField
{
    char OperatorID[STP_OPERATORID_LEN];       //操作员编号
    StpCancelSubOptIndexField()
    {
        memset(this, 0, sizeof(StpCancelSubOptIndexField));
    }
};

//宽邦策略
struct StpBigQuantStrategy {
  int StrategyId;                       //策略ID
  char StrategyPath[201];               //策略路径
  char StrategyName[201];               //策略名称
  char OperatorID[STP_OPERATORID_LEN];  // STP操作员账号
  char AccountID[STP_ACCOUNTID_LEN];    //资金账号
  char QuantId[65];                     //量化策略平台账号即OA账号
  char StrategyStatus;                  //策略状态
  char
      PriceMode;  //价格模式：1-最新价，2-指定价格，3-对手价1，4-对手价2，5-对手价3，6-对手价4，7-对手价5，8-本方价1，默认为指定价格
  int LastTradeDate;           //最后交易日
  int EntrustTime;             //委托时间
  int ExecuteDate;             //最后执行日
  char AlgorithmDes[201];      //策略描述
  char AlgorithmTemplateId[STP_ORDERLOCALID_LEN];  //算法模板ID
  double VolumeTraded;         //成交数量
  double VolumeTotalOriginal;  //总委托数量
  char OrderAlgoId[64];        //算法类型

  StpBigQuantStrategy() { memset(this, 0, sizeof(StpBigQuantStrategy)); }
};

//宽邦策略明细
struct StpBigQuantStrategyDetail {
  int TradeDate;                            //交易日
  int StrategyId;                           //策略ID
  int SeqNo;                                //序号
  char InstrumentID[STP_INSTRUMENTID_LEN];  //证券代码
  char Direction;                           //交易类型
  char OffsetFlag;                          //开平标志
  char HedgeFlag;                          //开平标志
  int EntrustAmount;                        //委托数量
  double EntrustPrice;                      //委托价格
  char ExchangeID[STP_EXCHANGEID_LEN];      //交易市场

  StpBigQuantStrategyDetail() { memset(this, 0, sizeof(StpBigQuantStrategyDetail)); }
};

//宽邦日志明细
struct StpBigQuantLogDetail {
  char OperatorID[STP_OPERATORID_LEN];  // STP操作员账号
  char AccountID[STP_ACCOUNTID_LEN];    //资金账号
  int StrategyId;                       //策略ID
  int Date;                             //日期
  int Time;                             //时间
  char Type;                            //类型
  char Details[402];                    //详细信息
  int SerialNo;                         //定位串

  StpBigQuantLogDetail() { memset(this, 0, sizeof(StpBigQuantLogDetail)); }
};

//宽邦日志明细
struct StpQryBigQuantLogDetailField {
  char OperatorID[STP_OPERATORID_LEN];  // STP操作员账号
  int SerialNo;                         //定位串
  int QueryDirection;                   //查询方向

  StpQryBigQuantLogDetailField() { memset(this, 0, sizeof(StpQryBigQuantLogDetailField)); }
};

//宽邦策略
struct StpReqUpdateBigQuantStrategy {
  int StrategyId;                     //策略ID
  char AccountID[STP_ACCOUNTID_LEN];  //资金账号
  char StrategyStatus;                //策略状态
  char
      PriceMode;  //价格模式：1-最新价，2-指定价格，3-对手价1，4-对手价2，5-对手价3，6-对手价4，7-对手价5，8-本方价1，默认为指定价格
  int EntrustTime;          //委托时间
  char AlgorithmDes[201];   //策略描述
  char AlgorithmTemplateId[STP_ORDERLOCALID_LEN];  //算法模板ID
  char OrderAlgoId[64];        //算法类型
  StpReqUpdateBigQuantStrategy() { memset(this, 0, sizeof(StpReqUpdateBigQuantStrategy)); }
};

//宽邦策略插入应答
struct StpRspInsertBigQuantStrategy {
  int StrategyId;  //策略ID

  StpRspInsertBigQuantStrategy() { memset(this, 0, sizeof(StpRspInsertBigQuantStrategy)); }
};

//宽邦策略插入请求
struct StpReqInsertBigQuantStrategy {
  char StrategyPath[201];  //策略路径
  char StrategyName[201];  //策略名称
  char QuantId[65];        //量化策略平台账号即OA账号
  char AlgorithmDes[201];  //策略描述

  StpReqInsertBigQuantStrategy() { memset(this, 0, sizeof(StpReqInsertBigQuantStrategy)); }
};

//查询BCT可交易标的（白名单）
struct StpQryBctTradableInstrumentsField
{
    char ExchangeID[STP_EXCHANGEID_LEN];                    //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                //证券代码
    StpQryBctTradableInstrumentsField()
    {
        memset(this, 0, sizeof(StpQryBctTradableInstrumentsField));
    }
};

//查询合约名义本金请求
struct StpReqQryContractUsableNotionAmtField
{
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    StpReqQryContractUsableNotionAmtField()
    {
        memset(this, 0, sizeof(StpReqQryContractUsableNotionAmtField));
    }
};

//查询合约名义本金应答
struct StpQryContractUsableNotionAmtField
{
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                     //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    double LongAllocation;                                  //多头可用名义本金
    double ShortAllocation;                                 //空头可用名义本金
    char AccountName[STP_ACCOUNTNAME_LEN];                  //账户名称
    double YdLongAllocation;                                //初始多头可用名义本金
    double YdShortAllocation;                               //初始空头可用名义本金
    char PartyCode[STP_PARTY_CODE_LEN];                     //客户编号
    char PartyName[STP_PARTY_NAME_LEN];                     //客户名称
    double PartentConAllPal;                                //总盈亏
    StpQryContractUsableNotionAmtField()
    {
        memset(this, 0, sizeof(StpQryContractUsableNotionAmtField));
    }
};

//查询合约持仓请求
struct StpReqQryContractPositionField
{
    char AccountID[STP_ACCOUNTID_LEN]; //账户编号
    StpReqQryContractPositionField()
    {
        memset(this, 0, sizeof(StpReqQryContractPositionField));
    }
};

//查询合约持仓
struct StpQryContractPositionField
{
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char PosiDirection;                                     //持仓多空方向
    char ExchangeID[STP_EXCHANGEID_LEN];                    //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                //证券代码    
    int32_t EnableAmount;                                   //可用数量
    int32_t TodayOpenVolume;                                //日间开仓数量
    int32_t TodayDropVolume;                                //日间平仓数量
    double NotionCost;                                      //名义成本
    int32_t FrozenAmount;                                   //冻结数量
    int32_t YdPosition;                                     //昨持仓
    int32_t TotalPosition;                                  //累计持仓数量
    StpQryContractPositionField()
    {
        memset(this, 0, sizeof(StpQryContractPositionField));
    }
};

//合约委托指令请求
struct StpReqInsertContractOrderField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char OrderRef[STP_ORDERREF_LEN];                        //报单引用
    char ExchangeID[STP_EXCHANGEID_LEN];                    //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                //证券代码    
    char Direction;                                         //委托方向
    char OrderPriceType;                                    //报单价格条件
    double LimitPrice;                                      //价格
    char CombOffsetFlag[STP_COMBOFFSETFLAG_LEN];            //开平标志
    char CombHedgeFlag[STP_COMBHEDGEFLAG_LEN];              //投机套保标志
    int32_t VolumeTotalOriginal;                            //原始数量
    int32_t MinVolume;                                      //最小成交量
    char Remark[STP_REMARK_LEN];                            //备注
    char SeniorOrderType;                                   //订单类型
    char OrderCondition[STP_SENIOR_ORDER_LEN];              //订单执行条件
    char OrderContents[STP_SENIOR_ORDER_LEN];               //订单执行内容
    int32_t ExpiryDate;                                     //到期日期
    char OrderAlgoId[STP_ALGOID_LEN];                       //算法ID
    StpReqInsertContractOrderField()
    {
        memset(this, 0, sizeof(StpReqInsertContractOrderField));
    }
};

//合约指令
struct StpContractCommandField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char OrderRef[STP_ORDERREF_LEN];                        //报单引用
    char ExchangeID[STP_EXCHANGEID_LEN];                    //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                //证券代码    
    char Direction;                                         //委托方向
    char OrderPriceType;                                    //报单价格条件
    double LimitPrice;                                      //价格
    char CombOffsetFlag[STP_COMBOFFSETFLAG_LEN];            //开平标志
    char CombHedgeFlag[STP_COMBHEDGEFLAG_LEN];              //投机套保标志
    int32_t VolumeTotalOriginal;                            //原始数量
    int32_t MinVolume;                                      //最小成交量
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号
    int32_t InsertDate;                                     //报单日期
    int32_t InsertTime;                                     //委托时间
    int32_t CancelFlag;                                     //撤单标志
    int32_t CancelTime;                                     //撤销时间
    int32_t VolumeTraded;                                   //今成交数量
    double TradeAmount;                                     //成交金额
    int32_t VolumeRemain;                                   //剩余数量
    int32_t VolumeCanceled;                                 //撤成\废单数量
    int32_t OrderStatus;                                    //报单状态
    char Remark[STP_REMARK_LEN];                            //备注
    char PositionStr[STP_POSITIONSTR_LEN];                  //定位串
    int32_t CheckTime;                                      //审批时间
    char PushNo[STP_DMA_ORDER_PUSHNO_LEN];                  //推送序号
    SessionIDType SessionID;                                //会话编号
    char AuditOperatorId[STP_OPERATORID_LEN];               //审核人员ID
    char AuditOperatorName[STP_OPERATORNAME_LEN];           //审核人员名称
    char SeniorOrderType;                                   //订单类型
    char OrderCondition[STP_SENIOR_ORDER_LEN];              //订单执行条件
    char OrderContents[STP_SENIOR_ORDER_LEN];               //订单执行内容
    int32_t ExpiryDate;                                     //到期日期
    char OrderAlgoId[STP_ALGOID_LEN];                       //算法ID
    char ReqTag[STP_REMARK_LEN];                            //请求标识 供外部文件单用户使用
    StpContractCommandField()
    {
        memset(this, 0, sizeof(StpContractCommandField));
    }
};

//查询合约指令记录请求
struct StpReqQryContractCommandField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    char PositionStr[STP_POSITIONSTR_LEN];                  //定位串
    StpReqQryContractCommandField()
    {
        memset(this, 0, sizeof(StpReqQryContractCommandField));
    }
};

//撤销委托指令请求
struct StpReqCancelContractOrderField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号
    StpReqCancelContractOrderField()
    {
        memset(this, 0, sizeof(StpReqCancelContractOrderField));
    }
};

//审核指令请求
struct StpReqAuditContractOrderField
{
    char OperatorID[STP_OPERATORID_LEN];                    //审核人员操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号
    int32_t RejectFlag;                                     //拒绝标志
    char RejectReason[STP_REJECT_REASON_LEN];               //拒绝理由
    char OperatorName[STP_OPERATORNAME_LEN];                //审核人员名称
    StpReqAuditContractOrderField()
    {
        memset(this, 0, sizeof(StpReqAuditContractOrderField));
    }
};

//查询操作员菜单权限请求
struct StpReqQryMenuAuthField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    StpReqQryMenuAuthField()
    {
        memset(this, 0, sizeof(StpReqQryMenuAuthField));
    }
};

//查询操作员菜单权限
struct StpQryMenuAuthField
{
    char AuthInfo[STP_AUTH_INFO_LEN];                       //菜单权限
    StpQryMenuAuthField()
    {
        memset(this, 0, sizeof(StpQryMenuAuthField));
    }
}; 

struct StpRspInsertContractOrderBatchField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ExchangeID[STP_EXCHANGEID_LEN];                    //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                //证券代码   
    char OrderRef[STP_ORDERREF_LEN];                        //报单引用 
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号
    int ErrorNo;                                            //错误号
    char ErrorInfo[STP_BANK_ERROR_INFO_LEN];                //错误信息

    StpRspInsertContractOrderBatchField()
    {
        memset(this, 0, sizeof(StpRspInsertContractOrderBatchField));
    }
};

struct StpRspCancelContractOrderBatchField
{
    char OperatorID[STP_OPERATORID_LEN];                    //操作员代码
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    char ContractCode[STP_CONTRACT_CODE_LEN];               //合约编码
    char ContractOrderID[STP_CONTRACT_ORDER_ID_LEN];        //合约委托编号
    int ErrorNo;                                            //错误号
    char ErrorInfo[STP_BANK_ERROR_INFO_LEN];                //错误信息

    StpRspCancelContractOrderBatchField()
    {
        memset(this, 0, sizeof(StpRspCancelContractOrderBatchField));
    }
};

struct StpReqQryDmaRiskDataField
{
    char AccountIDStr[STP_ACCOUNT_ID_STR_LEN];                      //账户编号串
    int64_t ContractID;                                       //合约ID

    StpReqQryDmaRiskDataField()
    {
        memset(this, 0, sizeof(StpReqQryDmaRiskDataField));
    }
};

struct StpQryDmaRiskDataField
{
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号
    int64_t ContractID;                                       //合约ID
    double LongShortRatio;                                  //多空名义本金比例
    int32_t StkCount;                                           //股票数量
    char OverConcentrationStkStr[STP_OVER_CONCENTRATION_STK_STR_LEN]; //集中度超限股票串
    char PositionRiskStk[STP_OVER_CONCENTRATION_STK_STR_LEN]; //持仓风险标的

    StpQryDmaRiskDataField()
    {
        memset(this, 0, sizeof(StpQryDmaRiskDataField));
    }
};

struct StpReqCalcLongShortCorrelationField
{
    char AccountID[STP_ACCOUNTID_LEN];                      //账户编号串
    int64_t ContractID;                                       //合约ID

    StpReqCalcLongShortCorrelationField()
    {
        memset(this, 0, sizeof(StpReqCalcLongShortCorrelationField));
    }
};

struct StpSyncBctDataField
{
    int32_t SyncDataType;                                       //同步数据类型

    StpSyncBctDataField()
    {
        memset(this, 0, sizeof(StpSyncBctDataField));
    }
};

struct StpDmaSystemMaintenanceOpField
{
    int32_t OpType;                                       //操作类型

    StpDmaSystemMaintenanceOpField()
    {
        memset(this, 0, sizeof(StpDmaSystemMaintenanceOpField));
    }
};

struct StpQryDmaSystemStatusField
{
    int32_t TradingDay;                                     //交易日
    int32_t InitDay;                                        //初始化日期
    int32_t Status;                                         //当前状态
    int32_t CurrOp;                                         //正在执行动作
    int32_t LastOpTime;                                     //最近执行时间
    int32_t LastOpResult;                                   //执行结果
    char LastOpRemark[STP_REMARK_LEN];                      //失败原因

    StpQryDmaSystemStatusField()
    {
        memset(this, 0, sizeof(StpQryDmaSystemStatusField));
    }
};

struct StpReqQryDmaRiskParamField
{
    char AccountIDStr[STP_ACCOUNT_ID_STR_LEN];                  //账户编号串
    int64_t ContractID;                                         //合约ID

    StpReqQryDmaRiskParamField()
    {
        memset(this, 0, sizeof(StpReqQryDmaRiskParamField));
    }
};

struct StpQryDmaRiskParamField
{
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    int64_t ContractID;                                         //合约ID
    char TradeStatus[STP_TRADE_STATUS_LEN];                     //交易状态
    char AuditWay[STP_AUDIT_WAY_LEN];                           //审核方式
    char FareModelStr[STP_FARE_MODEL_STR_LEN];                  //费用模板串

    StpQryDmaRiskParamField()
    {
        memset(this, 0, sizeof(StpQryDmaRiskParamField));
    }
};

struct StpReqSetDmaRiskParamField
{
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    int64_t ContractID;                                         //合约ID
    char TradeStatus[STP_TRADE_STATUS_LEN];                     //交易状态
    char AuditWay[STP_AUDIT_WAY_LEN];                           //审核方式
    char FareModelStr[STP_FARE_MODEL_STR_LEN];                  //费用模板串
    char OperateType[STP_OPERATE_TYPE_LEN];                     //操作类型

    StpReqSetDmaRiskParamField()
    {
        memset(this, 0, sizeof(StpReqSetDmaRiskParamField));
    }
};

struct StpReqQryDmaFareModelField
{
    char ModelID[STP_MODEL_ID_LEN];                  //模板编号

    StpReqQryDmaFareModelField()
    {
        memset(this, 0, sizeof(StpReqQryDmaFareModelField));
    }
};

struct StpQryDmaFareModelField
{
    char ModelID[STP_MODEL_ID_LEN];                     //模板编号
    char ModelName[STP_MODEL_NAME_LEN];                 //模板名称
    char ExchangeID[STP_EXCHANGEID_LEN];                //交易所代码
    char ProductClass[STP_PRODUCTCLASS_LEN];            //证券类别
    char SubProductClass[STP_SUB_PRODUCTCLASS_LEN];     //证券二级类别
    char FuturesKind[STP_FUTURES_KIND_LEN];             //期货品种
    char InstrumentID[STP_INSTRUMENTID_LEN];            //证券代码
    char OcDirection[STP_OC_DIRECTION_LEN];             //开平方向
    double FareByBalance;                               //按金额收费
    double FareByVolume;                                //按数量收费
    char Remark[STP_REMARK_LEN];                        //备注

    StpQryDmaFareModelField()
    {
        memset(this, 0, sizeof(StpQryDmaFareModelField));
    }
};

struct StpReqSetDmaFareModelField
{
    char ModelID[STP_MODEL_ID_LEN];                     //模板编号
    char ModelName[STP_MODEL_NAME_LEN];                 //模板名称
    char ExchangeID[STP_EXCHANGEID_LEN];                //交易所代码
    char ProductClass[STP_PRODUCTCLASS_LEN];            //证券类别
    char SubProductClass[STP_SUB_PRODUCTCLASS_LEN];     //证券二级类别
    char FuturesKind[STP_FUTURES_KIND_LEN];             //期货品种
    char InstrumentID[STP_INSTRUMENTID_LEN];            //证券代码
    char OcDirection[STP_OC_DIRECTION_LEN];             //开平方向
    double FareByBalance;                               //按金额收费
    double FareByVolume;                                //按数量收费
    char Remark[STP_REMARK_LEN];                        //备注
    char OperateType[STP_OPERATE_TYPE_LEN];             //操作类型：'1'新增 '2'修改 '3'删除

    StpReqSetDmaFareModelField()
    {
        memset(this, 0, sizeof(StpReqSetDmaFareModelField));
    }
};

struct StpReqQryETFOrderDetailField {
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    char OrderLocalID[STP_ORDERLOCALID_LEN];                    //本地报单编号
};

struct StpQryETFOrderDetailField {
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    int32_t TradingDay;                                         //交易日
    int32_t EntrustTime;                                        //委托时间
    int32_t BatchNo;	                                        //委托批号
    int32_t EntrustNo;                                          //委托编号
    int32_t DetailEntrustNo;                                    //明细委托编号
    char ExchangeID[STP_EXCHANGEID_LEN];                        //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                    //证券代码
    char Direction;                                             //委托方向
    int32_t VolumeTotalOriginal;                                //原始数量
    char OrderStatus;                                           //报单状态
    double LimitPrice;                                          //价格
};

struct StpReqQryETFTradeDetailField {
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    char OrderLocalID[STP_ORDERLOCALID_LEN];                    //本地报单编号
};

struct StpQryETFTradeDetailField {
    char AccountID[STP_ACCOUNTID_LEN];                          //账户编号串
    int32_t TradingDay;                                         //交易日
    int TradeTime;                                              //成交时间
    char TradeCode[STP_TRADECODE_LEN];                          //交易编码
    int32_t EntrustNo;                                          //委托编号
    char Direction;                                             //委托方向
    char ExchangeID[STP_EXCHANGEID_LEN];                        //交易所代码
    char InstrumentID[STP_INSTRUMENTID_LEN];                    //证券代码
    double TradeAmount;                                         //成交金额
    double Price;                                               //价格
    int Volume;                                                 //成交量
    double Commission;                                          //手续费
};
#pragma pack(pop)

#endif
