/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
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

/// OSD����
typedef enum
{
	CWALKPLAY_OSD_UNKNOW = -1,			///< δ֪����
	CWALKPLAY_OSD_TEXT	= 0,			///< �ı�
	CWALKPLAY_OSD_LINE	= 1,			///< ֱ��
	CWALKPLAY_OSD_RECT	= 2,			///< �Ŵ��������
	CWALKPLAY_OSD_TIME = 3,			///< ʱ��
	CWALKPLAY_OSD_LOCAL_TIME = 4,		///< �ͻ��˱���ʱ��
} CWALKPLayOSDType;

/// ��
typedef struct
{
	double x1;
	double y1;
} CWALKPLayPoint;

/// OSD�ı����뷽ʽ
typedef enum
{
	CWALKPLAY_ALIGNMENT_LEFT = 0X0001,	///< �����
	CWALKPLAY_ALIGNMENT_RIGHT = 0X0002	///< �Ҷ���
} CWALKPLayOSDTextAlignType;

/// �ı�
typedef struct
{
	CWALKPLayPoint point;			///< ����pos
	TCHAR text[256];			///< ����
	TCHAR fontFamily[64];		///< ������
	BOOL autoColor;				///< �Զ�������ɫ
	DWORD color;				///< ���ֵ���ɫ
	DWORD backColor;			///< ���ֱ�����ɫ
	double fontSize;			///< ������Եĳߴ�
	INT alignment;				///< ���뷽ʽ ����CWALKPLayOSDTextAlignType
	INT fillWaterMark;			///< osd��ʽ  0 ��ƽ�� 1 ƽ����Ļ
} CWALKPLayOSDText;

/// �߶�
typedef struct
{
	double x1;					///< ����x���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��x1=x/width
	double y1;					///< ����y���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��y1=y/height
	double x2;					///< �յ��x���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��x2=x/width
	double y2;					///< �յ��y���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��y2=y/height
	DWORD lineWidth;			///< �߶εĿ��
	DWORD color;				///< ��ɫ
}CWALKPLayOSDLine;

/// OSD����
typedef struct
{
	double x1;					///< ���Ͻ�x���꣬��ΧΪ[0.0,1.0]��x1=x/width
	double y1;					///< ���Ͻ�y���꣬��ΧΪ[0.0,1.0]��y1=y/height
	double w;					///< ��ȣ���ΧΪ[0.0,1.0]��x2=x/width
	double h;					///< �߶ȣ���ΧΪ[0.0,1.0]��y2=y/height
	DWORD lineWidth;			///< �߿�Ŀ��
	DWORD color;				///< �߿����ɫ
	DWORD fillColor;			///< ������ɫ, �ر��0xffffffff��ʾ�����
} CWALKPLayOSDRect;

/// ��������Ƶ������Ϣ
typedef struct
{
	LONG width;					///< ͼ����
	LONG height;				///< ͼ��߶�
	LONG type;					///< YUV�������� 0��YUV420֡��������δʹ��
	INT64 pts;					///< ʱ���
} CWALKPLayFrameInfo;

/// ��Ƶ������PCM֡
typedef struct
{
	INT pts;			///< ֡ʱ���
	INT channelType;	///< ����˳��0��˳�������1�����������������δʹ��		
	INT channels;		///< ������
	INT bitsPerSample;	///< ÿ����λ��
	INT samplesPerSec;	///< ÿ��������
	INT samples;		///< pcm�ֶ�ָ��Ĳ������ݵ�������
	BYTE* pcm;			///< ��������
} CWALKPLayPcmFrame;

/// ���ſ������������
typedef enum 
{ 
	CWALKPLAY_CMD_PLAY,			///< ����
	CWALKPLAY_CMD_PAUSE,			///< ��ͣ
	CWALKPLAY_CMD_FAST,			///< ����
	CWALKPLAY_CMD_SLOW,			///< ����
	CWALKPLAY_CMD_NORMAL,			///< �����ٶȲ���
	CWALKPLAY_CMD_FULL,			///< ȫ�ٲ���
	CWALKPLAY_CMD_FRAME,			///< ��֡����
	CWALKPLAY_CMD_GETTIME,			///< ��ȡ��ǰ���ŵ�ʱ���
	CWALKPLAY_CMD_GETSTATUS,		///< ��ȡ����״̬, ΪCWALKPLayControl�ж��������
	CWALKPLAY_CMD_GETSPEED,		///< ��ȡ�����ٶȣ�ΪCWALKPLaySpeedControl�ж��������
} CWALKPLayControl;

