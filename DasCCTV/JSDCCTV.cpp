#include "pch.h"
#include "JSDCCTV.h"

JSDCCTV::JSDCCTV(UserInfo DCSUserInfo) : m_DCSUserInfo(DCSUserInfo)
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
		InsertLog(WARN, "CWALK_PLAY_GetSDK_Version failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::InitFileSDK()
{
	wchar_t InfoBuf[INFOBUFFER_SIZE] = { 0 };
	int RealLen = 0;
	ErrorNum ret = CWALK_FILE_Init();
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_Init failed. Error number is %d\n", ret);
		return false;
	}

	m_IsInitFile = true;
	memset(InfoBuf, 0, sizeof(InfoBuf));
	ret = CWALK_FILE_GetSDK_Version(InfoBuf, sizeof(InfoBuf), &RealLen);
	if (ret == CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetSDK_Version failed. Error number is %d\n", ret);
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
		InsertLog(FATAL, "CWALK_NET102_Init failed. Error number is %d\n", ret);
		return false;
	}

	m_IsInitNet = true;
	memset(InfoBuf, 0, sizeof(InfoBuf));
	ret = CWALK_NET_GetSDK_Version(InfoBuf, sizeof(InfoBuf), &RealLen);
	if (ret == CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetSDK_Version failed. Error number is %d\n", ret);
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

	InsertLog(INFO, "INIT SDK SUCCESS !!!!\n");
	return true;
}


bool JSDCCTV::Login()
{
	ErrorNum ret = CWALK_NET_Login(&m_LoginHandle, m_DCSUserInfo.IPAddress, m_DCSUserInfo.Port, m_DCSUserInfo.UserName, m_DCSUserInfo.Password);
	if (ret != CWALKSDK_OK || m_LoginHandle == nullptr)
	{
		InsertLog(FATAL, "CWALK_NET_Login failed. Error number is %d\n", ret);
		return false;
	}

	m_IsLogin = true;
	InsertLog(INFO, "LOGIN SUCCESS !!!!\n");
	return true;
}


void JSDCCTV::Logout()
{
	if (m_IsLogin && m_LoginHandle)
	{
		ErrorNum ret = CWALK_NET_Logout(m_LoginHandle);
		if (ret != CWALKSDK_OK)
		{
			InsertLog(WARN, "CWALK_NET_Logout failed. Error number is %d\n", ret);
			InsertLog(WARN, "LOGOUT FAILED !!!!\n");
			m_LoginHandle = nullptr;
			m_IsLogin = false;
			return;
		}
	}

	m_LoginHandle = nullptr;
	m_IsLogin = false;
	InsertLog(INFO, "LOGOUT SUCCESS !!!!\n");
}


void JSDCCTV::ReleaseSDK()
{
	CWALK_NET_Cleanup();
	CWALK_FILE_Cleanup();
	CWALK_PLAY_Cleanup();
}


bool JSDCCTV::IsInit()
{
	return m_IsInitPlay && m_IsInitFile && m_IsInitNet;
}


bool JSDCCTV::IsLogin()
{
	return m_IsLogin;
}


void JSDCCTV::InsertLog(LOGLEVEL Level, const char* const _Format, ...)
{
	if (!m_LogFile.is_open())
	{
		return;
	}

	va_list args;
	va_start(args, _Format);
	int len = _vscprintf(_Format, args) + 1;
	char* buffer = new char[len * sizeof(char)];
	vsnprintf(buffer, len * sizeof(char), _Format, args);
	va_end(args);

	CString str;
	CString strHead;
	CTime curTime = CTime::GetCurrentTime();
	str.Format(L"[ %04d-%02d-%02d %02d:%02d:%02d ] %s", curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond(), buffer);
	
	switch (Level)
	{
	case FATAL: strHead	= L"[ FATAL ] "	;	break;
	case WARN:	strHead	= L"[ WARN ]  "	;	break;
	case DEBUG: strHead = L"[ DEBUG ] "	;	break;
	case INFO:	strHead	= L"[ INFO ]  "	;	break;
	default: break;
	}
	
	str = strHead + str;
	m_LogFile << str.GetBuffer(0);
	
	delete[] buffer;
}


bool JSDCCTV::SetLogFile(const wchar_t* LogPath, int Mode)
{
	m_LogFile.open(LogPath, Mode);
	if (!m_LogFile.is_open())
	{
		// LOG —— 创建日志文件失败
		return false;
	}

	InsertLog(INFO, "********************* Log start here *********************\n");
	return true;
}


void JSDCCTV::SetDCRUserInfo(UserInfo DCRUserInfo)
{
	m_DCRUserInfo = DCRUserInfo;
}


void JSDCCTV::GetDecodeMode(CWALK_PLAY_HD PlayHD, int* DecodeMode, int* HwType)
{
	ErrorNum ret = CWALK_PLAY_GetDecodeMode(PlayHD, DecodeMode, HwType);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetDecodeMode failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_SetDecodeStateCallBack(PlayHD, FnDecodeState, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_SetDecodeStateCallBack failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam)
{
	ErrorNum ret = CWALK_NET_SetTransferRobbedCallBack(m_LoginHandle, FnRobbed, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "SetTransferRobbedCallBack failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreatePlayerEx(PlayHD, Hwnd, StreamType, DecodeMode, HwType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CreatePlayerEx failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::ReleasePlayer(CWALK_PLAY_HD PlayHD)
{
	ErrorNum ret = CWALK_PLAY_ReleasePlayer(PlayHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_ReleasePlayer failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartStream(m_LoginHandle, StreamHD, AvPath, FnData, FnRobbed, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartStream failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::StreamRequestIFrame(CWALK_NET_HD StreamHD)
{
	ErrorNum ret = CWALK_NET_StreamRequestIFrame(StreamHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StreamRequestIFrame failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::StopStream(CWALK_NET_HD StreamHD)
{
	ErrorNum ret = CWALK_NET_StopStream(StreamHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_StopStream failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::QueryRecordInfo(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam)
{
	ErrorNum ret = CWALK_NET_QueryRecordInfo(m_LoginHandle, AvPath, VodType, BeginTime, EndTime, FnOnListSegment, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_QueryRecordInfo failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, CallBack_OnStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartPlaybackStream(m_LoginHandle, StreamHD, AvPath, VodType, BeginTime, EndTime, FnData, FnRobbed, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartPlaybackStream failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam)
{
	ErrorNum ret = CWALK_PLAY_PlayControl(PlayHD, Cmd, InParam, OutParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_PlayControl failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD)
{
	ErrorNum ret = CWALK_FILE_OpenWritbaleFile(FileName, WriteHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_OpenWritbaleFile failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos)
{
	ErrorNum ret = CWALK_NET_GetPlaybackStreamPos(StreamHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_GetPlaybackStreamPos failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::CloseWritableFile(CWALK_FILE_HD WriteHD)
{
	ErrorNum ret = CWALK_FILE_CloseWritableFile(WriteHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_CloseWritableFile failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName)
{
	ErrorNum ret = CWALK_PLAY_CapturePicture(PlayHD, FileName);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CapturePicture failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD)
{
	ErrorNum ret = CWALK_FILE_OpenReadableFile(FileName, ReadHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_OpenReadableFile failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::CloseReadableFile(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_CloseReadableFile(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_CloseReadableFile failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::FreeFile(void* Ptr)
{
	CWALK_FILE_Free(Ptr);
}


bool JSDCCTV::SetPlayMode(CWALK_FILE_HD ReadHD, int Mode)
{
	ErrorNum ret = CWALK_FILE_SetPlayMode(ReadHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_SetPlayMode failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode)
{
	ErrorNum ret = CWALK_FILE_GetPlayMode(ReadHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetPlayMode failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len)
{
	ErrorNum ret = CWALK_FILE_WriteData(WriteHD, data, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_WriteData failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::ReadSlice(CWALK_FILE_HD ReadHD, void** Data, int* Len)
{
	ErrorNum ret = CWALK_FILE_ReadSlice(ReadHD, Data, Len);
	if (ret != CWALKSDK_OK)
	{
		if (ret == CWALKSDK_ERR_END_OF_FILE)
		{
			InsertLog(INFO, "CWALK_FILE_ReadSlice end of the file\n");
		}
		else
		{
			InsertLog(FATAL, "CWALK_FILE_ReadSlice failed. Error number is %d\n", ret);
			return false;
		}
	}

	return true;
}


void JSDCCTV::GetFileDuration(CWALK_FILE_HD ReadHD, DWORD* Len)
{
	ErrorNum ret = CWALK_FILE_GetDuration(ReadHD, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetDuration failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len)
{
	ErrorNum ret = CWALK_FILE_GetPos(ReadHD, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetPos failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len)
{
	ErrorNum ret = CWALK_FILE_SetPos(ReadHD, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_GetDuration failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time)
{
	ErrorNum ret = CWALK_FILE_GetBaseTime(ReadHD, Time);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetBaseTime failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen)
{
	ErrorNum ret = CWALK_FILE_GetStringBaseTime(ReadHD, Buf, BufLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetStringBaseTime failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType)
{
	ErrorNum ret = CWALK_FILE_GetVideoInfo(ReadHD, Width, Height, Rate, StreamType);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetVideoInfo failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD)
{
	ErrorNum ret = CWALK_FILE_CreateExtrator(Data, Size, ExtratorHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_CreateExtrator failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size)
{
	ErrorNum ret = CWALK_FILE_InputData(ExtratorHD, Data, Size);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_InputData failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::NextFrame(CWALK_FILE_HD ExtratorHD, void* pStream, int* Len)
{
	ErrorNum ret = CWALK_FILE_NextFrame(ExtratorHD, pStream, Len);
	if (ret != CWALKSDK_OK)
	{
		if (ret == CWALKSDK_ERR_NOT_ENOUGH_MEM)
		{
			InsertLog(WARN, "CWALK_FILE_NextFrame failed. pStream dose not have enough memory. Please reallocate memory based on Len. Len is %d\n", (*Len));
		}

		InsertLog(WARN, "CWALK_FILE_NextFrame failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::ReleaseExtractor(CWALK_FILE_HD ExtratorHD)
{
	ErrorNum ret = CWALK_FILE_ReleaseExtractor(ExtratorHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_ReleaseExtractor failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, const TCHAR* Pool, const TCHAR* FilePath)
{
	ErrorNum ret = CWALK_FILE_OpenOfflineFile(Protocol, ReadHD, IP, Port, Pool, FilePath, m_DCRUserInfo.UserName, m_DCRUserInfo.Password);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_OpenOfflineFile failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::CloseOfflineFile(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_CloseOfflineFile(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_CloseOfflineFile failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_FILE_StartOfflineFileStream(ReadHD, BeginTime, EndTime, FnData, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_StartOfflineFileStream failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::StopOfflineFileStream(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_StopOfflineFileStream(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_StopOfflineFileStream failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, int* Width, int* Height, int* VCodec, int* ACodec)
{
	ErrorNum ret = CWALK_FILE_GetOfflineFileInfo(ReadHD, Size, Duration, FPS, Width, Height, VCodec, ACodec);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetOfflineFileInfo failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos)
{
	ErrorNum ret = CWALK_FILE_GetOfflineFileStreamPos(ReadHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_FILE_GetOfflineFileStreamPos failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFileStreamPos(ReadHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_SetOfflineFileStreamPos failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFileStreamSpeed(ReadHD, Speed);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_SetOfflineFileStreamSpeed failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFilePlaybackMode(ReadHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_FILE_SetOfflineFilePlaybackMode failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::DetectDecSupports(char* pDecoderTypes, INT_PTR* Len)
{
	ErrorNum ret = CWALK_PLAY_DetectDecSupports(pDecoderTypes, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_DetectDecSupports failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreatePlayerEx(PlayHD, Hwnd, StreamType, DecodeMode, HwType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CreatePlayerEx failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreateHWPlayer(PlayHD, Hwnd, StreamType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CreateHWPlayer failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::CheckHwSupport(int* Support)
{
	ErrorNum ret = 0; //CWALK_PLAY_CheckHwSupport(Support);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_CheckHwSupport failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport)
{
	ErrorNum ret = CWALK_PLAY_SetHwDecType(Type, IsSupport);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetHwDecType failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::InputData(CWALK_PLAY_HD PlayHD, const void* Data, int Len)
{
	ErrorNum ret = CWALK_PLAY_InputData(PlayHD, Data, Len);
	if (ret != CWALKSDK_OK)
	{
		if (ret == CWALKSDK_ERR_PLAY_FULL_SILCES)
		{
			InsertLog(WARN, "CWALK_PLAY_InputData failed. Play buffer is full\n");
		}
		else
		{
			InsertLog(FATAL, "CWALK_PLAY_InputData failed. Error number is %d\n", ret);
			return false;
		}
	}

	return true;
}


bool JSDCCTV::SetPane(CWALK_PLAY_HD PlayHD, const CWALKPLayRect* Rect, bool Ratio)
{
	ErrorNum ret = CWALK_PLAY_SetPane(PlayHD, Rect, Ratio);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetPane failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::ClearPlayBuffer(CWALK_PLAY_HD PlayHD)
{
	ErrorNum ret = CWALK_PLAY_ClearPlayBuffer(PlayHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_ClearPlayBuffer failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::SoundEnable(CWALK_PLAY_HD PlayHD, bool Enable)
{
	ErrorNum ret = CWALK_PLAY_SoundEnable(PlayHD, Enable);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_SoundEnable failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::SoundIsEnable(CWALK_PLAY_HD PlayHD, BOOL* Enable)
{
	ErrorNum ret = CWALK_PLAY_SoundIsEnable(PlayHD, Enable);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_SoundIsEnable failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetMasterVolume(int* Volume)
{
	ErrorNum ret = CWALK_PLAY_GetMasterVolume(Volume);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetMasterVolume failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetMasterVolume(int Volume)
{
	ErrorNum ret = CWALK_PLAY_SetMasterVolume(Volume);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetMasterVolume failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetMasterVolumeMute(int* Mute)
{
	ErrorNum ret = CWALK_PLAY_GetMasterVolumeMute(Mute);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetMasterVolumeMute failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetMasterVolumeMute(int Mute)
{
	ErrorNum ret = CWALK_PLAY_SetMasterVolumeMute(Mute);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetMasterVolumeMute failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetAudioCallback(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_SetAudioCallback(PlayHD, FnOnAudio, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetAudioCallback failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetColor(CWALK_PLAY_HD PlayHD, int* Brightness, int* Contrast, int* Saturation, int* Hue)
{
	ErrorNum ret = CWALK_PLAY_GetColor(PlayHD, Brightness, Contrast, Saturation, Hue);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetColor failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetColor(CWALK_PLAY_HD PlayHD, int Brightness, int Contrast, int Saturation, int Hue)
{
	ErrorNum ret = CWALK_PLAY_SetColor(PlayHD, Brightness, Contrast, Saturation, Hue);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetColor failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::CreateZoomRect(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* ZoomHD, const CWALKPLayOSDRect* Rect, HWND Hwnd)
{
	ErrorNum ret = CWALK_PLAY_CreateZoomRect(PlayHD, ZoomHD, Rect, Hwnd);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CreateZoomRect failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetZoomRect(CWALK_PLAY_HD ZoomHD, CWALKPLayOSDRect* Rect)
{
	ErrorNum ret = CWALK_PLAY_GetZoomRect(ZoomHD, Rect);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetZoomRect failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetZoomRect(CWALK_PLAY_HD ZoomHD, const CWALKPLayOSDRect* Rect)
{
	ErrorNum ret = CWALK_PLAY_SetZoomRect(ZoomHD, Rect);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetZoomRect failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::ReleaseZoomRect(CWALK_PLAY_HD ZoomHD)
{
	ErrorNum ret = CWALK_PLAY_ReleaseZoomRect(ZoomHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_ReleaseZoomRect failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::CreateOSD(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* osdHD, CWALKPLayOSDType Type, const void* osdInfo)
{
	ErrorNum ret = CWALK_PLAY_CreateOSD(PlayHD, osdHD, Type, osdInfo);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_CreateOSD failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, void* osdInfo)
{
	ErrorNum ret = CWALK_PLAY_GetOSD(osdHD, Type, osdInfo);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_GetOSD failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, const void* osdInfo)
{
	ErrorNum ret = CWALK_PLAY_SetOSD(osdHD, Type, osdInfo);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetOSD failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::ReleaseOSD(CWALK_PLAY_HD osdHD)
{
	ErrorNum ret = CWALK_PLAY_ReleaseOSD(osdHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_ReleaseOSD failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetIllumination(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth, int MaskHeight, double Factor)
{
	ErrorNum ret = CWALK_PLAY_SetIllumination(PlayHD, Rect, MaskWidth, MaskHeight, Factor);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetIllumination failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetScaleImageRange(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Min, int Max)
{
	ErrorNum ret = CWALK_PLAY_SetScaleImageRange(PlayHD, Rect, Min, Max);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetScaleImageRange failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetEmphasize(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth, int MaskHeight, double Factor)
{
	ErrorNum ret = CWALK_PLAY_SetEmphasize(PlayHD, Rect, MaskWidth, MaskHeight, Factor);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetEmphasize failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetSmooth(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth, int MaskHeight, double Factor)
{
	ErrorNum ret = CWALK_PLAY_SetSmooth(PlayHD, Rect, MaskWidth, MaskHeight, Factor);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetSmooth failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetDehaze(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, double TransMin)
{
	ErrorNum ret = CWALK_PLAY_SetDehaze(PlayHD, Rect, TransMin);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetDehaze failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetRetina(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect)
{
	ErrorNum ret = CWALK_PLAY_SetRetina(PlayHD, Rect);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetRetina failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetRestoration(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Blurring, double Angle, int Type)
{
	ErrorNum ret = CWALK_PLAY_SetRestoration(PlayHD, Rect, Blurring, Angle, Type);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_PLAY_SetRestoration failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::DelEnhance(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int EnhanceType)
{
	ErrorNum ret = CWALK_PLAY_DelEnhance(PlayHD, Rect, EnhanceType);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_PLAY_DelEnhance failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetNetServerVersion(void* InfoBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetServerVersion(m_LoginHandle, InfoBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetServerVersion failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetTicket(BYTE* InfoBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetTicket(m_DCSUserInfo.IPAddress, m_DCSUserInfo.Port, m_DCSUserInfo.UserName, m_DCSUserInfo.Password, InfoBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetTicket failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::LoginByTicket(BYTE* Ticket, int Len)
{
	ErrorNum ret = CWALK_NET_LoginByTicket(&m_LoginHandle, m_DCSUserInfo.IPAddress, m_DCSUserInfo.Port, Ticket, Len);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_LoginByTicket failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetServerTime(TCHAR* DateTime, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetServerTime(m_LoginHandle, DateTime, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetServerTime failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetServerTime(TCHAR* DateTime)
{
	ErrorNum ret = CWALK_NET_SetServerTime(m_LoginHandle, DateTime);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetServerTime failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SyncDeviceTime(const TCHAR* SerName, const TCHAR* HostName)
{
	ErrorNum ret = CWALK_NET_SyncDeviceTime(m_LoginHandle, SerName, HostName);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SyncDeviceTime failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetUserDescription(void* Buf, int* BufLen, int* DateLen)
{
	ErrorNum ret = CWALK_NET_GetUserDescription(m_LoginHandle, Buf, BufLen, DateLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetUserDescription failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetUserData(void* Buf, int BufLen, int* DataLen)
{
	ErrorNum ret = CWALK_NET_GetUserData(m_LoginHandle, Buf, BufLen, DataLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetUserData failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetUserData(void* Data, int DataLen)
{
	ErrorNum ret = CWALK_NET_SetUserData(m_LoginHandle, Data, DataLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetUserData failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetUserPassword(const TCHAR* OldPassword, const TCHAR* NewPassword)
{
	ErrorNum ret = CWALK_NET_SetUserPasswd(m_LoginHandle, OldPassword, NewPassword);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetUserPasswd failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::IsConnected(BOOL* Connect)
{
	ErrorNum ret = CWALK_NET_IsConnected(m_LoginHandle, Connect);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_IsConnected failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetObjectStatus(CWALKNetObjectType ObjType, const TCHAR* ObjName, int* Status)
{
	ErrorNum ret = CWALK_NET_GetObjectStatus(m_LoginHandle, ObjType, ObjName, Status);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetObjectStatus failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetVodStatus(int* Status)
{
	ErrorNum ret = CWALK_NET_GetVodStatus(m_LoginHandle, Status);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetVodStatus failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetPtzStatus(const TCHAR* CamName, void* StatusBuf, int BufLen, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetPtzStatus(m_LoginHandle, CamName, StatusBuf, BufLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetPtzStatus failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetCameraStatus(const TCHAR* ObjName, void* Buf, int BufLen, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetCameraStatus(m_LoginHandle, ObjName, Buf, BufLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetCameraStatus failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetServiceStatus(CWALKNetServiceType ServiceType, void* InfoBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetServiceStatus(m_LoginHandle, ServiceType, InfoBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetServiceStatus failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::ListObjects(CWALKNetObjectType ObjType, const TCHAR* SerName, int* Count, CallBack_OnListObj FnOnListObj, void* UserParam)
{
	ErrorNum ret = CWALK_NET_ListObjects(m_LoginHandle, ObjType, SerName, Count, FnOnListObj, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_ListObjects failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::ListObjectsEx(CWALKNetObjectType ObjType, const TCHAR* SerName, int* Count, CallBack_OnListObj FnOnListObj, void* UserParam, const TCHAR* GroupID, bool IsGetAllCamera)
{
	ErrorNum ret = CWALK_NET_ListObjectsEX(m_LoginHandle, ObjType, SerName, Count, FnOnListObj, UserParam, GroupID, IsGetAllCamera);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_ListObjectsEX failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::QueryProtectionRecord(const TCHAR* AvPath, CallBack_OnListSegments FnOnListSegment, void* UserParam)
{
	ErrorNum ret = CWALK_NET_QueryProtectionRecord(m_LoginHandle, AvPath, FnOnListSegment, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_QueryProtectionRecord failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetOnlineUsers(const TCHAR* SerName, CallBack_OnGetOnlineUsers FnOnUsers, void* UserParam)
{
	ErrorNum ret = CWALK_NET_GetOnlineUsers(m_LoginHandle, SerName, FnOnUsers, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetOnlineUsers failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetTransferStatus(const TCHAR* SerName, CallBack_OnGetTransferStatus FnOnStatus, void* UserParam)
{
	ErrorNum ret = CWALK_NET_GetTransferStatus(m_LoginHandle, SerName, FnOnStatus, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetTransferStatus failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::ProtectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime)
{
	ErrorNum ret = CWALK_NET_ProtectRecord(m_LoginHandle, AvPath, BeginTime, EndTime);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_ProtectRecord failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::UnprotectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime)
{
	ErrorNum ret = CWALK_NET_UnprotectRecord(m_LoginHandle, AvPath, BeginTime, EndTime);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_UnprotectRecord failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::AddObject(CWALKNetObjectType ObjType, const TCHAR* Parent, const TCHAR* ObjInfo)
{
	ErrorNum ret = CWALK_NET_AddObject(m_LoginHandle, ObjType, Parent, ObjInfo);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_AddObject failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::DelObject(CWALKNetObjectType ObjType, const TCHAR* ObjName)
{
	ErrorNum ret = CWALK_NET_DelObject(m_LoginHandle, ObjType, ObjName);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_DelObject failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetOrganization(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount)
{
	ErrorNum ret = CWALK_NET_GetOrganization(m_LoginHandle, Buf, BufLen, DataLen, OrgCount, DCSCount);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetOrganization failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetOrganizationEx(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount, BOOL bUseUserID)
{
	ErrorNum ret = CWALK_NET_GetOrganizationEX(m_LoginHandle, Buf, BufLen, DataLen, OrgCount, DCSCount, bUseUserID);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetOrganizationEX failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::ParseOrganizationInfo(const TCHAR* Info, int Type, int Index, const TCHAR* Key, void* ValueBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_ParseOrganizationInfo(Info, Type, Index, Key, ValueBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_ParseOrganizationInfo failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetServerTitle(const TCHAR* ServerName, void* InfoBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetServerTitle(m_LoginHandle, ServerName, InfoBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetServerTitle failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartTransfer(const TCHAR* Source, const TCHAR* Target)
{
	ErrorNum ret = CWALK_NET_StartTransfer(m_LoginHandle, Source, Target);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartTransfer failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::StopTransfer(const TCHAR* Target)
{
	ErrorNum ret = CWALK_NET_StopTransfer(m_LoginHandle, Target);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_StopTransfer failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartStreamByAsync(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, CallBack_OnStartRealStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartStreamByAsync(m_LoginHandle, StreamHD, AvPath, FnData, FnRobbed, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartStreamByAsync failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::StartRecord(const TCHAR* AvPath)
{
	ErrorNum ret = CWALK_NET_StartRecord(m_LoginHandle, AvPath);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartRecord failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::StopRecord(const TCHAR* AvPath)
{
	ErrorNum ret = CWALK_NET_StopRecord(m_LoginHandle, AvPath);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_StopRecord failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::CapCameraPicture(const TCHAR* AvPath, TCHAR* PicResolution, TCHAR* PicFormat, TCHAR* PicBuff, int BuffLen, int* RealLen)
{
	ErrorNum ret = CWALK_NET_CapCameraPicture(m_LoginHandle, AvPath, PicResolution, PicFormat, PicBuff, BuffLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_CapCameraPicture failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::PtzControl(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, int Param)
{
	ErrorNum ret = CWALK_NET_PtzControl(m_LoginHandle, AvPath, Cmd, Param);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_PtzControl first failed. Error number is %d\n", ret);
		return false;
	}

	ret = CWALK_NET_PtzControl(m_LoginHandle, AvPath, Cmd, 0);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_PtzControl second failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::PtzControlEx(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, const TCHAR* Param)
{
	ErrorNum ret = CWALK_NET_PtzControlEx(m_LoginHandle, AvPath, Cmd, Param);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_PtzControlEx first failed. Error number is %d\n", ret);
		return false;
	}

	ret = CWALK_NET_PtzControlEx(m_LoginHandle, AvPath, Cmd, 0);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_PtzControlEx second failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::PtzControl3D(const TCHAR* AvPath, int Direct, float x, float y, float w, float h)
{
	if (x < 0 || x > 1 || y < 0 || y > 1 || w < 0 || w > 1 || h < 0 || h > 1)
	{
		// LOG —— 参数错误
		InsertLog(FATAL, "PtzControl3D failed. Parameter error\n");
		return false;
	}

	ErrorNum ret = CWALK_NET_PtzControl3D(m_LoginHandle, AvPath, Direct, x, y, w, h);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_PtzControl3D failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::PtzLock(const TCHAR* AvPath, int LockTime)
{
	ErrorNum ret = CWALK_NET_PtzLock(m_LoginHandle, AvPath, LockTime);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_PtzLock failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::PtzAuxControl(const TCHAR* AvPath, int Num, BOOL Control)
{
	ErrorNum ret = CWALK_NET_PtzAuxControl(m_LoginHandle, AvPath, Num, Control);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_PtzAuxControl failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::GetCameraGis(const TCHAR* AvPath, void* Buf, int BufLen, int* RealLen)
{
	ErrorNum ret = CWALK_NET_GetCameraGis(m_LoginHandle, AvPath, Buf, BufLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetCameraGis failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::CancelGisInfoSubscription()
{
	ErrorNum ret = CWALK_NET_CancelGisInfoSubscription(m_LoginHandle);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_CancelGisInfoSubscription failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SubscribeGisInfo(CallBack_OnGisInfoUpload FnOnUpload, void* UserParam)
{
	ErrorNum ret = CWALK_NET_SubscribeGisInfo(m_LoginHandle, FnOnUpload, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SubscribeGisInfo failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetCameraLevel(const TCHAR* AvPath, int Level)
{
	ErrorNum ret = CWALK_NET_SetCameraLevel(m_LoginHandle, AvPath, Level);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetCameraLevel failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetCamerasChangedNotify(CallBack_OnCamerasChangedNotify FnOnCamerasChangedNotify, void* UserParam)
{
	ErrorNum ret = CWALK_NET_SetCamerasChangedNotify(m_LoginHandle, FnOnCamerasChangedNotify, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetCamerasChangedNotify failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetCamerasChangedVersion(INT64* ChangedVersion)
{
	ErrorNum ret = CWALK_NET_GetCamerasChangedVersion(m_LoginHandle, ChangedVersion);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetCamerasChangedVersion failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, CallBack_OnListSegments FnOnListSegment, void* UserParam)
{
	ErrorNum ret = CWALK_NET_QueryRecord(m_LoginHandle, AvPath, VodType, BeginTime, EndTime, FnOnListSegment, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_QueryRecord failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::StopPlayBackStream(CWALK_NET_HD PlayBackHD)
{
	ErrorNum ret = CWALK_NET_StopPlaybackStream(PlayBackHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_StopPlaybackStream failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::StartDownloadStreamEx(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, INT64 BeginThisPackage, INT64 BeginNextPackage, Callback_OnStreamDataEx FnData, CallBack_OnStreamRobbed FnRobbed, CallBack_OnStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_NET_StartDownloadStreamEx(m_LoginHandle, StreamHD, AvPath, VodType, BeginTime, EndTime, BeginThisPackage, BeginNextPackage, FnData, FnRobbed, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_StartDownloadStreamEx failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::StopDownloadStream(CWALK_NET_HD StreamHD)
{
	ErrorNum ret = CWALK_NET_StopDownloadStream(StreamHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_StopDownloadStream failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64 Pos)
{
	ErrorNum ret = CWALK_NET_SetPlaybackStreamPos(StreamHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetPlaybackStreamPos failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetPlayBackSpeed(CWALK_NET_HD StreamHD, double Speed)
{
	ErrorNum ret = CWALK_NET_SetPlaybackSpeed(StreamHD, Speed);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetPlaybackSpeed failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::SetPlayBackMode(CWALK_NET_HD StreamHD, INT32 Mode)
{
	ErrorNum ret = CWALK_NET_SetPlaybackMode(StreamHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SetPlaybackMode failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::AddTag(const TCHAR* TagName, const TCHAR* TagTime, const TCHAR* ChannelName, const TCHAR* Description, int TagType, int Level)
{
	ErrorNum ret = CWALK_NET_AddTag(m_LoginHandle, TagName, TagTime, ChannelName, Description, TagType, Level);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_AddTag failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::GetTagNames(int* NameCount, CallBack_OnGetTagNames FnOnNames, void* UserParam)
{
	ErrorNum ret = CWALK_NET_GetTagNames(m_LoginHandle, NameCount, FnOnNames, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_GetTagNames failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::QueryTag(const TCHAR* Condition, int* RecordCount, BOOL* IsEnd, CallBack_OnQueryTag FnOnQueryTag, void* UserParam)
{
/// Condition	查询条件,JSON格式字符串，可由CWALK_NET_InfoHelperXXX系列函数帮助生成
///
///		查询条件为如下一种或多种的组合：
///			maxCount		[INT]	 返回数据的最大条数，默认值：1000，最大值：2000
///			startPos		[INT]	 数据返回起始位置，默认值：0
///			tagNames		[string] 标记名称，必须是CWALK_NET_GetTagNames()得到的名称，支持多个，多个用“;”隔开，如："打架标记;车祸标记;报警标记"
///			channelNames	[string] 通道名称，支持多个，支持模糊查询，多个用“;”隔开，如："av/dcam/1;av/dcam/2;av/dcam/3"
///			beginTagTime	[string] 开始标记时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endTagTime		[string] 结束标记时间（不含）
///			beginCreateTime [string] 开始创建时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endCreateTime	[string] 结束创建时间（不含）
///			beginModifyTime [string] 开始修改时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endModifyTime	[string] 结束修改时间（不含）
///			tagType			[INT]	 标记类型 0 - 自动;1 - 手动;其它 - 未使用
///			level			[INT]	 标记级别,取值[1-5],1-不重要;2-不太重要;3-一般;4-重要;5-很重要
///			createUser		[string] 创建用户，注：不支持模糊查询
///			modifyUser		[string] 最后一次修改用户，注：不支持模糊查询
///			description		[string] 描述信息，支持关键字模糊查询
/// 
	ErrorNum ret = CWALK_NET_QueryTag(m_LoginHandle, Condition, RecordCount, IsEnd, FnOnQueryTag, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_QueryTag failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::ModifyTagName(const TCHAR* OldTagName, const TCHAR* NewTagName)
{
	ErrorNum ret = CWALK_NET_ModifyTagName(m_LoginHandle, OldTagName, NewTagName);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_ModifyTagName failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


bool JSDCCTV::ModifyTag(INT64 TagID, const TCHAR* TagName, const TCHAR* Description, int Level)
{
	ErrorNum ret = CWALK_NET_ModifyTag(m_LoginHandle, TagID, TagName, Description, Level);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_ModifyTag failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::DeleteTags(INT64 TagIdArray[], int ArrayLen)
{
	ErrorNum ret = CWALK_NET_DeleteTags(m_LoginHandle, TagIdArray, ArrayLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_DeleteTags failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::SubscribeEvent(CallBack_OnEvent FnOnEvent, void* UserParam)
{
	ErrorNum ret = CWALK_NET_SubscribeEvent(m_LoginHandle, FnOnEvent, UserParam);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_SubscribeEvent failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::CancelEventSubscription()
{
	ErrorNum ret = CWALK_NET_CancelEventSubscription(m_LoginHandle);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_CancelEventSubscription failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::ExecuteScript(const TCHAR* ScriptType, const TCHAR* Script)
{
	ErrorNum ret = CWALK_NET_ExecuteScript(m_LoginHandle, ScriptType, Script);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_ExecuteScript failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::InfoParseKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, void* ValueBuf, int Len, int* RealLen)
{
	ErrorNum ret = CWALK_NET_InfoParseKeyValue(ObjInfo, Key, ValueBuf, Len, RealLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoParseKeyValue failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::InfoParseIntKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, int* Value)
{
	ErrorNum ret = CWALK_NET_InfoParseIntKeyValue(ObjInfo, Key, Value);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoParseIntKeyValue failed. Error number is %d\n", ret);
	}
}


bool JSDCCTV::InfoHelperCreate(CWALK_HELP_HD* HelpHD)
{
	ErrorNum ret = CWALK_NET_InfoHelperCreate(HelpHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(FATAL, "CWALK_NET_InfoHelperCreate failed. Error number is %d\n", ret);
		return false;
	}

	return true;
}


void JSDCCTV::InfoHelperAddKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, const TCHAR* Value)
{
	ErrorNum ret = CWALK_NET_InfoHelperAddKeyValue(HelpHD, Key, Value);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoHelperAddKeyValue failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::InfoHelperAddIntKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, int Value)
{
	ErrorNum ret = CWALK_NET_InfoHelperAddIntKeyValue(HelpHD, Key, Value);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoHelperAddIntKeyValue failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::InfoHelperGetData(CWALK_HELP_HD HelpHD, LPCTSTR* Buf, int* BufLen)
{
	ErrorNum ret = CWALK_NET_InfoHelperGetData(HelpHD, Buf, BufLen);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoHelperGetData failed. Error number is %d\n", ret);
	}
}


void JSDCCTV::InfoHelperRelease(CWALK_HELP_HD HelpHD)
{
	ErrorNum ret = CWALK_NET_InfoHelperRelease(HelpHD);
	if (ret != CWALKSDK_OK)
	{
		InsertLog(WARN, "CWALK_NET_InfoHelperRelease failed. Error number is %d\n", ret);
	}
}
