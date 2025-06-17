#ifndef _T_HKMARKET_H_ 
#define _T_HKMARKET_H_

#include "tdef.h"

#pragma pack(push,1)

// 3.7.2 Security Definition (11) 证券定义-----------------
typedef struct t_securitydefine {
  T_I32 nActionDay;                   //自然日
  T_U32	uSecurityCode;                //证券代码,1-99999的5位十进制
  char sMarketCode[4];                //市场代码,MAIN,GEM,NASD,ETS,注意末尾可能没有0字符
  char sISINCode[12];                 //ISIN代码,证券国际代码.
  char sInstrumentType[4];            // BOND(债券),BWRT(篮子权证),EQTY(股票),TRST(信托),WRNT(权证)
  char sFiller1[2];                   //市价调节机制与收盘集合竞争价规则增加后生效果
  char sSpreadTableCode[2];           // '01' PArtA , '02' PartB
  char sSecurityShortName[40];        // 证券短名
  char sCurrencyCode[3];              // 货币代码,HKD,USD,EUR,JPY,GBP,CAD,SGD,CNY
  T_U8 usGCCSName[60];                // 香港中文繁体UnicodeUTF-16LE编码
  T_U8 usGBName[60];                  // GB简体UnicodeUTF-16LE编码
  T_U32	uLotSize;                     // 买卖单位，Board lot size for the security
  char sFiller12[4];                  //市价调节机制与收盘集合竞争价规则增加后生效果
  T_I32	iPrelosePrice;                // 前收市价
  char cVCMFlag;                      // Y VCM applicable N VCM not applicable市价调节机制与收盘集合竞争价规则增加后生效果
  char cShortSellFlag;                // Y Short-sell allowed,N Short-sell not allowed
  char cCASFlag;                      // Y CAS applicable N CAS not applicable 市价调节机制与收盘集合竞争价规则增加后生效果
  char cCCASSFlag;                    // Y CCASS security,N Non CCASS security
  char cDummySecurityFlag;            // Y Dummy security,N Normal security
  char cTestSecurityFlag;             // Y Test security,N Normal security
  char cStampDutyFlag;                // Y Stamp duty required,N Stamp duty not required
  char cFiller3;                      // res3
  T_U32	uListingDate;                 // 上市日期 YYYYMMDD,19000101 表示未知
  T_U32	uDelistingDate;               // 退市日期 YYYYMMDD,0 表示未知
  char sFreeText[38];                 // 固定长度的FreeText,如果没有，填写空格
  char sFiller4[82];                  // 市价调节机制与收盘集合竞争价规则增加后生效果
  char cEFNFlag;                      // Y EFN,N Non-EFN
  T_U32	uAccruedInterest;             // Accrued Interest,约定3位小数
  T_U32	uCouponRate;                  // Coupon Rate,约定3位小数
  char sFiller5[42];                  // 市价调节机制与收盘集合竞争价规则增加后生效果
  T_U32	uConversionRatio;             // Conversion Ratio,约定3位小数
  T_I32	iStrikePrice;                 // Strike Price行权价，约定3位小数
  char sFiller6[4];                   // 市价调节机制与收盘集合竞争价规则增加后生效果
  T_U32	uMaturityDate;                // 到期日，YYYYMMDD
  char cCallPutFlag;                  // Derivative Warrants/Basket: C Call,P Put ELI & CBBC: C Bull,P Bear / Rang
  char cStyle;                        // Style of the basket warrant:A American style,E European style,<blank> Other
  char sFiller7[50];                  // 市价调节机制与收盘集合竞争价规则增加后生效果
  T_U16	usNoUnderlyingSecurities;     // 0 to 20 for Basket Warrants;0 to 1 for Warrants and Structured Product
  struct t_uls {
    T_U32 uUnderlyingSecurityCode;    // 5-digit code identifying the underlying security.
    T_U32 uUnderlyingSecurityWeight;  //The weight of the underlying security code.
  } uls[];
} OMDMSG_SECURITYDEFINE; // sizeof() = 464 + 8*nu   (nu = usNoUnderlyingSecurities)


