#pragma once

#include "engineDef/dataStruct.hpp"

#pragma pack(push, 1)

struct IndexDataPayload
{
	double Open;
	double Last;
	double High;
	double Low;
	int Cumvol;
	double Cumamount; 
};

struct FutureDataPayload
{
	double Last;
	double Max;
	double Min;
	double Open;
	double High;
	double Low;
	int Cumvol;
	double Cumamount;
	int openInt;	//持仓量
	double askPrc;
	int askVol;
	double bidPrc;
	int bidVol;
};

#pragma pack(pop)

#define MARKET_DATA_TYPE_INDEX_DATA 203
#define MARKET_DATA_TYPE_ETF_DATA 204
#define MARKET_DATA_TYPE_FUTURE_DATA 205

using IndexData = MarketDataGeneric<IndexDataPayload>;
using ETFData = MarketDataGeneric<MarketDataStockL2>;
using FutureData = MarketDataGeneric<FutureDataPayload>;
