/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
///			All rights reserved
///
///
///			filename: cwalk_netsdk.h
///         description:  DCS ����SDK
///
///
///			create by ziqiu at 2020-05
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================
#ifndef _cwalk_netsdk_h_
#define _cwalk_netsdk_h_

#include "CWALKSDKDefines.h"

typedef struct CWALK_NET_HD__*		CWALK_NET_HD;
//typedef struct CWALK_HELP_HD__*	CWALK_HELP_HD;
typedef CWALK_NET_HD CWALK_HELP_HD;

/// DCS����ƽ̨����
typedef enum
{
	CWALKNET_SVRPLATTYPE_UNKNOWN	= 0,
	CWALKNET_SVRPLATTYPE_DCS671		= 1,	///< DCS_old
	CWALKNET_SVRPLATTYPE_DCSPLUS	= 2,	///< DCS
} CWALKNetSvrPlatType;

/// ��������
typedef enum
{
	CWALKNET_TYPE_UNKNOWN		= 0,		///< ����SDKʱ��ʾ�о�ȫ��
	CWALKNET_TYPE_SERVER		= 0x0001,	///< ����������
	CWALKNET_TYPE_GATEWAY		= 0x0002,	///< ���ط�����, dcs��֧��
	CWALKNET_TYPE_DEVICE		= 0x0004,	///< �����豸
	CWALKNET_TYPE_MOUNT			= 0x0008,	///< �����豸
	CWALKNET_TYPE_CAMERA		= 0x0010,	///< ����ͷ
	CWALKNET_TYPE_MONITOR		= 0x0020,	///< ������
	CWALKNET_TYPE_AUDIO			= 0x0040,	///< �Խ�ͨ��
	CWALKNET_TYPE_TRUNKIN		= 0x0100,	///< �������, dcs��֧��
	CWALKNET_TYPE_TRUNKOUT 		= 0x0200,	///< �������, dcs��֧��
	CWALKNET_TYPE_ALARMIN		= 0x1000,	///< ��������
	CWALKNET_TYPE_ALARMOUT		= 0x2000,   ///< �������
	CWALKNET_TYPE_GIS			= 0x4000
} CWALKNetObjectType;

typedef enum
{
	CWALKNET_GROUPTYPE_UNKNOW	=0,
	CWALKNET_GROUPTYPE_GROUP	=1,			///< ������������
	CWALKNET_GROUPTYPE_VIRTUALGROUP = 2	///< ҵ�����/������֯
}CWALKNetGroupType;

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

/// ��̨����ٶ�
#define CWALKNET_PTZ_MAX_SPEED	15
//  ���
#define MAX_BUFFER_SIZE 1024*1024*40
typedef enum
{
	CWALKNET_PTZ_PANRIGHT	= 0,	///< ��̨��ת
	CWALKNET_PTZ_RIGHTUP	= 1,	///< ��̨��������ת
	CWALKNET_PTZ_TILTUP		= 2,	///< ��̨����
	CWALKNET_PTZ_LEFTUP		= 3,	///< ��̨��������ת
	CWALKNET_PTZ_PANLEFT	= 4,	///< ��̨��ת
	CWALKNET_PTZ_LEFTDOWN	= 5,	///< ��̨�¸�����ת
	CWALKNET_PTZ_TILTDOWN	= 6,	///< ��̨�¸�
	CWALKNET_PTZ_RIGHTDOWN	= 7,	///< ��̨�¸�����ת
	CWALKNET_PTZ_SCAN		= 8,	///< ��̨�����Զ�ɨ��
	CWALKNET_PTZ_HALT		= 9,	///< ��ֹ̨ͣ
	CWALKNET_PTZ_IRIS		= 10,	///< ��Ȧ�仯(param>0����param<0��С��param=0��ʾֹͣ)
	CWALKNET_PTZ_ZOOM_IN	= 11,	///< ������(param>0���ʱ��param<0���ʱ�С��param=0��ʾֹͣ)
	CWALKNET_PTZ_FOCUS		= 12,	///< �۽�����(param>0ǰ����param<0�����param=0��ʾֹͣ)
	CWALKNET_PTZ_VIEW		= 13,	///< ת��ָ��Ԥ��λ
	CWALKNET_PTZ_SETVIEW	= 14,	///< ���õ�ǰλ��Ϊһ��Ԥ��λ
	CWALKNET_PTZ_AUX		= 15,	///< ��ͨ�����豸����(param=1 ��ʾ��,param=0 ��ʾ��,����ֵ��Ч)
	CWALKNET_PTZ_WASH		= 16,	///< ��ϴ
	CWALKNET_PTZ_WIPE		= 17,	///< ��ͨ��ˢ����
	CWALKNET_PTZ_LIGHT		= 18,	///< ��ͨ�ƹ��Դ
	CWALKNET_PTZ_POWER		= 19,	///< ��Դ
	CWALKNET_PTZ_WARD		= 31,
	CWALKNET_PTZ_DELVIEW	= 35,	///< ɾ��Ԥ��λ
	CWALKNET_PTZ_SETPOS		= 40,	///< ��̨ת����ָ��PTZ����	(EX��param="pan=36.0;tilt=56.0;zoom=2.0")
} CWALKNetPTZCommand;

/// �¼�����,����ֵС��50�¼����б���̬������̬����״̬,����50���¼�ֻ�б���̬
typedef enum
{
	CWALKNET_EVENT_UNKNOWN			= -1,	///< δ֪�¼�

	CWALKNET_EVENT_VIDEO_LOST		= 0,	///< ��Ƶ��ʧ����/�ָ�
	CWALKNET_EVENT_MOTION			= 1,	///< �˶���֪����/�ָ�
	CWALKNET_EVENT_VIDEO_HIDE		= 2,	///< ��Ƶ�ڵ�����/�ָ�
	CWALKNET_EVENT_VIDEO_BROKEN		= 3,	///< ��Ƶ���߷���/�ָ�

	CWALKNET_EVENT_ALARM_IN			= 10,	///< �������뱨��/�ָ�
	CWALKNET_EVENT_CAMERA_LOCK		= 12,	///< ���������/�ָ�
	CWALKNET_EVENT_MONITOR_LOCK		= 13,	///< ����������/�ָ�
	CWALKNET_EVENT_DIGITAL_STREAM	= 14,	///< �����������䷢��/ֹͣ
	CWALKNET_EVENT_MANUAL_RECORD	= 15,	///< �ֶ�¼����/ֹͣ
	CWALKNET_EVENT_DEVICE_BROKEN	= 16,	///< �豸��������/�ָ�
	CWALKNET_EVENT_ROFS_ERROR		= 17,	///< ROFS����Ĵ�����/�ָ�

	CWALKNET_EVENT_SYSTEM_INIT		= 50,	///< ϵͳ��ʼ��
	CWALKNET_EVENT_USER_LOGIN		= 51,	///< �û�����
	CWALKNET_EVENT_USER_LOGOUT		= 52,	///< �û�ע��
	CWALKNET_EVENT_MONITOR_SWITCH	= 53,	///< �������л�
	CWALKNET_EVENT_PTZ				= 54,	///< ��̨����
	CWALKNET_EVENT_OPEN_VIDEO_FILE	= 55,	///< ����Ƶ�ļ�
	CWALKNET_EVENT_CLOSE_VIDEO_FILE	= 56,	///< �ر���Ƶ�ļ�
	CWALKNET_EVENT_ALARM_INFO		= 57,	///< �����豸������Ϣ
	CWALKNET_EVENT_VA_ALARM			= 58,	///< ���ܱ����¼�
	CWALKNET_EVENT_OSD_CHANGE		= 59,	///< OSD��Ϣ�ı�
	CWALKNET_EVENT_INTRUSION		= 61,  ///< ��������
	CWALKNET_EVENT_TRAVERSE_PLANE	= 62,  ///< Խ����
	CWALKNET_EVENT_HIGH_DENSITY		= 6,   ///< ��Ա�ۼ�

	/// �豸�����¼�
	CWALKNET_EVENT_CPU_TOO_BUSY	= 100,	///< CPUʹ���ʹ��߱���
	CWALKNET_EVENT_MEMORY_TOO_HIGH	= 101,	///< �ڴ�ʹ���ʹ��߱���
	CWALKNET_EVENT_DISK_ARRAY_WRITE_FAILED = 102,	///< �������в���д
	CWALKNET_EVENT_DISK_ARRAY_ERROR= 103,	///< �������д���
	CWALKNET_EVENT_LOST_COMMODITY = 120,	///< ��Ʒ��ʧ
	

	//�����¼����û�����
	CWALKNET_EVENT_CMS_USER_PERMISSION = 1000 //���û�����
} CWALKNetEventType;

/// CWALKDB����
typedef enum
{
	CWALKNET_LOGTYPE_EVENT,	///< �¼���־
	CWALKNET_LOGTYPE_OPERAT,	///< ������־
} CWALKNetLogType;

/// ��־�������ͻ������Ͷ����У�DCS����
#define  CWALKNET_LCTD_DCS_CMS	1

/// DCS������־����
typedef enum
{
	/// ϵͳ���
	CWALKNET_OLT_REBOOT							= 1001,	///< 
	CWALKNET_OLT_SHUTDOWN						= 1002,	///< 
	CWALKNET_OLT_SET_TIME						= 1003,	///< 
	CWALKNET_OLT_SET_IP							= 1004,	///< 

	/// �û����
	CWALKNET_OLT_USER_LOGIN						= 101,	///< �û���¼
	CWALKNET_OLT_USER_LOGOUT					= 102,	///< �û��ǳ�

	/// ʵʱ������
	CWALKNET_OLT_REAL_STREAM_OPEN				= 201,	///< ʵʱ����
	CWALKNET_OLT_REAL_STREAM_CLOSE				= 202,	///< ʵʱ���ر�
	CWALKNET_OLT_TALK							= 211,	///< ����
	CWALKNET_OLT_LISTEN							= 212,	///< ����
	CWALKNET_OLT_DECODE_OPEN					= 221,	///< 
	CWALKNET_OLT_DECODE_PLAY					= 222,	///< 
	CWALKNET_OLT_DECODE_CLOSE					= 223,	///< 
	CWALKNET_OLT_DECODE_JOIN					= 224,	///< 

	CWALKNET_OLT_MONITOR_OPEN					= 231,	///< 
	CWALKNET_OLT_MONITOR_CLOSE					= 232,	///< 
	CWALKNET_OLT_MONITOR_VOD_OPEN				= 233,	///< 
	CWALKNET_OLT_MONITOR_VOD_PLAY				= 234,	///< 
	CWALKNET_OLT_MONITOR_VOD_PAUSE				= 235,	///< 
	CWALKNET_OLT_MONITOR_VOD_CLOSE				= 236,	///< 
	CWALKNET_OLT_MONITOR_LOCK					= 237,	///< 
	CWALKNET_OLT_MONITOR_UNLOCK					= 238,	///< 

	/// ¼�����
	CWALKNET_OLT_RECORD_REMOTE_OPEN				= 301,	///< Զ��¼���
	CWALKNET_OLT_RECORD_REMOTE_CLOSE			= 302,	///< Զ��¼��ر�
	CWALKNET_OLT_RECORD_SERVER_QUERY			= 303,	///< ������¼���ѯ
	CWALKNET_OLT_RECORD_DEVICE_QUERY			= 304,	///< �豸¼���ѯ
	CWALKNET_OLT_RECORD_MANUAL_START			= 305,	///< �ֶ�¼��ʼ
	CWALKNET_OLT_RECORD_MANUAL_STOP				= 306,	///< �ֶ�¼�����
	CWALKNET_OLT_RECORD_QUERY_SEGMENT			= 307,	///< ��ѯ¼��ʱ���
	CWALKNET_OLT_RECORD_QUERY_PROTECT_SEGMENT	= 308,	///< ��ѯ¼�񱣻�ʱ���
	CWALKNET_OLT_RECORD_SET_PROTECT_SEGMENT		= 309,	///< �趨¼�񱣻�ʱ���
	CWALKNET_OLT_RECORD_UNSET_PROTECT_SEGMENT	= 310,	///< ȥ��¼�񱣻�ʱ���
	CWALKNET_OLT_RECORD_QUERY_FILE				= 311,	///< ��ѯ¼���ļ�
	CWALKNET_OLT_RECORD_OPEN_PLAYBACK			= 312,	///< ��¼��ط�
	CWALKNET_OLT_RECORD_STOP_PLAYBACK			= 313,	///< ֹͣ¼��ط�
	CWALKNET_OLT_RECORD_DOWNLOAD_START			= 314,	///< ¼�����ؿ�ʼ
	CWALKNET_OLT_RECORD_DOWNLOAD_STOP			= 315,	///< ¼�����ؽ���
	CWALKNET_OLT_RECORD_LOCAL_START				= 316,	///< ����¼��ʼ
	CWALKNET_OLT_RECORD_LOCAL_STOP				= 317,	///< ����¼�����

	/// �������
	CWALKNET_OLT_MATRIX_START					= 401,	///< ����
	CWALKNET_OLT_MATRIX_STOP					= 402,	///< ֹͣ

	/// �¼�����
	CWALKNET_OLT_EVENT_SUBSCRIBE_START			= 501,	///< �¼����Ŀ�ʼ
	CWALKNET_OLT_EVENT_SUBSCRIBE_STOP			= 502,	///< �¼����Ľ���

	/// ��̨����
	CWALKNET_OLT_PTZ_CONTROL					= 601,	///< ��̨����
	CWALKNET_OLT_PTZ_LOCK						= 602,	///< ��̨����

	/// �������
	CWALKNET_OLT_UI_CAPTURE_IMG					= 701,	///< ץͼ

	/// �������
	CWALKNET_OLT_CONFIG_DOWNLOAD_FILE			= 801,	///< ���������ļ�
	CWALKNET_OLT_CONFIG_UPDATE_FILE				= 802,	///< ���������ļ�

	CWALKNET_OLT_CONFIG_REGISTER_GATEWAY		= 803,	///< ���������豸
	CWALKNET_OLT_CONFIG_UNREGISTER_GATEWAY		= 804,	///< ɾ�������豸
	CWALKNET_OLT_CONFIG_LIST_GATEWAY			= 805,	///< ��������豸�б�

	CWALKNET_OLT_CONFIG_REGISTER_MOUNT			= 806,	///< ���ӹ����豸
	CWALKNET_OLT_CONFIG_UNREGISTER_MOUNT		= 807,	///< ɾ�������豸
	CWALKNET_OLT_CONFIG_LIST_MOUNT				= 808,	///< ��ù����豸�б�

	CWALKNET_OLT_CONFIG_REGISTER_HOST			= 809,	///< �����豸
	CWALKNET_OLT_CONFIG_UNREGISTER_HOST			= 810,	///< ɾ���豸
	CWALKNET_OLT_CONFIG_LIST_HOST				= 811,	///< ����豸�б�

	CWALKNET_OLT_CONFIG_REGISTER_CAM			= 812,	///< ���������
	CWALKNET_OLT_CONFIG_UNREGISTER_CAM			= 813,	///< ɾ�������
	CWALKNET_OLT_CONFIG_LIST_CAM				= 814,	///< ���������б�

	CWALKNET_OLT_CONFIG_REGISTER_MON			= 815,	///< ���Ӽ�����
	CWALKNET_OLT_CONFIG_UNREGISTER_MON			= 816,	///< ɾ��������
	CWALKNET_OLT_CONFIG_LIST_MON				= 817,	///< ��ü������б�

	CWALKNET_OLT_CONFIG_REGISTER_IN_TRUNK		= 818,	///< �����������
	CWALKNET_OLT_CONFIG_UNREGISTER_IN_TRUNK		= 819,	///< ɾ���������
	CWALKNET_OLT_CONFIG_LIST_IN_TRUNK			= 820,	///< �����������б�

	CWALKNET_OLT_CONFIG_REGISTER_OUT_TRUNK		= 821,	///< �����������
	CWALKNET_OLT_CONFIG_UNREGISTER_OUT_TRUNK	= 822,	///< ɾ���������
	CWALKNET_OLT_CONFIG_LIST_OUT_TRUNK			= 823,	///< �����������б�

	CWALKNET_OLT_CONFIG_REGISTER_AUDIO			= 824,	///< ������Ƶ�豸
	CWALKNET_OLT_CONFIG_UNREGISTER_AUDIO		= 825,	///< ɾ����Ƶ�豸
	CWALKNET_OLT_CONFIG_LIST_AUDIO				= 826,	///< �����Ƶ�豸�б�

	CWALKNET_OLT_CONFIG_REGISTER_ALARM_IN		= 827,	///< ���ӱ��������豸
	CWALKNET_OLT_CONFIG_UNREGISTER_ALARM_IN		= 828,	///< ɾ�����������豸
	CWALKNET_OLT_CONFIG_LIST_ALARM_IN			= 829,	///< ��ñ��������豸�б�

	CWALKNET_OLT_CONFIG_REGISTER_ALARM_OUT		= 830,	///< ���ӱ�������豸
	CWALKNET_OLT_CONFIG_UNREGISTER_ALARM_OUT	= 831,	///< ɾ����������豸
	CWALKNET_OLT_CONFIG_LIST_ALARM_OUT			= 832,	///< ��ñ�������豸�б�

	CWALKNET_OLT_CONFIG_SET_CAM_LEVEL				= 833,	///< �趨���������
	CWALKNET_OLT_CONFIG_REGISTER_FORWARD_SERVER		= 834,	///< ����ת��������
	CWALKNET_OLT_CONFIG_UNREGISTER_FORWARD_SERVER	= 835,	///< ɾ��ת��������

} CWALKNetOperatLogType;

