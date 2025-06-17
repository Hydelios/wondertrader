/*! \mainpage 简介

  &emsp;&emsp;sipui2_i接口是数据使用者客户端接口，简称UI接口，连接服务器为sipsvr2。本文定义了UI接口的数据类型、数据结构、调用接口和错误码定义。<br>
  &emsp;&emsp;windows版接口采用标准DLL方式提供，linux版采用so动态库方式提供，封装了底层TCP通讯、报文压缩解压、命令解析，提
  供给客户端一个应用层级别的接口。全部接口函数采用C方式导出，凡是支持标准标准动态库的开发语言均可使用。<br>
  &emsp;&emsp;为提高效率和数据时效性，客户端具有以下几种数据获取方式：<br>
   方式 | 简述
  ---------|--------
  TCP订阅 | 适合广域网、internet等客户订阅少量标签，可分为最新订阅和增量订阅，增量订阅需要服务端支持。
  PGM可靠组播 | 局域网内，适合VIP大客户，只适合windows客户端。
  UDP组播 | 局域网内，适合大客户，windows和linux客户端适合
  TCP LNK | 适合VIP大客户，一般不开放这个权限，每一个客户都会耗用一份网络带宽资源。

  &emsp;&emsp;接口支持多线程，一个进程最多可以创建64个接口句柄，接口句柄采用linux 文件句柄的原理，是一个0-2048的整数，每一个
  合法句柄索引到内部一个接口对象，不是直接将内部对象指针返回给客户端作为句柄。句柄在多线程中传递和使用是安全的。
  <br>
  <br>
  \ref page_datatype <br><br>
  \ref page_struct	<br><br>
  \ref page_interface	<br><br>
  \ref page_errcode	<br>  <br>
  \ref page_ctrlcode <br>  <br>
  <CENTER> 上海中畅信息科技有限公司</CENTER>
  <CENTER> 2015年3月</CENTER>
  */

/*! \page page_datatype 类型定义
  类型定义 | 简述
  ---------|--------
  \ref T_I8 | \copybrief T_I8
  \ref T_U8 | \copybrief T_U8
  \ref T_I16 | \copybrief T_I16
  \ref T_U16 | \copybrief T_U16
  \ref T_I32 | \copybrief T_I32
  \ref T_U32 | \copybrief T_U32
  \ref T_I64 | \copybrief T_I64
  \ref T_U64 | \copybrief T_U64
  \ref SIPRET | \copybrief SIPRET
  \ref UIHANDLE | \copybrief UIHANDLE
  \ref CBPARAM | \copybrief CBPARAM

  <br>
  <CENTER> 上海中畅信息科技有限公司</CENTER>
  <CENTER> 2015年3月</CENTER>
 */

/*! \page page_struct 结构体定义
  结构体 | 简述
  ---------|--------
 \ref T_SIPTAGMSG | \copybrief   T_SIPTAGMSG
 \ref TPKG_SIP | \copybrief  TPKG_SIP
 \ref SIP_TAGERR | \copybrief  SIP_TAGERR
 \ref TPKG_SIP_TAGERR | \copybrief  TPKG_SIP_TAGERR
 \ref TPKG_SIP_SST | \copybrief  TPKG_SIP_SST
 \ref T_SSCTAG | \copybrief T_SSCTAG
 \ref TPKG_SIP_TAGMSGS | \copybrief TPKG_SIP_TAGMSGS

 <br>
  <CENTER> 上海中畅信息科技有限公司</CENTER>
  <CENTER> 2015年3月</CENTER>
 */

/*! \page page_interface 接口定义
 接口函数 | 简述
  ---------|--------
  \ref UI_Open | \copybrief UI_Open
  \ref UI_Close | \copybrief UI_Close
  \ref UI_SetPproxyInfo | \copybrief UI_SetPproxyInfo
  \ref UI_Connect | \copybrief UI_Connect
  \ref UI_IsConnect | \copybrief UI_IsConnect
  \ref UI_Disconnect | \copybrief UI_Disconnect
  \ref UI_SubscribeTags | \copybrief UI_SubscribeTags
  \ref UI_UnSubscribeTags | \copybrief UI_UnSubscribeTags
  \ref UI_UnSubscribeAll | \copybrief UI_UnSubscribeAll
  \ref UI_GetTagSnapshots | \copybrief UI_GetTagSnapshots
  \ref UI_GetTagHistory | \copybrief UI_GetTagHistory
  \ref UI_ParseTagMsgs | \copybrief UI_ParseTagMsgs
  \ref UI_AddTdaUser | \copybrief UI_AddTdaUser
  \ref UI_DelTdaUser | \copybrief UI_DelTdaUser
  \ref UI_GetTdaUser | \copybrief UI_GetTdaUser
  \ref INFO_GetSvrsAndCodes | \copybrief INFO_GetSvrsAndCodes
  \ref cb_OnNotify | \copybrief cb_OnNotify

  <br>
  <CENTER> 上海中畅信息科技有限公司</CENTER>
  <CENTER> 2015年3月</CENTER>
 */

