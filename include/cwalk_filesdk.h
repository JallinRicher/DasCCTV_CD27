/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: cwalk_filesdk.h
///         description:  DCS6.7.1 文件SDK
///
///
///			create by scg at 2012-08
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================

#ifndef _cwalk_filesdk_h_
#define _cwalk_filesdk_h_

#include "CWALKSDKDefines.h"

typedef struct CWALK_FILE_HD__* CWALK_FILE_HD;

//数据类型
typedef enum
{
	CWALKFILE_DATATYPE_H264,
	CWALKFILE_DATATYPE_mpeg4
}CWALKFileDataType;

#ifndef _CWALKNET_STREAM_TYPE
#define _CWALKNET_STREAM_TYPE
typedef enum
{
	CWALKNET_UNKNOWWN_STREAM_TYPE = -3,
	CWALKNET_STREAM_TYPE_OSD = 1,
	CWALKNET_STREAM_TYPE_VIDEO_IKEY = 2,
	CWALKNET_STREAM_TYPE_VIDEO_NOIKEY = 3,

}CWALKNET_STREAM_TYPE;
#endif
//视频类型
#ifndef _CWALKNET_VIDEO_STREAM_TYPE
#define _CWALKNET_VIDEO_STREAM_TYPE
typedef enum
{
	CWALKNET_VIDEO_STREAM_TYPE_UNKONWN = -1,
	CWALKNET_VIDEO_STREAM_TYPE_H261 = 0,
	CWALKNET_VIDEO_STREAM_TYPE_H263,
	CWALKNET_VIDEO_STREAM_TYPE_H263I,
	CWALKNET_VIDEO_STREAM_TYPE_H264,
	CWALKNET_VIDEO_STREAM_TYPE_H265,
	CWALKNET_VIDEO_STREAM_TYPE_MPEG1,
	CWALKNET_VIDEO_STREAM_TYPE_MPEG2,
	CWALKNET_VIDEO_STREAM_TYPE_MPEG2Video,
	CWALKNET_VIDEO_STREAM_TYPE_MPEG2TS,
	CWALKNET_VIDEO_STREAM_TYPE_MPEG4,
	CWALKNET_VIDEO_STREAM_TYPE_AVS,
	CWALKNET_VIDEO_STREAM_TYPE_FLV,
	CWALKNET_VIDEO_STREAM_TYPE_MSMPEG4V1,
	CWALKNET_VIDEO_STREAM_TYPE_MSMPEG4V2,
	CWALKNET_VIDEO_STREAM_TYPE_MSMPEG4V3,
	CWALKNET_VIDEO_STREAM_TYPE_WMV1,
	CWALKNET_VIDEO_STREAM_TYPE_WMV2,
	CWALKNET_VIDEO_STREAM_TYPE_WMV3,
	CWALKNET_VIDEO_STREAM_TYPE_MJPEG,
	CWALKNET_VIDEO_STREAM_TYPE_PNG,
	CWALKNET_VIDEO_STREAM_TYPE_JPEGLS,
	CWALKNET_VIDEO_STREAM_TYPE_SMARTSPYEYE,
	CWALKNET_VIDEO_STREAM_TYPE_VC1,
	CWALKNET_VIDEO_STREAM_TYPE_SVAC1,
}CWALKNET_VIDEO_STREAM_TYPE;
#endif

