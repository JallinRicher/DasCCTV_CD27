/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
///			All rights reserved
///
///
///			filename: cwalk_codecsdk.h
///         description:  DCS�����SDK
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
	CWALKCODEC_HW_NONE = 0,	// ��ʹ��Ӳ������
	CWALKCODEC_HW_INTEL,	// intel �����Կ�
	CWALKCODEC_HW_CUDA,		// Ӣΰ��CUDA�ܹ�
	CWALKCODEC_HW_DXVA2,	// Windows DXVA GPU�ӿڣ�ʹ��DXVA��windows���Զ�ѡ����Ч��GPU����Ӳ���룩
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
	CWALKCODEC_PIXFMT_YUV_420_I,		// ƽ��		 | Y Y Y Y , U U , V V
	CWALKCODEC_PIXFMT_YUV_420_NV12,		// ƽ��+��� | Y Y Y Y , UV UV
	CWALKCODEC_PIXFMT_YUV_420_NV21,		// ƽ��+��� | Y Y Y Y , VU VU
	CWALKCODEC_PIXFMT_YUV_420_J,		// ƽ�� ��ͬ��I420��ɫ�ʷ�Χ�Դ���I420
}CWALKCodecPixelFormat;

typedef struct {
	CWALKCodecId codecId;				// �����ʽ��UNKOWN��ʾδ֪���ɱ�������Զ�̽��
	CWALKCodecHWAcceType hwType;		// Ӳ���������ͣ�NONE��ʾʹ��CPU���
	CWALKCodecPixelFormat forcePixFmt;	// ǿ�����ظ�ʽ��UNKOWN������
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

/// ԭ������������ݻص�����
/// @param[in] userParam	�û�����
/// @param[in] decHD		���������
/// @param[in] data			�����׵�ַ
/// @param[in] dataLen		���ݳ���
/// @param[in] info			������ϸ��Ϣ
/// @return void
typedef void (CWALK_SDK_CALLBACK *Callback_OnRawData)(
	CWALK_DECODE_HD decHD,
	void* data,
	INT dataLen,
	CWALKDCodecRawInfo info,
	void* userParam
);

/// ����������
/// @param[out] decHD		���������
/// @param[in] params		���������
/// @param[in] fnData		ԭ������������ݻص�����ָ��
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_Create(
	CWALK_DECODE_HD* decHD, 
	CWALKCocdecParamSet params, 
	Callback_OnRawData fnData, 
	void* userParam
);

/// �����ݽ���
/// @param[in] decHD		�������������CWALK_DEC_Create()����
/// @param[in] data			dmslice��DCS˽�������ݡ�ʵʱ����¼�������ļ����ص�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_InputData(
	CWALK_DECODE_HD decHD, 
	const void* data
);

/// ���ٽ�����
/// ע�⣺������������������ݵ�ͬʱ���ٽ��������ӿڷ��̰߳�ȫ
/// @param[in] decHD		�������������CWALK_DEC_Create()����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_DEC_Destory(
	CWALK_DECODE_HD decHD
);

#endif