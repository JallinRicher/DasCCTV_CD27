#include "pch.h"
#include "CallBack.h"

BOOL CWALK_SDK_CALLBACK CameraListObject(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo)
{
	CallbackObj* obj = static_cast<CallbackObj*>(UserParam);
	BitmapComboBox* cameraComboBox = static_cast<BitmapComboBox*>(obj->UserParam);
	if (obj->Count <= 0)
	{
		return FALSE;
	}
	int index = cameraComboBox->AddString(ObjName);
	cameraComboBox->AddString(ObjInfo);
	// cameraComboBox->m_IndexToObjInfo[index] = ObjInfo;
	obj->Count--;
	return TRUE;
}