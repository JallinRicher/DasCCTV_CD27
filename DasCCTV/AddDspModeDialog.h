#pragma once
#include <map>
#include "afxdialogex.h"


// AddDspModeDialog 对话框

class AddDspModeDialog : public CDialog
{
	DECLARE_DYNAMIC(AddDspModeDialog)

public:
	AddDspModeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddDspModeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDDSPMODEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void ShowCameraList();
	void AddOneStation();
	void AddOneArea();
	void AddOneCameraToDspMode();
	void RemoveOneCameraFromDspMode();


public:
	CComboBox m_StationComboBox;
	CComboBox m_AreaComboBox;
	CListCtrl m_CameraList;
	CListCtrl m_DspModeList;
	CButton m_AddToDspModeButton;
	CButton m_RemoveFromDspModeButton;
};
