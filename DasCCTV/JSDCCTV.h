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
	JSDCCTV(UserInfo userInfo);

	bool InitSDK();																										// ��ʼ��SDK
	bool Login();																										// ��¼������
	void Logout();																										// �ǳ�������
	void ReleaseSDK();																									// �ͷ�SDK	
	bool SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);
	
	// ¼��ط�ģ��
	bool QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, 
		             CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);										// ¼���ѯ
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, 
							 CallBack_OnStreamMsg FnMsg, void* UserParam);												// �㲥¼��
	

	// ¼������ģ��
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);														// ��ȡ¼�����ؽ���
	

public:
	static void CWALK_SDK_CALLBACK OnRealDecodeState(CWALK_PLAY_HD PlayHD, const CWALKPLayStatInfo* FInfo, void* UserParam)
	{  }

	// ��Ƶ����ص�����
	static void CWALK_SDK_CALLBACK OnRealDecodeData(CWALK_PLAY_HD PlayHD, const void* Buf, int Len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
	{  }


public:
	static void CharToWChar(const char* Source, wchar_t* Destination);


public:		/************************************* CCTV �ļ�����ģ�� *************************************/
	
	// �ļ�ģ���ʼ��
	bool InitFileSDK();

	// ý���ļ�������
	static bool OpenReadableFile(const TCHAR* FileName, CWALK_FILE_HD* ReadHD);					// �򿪿ɶ��ļ�
	static void CloseReadableFile(CWALK_FILE_HD ReadHD);										// �رտɶ��ļ�
	static bool ReadSlice(CWALK_FILE_HD ReadHD, void** Data, int* Len);							// �ӿɶ��ļ��ж�ȡ���ݣ�������FreeFile�ͷ����ݣ������������Ϊһ��������slice
	static void FreeFile(void* Ptr);															// �ͷ��ڴ�
	static bool SetPlayMode(CWALK_FILE_HD ReadHD, int Mode);									// ���ò���ģʽ
	static bool GetPlayMode(CWALK_FILE_HD ReadHD, int* Mode);									// ��ò���ģʽ

	// ý���ļ�д����
	static bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);				// �򿪿�д�ļ�
	static void CloseWritableFile(CWALK_FILE_HD WriteHD);										// �ر�д�ļ�����
	static bool WriteData(CWALK_FILE_HD WriteHD, const void* data, int Len);					// ����д���ļ�������data����Ϊһ��������slice������������Ļص��������

	// ý���ļ�λ�ÿ���
	static void GetFileDuration(CWALK_FILE_HD ReadHD, DWORD* Len);								// ����ļ�������
	static void GetFilePos(CWALK_FILE_HD ReadHD, DWORD* Len);									// ����ļ���ȡλ��
	static bool SetFilePos(CWALK_FILE_HD ReadHD, DWORD Len);									// �����ļ���ȡλ��

	// �õ�¼���ļ���һ֡������ʱ��
	static void GetBaseTime(CWALK_FILE_HD ReadHD, INT64* Time);									// ���¼���һ֡������ʱ�䣬����ڸ������α�׼ʱ��ĺ�����
	static void GetStringBaseTime(CWALK_FILE_HD ReadHD, TCHAR* Buf, int BufLen, int* RealLen);	// ���¼���һ֡������ʱ�䣬���ر�׼��ʽ��ʱ���ַ������ڴ��ɵ����߷���

	// ���ݸ�ʽת��
	static void GetVideoInfo(CWALK_FILE_HD ReadHD, int* Width, int* Height, float* Rate, int* StreamType);		// ��ȡͼ����Ϣ
	static bool CreateExtrator(const void* Data, int Size, CWALK_FILE_HD* ExtratorHD);							// �������ݸ�ʽת����
	static bool InputData(CWALK_FILE_HD ExtratorHD, const void* Data, int Size);								// ��������
	static void NextFrame(CWALK_FILE_HD ExtratorHD, void* pStream, int* Len);									// ��ȡ���ݣ��ɻ���������ͣ�
	static void ReleaseExtractor(CWALK_FILE_HD ExtratorHD);														// �ͷ����ݸ�ʽת����

	// �����ļ�����
	bool OpenOfflineFile(const TCHAR* Protocol, CWALK_FILE_HD* ReadHD, const TCHAR* IP, const WORD Port, 
						 const TCHAR* Pool, const TCHAR* FilePath);												// �������ļ�
	static void CloseOfflineFile(CWALK_FILE_HD ReadHD);															// �ر������ļ�
	static bool StartOfflineFileStream(CWALK_FILE_HD ReadHD, const int BeginTime, const int EndTime, 
									   Callback_File_OnStreamData FnData, CallBack_File_OnStreamMsg FnMsg, 
									   void* UserParam);														// ���������ļ�����
	static void StopOfflineFileStream(CWALK_FILE_HD ReadHD);													// ֹͣ���߻ط�
	static void GetOfflineFileInfo(CWALK_FILE_HD ReadHD, INT64* Size, INT64* Duration, int* FPS, 
								   int* Width, int* Height, int* VCodec, int* ACodec);							// ��ȡ�����ļ�����ϸ��Ϣ
	static void GetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64* Pos);										// ��ȡ�����ļ����Ž���
	static bool SetOfflineFileStreamPos(CWALK_FILE_HD ReadHD, INT64 Pos);										// ���������ļ����Ž���
	static bool SetOfflineFileStreamSpeed(CWALK_FILE_HD ReadHD, double Speed);									// ���ò����ٶ�
	static bool SetOfflineFilePlayBackMode(CWALK_FILE_HD ReadHD, INT32 Mode);									// ���������ļ�����ģʽ


