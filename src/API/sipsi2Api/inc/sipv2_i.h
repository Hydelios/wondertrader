/*!
\file sipv2_i.h
\brief sip2.0接口公共定义

 定义了整个实时行情系统2.0版接口的公共数据类型和定义<br>
 基础类型定义，规范不同字节长度的整数<br>
 错误定义，服务端和客户端均会使用的错误码定义<br>

\author	 蒋勇
\version 2.0
\date    2015-2-3

*/

// 基本数据类型
#ifndef _SIPV2_H
#define _SIPV2_H

#ifndef _WIN32
	#ifndef __stdcall
		#define __stdcall		///< linux版本不需要，定义为空
	#endif
	#ifndef _cdecl
        #define _cdecl
    #endif // _cdecl
#endif

// 规范化基本数据类型的长度
typedef char					T_I8;	///<1字节带符号整数
typedef unsigned char			T_U8;   ///<1字节无符号整数

typedef short int				T_I16;	///<2字节带符号整数
typedef unsigned short int		T_U16;	///<2字节无符号整数

typedef int						T_I32;	///<4字节带符号整数
typedef unsigned int			T_U32;	///<4字节无符号整数

typedef long long			    T_I64;	///<8字节带符号整数
typedef unsigned long long	    T_U64;	///<8字节无符号整数

typedef T_I32					SIPRET; ///<SIP带错误码的返回值类型
typedef void*					CBPARAM;///<回调参数

//错误码定义
#define SIPE_OK					0	  ///<成功
#define SIPE_ERR				1     ///<未知或一般错误
#define SIPE_ERRHANDLE			(-1)  ///<错误的句柄

//通讯层错误
#define SIPE_TCPCONNECTERR		2     ///<TCP连接错误
#define SIPE_PROXY_CONNECTERR	3	  ///<代理连接错误
#define SIPE_PROXY_AUTHERR		4     ///<代理验证错误
#define SIPE_DISCONNECT			5     ///<连接断开
#define SIPE_TCPIOERR			6     ///<TCPIO错误
#define SIPE_CONSVRFAIL			7	  ///<连接服务器失败，应用程序可以收到这个错误通知时重新连接，用于维持自动重连
#define SIPE_SENDBLOCK		    8     ///<发送阻塞，无法发送

#define SIPE_TCPMSGERR			10    ///<通讯层报文错误
#define SIPE_TIMEOUT			11    ///<超时

#define SIPE_PGMERR				13	  ///<Start PGM error
#define SIPE_MCBERR				14	  ///<Start multicast error
#define SIPE_ASYNCONNECTOK		15	  ///<异步连接成功
#define SIPE_ASYNCONNECTERR		16    ///<异步连接失败

//协议层错误
#define SIPE_PKGFMT				100	  ///<报文格式错误
#define SIPE_PKGCODE			110	  ///<无此功能号
#define SIPE_PKGDATA			111	  ///<报文数据段

//应用层错误
#define SIPE_VERSION			120	  ///<版本错误
#define SIPE_NOUSER				121	  ///<无此账号
#define SIPE_USERAUTH			122	  ///<用户验证错误
#define SIPE_NOPOWER			123	  ///<权限错误
#define SIPE_NOTAG				124   ///<数据编码错误，无此编码
#define SIPE_NODATA				125   ///<无数据
#define SIPE_MSGTYPE			126   ///<标签值消息类型错误
#define SIPE_MSGSIZE 		    127   ///<标签消值息长度错误
#define SIPE_NOMCBOUT			128   ///<No multicast output
#define SIPE_NOPGMOUT			129   ///<No PGM output

#define SIPE_DATALINE			130   ///<数据源逻辑线路错误
#define SIPE_DSLCONFULL		    131   ///<数据源逻辑线路的物理连接数满

#define SIPE_TAGMSGSEQNO		132   ///<标签数据消息的序列号错误(非0不递增)

#define SIPE_CONNECTFULL		140   ///<连接满
#define SIPE_SSCFULL			141   ///<订阅满
#define SIPE_USERLOCKED			142   ///<用户被禁用，锁定
#define SIPE_USEREXDATE         143   //用户账号过期

#define SIPE_ERRARGS			150   ///<参数错误
#define SIPE_DSLMAINEXIST       151   ///<SI逻辑线路的主物理线路已存在
#define SIPE_SVRMEMERR			152   ///<服务器内存错误

#define SIPE_SVREXIST			180	  ///<服务器已连接(已运行)，infosvr返回这个错误码

#define SIPE_TDAUSERERR			191   ///<交易账号错误
#define SIPE_TAGNOTSUBSCRIPT	192   ///<标签没有订阅
#define SIPE_TDAUSERFULL		193   ///<单个交易数据标签添加的用户账号满,不大于1024个
#define SIPE_TDANOUSERID		194	  ///<没有交易数据账号

#define SIPE_SYSTAG				195   ///<系统标签
#define SIPE_NOSVR				196   ///<服务器不存在或或不在线
#define SIPE_CTRLCODE			197   ///<错误的控制码，或不支持的控制码
#define SIPE_CTRLOPTFULL		198   ///<控制命令缓冲满

#define SIPE_COOKIE				200   ///<错误的COOKIE

