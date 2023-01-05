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
	bool SetAudioCallBack(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);
	bool SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);

	// ʵʱ������ģ��
	bool StartVideoStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						  CallBack_OnStreamRobbed FnRobbed, void* UserParam);											// ����ʵʱ��Ƶ��
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);																	// ���� I ֡
	void StopVideoStream(CWALK_NET_HD StreamHD);																		// �ر�������

	// ¼��ط�ģ��
	bool QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, 
		             CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);										// ¼���ѯ
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, 
							 CallBack_OnStreamMsg FnMsg, void* UserParam);												// �㲥¼��
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);				// ���ſ���

	// ¼������ģ��
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);														// ��ȡ¼�����ؽ���
	
	// ʵʱ��ץͼģ��
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);													// ʵʱ��ץͼ


public:
	void CWALK_SDK_CALLBACK OnRealDecodeState(CWALK_PLAY_HD PlayHD, const CWALKPLayStatInfo* FInfo, void* UserParam)
	{  }

	// ��Ƶ����ص�����
	void CWALK_SDK_CALLBACK OnRealDecodeData(CWALK_PLAY_HD PlayHD, const void* Buf, int Len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
	{  }


public:
	static void CharToWChar(const char* Source, wchar_t* Destination);


public:		/************************************* CCTV �ļ�����ģ�� *************************************/

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

	// �������������ͷ�
	static void DetectDecSupports(char* pDecoderTypes, INT_PTR* Len);													// ö��֧��Ӳ�����ͽӿ�
	static bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType,
					         int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);		// ����������
	static bool CreatePlayerEx(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
		                       int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);	// ������������ͬCreatePlayer��
	static void ReleasePlayer(CWALK_PLAY_HD PlayHD);																	// �ͷŲ�����
	static bool CreateHwPlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
							   Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);								// ����Ӳ�ⲥ����
	static void CheckHwSupport(int *Support);																			// ����豸�Ƿ�֧��Ӳ��
	static bool SetHwDecType(CWALKPLayHWDecodeType Type, int* IsSupport);												// ����Ӳ��������
	static void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* Type, int* HwType);											// ��ȡ��ǰ��������
	
private:
	void InitPlaySDK();
	bool InitFileSDK();
	bool InitNetSDK();

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

