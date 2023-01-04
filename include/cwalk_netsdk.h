/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: cwalk_netsdk.h
///         description:  DCS 网络SDK
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

/// DCS服务平台类型
typedef enum
{
	CWALKNET_SVRPLATTYPE_UNKNOWN	= 0,
	CWALKNET_SVRPLATTYPE_DCS671		= 1,	///< DCS_old
	CWALKNET_SVRPLATTYPE_DCSPLUS	= 2,	///< DCS
} CWALKNetSvrPlatType;

/// 对象类型
typedef enum
{
	CWALKNET_TYPE_UNKNOWN		= 0,		///< 传入SDK时表示列举全部
	CWALKNET_TYPE_SERVER		= 0x0001,	///< 关联服务器
	CWALKNET_TYPE_GATEWAY		= 0x0002,	///< 网关服务器, dcs不支持
	CWALKNET_TYPE_DEVICE		= 0x0004,	///< 接入设备
	CWALKNET_TYPE_MOUNT			= 0x0008,	///< 挂载设备
	CWALKNET_TYPE_CAMERA		= 0x0010,	///< 摄像头
	CWALKNET_TYPE_MONITOR		= 0x0020,	///< 监视器
	CWALKNET_TYPE_AUDIO			= 0x0040,	///< 对讲通道
	CWALKNET_TYPE_TRUNKIN		= 0x0100,	///< 输入干线, dcs不支持
	CWALKNET_TYPE_TRUNKOUT 		= 0x0200,	///< 输出干线, dcs不支持
	CWALKNET_TYPE_ALARMIN		= 0x1000,	///< 报警输入
	CWALKNET_TYPE_ALARMOUT		= 0x2000,   ///< 报警输出
	CWALKNET_TYPE_GIS			= 0x4000
} CWALKNetObjectType;

typedef enum
{
	CWALKNET_GROUPTYPE_UNKNOW	=0,
	CWALKNET_GROUPTYPE_GROUP	=1,			///< 行政区划分组
	CWALKNET_GROUPTYPE_VIRTUALGROUP = 2	///< 业务分组/虚拟组织
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

/// 云台最大速度
#define CWALKNET_PTZ_MAX_SPEED	15
//  最大
#define MAX_BUFFER_SIZE 1024*1024*40
typedef enum
{
	CWALKNET_PTZ_PANRIGHT	= 0,	///< 云台右转
	CWALKNET_PTZ_RIGHTUP	= 1,	///< 云台上仰和右转
	CWALKNET_PTZ_TILTUP		= 2,	///< 云台上仰
	CWALKNET_PTZ_LEFTUP		= 3,	///< 云台上仰和左转
	CWALKNET_PTZ_PANLEFT	= 4,	///< 云台左转
	CWALKNET_PTZ_LEFTDOWN	= 5,	///< 云台下俯和左转
	CWALKNET_PTZ_TILTDOWN	= 6,	///< 云台下俯
	CWALKNET_PTZ_RIGHTDOWN	= 7,	///< 云台下俯和右转
	CWALKNET_PTZ_SCAN		= 8,	///< 云台左右自动扫描
	CWALKNET_PTZ_HALT		= 9,	///< 云台停止
	CWALKNET_PTZ_IRIS		= 10,	///< 光圈变化(param>0扩大、param<0缩小、param=0表示停止)
	CWALKNET_PTZ_ZOOM_IN	= 11,	///< 焦距变大(param>0倍率变大、param<0倍率变小、param=0表示停止)
	CWALKNET_PTZ_FOCUS		= 12,	///< 聚焦调整(param>0前调、param<0后调、param=0表示停止)
	CWALKNET_PTZ_VIEW		= 13,	///< 转到指定预置位
	CWALKNET_PTZ_SETVIEW	= 14,	///< 设置当前位置为一个预置位
	CWALKNET_PTZ_AUX		= 15,	///< 接通辅助设备开关(param=1 表示开,param=0 表示关,其它值无效)
	CWALKNET_PTZ_WASH		= 16,	///< 清洗
	CWALKNET_PTZ_WIPE		= 17,	///< 接通雨刷开关
	CWALKNET_PTZ_LIGHT		= 18,	///< 接通灯光电源
	CWALKNET_PTZ_POWER		= 19,	///< 电源
	CWALKNET_PTZ_WARD		= 31,
	CWALKNET_PTZ_DELVIEW	= 35,	///< 删除预置位
	CWALKNET_PTZ_SETPOS		= 40,	///< 云台转动到指定PTZ坐标	(EX：param="pan=36.0;tilt=56.0;zoom=2.0")
} CWALKNetPTZCommand;

/// 事件类型,类型值小于50事件的有报警态和正常态两种状态,大于50的事件只有报警态
typedef enum
{
	CWALKNET_EVENT_UNKNOWN			= -1,	///< 未知事件

	CWALKNET_EVENT_VIDEO_LOST		= 0,	///< 视频丢失发生/恢复
	CWALKNET_EVENT_MOTION			= 1,	///< 运动感知发生/恢复
	CWALKNET_EVENT_VIDEO_HIDE		= 2,	///< 视频遮挡发生/恢复
	CWALKNET_EVENT_VIDEO_BROKEN		= 3,	///< 视频断线发生/恢复

	CWALKNET_EVENT_ALARM_IN			= 10,	///< 报警输入报警/恢复
	CWALKNET_EVENT_CAMERA_LOCK		= 12,	///< 摄像机锁定/恢复
	CWALKNET_EVENT_MONITOR_LOCK		= 13,	///< 监视器锁定/恢复
	CWALKNET_EVENT_DIGITAL_STREAM	= 14,	///< 数字码流传输发起/停止
	CWALKNET_EVENT_MANUAL_RECORD	= 15,	///< 手动录像发起/停止
	CWALKNET_EVENT_DEVICE_BROKEN	= 16,	///< 设备发生断线/恢复
	CWALKNET_EVENT_ROFS_ERROR		= 17,	///< ROFS报告的错误发生/恢复

	CWALKNET_EVENT_SYSTEM_INIT		= 50,	///< 系统初始化
	CWALKNET_EVENT_USER_LOGIN		= 51,	///< 用户登入
	CWALKNET_EVENT_USER_LOGOUT		= 52,	///< 用户注销
	CWALKNET_EVENT_MONITOR_SWITCH	= 53,	///< 监视器切换
	CWALKNET_EVENT_PTZ				= 54,	///< 云台控制
	CWALKNET_EVENT_OPEN_VIDEO_FILE	= 55,	///< 打开视频文件
	CWALKNET_EVENT_CLOSE_VIDEO_FILE	= 56,	///< 关闭视频文件
	CWALKNET_EVENT_ALARM_INFO		= 57,	///< 报警设备报告信息
	CWALKNET_EVENT_VA_ALARM			= 58,	///< 智能报警事件
	CWALKNET_EVENT_OSD_CHANGE		= 59,	///< OSD信息改变
	CWALKNET_EVENT_INTRUSION		= 61,  ///< 区域入侵
	CWALKNET_EVENT_TRAVERSE_PLANE	= 62,  ///< 越界检测
	CWALKNET_EVENT_HIGH_DENSITY		= 6,   ///< 人员聚集

	/// 设备报警事件
	CWALKNET_EVENT_CPU_TOO_BUSY	= 100,	///< CPU使用率过高报警
	CWALKNET_EVENT_MEMORY_TOO_HIGH	= 101,	///< 内存使用率过高报警
	CWALKNET_EVENT_DISK_ARRAY_WRITE_FAILED = 102,	///< 磁盘阵列不能写
	CWALKNET_EVENT_DISK_ARRAY_ERROR= 103,	///< 磁盘阵列错误
	CWALKNET_EVENT_LOST_COMMODITY = 120,	///< 物品遗失
	

	//特殊事件，用户禁用
	CWALKNET_EVENT_CMS_USER_PERMISSION = 1000 //此用户禁用
} CWALKNetEventType;

/// CWALKDB类型
typedef enum
{
	CWALKNET_LOGTYPE_EVENT,	///< 事件日志
	CWALKNET_LOGTYPE_OPERAT,	///< 操作日志
} CWALKNetLogType;

/// 日志服务器客户端类型定义中，DCS类型
#define  CWALKNET_LCTD_DCS_CMS	1

/// DCS操作日志类型
typedef enum
{
	/// 系统相关
	CWALKNET_OLT_REBOOT							= 1001,	///< 
	CWALKNET_OLT_SHUTDOWN						= 1002,	///< 
	CWALKNET_OLT_SET_TIME						= 1003,	///< 
	CWALKNET_OLT_SET_IP							= 1004,	///< 

	/// 用户相关
	CWALKNET_OLT_USER_LOGIN						= 101,	///< 用户登录
	CWALKNET_OLT_USER_LOGOUT					= 102,	///< 用户登出

	/// 实时流操作
	CWALKNET_OLT_REAL_STREAM_OPEN				= 201,	///< 实时流打开
	CWALKNET_OLT_REAL_STREAM_CLOSE				= 202,	///< 实时流关闭
	CWALKNET_OLT_TALK							= 211,	///< 喊话
	CWALKNET_OLT_LISTEN							= 212,	///< 监听
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

	/// 录像操作
	CWALKNET_OLT_RECORD_REMOTE_OPEN				= 301,	///< 远程录像打开
	CWALKNET_OLT_RECORD_REMOTE_CLOSE			= 302,	///< 远程录像关闭
	CWALKNET_OLT_RECORD_SERVER_QUERY			= 303,	///< 服务器录像查询
	CWALKNET_OLT_RECORD_DEVICE_QUERY			= 304,	///< 设备录像查询
	CWALKNET_OLT_RECORD_MANUAL_START			= 305,	///< 手动录像开始
	CWALKNET_OLT_RECORD_MANUAL_STOP				= 306,	///< 手动录像结束
	CWALKNET_OLT_RECORD_QUERY_SEGMENT			= 307,	///< 查询录像时间段
	CWALKNET_OLT_RECORD_QUERY_PROTECT_SEGMENT	= 308,	///< 查询录像保护时间段
	CWALKNET_OLT_RECORD_SET_PROTECT_SEGMENT		= 309,	///< 设定录像保护时间段
	CWALKNET_OLT_RECORD_UNSET_PROTECT_SEGMENT	= 310,	///< 去除录像保护时间段
	CWALKNET_OLT_RECORD_QUERY_FILE				= 311,	///< 查询录像文件
	CWALKNET_OLT_RECORD_OPEN_PLAYBACK			= 312,	///< 打开录像回放
	CWALKNET_OLT_RECORD_STOP_PLAYBACK			= 313,	///< 停止录像回放
	CWALKNET_OLT_RECORD_DOWNLOAD_START			= 314,	///< 录像下载开始
	CWALKNET_OLT_RECORD_DOWNLOAD_STOP			= 315,	///< 录像下载结束
	CWALKNET_OLT_RECORD_LOCAL_START				= 316,	///< 本地录像开始
	CWALKNET_OLT_RECORD_LOCAL_STOP				= 317,	///< 本地录像结束

	/// 矩阵操作
	CWALKNET_OLT_MATRIX_START					= 401,	///< 启动
	CWALKNET_OLT_MATRIX_STOP					= 402,	///< 停止

	/// 事件订阅
	CWALKNET_OLT_EVENT_SUBSCRIBE_START			= 501,	///< 事件订阅开始
	CWALKNET_OLT_EVENT_SUBSCRIBE_STOP			= 502,	///< 事件订阅结束

	/// 云台操作
	CWALKNET_OLT_PTZ_CONTROL					= 601,	///< 云台控制
	CWALKNET_OLT_PTZ_LOCK						= 602,	///< 云台锁定

	/// 界面操作
	CWALKNET_OLT_UI_CAPTURE_IMG					= 701,	///< 抓图

	/// 配置相关
	CWALKNET_OLT_CONFIG_DOWNLOAD_FILE			= 801,	///< 下载配置文件
	CWALKNET_OLT_CONFIG_UPDATE_FILE				= 802,	///< 更新配置文件

	CWALKNET_OLT_CONFIG_REGISTER_GATEWAY		= 803,	///< 增加网关设备
	CWALKNET_OLT_CONFIG_UNREGISTER_GATEWAY		= 804,	///< 删除网关设备
	CWALKNET_OLT_CONFIG_LIST_GATEWAY			= 805,	///< 获得网关设备列表

	CWALKNET_OLT_CONFIG_REGISTER_MOUNT			= 806,	///< 增加挂载设备
	CWALKNET_OLT_CONFIG_UNREGISTER_MOUNT		= 807,	///< 删除挂载设备
	CWALKNET_OLT_CONFIG_LIST_MOUNT				= 808,	///< 获得挂载设备列表

	CWALKNET_OLT_CONFIG_REGISTER_HOST			= 809,	///< 增加设备
	CWALKNET_OLT_CONFIG_UNREGISTER_HOST			= 810,	///< 删除设备
	CWALKNET_OLT_CONFIG_LIST_HOST				= 811,	///< 获得设备列表

	CWALKNET_OLT_CONFIG_REGISTER_CAM			= 812,	///< 增加摄像机
	CWALKNET_OLT_CONFIG_UNREGISTER_CAM			= 813,	///< 删除摄像机
	CWALKNET_OLT_CONFIG_LIST_CAM				= 814,	///< 获得摄像机列表

	CWALKNET_OLT_CONFIG_REGISTER_MON			= 815,	///< 增加监视器
	CWALKNET_OLT_CONFIG_UNREGISTER_MON			= 816,	///< 删除监视器
	CWALKNET_OLT_CONFIG_LIST_MON				= 817,	///< 获得监视器列表

	CWALKNET_OLT_CONFIG_REGISTER_IN_TRUNK		= 818,	///< 增加输入干线
	CWALKNET_OLT_CONFIG_UNREGISTER_IN_TRUNK		= 819,	///< 删除输入干线
	CWALKNET_OLT_CONFIG_LIST_IN_TRUNK			= 820,	///< 获得输入干线列表

	CWALKNET_OLT_CONFIG_REGISTER_OUT_TRUNK		= 821,	///< 增加输出干线
	CWALKNET_OLT_CONFIG_UNREGISTER_OUT_TRUNK	= 822,	///< 删除输出干线
	CWALKNET_OLT_CONFIG_LIST_OUT_TRUNK			= 823,	///< 获得输出干线列表

	CWALKNET_OLT_CONFIG_REGISTER_AUDIO			= 824,	///< 增加音频设备
	CWALKNET_OLT_CONFIG_UNREGISTER_AUDIO		= 825,	///< 删除音频设备
	CWALKNET_OLT_CONFIG_LIST_AUDIO				= 826,	///< 获得音频设备列表

	CWALKNET_OLT_CONFIG_REGISTER_ALARM_IN		= 827,	///< 增加报警输入设备
	CWALKNET_OLT_CONFIG_UNREGISTER_ALARM_IN		= 828,	///< 删除报警输入设备
	CWALKNET_OLT_CONFIG_LIST_ALARM_IN			= 829,	///< 获得报警输入设备列表

	CWALKNET_OLT_CONFIG_REGISTER_ALARM_OUT		= 830,	///< 增加报警输出设备
	CWALKNET_OLT_CONFIG_UNREGISTER_ALARM_OUT	= 831,	///< 删除报警输出设备
	CWALKNET_OLT_CONFIG_LIST_ALARM_OUT			= 832,	///< 获得报警输出设备列表

	CWALKNET_OLT_CONFIG_SET_CAM_LEVEL				= 833,	///< 设定摄像机级别
	CWALKNET_OLT_CONFIG_REGISTER_FORWARD_SERVER		= 834,	///< 增加转发服务器
	CWALKNET_OLT_CONFIG_UNREGISTER_FORWARD_SERVER	= 835,	///< 删除转发服务器

} CWALKNetOperatLogType;

/// DCS服务类型
typedef enum
{
	CWALKNET_SERVICETYPE_CMSERVICE	= 1,			///< 主控服务
	CWALKNET_SERVICETYPE_STREAMINGSERVICE	= 2,	///< 转发服务
	CWALKNET_SERVICETYPE_STORAGESERVICE	= 3,		///< 存储服务
	CWALKNET_SERVICETYPE_USRSERVICE	= 4,			///< 认证服务
	CWALKNET_SERVICETYPE_LOGSERVICE	= 5,			///< 日志服务
} CWALKNetServiceType;

//用户能力定义
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
	Talk = 1,  ///<仅喊话
	Listen = 2, ///< 仅监听
	ListenAndTalk = 3 ///< 双向对讲
}CWALKAudioMode;

