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

	bool InitSDK();																										// 初始化SDK
	bool Login();																										// 登录服务器
	void Logout();																										// 登出服务器
	void ReleaseSDK();																									// 释放SDK	
	bool SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);
	bool SetAudioCallBack(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);
	bool SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);

	// 实时流播放模块
	bool StartVideoStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						  CallBack_OnStreamRobbed FnRobbed, void* UserParam);											// 启动实时视频流
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);																	// 请求 I 帧
	void StopVideoStream(CWALK_NET_HD StreamHD);																		// 关闭流传输

	// 录像回放模块
	bool QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, 
		             CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);										// 录像查询
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, 
							 CallBack_OnStreamMsg FnMsg, void* UserParam);												// 点播录像
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);				// 播放控制

	// 录像下载模块
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);														// 获取录像下载进度
	
	// 实时流抓图模块
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);													// 实时流抓图


public:
	void CWALK_SDK_CALLBACK OnRealDecodeState(CWALK_PLAY_HD PlayHD, const CWALKPLayStatInfo* FInfo, void* UserParam)
	{  }

	// 视频解码回调函数
	void CWALK_SDK_CALLBACK OnRealDecodeData(CWALK_PLAY_HD PlayHD, const void* Buf, int Len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
	{  }


public:
	static void CharToWChar(const char* Source, wchar_t* Destination);


public:		/************************************* CCTV 文件操作模块 *************************************/

	// 媒体文件读操作
	static bool OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD);					// 打开可读文件
	static void CloseReadableFile(CWALK_FILE_HD ReadHD);										// 关闭可读文件
	static bool ReadSlice(CWALK_FILE_HD ReadHD, void** Data, int* Len);							// 从可读文件中读取数据，必须用FreeFile释放数据；读出后的数据为一个完整的slice
	static void FreeFile(void* Ptr);															// 释放内存
	static bool SetPlayMode(CWALK_FILE_HD ReadHD, int Mode);									// 设置播放模式
	static bool GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode);									// 获得播放模式

	// 媒体文件写操作
	static bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);				// 打开可写文件
	static void CloseWritableFile(CWALK_FILE_HD WriteHD);										// 关闭写文件操作
	static bool WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len);					// 数据写入文件，参数data必须为一个完整的slice，可由流传输的回调函数获得

	// 媒体文件位置控制
	static void GetFileDuration(CWALK_FILE_HD ReadHD, DWORD* Len);								// 获得文件产长度
	static void GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len);									// 获得文件读取位置
	static bool SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len);									// 设置文件读取位置

	// 得到录像文件第一帧的生成时间
	static void GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time);									// 获得录像第一帧的生成时间，相对于格林威治标准时间的毫秒数
	static void GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen);	// 获得录像第一帧的生成时间，返回标准格式的时间字符串，内存由调用者分配

	// 数据格式转化
	static void GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType);		// 获取图像信息
	static bool CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD);							// 创建数据格式转换器
	static bool InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size);								// 输入数据
	static void NextFrame(CWALK_FILE_HD ExtratorHD, void* pStream, int* Len);									// 获取数据（可获得数据类型）
	static void ReleaseExtractor(CWALK_FILE_HD ExtratorHD);														// 释放数据格式转化器

	// 离线文件操作
	bool OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, 
						 const TCHAR* Pool, const TCHAR* FilePath);												// 打开离线文件
	static void CloseOfflineFile(CWALK_FILE_HD ReadHD);															// 关闭离线文件
	static bool StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, 
									   Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, 
									   void* UserParam);														// 开启离线文件传输
	static void StopOfflineFileStream(CWALK_FILE_HD ReadHD);													// 停止离线回放
	static void GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, 
								   int* Width, int* Height, int* VCodec, int* ACodec);							// 获取离线文件的详细信息
	static void GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos);										// 获取离线文件播放进度
	static bool SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos);										// 设置离线文件播放进度
	static bool SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed);									// 设置播放速度
	static bool SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode);									// 设置离线文件播放模式


public:		/************************************* CCTV 媒体播放模块 *************************************/

	// 播放器创建和释放
	static void DetectDecSupports(char* pDecoderTypes, INT_PTR* Len);													// 枚举支持硬解类型接口
	static bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType,
					         int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);		// 创建播放器
	static bool CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
		                       int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);	// 创建播放器（同CreatePlayer）
	static void ReleasePlayer(CWALK_PLAY_HD PlayHD);																	// 释放播放器
	static bool CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
							   Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);								// 创建硬解播放器
	static void CheckHwSupport(int *Support);																			// 检测设备是否支持硬解
	static bool SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport);												// 设置硬解码类型
	static void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* Type, int* HwType);											// 获取当前解码类型
	
private:
	void InitPlaySDK();
	bool InitFileSDK();
	bool InitNetSDK();

private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::fstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
};

