#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include "cwalk_playsdk.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"

class DisplayDialog;
class JSDCCTV;

#define NAME_LEN					64
#define FILE_PATH_LEN				128
#define RES_CODE_LEN				128
#define MAX_COMBO_ITEM_CNT			128
#define MAX_DISPLAY_CNT				16
#define MAX_DISPLAYMODE_CNT			32
#define MAINDIALOG_WIDTH			1920
#define MAINDIALOG_HEIGHT			1080
#define DISPLAY_INTERVAL			6
#define IPADDR_LEN					64
#define PASSWORD_LEN				64
#define CAMERA_CODE_LEN				128

#define DEFAULT_STR_LEN				128
#define DEFAULT_STR					_T("")
#define DEFAULT_INT					0


/************************************* CCTV 配置文件信息 *************************************/
#define CONFIG_FILE								_T("DasCCTV.ini")

#define SECTION_GLOBAL							_T("GLOBAL")
#define CONFIG_KEY_DEFAULT_LAYOUT				_T("DefaultLayout")

#define SECTION_DCSUSERINFO						_T("DCSUSERINFO")
#define SECTION_DCRUSERINFO						_T("DCRUSERINFO")
#define CONFIG_KEY_USERNAME						_T("UserName")
#define CONFIG_KEY_PASSWORD						_T("Password")
#define CONFIG_KEY_SERVERIP						_T("ServerIP")
#define CONFIG_KEY_SERVERPORT					_T("ServerPort")

#define SECTION_STORAGE							_T("STORAGE")
#define CONFIG_KEY_DOWNLOADPATH					_T("DownloadPath")

#define SECTION_LASTCAMERA						_T("LASTCAMERA")
#define CONFIG_KEY_LASTCAMERA_PREFIX			_T("LastCamera")
#define CONFIG_KEY_LASTCAMERATYPE_PREFIX		_T("LastCameraType")

#define SECTION_DISPLAYMODE						_T("DISPLAYMODE")
#define CONFIG_KEY_MODECOUNT					_T("ModeCount")
#define CONFIG_KEY_MODENAME_PREFIX				_T("ModeName")
#define CONFIG_KEY_MODECAMERA_PREFIX			_T("ModeCamera")
#define CONFIG_KEY_CAMERATYPE_PREFIX			_T("CameraType")



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
	IS_BLANK = 0,
	IS_LIVING,
	IS_SWITCHING,
	IS_RECORDING,
	IS_DOWNLOADING,
	IS_SNATCHING

}DisplayState;


typedef enum
{
	FULLSCREEN = 0,
	ONE_DIALOG = 1,
	FOUR_DIALOG = 4,
	NINE_DIALOG = 9,
	SIXTEEN_DIALOG = 16

}LayoutState;


// 播放信息
typedef struct DisplayDeviceInfo
{
	TCHAR DeviceResCode[RES_CODE_LEN];			// 设备资源编码
	TCHAR DeviceName[NAME_LEN];					// 设备名
	long DeviceID;								// 设备编号
	int DeviceType;								// 设备类型
	int DeviceSubType;							// 设备子类型
	int DeviceStatus;							// 设备状态
	long RegionID;								// 区域编号
	TCHAR RegionResCode[RES_CODE_LEN];		// 区域资源编码

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
	int CameraNumber;
	CString ModeName;
	CString ModeCamera[MAX_DISPLAY_CNT];			// AvPath
	CString CameraType[MAX_DISPLAY_CNT];
	
	_TypeDisplayMode_()
	{
		CameraNumber = 0;
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

}TypeGateway, *pTypeGateway;


typedef struct _TypeDevice_
{
	void SetData(const CString& Name, const CString& Title, const CString& Url);
	void GetData(CString& Name, CString& Title, CString& Url) const;

	CString name;
	CString title;
	CString url;

}TypeDevice, *pTypeDevice;


typedef struct _TypeCamera_
{
	void SetData(const CString& Type, const CString& Id, const CString& Name, const CString& OrgId, const CString& BelongId,
				 const CString& NodeId, const CString& RtspUrl, const CString& PtzEnable)
	{
		type = Type; id = Id; name = Name; orgId = OrgId; belongId = BelongId; nodeId = NodeId; rtspUrl = RtspUrl; ptzEnable = PtzEnable;
	}
	void GetData(CString& Type, CString& Id, CString& Name, CString& OrgId, CString& BelongId, CString& NodeId,
				 CString& RtspUrl, CString& PtzEnable) const
	{
		Type = type; Id = id; Name = name; OrgId = orgId; BelongId = belongId; NodeId = nodeId; RtspUrl = rtspUrl; PtzEnable = ptzEnable;
	}

	CString type;
	CString id;
	CString name;
	CString orgId;
	CString belongId;
	CString nodeId;
	CString rtspUrl;
	CString ptzEnable;

}TypeCamera, *pTypeCamera;


typedef struct _TypeMonitor_
{
	void SetData(const CString& Name, const CString& Title);
	void GetData(CString& Name, CString& Title) const;

	CString name;
	CString title;

}TypeMonitor, *pTypeMonitor;


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

}TypeAudio, *pTypeAudio;