#ifdef _WIN32
#pragma warning (disable : 4200)
#endif // _WIn32

#define PKG_MAXMSGS			0xFF	///<报文最大T_SIPTAGMSG消息个数
#define MAXTAGMSGDATASIZE	8168    ///<最大标签值消息数据长度;1400修改而来,兼容1.0版而修改;

///\brief 标签值消息
///
///SIP实时行情系统标签值，变长结构体，size = 40 - 8208
struct T_SIPTAGMSG
{
	char	Code[24];		///<标签名，3段组成的标签名
	T_I64	SeqNum;			///<数据序列号，上游数据源来的非连续递增的序列号，可能一直为0
	T_U32   Filler;			///<无意义，系统使用
	T_U16	MsgType;		///<消息类型，根据这个值确定MsgData的解析格式
	T_U16	MsgDataSize;	///<消息数据大小，指MsgData的字节数，不大于MAXTAGMSGDATASIZE
	T_U8	MsgData[];		///<消息数据
};

/// \brief 通知数据包
///
///TPKG_SIP是用于异步方式通知客户端的数据结构，根据不同的功能码PkgCode，后面的PkgSize和PkgData不同。
struct TPKG_SIP
{
	T_U16 PkgCode;			///<功能码，决定了PkgData的解析格式。
	T_U16 PkgSize;			///<数据包长度,包含头部(PkgCode和PkgSize所占空间字节数)。
	T_U8  PkgData[];		///<数据包数据。
};

///\brief 标签错误码
///
///当客户端提交数据或请求数据时，如果标签有错，使用该结构体提表述错误信息。
struct SIP_TAGERR
{
	char TagCode[24];		///<标签名,0结束字符串
	T_I32 Errcode;			///<错误码
};

///\brief 标签错误码通知数据包
///
///用于表述一组标签错误信息。
struct TPKG_SIP_TAGERR
{
	T_U16 PkgCode;			///<功能码，决定了PkgData的解析格式。
	T_U16 PkgSize;			///<数据包长度,包含头部(PkgCode和PkgSize所占空间字节数)。

	T_U32 TagNum;			///<标签数,小于等于PKG_MAXMSGS
	SIP_TAGERR TagErr[];	///<变长TSI_TAGERR数组,最大PKG_MAXMSGS，即0xFF
};

/// \brief 单状态错误信息通知数据包
///
///用于描述一个单状态错误码信息，包含错误描述。
struct TPKG_SIP_SST
{
	T_U16  PkgCode;				///< 功能码
	T_U16  PkgSize;				///< 报文长度，128
	SIPRET ErrCode;				///< 错误码
	char   Des[120];			///< 错误描述，0结束的ANSI字符串
};

///\brief 订阅标签
///
///客户端订阅标签结构体
struct T_SSCTAG
{
	char sTag[24];///<标签名，0结束的字符串
	T_U32 uSeqNo; ///<起始序列号，增量订阅才有效，0xFFFFFFFF表示从当前订阅
	T_U8  cMode;  ///<订阅模式,SSC_MODE_NEW最新，SSC_MODE_INC增量
	T_I8  cRes;   ///<保留
	T_I16 nErr;   ///<错误码
};//sizeof() = 32

/// \brief 标签消息组报文
///
///传输最大255个连续存放的T_SIPTAGMSG的数据包。用于服务器向客户端推送标签值
struct TPKG_SIP_TAGMSGS
{
	T_U16 PkgCode;				///<功能码，CPKG_WSI等
	T_U16 PkgSize;				///<报文长度
	T_U32 MsgNum;				///<T_SIPTAGMSG消息个数，不大于PKG_MAXMSGS
	T_U8  Bytes[];				///<按字节连续存放的T_SIPTAGMSG消息
};

#define CPKG_LOCAL_ERR			1		///<PkgCode，本地错误,数据包定义TPKG_SIP_SST
#define CPKG_PKGERR				2		///<PkgCode，应用层报文错误,当报文错误，或者服务器收到不认识的功能码报文时，使用这个功能码返回错误信息包,数据包定义TPKG_SIP_SST

///\brief 在线UI服务器信息
///
///详
struct T_ONLINEUISVR
{
	T_I32 connum; ///<当前连接数
	T_U16 wport;  ///<服务端口
	T_I16 nres;   ///<保留
	char svrname[10];///<服务器名
	char wanip[16];  ///<WAN IP地址
	char wantype[4]; ///<网络类型
	char lanip[16];	 ///<局域网IP
};//sizeof(56)

///\brief 证券代码
///
///和关系库中
struct T_SCITEM
{
	char mkcode[10];///<市场代码
	char sccode[18];///<证券代码
	char sctype[10];///<数据类型代码
	char name[26];  ///<证券名称
	T_I32 nautoid;  ///<自动ID
};//sizeof()= 68

struct T_SCITEMEX
{
	char mkcode[10];
	char sccode[18];
	char sctype[10];
	char name[26];
	int  autoid;
	char dtupdate[32];
};

#define SVRCTRL_RESET  193 ///< 0xc1服务器重启

#define PGMSG_TYPE     998  //!<分页消息类型,底层传输使用,定义小于1000,属于系统预置消息类型。

#ifdef ATSIPSVR
	#include "svr2def.h"
#endif

#endif
