#pragma once
#include <fstream>
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "cwalk_playsdk.h"
#include "cwalk_codecsdk.h"

#define INFOBUFFER_SIZE		256

struct UserInfo;
typedef CWALKSDKError ErrorNum;

class JSDCCTV
{
public:
	JSDCCTV(UserInfo DCSUserInfo);
	void InsertLog(LOGLEVEL Level, const char* const _Format, ...);
	static void CharToWChar(const char* Source, wchar_t* Destination);

	bool InitSDK();																										// ��ʼ��SDK
	bool Login();																										// ��¼������
	void Logout();																										// �ǳ�������
	void ReleaseSDK();																									// �ͷ�SDK
	bool IsInit();
	bool IsLogin();
	bool SetLogFile(const char* LogPath);

public:		/************************************* CCTV �ļ�����ģ�� *************************************/
	
	// �ļ�ģ���ʼ��
	bool InitFileSDK();

	// ý���ļ�������
	bool OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD);				// �򿪿ɶ��ļ�
	void CloseReadableFile(CWALK_FILE_HD ReadHD);										// �رտɶ��ļ�
	bool ReadSlice(CWALK_FILE_HD ReadHD, void** Data, int* Len);						// �ӿɶ��ļ��ж�ȡ���ݣ�������FreeFile�ͷ����ݣ������������Ϊһ��������slice
	void FreeFile(void* Ptr);															// �ͷ��ڴ�
	bool SetPlayMode(CWALK_FILE_HD ReadHD, int Mode);									// ���ò���ģʽ
	void GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode);									// ��ò���ģʽ

	// ý���ļ�д����
	bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);				// �򿪿�д�ļ�
	void CloseWritableFile(CWALK_FILE_HD WriteHD);										// �ر�д�ļ�����
	bool WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len);					// ����д���ļ�������data����Ϊһ��������slice������������Ļص��������

	// ý���ļ�λ�ÿ���
	void GetFileDuration(CWALK_FILE_HD ReadHD, DWORD* Len);								// ����ļ�������
	void GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len);									// ����ļ���ȡλ��
	bool SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len);									// �����ļ���ȡλ��

	// �õ�¼���ļ���һ֡������ʱ��
	void GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time);								// ���¼���һ֡������ʱ�䣬����ڸ������α�׼ʱ��ĺ�����
	void GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen);	// ���¼���һ֡������ʱ�䣬���ر�׼��ʽ��ʱ���ַ������ڴ��ɵ����߷���

	// ���ݸ�ʽת��
	void GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType);		// ��ȡͼ����Ϣ
	bool CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD);							// �������ݸ�ʽת����
	bool InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size);								// ��������
	void NextFrame(CWALK_FILE_HD ExtratorHD, void* pStream, int* Len);									// ��ȡ���ݣ��ɻ���������ͣ�
	void ReleaseExtractor(CWALK_FILE_HD ExtratorHD);													// �ͷ����ݸ�ʽת����

	// �����ļ�����
	bool OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, 
						 const TCHAR* Pool, const TCHAR* FilePath);										// �������ļ�
	void CloseOfflineFile(CWALK_FILE_HD ReadHD);														// �ر������ļ�
	bool StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, 
								Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, 
								void* UserParam);														// ���������ļ�����
	void StopOfflineFileStream(CWALK_FILE_HD ReadHD);													// ֹͣ���߻ط�
	void GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, 
							int* Width, int* Height, int* VCodec, int* ACodec);							// ��ȡ�����ļ�����ϸ��Ϣ
	void GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos);										// ��ȡ�����ļ����Ž���
	bool SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos);										// ���������ļ����Ž���
	bool SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed);									// ���ò����ٶ�
	bool SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode);									// ���������ļ�����ģʽ


