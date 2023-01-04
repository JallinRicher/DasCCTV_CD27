#pragma once
#include "afxdialogex.h"
#include "DisplayDialog.h"

class MainDialog;

// DisplayControlDialog 对话框
class DisplayControlDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayControlDialog)

public:
	DisplayControlDialog(MainDialog* ParentDialog, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayControlDialog();

	void FullScreen();
	void OneDisplayLayout();
	void FourDisplayLayout();
	void NineDisplayLayout();
	void SixteenDisplayLayout();
	void DefaultDisplayLayout();

	void StartDisplayMode();
	void StartMonitor();
	void StopMonitor();
	void StartPtzControl();
	void StopPtzControl();
	void StartSwitch();
	void StopSwitch();
	void StartSound();
	void StopSound();
	void SetDialogRect(int x, int y, int Width, int Height);

	void SetCurSelDisplayDialog(DisplayDialog* CurSel);
	void SetLayoutState(int layoutState);
	void SetLastLayoutState(int layoutState);
	int GetLastLayoutState() const;
	int GetLayoutState() const;
	DisplayDialog* GetCurSelDisplayDialog() const;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLATCONTROLDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	

private:
	MainDialog* m_ParentDialog;
	DisplayDialog* m_DisplayDialogs[MAX_DISPLAY_CNT];
	DisplayDialog* m_CurSelDisplayDialog;
	int m_LayoutState;
	int m_LastLayoutState;
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;
};