/// �����ٶȿ������������
typedef enum
{
	CWALKPLAY_SPEED_SLOW16 = -4,	///< ��16���ٲ��� 
	CWALKPLAY_SPEED_SLOW8  = -3,	///< ��8���ٲ��� 
	CWALKPLAY_SPEED_SLOW4  = -2,	///< ��4���ٲ��� 
	CWALKPLAY_SPEED_SLOW2  = -1,	///< ��2���ٲ��� 
	CWALKPLAY_SPEED_NORMAL = 0,	///< �������� 
	CWALKPLAY_SPEED_FAST2  = 1,	///< ��2���ٲ��� 
	CWALKPLAY_SPEED_FAST4  = 2,	///< ��4���ٲ��� 
	CWALKPLAY_SPEED_FAST8  = 3,	///< ��8���ٲ���  
	CWALKPLAY_SPEED_FAST16 = 4,	///< ��16���ٲ���  
	CWALKPLAY_SPEED_FAST32 = 5,	///< ��32���ٲ��� �ݲ�֧��
} CWALKPLaySpeedControl;

/// ��Ƶ��ǿ����ṹ��
typedef struct
{
	double x;					///< x���꣬�������Ƶ���Ŵ��ڣ�ȡֵ[0��1]
	double y;					///< y���꣬�������Ƶ���Ŵ��ڣ�ȡֵ[0��1]
	double h;					///< �߶ȣ��������Ƶ���Ŵ��ڣ�ȡֵ[0��1]
	double w;					///< ��ȣ��������Ƶ���Ŵ��ڣ�ȡֵ[0��1]
} CWALKPLayEnhanceRect;

/// ��Ƶ��ǿ����
typedef enum 
{
	CWALKPLAY_ILLUMIANTION		= 0x01,		///< ���ȹ�һ��
	CWALKPLAY_SCALEIMAGERANGE	= 0x02,		///< �Աȶ�����
	CWALKPLAY_EMPHASIZE		= 0x04,		///< ������
	CWALKPLAY_SMOOTH			= 0x08,		///< ȥ����
	CWALKPLAY_DEHAZE			= 0x10,		///< ȥ��
	CWALKPLAY_RETINA			= 0x20,		///< ����Ĥ�㷨
	CWALKPLAY_RESTORATION		= 0x40		///< ͼ��ԭ�㷨
} CWALKPLayEnhanceType;

/// ��������
typedef struct
{
	INT x;		///< ����x����
	INT y;		///< ����y����
	INT w;		///< ���Ϳ��
	INT h;		///< ���͸߶�
} CWALKPLayRect;

/// ���ŵ�������
typedef enum
{
	CWALKPLAY_STREAMTYPE_REALSTREAM,		///< ʵʱ��
	CWALKPLAY_STREAMTYPE_NONREALSTREAM,	///< ��ʵʱ��(���Ų�ʹ�ñ��ػ���)
	CWALKPLAY_STREAMTYPE_NONREALSTREAMDISK///< ��ʵʱ��������ʹ�ñ��ػ��棩
} CWALKPLayStreamType;

/// ����ʧ��
typedef enum
{
	CWALKPLAY_DECODE_STATE_OK,			///< �ɹ�����
	CWALKPLAY_DECODE_STATE_FAILE		///< ����ʧ��
}CWALKPLayDecodeState;
/// ������״̬��Ϣ
typedef struct
{
	CWALKPLayDecodeState decodeState; ///< ����״̬
	LONG width;					///< ͼ����
	LONG height;				///< ͼ��߶�
	INT64 pts;					///< ʱ���
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
	CWALKPLAY_AUTO,		///< ��Ӳ���Զ�����
	CWALKPLAY_GPUDECODE,	///< Ӳ����
	CWALKPLAY_CPUDECODE,	///< �����
	CWALKPLAY_AVCFECODE,	///< AVCF�����
	CWALKPLAY_HIKDECODE		///< HIK�����
}CWALKPLayDecodeMode;