/*! \page page_errcode 错误码定义
  宏定义 | 值 | 简述
  -------|----|------
  \ref SIPE_OK | 0 | \copybrief SIPE_OK
  \ref SIPE_ERR | 1 | \copybrief SIPE_ERR
  \ref SIPE_ERRHANDLE | (-1) | \copybrief SIPE_ERRHANDLE
  \ref SIPE_TCPCONNECTERR | 2 | \copybrief SIPE_TCPCONNECTERR
  \ref SIPE_PROXY_CONNECTERR | 3 | \copybrief SIPE_PROXY_CONNECTERR
  \ref SIPE_PROXY_AUTHERR | 4 | \copybrief SIPE_PROXY_AUTHERR
  \ref SIPE_DISCONNECT | 5 | \copybrief SIPE_DISCONNECT
  \ref SIPE_TCPIOERR | 6 | \copybrief SIPE_TCPIOERR
  \ref SIPE_TCPMSGERR | 10 | \copybrief SIPE_TCPMSGERR
  \ref SIPE_TIMEOUT | 11 | \copybrief SIPE_TIMEOUT
  \ref SIPE_PGMERR | 13 | \copybrief SIPE_PGMERR
  \ref SIPE_MCBERR | 14 | \copybrief SIPE_MCBERR
  \ref SIPE_ASYNCONNECTOK | 15 | \copybrief SIPE_ASYNCONNECTOK
  \ref SIPE_ASYNCONNECTERR | 16 | \copybrief SIPE_ASYNCONNECTERR
  \ref SIPE_PKGFMT | 100 | \copybrief SIPE_PKGFMT
  \ref SIPE_PKGCODE | 110 | \copybrief SIPE_PKGCODE
  \ref SIPE_PKGDATA | 111 | \copybrief SIPE_PKGDATA
  \ref SIPE_VERSION | 120 | \copybrief SIPE_VERSION
  \ref SIPE_NOUSER | 121 | \copybrief SIPE_NOUSER
  \ref SIPE_USERAUTH | 122 | \copybrief SIPE_USERAUTH
  \ref SIPE_NOPOWER | 123 | \copybrief SIPE_NOPOWER
  \ref SIPE_NOTAG | 124 | \copybrief SIPE_NOTAG
  \ref SIPE_NODATA | 125 | \copybrief SIPE_NODATA
  \ref SIPE_MSGTYPE | 126 | \copybrief SIPE_MSGTYPE
  \ref SIPE_MSGSIZE | 127 | \copybrief SIPE_MSGSIZE
  \ref SIPE_DATALINE | 130 | \copybrief SIPE_DATALINE
  \ref SIPE_DSLCONFULL | 131 | \copybrief SIPE_DSLCONFULL
  \ref SIPE_CONNECTFULL | 140 | \copybrief SIPE_CONNECTFULL
  \ref SIPE_SSCFULL	| 141 | \copybrief SIPE_SSCFULL
  \ref SIPE_USERLOCKED | 142 | \copybrief SIPE_USERLOCKED
  \ref SIPE_ERRARGS	| 150 | \copybrief SIPE_ERRARGS
  \ref SIPE_DSLMAINEXIST |  151  | \copybrief SIPE_DSLMAINEXIST
  \ref SIPE_SVRMEMERR	| 152  | \copybrief SIPE_SVRMEMERR
  \ref SIPE_SVREXIST	| 180	 | \copybrief SIPE_SVREXIST
  \ref SIPE_TDAUSERERR | 191 | \copybrief SIPE_TDAUSERERR
  \ref SIPE_TAGNOTSUBSCRIPT |192 | \copybrief SIPE_TAGNOTSUBSCRIPT
  \ref SIPE_TDAUSERFULL |	193  | \copybrief SIPE_TDAUSERFULL
  \ref SIPE_TDANOUSERID |	194 | \copybrief SIPE_TDANOUSERID
  \ref SIPE_SYSTAG |	195 | \copybrief SIPE_SYSTAG
  \ref SIPE_NOSVR | 196 | \copybrief SIPE_NOSVR
  \ref SIPE_CTRLCODE | 197 | \copybrief SIPE_CTRLCODE
  \ref SIPE_CTRLOPTFULL | 198  | \copybrief SIPE_CTRLOPTFULL
  \ref SIPE_COOKIE | 200 | \copybrief SIPE_COOKIE
  
  <br>

  \page page_ctrlcode 控制码定义
  宏定义 | 值 | 简述
  -------|----|------
  \ref SVRCTRL_RESET | 193 | \copybrief SVRCTRL_RESET

  <br>
  <CENTER> 上海中畅信息科技有限公司</CENTER>
  <CENTER> 2015年3月</CENTER>
*/

