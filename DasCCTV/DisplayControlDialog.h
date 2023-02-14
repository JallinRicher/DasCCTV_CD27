#pragma once
#include "afxdialogex.h"
#include "DisplayDialog.h"

class MainDialog;

// DisplayControlDialog 对话框
class DisplayControlDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayControlDialog)

public:
	DisplayControlDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayControlDialog();

	void FullScreen();
	void OneDisplayLayout();
	void FourDisplayLayout();
	void NineDisplayLayout();
	void SixteenDisplayLayout();
	void DefaultDisplayLayout();

	bool StartMonitor(const TCHAR* AvPath, int Index);
	bool StartMonitorBasedCurSelDlg(const TCHAR* AvPath);
	void StopMonitor(int Index);
	void StopMonitorBasedCurSelDlg();
	void StartPtzControl();
	void StopPtzControl();
	void StartSwitch();
	void StopSwitch();
	void StartSound();
	void StopSound();
	void SetDialogRect(int x, int y, int Width, int Height);

	void SetLayoutState(int layoutState);
	void SetLastLayoutState(int layoutState);
	int GetLastLayoutState() const;
	int GetLayoutState() const;

	void SetCurSelDisplayDialog(DisplayDialog* CurSel);
	DisplayDialog* GetCurSelDisplayDialog() const;




	virtual BOOL OnInitDialog();

private:
	void ChangeLayout(int Layout);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLATCONTROLDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	JSDCCTV* m_JsdCCTV;
	DisplayDialog* m_CurSelDisplayDialog;

private:
	DisplayDialog* m_DisplayDialogs[MAX_DISPLAY_CNT];
	MainDialog* m_ParentDialog;

	int m_LayoutState;
	int m_LastLayoutState;
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;
};