typedef enum
{
	CWALKPLAY_FMT_YV12,
	CWALKPLAY_FMT_NV12
} CWALKPLayYUVType;
//������ͼ��Ϣ
typedef struct {
	INT nCapID;
	CWALKPLayYUVType type;
	INT width; 
	INT height;
} CWALKPLayCaptureInfo;

//������Ϣ
typedef struct {
	double dFrameRate;
	double fps;
} CWALKPLayDecodeInfo;

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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetSDK_Version(
	TCHAR* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ��ʼ��SDK
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_Init();

/// ���SDK��Դ
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_Cleanup();

/// ö��֧��Ӳ�����ͽӿ�
/// @param[out]  pDecoderTypes ���ַ������أ������ַ�������64  ��ʽ�ԡ�|���ָ����磺intel|cuda|amd|dxva|
/// @param[in,out]  nLen			�����ַ�������
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_DetectDecSupports(
	char* pDecoderTypes,
	INT_PTR* nLen);


/// ����Ӳ��������
/// @param[in]	type		Ӳ��������
/// @param[out]	isSupport	�Ƿ�֧��
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetHwDecType(
	CWALKPLayHWDecodeType type, 
	INT* isSupport);


/// ��Ƶ����ص�����
/// @param[in]	playHD			���ž��
/// @param[in]	buf 			���������
/// @param[in]	len				���ݳ���
/// @param[in]	fInfo			ָ��ͼ�����������Ϣ�ṹָ��
/// @param[in]	userParam		�û����õĻص���������
typedef void (CWALK_SDK_CALLBACK* Callback_OnVideoDecodeData)(
	CWALK_PLAY_HD playHD, 
	const void* buf, 
	INT len, 
	const CWALKPLayFrameInfo* fInfo, 
	void* userParam
	);

///����豸�Ƿ�֧��Ӳ��
/// @param[out] nSupport			�Ƿ�֧�֣�1 - ֧��, ���� �� ��֧��
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CheckHwSupport(
	INT *nSupport
	);

/// ������������ʹ����󣬱������CWALK_PLAY_ReleasePlayer()�ͷ�
/// @param[out]	playHD			�����Ĳ��ž��
/// @param[in]	hwnd			���Ŵ��ھ��
/// @param[in]  streamType		���ŵ�������
/// @param[in]	fnOnDecoder		�ص�����ָ��
/// @param[in]	userParam		�û�����
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreatePlayer(
	CWALK_PLAY_HD* playHD,
	HWND hwnd/* = NULL*/,
	CWALKPLayStreamType streamType,
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// ����Ĭ��ʹ��Ӳ�ⲥ������ʹ����󣬱������CWALK_PLAY_ReleasePlayer()�ͷ�
/// @param[out]	playHD			�����Ĳ��ž��
/// @param[in]	hwnd			���Ŵ��ھ��
/// @param[in]  streamType		���ŵ�������
/// @param[in]	fnOnDecoder		�ص�����ָ��
/// @param[in]	userParam		�û�����
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateHWPlayer(
	CWALK_PLAY_HD* playHD, 
	HWND hwnd, 
	CWALKPLayStreamType streamType, 
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// ��ȡ��ǰ��������
/// @param[in]	playHD			�����Ĳ��ž��
/// @param[out]	decType			Ӳ��������, ����ֵ����ΪCWALKPLayDecodeMode
/// @param[out]	hwType			Ӳ�����ͣ�����ֵ����ΪCWALKPLayHWDecodeType
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetDecodeMode(
	CWALK_PLAY_HD playHD, 
	INT* decMode,
	INT* hwType
	);
	
/// ������������ʹ����󣬱������CWALK_PLAY_ReleasePlayer()�ͷ�
/// @param[out]	playHD			�����Ĳ��ž��
/// @param[in]	hwnd			���Ŵ��ھ��
/// @param[in]  streamType		���ŵ�������
/// @param[in]  decMode			�������ͣ�CWALKPLayDecodeMode����
/// @param[in]  hwType			GPU���ͣ� CWALKPLayHWDecodeType����
/// @param[in]	fnOnDecoder		�ص�����ָ��
/// @param[in]	userParam		�û�����
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreatePlayerEx(
	CWALK_PLAY_HD* playHD, 
	HWND hwnd, 
	CWALKPLayStreamType streamType, 
	INT decMode,
	INT hwType,
	Callback_OnVideoDecodeData fnOnDecoder, 
	void* userParam
	);

/// �ͷŲ�����
/// ע����CWALK_PLAY_CreatePlayer()��Ӧ
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleasePlayer(
	CWALK_PLAY_HD playHD
	);

/// ��Ƶ����ص�����
/// @param[in]	playHD			���ž��
/// @param[in]	pcmFrame		��Ƶ����֡
/// @param[in]	userParam		�û�����
typedef void (CWALK_SDK_CALLBACK* Callback_OnAudioDecodeData)(
	CWALK_PLAY_HD playHD, 
	CWALKPLayPcmFrame* pcmFrame,	
	void* userParam 
	);

/// ������Ƶ�ص�
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	fnOnAudio		��Ƶ����ص�����
/// @param[in]	userParam		�û�����
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetAudioCallback(
	CWALK_PLAY_HD playHD,
	Callback_OnAudioDecodeData fnOnAudio /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// ��������Ƶ����
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 data			�������ݣ�Ϊһ��������slice
/// @param[in]	 len			���ݳ���
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
/// -	CWALKSDK_ERR_PLAY_FULL_SILCES	 ���Ż���������
/// -	CWALKSDK_ERR_PLAY_IS_RELEASED	 ��������Դ�Ѿ��ͷţ�����CWALK_PLAY_ReleasePlayer()�Ѿ�������
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_InputData(
	CWALK_PLAY_HD playHD, 
	const void* data, 
	INT len
	);

/// ��������Ƶ����
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 data			�������ݣ�һ֡h264����
/// @param[in]	 len			���ݳ���
/// @param[in]	 bIsAudio		�Ƿ���Ƶ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
/// -	CWALKSDK_ERR_PLAY_FULL_SILCES	 ���Ż���������
/// -	CWALKSDK_ERR_PLAY_IS_RELEASED	 ��������Դ�Ѿ��ͷţ�����CWALK_PLAY_ReleasePlayer()�Ѿ�������
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_InputH264Data(
	CWALK_PLAY_HD playHD, 
	const void* data, 
	INT len,
	BOOL bIsAudio
	);

/// ��ȡ��Ƶ��Ϣ
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]  info			������Ϣ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetDecodeInfo(
	CWALK_PLAY_HD playHD, 
	CWALKPLayDecodeInfo* info
	);

/// ��ȡ��Ƶ��Ϣ
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]  width			��Ƶ���
/// @param[out]  height			��Ƶ�߶�
/// @param[out]  rate			֡��
/// @param[out]  streamType		��������
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetVideoInfo(
	CWALK_PLAY_HD playHD, 
	INT* width, 
	INT* height, 
	INT* rate, 
	UINT64* streamType
	);

/// ���ſ���
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 cmd			���ſ�������
/// @param[in]	 inParam		�������
/// @param[out]	 outParam		Ҫ��ȡ��ֵ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_PlayControl(
	CWALK_PLAY_HD playHD, 
	CWALKPLayControl cmd, 
	const void* inParam /*= NULL*/, 
	void* outParam/*= NULL*/
	);

/// ������ʾ����
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 rect			��Ƶ��ʾ����,rect��x��y��w��h��Ϊ0ʱ��ʾ���ڴ�С
/// @param[in]	 ratio			�Ƿ񱣳���Ƶ��߱ȣ�TRUE-������Ƶ��߱�(������rect)��FALSE-��������Ƶ��߱�
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPane(
	CWALK_PLAY_HD	playHD,
	const CWALKPLayRect* rect/* = NULL*/, 
	BOOL ratio
	);

///	������Ż������е�����
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ClearPlayBuffer(
	CWALK_PLAY_HD playHD
	);

/// ץͼ
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 fileName	   	�ļ�����,��:��D:\test.jpg�� �� ��test.jpg��
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePicture(
	CWALK_PLAY_HD playHD, 
	const TCHAR* fileName
	);

/// ����ץͼ
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]	 capID	   		���ؽ�ͼ���
/// @param[in]	 count	   		��ͼ����
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePictureEx(
	CWALK_PLAY_HD playHD, 
	INT* capID,
	INT	 count
	);