/*!
\file sipui2_i.h
\brief 接口函数定义
\author	 蒋勇
\version 2.0
\date    2015-3-24
*/


#ifndef _SIPUI2_I_H
#define _SIPUI2_I_H

#define TCPC_PROXY_NONE			0	 ///< 不代理
#define TCPC_PROXY_SOCKET5		1    ///< socket5代理

#define INVALID_SIPHANDLE		(-1) ///< 无效的SI句柄

typedef int	UIHANDLE;///<接口句柄，是一个0-2048的整数，和linux的文件句柄类似，索引到内部的一个对象，UI_Open返回这个句柄。

//UI登录方式
#define LOGIN_NR				0		///<普通方式，TCP订阅模式
#define LOGIN_LNK				1		///<TCPLNK，TCP级联方式
#define LOGIN_PGM				2		///<PGM方式，局域网可靠组播
#define LOGIN_MCB				3		///<Multicast,多播，双通道

#define	SSC_MODE_NEW			0		///<最新订阅
#define	SSC_MODE_INC			1		///<增量订阅

#define CPKG_SSCTAGERRNOTIFY	10012   ///<PkgCode，服务器推送来的订阅标签错误消息，数据包定义为TPKG_SIP_TAGERR
#define CPKG_SVRPUTMSG			10014	///<PkgCode，服务器推送标签值消息,数据包定义为TPKG_SIP_TAGMSGS


///\brief 用于异步方式通知数据到达、订阅标签错误、连接的断开等信息。
///\param pPkg [in] 通知数据包,需要解析的数据包类型有：
///宏定义 | 值 | 简述
///-------|----|------
///\ref CPKG_LOCAL_ERR | 1 | \copybrief CPKG_LOCAL_ERR
///\ref CPKG_PKGERR | 2 | \copybrief CPKG_PKGERR
///\ref CPKG_SSCTAGERRNOTIFY | 10012 | \copybrief CPKG_SSCTAGERRNOTIFY
///\ref CPKG_SVRPUTMSG | 10014 | \copybrief CPKG_SVRPUTMSG

///\param pParam [in] 回调应用程序自己的参数，即UI_Open带入的第二个参数。
///\return 无
typedef void (__stdcall *cb_OnNotify)(TPKG_SIP* pPkg, CBPARAM pParam); // 数据到达回调函数

