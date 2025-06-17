#ifndef _T_SH_MARKET_
#define _T_SH_MARKET_

#pragma warning (disable : 4996 4200)
#include "tdef.h"


#pragma pack(push,1)

// 1.1 股票行情
typedef struct t_SH_StockMarketDataL2 {
  T_I32 nActionDay;                 //自然日
  T_I32 nTime;                      //时间(HHMMSSmmm)
  T_I32 nStatus;                    //状态
  T_U32 uPreClose;                  //前收盘价
  T_U32 uOpen;                      //开盘价
  T_U32 uHigh;                      //最高价
  T_U32 uLow;                       //最低价
  T_U32 uMatch;                     //最新价
  T_U32 uAskPrice[10];              //申卖价
  T_U32 uAskVol[10];                //申卖量
  T_U32 uBidPrice[10];              //申买价
  T_U32 uBidVol[10];                //申买量
  T_U32 uNumTrades;                 //成交笔数
  T_I64 iVolume;                    //成交总量
  T_I64 iTurnover;                  //成交总金额
  T_I64 iTotalBidVol;               //委托买入总量
  T_I64 iTotalAskVol;               //委托卖出总量
  T_U32 uWeightedAvgBidPrice;       //加权平均委买价格
  T_U32 uWeightedAvgAskPrice;       //加权平均委卖价格
  T_I32 nIOPV;                      //IOPV净值估值
  T_I32 nYieldToMaturity;           //到期收益率
  T_U32 uHighLimited;               //涨停价
  T_U32 uLowLimited;                //跌停价
  char sPrefix[4];                  //证券信息前缀
  T_I32 nSyl1;                      //市盈率1 2 位小数 股票：价格/上年每股利润 债券：每百元应计利息
  T_I32 nSyl2;                      //市盈率2 2 位小数 股票：价格/本年每股利润 债券：到期收益率 基金：每百份的IOPV 或净值 权证：溢价率
  T_I32 nSD2;                       //升跌2（对比上一笔）
  char sTradingPhraseCode[8];       //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘P’表示产品停牌。
  T_I32 nPreIOPV;                   //基金 T-1 日收盘时刻 IOPV 仅标的为基金时有效
} Stock_MarketData,T_SH_StockMarketDataL2,*PSH_StockMarketDataL2;

//1.2 dbf行情，上交所与深交所均用此结构
typedef struct t_SH_StockMarketDataL1 {
  T_I32 nActionDay;                 //自然日
  T_I32 nTime;                      //时间(HHMMSSmmm)
  T_I32 nStatus;                    //状态
  T_U32 uPreClose;                  //前收盘价
  T_U32 uOpen;                      //开盘价
  T_U32 uHigh;                      //最高价
  T_U32 uLow;                       //最低价
  T_U32 uMatch;                     //最新价
  T_U32 uAskPrice[5];               //申卖价
  T_U32 uAskVol[5];                 //申卖量
  T_U32 uBidPrice[5];               //申买价
  T_U32 uBidVol[5];                 //申买量
  T_U32 uNumTrades;                 //成交笔数
  T_I64 iVolume;                    //成交总量
  T_I64 iTurnover;                  //成交总金额
  T_U32 uHighLimited;               //涨停价
  T_U32 uLowLimited;                //跌停价
  char sTradingPhaseCode[8];        //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘P’表示产品停牌。
  T_I32 nPreIOPV;                   //基金T-1日收盘时刻IOPV  MDStreamID == MD004 表示基金时有效
  T_I32 nIOPV;                      //基金IOPV  MDStreamID == MD004 表示基金时有效
} Stock_MarketData_L1,T_SH_StockMarketDataL1,*PSH_StockMarketDataL1;


//1.3 逐笔成交(Transaction)
typedef struct t_SH_StockStepTrade {
  T_I32 nActionDay;                 //自然日
  T_I32 nTradeIndex;                //成交序号
  T_I32 nTradeChannel;              //成交通道
  T_I32 nTradeTime;                 //成交时间 HHMMSSmmm
  T_I32 nTradePrice;                //成交价格 扩大10000倍
  T_I64 iTradeQty;                  //成交数量 股票：股 权证：份 债券：张
  T_I64 iTradeMoney;                //成交金额(元)
  T_I64 iTradeBuyNo;                //买方订单号
  T_I64 iTradeSellNo;               //卖方订单号
  char cTradeBSflag;                //内外盘标识 B -外盘，主动买  B-内盘,主动卖 N 未知
  char sRes[3];                     //保留字段1
} Stock_Transaction_SH,T_SH_StockStepTrade,*PSH_StockStepTrade; //上交所逐笔成交，对应交易所UA3201



//1.4 订单队列(Queue)
#ifndef _ORDER_QUEUE_
#define _ORDER_QUEUE_
typedef struct t_OrderQueueHead {
  T_I32 nActionDay;                 //自然日
  T_I32 nItem;                      //数据个数
} Stock_OrderQueue_Head,T_OrderQueueHead,*POrderQueueHead;
typedef struct t_OrderQueueItem {
  T_I32 nTime;                      //订单时间(HHMMSSmmm)
  T_I32 nSide;                      //买卖方向('B':Bid 'S':Ask)
  T_I32 nPrice;                     //成交价格
  T_I32 nOrders;                    //订单数量
  T_I32 nABItems;                   //明细个数
  T_I32 nABVolume[200];             //订单明细
} Stock_OrderQueue,T_OrderQueueItem,*POrderQueueItem;
#endif //_ORDER_QUEUE_

typedef struct t_SH_StockOrderQueue {
  T_OrderQueueHead tHead;
  T_OrderQueueItem tItem[0];
} T_SH_StockOrderQueue,*PSH_StockOrderQueue;

//1.5 指数
typedef struct t_SH_StockIndex {
  T_I32 nActionDay;                 //自然日
  T_I32 nTime;                      //时间(HHMMSSmmm)
  T_I32 nOpenIndex;                 //今开盘指数
  T_I32 nHighIndex;                 //最高指数
  T_I32 nLowIndex;                  //最低指数
  T_I32 nLastIndex;                 //最新指数
  T_I64 iTotalVolume;               //参与计算相应指数的交易数量
  T_I64 iTurnover;                  //参与计算相应指数的成交金额
  T_I32 nPreCloseIndex;             //前盘指数
} Stock_IndexData,T_SH_StockIndex,*PSH_StockIndex;

#pragma pack(pop)
#endif //_T_SH_MARKET_