/// DCS��������
typedef enum
{
	CWALKNET_SERVICETYPE_CMSERVICE	= 1,			///< ���ط���
	CWALKNET_SERVICETYPE_STREAMINGSERVICE	= 2,	///< ת������
	CWALKNET_SERVICETYPE_STORAGESERVICE	= 3,		///< �洢����
	CWALKNET_SERVICETYPE_USRSERVICE	= 4,			///< ��֤����
	CWALKNET_SERVICETYPE_LOGSERVICE	= 5,			///< ��־����
} CWALKNetServiceType;

//�û���������
typedef enum
{
	CWALKNET_LIST = (1<<0),
	CWALKNET_QUERY = (1<<1),
	CWALKNET_CONFIG = (1<<2),	
	CWALKNET_VIEW = (1<<3),
	CWALKNET_SWITCH = (1<<4),
	CWALKNET_PTZ = (1<<5),
	CWALKNET_RECORD = (1<<6),
	CWALKNET_VOD = (1<<7),
	CWALKNET_LISTENEVENT = (1<<8),
	CWALKNET_QUERYEVENT = (1<<9),
	CWALKNET_SETALARM = (1<<10),
	CWALKNET_QUERYLOG = (1<<11),
	CWALKNET_SYNCINFO = (1<<12),
	CWALKNET_CONFIGUSER = (1<<13),
	CWALKNET_CONFIGDB = (1<<14),
	CWALKNET_LISTONLINEUSER = (1<<15),
	CWALKNET_DOWNLOAD_VIDEO = (1<<16)
} CWALKNetDcsUsersAbility;

typedef enum
{
	Talk = 1,  ///<������
	Listen = 2, ///< ������
	ListenAndTalk = 3 ///< ˫��Խ�
}CWALKAudioMode;

typedef struct  
{
	float longitude;
	float latitude;
	INT focus;
}CWALKNetPTZPos;

/// OSD����
typedef enum
{
	CWALK_OSD_UNKNOW = -1,			///< δ֪����
	CWALK_OSD_TEXT	= 0,			///< �ı�
	CWALK_OSD_LINE	= 1,			///< ֱ��
	CWALK_OSD_RECT	= 2,			///< �Ŵ��������
	CWALK_OSD_TIME = 3,			///< ʱ��
} CWALKOSDType;

/// ��
typedef struct
{
	double x1;
	double y1;
} CWALKPoint;

/// OSD�ı����뷽ʽ
typedef enum
{
	CWALK_ALIGNMENT_LEFT = 0X0001,	///< �����
	CWALK_ALIGNMENT_RIGHT = 0X0002	///< �Ҷ���
} CWALKOSDTextAlignType;

/// �ı�
typedef struct
{
	CWALKPoint point;				///< ����pos
	TCHAR text[256];			///< ����
	TCHAR fontFamily[64];		///< ������
	BOOL autoColor;				///< �Զ�������ɫ
	DWORD color;				///< ���ֵ���ɫ
	DWORD backColor;			///< ���ֱ�����ɫ
	double fontSize;			///< ������Եĳߴ�
	INT alignment;				///< ���뷽ʽ ����CWALKPLayOSDTextAlignType
	INT fillWaterMark;			///< osd��ʽ  0 ��ƽ�� 1 ƽ����Ļ
} CWALKOSDText;

/// �߶�
typedef struct
{
	double x1;					///< ����x���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��x1=x/width
	double y1;					///< ����y���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��y1=y/height
	double x2;					///< �յ��x���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��x2=x/width
	double y2;					///< �յ��y���꣬Ϊ����ֵ����ΧΪ[0.0,1.0]��y2=y/height
	DWORD lineWidth;			///< �߶εĿ��
	DWORD color;				///< ��ɫ
}CWALKOSDLine;

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
} CWALKOSDRect;

/// �����û���Ϣ
typedef struct
{
	TCHAR userName[128];	    ///< �û���
	TCHAR userDomain[128];      ///< ��������, dcs���dcm��ַ
	TCHAR authServe[128];       ///< �û���֤������, dcs���dcm��ַ
	TCHAR rank[128];            ///< �û�ͷ��, dcs��֧��, ֵΪ��
	TCHAR role[128];            ///< �û���ɫ, dcsֵΪ��
	TCHAR userLocal[128];       ///< �û����ڵ�
	INT   level;                ///< �û�����
	TCHAR waterMarkText[128];   ///< ����ˮӡ����
	INT   waterMarkType;        ///< ����ˮӡ���� 0��ˮӡ 1����Ĭ�� 2 ����Ĭ�� 3 �����Զ��� 4 �����Զ���
}CWALKOnlineUser;

typedef struct _CWALKVodRecordInfo
{
	TCHAR file[64];
	// ����ʱ�䣬��ʽ��20160622213348
	TCHAR strBegin[64];
	TCHAR strEnd[64];
	int nDepth; //¼����ȣ�0-������¼��, ��0¼�����ڵĲ���,���ֵΪ256
	int nType;  //¼������
	TCHAR storage[128];  //���ڴ洢ID
}CWALKVodRecordInfo;

typedef struct
{
	TCHAR monitorId[128];	 /// ������id
	TCHAR monitorNo[32];	 /// ���������
	TCHAR deviceId[128];	 /// ������id
	TCHAR userName[128];	 /// �����û���
	TCHAR ip[128];			 /// �����û�ip
	TCHAR channelId[128];	 /// �����id 
	TCHAR channelName[128];  /// ���������
	TCHAR userId[64];		 /// �û�id
	TCHAR nodeId[64];		 /// �ڵ�id
	TCHAR monitorMode[16];   /// ������ģʽ
	TCHAR res[512];			 /// Ԥ��
}CWALKTransferStatus;

typedef struct 
{
	TCHAR begin[128];
	TCHAR end[128];
	int nDepth;			/// ¼�����. -1:ȫ���㼶, 0:����¼��, >0:¼�����ڵĲ���,���ֵΪ256
	TCHAR res[512];		/// Ԥ��
}CWALKTransferVodInfo;

typedef struct
{
	TCHAR osdInfo[512]; /// osd��Ϣ�ַ���
	TCHAR rtspUrl[512]; /// rtsp��ַ��
	//CWALKTransferVodInfo vodInfo;	/// ¼����ǽ��Ϣ
}CWALKTransferOptions;

typedef enum {

	CWALKCharacterEncoding_Local = 1,      //ȫ��ʹ��ϵͳĬ���ַ��������ܴ������������ַ����뵼�µ����ݽ���ʧ�ܵ�����
	CWALKCharacterEncoding_UTF8,           //ȫ��ʹ��UTF8���룻�Ƽ�ʹ�ø�����
	CWALKCharacterEncoding_UTF8_Later102,  //�ӿ�ʹ��UTF8���룬���ڽӿ�ʹ��Local���룻�������ѶԽӹ�DCSSDK�Ĳ�Ʒ�����汾�������
}CWALKCharacterEncodingType;