#ifdef __cplusplus
extern "C" {
#endif

///\brief 创建一个接口，返回一个接口句柄，其他接口函数均需要使用这个接口句柄，一个进程最多可同时打开64个句柄
///\param pFunNotify [in] 通知消息处理函数
///\param cbParam [in] 应用程序自己使用的参数，会原样传递到cb_OnNotify中第二个参数。
///\return 返回接口句柄，是一个0-2048的整数，和linux的文件句柄类似，索引到内部的一个对象。
UIHANDLE __stdcall	UI_Open(cb_OnNotify pFunNotify,CBPARAM cbParam);

///\brief 关闭接口,关闭UI_Open创建的接口，当应用程序退出时或不再使用接口时，使用UI_Close关闭接口
///
///\param h [in] UI_Open返回的接口句柄
///\return 无
void __stdcall UI_Close(UIHANDLE h);

///\brief 设置代理服务器信息，目前支持TCP的SOCKET5代理，这个函数只需在调用UI_Connect前连接前调用0或1次，如果多次调用这个接口改变代理信息，在下次调用UI_Connect时生效
///
///\param h [in] UI_Open返回的接口句柄
///\param uproxytype [in] 代理方式，TCPC_PROXY_NONE 或者 TCPC_PROXY_SOCKET5
///\param sproxyip [in] 代理服务器IP
///\param suport [in] 代理服务器端口
///\param suser [in] 代理服务器验证用户名
///\param spass [in] 代理服务器验证密码
///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK | \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
SIPRET	__stdcall UI_SetPproxyInfo(UIHANDLE h,unsigned short uproxytype,const char* sproxyip,unsigned short suport,const char *suser,const char *spass);


///\brief 连接到sipsvr2服务器
///
///\param h [in] UI_Open返回的接口句柄
///\param sip [in] sipsvr服务器IP地址,如果是PGM模式，用西文逗号分开，后面跟本地入口IP地址，比如"141.144.166.21,192.168.1.105"，本地入口IP可以有多个，用
///\param port [in] sipsvr服务器端口
///\param suer [in] 账号
///\param spass [in] 账号密码
///\param nMode [in] 连接方式
///\param bAsyn [in] 异步连接方式，立即返回，当后台连接成功后，会用TPKG_SIP_SST报文，ErrCode = SIPE_ASYNCONNECTOK或者SIPE_ASYNCONNECTERR通知
///连接方式     | 描述
///:--------- | :--------
///\ref LOGIN_NR|\copybrief LOGIN_NR
///\ref LOGIN_LNK|\copybrief LOGIN_LNK
///\ref LOGIN_PGM|\copybrief LOGIN_PGM
///\ref LOGIN_MCB|\copybrief LOGIN_MCB

///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK|\copybrief SIPE_OK
///\ref SIPE_ERRHANDLE|\copybrief SIPE_ERRHANDLE
///\ref SIPE_TCPCONNECTERR   |\copybrief SIPE_TCPCONNECTERR
///\ref SIPE_PROXY_CONNECTERR |\copybrief SIPE_PROXY_CONNECTERR
///\ref SIPE_PROXY_AUTHERR|\copybrief SIPE_PROXY_AUTHERR
///\ref SIPE_DISCONNECT|\copybrief SIPE_DISCONNECT
///\ref SIPE_TCPIOERR|\copybrief SIPE_TCPIOERR
///\ref SIPE_TIMEOUT|\copybrief SIPE_TIMEOUT
///\ref SIPE_VERSION|\copybrief SIPE_VERSION
///\ref SIPE_NOUSER |\copybrief SIPE_NOUSER
///\ref SIPE_USERAUTH |\copybrief SIPE_USERAUTH
SIPRET __stdcall UI_Connect(UIHANDLE h,const char *sip, unsigned short port,const char* suer,const char* spass,int nMode,bool bAsyn);


///\brief 检测当前是否已连接到服务器
///
///\param h [in] UI_Open返回的接口句柄
///\return 返回如下错误码。
///返回值     | 描述
///:--------- | :--------
///true，非0|已连接
///false，0|没有连接
bool __stdcall UI_IsConnect(UIHANDLE h);


///\brief 应用程序主动断开连接
///
///\param h h [in] UI_Open返回的接口句柄
///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK | \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
SIPRET __stdcall UI_Disconnect(UIHANDLE h);


///\brief 异步方式订阅标签值
///
///向服务器提交需要订阅的标签,该函数提交到服务器后立即返回，不等服务器应答，如果有标签错误错误，服务器会主动发送错误信息，客户端在cb_OnNotify回调函数中会得到通知。
///\param h [in] UI_Open返回的接口句柄
///\param ptags [in] 订阅标签结构体数组
///\param usize [in] ptags中的元素个数
///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK| \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
///\ref SIPE_DISCONNECT | \copybrief SIPE_DISCONNECT
SIPRET __stdcall UI_SubscribeTags(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);

///\brief 取消标签订阅
///
///取消标签订阅,取消订阅后，服务器不再推送取消标签的值。
///\param h [in] UI_Open返回的接口句柄
///\param ptags [in] 订阅标签结构体数组，只需要填写其中的标签名即可。
///\param usize [in] ptags中的元素个数
///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK| \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
///\ref SIPE_DISCONNECT | \copybrief SIPE_DISCONNECT
SIPRET __stdcall UI_UnSubscribeTags(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);

///\brief 取消所有标签订阅
///
///取消当前订阅的全部标签订阅，服务器不再推送任何标签值(公告信息除外)。
///\param h [in] UI_Open返回的接口句柄
///\return 返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK| \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
///\ref SIPE_DISCONNECT | \copybrief SIPE_DISCONNECT
SIPRET  __stdcall UI_UnSubscribeAll(UIHANDLE h);

///\brief 向服务器请求获取最新标签值，同步方式
///
///向服务器请求获取最新标签值，同步方式，要等待服务返回,是阻塞模式的，不建议采用这个方式，时效性不如订阅方式。
///\param h [in] UI_Open返回的接口句柄
///\param ptags [in/out] SIP_TAGERR数组，输入时填写标签名，输出时填写该标签的错误码。
///\param usize ptags 中元素个数
///\param	DoMsg [in] 调用者提供的处理解析结果的函数<br>
			///void DoMsg(T_SIPTAGMSG* pMsg,void* pParam)<br>
			///pMsg:解析出的T_SIPTAGMSG，<br>
			///pParam:调用者自己的参数,pParamDoMsg被传递到这里<br>
///\param pParamDoMsg [in] 传递给DoMsg的最后一个参数
///\return DoMsg会被调用多次，每次处理一个读到的标签值，返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK | \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
///\ref SIPE_DISCONNECT | \copybrief SIPE_DISCONNECT
///\ref SIPE_TCPMSGERR | \copybrief SIPE_TCPMSGERR
///\ref SIPE_TIMEOUT | \copybrief SIPE_TIMEOUT
SIPRET __stdcall UI_GetTagSnapshots(UIHANDLE h,SIP_TAGERR ptags[],T_U32 usize,
		void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),
		void* pParamDoMsg);

