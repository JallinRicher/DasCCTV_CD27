/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: CWALKSDKErrors.h
///         description:  DCS SDK错误定义
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

///< 返回错误码，-20000以外的为DCSSdk错误码，-20000以内的为内核错误码

#define CWALKSDK_OK							0		///< 操作成功完成
#define CWALKSDK_ERROR							-1		///< 未分类错误
#define CWALKSDK_ERR_NOT_SUPPORT				-20001	///< 此功能不支持
#define CWALKSDK_ERR_NOT_IMPL					-20002	///< 功能暂未实现
#define CWALKSDK_ERR_NOT_INIT					-20003	///< 未初始化
#define CWALKSDK_ERR_NOT_ENOUGH_MEM			-20005	///< 内存分配失败
#define CWALKSDK_ERR_NOT_ENOUGH_ID				-20004	///< 打开太多句柄，系统资源不足
#define CWALKSDK_ERR_INVALID_ID				-20006	///< 无效句柄，可能已经关闭
#define CWALKSDK_ERR_INVALID_NAME				-20007	///< 无效对象名，没有这个对象
#define CWALKSDK_ERR_INVALID_PARARM			-20008	///< 无效参数
#define CWALKSDK_FILE_NOFIND					-20009	///< 未打开文件或这文件打开失败
#define CWALKSDK_ISFINDING						-20010	///< 正在查找文件
#define CWALKSDK_NOMOREFILE					-20011	///< 查找文件时没有更多的文件
#define CWALKSDK_FILE_EXCEPTION				-20012	///< 查找文件时异常
#define CWALKSDK_ERR_URLPATH					-20013	///< 文件Url全路径错误
#define CWALKSDK_ERR_EXISTKEY					-20014	///< 元素已存在ESIST
#define CWALKSDK_ERR_NO_OBJECT					-20015	///< 查找对象不存在
#define CWALKSDK_ERR_OSD_SETTEXT				-20016	///< OSD叠加文本错误
#define CWALKSDK_ERR_OSD_TYPE					-20017	///< OSD类型错误
#define CWALKSDK_ERR_OSD_SHOW					-20018	///< OSD显示错误
#define CWALKSDK_ERR_DEFAULTPORT				-20019	///< 获取默认端口错误
#define CWALKSDK_ERROR_LOGIN					-20020	///< 登陆失败
#define CWALKSDK_NOMOREDATA					-20021	///< 没有更多查讯数据
#define CWALKSDK_ERR_SET_PASSWORD				-20022	///< 设置密码错误
#define CWALKSDK_ERR_NO_KEY					-20023	///< 设置键值不存在
#define CWALKSDK_ERR_NO_VALUE					-20024	///< 对应的键没有值
#define CWALKSDK_ERR_FUNCTION_NOT_IMPLEMENTED	-20025  ///< 功能未实现
#define CWALKSDK_ERR_CREATE_HANDLE				-20026  ///< 获得句柄为空
#define CWALKSDK_ERR_EVENT_RESUBSCRIBE			-20027  ///< 事件重复订阅
#define CWALKSDK_ERR_END_OF_FILE				-20028  ///< 读取文件完成
#define CWALKSDK_ERR_NO_HANDLE					-20029  ///< 句柄不存在
#define CWALKSDK_ERR_NULL_OBJECT				-20030  ///< 对象指针为空
#define CWALKSDK_ERR_FIRST_NOT_IFRAME			-20031  ///< 接收到的第一帧不是关键侦
#define CWALKSDK_ERR_UNSUPPORTED_PLATFORM		-20032  ///< 不支持当前平台
#define CWALKSDK_ERR_BUFFER_TOO_SMALL			-20033	///< 缓冲区太小
#define CWALKSDK_ERR_UNKNOWN_SERVICE			-20034  ///< 不支持的服务器类型
#define CWALKSDK_ERR_NO_PRIVILEGE			    -20035  ///< 没有权限
#define CWALKSDK_ERR_VIEW_NUM		            -20036  ///< 超过最大支持画面数
#define CWALKSDK_ERR_DISK_FULL					-20037  ///< 磁盘空间不足
#define CWALKSDK_ERR_INVALID_MEM				-20038  ///< 转码时内存错误（转码库返回）
#define CWALKSDK_ERR_ENCODER_OPEN				-20039  ///< 打开编码器错误（转码库返回）
#define CWALKSDK_ERR_SP_QUERY_SEGMENT			-20040	///< 未查询到该分段录像
#define CWALKSDK_ERR_NO_PVM_ADD			    -20041	///< 未获取到PVM地址
#define CWALKSDK_ERR_ES_UNAVAILABLE 			-20042	///< 日志服务不可用
#define CWALKSDK_ERR_AVCF_ERROR 			    -20043	///< AVCF出错
#define CWALKSDK_FILE_ISOPEN					-20044  ///< 文件已经打开
#define CWALKSDK_FILE_ISTRANSMIT				-20045  ///< 文件已在传输
#define CWALKSDK_ERR_ISHTTPS					-20046  ///< 仅支持使用https协议通信


