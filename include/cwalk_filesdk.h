/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
///			All rights reserved
///
///
///			filename: cwalk_filesdk.h
///         description:  DCS6.7.1 �ļ�SDK
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

//��������
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
//��Ƶ����
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

//��Ƶ����
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


/// ���SDK�汾��Ϣ
/// @param[out]	infoBuf		�õ�SDK�汾��Ϣ,�ڴ�ռ��ɵ����߷���,����JSON��ʽ�ַ���
///     ��ʽ˵����
///		{
///			"majorVersion" : X,					 //< ���汾��
///			"minorVersion" : X,					 //< �ΰ汾��
///			"microVersion" : X,					 //< ΢�汾��
///			"svnVer" : XXXXX					 //< SVN�ύ�汾
///			"svnRange" : XXXXX,					 //< SVN���汾
///			"svnDate" : "2008-08-08 08:08:08",	 //< SVN�ϴ�����
///			"buildDate" : "2008-08-08 08:08:08", //< ��������
///		}
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetSDK_Version(
	TCHAR* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ��ʼ��SDK
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_Init();

/// ���SDK��Դ.
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_Cleanup();


/// �򿪿ɶ��ļ�, �ļ���ʽ : .dmf �� .DMF
/// @param[in]	fileName	Ҫ�򿪵��ļ���, ��:"D:\test.dmf" �� "test.dmf"
/// @param[out] readHD		�õ����ļ��ľ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenReadableFile(
	const TCHAR* fileName,
	CWALK_FILE_HD* readHD
	);

/// �رտɶ��ļ�
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseReadableFile(
	CWALK_FILE_HD readHD
	);

/// �õ�¼���ļ���һ֡������ʱ��
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[out]	time		����¼���һ֡������ʱ�䣬����ڸ������α�׼ʱ��(1970-01-01 00:00:00.000)�ĺ���������λ������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetBaseTime(
	CWALK_FILE_HD readHD,
	INT64* time
	);

/// �õ�¼���ļ���һ֡������ʱ��
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[out] buf			����¼���һ֡������ʱ��,�ڴ�ռ��ɵ����߷���,ʱ���ʽ��"2012-01-01 13:20:00.000"
/// @param[in]  bufLen		buf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetStringBaseTime(
	CWALK_FILE_HD readHD,
	TCHAR* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// �ӿɶ��ļ��ж�ȡ����,
/// ע������������ݱ�����CWALK_FILE_Free()�ͷ�
///		����������Ϊһ��������slice
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[out]	data		����ָ��,ʹ�ú����ʹ��CWALK_FILE_Free()�ͷ�
/// @param[out]	len			���ݳ���
/// @return
///	-	CWALKSDK_OK				�ɹ�
/// -	CWALKSDK_ERR_END_OF_FILE	�����ļ�ĩβ
///	-	����					ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReadSlice(
	CWALK_FILE_HD readHD,
	void** data,
	INT* len
	);

/// �ͷ��ڴ�
/// @param[in]	ptr			ָ��
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_FILE_Free(
	void* ptr
	);

/// �õ��ļ����ܳ���
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[out] len			�õ��ļ����ܳ���,��λ:����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_GetDuration(
	CWALK_FILE_HD readHD,
	DWORD* len
	);

/// �����ļ��Ķ�ȡλ��
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[in]	pos			Ҫ���õ��ļ���ȡλ��,��λ:����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_SetPos(
	CWALK_FILE_HD readHD,
	DWORD pos
	);

/// �õ��ļ��Ķ�ȡλ��
/// @param[in]	readHD		�ɶ��ļ����,��CWALK_FILE_OpenReadableFile()���
/// @param[out] pos			�����ļ��Ķ�ȡλ��,��λ:����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_FILE_GetPos(
	CWALK_FILE_HD readHD,
	DWORD* pos
	);


/// ��һ����д���ļ�
/// @param[in]	fileName			�ļ���,��:"D:\test.dmf" �� "D:\test.avi" �� "D:\test.mp4"
/// @param[out] writeHD				�õ���д�ļ����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFile(
	const TCHAR* fileName,
	CWALK_FILE_HD* writeHD
	);

/// ��һ����д���ļ�, �ļ���ʽΪ:avi
/// @param[in]	fileName	�ļ���,��:"D:\test.avi" �� "test.avi"
/// @param[out] writeHD		�õ���д�ļ����
/// @param[in]  width		��Ƶ���
/// @param[in]  height		��Ƶ�߶�
/// @param[in]  rate		֡��
/// @param[in]  streamType	������ʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFileForAVI(
	const TCHAR* fileName,
	CWALK_FILE_HD* writeHD,
	INT width, 
	INT height,
	INT rate,
	UINT64 streamType
	);

