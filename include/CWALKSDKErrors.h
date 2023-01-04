/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
///			All rights reserved
///
///
///			filename: CWALKSDKErrors.h
///         description:  DCS SDK������
///
///
///			create by ziqiu at 2020-05
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================

#ifndef _CWALKSDKError_h_
#define _CWALKSDKError_h_

///< ���ش����룬-20000�����ΪDCSSdk�����룬-20000���ڵ�Ϊ�ں˴�����

#define CWALKSDK_OK							0		///< �����ɹ����
#define CWALKSDK_ERROR							-1		///< δ�������
#define CWALKSDK_ERR_NOT_SUPPORT				-20001	///< �˹��ܲ�֧��
#define CWALKSDK_ERR_NOT_IMPL					-20002	///< ������δʵ��
#define CWALKSDK_ERR_NOT_INIT					-20003	///< δ��ʼ��
#define CWALKSDK_ERR_NOT_ENOUGH_MEM			-20005	///< �ڴ����ʧ��
#define CWALKSDK_ERR_NOT_ENOUGH_ID				-20004	///< ��̫������ϵͳ��Դ����
#define CWALKSDK_ERR_INVALID_ID				-20006	///< ��Ч����������Ѿ��ر�
#define CWALKSDK_ERR_INVALID_NAME				-20007	///< ��Ч��������û���������
#define CWALKSDK_ERR_INVALID_PARARM			-20008	///< ��Ч����
#define CWALKSDK_FILE_NOFIND					-20009	///< δ���ļ������ļ���ʧ��
#define CWALKSDK_ISFINDING						-20010	///< ���ڲ����ļ�
#define CWALKSDK_NOMOREFILE					-20011	///< �����ļ�ʱû�и�����ļ�
#define CWALKSDK_FILE_EXCEPTION				-20012	///< �����ļ�ʱ�쳣
#define CWALKSDK_ERR_URLPATH					-20013	///< �ļ�Urlȫ·������
#define CWALKSDK_ERR_EXISTKEY					-20014	///< Ԫ���Ѵ���ESIST
#define CWALKSDK_ERR_NO_OBJECT					-20015	///< ���Ҷ��󲻴���
#define CWALKSDK_ERR_OSD_SETTEXT				-20016	///< OSD�����ı�����
#define CWALKSDK_ERR_OSD_TYPE					-20017	///< OSD���ʹ���
#define CWALKSDK_ERR_OSD_SHOW					-20018	///< OSD��ʾ����
#define CWALKSDK_ERR_DEFAULTPORT				-20019	///< ��ȡĬ�϶˿ڴ���
#define CWALKSDK_ERROR_LOGIN					-20020	///< ��½ʧ��
#define CWALKSDK_NOMOREDATA					-20021	///< û�и����Ѷ����
#define CWALKSDK_ERR_SET_PASSWORD				-20022	///< �����������
#define CWALKSDK_ERR_NO_KEY					-20023	///< ���ü�ֵ������
#define CWALKSDK_ERR_NO_VALUE					-20024	///< ��Ӧ�ļ�û��ֵ
#define CWALKSDK_ERR_FUNCTION_NOT_IMPLEMENTED	-20025  ///< ����δʵ��
#define CWALKSDK_ERR_CREATE_HANDLE				-20026  ///< ��þ��Ϊ��
#define CWALKSDK_ERR_EVENT_RESUBSCRIBE			-20027  ///< �¼��ظ�����
#define CWALKSDK_ERR_END_OF_FILE				-20028  ///< ��ȡ�ļ����
#define CWALKSDK_ERR_NO_HANDLE					-20029  ///< ���������
#define CWALKSDK_ERR_NULL_OBJECT				-20030  ///< ����ָ��Ϊ��
#define CWALKSDK_ERR_FIRST_NOT_IFRAME			-20031  ///< ���յ��ĵ�һ֡���ǹؼ���
#define CWALKSDK_ERR_UNSUPPORTED_PLATFORM		-20032  ///< ��֧�ֵ�ǰƽ̨
#define CWALKSDK_ERR_BUFFER_TOO_SMALL			-20033	///< ������̫С
#define CWALKSDK_ERR_UNKNOWN_SERVICE			-20034  ///< ��֧�ֵķ���������
#define CWALKSDK_ERR_NO_PRIVILEGE			    -20035  ///< û��Ȩ��
#define CWALKSDK_ERR_VIEW_NUM		            -20036  ///< �������֧�ֻ�����
#define CWALKSDK_ERR_DISK_FULL					-20037  ///< ���̿ռ䲻��
#define CWALKSDK_ERR_INVALID_MEM				-20038  ///< ת��ʱ�ڴ����ת��ⷵ�أ�
#define CWALKSDK_ERR_ENCODER_OPEN				-20039  ///< �򿪱���������ת��ⷵ�أ�
#define CWALKSDK_ERR_SP_QUERY_SEGMENT			-20040	///< δ��ѯ���÷ֶ�¼��
#define CWALKSDK_ERR_NO_PVM_ADD			    -20041	///< δ��ȡ��PVM��ַ
#define CWALKSDK_ERR_ES_UNAVAILABLE 			-20042	///< ��־���񲻿���
#define CWALKSDK_ERR_AVCF_ERROR 			    -20043	///< AVCF����
#define CWALKSDK_FILE_ISOPEN					-20044  ///< �ļ��Ѿ���
#define CWALKSDK_FILE_ISTRANSMIT				-20045  ///< �ļ����ڴ���
#define CWALKSDK_ERR_ISHTTPS					-20046  ///< ��֧��ʹ��httpsЭ��ͨ��


