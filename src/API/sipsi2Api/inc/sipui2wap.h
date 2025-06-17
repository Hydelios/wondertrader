/*! 
\file sipui2wap.h
\brief ui接口包装类  
 
为方便C++用户使用的动态加载动态库的包装类，适合windows和linux系统，仅供参考，不是SIPUI接口必须的部分。  
  
\author	 蒋勇
\version 2.0  
\date    2015-3-5
*/

#ifndef SIPUI2WAP_H
#define SIPUI2WAP_H

#ifdef _WIN32
	#include <windows.h>
#else  // linux
	#ifndef __stdcall
		#define __stdcall
	#endif

    #include <unistd.h>
    #include <dlfcn.h>

#endif
#include "sipv2_i.h"
#include "sipui2_i.h"

typedef UIHANDLE (__stdcall	*iUI_Open)(cb_OnNotify pFunNotify,CBPARAM cbParam);
typedef void (__stdcall *iUI_Close)(UIHANDLE h);
typedef SIPRET (__stdcall *iUI_SetPproxyInfo)(UIHANDLE h,unsigned short uproxytype,const char* sproxyip,unsigned short suport,const char *suser,const char *spass);
typedef SIPRET (__stdcall *iUI_Connect)(UIHANDLE h,const char *sip, unsigned short port,const char* suser,const char* spass,int nMode,bool bAsyn);
typedef SIPRET (__stdcall *iUI_Disconnect)(UIHANDLE h);
typedef bool (__stdcall *iUI_IsConnect)(UIHANDLE h);
typedef SIPRET (__stdcall *iUI_SubscribeTags)(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);
typedef SIPRET (__stdcall *iUI_UnSubscribeTags)(UIHANDLE h,T_SSCTAG ptags[],unsigned int usize);
typedef SIPRET (__stdcall *iUI_UnSubscribeAll)(UIHANDLE h);
typedef SIPRET (__stdcall *iUI_GetTagSnapshots)(UIHANDLE h,SIP_TAGERR ptags[],T_U32 usize,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),	void* pParamDoMsg);
typedef SIPRET (__stdcall *iUI_GetTagHistory)(UIHANDLE h,const char* stagname,T_U32 *puMsgNo,T_U32 *puRecs,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg);
typedef int  (__stdcall *iUI_ParseTagMsgs)(TPKG_SIP_TAGMSGS* pPkg,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg);

typedef SIPRET (__stdcall *iUI_AddTdaUser)(	UIHANDLE h,	const char* stag,	const char* suser,	const char* spass);
typedef SIPRET (__stdcall *iUI_DelTdaUser)(	UIHANDLE h,	const char* stag,	const char* suser);
typedef SIPRET (__stdcall *iUI_GetTdaUser)(	UIHANDLE h,	const char* stag,	T_U32 uUserIDs[],	T_U32 uBufSize,	T_U32 *puRetUsers);

typedef SIPRET (__stdcall *iINFO_GetSvrsAndCodes)(
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
        Unload();
    };
protected:
#ifdef _WIN32
    #define     dlclose(a)     FreeLibrary(a)
    #define     dlsym(a,b)     GetProcAddress(a,b)
    HINSTANCE   _dlhandle;
#else
    void        *_dlhandle;
#endif // _WIN32

    UIHANDLE    _handle;

    iUI_Open			_iUI_Open;
    iUI_Close			_iUI_Close;
	iUI_SetPproxyInfo	_iUI_SetPproxyInfo;
	iUI_Connect			_iUI_Connect;
	iUI_Disconnect		_iUI_Disconnect;
	iUI_IsConnect		_iUI_IsConnect;

	iUI_SubscribeTags	_iUI_SubscribeTags;
	iUI_UnSubscribeTags	_iUI_UnSubscribeTags;
	iUI_UnSubscribeAll  _iUI_UnSubscribeAll;
	
	iUI_GetTagSnapshots  _iUI_GetTagSnapshots;
	iUI_GetTagHistory	 _iUI_GetTagHistory;

	iUI_ParseTagMsgs	_iUI_ParseTagMsgs;
	iINFO_GetSvrsAndCodes _iINFO_GetSvrsAndCodes;

	iUI_AddTdaUser		_iUI_AddTdaUser;
	iUI_DelTdaUser		_iUI_DelTdaUser;
	iUI_GetTdaUser		_iUI_GetTdaUser;