/// �����ļ��ָ��С����д����֮ǰ����
/// @param[in]	writeHD		��д�ļ����,��CWALK_FILE_OpenWritbaleFile()��CWALK_FILE_OpenWritbaleFileForAVI()���
/// @param[in]	size		�ļ���С����MΪ��λ�����÷�Χ200M~1.5G
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetFileSize(
	CWALK_FILE_HD writeHD,
	DWORD      size
	);

/// �رտ�д�ļ�
/// @param[in]	writeHD		��д�ļ����,��CWALK_FILE_OpenWritbaleFile()��CWALK_FILE_OpenWritbaleFileForAVI()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseWritableFile(
	CWALK_FILE_HD writeHD
	);


/// ���ò���ģʽ
/// @param[in]	playHD		    �ɶ��ļ��������CWALK_FILE_OpenReadableFile()���
/// @param[in]  mode			ģʽ��1����ģʽ -1:����ģʽ
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetPlayMode(CWALK_FILE_HD readHD, INT mode);

/// ��ȡ����ģʽ
/// @param[in]	playHD		    �ɶ��ļ��������CWALK_FILE_OpenReadableFile()���
/// @param[out]  mode			ģʽ��<0:����ģʽ��>=0 ����ģʽ��Ĭ�ϵ���0
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetPlayMode(CWALK_FILE_HD readHD, INT* mode);


/// ������д���ļ�
/// ע: data����Ϊһ��������slice,����������Ļص��������
/// @param[in]	writeHD		��д�ļ����,��CWALK_FILE_OpenWritbaleFile()��CWALK_FILE_OpenWritbaleFileForAVI()���
/// @param[in]	data		����ָ��
/// @param[in]	len			���ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteData(
	CWALK_FILE_HD writeHD,
	const void* data,
	INT len
);

///�������ݸ�ʽת����
/// @param[in]	data		����(I֡)
/// @param[in]	size		���ݴ�С
/// @param[out] extractorHD	ת�����
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CreateExtrator(const void* data, INT size, CWALK_FILE_HD* extractorHD);

/// ��ȡͼ����Ϣ
/// @param[out] extractorHD	ת�����
/// @param[out]  width		��Ƶ���
/// @param[out]  height		��Ƶ�߶�
/// @param[out]  rate		֡��
/// @param[out]  streamType	������ʽ
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetVideoInfo(CWALK_FILE_HD extractorHD, INT* width, INT* height, float* rate, INT* streamType);

///��������
/// @param[in] extractorHD	ת�����
/// @param[in] data		������
/// @param[in] size		���ݴ�С
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_InputData(CWALK_FILE_HD extractorHD, const void* data, INT size);

///��ȡ����
/// @param[in] extractorHD	ת�����
/// @param[out]  pstream		��׼�������洢��
/// @param[in,out]  len		pstream�ռ��С������ʵ�����ݳ���
///	-	CWALKSDK_OK	�ɹ�
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream�ռ䲻����len��������ʵ����Ҫ�Ŀռ䣬�ô�ֵ�ٷ���ռ����µ���һ��
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame(CWALK_FILE_HD extractorHD, void* pstreame, INT* len);

///��ȡ���ݣ��ɻ���������ͣ�
/// @param[in] extractorHD	ת�����
/// @param[out]  pstream		��׼�������洢��
/// @param[in,out]  len		pstream�ռ��С������ʵ�����ݳ���
/// @param[out]  frametype		0-��Ƶ���ݣ�1-��Ƶ����
///	-	CWALKSDK_OK	�ɹ�
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream�ռ䲻����len��������ʵ����Ҫ�Ŀռ䣬�ô�ֵ�ٷ���ռ����µ���һ��
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame2(CWALK_FILE_HD extractorHD, void* pstream, INT* len, INT* frameType);

///��ȡ���ݣ��ɻ���������ͼ�I֡��
/// @param[in] extractorHD	ת�����
/// @param[out]  pstream		��׼�������洢��
/// @param[in,out]  len		pstream�ռ��С������ʵ�����ݳ���
/// @param[out]  frametype		0-��Ƶ���ݣ�1-��Ƶ����
/// @param[out]  isKey		0-����ƵI֡��1-��ƵI֡
///	-	CWALKSDK_OK	�ɹ�
/// -	CWALKSDK_ERR_NOT_ENOUGH_MEM pstream�ռ䲻����len��������ʵ����Ҫ�Ŀռ䣬�ô�ֵ�ٷ���ռ����µ���һ��
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_NextFrame3(CWALK_FILE_HD extractorHD, void* pstream, INT* len, INT* frameType, BOOL* isKey);

