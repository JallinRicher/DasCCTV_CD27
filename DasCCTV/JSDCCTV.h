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
	JSDCCTV(UserInfo DCSUserInfo);
	void InsertLog(LOGLEVEL Level, const char* const _Format, ...);
	static void CharToWChar(const char* Source, wchar_t* Destination);

	bool InitSDK();																										// 初始化SDK
	bool Login();																										// 登录服务器
	void Logout();																										// 登出服务器
	void ReleaseSDK();																									// 释放SDK
	bool IsInit();
	bool IsLogin();
	bool SetLogFile(const char* LogPath);

public:		/************************************* CCTV 文件操作模块 *************************************/
	
	// 文件模块初始化
	bool InitFileSDK();

	// 媒体文件读操作
	bool OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD);				// 打开可读文件
	void CloseReadableFile(CWALK_FILE_HD ReadHD);										// 关闭可读文件
	bool ReadSlice(CWALK_FILE_HD ReadHD, void** Data, int* Len);						// 从可读文件中读取数据，必须用FreeFile释放数据；读出后的数据为一个完整的slice
	void FreeFile(void* Ptr);															// 释放内存
	bool SetPlayMode(CWALK_FILE_HD ReadHD, int Mode);									// 设置播放模式
	void GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode);									// 获得播放模式

	// 媒体文件写操作
	bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);				// 打开可写文件
	void CloseWritableFile(CWALK_FILE_HD WriteHD);										// 关闭写文件操作
	bool WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len);					// 数据写入文件，参数data必须为一个完整的slice，可由流传输的回调函数获得

	// 媒体文件位置控制
	void GetFileDuration(CWALK_FILE_HD ReadHD, DWORD* Len);								// 获得文件产长度
	void GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len);									// 获得文件读取位置
	bool SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len);									// 设置文件读取位置

	// 得到录像文件第一帧的生成时间
	void GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time);								// 获得录像第一帧的生成时间，相对于格林威治标准时间的毫秒数
	void GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen);	// 获得录像第一帧的生成时间，返回标准格式的时间字符串，内存由调用者分配

	// 数据格式转化
	void GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType);		// 获取图像信息
	bool CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD);							// 创建数据格式转换器
	bool InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size);								// 输入数据
	void NextFrame(CWALK_FILE_HD ExtratorHD, void* pStream, int* Len);									// 获取数据（可获得数据类型）
	void ReleaseExtractor(CWALK_FILE_HD ExtratorHD);													// 释放数据格式转化器

	// 离线文件操作
	bool OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, 
						 const TCHAR* Pool, const TCHAR* FilePath);										// 打开离线文件
	void CloseOfflineFile(CWALK_FILE_HD ReadHD);														// 关闭离线文件
	bool StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, 
								Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, 
								void* UserParam);														// 开启离线文件传输
	void StopOfflineFileStream(CWALK_FILE_HD ReadHD);													// 停止离线回放
	void GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, 
							int* Width, int* Height, int* VCodec, int* ACodec);							// 获取离线文件的详细信息
	void GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos);										// 获取离线文件播放进度
	bool SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos);										// 设置离线文件播放进度
	bool SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed);									// 设置播放速度
	bool SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode);									// 设置离线文件播放模式