//音频类型
#ifndef _CWALKNET_AUDIO_STREAM_TYPE
#define _CWALKNET_AUDIO_STREAM_TYPE
typedef enum
{
	CWALKNET_AUDIO_STREAM_TYPE_UNKONWN = -2,
	CWALKNET_AUDIO_STREAM_TYPE_G711A = 200,
	CWALKNET_AUDIO_STREAM_TYPE_MP3,
	CWALKNET_AUDIO_STREAM_TYPE_PCM,
	CWALKNET_AUDIO_STREAM_TYPE_AAC,
	CWALKNET_AUDIO_STREAM_TYPE_G726,
	CWALKNET_AUDIO_STREAM_TYPE_HIKH_G722,
	CWALKNET_AUDIO_STREAM_TYPE_HIKH_G711,
	CWALKNET_AUDIO_STREAM_TYPE_G711M,
	CWALKNET_AUDIO_STREAM_TYPE_G726_ADPCM,
	CWALKNET_AUDIO_STREAM_TYPE_G726_16,
	CWALKNET_AUDIO_STREAM_HIKH_G726_24,
	CWALKNET_AUDIO_STREAM_TYPE_G726_32,
	CWALKNET_AUDIO_STREAM_TYPE_G722_64,
	CWALKNET_AUDIO_STREAM_TYPE_G722_56,
	CWALKNET_AUDIO_STREAM_TYPE_G722_48,
	CWALKNET_AUDIO_STREAM_TYPE_G722_1_32,
	CWALKNET_AUDIO_STREAM_TYPE_G722_1_24,
	CWALKNET_AUDIO_STREAM_TYPE_G726_40,
	CWALKNET_AUDIO_STREAM_TYPE_LLW,
	CWALKNET_AUDIO_STREAM_TYPE_G7231,
	CWALKNET_AUDIO_STREAM_HIKH_HIKH_G711_A,
}CWALKNET_AUDIO_STREAM_TYPE;
#endif


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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetSDK_Version(
	TCHAR* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 初始化SDK
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_Init();

/// 清除SDK资源.
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_Cleanup();


/// 打开可读文件, 文件格式 : .dmf 或 .DMF
/// @param[in]	fileName	要打开的文件名, 如:"D:\test.dmf" 或 "test.dmf"
/// @param[out] readHD		得到打开文件的句柄
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenReadableFile(
	const TCHAR* fileName,
	CWALK_FILE_HD* readHD
	);

/// 关闭可读文件
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseReadableFile(
	CWALK_FILE_HD readHD
	);

/// 得到录像文件第一帧的生成时间
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[out]	time		返回录像第一帧的生成时间，相对于格林威治标准时间(1970-01-01 00:00:00.000)的毫秒数，单位：毫秒
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetBaseTime(
	CWALK_FILE_HD readHD,
	INT64* time
	);

/// 得到录像文件第一帧的生成时间
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[out] buf			返回录像第一帧的生成时间,内存空间由调用者分配,时间格式："2012-01-01 13:20:00.000"
/// @param[in]  bufLen		buf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetStringBaseTime(
	CWALK_FILE_HD readHD,
	TCHAR* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// 从可读文件中读取数据,
/// 注：读出后的数据必须用CWALK_FILE_Free()释放
///		读出的数据为一个完整的slice
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[out]	data		数据指针,使用后必须使用CWALK_FILE_Free()释放
/// @param[out]	len			数据长度
/// @return
///	-	CWALKSDK_OK				成功
/// -	CWALKSDK_ERR_END_OF_FILE	读到文件末尾
///	-	其它					失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReadSlice(
	CWALK_FILE_HD readHD,
	void** data,
	INT* len
	);

/// 释放内存
/// @param[in]	ptr			指针
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_FILE_Free(
	void* ptr
	);

/// 得到文件的总长度
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[out] len			得到文件的总长度,单位:毫秒
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_GetDuration(
	CWALK_FILE_HD readHD,
	DWORD* len
	);

/// 设置文件的读取位置
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[in]	pos			要设置的文件读取位置,单位:毫秒
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_SetPos(
	CWALK_FILE_HD readHD,
	DWORD pos
	);

/// 得到文件的读取位置
/// @param[in]	readHD		可读文件句柄,由CWALK_FILE_OpenReadableFile()获得
/// @param[out] pos			返回文件的读取位置,单位:毫秒
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_GetPos(
	CWALK_FILE_HD readHD,
	DWORD* pos
	);


/// 打开一个可写的文件
/// @param[in]	fileName			文件名,如:"D:\test.dmf" 、 "D:\test.avi" 、 "D:\test.mp4"
/// @param[out] writeHD				得到可写文件句柄
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFile(
	const TCHAR* fileName,
	CWALK_FILE_HD* writeHD
	);

/// 打开一个可写的文件, 文件格式为:avi
/// @param[in]	fileName	文件名,如:"D:\test.avi" 或 "test.avi"
/// @param[out] writeHD		得到可写文件句柄
/// @param[in]  width		视频宽度
/// @param[in]  height		视频高度
/// @param[in]  rate		帧率
/// @param[in]  streamType	码流格式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFileForAVI(
	const TCHAR* fileName,
	CWALK_FILE_HD* writeHD,
	INT width, 
	INT height,
	INT rate,
	UINT64 streamType
	);