///�ͷ����ݸ�ʽת����
/// @param[in] extractorHD	ת�����
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReleaseExtractor(CWALK_FILE_HD extractorHD);

/// �򿪿�дAVI�ļ�
/// @param[in] fileName	�ļ���
/// @param[out] encoderHD	�ļ����
/// @param[in] width	���ݿ��
/// @param[in] height	���ݸ߶�
/// @param[in] frameRate����֡��
/// @param[in] streamType	��������
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenWritbaleFileForAVI2(const TCHAR* fileName, CWALK_FILE_HD* encodedrHD, INT width, INT height, float frameRate, CWALKFileDataType streamType);

/// д��AVI�ļ�
/// @param[in] encoderHD �ļ����
/// @param[in] sream	Ҫд�������
/// @param[in] size		���ݴ�С
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI(CWALK_FILE_HD encoderHD, const void* stream, INT size);

/// д��AVI�ļ�����д����Ƶ���ݣ�
/// @param[in] encoderHD �ļ����
/// @param[in] sream	Ҫд�������
/// @param[in] size		���ݴ�С
/// @param[in] frameType	0-��Ƶ���ݣ�1-��Ƶ����
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI2(CWALK_FILE_HD encoderHD, const void* stream, INT size, INT frameType);

/// д��AVI�ļ���ÿ1.5Gһ���ļ����棩
/// @param[in] encoderHD �ļ����
/// @param[in] sream	Ҫд�������
/// @param[in] size		���ݴ�С
/// @param[in] frameType	0-��Ƶ���ݣ�1-��Ƶ����
/// @param[out]  isKey		0-����ƵI֡��1-��ƵI֡
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteDataForAVI3(CWALK_FILE_HD encoderHD, const void* stream, INT size, INT frameType, BOOL isKey);

/// �ر��ļ�
/// @param[in] encoderHD �ļ����
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseWritebleFileForAVI(CWALK_FILE_HD encoderHD);

/// дOSD��Ϣ����Ƶ�ļ�
/// @param[in] fileName �ļ�����·��
/// @param[in] info		OSD��Ϣ  //��ʽ��ѭ����x|y|���ִ�С|������ɫ|������ɫ|�Զ���ɫ|���뷽ʽ|����|����|�Ƿ�ƽ��|�� ǰ������ΪС��
/// @param[in] len		��Ϣ���� //����С�� 256�ַ���
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_WriteOsdInfo(
	const char* fileName, 
	const char* info, 
	int len);

/// ����Ƶ�ļ���ȡOSD��Ϣ
/// @param[in] fileName �ļ�����·��
/// @param[out] info	OSD��Ϣ  //��ʽ����x|y|���ִ�С|������ɫ|������ɫ|�Զ���ɫ|���뷽ʽ|����|����|�Ƿ�ƽ��|�� ǰ������ΪС��
/// @param[out] len		��Ϣ���� // dmf : 256bit  mp4 : 30bit  avi : 256bit
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_ReadOsdInfo(
	const char* fileName, 
	char* info,
	int* len);

///��ȡ�����ļ���ӽӿ�


/// �����ݻص�����,��Callback_File_OnStreamData����
/// @param[in]	userParam	�û�����
///	@param[in]	readHD		�ļ����
/// @param[in]	data		�ص�������
/// @param[in]	dataLen		���ݳ���
typedef void (CWALK_SDK_CALLBACK *Callback_File_OnStreamData)(
	void* userParam,	
	CWALK_FILE_HD readHD,
	const void* data,
	DWORD dataLen
	);

/// �����ļ�������Ϣ�ص�,��CallBack_File_OnStreamMsg����
/// @param[in] userParam	�û�����
/// @param[in] readHD		�ļ����
/// @param[in] flag			-1  ����������
///							0   ���ݻص�����
///							1   ���ݻص���ʼ
///							2   ˢ�����ݣ�һ���ǵ���CWALK_FILE_SetFileStreamPos����յ�
///							3   �����ؿ��������˶��������¿���
typedef void (CWALK_SDK_CALLBACK *CallBack_File_OnStreamMsg)(
	void* userParam,
	CWALK_FILE_HD readHD,
	INT flag
	);

/// �������ļ�
/// @param[in] protocol		DCR��Э�飬dcr��local
/// @param[out] readHD		�ļ����
/// @param[in] ip			�ƴ洢IP��ַ ���ʮ����ipv4��ʽ ��:192.168.1.1
/// @param[in] port			�ƴ洢TCP�˿�
/// @param[in] pool			�洢����
/// @param[in] filePath		�洢�ϵ�·������: "/xabasdfas/1.mp4"
/// @param[in] username		DCR���û���
/// @param[in] password		DCR������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_OpenOfflineFile(
	const TCHAR* protocol, 
	CWALK_FILE_HD* readHD, 
	const TCHAR* ip,
	const WORD   port,
	const TCHAR* pool,
	const TCHAR* filePath,
	const TCHAR* username,
	const TCHAR* password); 

