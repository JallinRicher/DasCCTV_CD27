/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: cwalk_playsdk.h
///         description: DCS playerSDK
///
///
///			created by xzq in Aug 2020
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================

#ifndef _cwalk_player_h_
#define _cwalk_player_h_
#include "CWALKSDKDefines.h"

//#define PLAY_SCC

typedef struct CWALK_PLAY_HD__* CWALK_PLAY_HD;

/// OSD类型
typedef enum
{
	CWALKPLAY_OSD_UNKNOW = -1,			///< 未知类型
	CWALKPLAY_OSD_TEXT	= 0,			///< 文本
	CWALKPLAY_OSD_LINE	= 1,			///< 直线
	CWALKPLAY_OSD_RECT	= 2,			///< 放大矩形区域
	CWALKPLAY_OSD_TIME = 3,			///< 时间
	CWALKPLAY_OSD_LOCAL_TIME = 4,		///< 客户端本地时间
} CWALKPLayOSDType;

/// 点
typedef struct
{
	double x1;
	double y1;
} CWALKPLayPoint;

/// OSD文本对齐方式
typedef enum
{
	CWALKPLAY_ALIGNMENT_LEFT = 0X0001,	///< 左对齐
	CWALKPLAY_ALIGNMENT_RIGHT = 0X0002	///< 右对齐
} CWALKPLayOSDTextAlignType;

/// 文本
typedef struct
{
	CWALKPLayPoint point;			///< 文字pos
	TCHAR text[256];			///< 文字
	TCHAR fontFamily[64];		///< 字体族
	BOOL autoColor;				///< 自动绘制颜色
	DWORD color;				///< 文字的颜色
	DWORD backColor;			///< 文字背景颜色
	double fontSize;			///< 字体相对的尺寸
	INT alignment;				///< 对齐方式 见：CWALKPLayOSDTextAlignType
	INT fillWaterMark;			///< osd方式  0 不平铺 1 平铺屏幕
} CWALKPLayOSDText;

/// 线段
typedef struct
{
	double x1;					///< 起点的x坐标，为比例值，范围为[0.0,1.0]，x1=x/width
	double y1;					///< 起点的y坐标，为比例值，范围为[0.0,1.0]，y1=y/height
	double x2;					///< 终点的x坐标，为比例值，范围为[0.0,1.0]，x2=x/width
	double y2;					///< 终点的y坐标，为比例值，范围为[0.0,1.0]，y2=y/height
	DWORD lineWidth;			///< 线段的宽度
	DWORD color;				///< 颜色
}CWALKPLayOSDLine;

/// OSD矩形
typedef struct
{
	double x1;					///< 左上角x坐标，范围为[0.0,1.0]，x1=x/width
	double y1;					///< 左上角y坐标，范围为[0.0,1.0]，y1=y/height
	double w;					///< 宽度，范围为[0.0,1.0]，x2=x/width
	double h;					///< 高度，范围为[0.0,1.0]，y2=y/height
	DWORD lineWidth;			///< 边框的宽度
	DWORD color;				///< 边框的颜色
	DWORD fillColor;			///< 填充的颜色, 特别的0xffffffff表示不填充
} CWALKPLayOSDRect;

/// 解码后的视频数据信息
typedef struct
{
	LONG width;					///< 图像宽度
	LONG height;				///< 图像高度
	LONG type;					///< YUV数据类型 0－YUV420帧，其它－未使用
	INT64 pts;					///< 时间戳
} CWALKPLayFrameInfo;

/// 音频解码后的PCM帧
typedef struct
{
	INT pts;			///< 帧时间戳
	INT channelType;	///< 采样顺序，0－顺序采样，1－交错采样，其它－未使用		
	INT channels;		///< 声道数
	INT bitsPerSample;	///< 每样本位数
	INT samplesPerSec;	///< 每秒样本数
	INT samples;		///< pcm字段指向的采样数据的样本数
	BYTE* pcm;			///< 采样数据
} CWALKPLayPcmFrame;