public:		/************************************* CCTV 媒体播放模块 *************************************/
	
	// 播放模块初始化
	void InitPlaySDK();

	// 播放器创建和释放
	void DetectDecSupports(char* pDecoderTypes, INT_PTR* Len);													// 枚举支持硬解类型接口
	bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType,
					  int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);		// 创建播放器
	bool CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
		                int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);	// 创建播放器（同CreatePlayer）
	void ReleasePlayer(CWALK_PLAY_HD PlayHD);																	// 释放播放器
	bool CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
						Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);								// 创建硬解播放器
	void CheckHwSupport(int *Support);																			// 检测设备是否支持硬解（暂时不能使用）
	bool SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport);												// 设置硬解码类型
	void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* Type, int* HwType);											// 获取当前解码类型
	void SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);	// 设置解码状态回调函数

	// 媒体数据输入
	bool InputData(CWALK_PLAY_HD PlayHD, const void* Data, int Len);											// 为播放器提供Slice数据

	// 播放控制
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);		// 播放控制
	bool SetPane(CWALK_PLAY_HD PlayHD, const CWALKPLayRect* Rect, bool Ratio);									// 设置显示区域
	void ClearPlayBuffer(CWALK_PLAY_HD PlayHD);																	// 清除播放缓冲区中的数据

	// 抓图
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);											// 实时流抓图
	
	// 声音控制
	void SoundEnable(CWALK_PLAY_HD PlayHD, bool Enable);														// 允许/禁止声音播放，初始化为允许
	void SoundIsEnable(CWALK_PLAY_HD PlayHD, BOOL* Enable);														// 获取声音控制状态s
	void GetMasterVolume(int* Volume);																			// 获取系统主音量
	bool SetMasterVolume(int Volume);																			// 设置系统主音量
	void GetMasterVolumeMute(int* Mute);																		// 获取系统主音量静音
	bool SetMasterVolumeMute(int Mute);																			// 设置系统主音量静音
	bool SetAudioCallback(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);			// 设置音频回调函数

	// 颜色控制
	void GetColor(CWALK_PLAY_HD PlayHD, int* Brightness, int* Contrast, int* Saturation, int* Hue);				// 获取色彩值
	bool SetColor(CWALK_PLAY_HD PlayHD, int Brightness, int Contrast, int Saturation, int Hue);					// 设置色彩值

	// 数字放大
	bool CreateZoomRect(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* ZoomHD, const CWALKPLayOSDRect* Rect, HWND Hwnd);	// 创建数字放大区域
	void GetZoomRect(CWALK_PLAY_HD ZoomHD, CWALKPLayOSDRect* Rect);												// 获取数字放大区域信息
	bool SetZoomRect(CWALK_PLAY_HD ZoomHD, const CWALKPLayOSDRect* Rect);										// 设置数字放大区域信息
	void ReleaseZoomRect(CWALK_PLAY_HD ZoomHD);																	// 释放数字放大区域

	// OSD 部分
	bool CreateOSD(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* osdHD, CWALKPLayOSDType Type, const void* osdInfo);		// 创建 OSD
	void GetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, void* osdInfo);										// 获取 OSD 信息
	bool SetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, const void* osdInfo);								// 设置 OSD 信息
	void ReleaseOSD(CWALK_PLAY_HD osdHD);																		// 释放 OSD

	// 图像处理
	bool SetIllumination(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101, 
						 int MaskHeight = 101, double Factor = 0.7);											// 亮度归一化函数，用于场景内明暗差异过大的图像
	bool SetScaleImageRange(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Min = 30, int Max = 240);		// 对比度拉升函数，用于对比度较小的图像
	bool SetEmphasize(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101,
					  int MaskHeight = 101, double Factor = 0.7);												// 清晰化函数，用户模糊的图像
	bool SetSmooth(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth,
				   int MaskHeight, double Factor);																// 去噪声函数，用于噪点较大的图像
	bool SetDehaze(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, double TransMin = 0.6);						// 去雾函数，用于有雾，有沙尘的图像
	bool SetRetina(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect);											// 视网膜算法函数，用于严重逆光
	bool SetRestoration(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Blurring, double Angle, int Type);	// 图像复原算法，用于离焦，运动模糊
	void DelEnhance(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int EnhanceType);							// 取消图像增强