/// ץͼ������ˮӡ��
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 fileName	   	�ļ�����,��:��D:\test.jpg�� �� ��test.jpg��
/// @param[in]	type			OSD����
/// @param[in]	osdInfo			OSD��Ϣ��ΪCWALKPLayOSDRect��CWALKPLayOSDLine��CWALKPLayOSDText�е�һ�֣���type������Ӧ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CapturePictureByOSD(
	CWALK_PLAY_HD playHD, 
	const TCHAR* fileName,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

/// ��������,����/��ֹ��������,���ʼ��Ϊ����
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 enable			TRUE - ����FALSE - ��ֹ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SoundEnable(
	CWALK_PLAY_HD playHD, 
	BOOL enable
	);

///	��ȡ��������״̬
/// @param[in]	 playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]	 enable			TRUE - ����FALSE - ��ֹ
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SoundIsEnable(
	CWALK_PLAY_HD playHD, 
	BOOL* enable
	);

///	��ȡɫ��ֵ
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]	 brightness	    ���ȣ�  ֵΪ[-127,127]
/// @param[out]	 contrast		�Աȶȣ�ֵΪ[-127,127]
/// @param[out]	 saturation	    ���Ͷȣ�ֵΪ[-127,127]
/// @param[out]	 hue			ɫ����  ֵΪ[-127,127]
/// @return 
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetColor(
	CWALK_PLAY_HD playHD, 
	INT* brightness, 
	INT* contrast, 
	INT* saturation, 
	INT* hue
	);