/// 播放控制命令的类型
typedef enum 
{ 
	CWALKPLAY_CMD_PLAY,			///< 播放
	CWALKPLAY_CMD_PAUSE,			///< 暂停
	CWALKPLAY_CMD_FAST,			///< 快速
	CWALKPLAY_CMD_SLOW,			///< 慢速
	CWALKPLAY_CMD_NORMAL,			///< 正常速度播放
	CWALKPLAY_CMD_FULL,			///< 全速播放
	CWALKPLAY_CMD_FRAME,			///< 单帧播放
	CWALKPLAY_CMD_GETTIME,			///< 获取当前播放的时间戳
	CWALKPLAY_CMD_GETSTATUS,		///< 获取播放状态, 为CWALKPLayControl中定义的类型
	CWALKPLAY_CMD_GETSPEED,		///< 获取播放速度，为CWALKPLaySpeedControl中定义的类型
} CWALKPLayControl;

/// 播放速度控制命令的类型
typedef enum
{
	CWALKPLAY_SPEED_SLOW16 = -4,	///< 慢16倍速播放 
	CWALKPLAY_SPEED_SLOW8  = -3,	///< 慢8倍速播放 
	CWALKPLAY_SPEED_SLOW4  = -2,	///< 慢4倍速播放 
	CWALKPLAY_SPEED_SLOW2  = -1,	///< 慢2倍速播放 
	CWALKPLAY_SPEED_NORMAL = 0,	///< 正常播放 
	CWALKPLAY_SPEED_FAST2  = 1,	///< 快2倍速播放 
	CWALKPLAY_SPEED_FAST4  = 2,	///< 快4倍速播放 
	CWALKPLAY_SPEED_FAST8  = 3,	///< 快8倍速播放  
	CWALKPLAY_SPEED_FAST16 = 4,	///< 快16倍速播放  
	CWALKPLAY_SPEED_FAST32 = 5,	///< 快32倍速播放 暂不支持
} CWALKPLaySpeedControl;

/// 视频增强区域结构体
typedef struct
{
	double x;					///< x坐标，相对于视频播放窗口，取值[0－1]
	double y;					///< y坐标，相对于视频播放窗口，取值[0－1]
	double h;					///< 高度，相对于视频播放窗口，取值[0－1]
	double w;					///< 宽度，相对于视频播放窗口，取值[0－1]
} CWALKPLayEnhanceRect;

/// 视频增强类型
typedef enum 
{
	CWALKPLAY_ILLUMIANTION		= 0x01,		///< 亮度归一化
	CWALKPLAY_SCALEIMAGERANGE	= 0x02,		///< 对比度拉升
	CWALKPLAY_EMPHASIZE		= 0x04,		///< 清晰化
	CWALKPLAY_SMOOTH			= 0x08,		///< 去噪声
	CWALKPLAY_DEHAZE			= 0x10,		///< 去雾
	CWALKPLAY_RETINA			= 0x20,		///< 视网膜算法
	CWALKPLAY_RESTORATION		= 0x40		///< 图像复原算法
} CWALKPLayEnhanceType;

/// 矩型区域
typedef struct
{
	INT x;		///< 矩型x坐标
	INT y;		///< 矩型y坐标
	INT w;		///< 矩型宽度
	INT h;		///< 矩型高度
} CWALKPLayRect;

/// 播放的流类型
typedef enum
{
	CWALKPLAY_STREAMTYPE_REALSTREAM,		///< 实时流
	CWALKPLAY_STREAMTYPE_NONREALSTREAM,	///< 非实时流(播放不使用本地缓存)
	CWALKPLAY_STREAMTYPE_NONREALSTREAMDISK///< 非实时流（播放使用本地缓存）
} CWALKPLayStreamType;

/// 解码失败
typedef enum
{
	CWALKPLAY_DECODE_STATE_OK,			///< 成功解码
	CWALKPLAY_DECODE_STATE_FAILE		///< 解码失败
}CWALKPLayDecodeState;
/// 解码后的状态信息
typedef struct
{
	CWALKPLayDecodeState decodeState; ///< 解码状态
	LONG width;					///< 图像宽度
	LONG height;				///< 图像高度
	INT64 pts;					///< 时间戳
} CWALKPLayStatInfo;