protected:
	void Clear()
	{
		_dlhandle = NULL;
        _handle = INVALID_SIPHANDLE;
		_iUI_Open = NULL;
		_iUI_Close = NULL;
		_iUI_SetPproxyInfo = NULL;
		_iUI_Connect = NULL;
		_iUI_Disconnect = NULL;
		_iUI_IsConnect = NULL;
		
		_iUI_SubscribeTags = NULL;
		_iUI_UnSubscribeTags = NULL;
		_iUI_UnSubscribeAll = NULL;

		_iUI_GetTagSnapshots = NULL;
		_iUI_GetTagHistory = NULL;

		_iUI_ParseTagMsgs = NULL;
		_iINFO_GetSvrsAndCodes = NULL;

		_iUI_AddTdaUser = NULL;
		_iUI_DelTdaUser = NULL;
		_iUI_GetTdaUser = NULL;
	}
public:
    bool    IsLoad(){return (_dlhandle != NULL);}
    bool    IsCreate(){return (_handle !=0 );}
    bool    Load(const char* slibfile) // 加载库和提取接口
    {
        if(_dlhandle)
            Unload();
    #ifdef _WIN32
        _dlhandle = LoadLibraryA(slibfile);
    #else
        _dlhandle = dlopen( slibfile, RTLD_LAZY );
    #endif
        if (!_dlhandle)
            return false;

		_iUI_Open  =  (iUI_Open)dlsym(_dlhandle,"UI_Open");
		_iUI_Close  =  (iUI_Close)dlsym(_dlhandle,"UI_Close");
		_iUI_SetPproxyInfo  =  (iUI_SetPproxyInfo)dlsym(_dlhandle,"UI_SetPproxyInfo");
		_iUI_Connect  =  (iUI_Connect)dlsym(_dlhandle,"UI_Connect");
		_iUI_Disconnect  =  (iUI_Disconnect)dlsym(_dlhandle,"UI_Disconnect");
		_iUI_IsConnect = (iUI_IsConnect)dlsym(_dlhandle,"UI_IsConnect");
		
		_iUI_SubscribeTags  =  (iUI_SubscribeTags)dlsym(_dlhandle,"UI_SubscribeTags");		
		_iUI_UnSubscribeTags  =  (iUI_UnSubscribeTags)dlsym(_dlhandle,"UI_UnSubscribeTags");
		_iUI_UnSubscribeAll  =  (iUI_UnSubscribeAll)dlsym(_dlhandle,"UI_UnSubscribeAll");

		_iUI_GetTagSnapshots  =  (iUI_GetTagSnapshots)dlsym(_dlhandle,"UI_GetTagSnapshots");
		_iUI_GetTagHistory  =  (iUI_GetTagHistory)dlsym(_dlhandle,"UI_GetTagHistory");
		_iUI_ParseTagMsgs  =  (iUI_ParseTagMsgs)dlsym(_dlhandle,"UI_ParseTagMsgs");
		_iINFO_GetSvrsAndCodes = (iINFO_GetSvrsAndCodes)dlsym(_dlhandle,"INFO_GetSvrsAndCodes");

		_iUI_AddTdaUser = (iUI_AddTdaUser)dlsym(_dlhandle,"UI_AddTdaUser");
		_iUI_DelTdaUser = (iUI_DelTdaUser)dlsym(_dlhandle,"UI_DelTdaUser");
		_iUI_GetTdaUser = (iUI_GetTdaUser)dlsym(_dlhandle,"UI_GetTdaUser");

        return true;
    };
	bool    Unload() // 卸载库
    {
        if(!_dlhandle)
            return true;
        dlclose( _dlhandle );
		Clear();
        return true;

    }
	inline UIHANDLE GetUiHandle(){return _handle;};