///	����ɫ��ֵ
/// @param[in]	 playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	 brightness		���ȣ�  ֵΪ[-127,127]
/// @param[in]	 contrast		�Աȶȣ�ֵΪ[-127,127]
/// @param[in]	 saturation	    ���Ͷȣ�ֵΪ[-127,127]
/// @param[in]	 hue			ɫ����  ֵΪ[-127,127]
/// @return
///	-	CWALKSDK_OK     �ɹ�
///	-	����	     ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetColor(
	CWALK_PLAY_HD playHD, 
	INT brightness, 
	INT contrast, 
	INT saturation, 
	INT hue
	);

///	�������ַŴ�����
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]	zoomHD			���������ַŴ�������
/// @param[in]	rect			���ַŴ�������Ϣ
/// @param[in]	hwnd			�Ŵ��Ĵ��ھ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateZoomRect(
	CWALK_PLAY_HD playHD,
	CWALK_PLAY_HD* zoomHD,
	const CWALKPLayOSDRect* rect,
	HWND hwnd
	);

///	��ȡ���ַŴ�������Ϣ
/// @param[in]	zoomHD			 ���ַŴ�����������CWALK_PLAY_CreateZoomRect()���
/// @param[out]	rect			 ���Ҫ�õ������ӷŴ�������Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetZoomRect(
	CWALK_PLAY_HD zoomHD,
	CWALKPLayOSDRect* rect
	);

///	�������ַŴ�������Ϣ
/// @param[in]	zoomHD			���ַŴ�����������CWALK_PLAY_CreateZoomRect()���
/// @param[in]	rect			Ҫ���õ����ַŴ�������Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetZoomRect(
	CWALK_PLAY_HD zoomHD, 
	const CWALKPLayOSDRect* rect
	);

///	�ͷ����ַŴ�����
/// @param[in]	zoomHD			���ַŴ�����������CWALK_PLAY_CreateZoomRect()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseZoomRect( 
	CWALK_PLAY_HD zoomHD
	);

/// ��ȡ��Ƶ��OSD��Ϣ�ص�����
/// @param[in]	playHD		���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	userParam	�û�����
/// @param[in]	id			OSD��ʶ����ͬһ·��Ƶ��Ψһ��ʶһ��OSD��Ϣ��
/// @param[in]	osdType		OSD����
/// @param[in]	osdInfo		OSD��Ϣ����JSON��ʽ����
/// @return
///	-	TRUE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK* Callback_OnGetStreamOSDInfo)(
	CWALK_PLAY_HD playHD,
	void* userParam,
	INT id,	
	CWALKPLayOSDType osdType,
	const TCHAR* osdInfo
	);

