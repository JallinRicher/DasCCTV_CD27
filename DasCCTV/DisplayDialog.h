#pragma once
#include "afxdialogex.h"
#include <string>


struct DeviceInfo;
class DisplayControlDialog;

// DisplayDialog 对话框
class DisplayDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayDialog)

public:
	DisplayDialog(DisplayControlDialog* ParentDialog, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayDialog();
	
	void InitVariable();

	void SetDisplayState(int State);
	void SetDeviceResCode(const wchar_t* DeviceResCode);
	void SetDeviceName(const wchar_t* DeviceName);
	void SetDeviceID(long DeviceID);
	void SetDeviceType(int DeviceType);
	void SetDeviceSubType(int DeviceSubType);
	void SetDeviceStatus(int DeviceStatus);
	void SetRegionID(long RegionID);
	void SetRegionResCode(const wchar_t* RegionResCode);

	DisplayDeviceInfo GetDisplayInfo() const;
	int GetDisplayState() const;
	int GetSoundChannel() const;
	void GetDeviceResCode(wchar_t* Retval) const;
	void GetDeviceName(wchar_t* Retval) const;
	long GetDeviceID() const;
	int GetDeviceType() const;
	int GetDeviceSubType() const;
	int GetDeviceStatus() const;
	long GetRegionID() const;
	void GetRegionResCode(wchar_t* Retval) const;

	void OpenSound(int SoundChannel);
	bool IsOpenSound() const;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAYDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	DisplayControlDialog* m_ParentDialog;
	wchar_t m_DeviceResCode[RES_CODE_LEN];
	wchar_t m_DeviceName[NAME_LEN];
	long m_DeviceID;
	int m_DeviceType;
	int m_DeviceSubType;
	int m_DeviceStatus;
	long m_RegionID;
	wchar_t m_RegionResCode[RES_CODE_LEN];

	int m_DisplayState;						// 窗口的播放状态
	bool m_IsOpenSound;						// 是否打开声音
	long m_SoundChannel;					// 声音播放通道
};