typedef enum {
	CWALKNET_TVWALL_Switch_Set = 0x00,		// ��������
	CWALKNET_TVWALL_Switch_Remove,			// ɾ��ָ��������Ϣ
	CWALKNET_TVWALL_Switch_Get,				// ��ȡָ��������Ϣ
	CWALKNET_TVWALL_Switch_List,			// �о�����������Ϣ
	/* TVWall switch
	request/response = 
	{
		//���е�id
		"id": "����id",
		//�汾��;�ɷ����ά��;��������ʱ�˰汾�������˲�һ�»ᵼ�½ӿ�ʧ��
		"version" : 1,
		"name" : "��������",
		//(�����-������ͨ��)��Ӧ��ϵ����
		"links" : [
			{
				//������ͨ�����;��1��ʼ
				"channelNum": 1,
				//������ͨ��id;ʡ��ʱ�Զ���дΪchannelNum
				"channelId" : "xxx",
				"monitorId" : "������id",
				//����������;
				//0: �ͻ�����Ƶ������
				//1: ����ǽ�豸
				"monitorType" : 1,
				//�󶨵������Id
				"cameraId" : "xxx",
				//�󶨵����������
				"cameraName" : "xxx"
			}
		]
	}*/

	CWALKNET_TVWALL_RoundPlan_Set = 0x10,	// ���õ���ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_List,		    // �оٵ���ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Get,		    // ��ȡָ������ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Remove,	    // ɾ������ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Active,	    // �������ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Inactive,	    // ���õ���ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Start,	    // ����ִ�е���ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_Stop,		    // ����ֹͣ����ǽ��Ѳ�ƻ�
	CWALKNET_TVWALL_RoundPlan_GetState,	    // ��ȡָ����Ѳ�ƻ�״̬
	CWALKNET_TVWALL_RoundPlan_ListState,	// �о���Ѳ�ƻ�״̬
	/* TVWall RoundPlan
	request/response = 
	{
		// ��Ѳ�ƻ�id
		"id":"",
		// �汾��,�ɷ����ά��
		"version" : 1,
		// �ƻ�����
		"name" : "",
		// �������û��Ƿ�ɼ�
		"isSharedWithAllUser" : false,
		// �Ƿ񼤻�ƻ�
		"isActive" : true,
		// ��Ѳ�л�ʱ����(��),��Χ 5-65535
		"interval" : 10,
		// ��һ���ֽڱ�ʾ�Ƿ�ʹ��������Ϊ�ƻ���ѭ�����ڣ��Լ����ڼ�ִ����Ѳ�ƻ�
		// ��8λΪ1ʱ��ʾʹ��������Ϊ�ƻ���ѭ������
		// ��1λΪ1ʱ��ʾ[����]������Ѳ�ƻ�
		// ��2λΪ1��ʾ[��һ]������Ѳ�ƻ�
		// ��3λΪ1��ʾ[�ܶ�]������Ѳ�ƻ�����������
		// ���磺0b10001011 (139)��ʾ���ա���1����3ִ����Ѳ�ƻ�
		// ���磺0b00001011 (11)��ʾ��ʹ��������Ϊѭ������
		// ע:
		//  - 20210922 Ŀǰ��֧��������Ϊ�ƻ���ѭ������,��ֵС��128ʱ��ʾ�˼ƻ���Ч
		"cycleDaysOfWeek":255,
		// ������б�
		"cameras" : [
			{
				// �����id
				"id":"xxx",
				// [��ѡ]
				"cameraName" : "xxx"
			}
		],
		// ����������;
		// 0:�ͻ�����Ƶ������
		// 1:����ǽ�豸
		"monitorType":1,
		// ������ͨ���б�
		"monitorChls" : [
			{
				// [��ѡ] ������ͨ��id,ʡ��ʱ�Զ���дΪchannelNum
				"channelId":"xxx",
				// ������ͨ�����,��1��ʼ
				"channelNum" : 1,
				"monitorId" : "������id"
			}
		],
		// ʱ����б�
		"timeRanges":[
			{
				// ��ʼʱ��,��ʽ��HH*10000+mm*100+ss
				"startTime":3001,
				// ����ʱ��,��ʽ��HH*10000+mm*100+ss
				"endTime" : 123001
			}
		],
		// [����Ӧ] ��������´˼ƻ����û�Ψһid
		"creatorId":"",
		// [����Ӧ] ��������´˼ƻ����û���
		"creatorAccount" : ""
	}*/

	CWALKNET_TVWALL_OpenLive = 0x20,		// ʵʱ��Ƶ��ǽ
	CWALKNET_TVWALL_OpenVod,			    // ¼����Ƶ��ǽ
	CWALKNET_TVWALL_Close,				    // �رգ�ʵʱ��¼����ǽ��Ƶ

	CWALKNET_TVWALL_Layout_Set = 0x30,	    // ���õ���ǽ����
	CWALKNET_TVWALL_Layout_List,		    // �оٶ����ǽ����
	CWALKNET_TVWALL_Layout_Get,			    // ��ȡָ������ǽ����
	CWALKNET_TVWALL_Layout_Remove,		    // ɾ��ָ������ǽ����
	/* TVWALL_Layout
	request / response = 
	{
		// ����id
		"id":"xxx",
		// �汾��,�ɷ����ά��
		"version" : 1,
		// ������������´˲��ֵ��û�
		"creatorId" : "xxx",
		"creatorAccount" : "xxx",
		"creatorName" : "xxx",
		// ��������
		"name" : "��������",
		// ���ֵ�ǰ����
		"rows" : 2,
		// ���ֵ�ǰ����
		"columns" : 2,
		"items" : [
			{
				// �����ڲ����е�������,��1��ʼ;�����ֵ���ڲ��ֵ�rows,��ʾ����ڲ��ֵĵ�ǰ��ʾ��Χ
				"row":1,
				// �����ڲ����е�������,��1��ʼ;�����ֵ���ڲ��ֵ�columns,��ʾ����ڲ��ֵĵ�ǰ��ʾ��Χ
				"column" : 1,
				// ͨ������
				"name" : "xxx",
				// 0:dcs������ͨ��; 1:������
				"targetType" : 0,
				// ��������dcs������ͨ��id
				"targetId" : "xxx",
				// [��ѡ] ���targetType=1,����,��ʾ������ͨ������
				"moChannelCnt" : 4,
				// [��ѡ] ���targetType=1,����,��ʾ��������ǰ��������
				"moRows" : 2,
				// [��ѡ] ���targetType=1,����,��ʾ��������ǰ��������
				"moColumns" : 2
			}
		]
	}*/

	CWALKNET_TVWALL_ListChannelStatus = 0x40, // �оٵ���ǽͨ��״̬
	/* TVWall ListChannelStatus
	response = 
	[
		{
			// ������id
			"monitorId":"xxx",
			// ������ͨ�����,��1��ʼ
			"chlNum" : 1,
			// ������ͨ��id,���û��ͨ��id,��ֵ����chlNum
			"chlId" : "",
			// [��ѡ] �����ͨ����������ִ�е���Ѳ�ƻ���,���ʾ��Ѳ�ƻ�id
			"loopId" : "xxx1",
			// [��ѡ] ���loopId��Ϊ��,��ʾ��Ѳ�ƻ�����
			"loopName" : "xxx2",
			// [��ѡ] ���loopId��Ϊ��,��ʾ��Ѳ�ƻ�������id
			"loopCreatorId" : "xxxx1",
			// [��ѡ] ���loopId��Ϊ��,��ʾ��Ѳ�ƻ��������˻�
			"loopCreatorAccount" : "xxxx1",
			// [��ѡ] �������Ƶ������ǽ,��ʾ�����id
			"cameraId" : "xxx3",
			// [��ѡ] ���cameraId��Ϊ��,��ʾ���������
			"cameraName" : "xxxx",
			// [��ѡ] �������Ƶ������ǽ,��ʾ����Ƶ���û���id
			"userId" : "xxx4",
			// [��ѡ] ���userId��Ϊ��,��ʾ�û����˻���
			"userAccount" : "xxx5",
			// [��ѡ] ���userId��Ϊ��,��ʾ�û���
			"userName" : "xxx6"
		}
	]*/

	CWALKNET_TVWALL_MAX,
}CWALKNetTVWallCommand;

typedef struct {
	TCHAR* req;
	TCHAR* resp;
	INT respLen;

	TCHAR* message;
	INT messageLen;

	TCHAR dataId[128];
}CWALKNetTVWallParam;

typedef enum {
	CWALKNET_MatrixCtrl_LikeGet = 0,	// ��ȡ������
	CWALKNET_MatrixCtrl_LikeSet = 1,	// ����������
	CWALKNET_MatrixCtrl_MAX,
}CWALKNetMatrixCtlCommand;

typedef struct {
	CWALKNetMatrixCtlCommand cmd;

	TCHAR* req;		// ������� json��ʽ�ַ���
	TCHAR* resp;	// ��Ӧ���� json��ʽ�ַ���
	INT respLen;	// ��Ӧ���ݳ���

	TCHAR* message;	// ִ�н��
	INT messageLen;
}CWALKNetMatrixCtrlParam;

//״̬�������ֵ

/// ���SDK�汾��Ϣ
/// @param[out]	infoBuf		�õ�SDK�汾��Ϣ,�ڴ�ռ��ɵ����߷���,����ͨ��CWALK_NET_InfoParseKeyValue()������
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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetSDK_Version(
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���cmservice����汾��Ϣ
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]  infoBuf	infoBuf���ذ汾json
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerVersion(
	CWALK_NET_HD userHD, 
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// (���Ƽ�ʹ��)��ʼ��SDK,ʹ�ñ��ر���,
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Init();

/// ��ʼ��SDK
/// @param[in]	type		�ӿ����ݵı������ͣ��Ƽ�ʹ��CWALKCharacterEncoding_UTF8
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_Init(CWALKCharacterEncodingType type);

/// ���SDK��Դ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Cleanup();

///	��¼DCS������
/// @param[out]	userHD		�õ��û���¼���
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	userName	��¼�û���
///	@param[in]	passwd		��¼����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Login(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	const TCHAR* passwd
	);

///	��¼DCS������
/// @param[out]	userHD		�õ��û���¼���
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	userName	��¼�û���
///	@param[in]	passwd		��¼����
///	@param[in]	userMAC		MAC ADDR
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByMAC(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	const TCHAR* passwd,
	const TCHAR* userMAC
	);


///	��¼SPecial��������dcs��֧��
/// @param[out]	userHD		�õ��û���¼���
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	ipOrHost	url
///	@param[in]	port		tgt
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByTGT(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* url,
	const TCHAR* tgt
	);

///	ָ������¼DCS������
/// @param[out]	userHD		�õ��û���¼���
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	domain		����
///	@param[in]	img			ָ��������
///	@param[in]	len			img���ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByFingerModel(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* domain,
	const BYTE* img,
	INT len
	);

/// ��ȡ������仯�ص�����
///	@param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	changedVersion	objectsTree�İ汾���к�
typedef void (CWALK_SDK_CALLBACK *CallBack_OnCamerasChangedNotify)(
	void* userParam,
	CWALK_NET_HD userHD,
	INT64 changedVersion
	);

///	����������仯�ص��������ݲ�֧��
///	@param[in]	userHD		        ��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnCamerasChangedNotify	�ص�����ָ�룬���ΪNULL����ȡ���ص�
/// @param[in]	userParam	        �û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCamerasChangedNotify(
	CWALK_NET_HD userHD,
	CallBack_OnCamerasChangedNotify fnOnCamerasChangedNotify,
	void* userParam
	);

/// ��ȡ������仯�汾��Ϣ���ݲ�֧��
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	changedVersion	������仯�汾
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCamerasChangedVersion(
	CWALK_NET_HD userHD,
	INT64* changedVersion
	);

///	��ȡ��֤��
///	@param[in]	ipOrHost	��֤������IP��DCSʱΪcmservice��ip
///	@param[in]	port		��֤�������˿ڣ�DCSʱΪcmservice�Ķ˿�
///	@param[in]	userName	��¼�û���
///	@param[in]	passwd		��¼����
/// @param[out] infoBuf		������֤��Ϣ,�ڴ�ռ��ɵ����߷���
/// @param[in]  len			infoBuf����
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTicket(
	const TCHAR* ipOrHost,
	INT port, 
	const TCHAR* userName, 
	const TCHAR* passwd,
	BYTE* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

///	ͨ����֤��Ϣ��¼������
/// @param[out]	userHD		�õ��û���¼���
///	@param[in]	ipOrHost	������ip��dns
///	@param[in]	port		�������˿�
///	@param[in]	ticket	    ��֤��Ϣ����CWALK_NET_GetTicket()���
///	@param[in]	len		    ��֤��Ϣ����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByTicket(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port, 
	BYTE* ticket,
	INT len
	);

///	�ǳ�DCS������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Logout(
	CWALK_NET_HD userHD
	);

/// ����������������״̬
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	connect		����״̬��TRUE-����״̬��FALSE-����״̬
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_IsConnected(
	CWALK_NET_HD userHD, 
	BOOL* connect
	);

/// ��ȡ������ʱ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] dateTime	���ص�ʱ�䣬�ڴ�ռ��ɵ����߷���,��ʽΪ:"2020-01-01 13:20:00.000"
/// @param[in]  len			dateTime�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerTime(
	CWALK_NET_HD userHD,
	TCHAR* dateTime,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���÷�����ʱ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	dateTime	����ʱ��,��ʽ��"2020-01-01 13:20:00.000" �� "20200101132000000"
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetServerTime(
	CWALK_NET_HD userHD,
	const TCHAR* dateTime
	);

/// ���豸ʱ��ͬ��Ϊ������ϵͳʱ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
///							plus�зǿ�ʱ��ʾ�豸��ͨ��uuid
///	@param[in]	camPath	    ��������ΪID
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SyncDeviceTime(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	const TCHAR* camPath
	);

///	�õ��û���������Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	buf			���������Ϣ�ĵ�ַ���ڴ�ռ��ɵ����߷��䣻���ΪNULL���򷵻�������Ϣ��ʵ�ʳ��ȡ�
/// @param[in,out] bufLen   �����߷�����ڴ�ռ�ĳ��ȣ����ؿ�����buf�����ݵĳ���
/// @param[out]	dataLen		����������Ϣ��ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserDescription(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT* bufLen,
	INT* dataLen /*= NULL*/
	);

///	�޸��û����루��֧�֣�
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	oldPasswd	������
/// @param[in]  newPasswd	������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetUserPasswd(
	CWALK_NET_HD userHD,
	const TCHAR* oldPasswd,
	const TCHAR* newPasswd
	);

///	��ȡ�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	buf			����û����ݣ��ڴ�ռ��ɵ����߷��䣻���ΪNULL���򷵻��û����ݵ�ʵ�ʳ��ȡ�
/// @param[in]  bufLen		�����߷�����ڴ�ռ�ĳ���
/// @param[out]	dataLen		�����û����ݵ�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserData(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT bufLen,
	INT* dataLen /*= NULL*/
	);

///	�����û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	data		�û�����
/// @param[in]	dataLen		�û����ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetUserData(
	CWALK_NET_HD userHD,
	void* data,
	INT dataLen
	);

/// �о��û��ص�����
///	@param[in]	userParam	�û�����
///	@param[in]	jsonInfo	�����û���Ϣ json���ݽṹ
///					"onlineStatus":			����״̬ int
///					"departmentCode":		��֯������ str
///					"departmentName" :		��֯�������� str
///					"id" :					�û�ID str
///					"name" :				�û����� str
///					"userParam":			�û����� str
///					"loginName" :			�û���½���� str
///					"level" :				�û����� int
///					"watermarking" :		�Ƿ�ˮӡ str
///					"watermarkingTitle" :	ˮӡ���� str
///					"nodeId" :				�û�����ID str
typedef void (CWALK_SDK_CALLBACK *CallBack_OnListUsers)(
	void* userParam,
	const TCHAR* jsonUserInfo
	);

///	�о��û���Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnUsers	�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListUsers(
	CWALK_NET_HD userHD,
	CallBack_OnListUsers fnOnUsers,
	void* userParam
);

/// �о������û��ص�����
///	@param[in]	userParam	�û�����
///	@param[in]	userName	�û���
///	@param[in]	userDomain	�û�������, dcs���dcm��ַ
/// @param[in]	authServe	�û���֤������, dcs+���dcm��ַ
///	@param[in]	rank		�û�ͷ��, dcs��֧��, ֵΪ��
///	@param[in]	role		�û���ɫ, dcsֵΪ��
///	@param[in]	userLocal	�û����ڵ�
///	@param[in]	level		�û�����
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetOnlineUsers)(
	void* userParam,
	const TCHAR* userName,
	const TCHAR* userDomain,
	const TCHAR* authServe,
	const TCHAR* rank,
	const TCHAR* role,
	const TCHAR* userLocal,
	INT level
	);

