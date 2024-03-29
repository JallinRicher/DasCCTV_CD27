﻿#pragma once
#include "afxdialogex.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
#include "AddDspModeDialog.h"
#include "PtzControlButton.h"
#include "DisplayControlDialog.h"
#include "resource.h"
#include "JSDCCTV.h"

// MainDialog 对话框

class MainDialog : public CDialog
{
	DECLARE_DYNAMIC(MainDialog)

public:
	void ReadConfigFile();
	void InsertLog(LOGLEVEL Level, const char* const _Format, ...);
	bool SetLogFile(const char* LogPath, int Mode = std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::ate);
	static std::vector<std::string> SplitString(const char* _str, char _seq);
	static std::vector<CString> SplitString(const wchar_t* _wstr, wchar_t _seq);

	enum { IDD = IDD_MAINDIALOG };
	MainDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainDialog();
	
	bool Login();

	void ShowStationList();
	void ShowAreaList();
	void ShowCameraList();
	void ShowDisplayModeList();
	void ShowSwitchList();

	void SetProgressCtrlText(int HoldMiliseconds, const char* const _Format, ...);
	void SetProgressPos(int Pos) { m_MainDialogProgress.SetPos(Pos); }

	afx_msg void OnCbnSelchangeComboLayout();
	afx_msg void OnCbnSelchangeComboStation();
	afx_msg void OnCbnSelchangeComboArea();
	afx_msg void OnCbnSelchangeComboCamera();
	afx_msg void OnCbnSelchangeComboSound();
	afx_msg void OnBnClickedButtonFullscreen();
	afx_msg void OnCbnSelchangeComboDisplaymode();

	afx_msg void OnBnClickedButtonAdddspmode();
	afx_msg void OnBnClickedButtonDeldspmode();
	afx_msg void OnBnClickedButtonModifydspmode();
	afx_msg void OnBnClickedButtonStartdspmode();
	afx_msg void OnBnClickedButtonAddswitchmode();
	afx_msg void OnBnClickedButtonDelswitchmode();
	afx_msg void OnBnClickedButtonModifyswitchmode();
	afx_msg void OnBnClickedButtonStartswitchmode();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMCustomdrawMainprogress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	virtual BOOL OnInitDialog();

private:
	void InitCCTV();
	void InitFilePath();
	void InitUIFrame();
	void InitDisplayControlDialog();
	void InitBitmap();
	void InitAllComboBox();
	void InitButton();
	void InitPtzControlButton();

	void LoadBackground();
	HBRUSH SetStaticTextBG(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	JSDCCTV* m_JsdCCTV;

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

	CEdit m_CameraTitleEdit;
	CEdit m_CameraTypeEdit;

	CStatic m_MainDialogProgressText;
	CProgressCtrl m_MainDialogProgress;

private:
	bool m_IsLogin;
	unsigned int m_CurrentLayout;

	TCHAR m_AppWorkPath[FILE_PATH_LEN];
	TCHAR m_LogFilePath[FILE_PATH_LEN];
	TCHAR m_ConfigFilePath[FILE_PATH_LEN];
	TCHAR m_DownloadPath[FILE_PATH_LEN];

	std::fstream m_LogFile;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
	DisplayControlDialog* m_DisplayControl;
	
	CBrush m_BackgroundBrush;
	CBitmap m_BackgroundBitmap;
	CDC m_BackgroundDC;

	DspCtlDlgAttribute m_dspCtlDlgAttr;

};
