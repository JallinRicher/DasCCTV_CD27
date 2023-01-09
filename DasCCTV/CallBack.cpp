#include "pch.h"
#include "CallBack.h"

BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	MainDialog* MainDlg = (MainDialog*)UserParam;
	char ValueBuf[DEFAULT_STR_LEN] = { 0 };
	int RealLen = 0;

	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY: break;
	case CWALKNET_TYPE_DEVICE: break;
	case CWALKNET_TYPE_CAMERA: 
		JSDCCTV::InfoParseKeyValue(ObjInfo, L"name", ValueBuf, DEFAULT_STR_LEN, &RealLen);
		MainDlg->AddOneCamera("", "", 0, 0);
		memset(ValueBuf, 0, DEFAULT_STR_LEN);

		JSDCCTV::InfoParseKeyValue(ObjInfo, L"url", ValueBuf, DEFAULT_STR_LEN, &RealLen);

		memset(ValueBuf, 0, DEFAULT_STR_LEN);
		
		break;
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