/// �о������û��ص�����
///	@param[in]	userParam	�û�����
///	@param[in]	onlineUser	�û���Ϣ
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetOnlineUsersEx)(
	void* userParam,
	CWALKOnlineUser * onlineUser
	);


///	�о������û���Ϣ��ע��ֻ���оٵ��ȵ�ǰ�û�����͵��û�
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[in]	fnOnUsers	�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOnlineUsers(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	CallBack_OnGetOnlineUsers fnOnUsers,
	void* userParam
	);

CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOnlineUsersEx(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	CallBack_OnGetOnlineUsersEx fnOnUsers,
	void* userParam
	);

/// �������Ĵ�����Ϣ�ص�����
///	@param[in]	userParam	�û�����
///	@param[in]	source		Դ��ַ�����ض��ַ�����ͷ
///

/// 
///	@param[in]	target		Ŀ�ĵ�ַ,���ض��ַ�����ͷ
///	

///	
///	@param[in]	users		ʹ���û��������Ƕ�����ԡ�;���������磺"user1;user2;user3..."
/// @param[in]	trunkin		��ʹ�õ��������
/// @param[in]	trunkout	��Ӧ���ص��������
/// @param[in]	gateway		����������������
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetTransferStatus)(
	void* userParam,	
	const TCHAR* source,
	const TCHAR* target,
	const TCHAR* users,
	const TCHAR* trunkin,
	const TCHAR* trunkout,
	const TCHAR* gateway
	);

/// ��ȡ�������Ĵ�����Ϣ,ע��ֻ�ܻ�ȡ���ȵ�¼�û�����͵Ĵ���ʹ����Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[in]	fnOnStatus	�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTransferStatus(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	CallBack_OnGetTransferStatus fnOnStatus,
	void* userParam
	);


typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetTransferStatusEx)(
	void* userParam,
	const TCHAR* objName,
	CWALKTransferStatus* statusInfo
	);

CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTransferStatusEx(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	CallBack_OnGetTransferStatusEx fnOnStatus,
	void* userParam
	);

/// �õ���������״̬��Ϣ��dcs��֧��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]  serviceType ����������
/// @param[out] infoBuf		����ɷ��������ص���Ϣ���ڴ���ʹ���߷���
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServiceStatus(
	CWALK_NET_HD userHD,
	CWALKNetServiceType serviceType,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// �õ���������ַ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]  serviceType ����������
/// @param[out] buf			����ɷ��������صĵ�ַ��Ϣ���ڴ���ʹ���߷���,�����ַ�ԡ�,���ָ�
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServiceAddrs(
	CWALK_NET_HD userHD,
	CWALKNetServiceType serviceType,
	void* buf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// �õ�������ƽ̨��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] buf			����ɷ��������ص���Ϣ���ڴ���ʹ���߷���
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerInfo(
	CWALK_NET_HD userHD,
	void* buf,
	INT* realLen /*= NULL*/
	);

/// ��ȡ���ӳ���ص�����
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	id			������
/// @param[in]	name		��������
/// @return
///	-	TRUE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListID)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* id,
	const TCHAR* name				
	);

/// ��ȡ���ӳ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	idType		������ͣ�1��ͨ���� 2����������������δʹ�� 
/// @param[out]	count		�оٵ��Ķ������
/// @param[in]	fnOnListID	���ӳ���ص�����
/// @param[in]	userParam	�û����ݣ���Ϊ�ص������Ĳ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetID(
	CWALK_NET_HD userHD,
	INT idType,
	INT* count /*=NULL*/,
	CallBack_OnListID fnOnListID /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// �����оٻص�����
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		�оٵ��豸����
/// @param[in]	objName		��������
/// @param[in]	objInfo		������������,����ͨ��CWALK_NET_InfoParseKeyValue()������
/// @return
///	-	TRUE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListObj)(
	void* userParam,
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* objName,
	const TCHAR* objInfo				
	);

/// �оٶ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		Ҫ�оٵ��豸����
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[out]	count		�оٵ��Ķ������
/// @param[in]	fnOnListObj	�����оٻص�����
/// @param[in]	userParam	�û����ݣ���Ϊ�ص������Ĳ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjects(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* serName /*=NULL*/,
	INT* count /*=NULL*/,
	CallBack_OnListObj fnOnListObj /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// �оٶ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		Ҫ�оٵ��豸����
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[out]	count		�оٵ��Ķ������
/// @param[in]	fnOnListObj	�����оٻص�����
/// @param[in]	userParam	�û����ݣ���Ϊ�ص������Ĳ�����
/// @param[in] isGetAllCamera �Ƿ��о�������Ȩ���豸��isGetAllCamera =TRUE&&GroupID == NULL,��ȡ���е��������isGetAllCamera=FALSE&& GroupID == null,��֮ǰ�Ļ����л�ȡ��Ӧ����Ϣ
/// @param[in] GroupID      �оٵ�ǰ�����µ���Ȩ�޵��豸��GroupID��= NULL,��ȡ��ǰGroupid��Ӧ�������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjectsEX(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* serName /*=NULL*/,
	INT* count /*=NULL*/,
	CallBack_OnListObj fnOnListObj /*= NULL*/,
	void* userParam /*= NULL*/,
	const TCHAR *GroupID,
	bool isGetAllCamera
	);

/// �оٶ��󣬽�����Ϊ�ַ���
///	@param[in]		userHD			��¼���,��CWALK_NET_Login()���
/// @param[in]		objType			Ҫ�оٵ��豸����
/// @param[in]		resultData		�оٽ��
/// @param[in/out]	resultLen		����ʱΪӦ�÷���resultData���ȣ����ʱΪ������ȡ����Ȳ���᷵�ض�Ӧ����
/// @param[in]		isGetAllCamera	�Ƿ��о�������Ȩ���豸��isGetAllCamera =TRUE&&GroupID == NULL,��ȡ���е��������isGetAllCamera=FALSE&& GroupID == null,��֮ǰ�Ļ����л�ȡ��Ӧ����Ϣ
/// @param[in]		GroupID			�оٵ�ǰ�����µ���Ȩ�޵��豸��GroupID��= NULL,��ȡ��ǰGroupid��Ӧ�������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjectsEXAsStr(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	TCHAR* resultData,
	INT64* resultLen,
	const TCHAR *GroupID,
	bool isGetAllCamera
	);

/// �����оٶ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		Ҫ�оٵ��豸����
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[out]	camInfo		�������Ϣ
/// @param[in,out] len			camInfo����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjectsBatch(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* serName /*=NULL*/,
	TCHAR* camInfo,
	INT* len
	);

/// �����о������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[out]	camInfo		�������Ϣ
/// @param[out] len			camInfo����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatch(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	TCHAR* camInfo,
	INT* len
	);

/// �����о������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[in] isGetAllCamera �Ƿ��о�������Ȩ���豸��isGetAllCamera =TRUE&&GroupID == NULL,��ȡ���е��������isGetAllCamera=FALSE&& GroupID == null,��֮ǰ�Ļ����л�ȡ��Ӧ����Ϣ
/// @param[in] GroupID      �оٵ�ǰ���飨�����������µ���Ȩ�޵��豸��GroupID��= NULL,��ȡ��ǰGroupid��Ӧ�������
/// @param[out]	camInfo		�������Ϣ
/// @param[out] len			camInfo����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchEx(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	const TCHAR *GroupID,
	bool isGetAllCamera,
	TCHAR* camInfo,
	INT* len
	);

/// �����о������ ��dcs�ݲ�֧�֣�
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[out]	camInfo		�������Ϣ
/// @param[out] len			camInfo����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchBinary(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	BYTE* camInfo,
	INT* len
	);

/// �����о�ҵ��������������DCS֧�֣�
/// @param[in]	serName		����������,��ΪNULL��_T("")ʱ����ʾ��ǰ��¼������
/// @param[in] isGetAllCamera �Ƿ��о�������Ȩ���豸��isGetAllCamera =TRUE&&GroupID == NULL,��ȡ���е��������isGetAllCamera=FALSE&& GroupID == null,��֮ǰ�Ļ����л�ȡ��Ӧ����Ϣ
/// @param[in] GroupID      �оٵ�ǰ���飨ҵ����飩�µ���Ȩ�޵��豸��GroupID��= NULL,��ȡ��ǰGroupid��Ӧ�������
/// @param[out]	camInfo		�������Ϣ
/// @param[out] len			camInfo����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchInVirtualGroup(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	const TCHAR *GroupID,
	bool isGetAllCamera,
	void* camInfo,
	INT* len
	);

/// ��̬��Ӷ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		Ҫ�оٵ��豸����
/// @param[in]	parent		��Ч����
/// @param[in]	objInfo		������������Ϣ,JSON��ʽ�ַ���,����CWALK_NET_InfoXXXϵ�к�������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_AddObject(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* parent /*=NULL*/,
	const TCHAR* objInfo
	);

/// ɾ������
/// @param[in]  userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]  objType		Ҫ�оٵ��豸����
/// @param[in]  objName		��������,������CallBack_OnListObj()�ص��е�objName
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_DelObject(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* objName
	);

/// �õ���֯�ṹ��Ϣ
/// @param[in]  userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	buf			�����֯�ṹ��Ϣ�ĵ�ַ���ڴ�ռ��ɵ����߷��䣻���ΪNULL���򷵻�������Ϣ��ʵ�ʳ��ȡ�
/// @param[in,out] bufLen   �����߷�����ڴ�ռ�ĳ��ȣ����ؿ�����buf�����ݵĳ���
/// @param[out]	dataLen		������֯�ṹ��Ϣ��ʵ�ʳ���
/// @param[out] orgCount	������֯�ṹ�ڵ����
/// @param[out] dcsCount	������֯�ṹ��dcs�ĸ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOrganization(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT* bufLen,
	INT* dataLen /*= NULL*/,
	INT* orgCount /*= NULL*/,
	INT* dcsCount /*= NULL*/
	);

/// �õ�����ṹ��Ϣ��groupID��
/// @param[in]  userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	buf			�����֯�ṹ��Ϣ�ĵ�ַ���ڴ�ռ��ɵ����߷��䣻���ΪNULL���򷵻�������Ϣ��ʵ�ʳ��ȡ�
/// @param[in,out] bufLen   �����߷�����ڴ�ռ�ĳ��ȣ����ؿ�����buf�����ݵĳ���
/// @param[out]	dataLen		������֯�ṹ��Ϣ��ʵ�ʳ���
/// @param[out] orgCount	������֯�ṹ�ڵ����
/// @param[out] dcsCount	������֯�ṹ��dcs�ĸ���
/// @param[in] bUseUserID	�Ƿ�ʹ��userID
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOrganizationEX(
	CWALK_NET_HD userHD, 
	void* buf /*= NULL*/, 
	INT* bufLen, 
	INT* dataLen /*= NULL*/, 
	INT* orgCount /*= NULL*/,
	INT* dcsCount /*= NULL*/,
	BOOL bUseUserID
	);

/// �õ�����ṹ��Ϣ��groupID��
/// @param[in]  userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	groupType	�������ͣ����CWALKNetGroupType, CWALKNET_GROUPTYPE_UNKNOW�򷵻���������+ҵ����顣
/// @param[in]	buf			�����֯�ṹ��Ϣ�ĵ�ַ���ڴ�ռ��ɵ����߷��䣻���ΪNULL���򷵻�������Ϣ��ʵ�ʳ��ȡ�
/// @param[in,out] bufLen   �����߷�����ڴ�ռ�ĳ��ȣ����ؿ�����buf�����ݵĳ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetGroup(
	CWALK_NET_HD userHD,
	CWALKNetGroupType groupType,
	void* buf,
	INT* bufLen
	);

/// �õ���¼�������ı���
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	serverName	��Ч����
/// @param[out] infoBuf		��ŵ�¼�������ı��⣬�ڴ���ʹ���߷���
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerTitle(
	CWALK_NET_HD userHD,
	const TCHAR* serverName /*= NULL*/,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// �õ���¼������������
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[out] infoBuf		��ŵ�¼�����������ƣ��ڴ���ʹ���߷���
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerName(
	CWALK_NET_HD userHD,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ��ȡ����״̬
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objType		Ҫ�оٵ��豸����
/// @param[in]	objName		��������, ������CallBack_OnListObj�ص��е�objName
/// @param[out]	status		0 - ���ߣ�С��0ֵ - �����ߣ����� �� ������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetObjectStatus(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* ojbName,
	INT* status
	);

/// ��ȡ�����״̬	DCS.1���ز����������ID  DCS���������״̬
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objName		��������, ������CallBack_OnListObj�ص��е�objName
///							Ϊ��ʱ��ʾ��ѯ�����������״̬
/// @param[out]	buf			���״̬��Ϣ,�ڴ�ռ��ɵ����߷��䣬�������ͨ��CWALK_NET_InfoParseKeyValue()������
/// @param[in]	bufLen		buf����
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCameraStatus(
	CWALK_NET_HD userHD,
	const TCHAR* ojbName,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// ��ȡͨ��¼��ƻ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objName		��������, ������CallBack_OnListObj�ص��е�objName
/// @param[out]	buf			���״̬��Ϣ,�ڴ�ռ��ɵ����߷���
/// @param[in]	bufLen		buf����
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetRecordSchedule(
	CWALK_NET_HD userHD,
	const TCHAR* ojbName,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// ����������ļ���
/// ע�����óɹ�֮�󣬵��ڴ˼�����û�ͼ�󽫻ᱻ�ر�
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] level		Ҫ���õļ��𣬷�Χ��[0��256]��0 �� ��ʾû�����ƣ�
///								��0 �� ֵԽ��Ȩ��Խ�ߣ����Ϊ�û�����ļ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCameraLevel(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT level
	);

/// ��ʼ������ֶ�¼��, ע:�ֶ�¼���ڵǳ��󽫻��Զ�ֹͣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		AV������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath
	);

