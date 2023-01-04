#pragma once
#include <string>

#define NAME_LEN			64
#define RES_CODE_LEN		64
#define MAX_COMBO_ITEM_CNT	128
#define MAINDIALOG_WIDTH	1920
#define MAINDIALOG_HEIGHT	1080
#define DISPLAY_INTERVAL	5
#define MAX_DISPLAY_CNT		16
#define FILE_PATH_LEN		256
#define IPADDR_LEN			64
#define PASSWORD_LEN		64


enum { INVALID_VALUE = -1 };


typedef enum
{
	IS_LIVING = 0,
	IS_BLANK,
	IS_SWITCHING,
	IS_RECORDING,
	IS_DOWNLOADING,
	IS_SNATCHING
}DisplayState;


typedef enum
{
	FULLSCREEN = 1,
	FOUR_DIALOG = 4,
	NINE_DIALOG = 9,
	SIXTEEN_DIALOG = 16
}LayoutState;


// 播放信息
typedef struct DisplayDeviceInfo
{
	char DeviceResCode[RES_CODE_LEN];		// 设备资源编码
	char DeviceName[NAME_LEN];				// 设备名
	long DeviceID;							// 设备编号
	int DeviceType;							// 设备类型
	int DeviceSubType;						// 设备子类型
	int DeviceStatus;						// 设备状态
	long RegionID;							// 区域编号
	char RegionResCode[RES_CODE_LEN];		// 区域资源编码
#ifdef MULTI_SUBWAY_ROUTE
	int Route;
#endif

	DisplayDeviceInfo()
	{
		memset(DeviceResCode, 0, RES_CODE_LEN);
		memset(DeviceName, 0, NAME_LEN);
		DeviceID = INVALID_VALUE;
		DeviceType = INVALID_VALUE;
		DeviceSubType = INVALID_VALUE;
		DeviceStatus = INVALID_VALUE;
		RegionID = INVALID_VALUE;
		memset(RegionResCode, 0, RES_CODE_LEN);
#ifdef MULTI_SUBWAY_ROUTE
		Route = INVALID_VALUE;
#endif
	}
	
}DisplayDeviceInfo;


typedef struct UserInfo
{
	char UserName[NAME_LEN];
	char Password[PASSWORD_LEN];
	char IPAddress[IPADDR_LEN];
	int Port;
	bool IsLogin;
#ifdef MULTI_SUBWAY_ROUTE
	int Route;
#endif

	UserInfo()
	{
		memset(UserName, 0, NAME_LEN);
		memset(Password, 0, PASSWORD_LEN);
		memset(IPAddress, 0, IPADDR_LEN);
		Port = -1;
		IsLogin = false;
#ifdef MULTI_SUBWAY_ROUTE
		Route = -1;
#endif
	}
	
}UserInfo;


void CharToWChar(const char* Source, wchar_t* Destination)
{
	int _tempLen = MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), nullptr, 0);
	TCHAR* _tempWchar = new wchar_t[_tempLen + 1];
	memset(_tempWchar, 0, 2 * _tempLen + 2);
	MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), _tempWchar, _tempLen);
	wcsncpy_s(Destination, sizeof(Destination), _tempWchar, sizeof(_tempWchar));

	delete[] _tempWchar;
}