#pragma once
#include "MainDialog.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "cwalk_playsdk.h"
#include "JSDCCTV.h"

typedef struct sCallbackObj
{
	int		Count;
	void*	UserParam;

}CallbackObj;

BOOL CWALK_SDK_CALLBACK CameraListObject(void* userParam, CWALK_NET_HD userHD, CWALKNetObjectType objType, const TCHAR* objName, const TCHAR* objInfo);