#define CWALKSDK_ERR_PLAY_HD					-21001 ///< 获取窗口坐标失败
#define CWALKSDK_ERR_PLAY_NEED_SLICES			-21002 ///< 播放缓冲区需要数据
#define CWALKSDK_ERR_PLAY_FULL_SILCES			-21003 ///< 接收缓冲区已满
#define CWALKSDK_ERR_PLAY_INPUT_SLICES_CB		-21004 ///< 输入多个slice方式下回调函数没有设置
#define CWALKSDK_ERR_PLAY_INVALID_CMD			-21005 ///< 无效的播放请求
#define CWALKSDK_ERR_PLAY_INVALID_CMD_MATCH	-21007 ///< 实时播放时只支持暂停和继续播放命令
#define CWALKSDK_ERR_PLAY_INVALID_SPEED		-21006 ///< 错误的播放速度
#define CWALKSDK_ERR_PLAY_INVALID_CB_MODE		-21007 ///< 实时播放时不能采用回调方式输入Slice数据
#define CWALKSDK_ERR_PLAY_IS_RELEASED			-21008 ///< 资源已经释放
#define CWALKSDK_ERR_PLAY_THREAD_STOP			-21009 ///< 解码线程已经停止
#define CWALKSDK_ERR_PLAY_REOPEN				-21010 ///< 音频资源重复打开
#define CWALKSDK_ERR_PLAY_OPEN_AUDIO			-21011 ///< 打开音频设备失败
#define CWALKSDK_ERR_PLAY_START_AUDIO			-21012 ///< 开始采集音频失败
#define CWALKSDK_ERR_PLAY_STOP_AUDIO			-21013 ///< 停止采集音频失败
#define CWALKSDK_ERR_PLAY_VIDEO_INFO			-21014 ///< 视频信息获取失败
#define CWALKSDK_WARNING_PLAY_MAX_LOCALCACH	-21015 ///< 超过设置的本地缓存的最大警告值
#define CWALKSDK_WARNING_PLAY_MIN_LOCALCACH	-21016 ///< 小于设置的本地缓存的最小警告值
#define CWALKSDK_ERR_PLAY_PAUSE_CANNOT_SPEED	-21017 ///< 暂停时不能设置播放速度

///22000以上为日志服务器错误代码
#define CWALKSDK_ERR_LOG_UNKNOWTYPE			-22001 ///<	未定义的错误类型
#define CWALKSDK_ERR_LOG_DATA					-22002 ///<	数据查询结果不正确