/// ��ʼ������ֶ�¼��, ע:�ֶ�¼���ڵǳ��󽫻��Զ�ֹͣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		AV������
///	@param[in]	duration	¼��ʱ������λms���ɵ���CWALK_NET_StopRecord��ǰֹͣ
///	@param[in]	saveTime	¼�񱣴�ʱ�䣬��λ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRecordEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT64 duration,
	INT saveTime
	);

/// ֹͣ������ֶ�¼��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		AV������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath
	);

/// �о�¼��ʱ���
/// @param[in] userParam	�û�����
/// @param[in] userHD		��¼���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	ʱ��ο�ʼʱ��,��ʽ��"2020-01-01 13:20:00.000"
/// @param[in] endTime		ʱ��ν���ʱ�䣨������
/// @param[in] vodType		¼��λ�����ͣ��ڷ�ihost�����£�0Ϊ��������SS����1Ϊǰ���豸��
/// @return
///	-	TURE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListSegments)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime
	//const INT vodType
	);

typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListSegmentsInfo)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CWALKVodRecordInfo * recordInfo
	);


/// ��ѯ¼��
/// ע: �Ƿ�¼��ʱ��λᱻ���˵�,������Ϣ��¼����־��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0-������¼��, ��0 ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2020-01-01 13:20:00.000" �� "20200101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnOnListSegment	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordInfo(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegmentsInfo fnOnListSegment,
	void* userParam /*= NULL*/
	);

/// ��ѯ¼��
/// ע: �Ƿ�¼��ʱ��λᱻ���˵�,������Ϣ��¼����־��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnOnListSegment	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordExp(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);


/// �о�¼��ʱ���
/// @param[in] userParam	�û�����
/// @param[in] userHD		��¼���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	ʱ��ο�ʼʱ��,��ʽ��"2012-01-01 13:20:00.000"
/// @param[in] endTime		ʱ��ν���ʱ�䣨������
/// @param[in] segType		¼�����ͺ�¼����ȣ����һ���ֽ���¼����ȣ�ǰ����ֽ���¼�����ͣ���¼������ȡֵ
///		0 - �Զ�¼�� 
///		1 - Ԥ¼��
/// 	2 - �ֶ�¼��
/// @return
///	-	TURE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListSegmentsEx)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime, 
	INT	segType
	);

/// ��ѯ¼��
/// ע: �Ƿ�¼��ʱ��λᱻ���˵�,������Ϣ��¼����־��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0-������¼��, ��0 ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnOnListSegment	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegmentsEx fnOnListSegment,
	void* userParam /*= NULL*/
	);


/// �Զ���ѯ¼��
/// ע: �Ƿ�¼��ʱ��λᱻ���˵�,������Ϣ��¼����־��
/// �Զ���ѯ¼�񣬷��ص�һ�β�ѯ����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnOnListSegment	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordAuto(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);

/// ����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ProtectRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime
	);

/// ���¼�񱣻�
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_UnprotectRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime
	);

/// �о��ܱ���¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] fnOnListSegment	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryProtectionRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);

/// ��ȡvod״̬
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	status		�����״ֵ̬,����DCS
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetVodStatus(
	CWALK_NET_HD userHD,
	INT* status
	);

/// ��̨���ƣ�ͨ���û������
/// ע:��̨��ÿһ��������Ҫ���øýӿ�����,ǰ����������һ��,ֻ��paramһ��Ϊ��0,һ��Ϊ0
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] cmd			��̨��������
/// @param[in] param		����ֹ̨ͣ�������ǿ�ʼ����: >0 - ���趨�ٶȿ�ʼ;0 - ֹͣ,���ΪCWALKNET_PTZ_MAX_SPEED
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzControl(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CWALKNetPTZCommand cmd,
	INT param
	);

/// ��̨�������ؿ���
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] num			���ر��
/// @param[in] control		���Ʋ�����TRUE - �򿪣�FALSE �� �ر�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzAuxControl(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT num,
	BOOL control
	);

/// 3D��̨���ƣ�ͨ���û������
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] direct		��������,0 - �Ŵ�1 - ��С��2 - ���桢���� - δʹ��
/// @param[in] x			���Ʋ���,ȡֵ��Χ[0 - 1]
/// @param[in] y			���Ʋ���,ȡֵ��Χ[0 - 1]
/// @param[in] w			���Ʋ���,ȡֵ��Χ[0 - 1]
/// @param[in] h			���Ʋ���,ȡֵ��Χ[0 - 1]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_NET_PtzControl3D(
	CWALK_NET_HD userHD, 
	const TCHAR* avPath, 
	INT direct,
	float x,
	float y,
	float w,
	float h
	);

/// PTZ��������
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] lockTime		PTZ��������ʱ�� ��λΪ��(s)��0��ʾ��������0��ʾ����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzLock(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT lockTime
	);

/// ��̨������չ��ͨ���û������
/// ע:��̨��ÿһ��������Ҫ���øýӿ�����,ǰ����������һ��,ֻ��paramһ��Ϊ��0,һ��Ϊ0
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] cmd			��̨��������
/// @param[in] param		
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzControlEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CWALKNetPTZCommand cmd,
	const TCHAR* param
	);

/// ����Ԥ��λ��ͨ���û������
///	@param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		AV������
/// @param[in] name			Ԥ��λ����
/// @param[in] param		Ԥ��λ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzSetView(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* name,
	INT index
	);

/// ��ȡԤ��λ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		���������
/// @param[out]	bufInfo		Ԥ��λ��Ϣ��json��ʽ��[{"name":"set1", "index":1},{}]
/// @param[in]	len			bufInfo�ĳ���
/// @param[out]	realLen		�������ݵ�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzListView(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	void* bufInfo,
	INT len,
	INT* realLen
	);

/// ��ȡ��̨״̬
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[out] statusBuf	���PTZ��״̬��Ϣ���ڴ���ʹ���߷��䣬��Ϣ����ͨ��CWALK_NET_InfoParseKeyValue()������
/// @param[in]  bufLen		statusBuf�ĳ���
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzStatus(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	void* statusBuf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// ��ȡ��̨PTZ����������Ϣ
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[out] buf			���PTZ��������Ϣ���ڴ���ʹ���߷��䣬��ϢΪJson��ʽ�ַ���
/// @param[in]  bufLen		buf�ĳ���
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzPosition(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// ��ȡGIS��Ϣ
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	avPath		��������
/// @param[out] buf			���GIS��Ϣ���ڴ���ʹ���߷��䣬��ϢΪJson��ʽ�ַ���
/// @param[in]  bufLen		buf�ĳ���
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCameraGis(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);


/// GIS��Ϣ���Ļص�����
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	camPath		��������
/// @param[out] buf			���GIS��Ϣ����ϢΪJson��ʽ�ַ���
/// @param[in]  bufLen		buf�ĳ���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGisInfoUpload)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	const void* buf,
	const INT bufLen
	);

/// ����GIS��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnEvent	�����¼��Ļص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeGisInfo(
	CWALK_NET_HD userHD,
	CallBack_OnGisInfoUpload fnOnGisInfo,
	void* userParam
	);

/// �˶�GIS��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelGisInfoSubscription(
	CWALK_NET_HD userHD
	);

/// ������������GIS��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnEvent	�����¼��Ļص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeGisInfoByActive(
	CWALK_NET_HD userHD,
	CallBack_OnGisInfoUpload fnOnGisActive,
	void* userParam
);

/// �˶���������GIS��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelGisInfoSubscriptionByActive(
	CWALK_NET_HD userHD
);

/// ץȡͨ��ͼƬ��ͨ���������ֱ�ӷ��ص�ʵʱͼƬ��
/// @param[in]	userHD			��¼���,��CWALK_NET_Login()���
/// @param[in]	avPath			��������
/// @param[out] picResolution	ͼƬ�ֱ��ʣ�1920x1080...��
/// @param[out] picFormat		ͼƬ��װ��ʽ��jpeg,png,gif...��
/// @param[out] picBuff			���ͼƬ���������ݣ��ڴ���ʹ���߷���
/// @param[in]  buffLen			picBuff�ĳ���
/// @param[out] realLen			����ʵ����Ϣ�ĳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CapCameraPicture(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	TCHAR* picResolution,
	TCHAR* picFormat,
	TCHAR* picBuff,
	INT  buffLen,
	INT* realLen
);

/// ��������ͨ��
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraReset(
	CWALK_NET_HD userHD,
	const TCHAR* camPath
	);

/// ��ȡ����ͨ����ɫ���ڲ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[out]	brightness	���ȣ�  ֵΪ[-127,127]
/// @param[out]	contrast	�Աȶȣ�ֵΪ[-127,127]
/// @param[out]	saturation	���Ͷȣ�ֵΪ[-127,127]
/// @param[out]	hue			ɫ����  ֵΪ[-127,127]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraGetVideoColor(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT* brightness,
	INT* contrast,
	INT* saturation,
	INT* hue
	);

/// ��ȡ��Ƶͨ����Ƶ����
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[out]  channels		ͨ����
/// @param[out]  bitsPerSample	ÿ����λ��
/// @param[out]  samplesPerSec		ÿ��������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������

/// ��������ͨ����ɫ���ڲ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[in]	brightness	���ȣ�  ֵΪ[-127,127]
/// @param[in]	contrast	�Աȶȣ�ֵΪ[-127,127]
/// @param[in]	saturation	���Ͷȣ�ֵΪ[-127,127]
/// @param[in]	hue			ɫ����  ֵΪ[-127,127]
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraSetVideoColor(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT brightness,
	INT contrast,
	INT saturation,
	INT hue
	);

/// ��ȡ����ͨ���������
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[out]	standard	��Ƶ��ʽ 0: NTSC 1: PAL
/// @param[out]	frameRate	֡Ƶ ��PAL����ȡֵ1-25, NTSC����1-30
/// @param[out]	width		���
/// @param[out]	height		�߶�
/// @param[out]	bitRate		������;Ϊ0��ʾ���޶�������, ��0��ʾ�޶���������, ��λbits/sec
/// @param[out]	quality		ͼ������ ȡֵ0~31, ֵԽСͼ������Խ��
/// @param[out]	iFrameInterval	I֡���(>=1)
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraGetVideoEncoder(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT* standard,
	INT* frameRate,
	INT* width,
	INT* height,
	INT* bitRate,
	INT* quality,
	INT* iFrameInterval
	);

/// ��������ͨ���������
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	camPath		��������
/// @param[in]	standard	��Ƶ��ʽ 0: NTSC 1: PAL
/// @param[in]	frameRate	֡Ƶ ��PAL����ȡֵ1-25, NTSC����1-30
/// @param[in]	width		���
/// @param[in]	height		�߶�
/// @param[in]	bitRate		������;Ϊ0��ʾ���޶�������, ��0��ʾ�޶���������, ��λbits/sec
/// @param[in]	quality		ͼ������ ȡֵ0~31, ֵԽСͼ������Խ��
/// @param[in]	iFrameInterval	I֡���(>=1)
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraSetVideoEncoder(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT standard,
	INT frameRate,
	INT width,
	INT height,
	INT bitRate,
	INT quality,
	INT iFrameInterval
	);
 
/// ִ�нű�
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	scriptType	�ű�����
/// @param[in]	script		�ű�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ExecuteScript(
	CWALK_NET_HD userHD,
	const TCHAR* scriptType,
	const TCHAR* script
	);

/// �¼����Ļص�����
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	happenTime	��������ʱ�� "2012-01-01 13:20:00.000"(������)
/// @param[in]	objName		������������,����Ϊ"$"��"host/"��"av/"��"ai/"��
///							plusΪ�豸uuid��"cms"
/// @param[in]	objInfo		�������ϱ���������Ϣ
/// @param[in]	eventType	�¼�����
/// @param[in]	status		�¼�״̬,1Ϊ����̬,0Ϊ����̬
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEvent)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* happenTime,
	const TCHAR* objName,
	const TCHAR* objInfo,
	CWALKNetEventType eventType,
	INT status
	);

/// �¼�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnEvent	�����¼��Ļص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEvent(
	CWALK_NET_HD userHD,
	CallBack_OnEvent fnOnEvent,
	void* userParam
	);

/// ȡ������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscription(
	CWALK_NET_HD userHD
	);

/// �������ݶ��Ļص�����
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objName		��������
/// @param[in]	data		��������
/// @param[in]	dataLen		�������ݳ���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEvent2)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* objName,
	const BYTE* data,
	INT dataLen
	);

/// �������ݶ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnEvent	�����¼��Ļص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEvent2(
	CWALK_NET_HD userHD,
	CallBack_OnEvent2 fnOnEvent,
	void* userParam
	);

/// ȡ���������ݶ���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscription2(
	CWALK_NET_HD userHD
	);

/// �������ݻص���������չ����������¼���������
/// @param[in]	userParam	�û�����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	objName		������������,����Ϊ"$"��"host/"��"av/"��"ai/"��
/// @param[in]	happenTime	��������ʱ�� "2012-01-01 13:20:00.000"(������)
/// @param[in]	eventType	�¼�����
/// @param[in]	data		�������ϱ���������Ϣ,����ͨ��CWALK_NET_InfoParseKeyValue()������
/// @param[in]	dataLen		�ϱ���Ϣ���ݳ���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEventEx)(
	void* userParam,
	CWALK_NET_HD userHD,
	const char* objName,
	CWALKNetEventType eventType,
	INT64/*00*/ happenedTime,
	const void* data,
	INT_PTR dataLen
	);

