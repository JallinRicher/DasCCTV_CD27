#pragma once
#include "afxdialogex.h"
#include <map>
#include "JSDCCTV.h"
#include "MainDialog.h"
#include "GlobalDefines.h"
#include "BitmapComboBox.h"


// AddDspModeDialog 对话框

class AddDspModeDialog : public CDialog
{
	DECLARE_DYNAMIC(AddDspModeDialog)

public:
	AddDspModeDialog(MainDialog* ParentDialog, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddDspModeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDDSPMODEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void InitUIFrame();

	void AddOneStation(const TypeStation& Stataion);
	void AddOneArea(const TypeArea& Area);
	void ShowCameraList();


public:
	BitmapComboBox m_StationComboBox;
	BitmapComboBox m_AreaComboBox;
	CListCtrl m_CameraList;
	CListCtrl m_DspModeList;
	CButton m_AddToDspModeButton;
	CButton m_RemoveFromDspModeButton;

private:
	JSDCCTV* m_JsdCCTV;
	MainDialog* m_ParentDialog;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnBnClickedButtonAddtodspmode();
	afx_msg void OnBnClickedButtonRemovefromdspmode();
};
