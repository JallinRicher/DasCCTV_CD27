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
	DisplayDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayDialog();

	void SetDisplayState(int State);
	
	void UpdateCurSelDialogState();
	void FlashSelf();
	void DrawBorder();				// 暂未实现
	void DeleteBorder();

	void EnableSound(bool Flag);
	bool IsOpenSound() const;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

public:
	TypeCamera& CamerType()
	{ return m_Camera; }
	CWALK_PLAY_HD& PlayHD()
	{ return m_PlayHD; }
	CWALK_NET_HD& StreamHD()
	{ return m_StreamHD; }
	CWALKPLayPcmFrame& PcmFrame()
	{ return m_PcmFrame; }


	int& DisplayState()
	{ return m_DisplayState; }


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAYDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	DisplayControlDialog* m_ParentDialog;

	bool m_IsOpenSound;
	int m_DisplayState;
	
	CWALK_PLAY_HD m_PlayHD;
	CWALK_NET_HD m_StreamHD;
	CWALKPLayPcmFrame m_PcmFrame;

	TypeCamera m_Camera;

	CBitmap m_NoVideoBitmap;

};