/// �������ݶ��ģ���չ����������¼���������
///	ע: ����ʹ��CWALK_NET_CancelEventSubscriptionEx()ȡ������
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	userParam	�û�����
/// @param[in]	fnOnEvent	�����¼��Ļص�����
/// @param[in]	objNames	���ĵ��¼����󣬿����ж����ʹ���ַ�'\n'�ָ���NULL��ʾ�������У�
/// @param[in]	types		���ĵ��¼����ͣ������ж���������CWALKNET_EVENT_UNKNOWN��β��NULL��ʾ�������У�
/// @return
/// -	CWALKSDK_OK	�ɹ�
/// -	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEventEx(
	CWALK_NET_HD userHD,
	void* userParam,
	CallBack_OnEventEx fnOnEvent,
	const char* objNames,
	const CWALKNetEventType* types
	);

/// ȡ������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscriptionEx(
	CWALK_NET_HD userHD
	);

/// ������������������Ĵ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	source		���������
///							dcs+�в�����ʽͬCWALK_NET_StartStream
/// @param[in]	target		����������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartTransfer(
	CWALK_NET_HD userHD,
	const TCHAR* source,
	const TCHAR* target
	);

/// ������������������Ĵ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	source		���������
///							dcs+�в�����ʽͬCWALK_NET_StartStream
/// @param[in]	target		����������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartTransferEx(
	CWALK_NET_HD userHD,
	const TCHAR* source,
	const TCHAR* target,
	CWALKTransferOptions options
	);

/// ֹͣ��ĳ���������Ĵ���
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	target		����������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopTransfer(
	CWALK_NET_HD userHD,
	const TCHAR* target
	);


CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartVodTransfer(
	CWALK_NET_HD userHD,
	const TCHAR* source,
	const TCHAR* target,
	const TCHAR* window,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	INT16 vodType,
	const TCHAR* storage
	);

CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopVodTransfer(CWALK_NET_HD userHD, const TCHAR* target, const TCHAR* window);


/// �ָ�������Ĵ�������
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	target		���������ƣ�ͬһ��������������Ƶͨ����ţ�
/// @param[in]	window		���������������ţ�һ����������Ӧ���VO�����Ĭ��1��ʼ��
/// @param[in]	cnt			�ָ��������1��2��4��8��9....��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SplitScreen(CWALK_NET_HD userHD, const TCHAR* target, const TCHAR* window, const TCHAR* cnt);


/// ��ռ�ص�֪ͨ����
/// @param[in]	userParam	�û�����
/// @param[in]	streamHD	ʵʱ��Ƶ���,��CWALK_NET_StartStream()���
/// @param[in]	target		����ռ�ļ���������
/// @param[in]	robUser		��ռ�û�
/// @param[in]	robNode		��ռ���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnTransferRobbed)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* target,
	const TCHAR* robUser,
	const TCHAR* robNode
	);

/// �����л���ռ֪ͨ�ص�
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	fnOnRobbed  ��ռ֪ͨ�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetTransferRobbedCallBack(
	CWALK_NET_HD userHD,
	CallBack_OnTransferRobbed fnRobbed,
	void* userParam
	);

/// �����ݻص�����,��CWALK_NET_StartStream()��CWALK_NET_StartAudio��������CWALK_NET_StartPlaybackStream()����
/// @param[in]	userParam	�û�����
///	@param[in]	streamHD	���ž��
/// @param[in]	data		�ص�������
/// @param[in]	dataLen		�ص����ݳ���
typedef void (CWALK_SDK_CALLBACK *Callback_OnStreamData)(
	void* userParam,	
	CWALK_NET_HD streamHD,
	const void* data,
	INT dataLen
	);

/// �����ݻص�����,��CWALK_NET_StartPlaybackStreamEx()����
/// @param[in]	userParam	�û�����
///	@param[in]	streamHD	���ž��
/// @param[in]	data		�ص�������
/// @param[in]	dataLen		�ص����ݳ���
/// @param[in]	packageSeriNum		�ص���ǰ�������к�
typedef void (CWALK_SDK_CALLBACK *Callback_OnStreamDataEx)(
	void* userParam,	
	CWALK_NET_HD streamHD,
	const void* data,
	INT dataLen,
	INT64 packageSeriNum
	);


/// ʵʱ����ռ�ص�֪ͨ����
/// @param[in]	userParam	�û�����
/// @param[in]	streamHD	ʵʱ��Ƶ���,��CWALK_NET_StartStream()���
/// @param[in]	robUser		��ռ�û�
/// @param[in]	robNode		��ռ���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStreamRobbed)(
	void* userParam,
	CWALK_NET_HD streamHD,
	const TCHAR* robUser,
	const TCHAR* robNode	
	);

/// �첽ʵʱ��������Ϣ�ص�֪ͨ����
/// @param[in]	userParam	�û�����
/// @param[in]	streamHD	�첽ʵʱ��Ƶ���,��CWALK_NET_StartStreamByAsync()���
/// @param[in]  streamResult	�������
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStartRealStreamMsg)(
	void* userParam,
	CWALK_NET_HD streamHD,
	const CWALKSDKError streamResult
	);

/// ¼��ط���Ϣ�ص�
/// @param[in] userParam	�û�����
/// @param[in] streamHD		�طž��
/// @param[in] flag			-1   ����������
///							0    ���ݻص�����
///							1   ���ݻص���ʼ
///							2   ��¼���Ƿ�˽������δʹ�ã�
///							3   ��¼����˽������δʹ�ã�
///							4   ˢ�����ݣ�һ���ǵ���CWALK_NET_SetPlaybackStreamPos����յ�
///							5   �����ؿ��������˶��������¿���
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStreamMsg)(
	void* userParam,
	CWALK_NET_HD streamHD,
	INT flag
	);

/// ����ʵʱ��Ƶ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	streamHD	����ʵʱ�����ž��
///	@param[in]	avPath		AV������, ����"av/dcam/1", dcs����ĩβ��#����ý�����, ����video��audio��profile, ����ȡֵ��
///							video��H264  H265  MPEG4��audio��AAC G711 G726 G729��profile��CIF  D1  HD 0 1 2
///							����ý�����������ϣ����Ⱥ�˳������ #D1��#H264#HD#G711��#G711#HD#H264
///							profile�е�0��1��2��...������������
/// @param[in]	fnOnRealData ʵʱ�������ݻص�����
/// @param[in]	fnRobbed	��ռ֪ͨ�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartStream(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	void* userParam
	);

/// ����ʵʱ��Ƶ�����첽���ӣ���dcs+�нӿ�ͬCWALK_NET_StartStreamһ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	streamHD	����ʵʱ�����ž��
///	@param[in]	avPath		AV������
/// @param[in]	fnOnRealData ʵʱ�������ݻص�����
/// @param[in]	fnRobbed	��ռ֪ͨ�ص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartStreamByAsync(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStartRealStreamMsg fnMsg,
	void* userParam
	);

/// ֹͣʵʱ��Ƶ��
///	@param[in]	streamHD	ʵʱ��Ƶ���,��CWALK_NET_StartStream()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopStream(
	CWALK_NET_HD streamHD
	);

/// ʵʱ��Ƶ����I֡
///	@param[in]	streamHD	ʵʱ��Ƶ���,��CWALK_NET_StartStream()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StreamRequestIFrame(
	CWALK_NET_HD streamHD
	);

/// �򿪶Խ�ͨ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	audioHD		���ضԽ����
///	@param[in]	audioPath	�Խ�ͨ����
///							dcs+�в�����ʽͬCWALK_NET_StartStream
/// @param[in]	fnData		��Ƶ���ݻص�����
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartAudio(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* audioHD,
	const TCHAR* audioPath,
	Callback_OnStreamData fnData,
	void* userParam
	);
/// �򿪶Խ�ͨ��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	audioHD		���ضԽ����
///	@param[in]	audioPath	�Խ�ͨ����
///							dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in]  mode        ����ͨ��ģʽ
/// @param[in]	fnData		��Ƶ���ݻص�������mode = Talkʱ����Ϊ��
/// @param[in]	userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartAudioEx(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* audioHD,
	CWALKAudioMode mode,
	const TCHAR* audioPath,
	Callback_OnStreamData fnData,
	void* userParam
	);


/// ������Ƶ����
/// ע�����м�Ƶ���ݾ�Ϊ˳���������ʽΪPCM֡
/// @param[in]	audioHD		�Խ����,��CWALK_NET_StartAudio()���
/// @param[in]  channels	ͨ����
/// @param[in]  bitsPerSample	ÿ����λ��
/// @param[in]  channels	ÿ��������
/// @param[in]	buf			��Ƶ����
/// @param[in]	size		��Ƶ���ݳ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InputAudioData(
	CWALK_NET_HD audioHD,
	INT channels,
	INT bitsPerSample,
	INT samplesPerSec,
	BYTE* buf, 
	INT size
	);

/// �رնԽ�ͨ��
/// @param[in]	audioHD		�Խ����,��CWALK_NET_StartAudio()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopAudio(
	CWALK_NET_HD audioHD
	);

/// �㲥¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStream(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// �㲥¼������ȫ������¼��ʱ�ô�����Ĳ��Žӿ�
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStreamCache(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// �㲥¼�񣬵㲥��Ⱥ�洢��¼��ʱ����CRCУ��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStreambyCRC(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// ֹͣ¼��ط�
/// @param[in] streamHD	¼��طž��,��CWALK_NET_StartPlaybackStream()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStream(
	CWALK_NET_HD streamHD
	);

/// ��ȡ¼�񲥷Ž���
/// @param[in]	streamHD	¼��طž��,��CWALK_NET_StartPlaybackStream()�õ�
/// @param[out] pos			���ص�ǰ�Ĳ��Ž���,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPlaybackStreamPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// ����¼�񲥷�λ��
/// @param[in]	streamHD	¼��طž��,��CWALK_NET_StartPlaybackStream()�õ�
/// @param[in] pos			Ҫ���õĲ���λ��,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackStreamPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// �㲥¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStreamExp(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

/// �Զ��㲥¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStreamAuto(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

/// ֹͣ¼��ط�
/// @param[in] streamHD	¼��طž��,��CWALK_NET_StartPlaybackStreamAuto()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStreamAuto(
	CWALK_NET_HD streamHD
	);

/// ֹͣ¼��ط�
/// @param[in] streamHD	¼��طž��,��CWALK_NET_StartPlaybackStreamExp()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStreamExp(
	CWALK_NET_HD streamHD
	);

/// ��ȡ¼�񲥷Ž��ȣ�dcs+��ʵ��ͬCWALK_NET_GetPlaybackStreamPosһ��
/// @param[in]	streamHD	¼��طž��,��CWALK_NET_StartPlaybackStreamExp()�õ�
/// @param[out] pos			���ص�ǰ�Ĳ��Ž���,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPlaybackStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// ����¼�񲥷�λ��
/// @param[in]	streamHD	¼��طž��,��CWALK_NET_StartPlaybackStreamExp()�õ�
/// @param[in] pos			Ҫ���õĲ���λ��,����ڲ��ſ�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// @param[in]	streamHD	¼��طž��,��CWALK_NET_StartPlaybackStream()�õ�
/// @param[in]  bPause		true ��ͣ�����䣻 false ȡ����ͣ������������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetVodPause( 
	CWALK_NET_HD streamHD, 
	bool bPause 
	); //�˽ӿ�DCS��֧��

/// ����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼�����صľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStream(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

/// ¼�����أ�֧�ֶϵ�������
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] beginThisPackage	��ʼ�������ϵ�������
/// @param[in] beginNextPackage	�������� -1��ʾ��Ч��Ĭ��ʹ�ÿ�ʼ�������ɡ�
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamEx(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	INT64 beginThisPackage, 
	INT64 beginNextPackage,
	Callback_OnStreamDataEx fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

/// ֹͣ¼������
/// @param[in] streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStream()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStream(
	CWALK_NET_HD streamHD
	);

/// ��ͣ/����¼������ 
/// @param[in] streamHD	 ¼�����صľ�� 
/// @param[in] bPause	 ��ͣ/����¼�����أ�true��ͣ��false����¼������ 
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadPause( 
	CWALK_NET_HD streamHD, 
	bool bPause 
	);

/// ��ȡ¼�����ؽ��ȣ�dcs+��ʵ��ͬCWALK_NET_GetPlaybackStreamPosһ��
/// @param[in]	streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStream()�õ�
/// @param[out] pos			���ص�ǰ�����ؽ���,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetDownloadStreamPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// ����¼������λ��
/// @param[in]	streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStream()�õ�
/// @param[in] pos			Ҫ���õ�����λ��,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadStreamPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// ����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼�����صľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamExp(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// ֹͣ¼������
/// @param[in] streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStreamExp()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStreamExp(
	CWALK_NET_HD streamHD
	);

/// �Զ�����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼�����صľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamAuto(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// ֹͣ¼������
/// @param[in] streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStreamAuto()�õ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStreamAuto(
	CWALK_NET_HD streamHD
	);

/// ¼�����أ�֧�ֶϵ�������
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] beginThisPackage	��ʼ�������ϵ�������
/// @param[in] beginNextPackage	�������� -1��ʾ��Ч��Ĭ��ʹ�ÿ�ʼ�������ɡ�
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @param[in] type		osd����
/// @param[in] osdInfo	ˮӡ��Ϣ��CWALKOSDText��CWALKOSDLine��CWALKOSDRect�����е�һ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamExByOSD(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	INT64 beginThisPackage, 
	INT64 beginNextPackage,
	CWALKOSDType type, 
	const void* osdInfo,
	Callback_OnStreamDataEx fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// ����¼��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼�����صľ��
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @param[in] type			osd����
/// @param[in] osdInfo		ˮӡ��Ϣ��CWALKOSDText��CWALKOSDLine��CWALKOSDRect�����е�һ��
/// @return
/// ע��10.2sdk �˽ӿ���Ч ��ͨ��CWALK_FILE_OpenWritbaleFile�ӿڴ��� ���� CWALK_FILE_WriteOsdInfo�ӿ�д��osd��Ϣ
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamByOSD(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CWALKOSDType type, 
	const void* osdInfo,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStreamMsg fnMsg,
	void* userParam
	);