public:		/************************************* CCTV ý�岥��ģ�� *************************************/
	
	// ����ģ���ʼ��
	void InitPlaySDK();

	// �������������ͷ�
	void DetectDecSupports(char* pDecoderTypes, INT_PTR* Len);													// ö��֧��Ӳ�����ͽӿ�
	bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType,
					  int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);		// ����������
	bool CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
		                int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);	// ������������ͬCreatePlayer��
	void ReleasePlayer(CWALK_PLAY_HD PlayHD);																	// �ͷŲ�����
	bool CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
						Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);								// ����Ӳ�ⲥ����
	void CheckHwSupport(int *Support);																			// ����豸�Ƿ�֧��Ӳ�⣨��ʱ����ʹ�ã�
	bool SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport);												// ����Ӳ��������
	void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* Type, int* HwType);											// ��ȡ��ǰ��������
	void SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);	// ���ý���״̬�ص�����

	// ý����������
	bool InputData(CWALK_PLAY_HD PlayHD, const void* Data, int Len);											// Ϊ�������ṩSlice����

	// ���ſ���
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);		// ���ſ���
	bool SetPane(CWALK_PLAY_HD PlayHD, const CWALKPLayRect* Rect, bool Ratio);									// ������ʾ����
	void ClearPlayBuffer(CWALK_PLAY_HD PlayHD);																	// ������Ż������е�����

	// ץͼ
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);											// ʵʱ��ץͼ
	
	// ��������
	void SoundEnable(CWALK_PLAY_HD PlayHD, bool Enable);														// ����/��ֹ�������ţ���ʼ��Ϊ����
	void SoundIsEnable(CWALK_PLAY_HD PlayHD, BOOL* Enable);														// ��ȡ��������״̬s
	void GetMasterVolume(int* Volume);																			// ��ȡϵͳ������
	bool SetMasterVolume(int Volume);																			// ����ϵͳ������
	void GetMasterVolumeMute(int* Mute);																		// ��ȡϵͳ����������
	bool SetMasterVolumeMute(int Mute);																			// ����ϵͳ����������
	bool SetAudioCallback(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);			// ������Ƶ�ص�����

	// ��ɫ����
	void GetColor(CWALK_PLAY_HD PlayHD, int* Brightness, int* Contrast, int* Saturation, int* Hue);				// ��ȡɫ��ֵ
	bool SetColor(CWALK_PLAY_HD PlayHD, int Brightness, int Contrast, int Saturation, int Hue);					// ����ɫ��ֵ

	// ���ַŴ�
	bool CreateZoomRect(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* ZoomHD, const CWALKPLayOSDRect* Rect, HWND Hwnd);	// �������ַŴ�����
	void GetZoomRect(CWALK_PLAY_HD ZoomHD, CWALKPLayOSDRect* Rect);												// ��ȡ���ַŴ�������Ϣ
	bool SetZoomRect(CWALK_PLAY_HD ZoomHD, const CWALKPLayOSDRect* Rect);										// �������ַŴ�������Ϣ
	void ReleaseZoomRect(CWALK_PLAY_HD ZoomHD);																	// �ͷ����ַŴ�����

	// OSD ����
	bool CreateOSD(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* osdHD, CWALKPLayOSDType Type, const void* osdInfo);		// ���� OSD
	void GetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, void* osdInfo);										// ��ȡ OSD ��Ϣ
	bool SetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, const void* osdInfo);								// ���� OSD ��Ϣ
	void ReleaseOSD(CWALK_PLAY_HD osdHD);																		// �ͷ� OSD

	// ͼ����
	bool SetIllumination(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101, 
						 int MaskHeight = 101, double Factor = 0.7);											// ���ȹ�һ�����������ڳ�����������������ͼ��
	bool SetScaleImageRange(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Min = 30, int Max = 240);		// �Աȶ��������������ڶԱȶȽ�С��ͼ��
	bool SetEmphasize(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101,
					  int MaskHeight = 101, double Factor = 0.7);												// �������������û�ģ����ͼ��
	bool SetSmooth(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth,
				   int MaskHeight, double Factor);																// ȥ�����������������ϴ��ͼ��
	bool SetDehaze(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, double TransMin = 0.6);						// ȥ����������������ɳ����ͼ��
	bool SetRetina(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect);											// ����Ĥ�㷨�����������������
	bool SetRestoration(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Blurring, double Angle, int Type);	// ͼ��ԭ�㷨�������뽹���˶�ģ��
	void DelEnhance(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int EnhanceType);							// ȡ��ͼ����ǿ