typedef struct  
{
	float longitude;
	float latitude;
	INT focus;
}CWALKNetPTZPos;

/// OSD类型
typedef enum
{
	CWALK_OSD_UNKNOW = -1,			///< 未知类型
	CWALK_OSD_TEXT	= 0,			///< 文本
	CWALK_OSD_LINE	= 1,			///< 直线
	CWALK_OSD_RECT	= 2,			///< 放大矩形区域
	CWALK_OSD_TIME = 3,			///< 时间
} CWALKOSDType;

/// 点
typedef struct
{
	double x1;
	double y1;
} CWALKPoint;

/// OSD文本对齐方式
typedef enum
{
	CWALK_ALIGNMENT_LEFT = 0X0001,	///< 左对齐
	CWALK_ALIGNMENT_RIGHT = 0X0002	///< 右对齐
} CWALKOSDTextAlignType;

/// 文本
typedef struct
{
	CWALKPoint point;				///< 文字pos
	TCHAR text[256];			///< 文字
	TCHAR fontFamily[64];		///< 字体族
	BOOL autoColor;				///< 自动绘制颜色
	DWORD color;				///< 文字的颜色
	DWORD backColor;			///< 文字背景颜色
	double fontSize;			///< 字体相对的尺寸
	INT alignment;				///< 对齐方式 见：CWALKPLayOSDTextAlignType
	INT fillWaterMark;			///< osd方式  0 不平铺 1 平铺屏幕
} CWALKOSDText;

/// 线段
typedef struct
{
	double x1;					///< 起点的x坐标，为比例值，范围为[0.0,1.0]，x1=x/width
	double y1;					///< 起点的y坐标，为比例值，范围为[0.0,1.0]，y1=y/height
	double x2;					///< 终点的x坐标，为比例值，范围为[0.0,1.0]，x2=x/width
	double y2;					///< 终点的y坐标，为比例值，范围为[0.0,1.0]，y2=y/height
	DWORD lineWidth;			///< 线段的宽度
	DWORD color;				///< 颜色
}CWALKOSDLine;

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
} CWALKOSDRect;

/// 在线用户信息
typedef struct
{
	TCHAR userName[128];	    ///< 用户名
	TCHAR userDomain[128];      ///< 户所在域, dcs输出dcm地址
	TCHAR authServe[128];       ///< 用户认证服务器, dcs输出dcm地址
	TCHAR rank[128];            ///< 用户头衔, dcs不支持, 值为空
	TCHAR role[128];            ///< 用户角色, dcs值为空
	TCHAR userLocal[128];       ///< 用户所在地
	INT   level;                ///< 用户级别
	TCHAR waterMarkText[128];   ///< 数字水印内容
	INT   waterMarkType;        ///< 数字水印类型 0无水印 1满屏默认 2 标题默认 3 满屏自定义 4 标题自定义
}CWALKOnlineUser;

typedef struct _CWALKVodRecordInfo
{
	TCHAR file[64];
	// 本地时间，格式如20160622213348
	TCHAR strBegin[64];
	TCHAR strEnd[64];
	int nDepth; //录像深度，0-服务器录像, 非0录像所在的层数,最大值为256
	int nType;  //录像类型
	TCHAR storage[128];  //所在存储ID
}CWALKVodRecordInfo;

typedef struct
{
	TCHAR monitorId[128];	 /// 监视器id
	TCHAR monitorNo[32];	 /// 监视器编号
	TCHAR deviceId[128];	 /// 解码器id
	TCHAR userName[128];	 /// 操作用户名
	TCHAR ip[128];			 /// 操作用户ip
	TCHAR channelId[128];	 /// 摄像机id 
	TCHAR channelName[128];  /// 摄像机名称
	TCHAR userId[64];		 /// 用户id
	TCHAR nodeId[64];		 /// 节点id
	TCHAR monitorMode[16];   /// 监视器模式
	TCHAR res[512];			 /// 预留
}CWALKTransferStatus;

typedef struct 
{
	TCHAR begin[128];
	TCHAR end[128];
	int nDepth;			/// 录像深度. -1:全部层级, 0:本级录像, >0:录像所在的层数,最大值为256
	TCHAR res[512];		/// 预留
}CWALKTransferVodInfo;

typedef struct
{
	TCHAR osdInfo[512]; /// osd信息字符串
	TCHAR rtspUrl[512]; /// rtsp地址串
	//CWALKTransferVodInfo vodInfo;	/// 录像上墙信息
}CWALKTransferOptions;

typedef enum {

	CWALKCharacterEncoding_Local = 1,      //全部使用系统默认字符集；可能存在中文特殊字符乱码导致的数据解析失败等问题
	CWALKCharacterEncoding_UTF8,           //全部使用UTF8编码；推荐使用该配置
	CWALKCharacterEncoding_UTF8_Later102,  //接口使用UTF8编码，早期接口使用Local编码；适用于已对接过DCSSDK的产品升级版本的情况下
}CWALKCharacterEncodingType;

