#ifndef _WORKH_TEST
# define _WORKH_TEST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sipv2_i.h"
#include "sipui2_i.h"
#include "tshmarket.h"
#include "tszmarket.h"

//#define WIN32_LEAN_AND_MEAN

#pragma warning(disable : 4996)
#pragma warning(disable : 4819)

#define TWONODE 2

const char* GetErrInfo(T_I32 icode) ;
void _cdecl DoMsg(T_SIPTAGMSG* ptag, void* pParam);
void __stdcall  _OnNotifyMsg(TPKG_SIP* pPkg, CBPARAM pParam) ;
#endif
