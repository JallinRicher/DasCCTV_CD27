#pragma once
#include <string>
#include <vector>
#include <list>

#define NAME_LEN					64
#define FILE_PATH_LEN				256
#define RES_CODE_LEN				1024
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
#define DEFAULT_STR					""
#define DEFAULT_INT					0


/************************************* CCTV 配置文件信息 *************************************/
#define CONFIG_FILE								"DasCCTV.ini"

#define SECTION_GLOBAL							"GLOBAL"
#define CONFIG_KEY_DEFAULT_LAYOUT				"DefaultLayout"

#define SECTION_DCSUSERINFO						"DCSUSERINFO"
#define SECTION_DCRUSERINFO						"DCRUSERINFO"
#define CONFIG_KEY_USERNAME						"UserName"
#define CONFIG_KEY_PASSWORD						"Password"
#define CONFIG_KEY_SERVERIP						"ServerIP"
#define CONFIG_KEY_SERVERPORT					"ServerPort"

#define SECTION_STORAGE							"STORAGE"
#define CONFIG_KEY_DOWNLOADPATH					"DownloadPath"

#define SECTION_LASTCAMERA						"LASTCAMERA"
#define CONFIG_KEY_LASTCAMERA_PREFIX			"LastCamera"
#define CONFIG_KEY_LASTCAMERATYPE_PREFIX		"LastCameraType"

#define SECTION_DISPLAYMODE						"DISPLAYMODE"
#define CONFIG_KEY_MODECOUNT					"ModeCount"
#define CONFIG_KEY_MODENAME_PREFIX				"ModeName"
#define CONFIG_KEY_MODECAMERA_PREFIX			"ModeCamera"



typedef enum
{
	FATAL = 0,
	WARN,
	DEBUG,
	INFO

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
	char UserName[NAME_LEN];
	char Password[PASSWORD_LEN];
	char IPAddress[IPADDR_LEN];
	unsigned int Port;

	UserInfo()
	{
		memset(UserName, 0, sizeof(UserName));
		memset(Password, 0, sizeof(Password));
		memset(IPAddress, 0, sizeof(IPAddress));
		Port = 0;
	}
	
}UserInfo;


typedef struct _TypeDisplayMode_
{
	char ModeName[NAME_LEN];
	char ModeCamera[MAX_DISPLAY_CNT][RES_CODE_LEN];

	_TypeDisplayMode_()
	{
		memset(ModeName, 0, sizeof(ModeName));
		memset(ModeCamera, 0, sizeof(ModeCamera));
	}

}TypeDisplayMode, ModeArray[MAX_DISPLAYMODE_CNT];


typedef struct DisplayMode
{
	unsigned int ModeCount;
	ModeArray _modeArray;

	DisplayMode()
	{
		ModeCount = 0;
	}

}DisplayMode;


typedef struct _TypeGateway_
{
	_TypeGateway_()
	{
		disableEvent = -1;
		maxVod = -1;
	}

	void SetData(int DisableEvent, int MaxVod, const CString& Name, const CString& Title);
	void GetData(int& DisableEvent, int& MaxVod, CString& Name, CString& Title) const;

	int disableEvent;
	int maxVod;
	CString name;
	CString title;

}TypeGateway, * pTypeGateway;


typedef struct _TypeDevice_
{
	void SetData(const CString& Name, const CString& Title, const CString& Url);
	void GetData(CString& Name, CString& Title, CString& Url) const;

	CString name;
	CString title;
	CString url;

}TypeDevice, * pTypeDevice;


typedef struct _TypeCamera_
{
	_TypeCamera_()
	{
		level = -1;
	}

	void SetData(const CString& Addr, const CString& Host, const CString& Name, const CString& Path, const CString& Title);
	void GetData(CString& Addr, CString& Host, CString& Name, CString& Path, CString& Title) const;

	int level;
	CString addr;
	CString host;
	CString name;
	CString path;
	CString title;

}TypeCamera, * pTypeCamera;


typedef struct _TypeMonitor_
{
	void SetData(const CString& Name, const CString& Title);
	void GetData(CString& Name, CString& Title) const;

	CString name;
	CString title;

}TypeMonitor, * pTypeMonitor;


typedef struct _TypeAudio_
{
	_TypeAudio_()
	{
		audioin = -1;
		audioout = -1;
	}

	void SetData(const CString& Addr, int AudioIn, int AudioOut, const CString& HostUrl, const CString& Name, const CString& Title);
	void GetData(CString& Addr, int& AudioIn, int& AudioOut, CString& HostUrl, CString& Name, CString& Title) const;

	CString addr;
	int audioin;
	int audioout;
	CString hostUrl;
	CString name;
	CString title;

}TypeAudio, * pTypeAudio;


void CharToWideChar(LPSTR pChar, ULONG ulCharSize, BOOL bIsUTF8, LPCWSTR pWideChar);
void WideCharToChar(LPCWSTR pWideChar, ULONG ulCharSize, BOOL bIsUTF8, LPSTR pChar);
void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length);
void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length);
void ConvertStringToCtime(char* pcStr, CTime* pTime);