typedef enum
{
	CWALKPLAY_TYPE_UNKNOW = -1,
	CWALKPLAY_HWDECODE_AUTO,
	CWALKPLAY_HWDECODE_INTEL,
	CWALKPLAY_HWDECODE_CUDA,
	CWALKPLAY_HWDECODE_AMD,
	CWALKPLAY_HWDECODE_DXVA
} CWALKPLayHWDecodeType;

typedef enum
{
	CWALKPLAY_AUTO,		///< 软硬解自动调度
	CWALKPLAY_GPUDECODE,	///< 硬解码
	CWALKPLAY_CPUDECODE,	///< 软解吗
	CWALKPLAY_AVCFECODE,	///< AVCF解码库
	CWALKPLAY_HIKDECODE		///< HIK解码库
}CWALKPLayDecodeMode;

typedef enum
{
	CWALKPLAY_FMT_YV12,
	CWALKPLAY_FMT_NV12
} CWALKPLayYUVType;
//批量截图信息
typedef struct {
	INT nCapID;
	CWALKPLayYUVType type;
	INT width; 
	INT height;
} CWALKPLayCaptureInfo;

//解码信息
typedef struct {
	double dFrameRate;
	double fps;
} CWALKPLayDecodeInfo;

/// 获得SDK版本信息
/// @param[out]	infoBuf		得到SDK版本信息,内存空间由调用者分配,返回JSON格式字符串
///     格式说明：
///		{
///			"majorVersion" : X,					 //< 主版本号
///			"minorVersion" : X,					 //< 次版本号
///			"microVersion" : X,					 //< 微版本号
///			"svnVer" : XXXXX					 //< SVN提交版本
///			"svnRange" : XXXXX,					 //< SVN主版本
///			"svnDate" : "2008-08-08 08:08:08",	 //< SVN上传日期
///			"buildDate" : "2008-08-08 08:08:08", //< 编译日期
///		}
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetSDK_Version(
	TCHAR* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 初始化SDK
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_Init();

/// 清除SDK资源
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_Cleanup();

/// 枚举支持硬解类型接口
/// @param[out]  pDecoderTypes 以字符串返回，分配字符串长度64  格式以“|”分隔，如：intel|cuda|amd|dxva|
/// @param[in,out]  nLen			返回字符串长度
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_DetectDecSupports(
	char* pDecoderTypes,
	INT_PTR* nLen);


/// 设置硬解码类型
/// @param[in]	type		硬解码类型
/// @param[out]	isSupport	是否支持
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetHwDecType(
	CWALKPLayHWDecodeType type, 
	INT* isSupport);


/// 视频解码回调函数
/// @param[in]	playHD			播放句柄
/// @param[in]	buf 			解码后数据
/// @param[in]	len				数据长度
/// @param[in]	fInfo			指明图像或声音的信息结构指针
/// @param[in]	userParam		用户设置的回调函数参数
typedef void (CWALK_SDK_CALLBACK* Callback_OnVideoDecodeData)(
	CWALK_PLAY_HD playHD, 
	const void* buf, 
	INT len, 
	const CWALKPLayFrameInfo* fInfo, 
	void* userParam
	);

///检测设备是否支持硬解
/// @param[out] nSupport			是否支持，1 - 支持, 其它 － 不支持
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CheckHwSupport(
	INT *nSupport
	);

/// 创建播放器。使用完后，必须调用CWALK_PLAY_ReleasePlayer()释放
/// @param[out]	playHD			创建的播放句柄
/// @param[in]	hwnd			播放窗口句柄
/// @param[in]  streamType		播放的流类型
/// @param[in]	fnOnDecoder		回调函数指针
/// @param[in]	userParam		用户数据
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreatePlayer(
	CWALK_PLAY_HD* playHD,
	HWND hwnd/* = NULL*/,
	CWALKPLayStreamType streamType,
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// 创建默认使用硬解播放器。使用完后，必须调用CWALK_PLAY_ReleasePlayer()释放
/// @param[out]	playHD			创建的播放句柄
/// @param[in]	hwnd			播放窗口句柄
/// @param[in]  streamType		播放的流类型
/// @param[in]	fnOnDecoder		回调函数指针
/// @param[in]	userParam		用户数据
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateHWPlayer(
	CWALK_PLAY_HD* playHD, 
	HWND hwnd, 
	CWALKPLayStreamType streamType, 
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// 获取当前解码类型
/// @param[in]	playHD			创建的播放句柄
/// @param[out]	decType			硬解码类型, 返回值类型为CWALKPLayDecodeMode
/// @param[out]	hwType			硬解类型，返回值类型为CWALKPLayHWDecodeType
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetDecodeMode(
	CWALK_PLAY_HD playHD, 
	INT* decMode,
	INT* hwType
	);
	
/// 创建播放器。使用完后，必须调用CWALK_PLAY_ReleasePlayer()释放
/// @param[out]	playHD			创建的播放句柄
/// @param[in]	hwnd			播放窗口句柄
/// @param[in]  streamType		播放的流类型
/// @param[in]  decMode			解码类型，CWALKPLayDecodeMode类型
/// @param[in]  hwType			GPU类型， CWALKPLayHWDecodeType类型
/// @param[in]	fnOnDecoder		回调函数指针
/// @param[in]	userParam		用户数据
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreatePlayerEx(
	CWALK_PLAY_HD* playHD, 
	HWND hwnd, 
	CWALKPLayStreamType streamType, 
	INT decMode,
	INT hwType,
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// 释放播放器
/// 注：与CWALK_PLAY_CreatePlayer()对应
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleasePlayer(
	CWALK_PLAY_HD playHD
	);

/// 音频解码回调函数
/// @param[in]	playHD			播放句柄
/// @param[in]	pcmFrame		音频解码帧
/// @param[in]	userParam		用户数据
typedef void (CWALK_SDK_CALLBACK* Callback_OnAudioDecodeData)(
	CWALK_PLAY_HD playHD, 
	CWALKPLayPcmFrame* pcmFrame,	
	void* userParam 
	);

/// 设置音频回调
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	fnOnAudio		音频解码回调函数
/// @param[in]	userParam		用户数据
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetAudioCallback(
	CWALK_PLAY_HD playHD,
	Callback_OnAudioDecodeData fnOnAudio /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// 输入音视频数据
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 data			播放数据，为一个完整的slice
/// @param[in]	 len			数据长度
/// @return 
///	-	CWALKSDK_OK	 成功
/// -	CWALKSDK_ERR_PLAY_FULL_SILCES	 播放缓冲区已满
/// -	CWALKSDK_ERR_PLAY_IS_RELEASED	 播放器资源已经释放，即：CWALK_PLAY_ReleasePlayer()已经被调用
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_InputData(
	CWALK_PLAY_HD playHD, 
	const void* data, 
	INT len
	);

/// 输入音视频数据
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 data			播放数据，一帧h264数据
/// @param[in]	 len			数据长度
/// @param[in]	 bIsAudio		是否音频
/// @return 
///	-	CWALKSDK_OK	 成功
/// -	CWALKSDK_ERR_PLAY_FULL_SILCES	 播放缓冲区已满
/// -	CWALKSDK_ERR_PLAY_IS_RELEASED	 播放器资源已经释放，即：CWALK_PLAY_ReleasePlayer()已经被调用
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_InputH264Data(
	CWALK_PLAY_HD playHD, 
	const void* data, 
	INT len,
	BOOL bIsAudio
	);

/// 获取视频信息
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]  info			解码信息
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetDecodeInfo(
	CWALK_PLAY_HD playHD, 
	CWALKPLayDecodeInfo* info
	);

/// 获取视频信息
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]  width			视频宽度
/// @param[out]  height			视频高度
/// @param[out]  rate			帧率
/// @param[out]  streamType		码流类型
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetVideoInfo(
	CWALK_PLAY_HD playHD, 
	INT* width, 
	INT* height, 
	INT* rate, 
	UINT64* streamType
	);

/// 播放控制
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 cmd			播放控制命令
/// @param[in]	 inParam		输入参数
/// @param[out]	 outParam		要获取的值
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_PlayControl(
	CWALK_PLAY_HD playHD, 
	CWALKPLayControl cmd, 
	const void* inParam /*= NULL*/, 
	void* outParam/*= NULL*/
	);

/// 设置显示区域
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 rect			视频显示区域,rect的x、y、w、h均为0时表示窗口大小
/// @param[in]	 ratio			是否保持视频宽高比；TRUE-保持视频宽高比(必须设rect)，FALSE-不保持视频宽高比
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPane(
	CWALK_PLAY_HD	playHD,
	const CWALKPLayRect* rect/* = NULL*/, 
	BOOL ratio
	);

///	清除播放缓冲区中的数据
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ClearPlayBuffer(
	CWALK_PLAY_HD playHD
	);

/// 抓图
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 fileName	   	文件名称,如:“D:\test.jpg” 或 “test.jpg”
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePicture(
	CWALK_PLAY_HD playHD, 
	const TCHAR* fileName
	);

/// 批量抓图
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]	 capID	   		返回截图句柄
/// @param[in]	 count	   		截图数量
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePictureEx(
	CWALK_PLAY_HD playHD, 
	INT* capID,
	INT	 count
	);

/// 抓图（包含水印）
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 fileName	   	文件名称,如:“D:\test.jpg” 或 “test.jpg”
/// @param[in]	type			OSD类型
/// @param[in]	osdInfo			OSD信息，为CWALKPLayOSDRect、CWALKPLayOSDLine、CWALKPLayOSDText中的一种，与type参数对应
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePictureByOSD(
	CWALK_PLAY_HD playHD, 
	const TCHAR* fileName,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

/// 声音控制,允许/禁止声音播放,库初始化为允许
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 enable			TRUE - 允许，FALSE - 禁止
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SoundEnable(
	CWALK_PLAY_HD playHD, 
	BOOL enable
	);

///	获取声音控制状态
/// @param[in]	 playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]	 enable			TRUE - 允许，FALSE - 禁止
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SoundIsEnable(
	CWALK_PLAY_HD playHD, 
	BOOL* enable
	);

///	获取色彩值
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]	 brightness	    亮度，  值为[-127,127]
/// @param[out]	 contrast		对比度，值为[-127,127]
/// @param[out]	 saturation	    饱和度，值为[-127,127]
/// @param[out]	 hue			色调，  值为[-127,127]
/// @return 
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetColor(
	CWALK_PLAY_HD playHD, 
	INT* brightness, 
	INT* contrast, 
	INT* saturation, 
	INT* hue
	);

///	设置色彩值
/// @param[in]	 playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	 brightness		亮度，  值为[-127,127]
/// @param[in]	 contrast		对比度，值为[-127,127]
/// @param[in]	 saturation	    饱和度，值为[-127,127]
/// @param[in]	 hue			色调，  值为[-127,127]
/// @return
///	-	CWALKSDK_OK     成功
///	-	其它	     失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetColor(
	CWALK_PLAY_HD playHD, 
	INT brightness, 
	INT contrast, 
	INT saturation, 
	INT hue
	);

///	创建数字放大区域
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]	zoomHD			创建的数字放大区域句柄
/// @param[in]	rect			数字放大区域信息
/// @param[in]	hwnd			放大后的窗口句柄
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateZoomRect(
	CWALK_PLAY_HD playHD,
	CWALK_PLAY_HD* zoomHD,
	const CWALKPLayOSDRect* rect,
	HWND hwnd
	);