/// ��ȡ��Ƶ���е�OSD��Ϣ
/// @param[in]	playHD		���ž������CWALK_PLAY_CreatePlayer()���
///	@param[in]	fnOnGetOSDInfo	OSD��Ϣ�ص�����
///	@param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetStreamOSDInfo( 
	CWALK_PLAY_HD playHD,
	Callback_OnGetStreamOSDInfo fnOnGetOSDInfo,
	void* userParam /*= NULL*/
	);

/// �ر�/��ʾ��Ƶ���е�OSD��Ϣ  
/// ��idΪ��1ʱ����ʾ�ر�/��ʾ����OSD��Ϣ,����������Чid�󣬻ָ����ֿ��ƹ���
/// @param[in]	playHD		���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	id			OSD��ʶ
/// @param[in]	enable		TRUE����ʾ��FALSE������ʾ
/// @return
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StreamOSDInfoEnable( 
	CWALK_PLAY_HD playHD,
	INT id,
	BOOL enable
	);

///	����OSD
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]	osdHD			������OSD���
/// @param[in]	type			OSD����
/// @param[in]	osdInfo			OSD��Ϣ��ΪCWALKPLayOSDRect��CWALKPLayOSDLine��CWALKPLayOSDText�е�һ�֣���type������Ӧ
/// @return
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateOSD(
	CWALK_PLAY_HD playHD, 
	CWALK_PLAY_HD* osdHD,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

///	��ȡOSD��Ϣ
/// @param[in]	osdHD			OSD�������CWALK_PLAY_CreateOSD()���
/// @param[in]	type			OSD����
/// @param[out]	osdInfo			OSD��Ϣ��ΪCWALKPLayOSDRect��CWALKPLayOSDLine��CWALKPLayOSDText�е�һ�֣���type������Ӧ
///									��ָ����ڴ�ռ��ɵ����߷���/�ͷ�
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetOSD(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type,
	void* osdInfo
	);

///	����OSD��Ϣ
/// @param[in]	osdHD			OSD�������CWALK_PLAY_CreateOSD()���
/// @param[in]	type			OSD����
/// @param[in]	osdInfo			OSD��Ϣ��ΪCWALKPLayOSDRect��CWALKPLayOSDLine��CWALKPLayOSDText�е�һ�֣���type������Ӧ
/// @return
///	-	CWALKSDK_OK	 �ɹ�
///	-	����		 ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetOSD(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type, 
	const void* osdInfo
	);

///	�ͷ�OSD
/// @param[in]	osdHD			OSD�������CWALK_PLAY_CreateOSD()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseOSD(
	CWALK_PLAY_HD osdHD
	);

/// ��ʼͬ��OSD��Ϣ����ǰ����ģʽ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSyncOSDnCurrentDecMode(
	CWALK_PLAY_HD playHD
	);

/// ��OSD��Ϣͬ������ǰ����ģʽ��
/// @param[in]	osdHD			OSD�������CWALK_PLAY_CreateOSD()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SyncOSDO(
	CWALK_PLAY_HD osdHD,
	CWALKPLayOSDType type
	);

/// ��ʼͬ��Zoom��Ϣ����ǰ����ģʽ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSyncZoomOnCurrentDecMode(
	CWALK_PLAY_HD playHD
	);

/// �����ַŴ�ͬ������ǰ����ģʽ��
/// @param[in]	zoomHD			���ַŴ�����������CWALK_PLAY_CreateZoomRect()���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SyncZoom(
	CWALK_PLAY_HD zoomHD
	);

/// ������̨����
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	inputBuf		�������
/// @param[in]	inputBufSize	��������ڴ��С
/// @param[out]	outBuf			�������
/// @param[in,out]	outBufSize	��������ڴ��С���������Ǵ�С
CWALK_SDK_API	CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_VirtualPTZControl(
	CWALK_PLAY_HD playHD,
	const void* inputBuf,
	INT inputBufSize,
	void* outBuf,
	INT* outBufSize
	);

