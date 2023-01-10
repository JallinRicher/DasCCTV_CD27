#include "pch.h"
#include "CallBack.h"

CallBackOpt::CallBackOpt(CWALKNetObjectType ObjType)
{
	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY: break;
	case CWALKNET_TYPE_DEVICE: break;
	case CWALKNET_TYPE_CAMERA: 
	{
		m_callback_base = (_callback_base*)new CameraCallBack;
		break;
	}
	case CWALKNET_TYPE_MONITOR: break;
	case CWALKNET_TYPE_AUDIO: break;
	case CWALKNET_TYPE_TRUNKIN: break;
	case CWALKNET_TYPE_TRUNKOUT: break;
	case CWALKNET_TYPE_ALARMIN: break;
	case CWALKNET_TYPE_ALARMOUT: break;
	default: 
	{
		m_callback_base = nullptr;
		break;
	}
	}
}


int CameraCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	int Level = -1;
	char NameBuf[RES_CODE_LEN] = { 0 };
	char AddrBuf[RES_CODE_LEN] = { 0 };
	char PathBuf[RES_CODE_LEN] = { 0 };
	char TitleBuf[RES_CODE_LEN] = { 0 };
	char HostBuf[RES_CODE_LEN] = { 0 };
	MainDialog* MainDlg = (MainDialog*)UserParam;
	
	JSDCCTV::InfoParseIntKeyValue(ObjInfo, L"level", &Level);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"name", NameBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"addr", AddrBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"path", PathBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"title", TitleBuf, RES_CODE_LEN, nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"host", HostBuf, RES_CODE_LEN, nullptr);
	UNUSED(MainDlg);


	return CWALKSDK_OK;
}


int GatewayCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{

}


BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	CallBackOpt callbackOpt(ObjType);
	return callbackOpt.m_callback_base->Parse(UserParam, UserHD, ObjType, ObjName, ObjInfo);


	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY: break;
	case CWALKNET_TYPE_DEVICE: break;
	case CWALKNET_TYPE_CAMERA: break;
	case CWALKNET_TYPE_MONITOR: break;
	case CWALKNET_TYPE_AUDIO: break;
	case CWALKNET_TYPE_TRUNKIN: break;
	case CWALKNET_TYPE_TRUNKOUT: break;
	case CWALKNET_TYPE_ALARMIN: break;
	case CWALKNET_TYPE_ALARMOUT: break;
	default: break;
	}

	return 0;
}
