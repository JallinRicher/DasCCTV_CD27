﻿#pragma once
#include "afxdialogex.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
#include "PtzControlButton.h"
#include "DisplayControlDialog.h"

// MainDialog 对话框

class MainDialog : public CDialog
{
	DECLARE_DYNAMIC(MainDialog)

public:
	enum { IDD = IDD_MAINDIALOG };
	MainDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainDialog();
	
	void Login();
	void InitCCTV();
	void SetUserInfo(UserInfo& info);

#ifdef MULTI_SUBWAY_ROUTE
	std::vector<UserInfo> GetUserInfo() const;
#else
	UserInfo GetUserInfo() const;
#endif

	void AddOneDisplayMode(const char* ModeName);
	void DelCurSelDisplayMode();
	void ModifyCurSelDisplayMode();
	void StartCurSelDisplayMode();

	void ShowCurStationList();
	void ShowCurAreaList();
	void ShowCurCameraList();
	void ShowDisplayModeList();
	void ShowCurSwitchList();

private:
	void InitUIFrame();
	void InitBitmap();
	void InitAllComboBox();
	void InitButton();
	void InitPtzControlButton();
	void InitChildWindow();	

#ifdef MULTI_SUBWAY_ROUTE
	void AddOneStation(const char* StationName, const char* StationResCode, int Route);
	void AddOneArea(const char* AreaName, const char* AreaResCode, int Route);
	void AddOneCamera(const char* CameraName, const char* CameraResCode, int CameraType, int CameraStatus, int Route);
	void AddOneSwitch(const char* SwitchName, const char* SwitchCode, int Route);
	void DelCurSelSwitch(int Route);
#else
	void AddOneStation(const char* StationName, const char* StationResCode);
	void AddOneArea(const char* AreaName, const char* AreaResCode);
	void AddOneCamera(const char* CameraName, const char* CameraResCode, int CameraType, int CameraStatus);
	void AddOneSwitch(const char* SwitchName, const char* SwitchCode);
	void DelCurSelSwitch();
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BitmapComboBox m_LayoutComboBox;
	BitmapComboBox m_StationComboBox;
	BitmapComboBox m_AreaComboBox;
	BitmapComboBox m_CameraComboBox;
	BitmapComboBox m_SoundComboBox;
	BitmapComboBox m_DisplayComboBox;
	BitmapComboBox m_SwitchComboBox;

	CButton m_FullScreenButton;
	CButton m_AddDspModeButton;
	CButton m_DelDspModeButton;
	CButton m_ModifyDspModeButton;
	CButton m_StartDspModeButton;
	CButton m_AddSwitchButton;
	CButton m_DelSwitchButton;
	CButton m_ModifySwitchButton;
	CButton m_StartSwitchButton;

	CStatic m_MainDialogProgressText;
	CProgressCtrl m_MainDialogProgress;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboLayout();
	afx_msg void OnCbnSelchangeComboStation();
	afx_msg void OnCbnSelchangeComboArea();
	afx_msg void OnCbnSelchangeComboCamera();
	afx_msg void OnCbnSelchangeComboSound();
	afx_msg void OnBnClickedButtonFullscreen();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMCustomdrawMainprogress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonAdddspmode();
	afx_msg void OnBnClickedButtonDeldspmode();
	afx_msg void OnBnClickedButtonModifydspmode();
	afx_msg void OnBnClickedButtonStartdspmode();
	afx_msg void OnBnClickedButtonAddswitchmode();
	afx_msg void OnBnClickedButtonDelswitchmode();
	afx_msg void OnBnClickedButtonModifyswitchmode();
	afx_msg void OnBnClickedButtonStartswitchmode();
	virtual BOOL OnInitDialog();

private:
	DisplayControlDialog* m_DisplayControl;
	bool IsLogged;
#ifdef MULTI_SUBWAY_ROUTE
	std::vector<UserInfo> m_UserInfo;
#else
	UserInfo m_UserInfo;
#endif

};