/// 设置文件分割大小，在写数据之前调用
/// @param[in]	writeHD		可写文件句柄,由CWALK_FILE_OpenWritbaleFile()或CWALK_FILE_OpenWritbaleFileForAVI()获得
/// @param[in]	size		文件大小，以M为单位，设置范围200M~1.5G
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetFileSize(
	CWALK_FILE_HD writeHD,
	DWORD      size
	);

/// 关闭可写文件
/// @param[in]	writeHD		可写文件句柄,由CWALK_FILE_OpenWritbaleFile()或CWALK_FILE_OpenWritbaleFileForAVI()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseWritableFile(
	CWALK_FILE_HD writeHD
	);


/// 设置播放模式
/// @param[in]	playHD		    可读文件句柄，由CWALK_FILE_OpenReadableFile()获得
/// @param[in]  mode			模式，1正放模式 -1:倒放模式
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetPlayMode(CWALK_FILE_HD readHD, INT mode);

/// 获取播放模式
/// @param[in]	playHD		    可读文件句柄，由CWALK_FILE_OpenReadableFile()获得
/// @param[out]  mode			模式，<0:倒放模式，>=0 正放模式，默认等于0
/// @return 
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetPlayMode(CWALK_FILE_HD readHD, INT* mode);


/// 把数据写入文件
/// 注: data必须为一个完整的slice,可由流传输的回调函数获得
/// @param[in]	writeHD		可写文件句柄,由CWALK_FILE_OpenWritbaleFile()或CWALK_FILE_OpenWritbaleFileForAVI()获得
/// @param[in]	data		数据指针
/// @param[in]	len			数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteData(
	CWALK_FILE_HD writeHD,
	const void* data,
	INT len
);

///创建数据格式转换器
/// @param[in]	data		数据(I帧)
/// @param[in]	size		数据大小
/// @param[out] extractorHD	转换句柄
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CreateExtrator(const void* data, INT size, CWALK_FILE_HD* extractorHD);

/// 获取图像信息
/// @param[out] extractorHD	转换句柄
/// @param[out]  width		视频宽度
/// @param[out]  height		视频高度
/// @param[out]  rate		帧率
/// @param[out]  streamType	码流格式
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetVideoInfo(CWALK_FILE_HD extractorHD, INT* width, INT* height, float* rate, INT* streamType);

///输入数据
/// @param[in] extractorHD	转换句柄
/// @param[in] data		数据流
/// @param[in] size		数据大小
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_InputData(CWALK_FILE_HD extractorHD, const void* data, INT size);

///获取数据
/// @param[in] extractorHD	转换句柄
/// @param[out]  pstream		标准数据流存储区
/// @param[in,out]  len		pstream空间大小，返回实际数据长度
///	-	CWALKSDK_OK	成功
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream空间不够，len返回数据实际需要的空间，用此值再分配空间重新调用一次
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame(CWALK_FILE_HD extractorHD, void* pstreame, INT* len);

///获取数据（可获得数据类型）
/// @param[in] extractorHD	转换句柄
/// @param[out]  pstream		标准数据流存储区
/// @param[in,out]  len		pstream空间大小，返回实际数据长度
/// @param[out]  frametype		0-视频数据，1-音频数据
///	-	CWALKSDK_OK	成功
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream空间不够，len返回数据实际需要的空间，用此值再分配空间重新调用一次
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame2(CWALK_FILE_HD extractorHD, void* pstream, INT* len, INT* frameType);

///获取数据（可获得数据类型及I帧）
/// @param[in] extractorHD	转换句柄
/// @param[out]  pstream		标准数据流存储区
/// @param[in,out]  len		pstream空间大小，返回实际数据长度
/// @param[out]  frametype		0-视频数据，1-音频数据
/// @param[out]  isKey		0-非视频I帧，1-视频I帧
///	-	CWALKSDK_OK	成功
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream空间不够，len返回数据实际需要的空间，用此值再分配空间重新调用一次
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame3(CWALK_FILE_HD extractorHD, void* pstream, INT* len, INT* frameType, BOOL* isKey);