typedef enum {
	CWALKNET_TVWALL_Switch_Set = 0x00,		// 设置组切
	CWALKNET_TVWALL_Switch_Remove,			// 删除指定组切信息
	CWALKNET_TVWALL_Switch_Get,				// 获取指定组切信息
	CWALKNET_TVWALL_Switch_List,			// 列举所有组切信息
	/* TVWall switch
	request/response = 
	{
		//组切的id
		"id": "组切id",
		//版本号;由服务端维护;更新组切时此版本号与服务端不一致会导致接口失败
		"version" : 1,
		"name" : "组切名称",
		//(摄像机-监视器通道)对应关系数组
		"links" : [
			{
				//监视器通道编号;从1开始
				"channelNum": 1,
				//监视器通道id;省略时自动填写为channelNum
				"channelId" : "xxx",
				"monitorId" : "监视器id",
				//监视器类型;
				//0: 客户端视频播窗口
				//1: 电视墙设备
				"monitorType" : 1,
				//绑定的摄像机Id
				"cameraId" : "xxx",
				//绑定的摄像机名称
				"cameraName" : "xxx"
			}
		]
	}*/

	CWALKNET_TVWALL_RoundPlan_Set = 0x10,	// 设置电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_List,		    // 列举电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Get,		    // 获取指定电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Remove,	    // 删除电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Active,	    // 激活电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Inactive,	    // 禁用电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Start,	    // 立即执行电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_Stop,		    // 立即停止电视墙轮巡计划
	CWALKNET_TVWALL_RoundPlan_GetState,	    // 获取指定轮巡计划状态
	CWALKNET_TVWALL_RoundPlan_ListState,	// 列举轮巡计划状态
	/* TVWall RoundPlan
	request/response = 
	{
		// 轮巡计划id
		"id":"",
		// 版本号,由服务端维护
		"version" : 1,
		// 计划名称
		"name" : "",
		// 对其他用户是否可见
		"isSharedWithAllUser" : false,
		// 是否激活计划
		"isActive" : true,
		// 轮巡切换时间间隔(秒),范围 5-65535
		"interval" : 10,
		// 用一个字节表示是否使用以星期为计划的循环周期，以及星期几执行轮巡计划
		// 高8位为1时表示使用以星期为计划的循环周期
		// 低1位为1时表示[周日]激活轮巡计划
		// 低2位为1表示[周一]激活轮巡计划
		// 低3位为1表示[周二]激活轮巡计划，依此类推
		// 例如：0b10001011 (139)表示周日、周1、周3执行轮巡计划
		// 例如：0b00001011 (11)表示不使用以星期为循环周期
		// 注:
		//  - 20210922 目前仅支持以星期为计划的循环周期,此值小于128时表示此计划无效
		"cycleDaysOfWeek":255,
		// 摄像机列表
		"cameras" : [
			{
				// 摄像机id
				"id":"xxx",
				// [可选]
				"cameraName" : "xxx"
			}
		],
		// 监视器类型;
		// 0:客户端视频播窗口
		// 1:电视墙设备
		"monitorType":1,
		// 监视器通道列表
		"monitorChls" : [
			{
				// [可选] 监视器通道id,省略时自动填写为channelNum
				"channelId":"xxx",
				// 监视器通道编号,从1开始
				"channelNum" : 1,
				"monitorId" : "监视器id"
			}
		],
		// 时间段列表
		"timeRanges":[
			{
				// 开始时间,格式：HH*10000+mm*100+ss
				"startTime":3001,
				// 结束时间,格式：HH*10000+mm*100+ss
				"endTime" : 123001
			}
		],
		// [仅响应] 创建或更新此计划的用户唯一id
		"creatorId":"",
		// [仅响应] 创建或更新此计划的用户名
		"creatorAccount" : ""
	}*/

	CWALKNET_TVWALL_OpenLive = 0x20,		// 实时视频上墙
	CWALKNET_TVWALL_OpenVod,			    // 录像视频上墙
	CWALKNET_TVWALL_Close,				    // 关闭（实时、录像）上墙视频

	CWALKNET_TVWALL_Layout_Set = 0x30,	    // 设置电视墙布局
	CWALKNET_TVWALL_Layout_List,		    // 列举额电视墙布局
	CWALKNET_TVWALL_Layout_Get,			    // 获取指定电视墙布局
	CWALKNET_TVWALL_Layout_Remove,		    // 删除指定电视墙布局
	/* TVWALL_Layout
	request / response = 
	{
		// 布局id
		"id":"xxx",
		// 版本号,由服务端维护
		"version" : 1,
		// 创建或最近更新此布局的用户
		"creatorId" : "xxx",
		"creatorAccount" : "xxx",
		"creatorName" : "xxx",
		// 布局名称
		"name" : "布局名称",
		// 布局当前行数
		"rows" : 2,
		// 布局当前列数
		"columns" : 2,
		"items" : [
			{
				// 此项在布局中的所在行,从1开始;如果该值大于布局的rows,表示该项不在布局的当前显示范围
				"row":1,
				// 此项在布局中的所在列,从1开始;如果该值大于布局的columns,表示该项不在布局的当前显示范围
				"column" : 1,
				// 通道名称
				"name" : "xxx",
				// 0:dcs监视器通道; 1:监视器
				"targetType" : 0,
				// 监视器或dcs监视器通道id
				"targetId" : "xxx",
				// [可选] 如果targetType=1,必填,表示监视器通道数量
				"moChannelCnt" : 4,
				// [可选] 如果targetType=1,必填,表示监视器当前分屏行数
				"moRows" : 2,
				// [可选] 如果targetType=1,必填,表示监视器当前分屏列数
				"moColumns" : 2
			}
		]
	}*/

	CWALKNET_TVWALL_ListChannelStatus = 0x40, // 列举电视墙通道状态
	/* TVWall ListChannelStatus
	response = 
	[
		{
			// 监视器id
			"monitorId":"xxx",
			// 监视器通道编号,从1开始
			"chlNum" : 1,
			// 监视器通道id,如果没有通道id,则值等于chlNum
			"chlId" : "",
			// [可选] 如果此通道处于正在执行的轮巡计划中,则表示轮巡计划id
			"loopId" : "xxx1",
			// [可选] 如果loopId不为空,表示轮巡计划名称
			"loopName" : "xxx2",
			// [可选] 如果loopId不为空,表示轮巡计划创建者id
			"loopCreatorId" : "xxxx1",
			// [可选] 如果loopId不为空,表示轮巡计划创建者账户
			"loopCreatorAccount" : "xxxx1",
			// [可选] 如果有视频正在上墙,表示摄像机id
			"cameraId" : "xxx3",
			// [可选] 如果cameraId不为空,表示摄像机名称
			"cameraName" : "xxxx",
			// [可选] 如果有视频正在上墙,表示打开视频的用户的id
			"userId" : "xxx4",
			// [可选] 如果userId不为空,表示用户的账户名
			"userAccount" : "xxx5",
			// [可选] 如果userId不为空,表示用户名
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
	CWALKNET_MatrixCtrl_LikeGet = 0,	// 获取类命令
	CWALKNET_MatrixCtrl_LikeSet = 1,	// 设置类命令
	CWALKNET_MatrixCtrl_MAX,
}CWALKNetMatrixCtlCommand;

typedef struct {
	CWALKNetMatrixCtlCommand cmd;

	TCHAR* req;		// 请求参数 json格式字符串
	TCHAR* resp;	// 相应参数 json格式字符串
	INT respLen;	// 相应内容长度

	TCHAR* message;	// 执行结果
	INT messageLen;
}CWALKNetMatrixCtrlParam;

//状态缓存最大值

/// 获得SDK版本信息
/// @param[out]	infoBuf		得到SDK版本信息,内存空间由调用者分配,可以通过CWALK_NET_InfoParseKeyValue()来解析
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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetSDK_Version(
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 获得cmservice服务版本信息
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]  infoBuf	infoBuf返回版本json
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerVersion(
	CWALK_NET_HD userHD, 
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// (不推荐使用)初始化SDK,使用本地编码,
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Init();

/// 初始化SDK
/// @param[in]	type		接口数据的编码类型，推荐使用CWALKCharacterEncoding_UTF8
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_Init(CWALKCharacterEncodingType type);

/// 清除SDK资源
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Cleanup();

///	登录DCS服务器
/// @param[out]	userHD		得到用户登录句柄
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	userName	登录用户名
///	@param[in]	passwd		登录密码
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Login(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	const TCHAR* passwd
	);

///	登录DCS服务器
/// @param[out]	userHD		得到用户登录句柄
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	userName	登录用户名
///	@param[in]	passwd		登录密码
///	@param[in]	userMAC		MAC ADDR
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByMAC(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	const TCHAR* passwd,
	const TCHAR* userMAC
	);


///	登录SPecial服务器，dcs不支持
/// @param[out]	userHD		得到用户登录句柄
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	ipOrHost	url
///	@param[in]	port		tgt
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByTGT(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* url,
	const TCHAR* tgt
	);

///	指静脉登录DCS服务器
/// @param[out]	userHD		得到用户登录句柄
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	domain		域名
///	@param[in]	img			指静脉数据
///	@param[in]	len			img数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByFingerModel(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* domain,
	const BYTE* img,
	INT len
	);

/// 获取摄像机变化回调函数
///	@param[in]	userParam	用户数据
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	changedVersion	objectsTree的版本序列号
typedef void (CWALK_SDK_CALLBACK *CallBack_OnCamerasChangedNotify)(
	void* userParam,
	CWALK_NET_HD userHD,
	INT64 changedVersion
	);

///	设置摄像机变化回调函数，暂不支持
///	@param[in]	userHD		        登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnCamerasChangedNotify	回调函数指针，如果为NULL，将取消回调
/// @param[in]	userParam	        用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCamerasChangedNotify(
	CWALK_NET_HD userHD,
	CallBack_OnCamerasChangedNotify fnOnCamerasChangedNotify,
	void* userParam
	);

/// 获取摄像机变化版本信息，暂不支持
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	changedVersion	摄像机变化版本
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCamerasChangedVersion(
	CWALK_NET_HD userHD,
	INT64* changedVersion
	);

///	获取认证码
///	@param[in]	ipOrHost	认证服务器IP，DCS时为cmservice的ip
///	@param[in]	port		认证服务器端口，DCS时为cmservice的端口
///	@param[in]	userName	登录用户名
///	@param[in]	passwd		登录密码
/// @param[out] infoBuf		保存认证信息,内存空间由调用者分配
/// @param[in]  len			infoBuf长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTicket(
	const TCHAR* ipOrHost,
	INT port, 
	const TCHAR* userName, 
	const TCHAR* passwd,
	BYTE* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

///	通过认证信息登录服务器
/// @param[out]	userHD		得到用户登录句柄
///	@param[in]	ipOrHost	服务器ip或dns
///	@param[in]	port		服务器端口
///	@param[in]	ticket	    认证信息，由CWALK_NET_GetTicket()获得
///	@param[in]	len		    认证信息长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_LoginByTicket(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost,
	INT port, 
	BYTE* ticket,
	INT len
	);

///	登出DCS服务器
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_Logout(
	CWALK_NET_HD userHD
	);

/// 获得与服务器的连接状态
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	connect		连接状态，TRUE-正常状态，FALSE-断线状态
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_IsConnected(
	CWALK_NET_HD userHD, 
	BOOL* connect
	);

/// 获取服务器时间
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] dateTime	返回的时间，内存空间由调用者分配,格式为:"2020-01-01 13:20:00.000"
/// @param[in]  len			dateTime的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerTime(
	CWALK_NET_HD userHD,
	TCHAR* dateTime,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 设置服务器时间
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	dateTime	设置时间,格式："2020-01-01 13:20:00.000" 或 "20200101132000000"
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetServerTime(
	CWALK_NET_HD userHD,
	const TCHAR* dateTime
	);

/// 将设备时间同步为服务器系统时间
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
///							plus中非空时表示设备或通道uuid
///	@param[in]	camPath	    对象名称为ID
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SyncDeviceTime(
	CWALK_NET_HD userHD,
	const TCHAR* serName /*=NULL*/,
	const TCHAR* camPath
	);

///	得到用户的描述信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	buf			存放描述信息的地址；内存空间由调用者分配；如果为NULL，则返回描述信息的实际长度。
/// @param[in,out] bufLen   调用者分配的内存空间的长度，返回拷贝到buf中数据的长度
/// @param[out]	dataLen		返回描述信息的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserDescription(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT* bufLen,
	INT* dataLen /*= NULL*/
	);

///	修改用户密码（不支持）
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	oldPasswd	旧密码
/// @param[in]  newPasswd	新密码
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetUserPasswd(
	CWALK_NET_HD userHD,
	const TCHAR* oldPasswd,
	const TCHAR* newPasswd
	);

///	获取用户数据
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	buf			存放用户数据；内存空间由调用者分配；如果为NULL，则返回用户数据的实际长度。
/// @param[in]  bufLen		调用者分配的内存空间的长度
/// @param[out]	dataLen		返回用户数据的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserData(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT bufLen,
	INT* dataLen /*= NULL*/
	);

///	设置用户数据
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	data		用户数据
/// @param[in]	dataLen		用户数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetUserData(
	CWALK_NET_HD userHD,
	void* data,
	INT dataLen
	);

/// 列举用户回调函数
///	@param[in]	userParam	用户数据
///	@param[in]	jsonInfo	单个用户信息 json数据结构
///					"onlineStatus":			在线状态 int
///					"departmentCode":		组织机构码 str
///					"departmentName" :		组织机构名称 str
///					"id" :					用户ID str
///					"name" :				用户名称 str
///					"userParam":			用户参数 str
///					"loginName" :			用户登陆名称 str
///					"level" :				用户级别 int
///					"watermarking" :		是否水印 str
///					"watermarkingTitle" :	水印标题 str
///					"nodeId" :				用户所属ID str
typedef void (CWALK_SDK_CALLBACK *CallBack_OnListUsers)(
	void* userParam,
	const TCHAR* jsonUserInfo
	);

///	列举用户信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnUsers	回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListUsers(
	CWALK_NET_HD userHD,
	CallBack_OnListUsers fnOnUsers,
	void* userParam
);

/// 列举在线用户回调函数
///	@param[in]	userParam	用户数据
///	@param[in]	userName	用户名
///	@param[in]	userDomain	用户所在域, dcs输出dcm地址
/// @param[in]	authServe	用户认证服务器, dcs+输出dcm地址
///	@param[in]	rank		用户头衔, dcs不支持, 值为空
///	@param[in]	role		用户角色, dcs值为空
///	@param[in]	userLocal	用户所在地
///	@param[in]	level		用户级别
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

/// 列举在线用户回调函数
///	@param[in]	userParam	用户数据
///	@param[in]	onlineUser	用户信息
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetOnlineUsersEx)(
	void* userParam,
	CWALKOnlineUser * onlineUser
	);


///	列举在线用户信息，注：只能列举到比当前用户级别低的用户
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[in]	fnOnUsers	回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 服务器的传输信息回调函数
///	@param[in]	userParam	用户数据
///	@param[in]	source		源地址，以特定字符串开头
///

/// 
///	@param[in]	target		目的地址,以特定字符串开头
///	

