#pragma once
#include <string>
#include <vector>
#include <list>

#define NAME_LEN					64
#define FILE_PATH_LEN				256
#define RES_CODE_LEN				256
#define MAX_COMBO_ITEM_CNT			128
#define MAX_DISPLAY_CNT				16
#define MAX_DISPLAYMODE_CNT			32
#define MAINDIALOG_WIDTH			1920
#define MAINDIALOG_HEIGHT			1080
#define DISPLAY_INTERVAL			5
#define FILE_PATH_LEN				256
#define IPADDR_LEN					64
#define PASSWORD_LEN				64

#define DEFAULT_STR_LEN				256
#define DEFAULT_STR					L""
#define DEFAULT_INT					0


/************************************* CCTV 配置文件信息 *************************************/
#define CONFIG_FILE								L"DasCCTV.ini"

#define SECTION_GLOBAL							L"GLOBAL"
#define CONFIG_KEY_DEFAULT_LAYOUT				L"DefaultLayout"

#define SECTION_DCSUSERINFO						L"DCSUSERINFO"
#define SECTION_DCRUSERINFO						L"DCRUSERINFO"
#define CONFIG_KEY_USERNAME						L"UserName"
#define CONFIG_KEY_PASSWORD						L"Password"
#define CONFIG_KEY_SERVERIP						L"ServerIP"
#define CONFIG_KEY_SERVERPORT					L"ServerPort"

#define SECTION_STORAGE							L"STORAGE"
#define CONFIG_KEY_DOWNLOADPATH					L"DownloadPath"

#define SECTION_LASTCAMERA						L"LASTCAMERA"
#define CONFIG_KEY_LASTCAMERA_PREFIX			L"LastCamera"
#define CONFIG_KEY_LASTCAMERATYPE_PREFIX		L"LastCameraType"

#define SECTION_DISPLAYMODE						L"DISPLAYMODE"
#define CONFIG_KEY_MODECOUNT					L"ModeCount"
#define CONFIG_KEY_MODENAME_PREFIX				L"ModeName"
#define CONFIG_KEY_MODECAMERA_PREFIX			L"ModeCamera"



typedef enum
{
	FATAL = 0,
	WARN,
	DEBUG,
	INFO,
	BLANK
}LOGLEVEL;


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
	wchar_t DeviceResCode[RES_CODE_LEN];		// 设备资源编码
	wchar_t DeviceName[NAME_LEN];				// 设备名
	long DeviceID;								// 设备编号
	int DeviceType;								// 设备类型
	int DeviceSubType;							// 设备子类型
	int DeviceStatus;							// 设备状态
	long RegionID;								// 区域编号
	wchar_t RegionResCode[RES_CODE_LEN];		// 区域资源编码

	DisplayDeviceInfo()
	{
		memset(DeviceResCode, 0, sizeof(DeviceResCode));
		memset(DeviceName, 0, sizeof(DeviceName));
		DeviceID = INVALID_VALUE;
		DeviceType = INVALID_VALUE;
		DeviceSubType = INVALID_VALUE;
		DeviceStatus = INVALID_VALUE;
		RegionID = INVALID_VALUE;
		memset(RegionResCode, 0, sizeof(RegionResCode));
	}
	
}DisplayDeviceInfo;


typedef struct UserInfo
{
	wchar_t UserName[NAME_LEN];
	wchar_t Password[PASSWORD_LEN];
	wchar_t IPAddress[IPADDR_LEN];
	unsigned int Port;

	UserInfo()
	{
		memset(UserName, 0, sizeof(UserName));
		memset(Password, 0, sizeof(Password));
		memset(IPAddress, 0, sizeof(IPAddress));
		Port = 0;
	}
	
}UserInfo;


typedef struct _mode
{
	wchar_t ModeName[NAME_LEN];
	wchar_t ModeCamera[MAX_DISPLAY_CNT][RES_CODE_LEN];

	_mode()
	{
		memset(ModeName, 0, sizeof(ModeName));
		memset(ModeCamera, 0, sizeof(ModeCamera));
	}

}_mode, ModeArray[MAX_DISPLAYMODE_CNT];


typedef struct DisplayMode
{
	unsigned int ModeCount;
	ModeArray _modeArray;

	DisplayMode()
	{
		ModeCount = 0;
	}

}DisplayMode;


void CharToWChar(const char* Source, wchar_t* Destination)
{
	int _tempLen = MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), nullptr, 0);
	TCHAR* _tempWchar = new wchar_t[_tempLen + 1];
	memset(_tempWchar, 0, 2 * _tempLen + 2);
	MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), _tempWchar, _tempLen);
	wcsncpy_s(Destination, sizeof(Destination), _tempWchar, sizeof(_tempWchar));

	delete[] _tempWchar;
}