public:
	bool UIOpen(cb_OnNotify pFunNotify,CBPARAM cbParam)
	{
		if(_handle != INVALID_SIPHANDLE)
			return true;
		if(_dlhandle && _iUI_Open)
			_handle = _iUI_Open(pFunNotify,cbParam);
		return (_handle != INVALID_SIPHANDLE);
	}
	void  UIClose()
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_Close){
			_iUI_Close(_handle);
			_handle = INVALID_SIPHANDLE;
		}
	}
	SIPRET UISetPproxyInfo(unsigned short uproxytype,const char* sproxyip,unsigned short suport,const char *suser,const char *spass)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_SetPproxyInfo)
			return _iUI_SetPproxyInfo(_handle,uproxytype,sproxyip,suport,suser,spass);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIConnect(const char *sip, unsigned short port,const char* suser,const char* spass,int nMode,bool bAsyn)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_Connect)
			return _iUI_Connect(_handle,sip,port,suser,spass,nMode,bAsyn);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIDisconnect()
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_Disconnect)
			return _iUI_Disconnect(_handle);
		return SIPE_ERRHANDLE;
	}
	bool UIIsConnect()
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_IsConnect)
			return _iUI_IsConnect(_handle);
		return false;
	}
	SIPRET UISubscribeTags(T_SSCTAG ptags[],unsigned int usize)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_SubscribeTags)
			return _iUI_SubscribeTags(_handle,ptags,usize);
		return SIPE_ERRHANDLE;
	}

	SIPRET UIUnSubscribeTags(T_SSCTAG ptags[],unsigned int usize)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_UnSubscribeTags)
			return _iUI_UnSubscribeTags(_handle,ptags,usize);
		return SIPE_ERRHANDLE;
	}
	
	SIPRET UIUnSubscribeAll()
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_UnSubscribeAll)
			return _iUI_UnSubscribeAll(_handle);
		return SIPE_ERRHANDLE;
	}

	SIPRET UIGetTagSnapshots(SIP_TAGERR ptags[],T_U32 usize,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),	void* pParamDoMsg)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_GetTagSnapshots)
			return _iUI_GetTagSnapshots(_handle,ptags,usize,DoMsg,pParamDoMsg);
		return SIPE_ERRHANDLE;
	}
	SIPRET UIGetTagHistory(const char* stagname,T_U32 *puMsgNo,T_U32 *puRecs,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_GetTagHistory)
			return _iUI_GetTagHistory(_handle,stagname,puMsgNo,puRecs,DoMsg,pParamDoMsg);
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
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iINFO_GetSvrsAndCodes)
			return _iINFO_GetSvrsAndCodes(_handle,sip,wport,sUser,sPass,OnReadSvr,OnReadSvrParam,sflmk,sflsc,OnReadSc,OnReadScParam);
		return SIPE_ERRHANDLE;
	}

	int  UIParseTagMsgs(TPKG_SIP_TAGMSGS* pPkg,void(_cdecl *DoMsg)(T_SIPTAGMSG* ,void* ),void* pParamDoMsg)
	{
		if(_dlhandle && _iUI_ParseTagMsgs)
			return _iUI_ParseTagMsgs(pPkg,DoMsg,pParamDoMsg);
		return SIPE_ERRHANDLE;
	}

	SIPRET  UIAddTdaUser(const char* stag,	const char* suser,	const char* spass)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_AddTdaUser)
			return _iUI_AddTdaUser(_handle,stag,suser,spass);
		return SIPE_ERRHANDLE;
	}
	SIPRET  UIDelTdaUser(const char* stag,	const char* suser)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_DelTdaUser)
			return _iUI_DelTdaUser(_handle,stag,suser);
		return SIPE_ERRHANDLE;
	}
	SIPRET  UIGetTdaUser(const char* stag,	T_U32 uUserIDs[],	T_U32 uBufSize,	T_U32 *puRetUsers)
	{
		if(_handle != INVALID_SIPHANDLE && _dlhandle && _iUI_GetTdaUser)
			return _iUI_GetTdaUser(_handle,stag,uUserIDs,uBufSize,puRetUsers);
		return SIPE_ERRHANDLE;
	}

};
#endif //SIPSI2WAP_H