///	
///	@param[in]	users		使用用户，可能是多个，以“;”隔开，如："user1;user2;user3..."
/// @param[in]	trunkin		所使用的输入干线
/// @param[in]	trunkout	对应网关的输出干线
/// @param[in]	gateway		所经过的网关名称
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetTransferStatus)(
	void* userParam,	
	const TCHAR* source,
	const TCHAR* target,
	const TCHAR* users,
	const TCHAR* trunkin,
	const TCHAR* trunkout,
	const TCHAR* gateway
	);

/// 获取服务器的传输信息,注：只能获取到比登录用户级别低的传输使用信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[in]	fnOnStatus	回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 得到服务器的状态信息，dcs不支持
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]  serviceType 服务器类型
/// @param[out] infoBuf		存放由服务器返回的信息，内存由使用者分配
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServiceStatus(
	CWALK_NET_HD userHD,
	CWALKNetServiceType serviceType,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 得到服务器地址
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]  serviceType 服务器类型
/// @param[out] buf			存放由服务器返回的地址信息，内存由使用者分配,多个地址以“,”分割
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServiceAddrs(
	CWALK_NET_HD userHD,
	CWALKNetServiceType serviceType,
	void* buf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 得到服务器平台信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] buf			存放由服务器返回的信息，内存由使用者分配
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerInfo(
	CWALK_NET_HD userHD,
	void* buf,
	INT* realLen /*= NULL*/
	);

/// 获取编号映射表回调函数
/// @param[in]	userParam	用户数据
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	id			对象编号
/// @param[in]	name		对象名称
/// @return
///	-	TRUE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListID)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* id,
	const TCHAR* name				
	);

/// 获取编号映射表
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	idType		编号类型；1－通道； 2－监视器；其它－未使用 
/// @param[out]	count		列举到的对象个数
/// @param[in]	fnOnListID	编号映射表回调函数
/// @param[in]	userParam	用户数据（作为回调函数的参数）
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetID(
	CWALK_NET_HD userHD,
	INT idType,
	INT* count /*=NULL*/,
	CallBack_OnListID fnOnListID /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// 对象列举回调函数
/// @param[in]	userParam	用户数据
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		列举的设备类型
/// @param[in]	objName		对象名称
/// @param[in]	objInfo		对象所有属性,可以通过CWALK_NET_InfoParseKeyValue()来解析
/// @return
///	-	TRUE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListObj)(
	void* userParam,
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* objName,
	const TCHAR* objInfo				
	);

/// 列举对象
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		要列举的设备类型
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[out]	count		列举到的对象个数
/// @param[in]	fnOnListObj	对象列举回调函数
/// @param[in]	userParam	用户数据（作为回调函数的参数）
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjects(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* serName /*=NULL*/,
	INT* count /*=NULL*/,
	CallBack_OnListObj fnOnListObj /*= NULL*/,
	void* userParam /*= NULL*/
	);

/// 列举对象
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		要列举的设备类型
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[out]	count		列举到的对象个数
/// @param[in]	fnOnListObj	对象列举回调函数
/// @param[in]	userParam	用户数据（作为回调函数的参数）
/// @param[in] isGetAllCamera 是否列举所有有权限设备，isGetAllCamera =TRUE&&GroupID == NULL,获取所有的摄像机，isGetAllCamera=FALSE&& GroupID == null,从之前的缓存中获取相应的信息
/// @param[in] GroupID      列举当前分组下的有权限的设备，GroupID！= NULL,获取当前Groupid对应的摄像机
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 列举对象，结果输出为字符串
///	@param[in]		userHD			登录句柄,由CWALK_NET_Login()获得
/// @param[in]		objType			要列举的设备类型
/// @param[in]		resultData		列举结果
/// @param[in/out]	resultLen		输入时为应用分配resultData长度，输出时为结果长度。长度不足会返回对应错误。
/// @param[in]		isGetAllCamera	是否列举所有有权限设备，isGetAllCamera =TRUE&&GroupID == NULL,获取所有的摄像机，isGetAllCamera=FALSE&& GroupID == null,从之前的缓存中获取相应的信息
/// @param[in]		GroupID			列举当前分组下的有权限的设备，GroupID！= NULL,获取当前Groupid对应的摄像机
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjectsEXAsStr(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	TCHAR* resultData,
	INT64* resultLen,
	const TCHAR *GroupID,
	bool isGetAllCamera
	);

/// 批量列举对象
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		要列举的设备类型
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[out]	camInfo		摄像机信息
/// @param[in,out] len			camInfo长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListObjectsBatch(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* serName /*=NULL*/,
	TCHAR* camInfo,
	INT* len
	);

/// 批量列举摄像机
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[out]	camInfo		摄像机信息
/// @param[out] len			camInfo长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatch(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	TCHAR* camInfo,
	INT* len
	);

/// 批量列举摄像机
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[in] isGetAllCamera 是否列举所有有权限设备，isGetAllCamera =TRUE&&GroupID == NULL,获取所有的摄像机，isGetAllCamera=FALSE&& GroupID == null,从之前的缓存中获取相应的信息
/// @param[in] GroupID      列举当前分组（行政区划）下的有权限的设备，GroupID！= NULL,获取当前Groupid对应的摄像机
/// @param[out]	camInfo		摄像机信息
/// @param[out] len			camInfo长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchEx(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	const TCHAR *GroupID,
	bool isGetAllCamera,
	TCHAR* camInfo,
	INT* len
	);

/// 批量列举摄像机 （dcs暂不支持）
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[out]	camInfo		摄像机信息
/// @param[out] len			camInfo长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchBinary(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	BYTE* camInfo,
	INT* len
	);

/// 批量列举业务分组下摄像机（DCS支持）
/// @param[in]	serName		服务器名称,当为NULL或_T("")时，表示当前登录服务器
/// @param[in] isGetAllCamera 是否列举所有有权限设备，isGetAllCamera =TRUE&&GroupID == NULL,获取所有的摄像机，isGetAllCamera=FALSE&& GroupID == null,从之前的缓存中获取相应的信息
/// @param[in] GroupID      列举当前分组（业务分组）下的有权限的设备，GroupID！= NULL,获取当前Groupid对应的摄像机
/// @param[out]	camInfo		摄像机信息
/// @param[out] len			camInfo长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ListCameraBatchInVirtualGroup(
	CWALK_NET_HD userHD,
	const TCHAR* serName,
	const TCHAR *GroupID,
	bool isGetAllCamera,
	void* camInfo,
	INT* len
	);

/// 动态添加对象
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		要列举的设备类型
/// @param[in]	parent		无效参数
/// @param[in]	objInfo		对象其它的信息,JSON格式字符串,可由CWALK_NET_InfoXXX系列函数生成
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_AddObject(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* parent /*=NULL*/,
	const TCHAR* objInfo
	);

/// 删除对象
/// @param[in]  userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]  objType		要列举的设备类型
/// @param[in]  objName		对象名称,可以是CallBack_OnListObj()回调中的objName
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_DelObject(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* objName
	);

/// 得到组织结构信息
/// @param[in]  userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	buf			存放组织结构信息的地址；内存空间由调用者分配；如果为NULL，则返回描述信息的实际长度。
/// @param[in,out] bufLen   调用者分配的内存空间的长度，返回拷贝到buf中数据的长度
/// @param[out]	dataLen		返回组织结构信息的实际长度
/// @param[out] orgCount	返回组织结构节点个数
/// @param[out] dcsCount	返回组织结构中dcs的个数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOrganization(
	CWALK_NET_HD userHD,
	void* buf /*= NULL*/,
	INT* bufLen,
	INT* dataLen /*= NULL*/,
	INT* orgCount /*= NULL*/,
	INT* dcsCount /*= NULL*/
	);

/// 得到分组结构信息（groupID）
/// @param[in]  userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	buf			存放组织结构信息的地址；内存空间由调用者分配；如果为NULL，则返回描述信息的实际长度。
/// @param[in,out] bufLen   调用者分配的内存空间的长度，返回拷贝到buf中数据的长度
/// @param[out]	dataLen		返回组织结构信息的实际长度
/// @param[out] orgCount	返回组织结构节点个数
/// @param[out] dcsCount	返回组织结构中dcs的个数
/// @param[in] bUseUserID	是否使用userID
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetOrganizationEX(
	CWALK_NET_HD userHD, 
	void* buf /*= NULL*/, 
	INT* bufLen, 
	INT* dataLen /*= NULL*/, 
	INT* orgCount /*= NULL*/,
	INT* dcsCount /*= NULL*/,
	BOOL bUseUserID
	);

/// 得到分组结构信息（groupID）
/// @param[in]  userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	groupType	分组类型，详见CWALKNetGroupType, CWALKNET_GROUPTYPE_UNKNOW则返回行政区划+业务分组。
/// @param[in]	buf			存放组织结构信息的地址；内存空间由调用者分配；如果为NULL，则返回描述信息的实际长度。
/// @param[in,out] bufLen   调用者分配的内存空间的长度，返回拷贝到buf中数据的长度
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetGroup(
	CWALK_NET_HD userHD,
	CWALKNetGroupType groupType,
	void* buf,
	INT* bufLen
	);

/// 得到登录服务器的标题
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	serverName	无效参数
/// @param[out] infoBuf		存放登录服务器的标题，内存由使用者分配
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerTitle(
	CWALK_NET_HD userHD,
	const TCHAR* serverName /*= NULL*/,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 得到登录服务器的名称
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[out] infoBuf		存放登录服务器的名称，内存由使用者分配
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerName(
	CWALK_NET_HD userHD,
	void* infoBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 获取对象状态
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objType		要列举的设备类型
/// @param[in]	objName		对象名称, 可以是CallBack_OnListObj回调中的objName
/// @param[out]	status		0 - 在线；小于0值 - 不在线；其它 － 错误码
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetObjectStatus(
	CWALK_NET_HD userHD,
	CWALKNetObjectType objType,
	const TCHAR* ojbName,
	INT* status
	);

/// 获取摄像机状态	DCS.1返回不在线摄像机ID  DCS返回摄像机状态
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objName		对象名称, 可以是CallBack_OnListObj回调中的objName
///							为空时表示查询所有摄像机的状态
/// @param[out]	buf			存放状态信息,内存空间由调用者分配，结果可以通过CWALK_NET_InfoParseKeyValue()来解析
/// @param[in]	bufLen		buf长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCameraStatus(
	CWALK_NET_HD userHD,
	const TCHAR* ojbName,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// 获取通道录像计划表
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objName		对象名称, 可以是CallBack_OnListObj回调中的objName
/// @param[out]	buf			存放状态信息,内存空间由调用者分配
/// @param[in]	bufLen		buf长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetRecordSchedule(
	CWALK_NET_HD userHD,
	const TCHAR* ojbName,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// 设置摄像机的级别
/// 注：设置成功之后，低于此级别的用户图象将会被关闭
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] level		要设置的级别，范围：[0－256]，0 － 表示没有限制；
///								非0 － 值越大，权限越高，最高为用户本身的级别。
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCameraLevel(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT level
	);

/// 开始服务端手动录像, 注:手动录像在登出后将会自动停止
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		AV对象名
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath
	);

/// 开始服务端手动录像, 注:手动录像在登出后将会自动停止
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		AV对象名
///	@param[in]	duration	录像时长，单位ms，可调用CWALK_NET_StopRecord提前停止
///	@param[in]	saveTime	录像保存时间，单位天
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRecordEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT64 duration,
	INT saveTime
	);

/// 停止服务端手动录像
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		AV对象名
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath
	);

/// 列举录像时间段
/// @param[in] userParam	用户数据
/// @param[in] userHD		登录句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	时间段开始时间,格式："2020-01-01 13:20:00.000"
/// @param[in] endTime		时间段结束时间（不含）
/// @param[in] vodType		录像位置类型，在非ihost环境下，0为服务器（SS），1为前端设备。
/// @return
///	-	TURE		断续下一次回调
///	-	FALSE		结束回调
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


/// 查询录像
/// 注: 非法录像时间段会被过滤掉,错误信息记录到日志中
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0-服务器录像, 非0 录像所在的层数,最大值为256
/// @param[in] beginTime	起始时间, 格式："2020-01-01 13:20:00.000" 或 "20200101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnOnListSegment	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 查询录像
/// 注: 非法录像时间段会被过滤掉,错误信息记录到日志中
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnOnListSegment	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordExp(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);