public:		/************************************* CCTV ý�岥��ģ�� *************************************/
	
	// ����ģ���ʼ��
	void InitPlaySDK();

	// �������������ͷ�
	static void DetectDecSupports(char* pDecoderTypes, INT_PTR* Len);													// ö��֧��Ӳ�����ͽӿ�
	static bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType,
					         int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);		// ����������
	static bool CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
		                       int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);	// ������������ͬCreatePlayer��
	static void ReleasePlayer(CWALK_PLAY_HD PlayHD);																	// �ͷŲ�����
	static bool CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
							   Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);								// ����Ӳ�ⲥ����
	static void CheckHwSupport(int *Support);																			// ����豸�Ƿ�֧��Ӳ�⣨��ʱ����ʹ�ã�
	static bool SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport);												// ����Ӳ��������
	static void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* Type, int* HwType);											// ��ȡ��ǰ��������

	// ý����������
	static bool InputData(CWALK_PLAY_HD PlayHD, const void* Data, int Len);												// Ϊ�������ṩSlice����

	// ���ſ���
	static bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);			// ���ſ���
	static bool SetPane(CWALK_PLAY_HD PlayHD, const CWALKPLayRect* Rect, bool Ratio);									// ������ʾ����
	static void ClearPlayBuffer(CWALK_PLAY_HD PlayHD);																	// ������Ż������е�����

	// ץͼ
	static bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);											// ʵʱ��ץͼ
	
	// ��������
	static void SoundEnable(CWALK_PLAY_HD PlayHD, bool Enable);															// ����/��ֹ�������ţ���ʼ��Ϊ����
	static void SoundIsEnable(CWALK_PLAY_HD PlayHD, BOOL* Enable);														// ��ȡ��������״̬s
	static void GetMasterVolume(int* Volume);																			// ��ȡϵͳ������
	static bool SetMasterVolume(int Volume);																			// ����ϵͳ������
	static void GetMasterVolumeMute(int* Mute);																			// ��ȡϵͳ����������
	static bool SetMasterVolumeMute(int* Mute);																			// ����ϵͳ����������
	static bool SetAudioCallback(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);			// ������Ƶ�ص�����

	// ��ɫ����
	static void GetColor(CWALK_PLAY_HD PlayHD, int* Brightness, int* Contrast, int* Saturation, int* Hue);				// ��ȡɫ��ֵ
	static bool SetColor(CWALK_PLAY_HD PlayHD, int Brightness, int Contrast, int Saturation, int Hue);					// ����ɫ��ֵ

	// ���ַŴ�
	static bool CreateZoomRect(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* ZoomHD, const CWALKPLayOSDRect* Rect, HWND Hwnd);	// �������ַŴ�����
	static void GetZoomRect(CWALK_PLAY_HD ZoomHD, CWALKPLayOSDRect* Rect);												// ��ȡ���ַŴ�������Ϣ
	static bool SetZoomRect(CWALK_PLAY_HD ZoomHD, const CWALKPLayOSDRect* Rect);										// �������ַŴ�������Ϣ
	static void ReleaseZoomRect(CWALK_PLAY_HD ZoomHD);																	// �ͷ����ַŴ�����

	// OSD ����
	static bool CreateOSD(CWALK_PLAY_HD PlayHD, CWALK_PLAY_HD* osdHD, CWALKPLayOSDType Type, const void* osdInfo);		// ���� OSD
	static void GetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, void* osdInfo);										// ��ȡ OSD ��Ϣ
	static bool SetOSD(CWALK_PLAY_HD osdHD, CWALKPLayOSDType Type, const void* osdInfo);								// ���� OSD ��Ϣ
	static void ReleaseOSD(CWALK_PLAY_HD osdHD);																		// �ͷ� OSD

	// ͼ����
	static bool SetIllumination(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101, 
								int MaskHeight = 101, double Factor = 0.7);												// ���ȹ�һ�����������ڳ�����������������ͼ��
	static bool SetScaleImageRange(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Min = 30, int Max = 240);		// �Աȶ��������������ڶԱȶȽ�С��ͼ��
	static bool SetEmphasize(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth = 101,
							 int MaskHeight = 101, double Factor = 0.7);												// �������������û�ģ����ͼ��
	static bool SetSmooth(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int MaskWidth,
						  int MaskHeight, double Factor);																// ȥ�����������������ϴ��ͼ��
	static bool SetDehaze(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, double TransMin = 0.6);						// ȥ����������������ɳ����ͼ��
	static bool SetRetina(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect);												// ����Ĥ�㷨�����������������
	static bool SetRestoration(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int Blurring, double Angle, int Type);	// ͼ��ԭ�㷨�������뽹���˶�ģ��
	static void DelEnhance(CWALK_PLAY_HD PlayHD, CWALKPLayEnhanceRect Rect, int EnhanceType);							// ȡ��ͼ����ǿ


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
	static void ParseOrganizationInfo(const TCHAR* Info, int Type, int Index, const TCHAR* Key,		// ������֯�ṹ��Ϣ
							   void* ValueBuf, int Len, int* RealLen);								// ���������������,���ڽ��� CWALK_NET_GetOrganization() ���ص���֯�ṹ��Ϣ
	
	// ��ȡ��¼�������ı���
	void GetServerTitle(const TCHAR* ServerName, void* InfoBuf, int Len, int* RealLen);				// ��ȡ����������

	// ��ʾ��������
	bool StartTransfer(const TCHAR* Source, const TCHAR* Target);									// ������������������Ĵ���
	void StopTransfer(const TCHAR* Target);															// ֹͣ��ĳ���������Ĵ���
	bool SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);			// �����л���ռ֪ͨ�ص�

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



private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::fstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
};