#define CWALKSDK_ERR_PLAY_HD					-21001 ///< ��ȡ��������ʧ��
#define CWALKSDK_ERR_PLAY_NEED_SLICES			-21002 ///< ���Ż�������Ҫ����
#define CWALKSDK_ERR_PLAY_FULL_SILCES			-21003 ///< ���ջ���������
#define CWALKSDK_ERR_PLAY_INPUT_SLICES_CB		-21004 ///< ������slice��ʽ�»ص�����û������
#define CWALKSDK_ERR_PLAY_INVALID_CMD			-21005 ///< ��Ч�Ĳ�������
#define CWALKSDK_ERR_PLAY_INVALID_CMD_MATCH	-21007 ///< ʵʱ����ʱֻ֧����ͣ�ͼ�����������
#define CWALKSDK_ERR_PLAY_INVALID_SPEED		-21006 ///< ����Ĳ����ٶ�
#define CWALKSDK_ERR_PLAY_INVALID_CB_MODE		-21007 ///< ʵʱ����ʱ���ܲ��ûص���ʽ����Slice����
#define CWALKSDK_ERR_PLAY_IS_RELEASED			-21008 ///< ��Դ�Ѿ��ͷ�
#define CWALKSDK_ERR_PLAY_THREAD_STOP			-21009 ///< �����߳��Ѿ�ֹͣ
#define CWALKSDK_ERR_PLAY_REOPEN				-21010 ///< ��Ƶ��Դ�ظ���
#define CWALKSDK_ERR_PLAY_OPEN_AUDIO			-21011 ///< ����Ƶ�豸ʧ��
#define CWALKSDK_ERR_PLAY_START_AUDIO			-21012 ///< ��ʼ�ɼ���Ƶʧ��
#define CWALKSDK_ERR_PLAY_STOP_AUDIO			-21013 ///< ֹͣ�ɼ���Ƶʧ��
#define CWALKSDK_ERR_PLAY_VIDEO_INFO			-21014 ///< ��Ƶ��Ϣ��ȡʧ��
#define CWALKSDK_WARNING_PLAY_MAX_LOCALCACH	-21015 ///< �������õı��ػ������󾯸�ֵ
#define CWALKSDK_WARNING_PLAY_MIN_LOCALCACH	-21016 ///< С�����õı��ػ������С����ֵ
#define CWALKSDK_ERR_PLAY_PAUSE_CANNOT_SPEED	-21017 ///< ��ͣʱ�������ò����ٶ�

///22000����Ϊ��־�������������
#define CWALKSDK_ERR_LOG_UNKNOWTYPE			-22001 ///<	δ����Ĵ�������
#define CWALKSDK_ERR_LOG_DATA					-22002 ///<	���ݲ�ѯ�������ȷ