/// 列举录像时间段
/// @param[in] userParam	用户数据
/// @param[in] userHD		登录句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	时间段开始时间,格式："2012-01-01 13:20:00.000"
/// @param[in] endTime		时间段结束时间（不含）
/// @param[in] segType		录像类型和录像深度（最后一个字节是录像深度，前面的字节是录像类型），录像类型取值
///		0 - 自动录像 
///		1 - 预录像
/// 	2 - 手动录像
/// @return
///	-	TURE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnListSegmentsEx)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime, 
	INT	segType
	);

/// 查询录像
/// 注: 非法录像时间段会被过滤掉,错误信息记录到日志中
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0-服务器录像, 非0 录像所在的层数,最大值为256
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnOnListSegment	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegmentsEx fnOnListSegment,
	void* userParam /*= NULL*/
	);


/// 自动查询录像
/// 注: 非法录像时间段会被过滤掉,错误信息记录到日志中
/// 自动查询录像，返回第一次查询到的录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnOnListSegment	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordAuto(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);

/// 保护录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ProtectRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime
	);

/// 解除录像保护
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_UnprotectRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime
	);

/// 列举受保护录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] fnOnListSegment	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryProtectionRecord(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CallBack_OnListSegments fnOnListSegment,
	void* userParam /*= NULL*/
	);

/// 获取vod状态
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	status		对象的状态值,依赖DCS
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetVodStatus(
	CWALK_NET_HD userHD,
	INT* status
	);

/// 云台控制（通过用户句柄）
/// 注:云台的每一个动作都要调用该接口两次,前面两个参数一样,只是param一次为非0,一次为0
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] cmd			云台控制命令
/// @param[in] param		让云台停止动作还是开始动作: >0 - 以设定速度开始;0 - 停止,最大为CWALKNET_PTZ_MAX_SPEED
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzControl(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CWALKNetPTZCommand cmd,
	INT param
	);

/// 云台辅助开关控制
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] num			开关编号
/// @param[in] control		控制参数：TRUE - 打开；FALSE － 关闭
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzAuxControl(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT num,
	BOOL control
	);

/// 3D云台控制（通过用户句柄）
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] direct		控制命令,0 - 放大、1 - 缩小、2 - 跟随、其他 - 未使用
/// @param[in] x			控制参数,取值范围[0 - 1]
/// @param[in] y			控制参数,取值范围[0 - 1]
/// @param[in] w			控制参数,取值范围[0 - 1]
/// @param[in] h			控制参数,取值范围[0 - 1]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD  CWALK_NET_PtzControl3D(
	CWALK_NET_HD userHD, 
	const TCHAR* avPath, 
	INT direct,
	float x,
	float y,
	float w,
	float h
	);

/// PTZ控制锁定
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] lockTime		PTZ控制锁定时间 单位为秒(s)，0表示解锁，非0表示锁定
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzLock(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT lockTime
	);

/// 云台控制扩展（通过用户句柄）
/// 注:云台的每一个动作都要调用该接口两次,前面两个参数一样,只是param一次为非0,一次为0
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] cmd			云台控制命令
/// @param[in] param		
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzControlEx(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	CWALKNetPTZCommand cmd,
	const TCHAR* param
	);

/// 设置预置位（通过用户句柄）
///	@param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		AV对象名
/// @param[in] name			预置位别名
/// @param[in] param		预置位序号
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzSetView(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* name,
	INT index
	);

/// 获取预置位
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		摄像机名称
/// @param[out]	bufInfo		预置位信息，json格式：[{"name":"set1", "index":1},{}]
/// @param[in]	len			bufInfo的长度
/// @param[out]	realLen		返回数据的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_PtzListView(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	void* bufInfo,
	INT len,
	INT* realLen
	);

/// 获取云台状态
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[out] statusBuf	存放PTZ的状态信息，内存由使用者分配，信息可以通过CWALK_NET_InfoParseKeyValue()来解析
/// @param[in]  bufLen		statusBuf的长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzStatus(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	void* statusBuf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// 获取云台PTZ三相坐标信息
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[out] buf			存放PTZ的坐标信息，内存由使用者分配，信息为Json格式字符串
/// @param[in]  bufLen		buf的长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzPosition(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);

/// 获取GIS信息
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	avPath		对象名称
/// @param[out] buf			存放GIS信息，内存由使用者分配，信息为Json格式字符串
/// @param[in]  bufLen		buf的长度
/// @param[out] realLen		返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetCameraGis(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	void* buf,
	INT bufLen,
	INT* realLen /*= NULL*/
	);


/// GIS信息订阅回调函数
/// @param[in]	userParam	用户参数
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	camPath		对象名称
/// @param[out] buf			存放GIS信息，信息为Json格式字符串
/// @param[in]  bufLen		buf的长度
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGisInfoUpload)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	const void* buf,
	const INT bufLen
	);

/// 订阅GIS信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnEvent	处理事件的回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeGisInfo(
	CWALK_NET_HD userHD,
	CallBack_OnGisInfoUpload fnOnGisInfo,
	void* userParam
	);

/// 退订GIS信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelGisInfoSubscription(
	CWALK_NET_HD userHD
	);

/// 订阅主动推送GIS信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnEvent	处理事件的回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeGisInfoByActive(
	CWALK_NET_HD userHD,
	CallBack_OnGisInfoUpload fnOnGisActive,
	void* userParam
);

/// 退订主动推送GIS信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelGisInfoSubscriptionByActive(
	CWALK_NET_HD userHD
);

/// 抓取通道图片（通过摄像机端直接返回的实时图片）
/// @param[in]	userHD			登录句柄,由CWALK_NET_Login()获得
/// @param[in]	avPath			对象名称
/// @param[out] picResolution	图片分辨率（1920x1080...）
/// @param[out] picFormat		图片封装格式（jpeg,png,gif...）
/// @param[out] picBuff			存放图片二进制数据，内存由使用者分配
/// @param[in]  buffLen			picBuff的长度
/// @param[out] realLen			返回实际信息的长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CapCameraPicture(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	TCHAR* picResolution,
	TCHAR* picFormat,
	TCHAR* picBuff,
	INT  buffLen,
	INT* realLen
);

/// 重启摄像通道
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraReset(
	CWALK_NET_HD userHD,
	const TCHAR* camPath
	);

/// 获取摄像通道颜色调节参数
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[out]	brightness	亮度，  值为[-127,127]
/// @param[out]	contrast	对比度，值为[-127,127]
/// @param[out]	saturation	饱和度，值为[-127,127]
/// @param[out]	hue			色调，  值为[-127,127]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraGetVideoColor(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT* brightness,
	INT* contrast,
	INT* saturation,
	INT* hue
	);

/// 获取音频通道音频参数
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[out]  channels		通道数
/// @param[out]  bitsPerSample	每样本位数
/// @param[out]  samplesPerSec		每秒样本数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码

/// 设置摄像通道颜色调节参数
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[in]	brightness	亮度，  值为[-127,127]
/// @param[in]	contrast	对比度，值为[-127,127]
/// @param[in]	saturation	饱和度，值为[-127,127]
/// @param[in]	hue			色调，  值为[-127,127]
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CameraSetVideoColor(
	CWALK_NET_HD userHD,
	const TCHAR* camPath,
	INT brightness,
	INT contrast,
	INT saturation,
	INT hue
	);

/// 获取摄像通道编码参数
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[out]	standard	视频制式 0: NTSC 1: PAL
/// @param[out]	frameRate	帧频 在PAL制下取值1-25, NTSC制下1-30
/// @param[out]	width		宽度
/// @param[out]	height		高度
/// @param[out]	bitRate		比特率;为0表示不限定比特率, 非0表示限定最大比特率, 单位bits/sec
/// @param[out]	quality		图像质量 取值0~31, 值越小图像质量越好
/// @param[out]	iFrameInterval	I帧间隔(>=1)
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 设置摄像通道编码参数
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camPath		对象名称
/// @param[in]	standard	视频制式 0: NTSC 1: PAL
/// @param[in]	frameRate	帧频 在PAL制下取值1-25, NTSC制下1-30
/// @param[in]	width		宽度
/// @param[in]	height		高度
/// @param[in]	bitRate		比特率;为0表示不限定比特率, 非0表示限定最大比特率, 单位bits/sec
/// @param[in]	quality		图像质量 取值0~31, 值越小图像质量越好
/// @param[in]	iFrameInterval	I帧间隔(>=1)
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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
 
/// 执行脚本
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	scriptType	脚本类型
/// @param[in]	script		脚本
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ExecuteScript(
	CWALK_NET_HD userHD,
	const TCHAR* scriptType,
	const TCHAR* script
	);

/// 事件订阅回调函数
/// @param[in]	userParam	用户参数
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	happenTime	报警发生时间 "2012-01-01 13:20:00.000"(含毫秒)
/// @param[in]	objName		报警对象名称,可能为"$"、"host/"、"av/"、"ai/"等
///							plus为设备uuid或"cms"
/// @param[in]	objInfo		服务器上报的所有信息
/// @param[in]	eventType	事件类型
/// @param[in]	status		事件状态,1为报警态,0为正常态
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEvent)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* happenTime,
	const TCHAR* objName,
	const TCHAR* objInfo,
	CWALKNetEventType eventType,
	INT status
	);

/// 事件订阅
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnEvent	处理事件的回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEvent(
	CWALK_NET_HD userHD,
	CallBack_OnEvent fnOnEvent,
	void* userParam
	);

/// 取消订阅
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscription(
	CWALK_NET_HD userHD
	);

/// 智能数据订阅回调函数
/// @param[in]	userParam	用户参数
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objName		对象名称
/// @param[in]	data		智能数据
/// @param[in]	dataLen		智能数据长度
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEvent2)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* objName,
	const BYTE* data,
	INT dataLen
	);

/// 智能数据订阅
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnEvent	处理事件的回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEvent2(
	CWALK_NET_HD userHD,
	CallBack_OnEvent2 fnOnEvent,
	void* userParam
	);

/// 取消智能数据订阅
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscription2(
	CWALK_NET_HD userHD
	);

/// 智能数据回调函数（扩展，可以添加事件过滤器）
/// @param[in]	userParam	用户参数
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	objName		报警对象名称,可能为"$"、"host/"、"av/"、"ai/"等
/// @param[in]	happenTime	报警发生时间 "2012-01-01 13:20:00.000"(含毫秒)
/// @param[in]	eventType	事件类型
/// @param[in]	data		服务器上报的所有信息,可以通过CWALK_NET_InfoParseKeyValue()来解析
/// @param[in]	dataLen		上报信息数据长度
typedef void (CWALK_SDK_CALLBACK *CallBack_OnEventEx)(
	void* userParam,
	CWALK_NET_HD userHD,
	const char* objName,
	CWALKNetEventType eventType,
	INT64/*00*/ happenedTime,
	const void* data,
	INT_PTR dataLen
	);

/// 智能数据订阅（扩展，可以添加事件过滤器）
///	注: 必须使用CWALK_NET_CancelEventSubscriptionEx()取消订阅
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	userParam	用户数据
/// @param[in]	fnOnEvent	处理事件的回调函数
/// @param[in]	objNames	关心的事件对象，可以有多个，使用字符'\n'分隔（NULL表示订阅所有）
/// @param[in]	types		关心的事件类型，可以有多个，最后以CWALKNET_EVENT_UNKNOWN结尾（NULL表示订阅所有）
/// @return
/// -	CWALKSDK_OK	成功
/// -	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SubscribeEventEx(
	CWALK_NET_HD userHD,
	void* userParam,
	CallBack_OnEventEx fnOnEvent,
	const char* objNames,
	const CWALKNetEventType* types
	);

/// 取消订阅
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CancelEventSubscriptionEx(
	CWALK_NET_HD userHD
	);

/// 发起摄像机到监视器的传输
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	source		摄像机名称
///							dcs+中参数格式同CWALK_NET_StartStream
/// @param[in]	target		监视器名称
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartTransfer(
	CWALK_NET_HD userHD,
	const TCHAR* source,
	const TCHAR* target
	);

/// 发起摄像机到监视器的传输
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	source		摄像机名称
///							dcs+中参数格式同CWALK_NET_StartStream
/// @param[in]	target		监视器名称
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartTransferEx(
	CWALK_NET_HD userHD,
	const TCHAR* source,
	const TCHAR* target,
	CWALKTransferOptions options
	);

/// 停止到某个监视器的传输
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	target		监视器名称
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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


