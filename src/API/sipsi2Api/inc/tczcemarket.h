#ifndef _T_CZCE_MARKET_
#define _T_CZCE_MARKET_

#include "tdef.h"

#pragma pack(push,1)
//1.1 郑商所期货行情
typedef struct t_CZCE_FutursMarketData {
  T_I32 nActionDay;                    //业务发生日(自然日)
  T_I32 nTradingDay;                   //交易日
  T_I32 nTime;                         //时间(HHMMSSmmm)
  T_I32 nStatus;                       //状态
  T_I64 iPreOpenInterest;              //昨持仓
  T_U32 uPreClose;                     //昨收盘价
  T_U32 uPreSettlePrice;               //昨结算
  T_U32 uOpen;                         //开盘价
  T_U32 uHigh;                         //最高价
  T_U32 uLow;                          //最低价
  T_U32 uMatch;                        //最新价
  T_I64 iVolume;                       //成交总量
  T_I64 iTurnover;                     //成交总金额
  T_I64 iOpenInterest;                 //持仓总量
  T_U32 uClose;                        //今收盘
  T_U32 uSettlePrice;                  //今结算
  T_U32 uHighLimited;                  //涨停价
  T_U32 uLowLimited;                   //跌停价
  T_I32 nPreDelta;                     //昨虚实度
  T_I32 nCurrDelta;                    //今虚实度
  T_U32 uAskPrice[5];                  //申卖价
  T_U32 uAskVol[5];                    //申卖量
  T_U32 uBidPrice[5];                  //申买价
  T_U32 uBidVol[5];                    //申买量
} T_CZCE_FutursMarketData,*PCZCE_FutursMarketData;
//1.2 郑商所期货基础信息
/////产品类型-------------------------------------------------------
#define THOST_FTDC_PC_Futures '1'      //期货
#define THOST_FTDC_PC_Options '2'      //期货期权
#define THOST_FTDC_PC_Combination '3'  //组合
#define THOST_FTDC_PC_Spot '4'         //即期
#define THOST_FTDC_PC_EFP '5'          //期转现
#define THOST_FTDC_PC_SpotOption '6'   //现货期权
//合约生命周期----------------------------------------
#define THOST_FTDC_IP_NotStart '0'     //未上市
#define THOST_FTDC_IP_Started '1'      //上市
#define THOST_FTDC_IP_Pause '2'        //停牌
#define THOST_FTDC_IP_Expired '3'      //到期
//持仓类型-------------------------------------------------
#define THOST_FTDC_PT_Net '1'          //净持仓
#define THOST_FTDC_PT_Gross '2'        //综合持仓

////////////////////////////////////////////////////////////////////////
//////持仓日期类型
////////////////////////////////////////////////////////////////////////
#define THOST_FTDC_PDT_UseHistory '1'   //使用历史持仓
#define THOST_FTDC_PDT_NoUseHistory '2' //不使用历史持仓

////////////////////////////////////////////////////////////////////////
///大额单边保证金算法类型
////////////////////////////////////////////////////////////////////////
#define THOST_FTDC_MMSA_NO '0'         //不使用大额单边保证金算法
#define THOST_FTDC_MMSA_YES '1'        //使用大额单边保证金算法

////////////////////////////////////////////////////////////////////////
///期权类型类型
////////////////////////////////////////////////////////////////////////
#define THOST_FTDC_CP_CallOptions '1'  //看涨
#define THOST_FTDC_CP_PutOptions '2'   //看跌

////////////////////////////////////////////////////////////////////////
///组合类型类型
////////////////////////////////////////////////////////////////////////
#define THOST_FTDC_COMBT_Future '0'    //期货组合
#define THOST_FTDC_COMBT_BUL '1'       //垂直价差BUL
#define THOST_FTDC_COMBT_BER '2'       //垂直价差BER
#define THOST_FTDC_COMBT_STD '3'       //跨式组合
#define THOST_FTDC_COMBT_STG '4'       //宽跨式组合
#define THOST_FTDC_COMBT_PRT '5'       //备兑组合
#define THOST_FTDC_COMBT_CLD '6'       //时间价差组合

typedef struct t_CZCE_BaseInfo {
  T_I32 nActionDay;                   //自然日
  char sInstrumentID[31];             //合约代码
  char sExchangeID[9];                //交易所代码
  char sInstrumentName[24];           //合约名称 
  char sExchangeInstID[31];           //合约在交易所的代码
  char sProductID[31];                //产品代码 
  char cProductClass;                 //产品类型
  T_I32 nDeliveryYear;                //交割年份
  T_I32 nDeliveryMonth;               //交割月
  T_I32 nMaxMarketOrderVolume;        //市价单最大下单量
  T_I32 nMinMarketOrderVolume;        //市价单最小下单量
  T_I32 nMaxLimitOrderVolume;         //限价单最大下单量
  T_I32 nMinLimitOrderVolume;         //限价单最小下单量
  T_I32 nVolumeMultiple;              //合约数量乘数
  T_I64 i64PriceTick;                 //最小变动价位,扩大10000倍
  T_I32 nCreateDate;                  //创建日
  T_I32 nOpenDate;                    //上市日
  T_I32 nExpireDate;                  //到期日
  T_I32 nStartDelivDate;              //开始交割日
  T_I32 nEndDelivDate;                //结束交割日
  char cInstLifePhase;                //合约生命周期状态
  T_I32 nIsTrading;                   //当前是否交易
  char cPositionType;                 //持仓类型
  char cPositionDateType;             //持仓日期类型
  T_I64 i64LongMarginRatio;           //多头保证金率,扩大至10000倍
  T_I64 i64ShortMarginRatio;          //空头保证金率,扩大至10000倍
  char cMaxMarginSideAlgorithm;       //是否使用大额单边保证金算法
  char sUnderlyingInstrID[31];        //基础商品代码
  T_I64 i64StrikePrice;               //执行价,扩大至10000倍
  char cOptionsType;                  //期权类型
  T_I64 i64UnderlyingMultiple;        //合约基础商品乘数,扩大至10000倍
  char cCombinationType;              //组合类型
} T_CZCE_BaseInfo,*PCZCE_BaseInfo;

///发给做市商的询价请求
typedef struct t_CZCE_ForQuote {
  T_I32 nTradingDay;                   //交易日
  char sInstrumentID[31];              //合约代码
  char sForQuoteSysID[21];             //询价编号
  T_I32 nForQuoteTime;                 //询价时间
  int nActionDay;                      //业务日期 
  char sExchangeID[9];                 //交易所代码
} T_CZCE_ForQuote;

#pragma pack(pop)
#endif //_T_CZCE_MARKET_