/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: cwalk_nethelper.h
///         description:  DCS网络SDK扩展接口
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


/// 流接收端IP
struct CMSCameraViewsNode
{
	TCHAR cameraViews[16];		///< 流接收端IP
	CMSCameraViewsNode* next; 
};

/// 流接收端IP
struct CMSDigOutViewNode
{
	TCHAR diaOutView[16];		///< 流接收端IP
	CMSDigOutViewNode* next;	
};

/// 流接收端信息
struct CMSTargetsNode
{
	TCHAR iscmName[32];						///< 目标地址，如：“210808832”
	CMSCameraViewsNode* cameraViewsNode;	///< 流接收端IP，链表形式表示
	CMSDigOutViewNode* diaOutViewNode;		///< 流接收端IP，链表形式表示
	CMSTargetsNode* next;
};

/// 实时流传输状态
struct CMSTaskNode
{
	TCHAR forwarder[16];			///< 转发服务器的IP地址
	TCHAR source[64];				///< 源地址
	CMSTargetsNode* targetsNode;	///< 目标地址，链表形式表示
	CMSTaskNode* next;
};

/// 录像点播状态
struct CMSVodNode
{
	TCHAR channel[64];	///< 通道名
	TCHAR peerIP[16];	///< 流接收端IP
	INT type;			///< 录像类型，0 - 服务器录像？；1 - 设备录像？；其他 - 未定义？
	TCHAR user[32];		///< 点播录像用户，如：“admin”
	INT userLevel;		///< 点播录像用户级别，范围：[0-100]？
	CMSVodNode* next;
};

/// 主控服务状态
typedef struct CMSStatusInfoNode
{
	CMSTaskNode* taskNode;	///< 实时流传输状态，链表形式表示
	CMSVodNode* vodNode;	///< 录像点播状态，链表形式表示
} CMSStatusInfo;


/// 流接收端IP
struct FSPeersNode
{
	TCHAR peers[16];		///< 流接收端IP
	FSPeersNode* next;
};

/// 转发服务传输状态
struct FSTransferStatusNode
{
	FSPeersNode* peersNode;		///< 流接收端IP，链表形式表示
	TCHAR source[64];			///< 传输通道名
	TCHAR startTime[20];		///< 实时流开始时间，格式："20130823160819193"
	TCHAR target[32];			///< 目标地址
	FSTransferStatusNode* next;
};

/// 转发服务状态
typedef struct StreamingServiceStatusInfoNode
{
	TCHAR transferIP[16];						///< 转发服务器IP
	TCHAR master[16];							///< 主控服务器IP，一个转发服务器只能配置一个主控服务器
	FSTransferStatusNode* transferStatusNode;	///< 转发服务传输状态，链表形式表示
	StreamingServiceStatusInfoNode* next;
} *LPStreamingServiceStatusInfo;


/// 存储服务传输状态
struct SSStorageIPNode
{
	TCHAR beginTime[20];		///< 点播录像的起始时间，格式："20130823160110455"
	TCHAR endTime[20];			///< 点播录像的结束时间，格式："20130823161516000"
	TCHAR obj[64];				///< 点播录像通道名
	TCHAR peerIP[16];			///< 流接收端IP
	INT sessionID;				///< 点播会话ID，用来唯一标识一次录像点播
	SSStorageIPNode* next;
};

//存储服务状态
typedef struct StorageServiceStatusInfoNode
{
	TCHAR storageIP[16];			///< 服务器IP
	SSStorageIPNode* storageIPNode;	///< 存储服务传输状态，链表形式表示
	StorageServiceStatusInfoNode* next;
} *LPStorageServiceStatusInfo;

/// 对象解析帮助函数，用于解析CMService主控服务状态信息，解析结果存放在链表中
/// @param[in]	data		要解析的主控服务状态信息，由CWALK_NET_GetServiceStatus()获得
/// @param[out]	listInfo	返回链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCMSStatusParse(
	const TCHAR* data,
	CMSStatusInfo* listInfo
	);

/// 对象解析帮助函数，用于释放CMSStatusInfo链表
///	@param[in]	listInfo	链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCMSStatusFree(
	CMSStatusInfo* listInfo
	);

/// 对象解析帮助函数，用于解析FS转发服务状态信息，得到FS状态信息的链表
/// @param[in]	data		要解析的转发服务状态信息，由CWALK_NET_GetServiceStatus()获得
/// @param[out]	listInfo	返回链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperFSStatusParse(
	const TCHAR* data,
	LPStreamingServiceStatusInfo* listInfo
	);

///	对象解析帮助函数，用于释放LPStreamingServiceStatusInfo链表
///	@param[in]	listInfo	链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperFSStatusFree(
	LPStreamingServiceStatusInfo listInfo
	);

/// 对象解析帮助函数，用于解析SS存储服务点播状态信息，得到SS点播状态信息的链表
/// @param[in]	data		要解析的存储服务点播状态信息，由CWALK_NET_GetServiceStatus()获得
/// @param[out]	listInfo	返回链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperSSStatusParse(
	const TCHAR* data,
	LPStorageServiceStatusInfo* listInfo
	);

///	对象解析帮助函数，用于释放LPStorageServiceStatusInfo链表
///	@param[in]	listInfo	链表头指针
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败，错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperSSStatusFree(
	LPStorageServiceStatusInfo listInfo
	);

#endif	/// _cwalk_nethelper_h_