///	获取数字放大区域信息
/// @param[in]	zoomHD			 数字放大区域句柄，由CWALK_PLAY_CreateZoomRect()获得
/// @param[out]	rect			 存放要得到的数子放大区域信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetZoomRect(
	CWALK_PLAY_HD zoomHD,
	CWALKPLayOSDRect* rect
	);

///	设置数字放大区域信息
/// @param[in]	zoomHD			数字放大区域句柄，由CWALK_PLAY_CreateZoomRect()获得
/// @param[in]	rect			要设置的数字放大区域信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetZoomRect(
	CWALK_PLAY_HD zoomHD, 
	const CWALKPLayOSDRect* rect
	);

///	释放数字放大区域
/// @param[in]	zoomHD			数字放大区域句柄，由CWALK_PLAY_CreateZoomRect()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseZoomRect( 
	CWALK_PLAY_HD zoomHD
	);

/// 获取视频中OSD信息回调函数
/// @param[in]	playHD		播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	userParam	用户数据
/// @param[in]	id			OSD标识，在同一路视频中唯一标识一个OSD信息。
/// @param[in]	osdType		OSD类型
/// @param[in]	osdInfo		OSD信息，以JSON格式描述
/// @return
///	-	TRUE		继续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK* Callback_OnGetStreamOSDInfo)(
	CWALK_PLAY_HD playHD,
	void* userParam,
	INT id,	
	CWALKPLayOSDType osdType,
	const TCHAR* osdInfo
	);

