#include "stdafx.h"
#include "work.h"

const char* GetErrInfo(T_I32 icode) 
{
	static const char* pnull = "NULL";
	static const struct MSGCODE 
	{
		T_I32 icode;       ///< 错误码
		const char* sdes;  ///< 错误描述
	} errcode[] = {      //公用
		{SIPE_OK, "OK"},
		{SIPE_ERR, "ERROR"},
		{SIPE_ERRHANDLE, "INVALID_SIPHANDLE"},

		// TCP通讯层
		{SIPE_TCPCONNECTERR, "SIPE_TCPCONNECTERR"},
		{SIPE_PROXY_CONNECTERR, "SIPE_PROXY_CONNECTERR"},
		{SIPE_PROXY_AUTHERR, "SIPE_PROXY_AUTHERR"},
		{SIPE_DISCONNECT, "SIPE_DISCONNECT"},
		{SIPE_TCPIOERR, "SIPE_TCPIOERR"},

		// TCP消息层
		{SIPE_TCPMSGERR, "SIPE_TCPMSGERR"},
		{SIPE_TIMEOUT, "SIPE_TIMEOUT"},

		//消息传输层错误
		{SIPE_PKGFMT, "SIPE_PKGFMT"},

		//协议层
		{SIPE_PKGCODE, "SIPE_PKGCODE"},
		{SIPE_PKGDATA, "SIPE_PKGDATA"},
		{SIPE_ASYNCONNECTOK, "SIPE_ASYNCONNECTOK"},
		{SIPE_ASYNCONNECTERR, "SIPE_ASYNCONNECTERR"},

		//应用层
		{SIPE_VERSION, "SIPE_VERSION"},
		{SIPE_NOUSER, "SIPE_NOUSER"},
		{SIPE_USERAUTH, "SIPE_USERAUTH"},
		{SIPE_NOPOWER, "SIPE_NOPOWER"},
		{SIPE_NOTAG, "SIPE_NOTAG"},
		{SIPE_NODATA, "SIPE_NODATA"},
		{SIPE_MSGTYPE, "SIPE_MSGTYPE"},
		{SIPE_MSGSIZE, "SIPE_MSGSIZE"},

		{SIPE_DATALINE, "SIPE_DATALINE"},
		{SIPE_DSLCONFULL, "SIPE_DSLCONFULL"},

		{SIPE_TAGMSGSEQNO, "SIPE_TAGMSGSEQNO"},

		{SIPE_CONNECTFULL, "SIPE_CONNECTFULL"},
		{SIPE_SSCFULL, "SIPE_SSCFULL"},

		{SIPE_ERRARGS, "SIPE_ERRARGS"},
		{SIPE_DSLMAINEXIST, "SISIPE_DSLMAINEXIST"},
		{SIPE_SVRMEMERR, "SIPE_SVRMEMERR"},

		{SIPE_SVREXIST, "SIPE_SVREXIST"},

		{SIPE_TDAUSERERR, "SIPE_TDAUSERERR"},
		{SIPE_TAGNOTSUBSCRIPT, "SIPE_TAGNOTSUBSCRIPT"},
		{SIPE_TDAUSERFULL, "SIPE_TDAUSERFULL"},
		{SIPE_TDANOUSERID, "SIPE_TDANOUSERID"}};
		T_U32 i, un = sizeof(errcode) / sizeof(MSGCODE);
		for (i = 0; i < un; i++)
			if (errcode[i].icode == icode) return errcode[i].sdes;
		return pnull;
}


