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


class GatewayCallBack : public _callback_base
{
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};


class DeviceCallBack : public _callback_base
{
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};


class CameraCallBack : public _callback_base
{
public:
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};


class MonitorCallBack : public _callback_base
{
public:
	int Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo) override;
};




BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo);
void CWALK_SDK_CALLBACK StreamData_CallBack(void* UserParam, CWALK_NET_HD StreamHD, const void* Data, int DataLen);
void CWALK_SDK_CALLBACK VideoDecodeData_CallBack(CWALK_PLAY_HD PlayHD, const void* Buf, int len, const CWALKPLayFrameInfo* FInfo, void* UserParam);
void CWALK_SDK_CALLBACK AudioDecodeData_CallBack(CWALK_PLAY_HD PlayHD, CWALKPLayPcmFrame* PcmFrame, void* UserParma);