///释放数据格式转换器
/// @param[in] extractorHD	转换句柄
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReleaseExtractor(CWALK_FILE_HD extractorHD);

/// 打开可写AVI文件
/// @param[in] fileName	文件名
/// @param[out] encoderHD	文件句柄
/// @param[in] width	数据宽度
/// @param[in] height	数据高度
/// @param[in] frameRate数据帧率
/// @param[in] streamType	数据类型
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFileForAVI2(const TCHAR* fileName, CWALK_FILE_HD* encodedrHD, INT width, INT height, float frameRate, CWALKFileDataType streamType);

/// 写入AVI文件
/// @param[in] encoderHD 文件句柄
/// @param[in] sream	要写入的数据
/// @param[in] size		数据大小
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI(CWALK_FILE_HD encoderHD, const void* stream, INT size);

/// 写入AVI文件（可写入音频数据）
/// @param[in] encoderHD 文件句柄
/// @param[in] sream	要写入的数据
/// @param[in] size		数据大小
/// @param[in] frameType	0-视频数据，1-音频数据
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI2(CWALK_FILE_HD encoderHD, const void* stream, INT size, INT frameType);

/// 写入AVI文件（每1.5G一个文件保存）
/// @param[in] encoderHD 文件句柄
/// @param[in] sream	要写入的数据
/// @param[in] size		数据大小
/// @param[in] frameType	0-视频数据，1-音频数据
/// @param[out]  isKey		0-非视频I帧，1-视频I帧
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI3(CWALK_FILE_HD encoderHD, const void* stream, INT size, INT frameType, BOOL isKey);

/// 关闭文件
/// @param[in] encoderHD 文件句柄
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseWritebleFileForAVI(CWALK_FILE_HD encoderHD);

/// 写OSD信息到视频文件
/// @param[in] fileName 文件名称路径
/// @param[in] info		OSD信息  //格式遵循：“x|y|文字大小|文字颜色|背景颜色|自动颜色|对齐方式|字体|内容|是否平铺|” 前三个个为小数
/// @param[in] len		信息长度 //长度小于 256字符。
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteOsdInfo(
	const char* fileName, 
	const char* info, 
	int len);

/// 从视频文件读取OSD信息
/// @param[in] fileName 文件名称路径
/// @param[out] info	OSD信息  //格式：“x|y|文字大小|文字颜色|背景颜色|自动颜色|对齐方式|字体|内容|是否平铺|” 前三个个为小数
/// @param[out] len		信息长度 // dmf : 256bit  mp4 : 30bit  avi : 256bit
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReadOsdInfo(
	const char* fileName, 
	char* info,
	int* len);

///读取离线文件添加接口


/// 流数据回调函数,由Callback_File_OnStreamData调用
/// @param[in]	userParam	用户数据
///	@param[in]	readHD		文件句柄
/// @param[in]	data		回调的数据
/// @param[in]	dataLen		数据长度
typedef void (CWALK_SDK_CALLBACK *Callback_File_OnStreamData)(
	void* userParam,	
	CWALK_FILE_HD readHD,
	const void* data,
	DWORD dataLen
	);

/// 离线文件播放消息回调,由CallBack_File_OnStreamMsg调用
/// @param[in] userParam	用户数据
/// @param[in] readHD		文件句柄
/// @param[in] flag			-1  出错，断流等
///							0   数据回调结束
///							1   数据回调开始
///							2   刷新数据，一般是调用CWALK_FILE_SetFileStreamPos后会收到
///							3   断流重开，发生了断流并重新开流
typedef void (CWALK_SDK_CALLBACK *CallBack_File_OnStreamMsg)(
	void* userParam,
	CWALK_FILE_HD readHD,
	INT flag
	);

/// 打开离线文件
/// @param[in] protocol		DCR的协议，dcr、local
/// @param[out] readHD		文件句柄
/// @param[in] ip			云存储IP地址 点分十进制ipv4格式 例:192.168.1.1
/// @param[in] port			云存储TCP端口
/// @param[in] pool			存储池名
/// @param[in] filePath		存储上的路径，例: "/xabasdfas/1.mp4"
/// @param[in] username		DCR的用户名
/// @param[in] password		DCR的密码
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenOfflineFile(
	const TCHAR* protocol, 
	CWALK_FILE_HD* readHD, 
	const TCHAR* ip,
	const WORD   port,
	const TCHAR* pool,
	const TCHAR* filePath,
	const TCHAR* username,
	const TCHAR* password); 

