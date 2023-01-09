#pragma once
#include "afxdialogex.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"
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
	bool SetLogFile(const wchar_t* LogPath, int Mode = std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::ate);
	static std::vector<std::string> SplitString(const char* _str, char _seq);
	static std::vector<CString> SplitString(const wchar_t* _wstr, wchar_t _seq);

	enum { IDD = IDD_MAINDIALOG };
	MainDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainDialog();
	
	bool Login();
	
	void AddOneDisplayMode(const char* ModeName);
	void DelCurSelDisplayMode();
	void ModifyCurSelDisplayMode();
	void StartCurSelDisplayMode();

	void ShowCurStationList();
	void ShowCurAreaList();
	void ShowCurCameraList();
	void ShowDisplayModeList();
	void ShowCurSwitchList();

	void AddOneStation(const char* StationName, const char* StationResCode);
	void AddOneArea(const char* AreaName, const char* AreaResCode);
	void AddOneCamera(const char* CameraName, const char* CameraResCode, int CameraType, int CameraStatus);
	void AddOneSwitch(const char* SwitchName, const char* SwitchCode);
	void DelCurSelSwitch();

private:
	void InitCCTV();
	void InitFilePath();
	void InitUIFrame();
	void InitBitmap();
	void InitAllComboBox();
	void InitButton();
	void InitPtzControlButton();
	void InitChildWindow();	



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
	bool m_IsLogin;
	unsigned int m_CurrentLayout;

	wchar_t m_AppWorkPath[FILE_PATH_LEN];
	wchar_t m_LogFilePath[FILE_PATH_LEN];
	wchar_t m_ConfigFilePath[FILE_PATH_LEN];
	wchar_t m_DownloadPath[FILE_PATH_LEN];

	std::fstream m_LogFile;
	UserInfo m_DCSUserInfo;
	UserInfo m_DCRUserInfo;
	DisplayMode m_DisplayMode;
	DisplayControlDialog* m_DisplayControl;
	
	JSDCCTV* m_JsdCCTV;
};