/// 获取视频流中的OSD信息
/// @param[in]	playHD		播放句柄，由CWALK_PLAY_CreatePlayer()获得
///	@param[in]	fnOnGetOSDInfo	OSD信息回调函数
///	@param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetStreamOSDInfo( 
	CWALK_PLAY_HD playHD,
	Callback_OnGetStreamOSDInfo fnOnGetOSDInfo,
	void* userParam /*= NULL*/
	);

/// 关闭/显示视频流中的OSD信息  
/// 当id为－1时，表示关闭/显示所有OSD信息,重新设置有效id后，恢复部分控制功能
/// @param[in]	playHD		播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	id			OSD标识
/// @param[in]	enable		TRUE－显示，FALSE－不显示
/// @return
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StreamOSDInfoEnable( 
	CWALK_PLAY_HD playHD,
	INT id,
	BOOL enable
	);

///	创建OSD
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]	osdHD			创建的OSD句柄
/// @param[in]	type			OSD类型
/// @param[in]	osdInfo			OSD信息，为CWALKPLayOSDRect、CWALKPLayOSDLine、CWALKPLayOSDText中的一种，与type参数对应
/// @return
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateOSD(
	CWALK_PLAY_HD playHD, 
	CWALK_PLAY_HD* osdHD,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

///	获取OSD信息
/// @param[in]	osdHD			OSD句柄，由CWALK_PLAY_CreateOSD()获得
/// @param[in]	type			OSD类型
/// @param[out]	osdInfo			OSD信息，为CWALKPLayOSDRect、CWALKPLayOSDLine、CWALKPLayOSDText中的一种，与type参数对应
///									所指向的内存空间由调用者分配/释放
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetOSD(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type,
	void* osdInfo
	);

///	设置OSD信息
/// @param[in]	osdHD			OSD句柄，由CWALK_PLAY_CreateOSD()获得
/// @param[in]	type			OSD类型
/// @param[in]	osdInfo			OSD信息，为CWALKPLayOSDRect、CWALKPLayOSDLine、CWALKPLayOSDText中的一种，与type参数对应
/// @return
///	-	CWALKSDK_OK	 成功
///	-	其它		 失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetOSD(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

///	释放OSD
/// @param[in]	osdHD			OSD句柄，由CWALK_PLAY_CreateOSD()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseOSD(
	CWALK_PLAY_HD osdHD
	);