/// 关闭离线文件
/// @param[out] readHD		文件句柄
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseOfflineFile(CWALK_FILE_HD readHD);

/// 获取离线文件的详细信息
/// @param[in]	readHD		文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[out] size	    返回离线视频文件的大小
/// @param[out] duration    返回离线视频文件的长度，单位毫秒
/// @param[out] fps		    返回离线视频文件的帧率
/// @param[out] width		返回离线视频文件的宽
/// @param[out] height		返回离线视频文件的高
/// @param[out] vCodec		返回离线视频文件的视频编码格式
/// @param[out] aCodec		返回离线视频文件的音频编码格式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetOfflineFileInfo(
	CWALK_FILE_HD readHD,
	INT64* size,
	INT64* duration,
	INT*   fps,
	INT*   width,
	INT*   height,
	INT*   vCodec,
	INT*   aCodec
	);

/// 离线文件播放
/// @param[in] readHD		文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[in] beginTime	相对文件的开始时间，单位毫秒
/// @param[in] endTime		相对文件的结束时间，单位毫秒（保留，目前无作用）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnMsg		消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_StartOfflineFileStream(
	CWALK_FILE_HD readHD, 
	const INT beginTime, 
	const INT endTime, 
	Callback_File_OnStreamData fnData, 
	CallBack_File_OnStreamMsg fnMsg, 
	void* userParam
	);

/// 获取离线文件播放进度
/// @param[in]	readHD	文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[out] pos		返回当前的播放进度,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetOfflineFileStreamPos(CWALK_FILE_HD readHD, INT64* pos);

/// 设置离线文件播放位置
/// @param[in]	readHD	文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[in] pos		要设置的播放位置,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFileStreamPos(CWALK_FILE_HD readHD, INT64 pos);

/// 设置播放速度
/// @param[in] readHD	 文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[in]	speed    0代表暂停，其它取值1.0、2.0、4.0、8.0、16.0、32.0、0.5、0.25、0.125、0.0625
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFileStreamSpeed(CWALK_FILE_HD readHD, double speed);

/// 设置离线文件播放模式
/// @param[in] readHD	文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @param[in] mode	模式，>0:正序播放 <0:倒序播放 ==0:缺省模式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFilePlaybackMode(CWALK_FILE_HD readHD, INT32 mode);

/// 停止离线回放
/// @param[in] readHD	文件句柄,由CWALK_FILE_OpenOfflineFile得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_StopOfflineFileStream(CWALK_FILE_HD readHD);


/// slice去头,并解析参数 供filesdk使用
/// @param[in]	srcData		源流数据
/// @param[in]	srcLen		源流数据长度
/// @param[out]	decData		去头后流数据
/// @param[out]	decLen		去头后源流数据长度
/// @param[out]	streamType	流数据类型
/// @param[out]	isIFrame	若为视频数据，是否为I帧
/// @param[out]	pts		    时间戳
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_RemoveSliceHeadWithParam_ForFileSDK(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen,
	INT *streamType,
	INT *isIFrame,
	INT64 *pts);

/// 创建视频滤镜器
/// @param[out]  filterHD	视频滤镜句柄
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CreateVideoFilter(CWALK_FILE_HD* filterHD);

/// 销毁视频滤镜器
/// @param[in]	 filterHD	视频滤镜句柄
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_DestroyVideoFilter(CWALK_FILE_HD filterHD);

/// 视频滤镜处理一帧视频
/// @param[out]  filterHD	视频滤镜句柄
/// @param[in]   srcData	源帧数据，仅支持dmslice（h264、mpeg2、mpeg4）
/// @param[in]   srcDataLen	源帧数据长度
/// @param[in]   pts		帧数据时间戳，此参数暂时废弃，填0即可。
/// @param[out]	 dstData	输出帧数据，内存由使用这创建
/// @param[out]	 dstDataLen 输出帧数据长度
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_VideoFilterDealAFrame(
	CWALK_FILE_HD filterHD,
	const void* srcData,
	const UINT srcDataLen,
	const UINT64 pts,
	void* dstData,
	UINT* dstDataLen);


#endif