// 3.9.9 Order Imbalance(56)
typedef struct t_orderimbalance {
  T_I32 nActionDay;                 //自然日
  T_U32 uSecurityCode;              // 5 digit security codes with possible		values 1 – 99999
  char cOrderImbalanceDirection;    // N Buy = Sell
  //B Buy Surplus
  //	S Sell Surplus
  //	<space> Not applicable, i.e. when
  //	IEP is not availabl
  char cFiller1;
  T_U64 u64OrderImbalanceQuantity;
  /*The absolute difference
  between the matchable buy
  quantity and the sell quantity at
  IEP
  Value should be ignored if Order
  Imbalance Direction is <space>*/
  char cFiller2;
} OMDMSG_ORDERIMBALANCE; //sizeof() == 20

//3.10.7 Reference Price (43)
typedef struct t_referenceprice {
  T_I32 nActionDay;             //自然日
  T_U32 uSecurityCode;          // 5 digit security codes with possible		values 1 – 99999
  T_I32 nReferencePrice;        // Reference price of the security for order input 
  T_I32 nLowerPrice;       
  T_I32 nUpperPrice;
} OMDMSG_REFERENCEPRICE; //sizeof() == 20

//3.10.8 VCM Trigger(23)
typedef struct t_vcmtrigger {
  T_I32 nActionDay;             //自然日
  T_U32 uSecurityCode;          // 5 digit security codes with possible		values 1 – 99999
  T_U64 u64CoolingOffStartTime;
  T_U64 u64CoolingOffEndTime;
  T_I32 nVCMReferencePrice;
  T_I32 nVCMLowerPrice;
  T_I32 nVCMUpperPrice;
} OMDMSG_VCMTRIGGER; //sizeof() == 36

// 3.8.2 Security Status (21) 证券状态---------------------
typedef struct t_securitystatus	{
  T_I32 nActionDay;             //自然日
  T_U32	uSecurityCode;          //证券代码,1-99999的5位十进制
  T_U8 ucSecurityTradingStatus; //状态: 2 Trading Halt;3 Resume
  char cFiller[3];		
} OMDMSG_SECURITYSTATUS; // sizeof() = 12

// 3.7.4 Currency Rate (14) 汇率---------------------------
typedef struct t_currencyrate	{
  T_I32 nActionDay;             //自然日
  char sCurrencyCode[3];        //货币代码,HKD,USD,EUR,JPY,GBP,CAD,SGD,CNY
  char cFiller;			
  T_U16	usCurrencyFactor;       // 非0表示价格乘以10 n次方
  char sFiller[2];
  T_U32	uCurrencyRate;          // HKD表示的外币单位，约定4位小数
} OMDMSG_CURRENCERATE; // sizeof() = 16

// 3.10.4 Closing Price (62) 收市价------------------------
typedef struct t_closeprice	{
  T_I32 nActionDay;             //自然日
  T_U32	uSecurityCode;          //证券代码,1-99999的5位十进制
  T_I32	iPrice;                 //收市价格，约定3位小数
  T_U32	uNumberOfTrades;        //交易数,Total Number of Trades performed on the given instrument
} OMDMSG_CLOSEPRICE;	//sizeof() = 16

// 3.13.2 Index Data (71) 指数数据-------------------------
typedef struct t_indexdata {
  T_I32 nActionDay;             //自然日
  char sIndexCode[11];          //Upstream source’s index code
  char cIndexStatus;            //Index status.
  //C Closing value
  //I Indicative
  //O Opening index
  //P Last close value (prev. ses.)
  //R Preliminary close
  //S Stop loss index
  //T Real-time index value
  T_I64	lIndexTime;             //自1970-1-1 0：0：0 GMT时标，单位纳秒	
  T_I64	lIndexValue;            //4位小数，Current value of the index
  T_I64	lNetChgPrevDay;         //4位小数，Net change in value from previous day’s closing value versus last index value 
  T_I64	lHighValue;             //4位小数
  T_I64	lLowValue;              //4位小数
  T_I64	lEASValue;              //2位小数,Estimated Average Settlement Value
  T_I64	lIndexTurnover;         //4位小数
  T_I64	lOpeningValue;          //4位小数
  T_I64	lClosingValue;          //4位小数
  T_I64	lPreviousSesClose;      //4位小数,Previous session closing value
  T_I64	lIndexVolume;           //4位小数,Index volume of underlying constituents.,Only applicable for CSI.
  T_I32	iNetChgPrevDayPct;      //4位小数,Net change in percentage from previous day’s closing value versus last value
  char cException;              //Exception indicator
  //# Index with HSIL defined exceptional rule applied
  //' ' Normal index (empty string)
  char sFiller[3];
} OMDMSG_INDEXDATA;	//sizeof() = 112