///23000����ΪSDK�����������
#define CWALKSDK_ERR_CODEC_NOTKEY			-23001	///< ���ǹؼ�֡I֡
#define CWALKSDK_ERR_CODEC_OPEN_DEC_FAIL	-23002	///< �򿪽�����ʧ��
#define CWALKSDK_ERR_CODEC_DEC_INPUT_FAIL	-23003	///< �������������ʧ��
#define CWALKSDK_ERR_CODEC_SNAPSHOT_KEYFRAME_FAIL	-23004	///< ���벢����I֡ʧ��

///100000����ΪCMService�������
#define DCS_ERR_SS_NOT_AVAILABLE        	-101001 ///<	δ����StroageProxyService  
#define DCS_ERR_FS_NOT_AVAILABLE			-101002 ///<	δ����StreamingService  
#define DCS_ERR_PAU_NOT_AVAILABLE 		-101003 ///<	ACService������   
#define DCS_ERR_DEVICE_NOT_ATTACHE_PAU	-101004 ///<	ACService������(ACService������)   
#define DCS_ERR_USER_STREAM_OVERRAGE		-101005 ///<    �����û���������
#define DCS_ERR_PLAT_STREAM_OVERRAGE		-101006 ///<    ����ƽ̨��������
#define DCS_ERR_INVALID_JOSN				-101007 ///<    �Ƿ���JSON�ַ���
#define DCS_ERR_PAU_SEND_FAILED			-101008 ///<	��ACService֮��ͨ��ʧ��
#define DCS_ERR_MONITOR_LOCKED			-101030 ///<	�������Ѿ�������
#define DCS_ERR_MONITOR_CANNOT_CONTROL	-101031 ///<	���������ܱ�����
#define DCS_ERR_SESSION_NOT_FOUND 		-102001 ///<	�Ự��Ч�������ڣ�  
#define DCS_ERR_FS_STREAM_BROKEN			-102002 ///<	StreamingService������
#define DCS_ERR_NOT_LOCAL_MONITOR			-102003 ///<	�ǽڵ��ڲ�������
#define DCS_INF_MONITOR_LOCKED  			-102004 ///<	������������
#define DCS_ERR_CHANNLE_DISABLED			-103001 ///<	ͨ��������
#define DCS_ERR_PAU_DISABLED				-103002 ///<	ACService������
#define DCS_ERR_LOG_NOT_AVAILABLE			-103003 ///<	δ������־����
#define DCS_ERR_PAU_NOT_OPEN				-103004 ///<	��ACService����OPENʧ��
#define DCS_ERR_DCS_NOT_OPEN				-103005 ///<	��DCS����OPENʧ��
#define DCS_ERR_LOCALDB_UNINIT			-103006 ///<	�������ݿ�δ��ʼ��
#define DCS_ERR_LOCALDB_EXCEPTION			-103007 ///<	�������ݿ��쳣
#define DCS_ERR_CHANNEL_RECORD_EXITS		-103008 ///<	ͨ������¼��
#define DCS_ERR_DCS_NOT_AVAILABLE			-103009 ///<	δ����DCS
#define DCS_ERR_AUDIOTALK_IN_USE			-103010 ///<	����ͨ����ռ��
#define DCS_ERR_DEVICE_NOT_EXIST			-103011 ///<	�豸������
#define DCS_ERR_REQUEST_PATH_EXISTED		-103012 ///<	�����·���Ѿ�����
#define DCS_ERR_ROFS3S_NOT_AVAILABLE		-103013 ///<	�޿��õ�rofs3s
#define DCS_ERR_PAU_DISCONNECT			-103014 ///<	ACService�����޷�����
#define DCS_ERR_RESOURCESHIELD			-103015 ///<	����ԴȨ��(��Դ����)
#define DCS_ERR_SCAN_EXIST				-103016 ///<	����Ѳ���Ѵ���
#define DCS_ERR_MACRO_EXIST				-103017 ///<	���̺��Ѵ���
#define DCS_ERR_ORDER_CALL				-103018 ///<	���ô������
#define DCS_ERR_USER_DISABLED				-103019 ///<	�û�������
#define DCS_ERR_RECORD_REUSE				-103020 ///<	ͨ��¼�񱻸���



#endif
