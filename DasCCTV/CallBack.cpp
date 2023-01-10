#include "pch.h"
#include "CallBack.h"

CallBackOpt::CallBackOpt(CWALKNetObjectType ObjType) : m_callback_base(nullptr)
{
	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY: break;
	case CWALKNET_TYPE_DEVICE: break;
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
	wchar_t NameBuf[RES_CODE_LEN] = { 0 };
	wchar_t TitleBuf[RES_CODE_LEN] = { 0 };
	MainDialog* MainDlg = (MainDialog*)UserParam;

	JSDCCTV::InfoParseKeyValue(ObjInfo, L"name", NameBuf, sizeof(NameBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"title", TitleBuf, sizeof(TitleBuf), nullptr);

	TypeGateway Gateway;
	Gateway.SetData(DisableEvent, MaxVod, NameBuf, TitleBuf);
	MainDlg->m_StationComboBox.AddOneRow(NameBuf);
	MainDlg->m_StationComboBox.AddOneGateway(Gateway);

	return CWALKSDK_OK;
}


int DeviceCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	wchar_t NameBuf[RES_CODE_LEN] = { 0 };
	wchar_t TitleBuf[RES_CODE_LEN] = { 0 };
	wchar_t UrlBuf[RES_CODE_LEN] = { 0 };

	JSDCCTV::InfoParseKeyValue(ObjInfo, L"name", NameBuf, sizeof(NameBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"title", TitleBuf, sizeof(TitleBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"url", UrlBuf, sizeof(UrlBuf), nullptr);

	TypeDevice Device;
	Device.SetData(NameBuf, TitleBuf, UrlBuf);

}


int CameraCallBack::Parse(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	int Level = -1;
	wchar_t NameBuf[RES_CODE_LEN] = { 0 };
	wchar_t AddrBuf[RES_CODE_LEN] = { 0 };
	wchar_t PathBuf[RES_CODE_LEN] = { 0 };
	wchar_t TitleBuf[RES_CODE_LEN] = { 0 };
	wchar_t HostBuf[RES_CODE_LEN] = { 0 };
	MainDialog* MainDlg = (MainDialog*)UserParam;
	
	JSDCCTV::InfoParseIntKeyValue(ObjInfo, L"level", &Level);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"name", NameBuf, sizeof(NameBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"addr", AddrBuf, sizeof(AddrBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"path", PathBuf, sizeof(PathBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"title", TitleBuf, sizeof(TitleBuf), nullptr);
	JSDCCTV::InfoParseKeyValue(ObjInfo, L"host", HostBuf, sizeof(HostBuf), nullptr);

	TypeCamera camera;
	camera.SetData(AddrBuf, HostBuf, NameBuf, PathBuf, TitleBuf);
	MainDlg->m_CameraComboBox.AddOneRow(NameBuf);
	MainDlg->m_CameraComboBox.AddOneCamera(camera);

	return CWALKSDK_OK;
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
