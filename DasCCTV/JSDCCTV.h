#pragma once
#include <fstream>
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "cwalk_playsdk.h"
#include "cwalk_codecsdk.h"

#define INFOBUFFER_SIZE		256

struct UserInfo;
typedef CWALKSDKError ErrorNum;

class JSDCCTV
{
public:
	JSDCCTV(UserInfo userInfo);

	bool InitSDK();																											// 初始化SDK
	bool Login();																											// 登录服务器
	void Logout();																											// 登出服务器
	void ReleaseSDK();																										// 释放SDK
	void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* DecodeMode, int* HwType);													// 获取当前解码类型			
	bool SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);
	bool SetAudioCallBack(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);
	bool SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);

	// 实时流播放模块
	bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
					  int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);					// 创建播放器
	void ReleasePlayer(CWALK_PLAY_HD PlayHD);																				// 释放播放器
	bool StartVideoStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						  CallBack_OnStreamRobbed FnRobbed, void* UserParam);												// 启动实时视频流
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);																		// 请求 I 帧
	void StopVideoStream(CWALK_NET_HD StreamHD);																			// 关闭流传输

	// 录像回放模块
	bool QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, 
		             CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);											// 录像查询
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, 
							 CallBack_OnStreamMsg FnMsg, void* UserParam);													// 点播录像
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);					// 播放控制

	// 录像下载模块
	bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);													// 打开可写文件
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);															// 获取录像下载进度
	void CloseWritableFile(CWALK_FILE_HD WriteHD);																			// 关闭写文件操作
	
	// 实时流抓图模块
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);														// 实时流抓图

private:
	void InitPlaySDK();
	bool InitFileSDK();
	bool InitNetSDK();

	void CWALK_SDK_CALLBACK OnRealDecodeState(CWALK_PLAY_HD PlayHD, const CWALKPLayStatInfo* FInfo, void* UserParam)
	{

	}

	// 视频解码回调函数
	void CWALK_SDK_CALLBACK OnRealDecodeData(CWALK_PLAY_HD PlayHD, const void* Buf, int Len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
	{

	}

public:
	static void CharToWChar(const char* Source, wchar_t* Destination);

private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::fstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_UserInfo;
};

