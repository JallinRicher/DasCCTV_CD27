#pragma once
#include "MainDialog.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "cwalk_playsdk.h"
#include "JSDCCTV.h"


class _callback_base
{
public:
	virtual int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) = 0;
	virtual ~_callback_base() {};
};


class CallBackOpt
{
public:
	CallBackOpt(CWALKNetObjectType ObjType);
	~CallBackOpt();
	_callback_base* m_callback_base;
};


class CameraCallBack : public _callback_base
{
public:
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};


class GatewayCallBack : public _callback_base
{
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};



BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo);