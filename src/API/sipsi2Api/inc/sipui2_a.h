/*!
\file sipui2_a.h
\brief ui接口类

静态连接版for linux

\author	 蒋勇
\version 2.0
\date    2015-10-13
*/

#ifndef SIPUI2_A_H
#define SIPUI2_A_H

#ifdef _WIN32
	#include <windows.h>
#else  // linux
	#ifndef __stdcall
		#define __stdcall
	#endif

    #include <unistd.h>
    #include <pthread.h>
    #include <sys/time.h>
	#include <errno.h>
   // #include <dlfcn.h>

#endif
#include "sipv2_i.h"
#include "sipui2_i.h"

UIHANDLE __stdcall	UI_Open(cb_OnNotify pFunNotify,CBPARAM cbParam);
 void __stdcall UI_Close(UIHANDLE h);
 SIPRET __stdcall UI_SetPproxyInfo(UIHANDLE h,unsigned short uproxytype,const char* sproxyip,unsigned short suport,const char *suser,const char *spass);
 SIPRET __stdcall UI_Connect(UIHANDLE h,const char *sip, unsigned short port,const char* suser,const char* spass,int nMode,bool bAsyn);
 SIPRET __stdcall UI_Disconnect(UIHANDLE h);
 bool __stdcall UI_IsConnect(UIHANDLE h);
 SIPRET __stdcall UI_SubscribeTags(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);
 SIPRET __stdcall UI_UnSubscribeTags(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);
 SIPRET __stdcall UI_UnSubscribeAll(UIHANDLE h);
 SIPRET __stdcall UI_GetTagSnapshots(UIHANDLE h,SIP_TAGERR ptags[],T_U32 usize,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),	void* pParamDoMsg);
 SIPRET __stdcall UI_GetTagHistory(UIHANDLE h,const char* stagname,T_U32 *puMsgNo,T_U32 *puRecs,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg);
 int  __stdcall UI_ParseTagMsgs(TPKG_SIP_TAGMSGS* pPkg,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg);

 SIPRET __stdcall UI_AddTdaUser(	UIHANDLE h,	const char* stag,	const char* suser,	const char* spass);
 SIPRET __stdcall UI_DelTdaUser(	UIHANDLE h,	const char* stag,	const char* suser);
 SIPRET __stdcall UI_GetTdaUser(	UIHANDLE h,	const char* stag,	T_U32 uUserIDs[],	T_U32 uBufSize,	T_U32 *puRetUsers);

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
class CSipUi2
{
public:
    CSipUi2(){
        Clear();
    };
    virtual ~CSipUi2(){
        UIClose();
    };
protected:

    UIHANDLE    _handle;

protected:
	inline void Clear()
	{
        _handle = INVALID_SIPHANDLE;
	}
public:
    bool    IsCreate(){return (_handle != INVALID_SIPHANDLE );}

	inline UIHANDLE GetUiHandle(){return _handle;};
public:
	bool UIOpen(cb_OnNotify pFunNotify,CBPARAM cbParam)
	{
		if(_handle != INVALID_SIPHANDLE)
			return true;
		_handle = UI_Open(pFunNotify,cbParam);
		return (_handle != INVALID_SIPHANDLE);
	}
	void  UIClose()
	{
		if(_handle != INVALID_SIPHANDLE ){
			UI_Close(_handle);
			_handle = INVALID_SIPHANDLE;
		}
	}
	SIPRET UISetPproxyInfo(unsigned short uproxytype,const char* sproxyip,unsigned short suport,const char *suser,const char *spass)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_SetPproxyInfo(_handle,uproxytype,sproxyip,suport,suser,spass);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIConnect(const char *sip, unsigned short port,const char* suser,const char* spass,int nMode,bool bAsyn)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_Connect(_handle,sip,port,suser,spass,nMode,bAsyn);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIDisconnect()
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_Disconnect(_handle);
		return SIPE_ERRHANDLE;
	}
	bool UIIsConnect()
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_IsConnect(_handle);
		return false;
	}
	SIPRET UISubscribeTags(T_SSCTAG ptags[],unsigned int usize)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_SubscribeTags(_handle,ptags,usize);
		return SIPE_ERRHANDLE;
	}

	SIPRET UIUnSubscribeTags(T_SSCTAG ptags[],unsigned int usize)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_UnSubscribeTags(_handle,ptags,usize);
		return SIPE_ERRHANDLE;
	}

	SIPRET UIUnSubscribeAll()
	{
		if(_handle != INVALID_SIPHANDLE)
			return UI_UnSubscribeAll(_handle);
		return SIPE_ERRHANDLE;
	}

	SIPRET UIGetTagSnapshots(SIP_TAGERR ptags[],T_U32 usize,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),	void* pParamDoMsg)
	{
		if(_handle != INVALID_SIPHANDLE)
			return UI_GetTagSnapshots(_handle,ptags,usize,DoMsg,pParamDoMsg);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIGetTagHistory(const char* stagname,T_U32 *puMsgNo,T_U32 *puRecs,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_GetTagHistory(_handle,stagname,puMsgNo,puRecs,DoMsg,pParamDoMsg);
		return SIPE_ERRHANDLE;
	}

	SIPRET INFOGetSvrsAndCodes(
		const char* sip,
		unsigned short wport,
		const char* sUser,
		const char* sPass,
		void(_cdecl *OnReadSvr)(T_ONLINEUISVR svrs[],unsigned int uitems,void* pParam),
		void* OnReadSvrParam,
		const char* sflmk,const char* sflsc,
		void(_cdecl *OnReadSc)(T_SCITEM scs[],unsigned int uitems,void* pParam),
		void* OnReadScParam
	)
	{
		if(_handle != INVALID_SIPHANDLE )
			return INFO_GetSvrsAndCodes(_handle,sip,wport,sUser,sPass,OnReadSvr,OnReadSvrParam,sflmk,sflsc,OnReadSc,OnReadScParam);
		return SIPE_ERRHANDLE;
	}

	int  UIParseTagMsgs(TPKG_SIP_TAGMSGS* pPkg,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg)
	{
		return UI_ParseTagMsgs(pPkg,DoMsg,pParamDoMsg);
	}

	SIPRET  UIAddTdaUser(const char* stag,	const char* suser,	const char* spass)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_AddTdaUser(_handle,stag,suser,spass);
		return SIPE_ERRHANDLE;
	}
	SIPRET  UIDelTdaUser(const char* stag,	const char* suser)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_DelTdaUser(_handle,stag,suser);
		return SIPE_ERRHANDLE;
	}
	SIPRET  UIGetTdaUser(const char* stag,	T_U32 uUserIDs[],	T_U32 uBufSize,	T_U32 *puRetUsers)
	{
		if(_handle != INVALID_SIPHANDLE )
			return UI_GetTdaUser(_handle,stag,uUserIDs,uBufSize,puRetUsers);
		return SIPE_ERRHANDLE;
	}
};
#endif //SIPSI2WAP_H