/// 分割监视器的窗格数量
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	target		监视器名称（同一解码器下任意视频通道编号）
/// @param[in]	window		解码器输出窗口序号（一个解码器对应多个VO输出，默认1开始）
/// @param[in]	cnt			分割窗格数量（1、2、4、8、9....）
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SplitScreen(CWALK_NET_HD userHD, const TCHAR* target, const TCHAR* window, const TCHAR* cnt);


/// 抢占回调通知函数
/// @param[in]	userParam	用户参数
/// @param[in]	streamHD	实时视频句柄,由CWALK_NET_StartStream()获得
/// @param[in]	target		被抢占的监视器名称
/// @param[in]	robUser		抢占用户
/// @param[in]	robNode		抢占结点
typedef void (CWALK_SDK_CALLBACK *CallBack_OnTransferRobbed)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* target,
	const TCHAR* robUser,
	const TCHAR* robNode
	);

/// 设置切换抢占通知回调
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	fnOnRobbed  抢占通知回调函数
/// @param[in]	userParam	用户参数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetTransferRobbedCallBack(
	CWALK_NET_HD userHD,
	CallBack_OnTransferRobbed fnRobbed,
	void* userParam
	);

/// 流数据回调函数,由CWALK_NET_StartStream()、CWALK_NET_StartAudio（）或者CWALK_NET_StartPlaybackStream()调用
/// @param[in]	userParam	用户数据
///	@param[in]	streamHD	播放句柄
/// @param[in]	data		回调的数据
/// @param[in]	dataLen		回调数据长度
typedef void (CWALK_SDK_CALLBACK *Callback_OnStreamData)(
	void* userParam,	
	CWALK_NET_HD streamHD,
	const void* data,
	INT dataLen
	);

/// 流数据回调函数,由CWALK_NET_StartPlaybackStreamEx()调用
/// @param[in]	userParam	用户数据
///	@param[in]	streamHD	播放句柄
/// @param[in]	data		回调的数据
/// @param[in]	dataLen		回调数据长度
/// @param[in]	packageSeriNum		回调当前数据序列号
typedef void (CWALK_SDK_CALLBACK *Callback_OnStreamDataEx)(
	void* userParam,	
	CWALK_NET_HD streamHD,
	const void* data,
	INT dataLen,
	INT64 packageSeriNum
	);


/// 实时流抢占回调通知函数
/// @param[in]	userParam	用户数据
/// @param[in]	streamHD	实时视频句柄,由CWALK_NET_StartStream()获得
/// @param[in]	robUser		抢占用户
/// @param[in]	robNode		抢占结点
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStreamRobbed)(
	void* userParam,
	CWALK_NET_HD streamHD,
	const TCHAR* robUser,
	const TCHAR* robNode	
	);

/// 异步实时流开流消息回调通知函数
/// @param[in]	userParam	用户数据
/// @param[in]	streamHD	异步实时视频句柄,由CWALK_NET_StartStreamByAsync()获得
/// @param[in]  streamResult	开流结果
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStartRealStreamMsg)(
	void* userParam,
	CWALK_NET_HD streamHD,
	const CWALKSDKError streamResult
	);

/// 录像回放消息回调
/// @param[in] userParam	用户数据
/// @param[in] streamHD		回放句柄
/// @param[in] flag			-1   出错，断流等
///							0    数据回调结束
///							1   数据回调开始
///							2   该录像是非私有流（未使用）
///							3   该录像是私有流（未使用）
///							4   刷新数据，一般是调用CWALK_NET_SetPlaybackStreamPos后会收到
///							5   断流重开，发生了断流并重新开流
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStreamMsg)(
	void* userParam,
	CWALK_NET_HD streamHD,
	INT flag
	);

/// 启动实时视频流
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	streamHD	返回实时流播放句柄
///	@param[in]	avPath		AV对象名, 例如"av/dcam/1", dcs可在末尾用#传入媒体参数, 包括video、audio、profile, 具体取值：
///							video：H264  H265  MPEG4；audio：AAC G711 G726 G729；profile：CIF  D1  HD 0 1 2
///							三种媒体参数任意组合，无先后顺序，例如 #D1、#H264#HD#G711、#G711#HD#H264
///							profile中的0、1、2、...代表主子码流
/// @param[in]	fnOnRealData 实时播放数据回调函数
/// @param[in]	fnRobbed	抢占通知回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartStream(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	void* userParam
	);

/// 启动实时视频流（异步连接），dcs+中接口同CWALK_NET_StartStream一样
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	streamHD	返回实时流播放句柄
///	@param[in]	avPath		AV对象名
/// @param[in]	fnOnRealData 实时播放数据回调函数
/// @param[in]	fnRobbed	抢占通知回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartStreamByAsync(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* streamHD,
	const TCHAR* avPath,
	Callback_OnStreamData fnData,
	CallBack_OnStreamRobbed fnRobbed,
	CallBack_OnStartRealStreamMsg fnMsg,
	void* userParam
	);

/// 停止实时视频流
///	@param[in]	streamHD	实时视频句柄,由CWALK_NET_StartStream()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopStream(
	CWALK_NET_HD streamHD
	);

/// 实时视频请求I帧
///	@param[in]	streamHD	实时视频句柄,由CWALK_NET_StartStream()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StreamRequestIFrame(
	CWALK_NET_HD streamHD
	);

/// 打开对讲通道
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	audioHD		返回对讲句柄
///	@param[in]	audioPath	对讲通道名
///							dcs+中参数格式同CWALK_NET_StartStream
/// @param[in]	fnData		音频数据回调函数
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartAudio(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* audioHD,
	const TCHAR* audioPath,
	Callback_OnStreamData fnData,
	void* userParam
	);
/// 打开对讲通道
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	audioHD		返回对讲句柄
///	@param[in]	audioPath	对讲通道名
///							dcs中参数格式同CWALK_NET_StartStream
/// @param[in]  mode        语言通道模式
/// @param[in]	fnData		音频数据回调函数，mode = Talk时可以为空
/// @param[in]	userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartAudioEx(
	CWALK_NET_HD userHD,
	CWALK_NET_HD* audioHD,
	CWALKAudioMode mode,
	const TCHAR* audioPath,
	Callback_OnStreamData fnData,
	void* userParam
	);


/// 输入音频数据
/// 注：所有间频数据均为顺序采样，格式为PCM帧
/// @param[in]	audioHD		对讲句柄,由CWALK_NET_StartAudio()获得
/// @param[in]  channels	通道数
/// @param[in]  bitsPerSample	每样本位数
/// @param[in]  channels	每秒样本数
/// @param[in]	buf			音频数据
/// @param[in]	size		音频数据长度
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InputAudioData(
	CWALK_NET_HD audioHD,
	INT channels,
	INT bitsPerSample,
	INT samplesPerSec,
	BYTE* buf, 
	INT size
	);

/// 关闭对讲通道
/// @param[in]	audioHD		对讲句柄,由CWALK_NET_StartAudio()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopAudio(
	CWALK_NET_HD audioHD
	);

/// 点播录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 点播录像，增加全速下载录像时用带缓存的播放接口
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 点播录像，点播集群存储的录像时进行CRC校验
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 停止录像回放
/// @param[in] streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStream()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStream(
	CWALK_NET_HD streamHD
	);

/// 获取录像播放进度
/// @param[in]	streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStream()得到
/// @param[out] pos			返回当前的播放进度,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPlaybackStreamPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// 设置录像播放位置
/// @param[in]	streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStream()得到
/// @param[in] pos			要设置的播放位置,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackStreamPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// 点播录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 自动点播录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 停止录像回放
/// @param[in] streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStreamAuto()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStreamAuto(
	CWALK_NET_HD streamHD
	);

/// 停止录像回放
/// @param[in] streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStreamExp()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopPlaybackStreamExp(
	CWALK_NET_HD streamHD
	);

/// 获取录像播放进度，dcs+中实现同CWALK_NET_GetPlaybackStreamPos一样
/// @param[in]	streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStreamExp()得到
/// @param[out] pos			返回当前的播放进度,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPlaybackStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// 设置录像播放位置
/// @param[in]	streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStreamExp()得到
/// @param[in] pos			要设置的播放位置,相对于播放开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// @param[in]	streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStream()得到
/// @param[in]  bPause		true 暂停流传输； false 取消暂停，继续流传输
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetVodPause( 
	CWALK_NET_HD streamHD, 
	bool bPause 
	); //此接口DCS不支持

/// 下载录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像下载的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 录像下载（支持断点续传）
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] beginThisPackage	开始索引（断点续传）
/// @param[in] beginNextPackage	结束索引 -1表示无效，默认使用开始索引即可。
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 停止录像下载
/// @param[in] streamHD	录像下载句柄,由CWALK_NET_StartDownloadStream()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStream(
	CWALK_NET_HD streamHD
	);

/// 暂停/继续录像下载 
/// @param[in] streamHD	 录像下载的句柄 
/// @param[in] bPause	 暂停/继续录像下载，true暂停，false继续录像下载 
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadPause( 
	CWALK_NET_HD streamHD, 
	bool bPause 
	);

/// 获取录像下载进度，dcs+中实现同CWALK_NET_GetPlaybackStreamPos一样
/// @param[in]	streamHD	录像下载句柄,由CWALK_NET_StartDownloadStream()得到
/// @param[out] pos			返回当前的下载进度,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetDownloadStreamPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// 设置录像下载位置
/// @param[in]	streamHD	录像下载句柄,由CWALK_NET_StartDownloadStream()得到
/// @param[in] pos			要设置的下载位置,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadStreamPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);

/// 下载录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像下载的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 停止录像下载
/// @param[in] streamHD	录像下载句柄,由CWALK_NET_StartDownloadStreamExp()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStreamExp(
	CWALK_NET_HD streamHD
	);

/// 自动下载录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像下载的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 停止录像下载
/// @param[in] streamHD	录像下载句柄,由CWALK_NET_StartDownloadStreamAuto()得到
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopDownloadStreamAuto(
	CWALK_NET_HD streamHD
	);

/// 录像下载（支持断点续传）
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] beginThisPackage	开始索引（断点续传）
/// @param[in] beginNextPackage	结束索引 -1表示无效，默认使用开始索引即可。
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @param[in] type		osd类型
/// @param[in] osdInfo	水印信息，CWALKOSDText、CWALKOSDLine和CWALKOSDRect类型中的一种
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 下载录像
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像下载的句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @param[in] type			osd类型
/// @param[in] osdInfo		水印信息，CWALKOSDText、CWALKOSDLine和CWALKOSDRect类型中的一种
/// @return
/// 注：10.2sdk 此接口无效 都通过CWALK_FILE_OpenWritbaleFile接口创建 或者 CWALK_FILE_WriteOsdInfo接口写入osd信息
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 获取录像下载进度，dcs+中实现同CWALK_NET_GetPlaybackStreamPos一样
/// @param[in]	streamHD	录像下载句柄,由CWALK_NET_StartDownloadStreamExp()得到
/// @param[out] pos			返回当前的下载进度,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetDownloadStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64* pos
	);

/// 设置录像下载位置
/// @param[in]	streamHD	录像下载句柄,由CWALK_NET_StartDownloadStreamExp()得到
/// @param[in] pos			要设置的下载位置,相对于当前时间段开始时间的毫秒数
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetDownloadStreamExpPos(
	CWALK_NET_HD streamHD,
	INT64 pos
	);


/// 设置回放速度
/// @param[in]	speed		0代表暂停，其它取值1.0、2.0、4.0、8.0、16.0、32.0、0.5、0.25、0.125、0.0625
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackSpeed(
	CWALK_NET_HD streamHD,
	double speed
	);

/// 向CWALKDB中写日志
///		
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	logType		日志类型
/// @param[in]	info		日志信息，JSON格式字符串，可由CWALK_NET_InfoHelperXXX系列函数帮助生成
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InsertLog(
	CWALK_NET_HD userHD,
	CWALKNetLogType logType,
	const TCHAR* info
	);

/// CWALKDB日志查询结果回调函数
///		
/// @param[in]	logType		日志类型
/// @param[in]	logInfo		查询结果数据
/// @param[in]  userParam	用户数据
/// @return
///	-	TURE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnQueryLog)(
	CWALKNetLogType logType,
	const TCHAR* logInfo,
	void* userParam 
	);