///\brief 向服务器请求获取历史数据，同步方式
///
///向服务器请求获取最新标签值，同步方式，要等待服务返回,是阻塞模式的。
///\param h [in] UI_Open返回的接口句柄
///\param stagname [in] 标签名,0结束的字符串
///\param puSeqNo [in/out] 起始数据消息号，0表示从开始，这是sipsvr服务器收到上游数据时编写的递增不一定连续的序号，每天初始化后复位。返回时填写最后一个记录的序列号。
///\param puRecs [out] 返回时回填读到的记录个数
///\param	DoMsg [in] 调用者提供的处理解析结果的函数<br>
			///void DoMsg(T_SIPTAGMSG* pMsg,void* pParam)<br>
			///pMsg:解析出的T_SIPTAGMSG，<br>
			///pParam:调用者自己的参数,pParamDoMsg被传递到这里<br>
///\param pParamDoMsg [in] 传递给DoMsg的最后一个参数
///\return DoMsg会被调用多次，每次处理一个读到的标签值，返回如下错误码。
///错误码     | 描述
///:--------- | :--------
///\ref SIPE_OK | \copybrief SIPE_OK
///\ref SIPE_ERRHANDLE | \copybrief SIPE_ERRHANDLE
///\ref SIPE_DISCONNECT | \copybrief SIPE_DISCONNECT
///\ref SIPE_TCPMSGERR | \copybrief SIPE_TCPMSGERR
///\ref SIPE_TIMEOUT | \copybrief SIPE_TIMEOUT
SIPRET __stdcall UI_GetTagHistory(UIHANDLE h,const char* stagname,T_U32 *puSeqNo,T_U32 *puRecs,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg);


///\brief 从infosvr服务器获得可用服务器和代码表
///
///从infosvr服务器获得可用服务器和代码表,根据参数不同可以只读服务器表或代码表
///\param h  [in] UI_Open返回的接口句柄
///\param sip [in] infosvr的服务器IP
///\param wport [in] infosvr的信息服务端口
///\param sUser [in] 用户名
///\param sPass [in] 密码
///\param OnReadSvr [in] 处理读回的服务器函数，NULL表示不读取可用服务器（和用户同一个组）列表，
///\param OnReadSvrParam [in] OnReadSvr用的参数，一般带入集合对象指针
///\param sflmk [in] 读取代码表时市场匹配串,*或NULL表示全部
///\param sflsc [in] 读取代码表时代码匹配串,*或NULL表示全部
///\param OnReadSc [in] 处理读回的代码表的函数,NULL表示不读取代码表
///\param OnReadScParam [in] OnReadSc用的参数，一般带入集合对象指针
///\return SIE_OK表示成功，其他为错误码
SIPRET __stdcall INFO_GetSvrsAndCodes(
	UIHANDLE h,
	const char* sip,
	unsigned short wport,
	const char* sUser,
	const char* sPass,
	void(_cdecl *OnReadSvr)(T_ONLINEUISVR svrs[],unsigned int uitems,void* pParam),
	void* OnReadSvrParam,
	const char* sflmk,const char* sflsc,
	void(_cdecl *OnReadSc)(T_SCITEM scs[],unsigned int uitems,void* pParam),
	void* OnReadScParam
	);

