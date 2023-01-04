/// ==========================================================================
///
///			Copyright(C) �ƴӿƼ����޹�˾
///			All rights reserved
///
///
///			filename: cwalk_nethelper.h
///         description:  DCS����SDK��չ�ӿ�
///
///
///			create by ziqiu at 2020-05
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================
#ifndef _cwalk_nethelper_h_
#define _cwalk_nethelper_h_

#include "cwalk_netsdk.h"


/// �����ն�IP
struct CMSCameraViewsNode
{
	TCHAR cameraViews[16];		///< �����ն�IP
	CMSCameraViewsNode* next; 
};

/// �����ն�IP
struct CMSDigOutViewNode
{
	TCHAR diaOutView[16];		///< �����ն�IP
	CMSDigOutViewNode* next;	
};

/// �����ն���Ϣ
struct CMSTargetsNode
{
	TCHAR iscmName[32];						///< Ŀ���ַ���磺��210808832��
	CMSCameraViewsNode* cameraViewsNode;	///< �����ն�IP��������ʽ��ʾ
	CMSDigOutViewNode* diaOutViewNode;		///< �����ն�IP��������ʽ��ʾ
	CMSTargetsNode* next;
};

/// ʵʱ������״̬
struct CMSTaskNode
{
	TCHAR forwarder[16];			///< ת����������IP��ַ
	TCHAR source[64];				///< Դ��ַ
	CMSTargetsNode* targetsNode;	///< Ŀ���ַ��������ʽ��ʾ
	CMSTaskNode* next;
};

/// ¼��㲥״̬
struct CMSVodNode
{
	TCHAR channel[64];	///< ͨ����
	TCHAR peerIP[16];	///< �����ն�IP
	INT type;			///< ¼�����ͣ�0 - ������¼�񣿣�1 - �豸¼�񣿣����� - δ���壿
	TCHAR user[32];		///< �㲥¼���û����磺��admin��
	INT userLevel;		///< �㲥¼���û����𣬷�Χ��[0-100]��
	CMSVodNode* next;
};

/// ���ط���״̬
typedef struct CMSStatusInfoNode
{
	CMSTaskNode* taskNode;	///< ʵʱ������״̬��������ʽ��ʾ
	CMSVodNode* vodNode;	///< ¼��㲥״̬��������ʽ��ʾ
} CMSStatusInfo;


/// �����ն�IP
struct FSPeersNode
{
	TCHAR peers[16];		///< �����ն�IP
	FSPeersNode* next;
};

/// ת��������״̬
struct FSTransferStatusNode
{
	FSPeersNode* peersNode;		///< �����ն�IP��������ʽ��ʾ
	TCHAR source[64];			///< ����ͨ����
	TCHAR startTime[20];		///< ʵʱ����ʼʱ�䣬��ʽ��"20130823160819193"
	TCHAR target[32];			///< Ŀ���ַ
	FSTransferStatusNode* next;
};

/// ת������״̬
typedef struct StreamingServiceStatusInfoNode
{
	TCHAR transferIP[16];						///< ת��������IP
	TCHAR master[16];							///< ���ط�����IP��һ��ת��������ֻ������һ�����ط�����
	FSTransferStatusNode* transferStatusNode;	///< ת��������״̬��������ʽ��ʾ
	StreamingServiceStatusInfoNode* next;
} *LPStreamingServiceStatusInfo;


/// �洢������״̬
struct SSStorageIPNode
{
	TCHAR beginTime[20];		///< �㲥¼�����ʼʱ�䣬��ʽ��"20130823160110455"
	TCHAR endTime[20];			///< �㲥¼��Ľ���ʱ�䣬��ʽ��"20130823161516000"
	TCHAR obj[64];				///< �㲥¼��ͨ����
	TCHAR peerIP[16];			///< �����ն�IP
	INT sessionID;				///< �㲥�ỰID������Ψһ��ʶһ��¼��㲥
	SSStorageIPNode* next;
};

//�洢����״̬
typedef struct StorageServiceStatusInfoNode
{
	TCHAR storageIP[16];			///< ������IP
	SSStorageIPNode* storageIPNode;	///< �洢������״̬��������ʽ��ʾ
	StorageServiceStatusInfoNode* next;
} *LPStorageServiceStatusInfo;

/// ��������������������ڽ���CMService���ط���״̬��Ϣ��������������������
/// @param[in]	data		Ҫ���������ط���״̬��Ϣ����CWALK_NET_GetServiceStatus()���
/// @param[out]	listInfo	��������ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCMSStatusParse(
	const TCHAR* data,
	CMSStatusInfo* listInfo
	);

/// ����������������������ͷ�CMSStatusInfo����
///	@param[in]	listInfo	����ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCMSStatusFree(
	CMSStatusInfo* listInfo
	);

/// ��������������������ڽ���FSת������״̬��Ϣ���õ�FS״̬��Ϣ������
/// @param[in]	data		Ҫ������ת������״̬��Ϣ����CWALK_NET_GetServiceStatus()���
/// @param[out]	listInfo	��������ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperFSStatusParse(
	const TCHAR* data,
	LPStreamingServiceStatusInfo* listInfo
	);

///	����������������������ͷ�LPStreamingServiceStatusInfo����
///	@param[in]	listInfo	����ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperFSStatusFree(
	LPStreamingServiceStatusInfo listInfo
	);

/// ��������������������ڽ���SS�洢����㲥״̬��Ϣ���õ�SS�㲥״̬��Ϣ������
/// @param[in]	data		Ҫ�����Ĵ洢����㲥״̬��Ϣ����CWALK_NET_GetServiceStatus()���
/// @param[out]	listInfo	��������ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperSSStatusParse(
	const TCHAR* data,
	LPStorageServiceStatusInfo* listInfo
	);

///	����������������������ͷ�LPStorageServiceStatusInfo����
///	@param[in]	listInfo	����ͷָ��
/// @return
///	-	CWALKSDK_OK	�ɹ�
///	-	����		ʧ�ܣ�������
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperSSStatusFree(
	LPStorageServiceStatusInfo listInfo
	);

#endif	/// _cwalk_nethelper_h_