///23000以上为SDK编解码库错误码
#define CWALKSDK_ERR_CODEC_NOTKEY			-23001	///< 不是关键帧I帧
#define CWALKSDK_ERR_CODEC_OPEN_DEC_FAIL	-23002	///< 打开解码器失败
#define CWALKSDK_ERR_CODEC_DEC_INPUT_FAIL	-23003	///< 数据送入编码器失败
#define CWALKSDK_ERR_CODEC_SNAPSHOT_KEYFRAME_FAIL	-23004	///< 解码并快照I帧失败

///100000以上为CMService错误代码
#define DCS_ERR_SS_NOT_AVAILABLE        	-101001 ///<	未分配StroageProxyService  
#define DCS_ERR_FS_NOT_AVAILABLE			-101002 ///<	未分配StreamingService  
#define DCS_ERR_PAU_NOT_AVAILABLE 		-101003 ///<	ACService不可用   
#define DCS_ERR_DEVICE_NOT_ATTACHE_PAU	-101004 ///<	ACService不可用(ACService不可用)   
#define DCS_ERR_USER_STREAM_OVERRAGE		-101005 ///<    超出用户流控限制
#define DCS_ERR_PLAT_STREAM_OVERRAGE		-101006 ///<    超出平台流控限制
#define DCS_ERR_INVALID_JOSN				-101007 ///<    非法的JSON字符串
#define DCS_ERR_PAU_SEND_FAILED			-101008 ///<	与ACService之间通信失败
#define DCS_ERR_MONITOR_LOCKED			-101030 ///<	监视器已经被锁定
#define DCS_ERR_MONITOR_CANNOT_CONTROL	-101031 ///<	监视器不能被控制
#define DCS_ERR_SESSION_NOT_FOUND 		-102001 ///<	会话无效（不存在）  
#define DCS_ERR_FS_STREAM_BROKEN			-102002 ///<	StreamingService流断线
#define DCS_ERR_NOT_LOCAL_MONITOR			-102003 ///<	非节点内部监视器
#define DCS_INF_MONITOR_LOCKED  			-102004 ///<	监视器被锁定
#define DCS_ERR_CHANNLE_DISABLED			-103001 ///<	通道不可用
#define DCS_ERR_PAU_DISABLED				-103002 ///<	ACService不可用
#define DCS_ERR_LOG_NOT_AVAILABLE			-103003 ///<	未分配日志服务
#define DCS_ERR_PAU_NOT_OPEN				-103004 ///<	与ACService服务OPEN失败
#define DCS_ERR_DCS_NOT_OPEN				-103005 ///<	与DCS服务OPEN失败
#define DCS_ERR_LOCALDB_UNINIT			-103006 ///<	本地数据库未初始化
#define DCS_ERR_LOCALDB_EXCEPTION			-103007 ///<	本地数据库异常
#define DCS_ERR_CHANNEL_RECORD_EXITS		-103008 ///<	通道已在录像
#define DCS_ERR_DCS_NOT_AVAILABLE			-103009 ///<	未分配DCS
#define DCS_ERR_AUDIOTALK_IN_USE			-103010 ///<	喊话通道被占用
#define DCS_ERR_DEVICE_NOT_EXIST			-103011 ///<	设备不存在
#define DCS_ERR_REQUEST_PATH_EXISTED		-103012 ///<	请求的路径已经存在
#define DCS_ERR_ROFS3S_NOT_AVAILABLE		-103013 ///<	无可用的rofs3s
#define DCS_ERR_PAU_DISCONNECT			-103014 ///<	ACService服务无法连接
#define DCS_ERR_RESOURCESHIELD			-103015 ///<	无资源权限(资源屏蔽)
#define DCS_ERR_SCAN_EXIST				-103016 ///<	键盘巡检已存在
#define DCS_ERR_MACRO_EXIST				-103017 ///<	键盘宏已存在
#define DCS_ERR_ORDER_CALL				-103018 ///<	调用次序错误
#define DCS_ERR_USER_DISABLED				-103019 ///<	用户被禁用
#define DCS_ERR_RECORD_REUSE				-103020 ///<	通道录像被复用



#endif