/// ��ȡ¼�����ؽ��ȣ�dcs+��ʵ��ͬCWALK_NET_GetPlaybackStreamPosһ��
/// @param[in]	streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStreamExp()�õ�
/// @param[out] pos			���ص�ǰ�����ؽ���,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetDownloadStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// ����¼������λ��
/// @param[in]	streamHD	¼�����ؾ��,��CWALK_NET_StartDownloadStreamExp()�õ�
/// @param[in] pos			Ҫ���õ�����λ��,����ڵ�ǰʱ��ο�ʼʱ��ĺ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);


/// ���ûط��ٶ�
/// @param[in]	speed		0������ͣ������ȡֵ1.0��2.0��4.0��8.0��16.0��32.0��0.5��0.25��0.125��0.0625
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackSpeed(
	CWALK_NET_HD streamHD,
	double speed
	);

/// ��CWALKDB��д��־
///		
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	logType		��־����
/// @param[in]	info		��־��Ϣ��JSON��ʽ�ַ���������CWALK_NET_InfoHelperXXXϵ�к�����������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InsertLog(
	CWALK_NET_HD userHD,
	CWALKNetLogType logType,
	const TCHAR* info
	);

/// CWALKDB��־��ѯ����ص�����
///		
/// @param[in]	logType		��־����
/// @param[in]	logInfo		��ѯ�������
/// @param[in]  userParam	�û�����
/// @return
///	-	TURE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnQueryLog)(
	CWALKNetLogType logType,
	const TCHAR* logInfo,
	void* userParam 
	);

/// ��ѯCWALKDB��־
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	logType		��ѯ����
/// @param[out]	isEnd		��ѯ�Ƿ������TRUE������û�����ݣ�FALSE�����滹������
/// @param[in]	queryInfo	��ѯ������JSON��ʽ�ַ���������CWALK_NET_InfoHelperXXXϵ�к�����������
/// @param[in]  fnQueryLog	��ѯ����ص�����ָ��
/// @param[in]  userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryLog(
	CWALK_NET_HD userHD,
	CWALKNetLogType logType,
	BOOL* isEnd /*=NULL*/,
	const TCHAR* queryInfo,
	CallBack_OnQueryLog fnQueryLog,
	void* userParam/*= NULL*/
	);

/// ������ƻص�����
/// @param[in]	tagName		�������
/// @param[in]  userParam	�û�����
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetTagNames)(
	const TCHAR* tagName,
	void* userParam 
	);

/// ������б������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	nameCount	���ر�����Ƹ���
/// @param[in]	fnOnNames	������ƻص�����ָ��
/// @param[in]  userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTagNames(
	CWALK_NET_HD userHD,
	INT* nameCount /*= NULL*/,
	CallBack_OnGetTagNames fnOnNames,
	void* userParam /*= NULL*/
	);

/// �޸ı������
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	oldTagName	�ɱ������,������CWALK_NET_GetTagNames()�л�õ�����
///	@param[in]	newTagName	�±������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ModifyTagName(
	CWALK_NET_HD userHD,
	const TCHAR* oldTagName,
	const TCHAR* newTagName
	);

/// ���֡���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	tagName		�������,������CWALK_NET_GetTagNames()�л�õ�����
///	@param[in]	tagTime		���ʱ��,Ĭ��Ϊ������ϵͳʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
///	@param[in]	channelName	ͨ������,��:"av/dcam/1"
///	@param[in]	description	���������Ϣ
///	@param[in]	tagType		�������0 - �Զ�;1 - �ֶ�;���� - δʹ��
///	@param[in]	level		��Ǽ���,ȡֵ[1-5],1-����Ҫ;2-��̫��Ҫ;3-һ��;4-��Ҫ;5-����Ҫ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_AddTag(
	CWALK_NET_HD userHD,
	const TCHAR* tagName,
	const TCHAR* tagTime /*= NULL*/,
	const TCHAR* channelName,
	const TCHAR* description /*= NULL*/,
	INT tagType,
	INT level
	);

/// ֡��ǲ�ѯ�ص�����
/// @param[in]	tagInfo		֡�����Ϣ, JSON��ʽ�ַ���,����ͨ��CWALK_NET_InfoParseXXXX()ϵ�к���������
///		
///		�����Ϣ���������£�
///			id				������¼�����ݿ��е�����ID
///			tagName			�������
///			tagTime			���ʱ��
///			channelName		ͨ������
///			description		���������Ϣ
///			tagType			������� 0 - �Զ�;1 - �ֶ�;���� - δʹ��
///			level			��Ǽ���,ȡֵ[1-5],1-����Ҫ;2-��̫��Ҫ;3-һ��;4-��Ҫ;5-����Ҫ
///			createUser		��Ǵ�����
///			createTime		��Ǵ���ʱ��
///			modifyUser		���һ���޸���
///			modifyTime		���һ���޸�ʱ��
///
/// @param[in]  userParam	�û�����
/// @return
///	-	TURE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnQueryTag)(
	const TCHAR* tagInfo,
	void* userParam
	);

/// ��ѯ֡���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	condition	��ѯ����,JSON��ʽ�ַ���������CWALK_NET_InfoHelperXXXϵ�к�����������
///
///		��ѯ����Ϊ����һ�ֻ���ֵ���ϣ�
///			maxCount		[INT]	 �������ݵ����������Ĭ��ֵ��1000�����ֵ��2000
///			startPos		[INT]	 ���ݷ�����ʼλ�ã�Ĭ��ֵ��0
///			tagNames		[string] ������ƣ�������CWALK_NET_GetTagNames()�õ������ƣ�֧�ֶ��������á�;���������磺"��ܱ��;�������;�������"
///			channelNames	[string] ͨ�����ƣ�֧�ֶ����֧��ģ����ѯ������á�;���������磺"av/dcam/1;av/dcam/2;av/dcam/3"
///			beginTagTime	[string] ��ʼ���ʱ�䣬��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
///			endTagTime		[string] �������ʱ�䣨������
///			beginCreateTime [string] ��ʼ����ʱ�䣬��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
///			endCreateTime	[string] ��������ʱ�䣨������
///			beginModifyTime [string] ��ʼ�޸�ʱ�䣬��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
///			endModifyTime	[string] �����޸�ʱ�䣨������
///			tagType			[INT]	 ������� 0 - �Զ�;1 - �ֶ�;���� - δʹ��
///			level			[INT]	 ��Ǽ���,ȡֵ[1-5],1-����Ҫ;2-��̫��Ҫ;3-һ��;4-��Ҫ;5-����Ҫ
///			createUser		[string] �����û���ע����֧��ģ����ѯ
///			modifyUser		[string] ���һ���޸��û���ע����֧��ģ����ѯ
///			description		[string] ������Ϣ��֧�ֹؼ���ģ����ѯ
///
/// @param[out] recordCount	���������ص���������
/// @param[out]	isEnd		�Ƿ��Ѳ�ѯ�����, TRUE - �Ѿ���ѯ�����FALSE - δ��ѯ����󣬺��滹�з��ϲ�ѯ����������δ����
/// @param[out]	fnOnQueryTag֡��ǲ�ѯ�ص�����ָ��
/// @param[in]  userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryTag(
	CWALK_NET_HD userHD,
	const TCHAR* condition,
	INT* recordCount /*= NULL*/,
	BOOL* isEnd /*= NULL*/,
	CallBack_OnQueryTag fnOnQueryTag /*= NULL*/, 
	void* userParam /*= NULL*/
	);

/// ɾ��֡���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	tagIdArray	֡���ID����
/// @param[in]	arrayLen	���鳤��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_DeleteTags(
	CWALK_NET_HD userHD,
	INT64 tagIdArray[],
	INT arrayLen
	);

/// �޸�֡���
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	tagId		֡���ID
/// @param[in]	tagName		�޸ĺ��֡������ƣ�������CWALK_NET_GetTagNames()�õ�������
/// @param[in]	description �޸ĺ������
/// @param[in]	Level		�޸ĺ�ļ���	
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ModifyTag(
	CWALK_NET_HD userHD,
	INT64 tagId,
	const TCHAR* tagName /*= NULL*/,
	const TCHAR* description /*= NULL*/,
	INT level
	);

/// ��ȡ��̨��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		���������
/// @param[out]	bufInfo		��̨��Ϣ������ͨ��CWALK_NET_InfoParseKeyValue()������
/// @param[in]	len			bufInfo�ĳ���
/// @param[out]	realLen		�������ݵ�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzInfo(
	CWALK_NET_HD userHD,
	const TCHAR* avPaht,
	void* bufInfo,
	INT len,
	INT* realLen
	);

/// ������̨��Ϣ
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	avPath		���������
/// @param[in]	ptzinfo		��̨��Ϣ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPtzInfo(
	CWALK_NET_HD userHD,
	const TCHAR* avPaht,
	CWALKNetPTZPos ptzinfo
	);

/// ͸��cmserviceָ�dcsר��
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[in]	funcPost	http post�Ľӿ���������GetServiceStatus
/// @param[in]	msgPost		post��msg������{"GetServiceStatus":{"serviceType":"streamingservice"}}
/// @param[out]	outResult   ������,json��ʽ
/// @param[in]  len			outResult�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CmsHttpPost(
	CWALK_NET_HD userHD,
	const TCHAR* funcPost,
	const TCHAR* msgPost,
	void* outResult,
	INT len,
	INT* realLen
	);

/// ���������������,���ڽ��� CWALK_NET_GetOrganization() ���ص���֯�ṹ��Ϣ
/// @param[in]  info		��֯�ṹ��Ϣ
/// @param[in]  type		��֯�ṹ���ͣ�1 - ��ʾ��֯�ṹ�ڵ㣻2 - ��ʾdcs�ڵ㣻����  - δʹ��
/// @param[in]  index		�ڵ�����
/// @param[in]  key			�ڵ�����
/// @param[out] valueBuf	��Žڵ�����ԣ��ڴ�ռ���ʹ���߷���
/// @param[in]  len			valueBuf�Ĵ�С
/// @param[out] realLen		�������Ե�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ParseOrganizationInfo(
	const TCHAR* info,
	INT type,
	INT index, 
	const TCHAR* key,
	void* valueBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���������������,���ڽ���Key-Value��ʽJSON�ַ���
/// @param[in]	objInfo		JSON��ʽ�ַ���
/// @param[in]	key			Ҫ��������Ϣ
/// @param[out]	valueBuf	���key����Ӧ��ֵ,�ڴ���ʹ���߷���
/// @param[in]	len			valueBuf�Ĵ�С
/// @param[out] realLen		�������Ե�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyValue(
	const TCHAR* objInfo,
	const TCHAR* key,
	void* valueBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���������������,���ڻ�ȡKey-Value��ʽJSON�ַ������Ӽ�Key����
/// @param[in]	objInfo		JSON��ʽ�ַ���
/// @param[out]	namesBuf	���key������Ϣ����ʽΪkey1,key2,key3�ȵ�
/// @param[in]	len			namesBuf�Ĵ�С
/// @param[out]	realLen		�������Ե�ʵ�ʳ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyGetMemberNames(
	const TCHAR* objInfo,
	void* namesBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���������������,���ڻ�ȡKey-Value��ʽJSON�ַ����Ӽ���������
/// @param[in]	objInfo		JSON��ʽ�ַ���
/// @param[in]	key			JSON�����ʶ������Ϣ
/// @param[out]	count		��JSON����ĸ���
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyArrayValueCount(
	const TCHAR* objInfo,
	const TCHAR* key,
	INT* count
	);

/// ���������������,���ڻ�ȡKey-Value��ʽJSON�ַ����Ӽ�����ָ��������JSON��
/// @param[in]	index		��JSON������
/// @param[in]	objInfo		JSON��ʽ�ַ���
/// @param[in]	key			Ҫ��������Ϣ
/// @param[out]	objBuf		�����JSON��,�ڴ���ʹ���߷���
/// @param[in]	len			objBuf�Ĵ�С
/// @param[out] realLen		�������Ե�ʵ�ʳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyIndexArrayValue(
	INT index,
	const TCHAR* objInfo,
	const TCHAR* key,
	void* objBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// ���������������,���ڽ���Key-Value��ʽJSON�ַ���
/// @param[in]	objInfo		JSON��ʽ�ַ���
/// @param[in]	key			Ҫ��������Ϣ
/// @param[out]	value		���key����Ӧ��ֵ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseIntKeyValue(
	const TCHAR* objInfo,
	const TCHAR* key,
	INT* value
	);

/// ����Key-Value��ʽ��������,����һ��Key-Value��ʽJSON�ַ���������
/// @param[out]	helpHD		����helpHD, ע������֮��,����ʹ��CWALK_NET_InfoHelperRelease()�ͷ�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCreate(
	CWALK_HELP_HD* helpHD
	);

/// ������Ϣ���ɰ�������,���key-value��������Ϣ
/// @param[in]	helpHD		�������������,��CWALK_NET_InfoHelperCreate()���
/// @param[in]	key			�������Լ�
/// @param[in]	value		��������ֵ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperAddKeyValue(
	CWALK_HELP_HD helpHD,
	const TCHAR* key,
	const TCHAR* value
	);

/// ������Ϣ���ɰ�������,���key-value��������Ϣ
/// @param[in]	helpHD		�������������,��CWALK_NET_InfoHelperCreate()���
/// @param[in]	key			�������Լ�
/// @param[in]	value		��������ֵ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperAddIntKeyValue(
	CWALK_HELP_HD helpHD,
	const TCHAR* key,
	INT value
	);