public:		/************************************* CCTV ����ģ�� *************************************/
	
	// ��ʼ������ģ��
	bool InitNetSDK();
	void GetNetServerVersion(void* InfoBuf, int Len, int* RealLen);									// ��� CMS ����汾��Ϣ

	// ��ȡ��֤��
	void GetTicket(BYTE* InfoBuf, int Len, int* RealLen);											// ��ȡ��֤��
	bool LoginByTicket(BYTE* Ticket, int Len);														// ͨ����֤��Ϣ��¼������

	// ʱ��ͬ��
	void GetServerTime(TCHAR* DateTime, int Len, int* RealLen);										// ��ȡ������ʱ�䣬��ʽΪ����2012-01-01 13:20:00.000��
	bool SetServerTime(TCHAR* DateTime);															// ���÷�����ʱ�䣬��ʽΪ����2012-01-01 13:20:00.000�� �� ��20120101132000000��
	bool SyncDeviceTime(const TCHAR* SerName, const TCHAR* HostName);								// ���豸ʱ��ͬ��Ϊ������ϵͳʱ�䣬�� SerName Ϊ��ʱ����ʾ��ǰ��¼������

	// ��ȡ�û�������Ϣ
	void GetUserDescription(void* Buf, int* BufLen, int* DateLen);									// ��ȡ�û�������Ϣ

	// �û��������û�ȡ
	void GetUserData(void* Buf, int BufLen, int* DataLen);											// ��ȡ�û�����
	bool SetUserData(void* Data, int DataLen);														// �����û�����
	bool SetUserPassword(const TCHAR* OldPassword, const TCHAR* NewPassword);						// �޸��û�����

	// ״̬��ȡ
	void IsConnected(BOOL* Connect);																// ����������������״̬
	void GetObjectStatus(CWALKNetObjectType ObjType, const TCHAR* ObjName, int* Status);			// ��ȡ����״̬
	void GetVodStatus(int* Status);																	// ��ȡ VOD ״̬
	void GetPtzStatus(const TCHAR* CamName, void* StatusBuf, int BufLen, int* RealLen);				// ��ȡ��̨״̬
	void GetCameraStatus(const TCHAR* ObjName, void* Buf, int BufLen, int* RealLen);				// ��ȡ����ͷ��̨״̬
	void GetServiceStatus(CWALKNetServiceType ServiceType, void* InfoBuf, int Len, int* RealLen);	// ��ȡ������״̬��Ϣ

	// �о�
	void ListObjects(CWALKNetObjectType ObjType, const TCHAR* SerName = nullptr,					// �оٶ��󣬵� SerName Ϊ��ʱ����ʾ��ǰ��¼������
					 int* Count = nullptr, CallBack_OnListObj FnOnListObj = nullptr, 
					 void* UserParam = nullptr);													
	void ListObjectsEx(CWALKNetObjectType ObjType, const TCHAR* SerName = nullptr,					// �оٶ��󣬵� SerName Ϊ��ʱ����ʾ��ǰ��¼��������GroupID ��Ϊ�ձ�ʾ�о�
					   int* Count = nullptr, CallBack_OnListObj FnOnListObj = nullptr,				// ��ǰ GroupID ��Ӧ���������IsGetAllCamera ��ʾ�Ƿ��о�������Ȩ�޵��豸
					   void* UserParam = nullptr, const TCHAR* GroupID = nullptr,					// IsGetAllCamera = true && GroupID == NULL ���� ��ȡ���������
					   bool IsGetAllCamera = false);												// IsGetAllCamera = false && GroupID == NULL ���� ��֮ǰ�Ļ����л�ȡ��Ӧ��Ϣ		
																									
	void QueryProtectionRecord(const TCHAR* AvPath, CallBack_OnListSegments FnOnListSegment,
							   void* UserParam = nullptr);											// �о��ܱ���¼��
																									
	void GetOnlineUsers(const TCHAR* SerName, CallBack_OnGetOnlineUsers FnOnUsers, void* UserParam);// �о������û���Ϣ���� SerName Ϊ��ʱ����ʾ��ǰ��¼������

	// ��ȡ�������Ĵ�����Ϣ
	void GetTransferStatus(const TCHAR* SerName, CallBack_OnGetTransferStatus FnOnStatus,
						   void* UserParam);														// ��ȡ�������Ĵ�����Ϣ

	// ¼�񱣻�
	bool ProtectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime);			// ����¼��
	void UnprotectRecord(const TCHAR* AvPath, const TCHAR* BeginTime, const TCHAR* EndTime);		// ���¼�񱣻�

	// ������Ӻ�ɾ��
	bool AddObject(CWALKNetObjectType ObjType, const TCHAR* Parent, const TCHAR* ObjInfo);			// ��̬��Ӷ���
	bool DelObject(CWALKNetObjectType ObjType, const TCHAR* ObjName);								// ɾ������

	// ��֯�ṹ��Ϣ��ȡ�ͽ���
	void GetOrganization(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount);		// ��ȡ��֯�ṹ��Ϣ
	void GetOrganizationEx(void* Buf, int* BufLen, int* DataLen, int* OrgCount, int* DCSCount,		// �õ�����ṹ��Ϣ����ȡȫ��������Ϣ����ͨ���û�ID��ȡ����Ҫ�ϲ�Ӧ�ù���
						   BOOL bUseUserID);														
	void ParseOrganizationInfo(const TCHAR* Info, int Type, int Index, const TCHAR* Key,			// ������֯�ṹ��Ϣ
							   void* ValueBuf, int Len, int* RealLen);								// ���������������,���ڽ��� CWALK_NET_GetOrganization() ���ص���֯�ṹ��Ϣ
	
	// ��ȡ��¼�������ı���
	void GetServerTitle(const TCHAR* ServerName, void* InfoBuf, int Len, int* RealLen);				// ��ȡ����������

	// ��ʾ��������
	bool StartTransfer(const TCHAR* Source, const TCHAR* Target);									// ������������������Ĵ���
	void StopTransfer(const TCHAR* Target);															// ֹͣ��ĳ���������Ĵ���
	void SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);			// �����л���ռ֪ͨ�ص�

	// ʵʱԤ��
	bool StartStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData,
					 CallBack_OnStreamRobbed FnRobbed, void* UserParam);									// ����ʵʱ��Ƶ��
	void StopStream(CWALK_NET_HD StreamHD);																	// �ر�������
	bool StartStreamByAsync(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						    CallBack_OnStreamRobbed FnRobbed, CallBack_OnStartRealStreamMsg FnMsg, 
							void* UserParam);																// ����ʵʱ��Ƶ�����첽��
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);														// ���� I ֡
	bool StartRecord(const TCHAR* AvPath);																	// ��ʼ������ֶ�¼��
	void StopRecord(const TCHAR* AvPath);																	// ֹͣ������ֶ�¼��
	void CapCameraPicture(const TCHAR* AvPath, TCHAR* PicResolution, TCHAR* PicFormat, TCHAR* PicBuff,
						  int BuffLen, int* RealLen);														// ץȡ�����ʵʱͼƬ

	// ��̨����
	bool PtzControl(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, int Param);								// ��̨���ƣ�ͨ���û������
	bool PtzControlEx(const TCHAR* AvPath, CWALKNetPTZCommand Cmd, const TCHAR* Param);						// ��̨������չ��ͨ���û������
	bool PtzControl3D(const TCHAR* AvPath, int Direct, float x, float y, float w, float h);					// 3D ��̨���ƣ�ͨ���û������
	void PtzLock(const TCHAR* AvPath, int LockTime);														// PTZ ��������
	void PtzAuxControl(const TCHAR* AvPath, int Num, BOOL Control);											// ��̨�������ؿ���

	// GIS ���ܽӿ�
	void GetCameraGis(const TCHAR* AvPath, void* Buf, int BufLen, int* RealLen);							// ��ȡ GIS ��Ϣ
	void CancelGisInfoSubscription();																		// �˶� GIS ��Ϣ
	bool SubscribeGisInfo(CallBack_OnGisInfoUpload FnOnUpload, void* UserParam);							// ���� GIS ��Ϣ

	// �������������
	bool SetCameraLevel(const TCHAR* AvPath, int Level);													// �������������

	// �������Ϣ��ȡ
	bool SetCamerasChangedNotify(CallBack_OnCamerasChangedNotify FnOnCamerasChangedNotify, void* UserParam);// ����������仯�ص�����
	void GetCamerasChangedVersion(INT64* ChangedVersion);													// ��ȡ������仯�汾��Ϣ

	// Զ��¼��
	void QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime,
					 CallBack_OnListSegments FnOnListSegment, void* UserParam);								// ��ѯ¼�񣬷Ƿ�¼��ʱ��λᱻ���˵���������Ϣ��¼����־��
	void QueryRecordInfo(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime,
						 CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);						// ¼���ѯ
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime,
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed,
							 CallBack_OnStreamMsg FnMsg, void* UserParam);									// �㲥¼��
	void StopPlayBackStream(CWALK_NET_HD PlayBackHD);														// ֹͣ¼��طţ�PlayBackHD �� StartPlayBackStream �õ�
	bool StartDownloadStreamEx(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
							   const TCHAR* EndTime, INT64 BeginThisPackage, INT64 BeginNextPackage,
							   Callback_OnStreamDataEx FnData, CallBack_OnStreamRobbed FnRobbed,
							   CallBack_OnStreamMsg FnMsg, void* UserParam);								// ¼�����أ�֧�ֶϵ�������
	void StopDownloadStream(CWALK_NET_HD StreamHD);															// ֹͣ¼������
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);											// ��ȡ¼�����ؽ���
	bool SetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64 Pos);											// ����¼�񲥷�λ��
	bool SetPlayBackSpeed(CWALK_NET_HD StreamHD, double Speed);												// ����¼��طŸ����ٶ�
	bool SetPlayBackMode(CWALK_NET_HD StreamHD, INT32 Mode);												// ���� VOD ����ģʽ

	// ֡���
	bool AddTag(const TCHAR* TagName, const TCHAR* TagTime, const TCHAR* ChannelName, 
				const TCHAR* Description, int TagType, int Level);											// ���֡���
	void GetTagNames(int* NameCount, CallBack_OnGetTagNames FnOnNames, void* UserParam);					// ��ȡ���б������
	void QueryTag(const TCHAR* Condition, int* RecordCount, BOOL* IsEnd, CallBack_OnQueryTag FnOnQueryTag,
				  void* UserParam);																			// ��ȡ���б������
	bool ModifyTagName(const TCHAR* OldTagName, const TCHAR* NewTagName);									// �޸ı������
	bool ModifyTag(INT64 TagID, const TCHAR* TagName, const TCHAR* Description, int Level);					// �޸�֡���
	void DeleteTags(INT64 TagIdArray[], int ArrayLen);														// ɾ��֡���

	// �¼�����
	bool SubscribeEvent(CallBack_OnEvent FnOnEvent, void* UserParam);										// �¼�����
	void CancelEventSubscription();																			// ȡ������

	// ִ�нű�
	bool ExecuteScript(const TCHAR* ScriptType, const TCHAR* Script);										// ִ�нű�

	// ��������
	void InfoParseKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, void* ValueBuf,
						   int Len, int* RealLen);															// ��������������������ڻ�ȡ ListObjects �����У�objInfo �����еĶ���������Ϣ
	void InfoParseIntKeyValue(const TCHAR* ObjInfo, const TCHAR* Key, int* Value);							// ��������������������ڽ��� Key-Value ��ʽ JSON �ַ���
	bool InfoHelperCreate(CWALK_HELP_HD* HelpHD);															// ���� Key-Value ��ʽ��������������һ�� Key-Value ��ʽ JSON �ַ���������������֮�󣬱���ʹ�� InfoHelperRelease �ͷ� 
	void InfoHelperAddKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, const TCHAR* Value);					// ������Ϣ���ɰ������������ key-value ��������Ϣ
	void InfoHelperAddIntKeyValue(CWALK_HELP_HD HelpHD, const TCHAR* Key, int Value);						// ������Ϣ���ɰ������������ key-value ��������Ϣ
	void InfoHelperGetData(CWALK_HELP_HD HelpHD, LPCTSTR* Buf, int* BufLen);								// ������Ϣ���ɰ����������õ��������е�����
	void InfoHelperRelease(CWALK_HELP_HD HelpHD);															// ������Ϣ���ɰ�������,�ͷ���Դ

private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::ofstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
};