/// 开始同步OSD信息到当前解码模式下
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSyncOSDnCurrentDecMode(
	CWALK_PLAY_HD playHD
	);

/// 将OSD信息同步到当前解码模式下
/// @param[in]	osdHD			OSD句柄，由CWALK_PLAY_CreateOSD()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SyncOSDO(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type
	);

/// 开始同步Zoom信息到当前解码模式下
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSyncZoomOnCurrentDecMode(
	CWALK_PLAY_HD playHD
	);

/// 将数字放大同步到当前解码模式下
/// @param[in]	zoomHD			数字放大区域句柄，由CWALK_PLAY_CreateZoomRect()获得
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SyncZoom(
	CWALK_PLAY_HD zoomHD
	);

/// 虚拟云台控制
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	inputBuf		输入参数
/// @param[in]	inputBufSize	输入参数内存大小
/// @param[out]	outBuf			输出参数
/// @param[in,out]	outBufSize	输出参数内存大小，返回真是大小
CWALK_SDK_API	CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_VirtualPTZControl(
	CWALK_PLAY_HD playHD,
	const void* inputBuf,
	INT inputBufSize,
	void* outBuf,
	INT* outBufSize
	);

/// 亮度归一化函数，用于场景内明暗差异过大的图像
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	nMaskWidth		局部平滑宽度，推荐 30，范围[1-100]
/// @param[in]	nMaskHeight		局部平滑高度，推荐 30，范围[1-100]
/// @param[in]	factor			局部平滑宽度，推荐 0.7，范围[0.1－2]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetIllumination(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth/* = 101*/,
	INT maskHeight/* = 101*/,
	double factor/* = 0.7*/
	);

