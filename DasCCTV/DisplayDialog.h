#pragma once
#include "afxdialogex.h"
#include "cwalk_playsdk.h"
#include "cwalk_filesdk.h"
#include "cwalk_netsdk.h"
#include "JSDCCTV.h"
#include "CallBack.h"
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
	DisplayState GetDisplayState() const;
	void UpdateCurSelDialogState();
	void FlashSelf();

	void EnableSound(bool Flag);
	bool IsOpenSound() const;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:
	void DrawBorder();
	void DeleteBorder();


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
	TypeCamera m_Camera;

private:
	DisplayControlDialog* m_ParentDialog;
	JSDCCTV* m_JsdCCTV;

	DisplayState m_DisplayState;			// 窗口的播放状态
	bool m_IsOpenSound;						// 是否打开声音

	CBitmap m_NoVideoBitmap;
};
