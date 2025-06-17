#ifndef _T_SHHK_MARKET_
#define _T_SHHK_MARKET_

#include "tdef.h"

#pragma pack(push,1)

//1.1 沪港通行情
typedef struct t_SHHK_StockMarketData {
  T_I32 nActionDay;       //自然日
  T_I32 nTime;            //时间(HHMMSSmmm)
  T_I32 iPrelosePrice;    //前一天收盘价
  T_I32 iNorminalPx;      //按盘价
  T_I32 iHighPx;          //最高价
  T_I32 iLowPx;           //最低价
  T_I32 iLastPx;          //最新价
  T_U64 ulSharesTraded;   //交易量(股)
  T_I64 lTurnover;        //交易额,约定4位小数
  char cTradingStatus;    //‘0’表示正常，‘1’表示暂停交易
  char cFiller[3];
  T_I32 iPrice_b[5];      //申买量
  T_U64 ulQuantity_b[5];  //申买价,约定4位小数
  T_I32 iPrice_s[5];      //申卖量
  T_U64 ulQuantity_s[5];  //申卖价,约定4位小数
} T_SHHK_StockMarketData, *PSHHK_StockMarketData;

#pragma pack(pop)
#endif //_T_SHHK_MARKET_