/// 对比度拉升函数，用于对比度较小的图像
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	min				局部平滑宽度，推荐 30， 范围[1－100]
/// @param[in]	max				局部平滑高度，推荐 80，范围[1－100]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
/// 注： max > min
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetScaleImageRange(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT min/* = 30*/,
	INT max/* = 240*/
	);

/// 清晰化函数，用于模糊的图像
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	maskWidth		局部加强宽度，推荐 7，范围[1－100]
/// @param[in]	maskHeight		局不加强高度，推荐 7，范围[1－100]
/// @param[in]	factor			局部加强幅度，推荐 50，范围[1－100]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetEmphasize(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth/* = 7*/,
	INT maskHeight/* = 7*/,
	double factor/* = 1*/
	);

/// 去噪声函数，用于噪点较大的图像的图像
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	maskWidth		局部加强宽度，推荐 7，范围[1－100]
/// @param[in]	maskHeight		局不加强高度，推荐 7，范围[1－100]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetSmooth(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth,
	INT maskHeight,
	double factor
	);

/// 去雾函数，用于有雾，有沙尘的图像
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	transMin		去雾强度，推荐 60，范围[1－100]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetDehaze(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	double transMin/* = 0.6*/
	);

/// 视网膜算法函数，用于严重逆光
/// 注：算法速度较慢，尽量只对图像局部处于进行处理
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRetina(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect
	);

/// 图像复原算法，用于离焦、运动模糊
/// 注：算法速度较慢，尽量只对图像局部处于进行处理
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]	blurring		图像模糊程度，推荐 5，范围[1－18]
/// @param[in]	angle			运动模糊有效，推荐 0，范围[0－360]
/// @param[in]	type			模糊种类，0－离焦、1－运动、其它－未使用
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRestoration(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT blurring,
	double angle,
	INT type
	);

/// 取消图像增强
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]	rect			图像增强区域
/// @param[in]  enhanceType		图像增强类型，CWALKPLayEnhanceType类型的或值
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_DelEnhance(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT enhanceType
	);

/// 在窗口之上绘制矩形
/// 注：此功能不会修改YUV数据
/// @param[in]	playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out] rectHD			获取创建的矩形句柄
/// @param[in]	rect			矩形参数信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateRectOnWindow(
	CWALK_PLAY_HD playHD, 
	CWALK_PLAY_HD* rectHD,
	const CWALKPLayOSDRect* rect 
	);

/// 重设窗口上的矩形参数
/// @param[in]	rectHD			矩形句柄,由CWALK_PLAY_CreateRectOnWindow()获得
/// @param[in]	rect			矩形参数信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRectOnWindow(
	CWALK_PLAY_HD rectHD,
	const CWALKPLayOSDRect* rect
	);

/// 获取窗口上的矩形参数
/// @param[in]	rectHD			矩形句柄,由CWALK_PLAY_CreateRectOnWindow()获得
/// @param[out]	rect			矩形参数信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetRectOnWindow(
	CWALK_PLAY_HD rectHD,
	CWALKPLayOSDRect* rect 
	);

/// 释放窗口上的矩形
/// @param[in]	rectHD			矩形句柄,由CWALK_PLAY_CreateRectOnWindow()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseRectOnWindow(
	CWALK_PLAY_HD rectHD
	);


/// 音频采集回调函数
/// @param[in]  channels		通道数
/// @param[in]  bitsPerSample	每样本位数
/// @param[in]  channels		每秒样本数
/// @param[in]	buf				音频数据
/// @param[in]	size			音频数据长度
/// @param[in]	userParam		用户设置的回调函数参数
typedef void (CWALK_SDK_CALLBACK* Callback_OnAudioInData)(
	INT channels,
	INT bitsPerSample,
	INT samplesPerSec,
	BYTE* buf, 
	INT size,
	void* userParam
	);