/// �ر������ļ�
/// @param[out] readHD		�ļ����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CloseOfflineFile(CWALK_FILE_HD readHD);

/// ��ȡ�����ļ�����ϸ��Ϣ
/// @param[in]	readHD		�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[out] size	    ����������Ƶ�ļ��Ĵ�С
/// @param[out] duration    ����������Ƶ�ļ��ĳ��ȣ���λ����
/// @param[out] fps		    ����������Ƶ�ļ���֡��
/// @param[out] width		����������Ƶ�ļ��Ŀ�
/// @param[out] height		����������Ƶ�ļ��ĸ�
/// @param[out] vCodec		����������Ƶ�ļ�����Ƶ�����ʽ
/// @param[out] aCodec		����������Ƶ�ļ�����Ƶ�����ʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
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

/// �����ļ�����
/// @param[in] readHD		�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[in] beginTime	����ļ��Ŀ�ʼʱ�䣬��λ����
/// @param[in] endTime		����ļ��Ľ���ʱ�䣬��λ���루������Ŀǰ�����ã�
/// @param[in] fnData		�������ص�����
/// @param[in] fnMsg		��Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_StartOfflineFileStream(
	CWALK_FILE_HD readHD, 
	const INT beginTime, 
	const INT endTime, 
	Callback_File_OnStreamData fnData, 
	CallBack_File_OnStreamMsg fnMsg, 
	void* userParam
	);

/// ��ȡ�����ļ����Ž���
/// @param[in]	readHD	�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[out] pos		���ص�ǰ�Ĳ��Ž���,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_GetOfflineFileStreamPos(CWALK_FILE_HD readHD, INT64* pos);

/// ���������ļ�����λ��
/// @param[in]	readHD	�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[in] pos		Ҫ���õĲ���λ��,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFileStreamPos(CWALK_FILE_HD readHD, INT64 pos);

/// ���ò����ٶ�
/// @param[in] readHD	 �ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[in]	speed    0������ͣ������ȡֵ1.0��2.0��4.0��8.0��16.0��32.0��0.5��0.25��0.125��0.0625
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFileStreamSpeed(CWALK_FILE_HD readHD, double speed);

/// ���������ļ�����ģʽ
/// @param[in] readHD	�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @param[in] mode	ģʽ��>0:���򲥷� <0:���򲥷� ==0:ȱʡģʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_SetOfflineFilePlaybackMode(CWALK_FILE_HD readHD, INT32 mode);

/// ֹͣ���߻ط�
/// @param[in] readHD	�ļ����,��CWALK_FILE_OpenOfflineFile�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_StopOfflineFileStream(CWALK_FILE_HD readHD);


/// sliceȥͷ,���������� ��filesdkʹ��
/// @param[in]	srcData		Դ������
/// @param[in]	srcLen		Դ�����ݳ���
/// @param[out]	decData		ȥͷ��������
/// @param[out]	decLen		ȥͷ��Դ�����ݳ���
/// @param[out]	streamType	����������
/// @param[out]	isIFrame	��Ϊ��Ƶ���ݣ��Ƿ�ΪI֡
/// @param[out]	pts		    ʱ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_RemoveSliceHeadWithParam_ForFileSDK(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen,
	INT *streamType,
	INT *isIFrame,
	INT64 *pts);

/// ������Ƶ�˾���
/// @param[out]  filterHD	��Ƶ�˾����
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_CreateVideoFilter(CWALK_FILE_HD* filterHD);

/// ������Ƶ�˾���
/// @param[in]	 filterHD	��Ƶ�˾����
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_DestroyVideoFilter(CWALK_FILE_HD filterHD);

/// ��Ƶ�˾�����һ֡��Ƶ
/// @param[out]  filterHD	��Ƶ�˾����
/// @param[in]   srcData	Դ֡���ݣ���֧��dmslice��h264��mpeg2��mpeg4��
/// @param[in]   srcDataLen	Դ֡���ݳ���
/// @param[in]   pts		֡����ʱ������˲�����ʱ��������0���ɡ�
/// @param[out]	 dstData	���֡���ݣ��ڴ���ʹ���ⴴ��
/// @param[out]	 dstDataLen ���֡���ݳ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_FILE_VideoFilterDealAFrame(
	CWALK_FILE_HD filterHD,
	const void* srcData,
	const UINT srcDataLen,
	const UINT64 pts,
	void* dstData,
	UINT* dstDataLen);


#endif
