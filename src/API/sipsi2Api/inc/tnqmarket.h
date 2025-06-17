
#ifndef _T_NQ_MARKET_
#define _T_NQ_MARKET_

#pragma warning (disable : 4996 4200)
#include "tdef.h"

#pragma pack(push,1)

//1.1 指数
typedef struct t_NQ_StockIndex {
  T_I32 nActionDay;           //自然日
  T_I32 nTime;                //时间(HHMMSSmmm)
  T_I32 nOpenIndex;           //今开盘指数
  T_I32 nHighIndex;           //最高指数
  T_I32 nLowIndex;            //最低指数
  T_I32 nLastIndex;           //最新指数
  T_I64 iTotalVolume;         //参与计算相应指数的交易数量
  T_I64 iTurnover;            //参与计算相应指数的成交金额
  T_I32 nPreCloseIndex;       //前盘指数
} T_NQ_StockIndex, *PNQH_StockIndex;

// 1.2 股票行情
typedef struct t_NQ_StockMarketData {
  T_I32 nActionDay;           //自然日
  T_I32 nTime;                //时间(HHMMSSmmm)
  T_U32 uPreClose;            //前收盘价
  T_U32 uOpen;                //开盘价
  T_U32 uHigh;                //最高价
  T_U32 uLow;                 //最低价
  T_U32 uMatch;               //最新价
  T_U32 uNumTrades;           //成交笔数
  T_I64 iVolume;              //成交总量
  T_I64 iTurnover;            //成交总金额
  T_U32 uHighLimited;         //涨停价
  T_U32 uLowLimited;          //跌停价
  T_I32 nSyl1;                //市盈率1 2 位小数 股票：价格/上年每股利润 债券：每百元应计利息
  T_I32 nSyl2;                //市盈率2 2 位小数 股票：价格/本年每股利润 债券：到期收益率 基金：每百份的IOPV 或净值 权证：溢价率
  T_I32 nSD2;                 //升跌2（对比上一笔）
  T_I64 iPosition;            //合约持仓量
  T_U32 uAskPrice[5];         //申卖价
  T_U32 uAskVol[5];           //申卖量
  T_U32 uBidPrice[5];         //申买价
  T_U32 uBidVol[5];           //申买量
} T_NQ_StockMarketData, *PNQ_StockMarketData;

#pragma pack(pop)

#endif //_T_NQ_MARKET_