public:		/************************************* CCTV 网络模块 *************************************/
	
	// 初始化网络模块
	bool InitNetSDK();
	void GetNetServerVersion(void* InfoBuf, int Len, int* RealLen);									// 获得 CMS 服务版本信息

	// 获取认证码
	void GetTicket(BYTE* InfoBuf, int Len, int* RealLen);											// 获取认证码
	bool LoginByTicket(BYTE* Ticket, int Len);														// 通过认证信息登录服务器

	// 时间同步
	void GetServerTime(TCHAR* DateTime, int Len, int* RealLen);										// 获取服务器时间，格式为：“2012-01-01 13:20:00.000”
	bool SetServerTime(TCHAR* DateTime);															// 设置服务器时间，格式为：“2012-01-01 13:20:00.000” 或 “20120101132000000”
	bool SyncDeviceTime(const TCHAR* SerName, const TCHAR* HostName);								// 将设备时间同步为服务器系统时间，当 SerName 为空时，表示当前登录服务器

	// 获取用户描述信息
	void GetUserDescription(void* Buf, int* BufLen, int* DateLen);									// 获取用户描述信息

	// 用户数据设置获取
	void GetUserData(void* Buf, int BufLen, int* DataLen);											// 获取用户数据
	bool SetUserData(void* Data, int DataLen);														// 设置用户数据
	bool SetUserPassword(const TCHAR* OldPassword, const TCHAR* NewPassword);						// 修改用户密码

	// 状态获取
	void IsConnected(BOOL* Connect);																// 获得与服务器的连接状态
	void GetObjectStatus(CWALKNetObjectType ObjType, const TCHAR* ObjName, int* Status);			// 获取对象状态
	void GetVodStatus(int* Status);																	// 获取 VOD 状态
	void GetPtzStatus(const TCHAR* CamName, void* StatusBuf, int BufLen, int* RealLen);				// 获取云台状态
	void GetCameraStatus(const TCHAR* ObjName, void* Buf, int BufLen, int* RealLen);				// 获取摄像头云台状态
	void GetServiceStatus(CWALKNetServiceType ServiceType, void* InfoBuf, int Len, int* RealLen);	// 获取服务器状态信息

	// 列举
	void ListObjects(CWALKNetObjectType ObjType, const TCHAR* SerName = nullptr,					// 列举对象，当 SerName 为空时，表示当前登录服务器
					 int* Count = nullptr, CallBack_OnListObj FnOnListObj = nullptr, 
					 void* UserParam = nullptr);													
	void ListObjectsEx(CWALKNetObjectType ObjType, const TCHAR* SerName = nullptr,					// 列举对象，当 SerName 为空时，表示当前登录服务器；GroupID 不为空表示列举
					   int* Count = nullptr, CallBack_OnListObj FnOnListObj = nullptr,				// 当前 GroupID 对应的摄像机；IsGetAllCamera 表示是否列举所有有权限的设备
					   void* UserParam = nullptr, const TCHAR* GroupID = nullptr,					// IsGetAllCamera = true && GroupID == NULL —— 获取所有摄像机
					   bool IsGetAllCamera = false);												// IsGetAllCamera = false && GroupID == NULL —— 从之前的缓存中获取相应信息		
																									
	void QueryProtectionRecord(const TCHAR* AvPath, CallBack_OnListSegments FnOnListSegment,
							   void* UserParam = nullptr);											// 列举受保护录像
																									
	void GetOnlineUsers(const TCHAR* SerName, CallBack_OnGetOnlineUsers FnOnUsers, void* UserParam);// 列举在线用户信息，当 SerName 为空时，表示当前登录服务器

	// 获取服务器的传输信息
	void GetTransferStatus(const TCHAR* SerName, CallBack_OnGetTransferStatus FnOnStatus,
						   void* UserParam);														// 获取服务器的传输信息

	// 录像保护
	bool ProtectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime);			// 保护录像
	void UnprotectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime);		// 解除录像保护

	// 对象添加和删除
	bool AddObject(CWALKNetObjectType ObjType, const TCHAR* Parent, const TCHAR* ObjInfo);			// 动态添加对象
	bool DelObject(CWALKNetObjectType ObjType, const TCHAR* ObjName);								// 删除对象

	// 组织结构信息获取和解析
	void GetOrganization(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount);		// 获取组织结构信息
	void GetOrganizationEx(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount,		// 得到分组结构信息，获取全部分组信息，不通过用户ID获取，需要上层应用过滤
						   BOOL bUseUserID);														
	void ParseOrganizationInfo(const TCHAR* Info, int Type, int Index, const TCHAR* Key,			// 解析组织结构信息
							   void* ValueBuf, int Len, int* RealLen);								// 对象解析帮助函数,用于解析 CWALK_NET_GetOrganization() 返回的组织结构信息
	
	// 获取登录服务器的标题
	void GetServerTitle(const TCHAR* ServerName, void* InfoBuf, int Len, int* RealLen);				// 获取服务器标题

	// 显示至监视器
	bool StartTransfer(const TCHAR* Source, const TCHAR* Target);									// 发起摄像机到监视器的传输
	void StopTransfer(const TCHAR* Target);															// 停止到某个监视器的传输
	void SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);			// 设置切换抢占通知回调

	// 实时预览
	bool StartStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData,
					 CallBack_OnStreamRobbed FnRobbed, void* UserParam);									// 启动实时视频流
	void StopStream(CWALK_NET_HD StreamHD);																	// 关闭流传输
	bool StartStreamByAsync(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						    CallBack_OnStreamRobbed FnRobbed, CallBack_OnStartRealStreamMsg FnMsg, 
							void* UserParam);																// 启动实时视频流（异步）
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);														// 请求 I 帧
	bool StartRecord(const TCHAR* AvPath);																	// 开始服务端手动录像
	void StopRecord(const TCHAR* AvPath);																	// 停止服务端手动录像
	void CapCameraPicture(const TCHAR* AvPath, TCHAR* PicResolution, TCHAR* PicFormat, TCHAR* PicBuff,
						  int BuffLen, int* RealLen);														// 抓取摄像机实时图片

	// 云台控制
	bool PtzControl(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, int Param);								// 云台控制（通过用户句柄）
	bool PtzControlEx(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, const TCHAR* Param);						// 云台控制扩展（通过用户句柄）
	bool PtzControl3D(const TCHAR* AvPath, int Direct, float x, float y, float w, float h);					// 3D 云台控制（通过用户句柄）
	void PtzLock(const TCHAR* AvPath, int LockTime);														// PTZ 控制锁定
	void PtzAuxControl(const TCHAR* AvPath, int Num, BOOL Control);											// 云台辅助开关控制

	// GIS 功能接口
	void GetCameraGis(const TCHAR* AvPath, void* Buf, int BufLen, int* RealLen);							// 获取 GIS 信息
	void CancelGisInfoSubscription();																		// 退订 GIS 信息
	bool SubscribeGisInfo(CallBack_OnGisInfoUpload FnOnUpload, void* UserParam);							// 订阅 GIS 信息

	// 设置摄像机级别
	bool SetCameraLevel(const TCHAR* AvPath, int Level);													// 设置摄像机级别

	// 摄像机信息获取
	bool SetCamerasChangedNotify(CallBack_OnCamerasChangedNotify FnOnCamerasChangedNotify, void* UserParam);// 设置摄像机变化回调函数
	void GetCamerasChangedVersion(INT64* ChangedVersion);													// 获取摄像机变化版本信息

	// 远程录像
	void QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime,
					 CallBack_OnListSegments FnOnListSegment, void* UserParam);								// 查询录像，非法录像时间段会被过滤掉，错误信息记录到日志中
	void QueryRecordInfo(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime,
						 CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);						// 录像查询
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime,
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed,
							 CallBack_OnStreamMsg FnMsg, void* UserParam);									// 点播录像
	void StopPlayBackStream(CWALK_NET_HD PlayBackHD);														// 停止录像回放，PlayBackHD 由 StartPlayBackStream 得到
	bool StartDownloadStreamEx(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
							   const TCHAR* EndTime, INT64 BeginThisPackage, INT64 BeginNextPackage,
							   Callback_OnStreamDataEx FnData, CallBack_OnStreamRobbed FnRobbed,
							   CallBack_OnStreamMsg FnMsg, void* UserParam);								// 录像下载（支持断点续传）
	void StopDownloadStream(CWALK_NET_HD StreamHD);															// 停止录像下载
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);											// 获取录像下载进度
	bool SetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64 Pos);											// 设置录像播放位置
	bool SetPlayBackSpeed(CWALK_NET_HD StreamHD, double Speed);												// 设置录像回放给流速度
	bool SetPlayBackMode(CWALK_NET_HD StreamHD, INT32 Mode);												// 设置 VOD 播放模式

	// 帧标记
	bool AddTag(const TCHAR* TagName, const TCHAR* TagTime, const TCHAR* ChannelName, 
				const TCHAR* Description, int TagType, int Level);											// 添加帧标记
	void GetTagNames(int* NameCount, CallBack_OnGetTagNames FnOnNames, void* UserParam);					// 获取所有标记名称
	void QueryTag(const TCHAR* Condition, int* RecordCount, BOOL* IsEnd, CallBack_OnQueryTag FnOnQueryTag,
				  void* UserParam);																			// 获取所有标记名称
	bool ModifyTagName(const TCHAR* OldTagName, const TCHAR* NewTagName);									// 修改标记名称
	bool ModifyTag(INT64 TagID, const TCHAR* TagName, const TCHAR* Description, int Level);					// 修改帧标记
	void DeleteTags(INT64 TagIdArray[], int ArrayLen);														// 删除帧标记

	// 事件订阅
	bool SubscribeEvent(CallBack_OnEvent FnOnEvent, void* UserParam);										// 事件订阅
	void CancelEventSubscription();																			// 取消订阅

	// 执行脚本
	bool ExecuteScript(const TCHAR* ScriptType, const TCHAR* Script);										// 执行脚本

	// 帮助函数
	void InfoParseKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, void* ValueBuf,
						   int Len, int* RealLen);															// 对象解析帮助函数，用于获取 ListObjects 函数中，objInfo 参数中的对象属性信息
	void InfoParseIntKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, int* Value);							// 对象解析帮助函数，用于解析 Key-Value 格式 JSON 字符串
	bool InfoHelperCreate(CWALK_HELP_HD* HelpHD);															// 创建 Key-Value 格式辅助函数，创建一个 Key-Value 格式 JSON 字符串生成器；用完之后，必须使用 InfoHelperRelease 释放 
	void InfoHelperAddKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, const TCHAR* Value);					// 对象信息生成帮助函数，添加 key-value 到对象信息
	void InfoHelperAddIntKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, int Value);						// 对象信息生成帮助函数，添加 key-value 到对象信息
	void InfoHelperGetData(CWALK_HELP_HD HelpHD, LPCTSTR* Buf, int* BufLen);								// 对象信息生成帮助函数，得到缓存区中的数据
	void InfoHelperRelease(CWALK_HELP_HD HelpHD);															// 对象信息生成帮助函数,释放资源

private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::ofstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
};