static void DoPrintMessage(T_SIPTAGMSG* msg) 
{
	switch (msg->MsgType) {
	case 1000: {  // 上交所指数
		T_SH_StockIndex* index = (T_SH_StockIndex*)msg->MsgData;
		printf(
			"tag:%s time:%d open:%d high:%d low:%d last:%d volume:%lld "
			"turnover:%lld\n",
			msg->Code, index->nTime, index->nOpenIndex, index->nHighIndex,
			index->nLowIndex, index->nLastIndex, index->iTotalVolume,
			index->iTurnover);
		break;
			   }

	case 1001: {  // 上交所逐笔成交
		T_SH_StockStepTrade* step_trade = (T_SH_StockStepTrade*)msg->MsgData;
		printf("zb code:%s time:%d price:%d qty:%lld balance:%lld BS:[%c]\n", msg->Code,
			step_trade->nTradeTime, step_trade->nTradePrice,
			step_trade->iTradeQty, step_trade->iTradeMoney, step_trade->cTradeBSflag);
		break;
			   }

	case 1002: 
		{  // 上交所委托队列
			T_SH_StockOrderQueue* order_queue = (T_SH_StockOrderQueue*)msg->MsgData;
			for (int i = 0; i < order_queue->tHead.nItem; i++) 
			{
				T_OrderQueueItem& item = order_queue->tItem[i];
				printf("wt tag:%s time:%d side:%c price:%d orders:%d nABItems:%d nABVolume:%d\n", msg->Code,
					item.nTime, (char)item.nSide, item.nOrders, item.nABItems, item.nABVolume[0]);
			}
			break;
		}

	case 1004: 
		{  // 上交所L2
			T_SH_StockMarketDataL2* market_data =
				(T_SH_StockMarketDataL2*)msg->MsgData;
			printf(
				"pk tag: %s time:%d open:%d high:%d low:%d last:%d volume:%lld "
				"turnover:%lld uPreClose:%d \n",
				msg->Code, market_data->nTime, market_data->uOpen, market_data->uHigh,
				market_data->uLow, market_data->uMatch, market_data->iVolume,
				market_data->iTurnover, market_data->uPreClose);
			break;
		}

	case 1005: {  // 上交所L1
		T_SH_StockMarketDataL1* market_data =
			(T_SH_StockMarketDataL1*)msg->MsgData;
		printf(
			"tag: %s time:%d open:%d high:%d low:%d last:%d volume:%lld "
			"turnover:%lld\n",
			msg->Code, market_data->nTime, market_data->uOpen, market_data->uHigh,
			market_data->uLow, market_data->uMatch, market_data->iVolume,
			market_data->iTurnover);
		break;
			   }

	case 2000: {  // 深交所指数
		T_SZ_StockIndex* index = (T_SZ_StockIndex*)msg->MsgData;
		printf(
			"tag: %s time:%d open:%d high:%d low:%d last:%d volume:%lld "
			"turnover:%lld\n",
			msg->Code, index->nTime, index->nOpenIndex, index->nHighIndex,
			index->nLowIndex, index->nLastIndex, index->iTotalVolume,
			index->iTurnover);
		break;
			   }

	case 2001: {  // 深交所逐笔成交
		T_SZ_StockStepTrade* step_trade = (T_SZ_StockStepTrade*)msg->MsgData;
		printf("tag:%s time:%lld trade_price:%lld qty:%lld\n", msg->Code,
			step_trade->i64TransactTime, step_trade->i64LastPx,
			step_trade->i64LastQty);
		break;
			   }

	case 2002: {  // 深交所委托队列
		T_SZ_StockOrderQueue* order_queue = (T_SZ_StockOrderQueue*)msg->MsgData;
		for (int i = 0; i < order_queue->tHead.nItem; i++) {
			T_OrderQueueItem& item = order_queue->tItem[i];
			printf("tag:%s time:%d side:%c price:%d orders:%d", msg->Code,
				item.nTime, (char)item.nSide, item.nOrders);
		}
		break;
			   }

	case 2003: {  // 深交所逐笔委托
		T_SZ_StockStepOrder* step_order = (T_SZ_StockStepOrder*)msg->MsgData;
		printf("tag:%s time:%lld trade_price:%lld qty:%lld\n", msg->Code,
			step_order->i64TransactTime, step_order->i64Price,
			step_order->i64OrderQty);
		break;
			   }

	case 2004: {  // 深交所L2
		T_SZ_StockMarketDataL2* market_data =
			(T_SZ_StockMarketDataL2*)msg->MsgData;
		printf(
			"tag: %s time:%d open:%d high:%d low:%d last:%d volume:%lld "
			"turnover:%lld\n",
			msg->Code, market_data->nTime, market_data->uOpen, market_data->uHigh,
			market_data->uLow, market_data->uMatch, market_data->iVolume,
			market_data->iTurnover);
		break;
			   }

	case 2005: {  // 深交所L1
		T_SZ_StockMarketDataL1* market_data =
			(T_SZ_StockMarketDataL1*)msg->MsgData;
		printf(
			"tag: %s time:%d open:%d high:%d low:%d last:%d volume:%lld "
			"turnover:%lld\n",
			msg->Code, market_data->nTime, market_data->uOpen, market_data->uHigh,
			market_data->uLow, market_data->uMatch, market_data->iVolume,
			market_data->iTurnover);
		break;
			   }

	default:
		break;
	}
}

