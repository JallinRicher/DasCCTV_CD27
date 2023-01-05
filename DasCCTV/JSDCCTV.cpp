#include "pch.h"
#include "JSDCCTV.h"

JSDCCTV::JSDCCTV(UserInfo userInfo) : m_DCSUserInfo(userInfo)
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
	CharToWChar(m_DCSUserInfo.IPAddress, IPAddress);
	CharToWChar(m_DCSUserInfo.UserName, UserName);
	CharToWChar(m_DCSUserInfo.Password, Password);

	ErrorNum ret = CWALK_NET_Login(&m_LoginHandle, IPAddress, m_DCSUserInfo.Port, UserName, Password);
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


bool JSDCCTV::OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD)
{
	ErrorNum ret = CWALK_FILE_OpenReadableFile(FileName, ReadHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::CloseReadableFile(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_CloseReadableFile(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
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
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode)
{
	ErrorNum ret = CWALK_FILE_GetPlayMode(ReadHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len)
{
	ErrorNum ret = CWALK_FILE_WriteData(WriteHD, data, Len);
	if (ret != CWALKSDK_OK)
	{
		// LOG
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
			// LOG —— 读到文件末尾
		}
		else
		{
			// LOG
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
		// LOG
	}
}


void JSDCCTV::GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len)
{
	ErrorNum ret = CWALK_FILE_GetPos(ReadHD, Len);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len)
{
	ErrorNum ret = CWALK_FILE_SetPos(ReadHD, Len);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time)
{
	ErrorNum ret = CWALK_FILE_GetBaseTime(ReadHD, Time);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen)
{
	ErrorNum ret = CWALK_FILE_GetStringBaseTime(ReadHD, Buf, BufLen, RealLen);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType)
{
	ErrorNum ret = CWALK_FILE_GetVideoInfo(ReadHD, Width, Height, Rate, StreamType);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD)
{
	ErrorNum ret = CWALK_FILE_CreateExtrator(Data, Size, ExtratorHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size)
{
	ErrorNum ret = CWALK_FILE_InputData(ExtratorHD, Data, Size);
	if (ret != CWALKSDK_OK)
	{
		// LOG
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
			// LOG —— pStream 空间不够，Len 返回数据实际需要的空间，用此值再分配空间重新调用一次
		}
		// LOG
	}
}


void JSDCCTV::ReleaseExtractor(CWALK_FILE_HD ExtratorHD)
{
	ErrorNum ret = CWALK_FILE_ReleaseExtractor(ExtratorHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, const TCHAR* Pool, const TCHAR* FilePath)
{
	TCHAR UserName[NAME_LEN] = { 0 };
	TCHAR Password[PASSWORD_LEN] = { 0 };
	CharToWChar(m_DCRUserInfo.UserName, UserName);
	CharToWChar(m_DCRUserInfo.Password, Password);

	ErrorNum ret = CWALK_FILE_OpenOfflineFile(Protocol, ReadHD, IP, Port, Pool, FilePath, UserName, Password);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::CloseOfflineFile(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_CloseOfflineFile(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, void* UserParam)
{
	ErrorNum ret = CWALK_FILE_StartOfflineFileStream(ReadHD, BeginTime, EndTime, FnData, FnMsg, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::StopOfflineFileStream(CWALK_FILE_HD ReadHD)
{
	ErrorNum ret = CWALK_FILE_StopOfflineFileStream(ReadHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, int* Width, int* Height, int* VCodec, int* ACodec)
{
	ErrorNum ret = CWALK_FILE_GetOfflineFileInfo(ReadHD, Size, Duration, FPS, Width, Height, VCodec, ACodec);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos)
{
	ErrorNum ret = CWALK_FILE_GetOfflineFileStreamPos(ReadHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFileStreamPos(ReadHD, Pos);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFileStreamSpeed(ReadHD, Speed);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode)
{
	ErrorNum ret = CWALK_FILE_SetOfflineFilePlaybackMode(ReadHD, Mode);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::DetectDecSupports(char* pDecoderTypes, INT_PTR* Len)
{
	ErrorNum ret = CWALK_PLAY_DetectDecSupports(pDecoderTypes, Len);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreatePlayerEx(PlayHD, Hwnd, StreamType, DecodeMode, HwType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_CreateHWPlayer(PlayHD, Hwnd, StreamType, FnOnDecoder, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::CheckHwSupport(int* Support)
{
	ErrorNum ret = 0; //CWALK_PLAY_CheckHwSupport(Support);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport)
{
	ErrorNum ret = CWALK_PLAY_SetHwDecType(Type, IsSupport);
	if (ret != CWALKSDK_OK)
	{
		// LOG
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
			// LOG —— 播放缓冲区已满
		}
		else
		{
			// LOG
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
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::ClearPlayBuffer(CWALK_PLAY_HD PlayHD)
{
	ErrorNum ret = CWALK_PLAY_ClearPlayBuffer(PlayHD);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::SoundEnable(CWALK_PLAY_HD PlayHD, bool Enable)
{
	ErrorNum ret = CWALK_PLAY_SoundEnable(PlayHD, Enable);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::SoundIsEnable(CWALK_PLAY_HD PlayHD, BOOL* Enable)
{
	ErrorNum ret = CWALK_PLAY_SoundIsEnable(PlayHD, Enable);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


void JSDCCTV::GetMasterVolume(int* Volume)
{
	ErrorNum ret = CWALK_PLAY_GetMasterVolume(Volume);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetMasterVolume(int Volume)
{
	ErrorNum ret = CWALK_PLAY_SetMasterVolume(Volume);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


void JSDCCTV::GetMasterVolumeMute(int* Mute)
{
	ErrorNum ret = CWALK_PLAY_GetMasterVolumeMute(Mute);
	if (ret != CWALKSDK_OK)
	{
		// LOG
	}
}


bool JSDCCTV::SetMasterVolumeMute(int* Mute)
{
	ErrorNum ret = CWALK_PLAY_GetMasterVolumeMute(Mute);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}


bool JSDCCTV::SetAudioCallback(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam)
{
	ErrorNum ret = CWALK_PLAY_SetAudioCallback(PlayHD, FnOnAudio, UserParam);
	if (ret != CWALKSDK_OK)
	{
		// LOG
		return false;
	}

	return true;
}
