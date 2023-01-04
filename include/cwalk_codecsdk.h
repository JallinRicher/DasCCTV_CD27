/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: cwalk_codecsdk.h
///         description:  DCS编解码SDK
///
///
///			create by plh at 2022-02-18
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================

#ifndef __CodecSDK_H__
#define __CodecSDK_H__

#include <Windows.h>
#include "CWALKSDKDefines.h"

typedef struct CWALK_NET_HD__*		CWALK_DECODE_HD;

typedef enum {
	CWALKCODEC_RAWTYPE_UNKOWN = 0,
	CWALKCODEC_RAWTYPE_VIDEO,
	CWALKCODEC_RAWTYPE_AUDIO,
}CWALKCodecRawType;

typedef enum {
	CWALKCODEC_HW_NONE = 0,	// 不使用硬件加速
	CWALKCODEC_HW_INTEL,	// intel 集成显卡
	CWALKCODEC_HW_CUDA,		// 英伟达CUDA架构
	CWALKCODEC_HW_DXVA2,	// Windows DXVA GPU接口（使用DXVA，windows会自动选择有效的GPU进行硬解码）
}CWALKCodecHWAcceType;

typedef enum {
	CWALKCODEC_VCODE_UNKNOWN = 0,
	CWALKCODEC_VCODE_MPEG4,
	CWALKCODEC_VCODE_H263,
	CWALKCODEC_VCODE_H264,
	CWALKCODEC_VCODE_H265,
	CWALKCODEC_VCODE_JPEG = 10,
}CWALKCodecId;

typedef enum {
	CWALKCODEC_PIXFMT_UNKNOW = 0,
	CWALKCODEC_PIXFMT_YUV_420_I,		// 平面		 | Y Y Y Y , U U , V V
	CWALKCODEC_PIXFMT_YUV_420_NV12,		// 平面+打包 | Y Y Y Y , UV UV
	CWALKCODEC_PIXFMT_YUV_420_NV21,		// 平面+打包 | Y Y Y Y , VU VU
	CWALKCODEC_PIXFMT_YUV_420_J,		// 平面 等同于I420，色彩范围稍大于I420
}CWALKCodecPixelFormat;

typedef struct {
	CWALKCodecId codecId;				// 编码格式，UNKOWN表示未知，由编解码器自动探测
	CWALKCodecHWAcceType hwType;		// 硬件加速类型，NONE表示使用CPU软解
	CWALKCodecPixelFormat forcePixFmt;	// 强制像素格式，UNKOWN表不启用
}CWALKCocdecParamSet;

typedef struct {
	CWALKCodecRawType type;
	int format;	// video=CWALKCodecPixelFormat
	// video
	int width;
	int height;
	// audio
	int sampleRate;
	int channels;
	// ex
	long long pts;
}CWALKDCodecRawInfo;

/// 原生（解码后）数据回调函数
/// @param[in] userParam	用户参数
/// @param[in] decHD		解码器句柄
/// @param[in] data			数据首地址
/// @param[in] dataLen		数据长度
/// @param[in] info			数据详细信息
/// @return void
typedef void (CWALK_SDK_CALLBACK *Callback_OnRawData)(
	CWALK_DECODE_HD decHD,
	void* data,
	INT dataLen,
	CWALKDCodecRawInfo info,
	void* userParam
);

/// 创建解码器
/// @param[out] decHD		解码器句柄
/// @param[in] params		解码参数集
/// @param[in] fnData		原生（解码后）数据回调函数指针
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_Create(
	CWALK_DECODE_HD* decHD, 
	CWALKCocdecParamSet params, 
	Callback_OnRawData fnData, 
	void* userParam
);

/// 送数据解码
/// @param[in] decHD		解码器句柄，由CWALK_DEC_Create()返回
/// @param[in] data			dmslice，DCS私有流数据。实时流、录像流、文件流回调数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_InputData(
	CWALK_DECODE_HD decHD, 
	const void* data
);

/// 销毁解码器
/// 注意：不可在向解码器送数据的同时销毁解码器，接口非线程安全
/// @param[in] decHD		解码器句柄，由CWALK_DEC_Create()返回
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_Destory(
	CWALK_DECODE_HD decHD
);

#endif