/// 查询CWALKDB日志
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	logType		查询类型
/// @param[out]	isEnd		查询是否结束，TRUE－后面没有数据，FALSE－后面还有数据
/// @param[in]	queryInfo	查询条件，JSON格式字符串，可由CWALK_NET_InfoHelperXXX系列函数帮助生成
/// @param[in]  fnQueryLog	查询结果回调函数指针
/// @param[in]  userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryLog(
	CWALK_NET_HD userHD,
	CWALKNetLogType logType,
	BOOL* isEnd /*=NULL*/,
	const TCHAR* queryInfo,
	CallBack_OnQueryLog fnQueryLog,
	void* userParam/*= NULL*/
	);

/// 标记名称回调函数
/// @param[in]	tagName		标记名称
/// @param[in]  userParam	用户数据
typedef void (CWALK_SDK_CALLBACK *CallBack_OnGetTagNames)(
	const TCHAR* tagName,
	void* userParam 
	);

/// 获得所有标记名称
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	nameCount	返回标记名称个数
/// @param[in]	fnOnNames	标记名称回调函数指针
/// @param[in]  userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetTagNames(
	CWALK_NET_HD userHD,
	INT* nameCount /*= NULL*/,
	CallBack_OnGetTagNames fnOnNames,
	void* userParam /*= NULL*/
	);

/// 修改标记名称
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	oldTagName	旧标记名称,必须是CWALK_NET_GetTagNames()中获得的名称
///	@param[in]	newTagName	新标记名称
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ModifyTagName(
	CWALK_NET_HD userHD,
	const TCHAR* oldTagName,
	const TCHAR* newTagName
	);

/// 添加帧标记
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	tagName		标记名称,必须是CWALK_NET_GetTagNames()中获得的名称
///	@param[in]	tagTime		标记时间,默认为服务器系统时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///	@param[in]	channelName	通道名称,如:"av/dcam/1"
///	@param[in]	description	标记描述信息
///	@param[in]	tagType		标记类型0 - 自动;1 - 手动;其它 - 未使用
///	@param[in]	level		标记级别,取值[1-5],1-不重要;2-不太重要;3-一般;4-重要;5-很重要
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_AddTag(
	CWALK_NET_HD userHD,
	const TCHAR* tagName,
	const TCHAR* tagTime /*= NULL*/,
	const TCHAR* channelName,
	const TCHAR* description /*= NULL*/,
	INT tagType,
	INT level
	);

/// 帧标记查询回调函数
/// @param[in]	tagInfo		帧标记信息, JSON格式字符串,可以通过CWALK_NET_InfoParseXXXX()系列函数来解析
///		
///		标记信息中属性如下：
///			id				本条记录在数据库中的索引ID
///			tagName			标记名称
///			tagTime			标记时间
///			channelName		通道名称
///			description		标记描述信息
///			tagType			标记类型 0 - 自动;1 - 手动;其它 - 未使用
///			level			标记级别,取值[1-5],1-不重要;2-不太重要;3-一般;4-重要;5-很重要
///			createUser		标记创建者
///			createTime		标记创建时间
///			modifyUser		最后一次修改者
///			modifyTime		最后一次修改时间
///
/// @param[in]  userParam	用户数据
/// @return
///	-	TURE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_OnQueryTag)(
	const TCHAR* tagInfo,
	void* userParam
	);

/// 查询帧标记
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	condition	查询条件,JSON格式字符串，可由CWALK_NET_InfoHelperXXX系列函数帮助生成
///
///		查询条件为如下一种或多种的组合：
///			maxCount		[INT]	 返回数据的最大条数，默认值：1000，最大值：2000
///			startPos		[INT]	 数据返回起始位置，默认值：0
///			tagNames		[string] 标记名称，必须是CWALK_NET_GetTagNames()得到的名称，支持多个，多个用“;”隔开，如："打架标记;车祸标记;报警标记"
///			channelNames	[string] 通道名称，支持多个，支持模糊查询，多个用“;”隔开，如："av/dcam/1;av/dcam/2;av/dcam/3"
///			beginTagTime	[string] 开始标记时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endTagTime		[string] 结束标记时间（不含）
///			beginCreateTime [string] 开始创建时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endCreateTime	[string] 结束创建时间（不含）
///			beginModifyTime [string] 开始修改时间，格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
///			endModifyTime	[string] 结束修改时间（不含）
///			tagType			[INT]	 标记类型 0 - 自动;1 - 手动;其它 - 未使用
///			level			[INT]	 标记级别,取值[1-5],1-不重要;2-不太重要;3-一般;4-重要;5-很重要
///			createUser		[string] 创建用户，注：不支持模糊查询
///			modifyUser		[string] 最后一次修改用户，注：不支持模糊查询
///			description		[string] 描述信息，支持关键字模糊查询
///
/// @param[out] recordCount	服务器返回的数据条数
/// @param[out]	isEnd		是否已查询到最后, TRUE - 已经查询到最后；FALSE - 未查询到最后，后面还有符合查询条件的数据未返回
/// @param[out]	fnOnQueryTag帧标记查询回调函数指针
/// @param[in]  userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryTag(
	CWALK_NET_HD userHD,
	const TCHAR* condition,
	INT* recordCount /*= NULL*/,
	BOOL* isEnd /*= NULL*/,
	CallBack_OnQueryTag fnOnQueryTag /*= NULL*/, 
	void* userParam /*= NULL*/
	);

/// 删除帧标记
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	tagIdArray	帧标记ID数组
/// @param[in]	arrayLen	数组长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_DeleteTags(
	CWALK_NET_HD userHD,
	INT64 tagIdArray[],
	INT arrayLen
	);

/// 修改帧标记
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	tagId		帧标记ID
/// @param[in]	tagName		修改后的帧标记名称，必须是CWALK_NET_GetTagNames()得到的名称
/// @param[in]	description 修改后的描述
/// @param[in]	Level		修改后的级别	
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ModifyTag(
	CWALK_NET_HD userHD,
	INT64 tagId,
	const TCHAR* tagName /*= NULL*/,
	const TCHAR* description /*= NULL*/,
	INT level
	);

/// 获取云台信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		摄像机名称
/// @param[out]	bufInfo		云台信息，可以通过CWALK_NET_InfoParseKeyValue()来解析
/// @param[in]	len			bufInfo的长度
/// @param[out]	realLen		返回数据的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetPtzInfo(
	CWALK_NET_HD userHD,
	const TCHAR* avPaht,
	void* bufInfo,
	INT len,
	INT* realLen
	);

/// 设置云台信息
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	avPath		摄像机名称
/// @param[in]	ptzinfo		云台信息
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPtzInfo(
	CWALK_NET_HD userHD,
	const TCHAR* avPaht,
	CWALKNetPTZPos ptzinfo
	);

/// 透传cmservice指令，dcs专用
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	funcPost	http post的接口名，例如GetServiceStatus
/// @param[in]	msgPost		post的msg，例如{"GetServiceStatus":{"serviceType":"streamingservice"}}
/// @param[out]	outResult   输出结果,json格式
/// @param[in]  len			outResult的大小
/// @param[out] realLen		返回实际信息的长度
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_CmsHttpPost(
	CWALK_NET_HD userHD,
	const TCHAR* funcPost,
	const TCHAR* msgPost,
	void* outResult,
	INT len,
	INT* realLen
	);

/// 对象解析帮助函数,用于解析 CWALK_NET_GetOrganization() 返回的组织结构信息
/// @param[in]  info		组织结构信息
/// @param[in]  type		组织结构类型，1 - 表示组织结构节点；2 - 表示dcs节点；其它  - 未使用
/// @param[in]  index		节点索引
/// @param[in]  key			节点属性
/// @param[out] valueBuf	存放节点的属性，内存空间有使用者分配
/// @param[in]  len			valueBuf的大小
/// @param[out] realLen		返回属性的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_ParseOrganizationInfo(
	const TCHAR* info,
	INT type,
	INT index, 
	const TCHAR* key,
	void* valueBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 对象解析帮助函数,用于解析Key-Value格式JSON字符串
/// @param[in]	objInfo		JSON格式字符串
/// @param[in]	key			要解析的信息
/// @param[out]	valueBuf	存放key所对应的值,内存由使用者分配
/// @param[in]	len			valueBuf的大小
/// @param[out] realLen		返回属性的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyValue(
	const TCHAR* objInfo,
	const TCHAR* key,
	void* valueBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 对象解析帮助函数,用于获取Key-Value格式JSON字符串的子集Key集合
/// @param[in]	objInfo		JSON格式字符串
/// @param[out]	namesBuf	存放key集合信息，格式为key1,key2,key3等等
/// @param[in]	len			namesBuf的大小
/// @param[out]	realLen		返回属性的实际长度
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyGetMemberNames(
	const TCHAR* objInfo,
	void* namesBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 对象解析帮助函数,用于获取Key-Value格式JSON字符串子集数组数量
/// @param[in]	objInfo		JSON格式字符串
/// @param[in]	key			JSON数组标识名称信息
/// @param[out]	count		子JSON数组的个数
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyArrayValueCount(
	const TCHAR* objInfo,
	const TCHAR* key,
	INT* count
	);

/// 对象解析帮助函数,用于获取Key-Value格式JSON字符串子集数组指定索引的JSON串
/// @param[in]	index		子JSON串索引
/// @param[in]	objInfo		JSON格式字符串
/// @param[in]	key			要解析的信息
/// @param[out]	objBuf		存放子JSON串,内存由使用者分配
/// @param[in]	len			objBuf的大小
/// @param[out] realLen		返回属性的实际长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseKeyIndexArrayValue(
	INT index,
	const TCHAR* objInfo,
	const TCHAR* key,
	void* objBuf,
	INT len,
	INT* realLen /*= NULL*/
	);

/// 对象解析帮助函数,用于解析Key-Value格式JSON字符串
/// @param[in]	objInfo		JSON格式字符串
/// @param[in]	key			要解析的信息
/// @param[out]	value		存放key所对应的值
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoParseIntKeyValue(
	const TCHAR* objInfo,
	const TCHAR* key,
	INT* value
	);

/// 创建Key-Value格式辅助函数,创建一个Key-Value格式JSON字符串生成器
/// @param[out]	helpHD		返回helpHD, 注：用完之后,必须使用CWALK_NET_InfoHelperRelease()释放
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperCreate(
	CWALK_HELP_HD* helpHD
	);

/// 对象信息生成帮助函数,添加key-value到对象信息
/// @param[in]	helpHD		辅助函数集句柄,由CWALK_NET_InfoHelperCreate()获得
/// @param[in]	key			对象属性键
/// @param[in]	value		对象属性值
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperAddKeyValue(
	CWALK_HELP_HD helpHD,
	const TCHAR* key,
	const TCHAR* value
	);

/// 对象信息生成帮助函数,添加key-value到对象信息
/// @param[in]	helpHD		辅助函数集句柄,由CWALK_NET_InfoHelperCreate()获得
/// @param[in]	key			对象属性键
/// @param[in]	value		对象属性值
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperAddIntKeyValue(
	CWALK_HELP_HD helpHD,
	const TCHAR* key,
	INT value
	);

/// 对象信息生成帮助函数,得到缓存区中的数据
/// @param[in]	helpHD		辅助函数集句柄,由CWALK_NET_InfoHelperCreate()获得
/// @param[out] buf			缓存区地址
///								注：一但调用CWALK_NET_InfoHelperRelease()之后,
///								所有的返回数据全部失效,建议把得到的数据进行拷贝处理
/// @param[out]	bufLen		缓存区长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_InfoHelperGetData(
	CWALK_HELP_HD helpHD,
	LPCTSTR* buf,
	INT* bufLen
	);

/// 对象信息生成帮助函数,释放资源
/// @param[in]	helpHD		辅助函数集句柄,由CWALK_NET_InfoHelperCreate()获得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD	CWALK_NET_InfoHelperRelease(
	CWALK_HELP_HD helpHD
	);

/// slice去头 测试使用
/// @param[in]	srcData		源流数据
/// @param[in]	srcLen		源流数据长度
/// @param[out]	decData		去头后流数据
/// @param[out]	decLen		去头后源流数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD	CWALK_NET_RemoveSliceHead(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen);

/// slice去头,并解析参数 测试使用
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
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_RemoveSliceHeadWithParam(
	void *srcData,
	INT srcLen,
	void *decData,
	INT *decLen,
	INT *streamType,
	INT *isIFrame,
	INT64 *pts);


