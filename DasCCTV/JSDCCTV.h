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

	bool InitSDK();																											// ��ʼ��SDK
	bool Login();																											// ��¼������
	void Logout();																											// �ǳ�������
	void ReleaseSDK();																										// �ͷ�SDK
	void GetDecodeMode(CWALK_PLAY_HD PlayHD, int* DecodeMode, int* HwType);													// ��ȡ��ǰ��������			
	bool SetDecodeStateCallBack(CWALK_PLAY_HD PlayHD, Callback_OnDecodeState FnDecodeState, void* UserParam);
	bool SetAudioCallBack(CWALK_PLAY_HD PlayHD, Callback_OnAudioDecodeData FnOnAudio, void* UserParam);
	bool SetTransferRobbedCallBack(CallBack_OnTransferRobbed FnRobbed, void* UserParam);

	// ʵʱ������ģ��
	bool CreatePlayer(CWALK_PLAY_HD* PlayHD, HWND Hwnd, CWALKPLayStreamType StreamType, 
					  int DecodeMode, int HwType, Callback_OnVideoDecodeData FnOnDecoder, void* UserParam);					// ����������
	void ReleasePlayer(CWALK_PLAY_HD PlayHD);																				// �ͷŲ�����
	bool StartVideoStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, Callback_OnStreamData FnData, 
						  CallBack_OnStreamRobbed FnRobbed, void* UserParam);												// ����ʵʱ��Ƶ��
	bool StreamRequestIFrame(CWALK_NET_HD StreamHD);																		// ���� I ֡
	void StopVideoStream(CWALK_NET_HD StreamHD);																			// �ر�������

	// ¼��ط�ģ��
	bool QueryRecord(const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, const TCHAR* EndTime, 
		             CallBack_OnListSegmentsInfo FnOnListSegment, void* UserParam);											// ¼���ѯ
	bool StartPlayBackStream(CWALK_NET_HD* StreamHD, const TCHAR* AvPath, INT16 VodType, const TCHAR* BeginTime, 
						     const TCHAR* EndTime, Callback_OnStreamData FnData, CallBack_OnStreamRobbed FnRobbed, 
							 CallBack_OnStreamMsg FnMsg, void* UserParam);													// �㲥¼��
	bool PlayerControl(CWALK_PLAY_HD PlayHD, CWALKPLayControl Cmd, const void* InParam, void* OutParam);					// ���ſ���

	// ¼������ģ��
	bool OpenWritableFile(const TCHAR* FileName, CWALK_FILE_HD* WriteHD);													// �򿪿�д�ļ�
	bool GetPlayBackStreamPos(CWALK_NET_HD StreamHD, INT64* Pos);															// ��ȡ¼�����ؽ���
	void CloseWritableFile(CWALK_FILE_HD WriteHD);																			// �ر�д�ļ�����
	
	// ʵʱ��ץͼģ��
	bool CapturePicture(CWALK_PLAY_HD PlayHD, const TCHAR* FileName);														// ʵʱ��ץͼ

private:
	void InitPlaySDK();
	bool InitFileSDK();
	bool InitNetSDK();

	void CWALK_SDK_CALLBACK OnRealDecodeState(CWALK_PLAY_HD PlayHD, const CWALKPLayStatInfo* FInfo, void* UserParam)
	{

	}

	// ��Ƶ����ص�����
	void CWALK_SDK_CALLBACK OnRealDecodeData(CWALK_PLAY_HD PlayHD, const void* Buf, int Len, const CWALKPLayFrameInfo* FInfo, void* UserParam)
	{

	}

public:
	static void CharToWChar(const char* Source, wchar_t* Destination);

private:
	bool m_IsInitPlay;
	bool m_IsInitFile;
	bool m_IsInitNet;
	bool m_IsLogin;
	std::fstream m_LogFile;

	CWALK_NET_HD m_LoginHandle;
	UserInfo m_UserInfo;
};