void _cdecl DoMsg(T_SIPTAGMSG* ptag, void* pParam) 
{
	if (ptag->Code[0] == '0' && ptag->Code[1] == '.') 
	{
#ifdef _WIN32
		printf("%s: userid = %u,MsgNo = %u,SeqNum = %I64d\n", ptag->Code,
			*((T_U32*)ptag->MsgData), ptag->Filler, ptag->SeqNum);
#else
		printf("%s: userid = %u,MsgNo = %u,SeqNum = %lld\n", ptag->Code,
			*((T_U32*)ptag->MsgData), ptag->Filler, ptag->SeqNum);
#endif
	} 
	else if (0 != strcmp(ptag->Code, "MSG.PUBLIC.T")) 
	{
		DoPrintMessage(ptag);
	}
}


void __stdcall  _OnNotifyMsg(TPKG_SIP* pPkg, CBPARAM pParam) 
{  
	printf("_OnNotifyMsg\n");

	//本地错误
	if (CPKG_LOCAL_ERR == pPkg->PkgCode) 
	{
		TPKG_SIP_SST* p = (TPKG_SIP_SST*)pPkg;
		if (p->ErrCode == SIPE_DISCONNECT)  // 连接断开
		{
			printf("error! OnNotify:%s,%s\n", GetErrInfo(p->ErrCode), p->Des);
		}
		else if (p->ErrCode == SIPE_ASYNCONNECTERR) //异步连接失败
		{
			printf("error: SIPE_ASYNCONNECTERR\n");
		}
		else if (p->ErrCode == SIPE_ASYNCONNECTOK) //异步连接成功
		{
			printf("OnNotify: SIPE_ASYNCONNECTOK\n");
		}
		else if (p->ErrCode == SIPE_CONSVRFAIL) //连接服务器失败,应用程序可以收到这个错误通知时重新连接，用于维持自动重连
		{
			printf("error: SIPE_CONSVRFAIL\n");
			//重连，再次调用UI_Connect()即可
		}	
		else if (p->ErrCode == SIPE_DISCONNECT) //连接服务器失败,应用程序可以收到这个错误通知时重新连接，用于维持自动重连
		{
			printf("error: SIPE_DISCONNECT\n");
			//重连,再次调用UI_Connect()即可
			
		}
		else
		{
			printf("error:%s,%s\n", GetErrInfo(p->ErrCode), p->Des);
		}
	}
	//盘口、逐笔成交、委托队列、逐笔委托 数据
	else if (CPKG_SVRPUTMSG == pPkg->PkgCode)  
	{
		UI_ParseTagMsgs((TPKG_SIP_TAGMSGS*)pPkg, DoMsg, NULL);
	} 
	else if (CPKG_SSCTAGERRNOTIFY == pPkg->PkgCode)  //订阅标签错误
	{
		TPKG_SIP_TAGERR* p = (TPKG_SIP_TAGERR*)pPkg;
		T_U16 i;
		for (i = 0; i < p->TagNum; i++)
			printf("OnNotify:Tag = %s,errcode = %d,errdes = %s\n", p->TagErr[i].TagCode, p->TagErr[i].Errcode, GetErrInfo(p->TagErr[i].Errcode));
	} 
	else
	{
		printf("OnNotify PkgCode = %d,PkgSize = %d\n", pPkg->PkgCode,pPkg->PkgSize);
	}

	return;
}