/// 设置VOD播放模式
/// @param[in] streamHD	录像回放句柄,由CWALK_NET_StartPlaybackStream()得到
/// @param[in] mode	模式，>0:正序播放 <0:倒序播放 ==0:缺省模式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetPlaybackMode(
	CWALK_NET_HD streamHD,
	INT32 mode
	);

/// 获取服务器的平台类型
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out]	platType	输出服务器的平台类型
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetServerPlatType(
	CWALK_NET_HD userHD,
	CWALKNetSvrPlatType *platType);

/// 统计在线数接口 仅测试使用
///	@param[in]	loginHD			登录句柄,由CWALK_NET_Login()获得
/// @param[in]	camCount		摄像机总数
/// @param[in]	onlineCount		在线摄像机数
/// @return
///	-	TRUE	成功
///	-	其它	失败,错误码
CWALK_SDK_API BOOL CWALK_SDK_METHOD CWALK_NET_RefreshAllCamStatusCount(CWALK_NET_HD loginHD, UINT &camCount , UINT &onlineCount);

///	获取用户登录错误信息	by cpw 2016-11-16 14:21
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	userName	登录用户名
///	@param[out]	times		错误剩余次数
///	@param[out]	locked		解锁剩余时间  单位：s
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetUserErrorInfo(
	const TCHAR* ipOrHost,
	INT port,
	const TCHAR* userName,
	INT& times,
	INT64& locked
	);

///	解锁用户
/// @param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	ipOrHost	DCS服务器的ip或dns
///	@param[in]	port		DCS服务器的服务端口
///	@param[in]	userName	要解锁的用户
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_UnlockedUser(
	CWALK_NET_HD* userHD,
	const TCHAR* ipOrHost, 
	INT port,
	const TCHAR* userName
	);


/// 列举录像时间段
/// @param[in] userParam	用户数据
/// @param[in] userHD		登录句柄
/// @param[in] avPath		摄像机通道名称
/// @param[in] beginTime	时间段开始时间,格式："2012-01-01 13:20:00.000"
/// @param[in] endTime		时间段结束时间（不含）
/// @param[in] storageAddr	存储地址，录像点播、下载时用到
/// @return
///	-	TURE		断续下一次回调
///	-	FALSE		结束回调
typedef BOOL (CWALK_SDK_CALLBACK *CallBack_QueryRecordSAddr)(
	void* userParam,
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	const TCHAR* beginTime,
	const TCHAR* endTime, 
	const TCHAR* storageAddr
	);

/// 查询录像，回调函数带存储地址
/// 注: 非法录像时间段会被过滤掉,错误信息记录到日志中
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[in] avPath		摄像机通道名称
/// @param[in] vodType		0-服务器录像, 非0设备录像
/// @param[in] beginTime	起始时间, 格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] fnOnQueryRecords	回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_QueryRecordSAddr(
	CWALK_NET_HD userHD,
	const TCHAR* avPath,
	INT16 vodType,
	const TCHAR* beginTime,
	const TCHAR* endTime,
	CallBack_QueryRecordSAddr fnCB,
	void* userParam /*= NULL*/
	);

/// 点播录像，参数带存储地址
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像回放的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] storageAddr	存储地址
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 下载录像，参数带存储地址
/// @param[in] userHD		登录句柄,由CWALK_NET_Login()获得
/// @param[out] streamHD	得到录像下载的句柄
/// @param[in] avPath		摄像机通道名称, dcs中参数格式同CWALK_NET_StartStream
/// @param[in] vodType		0 - 服务器录像, 非0 - 录像所在的层数,最大值为256
/// @param[in] beginTime	开始时间,格式："2012-01-01 13:20:00.000" 或 "20120101132000000"
/// @param[in] endTime		结束时间（不含）
/// @param[in] storageAddr	存储地址
/// @param[in] fnData		数据流回调函数
/// @param[in] fnRobbed		抢占回调函数
/// @param[in] fnMsg		录像消息回调函数
/// @param[in] userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
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

/// 获取分组，10.2支持
/// @param[in] userHd		登录句柄,由CWALK_NET_Login()获得
/// @param[out] data		数据缓存，由调用者分配内存，被调者填充分组数据(json数组)
/// @param[in/out] bufLen	数据缓存大小，由调用者指定，当小于数据大小时，被调者将其改为所需的大小。
/// @param[in] bVirtualGroup	 是否是业务分组
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_ListGroupWithCount(CWALK_NET_HD userHd,TCHAR* const data, INT32* const bufLen,BOOL bVirtualGroup);

/// 分页获取分组下的摄像机，10.2支持
/// @param[in] userHd		登录句柄,由CWALK_NET_Login()获得
/// @param[out] data		数据缓存，由调用者分配内存，被调者填充摄像机数据(json数组，编码格式为 小字节序的Unicode)
/// @param[in/out] bufLen	数据缓存大小，由调用者指定，当小于数据大小时，被调者将其改为所需的大小。
/// @param[in] bVirtualGroup	 是否是业务分组
/// @param[in] groupId	 	分组id
/// @param[in] pageSize	 	每页大小
/// @param[in] pageIndex	页码，从0开始
/// @param[in] sort	 		分页排序方式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_ListCamerasByPage(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup, const TCHAR * groupId,INT32 pageSize,INT32 pageIndex,CWALKCameraSort sort);


/// 模糊搜索摄像机并返回匹配度最高的前1000条，10.2支持
/// @param[in] userHd		登录句柄,由CWALK_NET_Login()获得
/// @param[out] data		数据缓存，由调用者分配内存，被调者填充摄像机数据(json数组)
/// @param[in/out] bufLen	数据缓存大小，由调用者指定，当小于数据大小时，被调者将其改为所需的大小。
/// @param[in] bVirtualGroup	 是否是业务分组
/// @param[in] searchText	搜索字符串
/// @param[in] groupId      分组id。如果分组id不为空，则在该分组及其子分组下搜索
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_SearchCamerasLimited(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* searchText,const TCHAR* groupId);

/// 获取指定分组下指定摄像机所在页
/// @param[in] userHd		登录句柄,由CWALK_NET_Login()获得
/// @param[out] data		数据缓存，由调用者分配内存，被调者填充摄像机数据(json数组)
/// @param[in/out] bufLen	数据缓存大小，由调用者指定，当小于数据大小时，被调者将其改为所需的大小。
/// @param[in] bVirtualGroup	 是否是业务分组
/// @param[in] groupId	 	分组id
/// @param[in] cameraId	 	摄像机Id
/// @param[in] pageSize	 	每页大小
/// @param[out] pageIndex	页码，从0开始
/// @param[in] sort	 		分页排序方式
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_GetPageOfCamera(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* groupId,const TCHAR* cameraId,INT32 pageSize,INT* const pageIndex,CWALKCameraSort sort);

/// 获取指定的摄像机
/// @param[in] userHd		登录句柄,由CWALK_NET_Login()获得
/// @param[out] data		数据缓存，由调用者分配内存，被调者填充摄像机数据(json数组)
/// @param[in/out] bufLen	数据缓存大小，由调用者指定，当小于数据大小时，被调者将其改为所需的大小。
/// @param[in] bVirtualGroup	 是否是业务分组
/// @param[in] objNamesJsArr	摄像机objName组成的json数组
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET102_GetCamerasByObjName(CWALK_NET_HD userHd,TCHAR* const data,INT32* const bufLen,BOOL bVirtualGroup,const TCHAR* objNamesJsArr);


/// 图片数据回调函数,由CWALK_NET_StartRealtimeImage()调用
/// @param[in]	userParam	用户数据
///	@param[in]	imageHD		图片实时预览句柄
///	@param[in]  avPath		AV对象名
/// @param[in]	data		回调的json格式数据
/// @param[in]	dataLen		回调数据长度
typedef void (CWALK_SDK_CALLBACK *Callback_OnRealtimeImageData)(
	void* userParam,
	CWALK_NET_HD imageHD,
	const TCHAR* avPath,
	const void* data,
	INT dataLen
	);

/// 实时图片数据消息回调通知函数
/// @param[in]	userParam		用户数据
/// @param[in]	imageHD			图片实时预览句柄,由CWALK_NET_StartRealtimeImage()获得
/// @param[in]  code			消息码
///								2  - 打开成功
///								1  - 连接成功
///								-1 - 连接失败
///								-2 - 打开失败，avpath无效
///								-3 - 被服务端关闭
typedef void (CWALK_SDK_CALLBACK *CallBack_OnStartRealImageMsg)(
	void* userParam,
	CWALK_NET_HD imageHD,
	const int code
	);

/// 开启实时图片预览
/// @param[in]  userHd		登录句柄,由CWALK_NET_Login()获得
///	@param[out] imageHd		图片预览句柄
///	@param[in]  avPath		AV对象名
///	@param[in]  fnData		图片数据回调函数
///	@param[in]  fnMsg		预览状态回调函数
///	@param[in]  userParam	用户数据
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StartRealtimeImage(
	CWALK_NET_HD userHD, 
	CWALK_NET_HD* imageHD, 
	const TCHAR* avPath,
	Callback_OnRealtimeImageData fnData,
	CallBack_OnStartRealImageMsg fnMsg,
	void* userParam
	);

/// 关闭实时图片预览
///	@param[in] imageHd		图片预览句柄，由CWALK_NET_StartRealtimeImage()所得
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_StopRealtimeImage(
	CWALK_NET_HD imageHD
	);

/// 获得与备用服务器的连接状态(指下级或车站)
///	@param[in]	userHD		登录句柄,由CWALK_NET_Login()获得
///	@param[in]	Ip			服务的IP
///	@param[in]	port		服务的端口
/// @param[out]	connect		连接状态，TRUE-正常状态，FALSE-断线状态
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_IsConnectedBackup(
	CWALK_NET_HD userHD, 
	const TCHAR* Ip,
	const INT	 port,
	BOOL* connect
	);

/// 得到备用服务的IP和Port
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[out] Ip			备用服务器的IP，内存由使用者分配
/// @param[in]  len			infoBuf的大小
/// @param[out] realLen		返回实际信息的长度
/// @param[out] port		备用服务的端口
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_GetBackupInfo(
	CWALK_NET_HD userHD,
	void* ip,
	INT len,
	INT* realLen,
	INT* port
	);

/// 电视墙控制接口
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	cmd			电视墙操作命令码 ref CWALKNetTVWallCommand
/// @param[in]	param		操作命令参数结构体
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_TVWallControl(
	CWALK_NET_HD userHD, 
	const CWALKNetTVWallCommand cmd,
	CWALKNetTVWallParam* param
	);


/// 拼控(多路解码器)设备控制接口
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	decPath 	拼控设备编号
/// @param[in]	param		操作命令参数结构体
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_MatrixDevControl(
	CWALK_NET_HD userHD,
	const TCHAR* decPath,
	CWALKNetMatrixCtrlParam* param
);

/// 简单的数据加密方法
/// @param[in]	secretKey	加密密钥
/// @param[in]	srcData		源数据
/// @param[out] result		加密后数据
/// @param[out] resultLen	加密后数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SimpleEncyptedData(
	const TCHAR* secretKey, 
	const TCHAR* srcData, 
	TCHAR* result, 
	INT* resultLen
	);

/// 简单的数据解密方法
/// @param[in]	secretKey	解密密钥
/// @param[in]	srcData		密文
/// @param[out] result		解密后数据
/// @param[out] resultLen	解密后数据长度
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SimpleDecodeData(
	const TCHAR* secretKey, 
	const TCHAR* srcData, 
	TCHAR* result, 
	INT* resultLen
	);

/// 设置摄像机经纬度坐标
/// @param[in]	userHD 		登录句柄,由CWALK_NET_Login()获得
/// @param[in]	strGroupId 	所属组织机构编号
/// @param[in]	avPath 		相机编号
/// @param[in]	longitude 	经度值
/// @param[in]	latitude 	纬度值
/// @return
///	-	CWALKSDK_OK	成功
///	-	其它		失败,错误码
CWALK_SDK_API CWALKSDKError CWALK_SDK_METHOD CWALK_NET_SetCamerasCoordinate(
	CWALK_NET_HD userHD, 
	const TCHAR* strGroupId, 
	const TCHAR* avPath, 
	const TCHAR* longitude, 
	const TCHAR* latitude
	);

#endif	/// _cwalk_netsdk_h_