///\brief 添加交易数据账号
///
///添加交易数据账号,
///\param h  [in] UI_Open返回的接口句柄
///\param stag  [in] 交易数据标签名，必须先要订阅,市场ID为两个'0'字符，比如00.cjhb.td
///\param suser [in] 数据所属用户,全数字账号
///\param spass [in] 数据所属用户密码
///\return SIE_OK表示成功，其他为错误码
SIPRET __stdcall UI_AddTdaUser(	UIHANDLE h,	const char* stag,	const char* suser,	const char* spass);


///\brief 删除交易数据账号
///
///添加交易数据账号,
///\param h  [in] UI_Open返回的接口句柄
///\param stag  [in] 交易数据标签名，必须先要订阅,市场ID为两个'0'字符，比如00.cjhb.td
///\param suser [in] 数据所属用户,全数字账号
///\return SIE_OK表示成功，其他为错误码
SIPRET __stdcall UI_DelTdaUser(	UIHANDLE h,	const char* stag,	const char* suser);


///\brief 获取交易数据标签下用户账号
///
///添加交易数据账号,
///\param h  [in] UI_Open返回的接口句柄
///\param stag  [in] 交易数据标签名，必须先要订阅
///\param uUserIDs [out] 数据所属用户ID数组
///\param uBufSize [in] uUserIDs数组大小
///\param puRetUsers [out] 读取到的用户ID个数
///\return SIE_OK表示成功，其他为错误码
SIPRET __stdcall UI_GetTdaUser(	UIHANDLE h,	const char* stag,	T_U32 uUserIDs[],	T_U32 uBufSize,	T_U32 *puRetUsers);

///\brief 辅助函数，解析TPKG_SIP_TAGMSGS数据包
///
///将TPKG_SIP_TAGMSGS数据包解析为T_SIPTAGMSG，该接口函数是一个静态函数，无需指定接口句柄，用于方便
///调用者在cb_OnNotify回掉函数中解析TPKG_SIP_TAGMSGS数据包。当然调用者也可以不使用这个函数而自己解析TPKG_SIP_TAGMSGS数据包
///\param	pPkg [in] TPKG_SIP_TAGMSGS数据包结构体指针
///\param	DoMsg [in] 调用者提供的处理解析结果的函数<br>
			///void DoMsg(T_SIPTAGMSG* pMsg,void* pParam)<br>
			///pMsg:解析出的T_SIPTAGMSG，<br>
			///pParam:调用者自己的参数,pParamDoMsg被传递到这里<br>
///\param  pParamDoMsg [in] DoMsg的最后一个参数
///\return 返回解析出的T_SIPTAGMSG个数。
///\remark DoMsg会被调用多次，每解析出一个T_SIPTAGMSG就会调用一次。
	int  __stdcall UI_ParseTagMsgs(TPKG_SIP_TAGMSGS* pPkg,
		void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),
		void* pParamDoMsg);

///\brief 从infosvr服务器获得可用代码表
///
///从infosvr服务器获得可用代码表
///\param h  [in] UI_Open返回的接口句柄
///\param sip [in] infosvr的服务器IP
///\param wport [in] infosvr的信息服务端口
///\param sUser [in] 用户名
///\param sPass [in] 密码	
///\param sflmk [in] 读取代码表时市场匹配串,*或NULL表示全部
///\param sflsc [in] 读取代码表时代码匹配串,*或NULL表示全部
///\param OnReadSc [in] 处理读回的代码表的函数
///\param OnReadScParam [in] OnReadSc用的参数，一般带入集合对象指针
///\return SIE_OK表示成功，其他为错误码
SIPRET __stdcall INFO_GetCodes(
		UIHANDLE h,
		const char* sip,
		unsigned short wport,
		const char* sUser,
		const char* sPass,
		const char* sflmk, const char* sflsc,
		void(_cdecl *OnReadSc)(T_SCITEMEX scs[], unsigned int uitems, void* pParam),
		void* OnReadScParam
	);

#ifdef __cplusplus
}
#endif

#endif //_SIPUI2_I_H