typedef struct _OSD
{
	_OSD()
	{
		hd = NULL;
		type = (CWALKPLayOSDType)-1;
	}
	CWALK_PLAY_HD hd;
	CWALKPLayOSDType type;
}OSD;


typedef struct _SaveFile
{
	_SaveFile()
	{
#ifdef WATERMARK
		transHD = NULL;
#endif
		writeHd = NULL;
		playbackHd = NULL;
		extractorHd = NULL;
		file = "";
		hwnd = NULL;
		isAVI = FALSE;
		encoding = FALSE;
	}

	CWALK_FILE_HD writeHd;
	CWALK_FILE_HD extractorHd;
	CWALK_NET_HD playbackHd;
	BOOL isAVI;
	BOOL encoding;
	CString file;

	HWND hwnd;
#ifdef WATERMARK
	//测试转码+水印
	CWALK_STREAM_TRANS_HD transHD;
#endif
}SaveFile, *pSaveFile;


typedef struct _RealStream
{
	_RealStream()
	{
		realEventHd = NULL;
		realTransferHd = NULL;
		realLiveHd = NULL;
		realPlayerHd = NULL;
		realZoomHd = NULL;
		decodInfohd = NULL;

		isSeverRecoding = FALSE;
		isLocalRecoding = FALSE;

		isStream = FALSE;

		hwnd = NULL;
		hwndZoom = NULL;
		simpleName = "";
		name = "";
		title = "";
		path = "";
		level = -1;
		target = "";

		addr = "";
		host = "";

		hItem = NULL;
		isHWDeocder = FALSE;
		isshow = false;
		isHwDec = FALSE;
	}

	void ClearAllContent();
	CWALK_NET_HD realEventHd;
	CWALK_NET_HD realTransferHd;
	CWALK_NET_HD realLiveHd;
	CWALK_PLAY_HD realPlayerHd;
	CWALK_PLAY_HD realZoomHd;
	BOOL isSeverRecoding;
	BOOL isLocalRecoding;
	BOOL isHWDeocder;

	HWND hwnd;
	HWND hwndZoom;
	CString simpleName;
	CString name;
	CString title;
	CString path;
	CString strOrg;
	CString strOrgPath;
	INT level;
	CString target;

	CString addr;
	CString host;
	INT avType;								//判断是否配置云台

	INT isRecording;
	INT motionDetected;
	INT status;
	INT videoLost;
	BOOL isStream;
	UINT64 beginTime;

	HTREEITEM hItem;
	std::vector<OSD> osdHd;
	SaveFile saveFile;

	std::map<INT, BOOL> osd_id_status;

	CWALK_PLAY_HD decodInfohd;				//保存osdhd
	bool isshow;							//判断是否显示
	BOOL isHwDec;
}RealStream, *pRealStream;


typedef struct _RealPlay
{
	_RealPlay()
	{
		m_JsdCCTV = nullptr;
		m_PlayHD = nullptr;
		m_StreamHD = nullptr;
	}

	JSDCCTV* m_JsdCCTV;
	CWALK_PLAY_HD m_PlayHD;
	CWALK_NET_HD m_StreamHD;
	
}RealPlay, *pRealPlay;


typedef struct _CurOpenSoundDialog
{
	DisplayDialog* m_CurOpenSoundDialog;
	CWALKPLayPcmFrame m_PcmFrame;

}OpenSoundDialog;


typedef struct _Organization_
{
	CString id;
	CString parentid;
	CString name;
	CString administrativeDivision;
	CString description;

}TypeOrg, TypeStation, TypeArea;


typedef struct _Camera_Callback_
{
	CString m_CurSelAreaId;
	std::vector<TypeCamera> m_vecCameras;

}TypeCameraCallback;


typedef struct _DspCtlDlgAttibute
{
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;

}DspCtlDlgAttibute;


void CharToWideChar(LPSTR pChar, ULONG ulCharSize, BOOL bIsUTF8, LPCWSTR pWideChar);
void WideCharToChar(LPCWSTR pWideChar, ULONG ulCharSize, BOOL bIsUTF8, LPSTR pChar);
void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length);
void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length);
void ConvertStringToCtime(char* pcStr, CTime* pTime);