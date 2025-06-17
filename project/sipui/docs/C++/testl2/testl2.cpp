// testl2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include "work.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int iRet=0;

	//打开接口句柄
	UIHANDLE hr = UI_Open(_OnNotifyMsg, NULL); //_OnNotifyMsg 为回调接口
	if ( hr==INVALID_SIPHANDLE ) //无效句柄
	{
		printf("UI_Open error!\n");
		return -1;
	}

	//建立连接
	iRet = UI_Connect(hr, "183.134.103.19", 30002, "ctcs99999", "ctcs99999", LOGIN_NR, false);
	if ( iRet != SIPE_OK)
	{
		printf("%s\n", GetErrInfo(iRet));
		return -2;
	}
	
	while (true)
	{
		//检测当前是否已连接到服务器
		if (!UI_IsConnect(hr))
		{
			printf("与服务端连接没有成功\n");
			_sleep(3000);
		}
		else
		{
			break;
		}
	}

	//组织盘口订阅信息
	T_SSCTAG tag[TWONODE];  //T_SSCTAG 使用说明请见定义
	memset(tag, 0, sizeof(T_SSCTAG)*TWONODE);
	
	//组织订阅上海的股票
	strcpy(tag[0].sTag, "SH.600570.L2");
	tag[0].cMode = SSC_MODE_INC;
	tag[0].uSeqNo = -1;

	//组织订阅深圳的股票
	strcpy(tag[1].sTag, "SZ.000001.L2");
	tag[1].cMode = SSC_MODE_INC;
	tag[1].uSeqNo = -1;

	//订阅盘口
	iRet = UI_SubscribeTags(hr, tag, 1); //-1 因为测试环境只有上海的行情
	if ( iRet )
	{
		printf("UI_SubscribeTags failure, error_no=[%d] \n", iRet);
		return -2;
	}
#if 0
	//订阅逐笔成交
	//组织订阅上海的股票逐笔成交
	strcpy(tag[0].sTag, "SH.600570.ZC");
	tag[0].cMode = SSC_MODE_INC;
	tag[0].uSeqNo = -1;

	//组织订阅深圳的股票逐笔成交
	strcpy(tag[1].sTag, "SZ.000001.ZC");
	tag[1].cMode = SSC_MODE_INC;
	tag[1].uSeqNo = -1;
	iRet = UI_SubscribeTags(hr, tag, TWONODE-1); //-1 因为测试环境只有上海的行情
	if ( iRet )
	{
		printf("UI_SubscribeTags failure, error_no=[%d] \n", iRet);
		return -2;
	}

	//订阅委托队列
	//组织订阅上海的股票委托队列
	strcpy(tag[0].sTag, "SH.600570.WD");
	tag[0].cMode = SSC_MODE_INC;
	tag[0].uSeqNo = -1;

	//组织订阅深圳的股票委托队列
	strcpy(tag[1].sTag, "SZ.000001.WD");
	tag[1].cMode = SSC_MODE_INC;
	tag[1].uSeqNo = -1;
	iRet = UI_SubscribeTags(hr, tag, TWONODE-1); //-1 因为测试环境只有上海的行情
	if ( iRet )
	{
		printf("UI_SubscribeTags failure, error_no=[%d] \n", iRet);
		return -2;
	}

	//订阅深圳的逐笔委托
	//组织订阅上海的股票逐笔委托
	strcpy(tag[0].sTag, "SH.000001.ZW");
	tag[0].cMode = SSC_MODE_INC;
	tag[0].uSeqNo = -1;
	iRet = UI_SubscribeTags(hr, tag, TWONODE-1); //-1 因为测试环境只有上海的行情
	if ( iRet )
	{
		printf("UI_SubscribeTags failure, error_no=[%d] \n", iRet);
		return -2;
	}
#endif

	while (true)
	{
		//检测当前是否已连接到服务器
		if (!UI_IsConnect(hr))
		{
			printf("与服务端连接没有成功\n");
			_sleep(3000);
		}
	}

	//停留
	getchar();

	//取消全部订阅
	iRet = UI_UnSubscribeAll(hr);
	if ( iRet==SIPE_ERRHANDLE )
	{
		printf("error! UI_UnSubscribeAll handle\n");
	}
	else if ( iRet==SIPE_DISCONNECT )
	{
		printf("连接断开\n");
	}

	//关闭连接
	iRet = UI_Disconnect(hr);
    if ( iRet==SIPE_ERRHANDLE )
	{
		printf("error handle\n");
	}
	getchar();
	//关闭接口句柄
	UI_Close(hr);


	return iRet;
}

