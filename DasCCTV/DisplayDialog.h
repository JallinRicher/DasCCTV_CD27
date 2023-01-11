#pragma once
#include "afxdialogex.h"
#include "cwalk_playsdk.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include <string>


struct DeviceInfo;
class DisplayControlDialog;
class MainDialog;

// DisplayDialog 对话框
class DisplayDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayDialog)

public:
	DisplayDialog(DisplayControlDialog* ParentDialog, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayDialog();

	void SetDisplayState(DisplayState State);
	void SetDeviceResCode(const TCHAR* DeviceResCode);
	void SetDeviceName(const TCHAR* DeviceName);
	void SetDeviceID(long DeviceID);
	void SetDeviceType(int DeviceType);
	void SetDeviceSubType(int DeviceSubType);
	void SetDeviceStatus(int DeviceStatus);
	void SetRegionID(long RegionID);
	void SetRegionResCode(const TCHAR* RegionResCode);

	DisplayDeviceInfo GetDisplayInfo() const;
	DisplayState GetDisplayState() const;
	int GetSoundChannel() const;
	void GetDeviceResCode(TCHAR* Retval) const;
	void GetDeviceName(TCHAR* Retval) const;
	long GetDeviceID() const;
	int GetDeviceType() const;
	int GetDeviceSubType() const;
	int GetDeviceStatus() const;
	long GetRegionID() const;
	void GetRegionResCode(TCHAR* Retval) const;

	void OpenSound(int SoundChannel);
	bool IsOpenSound() const;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAYDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CWALK_PLAY_HD m_PlayHD;
	CWALK_NET_HD m_StreamHD;

private:
	DisplayControlDialog* m_ParentDialog;
	TCHAR m_DeviceResCode[RES_CODE_LEN];
	TCHAR m_DeviceName[NAME_LEN];
	long m_DeviceID;
	int m_DeviceType;
	int m_DeviceSubType;
	int m_DeviceStatus;
	long m_RegionID;
	TCHAR m_RegionResCode[RES_CODE_LEN];

	DisplayState m_DisplayState;			// 窗口的播放状态
	bool m_IsOpenSound;						// 是否打开声音
	long m_SoundChannel;					// 声音播放通道
};
