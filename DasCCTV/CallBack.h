#pragma once
#include "MainDialog.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "cwalk_playsdk.h"
#include "JSDCCTV.h"

class CallBackOpt;

BOOL CWALK_SDK_CALLBACK ListObject_CallBack(void* UserParam, CWALK_NET_HD UserHD, CWALKNetObjectType ObjType, const TCHAR* ObjName, const TCHAR* ObjInfo);