/// ���ȹ�һ�����������ڳ�����������������ͼ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	nMaskWidth		�ֲ�ƽ����ȣ��Ƽ� 30����Χ[1-100]
/// @param[in]	nMaskHeight		�ֲ�ƽ���߶ȣ��Ƽ� 30����Χ[1-100]
/// @param[in]	factor			�ֲ�ƽ����ȣ��Ƽ� 0.7����Χ[0.1��2]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetIllumination(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth/* = 101*/,
	INT maskHeight/* = 101*/,
	double factor/* = 0.7*/
	);

/// �Աȶ��������������ڶԱȶȽ�С��ͼ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	min				�ֲ�ƽ����ȣ��Ƽ� 30�� ��Χ[1��100]
/// @param[in]	max				�ֲ�ƽ���߶ȣ��Ƽ� 80����Χ[1��100]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
/// ע�� max > min
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetScaleImageRange(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT min/* = 30*/,
	INT max/* = 240*/
	);

/// ����������������ģ����ͼ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	maskWidth		�ֲ���ǿ��ȣ��Ƽ� 7����Χ[1��100]
/// @param[in]	maskHeight		�ֲ���ǿ�߶ȣ��Ƽ� 7����Χ[1��100]
/// @param[in]	factor			�ֲ���ǿ���ȣ��Ƽ� 50����Χ[1��100]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetEmphasize(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth/* = 7*/,
	INT maskHeight/* = 7*/,
	double factor/* = 1*/
	);

/// ȥ�����������������ϴ��ͼ���ͼ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	maskWidth		�ֲ���ǿ��ȣ��Ƽ� 7����Χ[1��100]
/// @param[in]	maskHeight		�ֲ���ǿ�߶ȣ��Ƽ� 7����Χ[1��100]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetSmooth(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT maskWidth,
	INT maskHeight,
	double factor
	);

/// ȥ����������������ɳ����ͼ��
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	transMin		ȥ��ǿ�ȣ��Ƽ� 60����Χ[1��100]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetDehaze(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	double transMin/* = 0.6*/
	);

/// ����Ĥ�㷨�����������������
/// ע���㷨�ٶȽ���������ֻ��ͼ��ֲ����ڽ��д���
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRetina(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect
	);

/// ͼ��ԭ�㷨�������뽹���˶�ģ��
/// ע���㷨�ٶȽ���������ֻ��ͼ��ֲ����ڽ��д���
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]	blurring		ͼ��ģ���̶ȣ��Ƽ� 5����Χ[1��18]
/// @param[in]	angle			�˶�ģ����Ч���Ƽ� 0����Χ[0��360]
/// @param[in]	type			ģ�����࣬0���뽹��1���˶���������δʹ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRestoration(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT blurring,
	double angle,
	INT type
	);

/// ȡ��ͼ����ǿ
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]	rect			ͼ����ǿ����
/// @param[in]  enhanceType		ͼ����ǿ���ͣ�CWALKPLayEnhanceType���͵Ļ�ֵ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_DelEnhance(
	CWALK_PLAY_HD playHD,
	CWALKPLayEnhanceRect rect,
	INT enhanceType
	);

/// �ڴ���֮�ϻ��ƾ���
/// ע���˹��ܲ����޸�YUV����
/// @param[in]	playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out] rectHD			��ȡ�����ľ��ξ��
/// @param[in]	rect			���β�����Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_CreateRectOnWindow(
	CWALK_PLAY_HD playHD, 
	CWALK_PLAY_HD* rectHD,
	const CWALKPLayOSDRect* rect 
	);

/// ���贰���ϵľ��β���
/// @param[in]	rectHD			���ξ��,��CWALK_PLAY_CreateRectOnWindow()���
/// @param[in]	rect			���β�����Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetRectOnWindow(
	CWALK_PLAY_HD rectHD,
	const CWALKPLayOSDRect* rect
	);

/// ��ȡ�����ϵľ��β���
/// @param[in]	rectHD			���ξ��,��CWALK_PLAY_CreateRectOnWindow()���
/// @param[out]	rect			���β�����Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetRectOnWindow(
	CWALK_PLAY_HD rectHD,
	CWALKPLayOSDRect* rect 
	);

/// �ͷŴ����ϵľ���
/// @param[in]	rectHD			���ξ��,��CWALK_PLAY_CreateRectOnWindow()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_ReleaseRectOnWindow(
	CWALK_PLAY_HD rectHD
	);