/// 打开系统默认的音频采集设备
/// 注：只可打开一次; 默认打开设备后为Stop状态
/// @param[in]  channels		通道数
/// @param[in]  bitsPerSample	每样本位数
/// @param[in]  channels		每秒样本数
/// @param[in]  fnCallBack		采集完一个buffer时的数据处理回调通知函数
/// @param[in]  userParam		回调函数用户参数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_OpenSystemAudioIn(
	INT channels/* = 1*/,
	INT bitsPerSample/* = 16*/,
	INT samplesPerSec/* = 8000*/,
	Callback_OnAudioInData fnCallBack,
	void* userParam/* = NULL*/
	);

/// 开始采集音频数据
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSystemAudioIn();

/// 停止采集音频数据
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StopSystemAudioIn();

/// 关闭系统默认的音频采集设备
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_CloseSystemAudioIn();


/// 获取系统主音量, 取值范围: [0 - 0xFFFF]
/// @param[out] volume			高8位为左声道, 低8位为右声道
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetMasterVolume(
	INT* volume
	);

///设置系统主音量, 取值范围: [0 - 0xFFFF]
/// @param[in]  volume			高8位为左声道, 低8位为右声道
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetMasterVolume(
	INT volume
	);

/// 设置系统主音量静音
/// @param[in]  mute			是否静音，1 - 静音, 0 - 取消静音, 其它 － 未使用
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetMasterVolumeMute(
	INT mute
	);

///获取系统主音量静音
/// @param[out] mute			是否静音，1 - 静音, 0 - 取消静音，其它 － 未使用
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetMasterVolumeMute(
	INT* mute
	);

typedef void (CWALK_SDK_CALLBACK* Callback_OnDecodeState)(
	CWALK_PLAY_HD playHD,
	const CWALKPLayStatInfo* fInfo, 
	void* userParam
	);

CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetDecodeStateCallBack(
	CWALK_PLAY_HD playHD, 
	Callback_OnDecodeState fnDecState,
	void* userParam
	);

/// 批量截图yuv数据回调函数
/// @param[in]		playHD			播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]		data			yuv数据
/// @param[out]		nLen			yuv长度
/// @param[out]		Info			yuv参数信息
/// @param[in]		userParam		用户设置的回调函数参数
typedef void (CWALK_SDK_CALLBACK* Callback_OnImageData)(
	CWALK_PLAY_HD playHD,
	const CHAR* data,
	INT nLen,
	CWALKPLayCaptureInfo* Info, 
	void* userParam
	);
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetImageCallback(
	CWALK_PLAY_HD playHD, 
	Callback_OnImageData fnImageData,
	void* userParam
	);

/// 无效接口
typedef void (CWALK_SDK_CALLBACK* Callback_OnInputData)(
	INT count, 
	void* userParam
	);
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetInputDataCallBack(
	CWALK_PLAY_HD playHD, 
	Callback_OnInputData fnInputData,
	void* userParam
	);
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ResetInputDataFlag(
	CWALK_PLAY_HD playHD
	);

//////////////////////////////////////////////////////////////////////////
/// v2.0 added
/// >>>> 2014/6/10 Xialiming


/// 设置播放时段
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]  beginTime		播放起始时间
/// @param[in]  endTime		播放结束时间
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPlayTimeSeg(CWALK_PLAY_HD playHD, INT64 beginTime, INT64 endTime);

/// 获取播放时段
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]  beginTime		播放起始时间
/// @param[out]  endTime			播放结束时间
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetPlayTimeSeg(CWALK_PLAY_HD playHD, INT64* beginTime, INT64* endTime);

/// 设置播放模式
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[in]  mode			播放模式，1正放；-1倒放模式，
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPlayMode(
	CWALK_PLAY_HD playHD, 
	INT mode);

/// 获取播放模式
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]  mode			播放模式，1正放；-1倒放模式，
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetPlayMode(
	CWALK_PLAY_HD playHD, 
	INT* mode);


/// 设置当前获取YUV的状态
/// @param[in]	playHD		    播放句柄，由CWALK_PLAY_CreatePlayer()获得
/// @param[out]  bStop			TRUE,不在获取YUV数据
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetYUVCallStatus(CWALK_PLAY_HD playHD, BOOL bStop);


#endif	//_cwalk_player_h_