/// ������Ϣ���ɰ�������,�õ��������е�����
/// @param[in]	helpHD		�������������,��CWALK_NET_InfoHelperCreate()���
/// @param[out] buf			��������ַ
///								ע��һ������CWALK_NET_InfoHelperRelease()֮��,
///								���еķ�������ȫ��ʧЧ,����ѵõ������ݽ��п�������
/// @param[out]	bufLen		����������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperGetData(
	CWALK_HELP_HD helpHD,
	LPCTSTR* buf,
	INT* bufLen
	);

/// ������Ϣ���ɰ�������,�ͷ���Դ
/// @param[in]	helpHD		�������������,��CWALK_NET_InfoHelperCreate()���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD	CWALK_NET_InfoHelperRelease(
	CWALK_HELP_HD helpHD
	);

/// sliceȥͷ ����ʹ��
/// @param[in]	srcData		Դ������
/// @param[in]	srcLen		Դ�����ݳ���
/// @param[out]	decData		ȥͷ��������
/// @param[out]	decLen		ȥͷ��Դ�����ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD	CWALK_NET_RemoveSliceHead(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen);

/// sliceȥͷ,���������� ����ʹ��
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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_RemoveSliceHeadWithParam(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen,
	INT *streamType,
	INT *isIFrame,
	INT64 *pts);


/// ����VOD����ģʽ
/// @param[in] streamHD	¼��طž��,��CWALK_NET_StartPlaybackStream()�õ�
/// @param[in] mode	ģʽ��>0:���򲥷� <0:���򲥷� ==0:ȱʡģʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackMode(
	CWALK_NET_HD streamHD,
	INT32 mode
	);

/// ��ȡ��������ƽ̨����
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
/// @param[out]	platType	�����������ƽ̨����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerPlatType(
	CWALK_NET_HD userHD,
	CWALKNetSvrPlatType *platType);

/// ͳ���������ӿ� ������ʹ��
///	@param[in]	loginHD			��¼���,��CWALK_NET_Login()���
/// @param[in]	camCount		���������
/// @param[in]	onlineCount		�����������
/// @return
///	-	TRUE	�ɹ�
///	-	����	ʧ��,������
CWALK_SDK_API BOOL CWALK_SDK_METHOD CWALK_NET_RefreshAllCamStatusCount(CWALK_NET_HD loginHD, UINT &camCount , UINT &onlineCount);

///	��ȡ�û���¼������Ϣ	by cpw 2016-11-16 14:21
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	userName	��¼�û���
///	@param[out]	times		����ʣ�����
///	@param[out]	locked		����ʣ��ʱ��  ��λ��s
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserErrorInfo(
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	INT& times,
	INT64& locked
	);

///	�����û�
/// @param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	ipOrHost	DCS��������ip��dns
///	@param[in]	port		DCS�������ķ���˿�
///	@param[in]	userName	Ҫ�������û�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_UnlockedUser(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost, 
	INT port,
	const TCHAR* userName
	);


/// �о�¼��ʱ���
/// @param[in] userParam	�û�����
/// @param[in] userHD		��¼���
/// @param[in] avPath		�����ͨ������
/// @param[in] beginTime	ʱ��ο�ʼʱ��,��ʽ��"2012-01-01 13:20:00.000"
/// @param[in] endTime		ʱ��ν���ʱ�䣨������
/// @param[in] storageAddr	�洢��ַ��¼��㲥������ʱ�õ�
/// @return
///	-	TURE		������һ�λص�
///	-	FALSE		�����ص�
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_QueryRecordSAddr)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime, 
	const TCHAR* storageAddr
	);

/// ��ѯ¼�񣬻ص��������洢��ַ
/// ע: �Ƿ�¼��ʱ��λᱻ���˵�,������Ϣ��¼����־��
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[in] avPath		�����ͨ������
/// @param[in] vodType		0-������¼��, ��0�豸¼��
/// @param[in] beginTime	��ʼʱ��, ��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] fnOnQueryRecords	�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordSAddr(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_QueryRecordSAddr fnCB,
	void* userParam /*= NULL*/
	);

/// �㲥¼�񣬲������洢��ַ
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼��طŵľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] storageAddr	�洢��ַ
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartPlaybackStreamSAddr(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	const TCHAR* storageAddr, 
	Callback_OnStreamData fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

/// ����¼�񣬲������洢��ַ
/// @param[in] userHD		��¼���,��CWALK_NET_Login()���
/// @param[out] streamHD	�õ�¼�����صľ��
/// @param[in] avPath		�����ͨ������, dcs�в�����ʽͬCWALK_NET_StartStream
/// @param[in] vodType		0 - ������¼��, ��0 - ¼�����ڵĲ���,���ֵΪ256
/// @param[in] beginTime	��ʼʱ��,��ʽ��"2012-01-01 13:20:00.000" �� "20120101132000000"
/// @param[in] endTime		����ʱ�䣨������
/// @param[in] storageAddr	�洢��ַ
/// @param[in] fnData		�������ص�����
/// @param[in] fnRobbed		��ռ�ص�����
/// @param[in] fnMsg		¼����Ϣ�ص�����
/// @param[in] userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartDownloadStreamSAddr(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	const TCHAR* storageAddr, 
	Callback_OnStreamData fnData/*= NULL*/,
	CallBack_OnStreamRobbed fnRobbed/*= NULL*/,
	CallBack_OnStreamMsg fnMsg/*= NULL*/,
	void* userParam
	);

typedef enum{
	CWALKCameraSortNameDesc=0,
	CWALKCameraSortNameAsc
}CWALKCameraSort;

/// ��ȡ���飬10.2֧��
/// @param[in] userHd		��¼���,��CWALK_NET_Login()���
/// @param[out] data		���ݻ��棬�ɵ����߷����ڴ棬����������������(json����)
/// @param[in/out] bufLen	���ݻ����С���ɵ�����ָ������С�����ݴ�Сʱ�������߽����Ϊ����Ĵ�С��
/// @param[in] bVirtualGroup	 �Ƿ���ҵ�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_ListGroupWithCount(CWALK_NET_HD userHd,TCHAR* const data, INT32* const bufLen,BOOL bVirtualGroup);

/// ��ҳ��ȡ�����µ��������10.2֧��
/// @param[in] userHd		��¼���,��CWALK_NET_Login()���
/// @param[out] data		���ݻ��棬�ɵ����߷����ڴ棬������������������(json���飬�����ʽΪ С�ֽ����Unicode)
/// @param[in/out] bufLen	���ݻ����С���ɵ�����ָ������С�����ݴ�Сʱ�������߽����Ϊ����Ĵ�С��
/// @param[in] bVirtualGroup	 �Ƿ���ҵ�����
/// @param[in] groupId	 	����id
/// @param[in] pageSize	 	ÿҳ��С
/// @param[in] pageIndex	ҳ�룬��0��ʼ
/// @param[in] sort	 		��ҳ����ʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_ListCamerasByPage(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup, const TCHAR * groupId,INT32 pageSize,INT32 pageIndex,CWALKCameraSort sort);


/// ģ�����������������ƥ�����ߵ�ǰ1000����10.2֧��
/// @param[in] userHd		��¼���,��CWALK_NET_Login()���
/// @param[out] data		���ݻ��棬�ɵ����߷����ڴ棬������������������(json����)
/// @param[in/out] bufLen	���ݻ����С���ɵ�����ָ������С�����ݴ�Сʱ�������߽����Ϊ����Ĵ�С��
/// @param[in] bVirtualGroup	 �Ƿ���ҵ�����
/// @param[in] searchText	�����ַ���
/// @param[in] groupId      ����id���������id��Ϊ�գ����ڸ÷��鼰���ӷ���������
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_SearchCamerasLimited(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* searchText,const TCHAR* groupId);

/// ��ȡָ��������ָ�����������ҳ
/// @param[in] userHd		��¼���,��CWALK_NET_Login()���
/// @param[out] data		���ݻ��棬�ɵ����߷����ڴ棬������������������(json����)
/// @param[in/out] bufLen	���ݻ����С���ɵ�����ָ������С�����ݴ�Сʱ�������߽����Ϊ����Ĵ�С��
/// @param[in] bVirtualGroup	 �Ƿ���ҵ�����
/// @param[in] groupId	 	����id
/// @param[in] cameraId	 	�����Id
/// @param[in] pageSize	 	ÿҳ��С
/// @param[out] pageIndex	ҳ�룬��0��ʼ
/// @param[in] sort	 		��ҳ����ʽ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_GetPageOfCamera(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* groupId,const TCHAR* cameraId,INT32 pageSize,INT* const pageIndex,CWALKCameraSort sort);

/// ��ȡָ���������
/// @param[in] userHd		��¼���,��CWALK_NET_Login()���
/// @param[out] data		���ݻ��棬�ɵ����߷����ڴ棬������������������(json����)
/// @param[in/out] bufLen	���ݻ����С���ɵ�����ָ������С�����ݴ�Сʱ�������߽����Ϊ����Ĵ�С��
/// @param[in] bVirtualGroup	 �Ƿ���ҵ�����
/// @param[in] objNamesJsArr	�����objName��ɵ�json����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_GetCamerasByObjName(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* objNamesJsArr);


/// ͼƬ���ݻص�����,��CWALK_NET_StartRealtimeImage()����
/// @param[in]	userParam	�û�����
///	@param[in]	imageHD		ͼƬʵʱԤ�����
///	@param[in]  avPath		AV������
/// @param[in]	data		�ص���json��ʽ����
/// @param[in]	dataLen		�ص����ݳ���
typedef void (CWALK_SDK_CALLBACK *Callback_OnRealtimeImageData)(
	void* userParam,
	CWALK_NET_HD imageHD,
	const TCHAR* avPath,
	const void* data,
	INT dataLen
	);

/// ʵʱͼƬ������Ϣ�ص�֪ͨ����
/// @param[in]	userParam		�û�����
/// @param[in]	imageHD			ͼƬʵʱԤ�����,��CWALK_NET_StartRealtimeImage()���
/// @param[in]  code			��Ϣ��
///								2  - �򿪳ɹ�
///								1  - ���ӳɹ�
///								-1 - ����ʧ��
///								-2 - ��ʧ�ܣ�avpath��Ч
///								-3 - ������˹ر�
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStartRealImageMsg)(
	void* userParam,
	CWALK_NET_HD imageHD,
	const int code
	);

/// ����ʵʱͼƬԤ��
/// @param[in]  userHd		��¼���,��CWALK_NET_Login()���
///	@param[out] imageHd		ͼƬԤ�����
///	@param[in]  avPath		AV������
///	@param[in]  fnData		ͼƬ���ݻص�����
///	@param[in]  fnMsg		Ԥ��״̬�ص�����
///	@param[in]  userParam	�û�����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRealtimeImage(
	CWALK_NET_HD userHD, 
	CWALK_NET_HD* imageHD, 
	const TCHAR* avPath,
	Callback_OnRealtimeImageData fnData,
	CallBack_OnStartRealImageMsg fnMsg,
	void* userParam
	);

/// �ر�ʵʱͼƬԤ��
///	@param[in] imageHd		ͼƬԤ���������CWALK_NET_StartRealtimeImage()����
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopRealtimeImage(
	CWALK_NET_HD imageHD
	);

/// ����뱸�÷�����������״̬(ָ�¼���վ)
///	@param[in]	userHD		��¼���,��CWALK_NET_Login()���
///	@param[in]	Ip			�����IP
///	@param[in]	port		����Ķ˿�
/// @param[out]	connect		����״̬��TRUE-����״̬��FALSE-����״̬
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_IsConnectedBackup(
	CWALK_NET_HD userHD, 
	const TCHAR* Ip,
	const INT	 port,
	BOOL* connect
	);

/// �õ����÷����IP��Port
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[out] Ip			���÷�������IP���ڴ���ʹ���߷���
/// @param[in]  len			infoBuf�Ĵ�С
/// @param[out] realLen		����ʵ����Ϣ�ĳ���
/// @param[out] port		���÷���Ķ˿�
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetBackupInfo(
	CWALK_NET_HD userHD,
	void* ip,
	INT len,
	INT* realLen,
	INT* port
	);

/// ����ǽ���ƽӿ�
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	cmd			����ǽ���������� ref CWALKNetTVWallCommand
/// @param[in]	param		������������ṹ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_TVWallControl(
	CWALK_NET_HD userHD, 
	const CWALKNetTVWallCommand cmd,
	CWALKNetTVWallParam* param
	);


/// ƴ��(��·������)�豸���ƽӿ�
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	decPath 	ƴ���豸���
/// @param[in]	param		������������ṹ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_MatrixDevControl(
	CWALK_NET_HD userHD,
	const TCHAR* decPath,
	CWALKNetMatrixCtrlParam* param
);

/// �򵥵����ݼ��ܷ���
/// @param[in]	secretKey	������Կ
/// @param[in]	srcData		Դ����
/// @param[out] result		���ܺ�����
/// @param[out] resultLen	���ܺ����ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SimpleEncyptedData(
	const TCHAR* secretKey, 
	const TCHAR* srcData, 
	TCHAR* result, 
	INT* resultLen
	);

/// �򵥵����ݽ��ܷ���
/// @param[in]	secretKey	������Կ
/// @param[in]	srcData		����
/// @param[out] result		���ܺ�����
/// @param[out] resultLen	���ܺ����ݳ���
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SimpleDecodeData(
	const TCHAR* secretKey, 
	const TCHAR* srcData, 
	TCHAR* result, 
	INT* resultLen
	);

/// �����������γ������
/// @param[in]	userHD 		��¼���,��CWALK_NET_Login()���
/// @param[in]	strGroupId 	������֯�������
/// @param[in]	avPath 		������
/// @param[in]	longitude 	����ֵ
/// @param[in]	latitude 	γ��ֵ
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ��,������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCamerasCoordinate(
	CWALK_NET_HD userHD, 
	const TCHAR* strGroupId, 
	const TCHAR* avPath, 
	const TCHAR* longitude, 
	const TCHAR* latitude
	);

#endif	/// _cwalk_netsdk_h_