/// ��Ƶ�ɼ��ص�����
/// @param[in]  channels		ͨ����
/// @param[in]  bitsPerSample	ÿ����λ��
/// @param[in]  channels		ÿ��������
/// @param[in]	buf				��Ƶ����
/// @param[in]	size			��Ƶ���ݳ���
/// @param[in]	userParam		�û����õĻص���������
typedef void (CWALK_SDK_CALLBACK* Callback_OnAudioInData)(
	INT channels,
	INT bitsPerSample,
	INT samplesPerSec,
	BYTE* buf, 
	INT size,
	void* userParam
	);

/// ��ϵͳĬ�ϵ���Ƶ�ɼ��豸
/// ע��ֻ�ɴ�һ��; Ĭ�ϴ��豸��ΪStop״̬
/// @param[in]  channels		ͨ����
/// @param[in]  bitsPerSample	ÿ����λ��
/// @param[in]  channels		ÿ��������
/// @param[in]  fnCallBack		�ɼ���һ��bufferʱ�����ݴ���ص�֪ͨ����
/// @param[in]  userParam		�ص������û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_OpenSystemAudioIn(
	INT channels/* = 1*/,
	INT bitsPerSample/* = 16*/,
	INT samplesPerSec/* = 8000*/,
	Callback_OnAudioInData fnCallBack,
	void* userParam/* = NULL*/
	);

/// ��ʼ�ɼ���Ƶ����
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StartSystemAudioIn();

/// ֹͣ�ɼ���Ƶ����
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_StopSystemAudioIn();

/// �ر�ϵͳĬ�ϵ���Ƶ�ɼ��豸
CWALK_SDK_API void CWALK_SDK_METHOD CWALK_PLAY_CloseSystemAudioIn();


/// ��ȡϵͳ������, ȡֵ��Χ: [0 - 0xFFFF]
/// @param[out] volume			��8λΪ������, ��8λΪ������
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetMasterVolume(
	INT* volume
	);

///����ϵͳ������, ȡֵ��Χ: [0 - 0xFFFF]
/// @param[in]  volume			��8λΪ������, ��8λΪ������
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetMasterVolume(
	INT volume
	);

/// ����ϵͳ����������
/// @param[in]  mute			�Ƿ�����1 - ����, 0 - ȡ������, ���� �� δʹ��
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetMasterVolumeMute(
	INT mute
	);

///��ȡϵͳ����������
/// @param[out] mute			�Ƿ�����1 - ����, 0 - ȡ������������ �� δʹ��
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
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

/// ������ͼyuv���ݻص�����
/// @param[in]		playHD			���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]		data			yuv����
/// @param[out]		nLen			yuv����
/// @param[out]		Info			yuv������Ϣ
/// @param[in]		userParam		�û����õĻص���������
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

/// ��Ч�ӿ�
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


/// ���ò���ʱ��
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]  beginTime		������ʼʱ��
/// @param[in]  endTime		���Ž���ʱ��
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPlayTimeSeg(CWALK_PLAY_HD playHD, INT64 beginTime, INT64 endTime);

/// ��ȡ����ʱ��
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]  beginTime		������ʼʱ��
/// @param[out]  endTime			���Ž���ʱ��
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetPlayTimeSeg(CWALK_PLAY_HD playHD, INT64* beginTime, INT64* endTime);

/// ���ò���ģʽ
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[in]  mode			����ģʽ��1���ţ�-1����ģʽ��
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetPlayMode(
	CWALK_PLAY_HD playHD, 
	INT mode);

/// ��ȡ����ģʽ
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]  mode			����ģʽ��1���ţ�-1����ģʽ��
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_GetPlayMode(
	CWALK_PLAY_HD playHD, 
	INT* mode);


/// ���õ�ǰ��ȡYUV��״̬
/// @param[in]	playHD		    ���ž������CWALK_PLAY_CreatePlayer()���
/// @param[out]  bStop			TRUE,���ڻ�ȡYUV����
/// @return 
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_PLAY_SetYUVCallStatus(CWALK_PLAY_HD playHD, BOOL bStop);


#endif	//_cwalk_player_h_
