#include "pch.h"
#include "CallBack.h"

CallBackOpt::CallBackOpt(CWALKNetObjectType ObjType) : m_callback_base(nullptr)
{
	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY:
		m_callback_base = (_callback_base*)new GatewayCallBack;
		break;
	case CWALKNET_TYPE_DEVICE:
		m_callback_base = (_callback_base*)new DeviceCallBack;
		break;
	case CWALKNET_TYPE_CAMERA:
		m_callback_base = (_callback_base*)new CameraCallBack;
		break;
	case CWALKNET_TYPE_MONITOR: break;
	case CWALKNET_TYPE_AUDIO: break;
	case CWALKNET_TYPE_TRUNKIN: break;
	case CWALKNET_TYPE_TRUNKOUT: break;
	case CWALKNET_TYPE_ALARMIN: break;
	case CWALKNET_TYPE_ALARMOUT: break;
	default: 
		m_callback_base = nullptr;
		break;
	}
}


CallBackOpt::~CallBackOpt()
{
	if (m_callback_base)
	{
		delete m_callback_base;
		m_callback_base = nullptr;
	}
}


int GatewayCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	int MaxVod = -1;
	int DisableEvent = -1;
	char NameBuf[RES_CODE_LEN] = { 0 };
	char TitleBuf[RES_CODE_LEN] = { 0 };
	
	JSDCCTV::InfoParseKeyValue(ObjInfo, "name", NameBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, "title", TitleBuf, RES_CODE_LEN, nullptr);
	
	TypeGateway Gateway;
	Gateway.SetData(DisableEvent, MaxVod, NameBuf, TitleBuf);
	((std::vector<TypeGateway>*)UserParam)->push_back(Gateway);

	return CWALKSDK_OK;
}


int DeviceCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	char NameBuf[RES_CODE_LEN] = { 0 };
	char TitleBuf[RES_CODE_LEN] = { 0 };
	char UrlBuf[RES_CODE_LEN] = { 0 };

	JSDCCTV::InfoParseKeyValue(ObjInfo, "name", NameBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, "title", TitleBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, "url", UrlBuf, RES_CODE_LEN, nullptr);

	TypeDevice Device;
	Device.SetData(NameBuf, TitleBuf, UrlBuf);
	((std::vector<TypeDevice>*)UserParam)->push_back(Device);

	return CWALKSDK_OK;
}


int CameraCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	char ParentIdBuf[RES_CODE_LEN] = { 0 };
	char IdBuf[RES_CODE_LEN] = { 0 };
	char NameBuf[RES_CODE_LEN] = { 0 };
	char BelongIdBuf[RES_CODE_LEN] = { 0 };
	char NodeIdBuf[RES_CODE_LEN] = { 0 };
	char RtspUrlBuf[RES_CODE_LEN] = { 0 };
	char PtzEnableBuf[RES_CODE_LEN] = { 0 };
	char TypeBuf[RES_CODE_LEN] = { 0 };
	TypeCameraCallback* stCameraCallback = (TypeCameraCallback*)UserParam;
	CString ParentId = stCameraCallback->m_CurSelAreaId;
	
	JSDCCTV::InfoParseKeyValue(ObjInfo, "orgId", ParentIdBuf, RES_CODE_LEN, nullptr);
	if (ParentId == ParentIdBuf)
	{
		JSDCCTV::InfoParseKeyValue(ObjInfo, "id", IdBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "name", NameBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "belongId", BelongIdBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "nodeId", NodeIdBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "rtspUrl", RtspUrlBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "ptzEnable", PtzEnableBuf, RES_CODE_LEN, nullptr);
		JSDCCTV::InfoParseKeyValue(ObjInfo, "type", TypeBuf, RES_CODE_LEN, nullptr);

		TypeCamera camera;
		camera.SetData(TypeBuf, IdBuf, NameBuf, ParentIdBuf, BelongIdBuf, NodeIdBuf, RtspUrlBuf, PtzEnableBuf);
	}

	return CWALKSDK_OK;
}


int MonitorCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	char NameBuf[RES_CODE_LEN] = { 0 };
	char TitleBuf[RES_CODE_LEN] = { 0 };

	JSDCCTV::InfoParseKeyValue(ObjInfo, "name", NameBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, "title", TitleBuf, RES_CODE_LEN, nullptr);

	TypeMonitor monitor;
	monitor.SetData(NameBuf, TitleBuf);
	((std::vector<TypeMonitor>*)UserParam)->push_back(monitor);

	return CWALKSDK_OK;
}





BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	CallBackOpt callbackOpt(ObjType);
	return callbackOpt.m_callback_base->Parse(UserParam, UserHD, ObjType, ObjName, ObjInfo);

	return CWALKSDK_OK;
}


void CWALK_SDK_CALLBACK StreamData_CallBack(void* UserParam, CWALK_NET_HD StreamHD, const void* Data, int DataLen)
{
	RealPlay* _realPlay = (pRealPlay)UserParam;
	if (!_realPlay->m_JsdCCTV->InputData(_realPlay->m_PlayHD, Data, DataLen))
	{
		// LOG ¡ª¡ª ÏÔÊ¾ÔÚÆÁÄ»ÉÏ
	}
}


void CWALK_SDK_CALLBACK VideoDecodeData_CallBack(CWALK_PLAY_HD PlayHD, const void* Buf, int len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
{

}


void CWALK_SDK_CALLBACK AudioDecodeData_CallBack(CWALK_PLAY_HD PlayHD, CWALKPLayPcmFrame* PcmFrame, void* UserParma)
{
	
}
