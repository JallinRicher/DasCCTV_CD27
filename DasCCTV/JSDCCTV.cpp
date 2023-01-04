#include "pch.h"
#include "JSDCCTV.h"

JSDCCTV::JSDCCTV(UserInfo userInfo) : m_UserInfo(userInfo)
{
	m_IsInitPlay = false;
	m_IsInitFile = false;
	m_IsInitNet = false;
	m_IsLogin = false;

	m_LoginHandle = nullptr;
}


void JSDCCTV::CharToWChar(const char* Source, wchar_t* Destination)
{
	int _tempLen = MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), nullptr, 0);
	TCHAR* _tempWchar = new wchar_t[_tempLen + 1];
	memset(_tempWchar, 0, 2 * _tempLen + 2);
	MultiByteToWideChar(CP_ACP, 0, Source, strlen(Source), _tempWchar, _tempLen);
	wcsncpy_s(Destination, sizeof(Destination), _tempWchar, sizeof(_tempWchar));

	delete[] _tempWchar;
}


void JSDCCTV::InitPlaySDK()
{
	wchar_t InfoBuf[INFOBUFFER_SIZE] = { 0 };
	int RealLen = 0;
	CWALK_PLAY_Init();
	m_IsInitPlay = true;
	ErrorNum ret = CWALK_PLAY_GetSDK_Version(InfoBuf, sizeof(InfoBuf), &RealLen);
	if (ret == CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::InitFileSDK()
{
	wchar_t InfoBuf[INFOBUFFER_SIZE] = { 0 };
	int RealLen = 0;
	ErrorNum ret = CWALK_FILE_Init();
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	m_IsInitFile = true;
	memset(InfoBuf, 0, sizeof(InfoBuf));
	ret = CWALK_FILE_GetSDK_Version(InfoBuf, sizeof(InfoBuf), &RealLen);
	if (ret == CWALKSDK_OK)
	{
		// LOG
	}

	return true;
}


bool JSDCCTV::InitNetSDK()
{
	wchar_t InfoBuf[INFOBUFFER_SIZE] = { 0 };
	int RealLen = 0;
	ErrorNum ret = CWALK_NET102_Init(CWALKCharacterEncoding_UTF8_Later102);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	m_IsInitNet = true;
	memset(InfoBuf, 0, sizeof(InfoBuf));
	ret = CWALK_NET_GetSDK_Version(InfoBuf, sizeof(InfoBuf), &RealLen);
	if (ret == CWALKSDK_OK)
	{
		// LOG
	}

	return true;
}


bool JSDCCTV::InitSDK()
{
	InitPlaySDK();

	if (!InitFileSDK())
		return false;

	if (!InitNetSDK())
		return false;

	// LOG
	return true;
}


bool JSDCCTV::Login()
{
	TCHAR IPAddress[IPADDR_LEN] = { 0 };
	TCHAR UserName[NAME_LEN] = { 0 };
	TCHAR Password[PASSWORD_LEN] = { 0 };
	CharToWChar(m_UserInfo.IPAddress, IPAddress);
	CharToWChar(m_UserInfo.UserName, UserName);
	CharToWChar(m_UserInfo.Password, Password);

	ErrorNum ret = CWALK_NET_Login(&m_LoginHandle, IPAddress, m_UserInfo.Port, UserName, Password);
	if (ret != CWALKSDK_OK || m_LoginHandle == nullptr)
	{
		// LOG
		return false;
	}

	m_IsLogin = true;
	// LOG
	return true;
}


void JSDCCTV::Logout()
{
	if (m_IsLogin && m_LoginHandle)
	{
		ErrorNum ret = CWALK_NET_Logout(m_LoginHandle);
		if (ret != CWALKSDK_OK)
		{
			// LOG
		}

		m_LoginHandle = nullptr;
		m_IsLogin = false;
	}

	// LOG
}


void JSDCCTV::ReleaseSDK()
{
	CWALK_NET_Cleanup();
	CWALK_FILE_Cleanup();
	CWALK_PLAY_Cleanup();
}


void JSDCCTV::GetDecodeMode(CWALK_PLAY_HD PlayHD, int* DecodeMode, int* HwType)
{
	ErrorNum ret = CWALK_PLAY_GetDecodeMode(PlayHD, DecodeMode, HwType);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_SetDecodeStateCallBack(PlayHD, FnDecodeState, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::SetAudioCallBack(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_SetAudioCallback(PlayHD, FnOnAudio, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam)
{
	ErrorNum ret = CWALK_NET_SetTransferRobbedCallBack(m_LoginHandle, FnRobbed, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreatePlayerEx(PlayHD, Hwnd, StreamType, DecodeMode, HwType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::ReleasePlayer(CWALK_PLAY_HD PlayHD)
{
	ErrorNum ret = CWALK_PLAY_ReleasePlayer(PlayHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::StartVideoStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartStream(m_LoginHandle, StreamHD, AvPath, FnData, FnRobbed, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::StreamRequestIFrame(CWALK_NET_HD StreamHD)
{
	ErrorNum ret = CWALK_NET_StreamRequestIFrame(StreamHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::StopVideoStream(CWALK_NET_HD StreamHD)
{
	ErrorNum ret = CWALK_NET_StopStream(StreamHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam)
{
	ErrorNum ret = CWALK_NET_QueryRecordInfo(m_LoginHandle, AvPath, VodType, BeginTime, EndTime, FnOnListSegment, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, CallBack_OnStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartPlaybackStream(m_LoginHandle, StreamHD, AvPath, VodType, BeginTime, EndTime, FnData, FnRobbed, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam)
{
	ErrorNum ret = CWALK_PLAY_PlayControl(PlayHD, Cmd, InParam, OutParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD)
{
	ErrorNum ret = CWALK_FILE_OpenWritbaleFile(FileName, WriteHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos)
{
	ErrorNum ret = CWALK_NET_GetPlaybackStreamPos(StreamHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::CloseWritableFile(CWALK_FILE_HD WriteHD)
{
	ErrorNum ret = CWALK_FILE_CloseWritableFile(WriteHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName)
{
	ErrorNum ret = CWALK_PLAY_CapturePicture(PlayHD, FileName);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}