// MsgType = 90 , 根据OMD 53消息还原的10档行情
#define OMD_LEVEL2	10
typedef struct t_omdmsgex_level2 {
  T_I32 nActionDay;             //自然日
  T_U32 uSecurityCode;          //证券代码,1-99999的5位十进制

  T_I64 ltime;                  //时间OMD中定义的时间,自1970-1-1 0：0：0 GMT时标，单位纳秒,0表示数据无效
  T_I32 iPreClosePrice;         //前一天收盘价，来自11
  T_I32 iPrice;                 //按盘价格，约定4位小数 ,来自40
  T_I32 iOpenPrice;             //开盘价

  T_U64 ulSharesTraded;         //交易量(股) ,随后的6个来自60
  T_I64 lTurnover;              //交易额,约定4位小数
  T_I32 iHighPrice;             //最高价，约定4位小数
  T_I32 iLowPrice;              //最低价，约定4位小数
  T_I32 iLastPrice;             //最后价，约定4位小数
  T_I32 iVWAP;                  //Volume-Weighted Average Price成交量加权平均价格，约定3位小数

  //以下按照53撮合
  T_I32 iPrice_b[OMD_LEVEL2];
  T_U64 uQuantity_b[OMD_LEVEL2];

  T_I32 iPrice_s[OMD_LEVEL2];
  T_U64 uQuantity_s[OMD_LEVEL2];
} OMDMSGEX_LEVEL2, *POMDMSGEX_LEVEL2; // sizeof() = 256

#define OMD_LEVEL1   5
typedef struct t_omdmsgex_level1 {
  T_I32 nActionDay;             //自然日
  T_U32 uSecurityCode;          //证券代码,1-99999的5位十进制

  T_I64 ltime;                  // 时间OMD中定义的时间,自1970-1-1 0：0：0 GMT时标，单位纳秒,0表示数据无效
  T_I32 iPreClosePrice;         // 前一天收盘价，来自11
  T_I32 iPrice;                 //挂牌价格，约定3位小数 ,来自40
  T_I32 iOpenPrice;             //开盘价

  T_U64 ulSharesTraded;         //交易量(股) ,随后的6个来自60
  T_I64 lTurnover;              //交易额,约定4位小数
  T_I32 iHighPrice;             //最高价，约定4位小数
  T_I32 iLowPrice;              //最低价，约定4位小数
  T_I32 iLastPrice;             //最后价，约定4位小数
  T_I32 iVWAP;                  //Volume-Weighted Average Price成交量加权平均价格，约定3位小数

  //按照53撮合
  T_I32 iPrice_b[OMD_LEVEL1];
  T_U64 uQuantity_b[OMD_LEVEL1];

  T_I32 iPrice_s[OMD_LEVEL1];	
  T_U64 uQuantity_s[OMD_LEVEL1];
} OMDMSGEX_LEVEL1, *POMDMSGEX_LEVEL1; // sizeof() =  176

// MsgType = 92 , 根据OMD 54消息生成的经纪商队列
typedef struct t_omdmsgex_brokerqueue {
  T_I32 nActionDay;           //自然日
  T_U32 uSecurityCode;        //证券代码,1-99999的5位十进制

  T_I32 nAskTime;             //叫卖时间（HHMMSSmmm）
  T_I32 nBidTime;             //叫买时间（HHMMSSmmm）
  T_I32 nAskBrokers;          //叫卖经纪商个数
  T_I32 nBidBrokers;          //叫买经纪商个数
  T_U16 usAskBroker[40];      //叫卖前40经纪商ID
  T_U8 ucAskPriceLevel[40];   //叫卖前40经纪商对应的价格档位
  T_U16 usBidBroker[40];      //叫买前40经纪商ID
  T_U8 ucBidPriceLevel[40];   //叫买前40经纪商对应的价格档位
} OMDMSGEX_BROKERQUEUE, *POMDMSGEX_BROKERQUEUE;


#pragma pack(pop)

#endif //_T_HKMARKET_H_