// DisplayDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "MainDialog.h"
#include "DisplayDialog.h"
#include "DisplayControlDialog.h"



// DisplayDialog 对话框

IMPLEMENT_DYNAMIC(DisplayDialog, CDialog)

DisplayDialog::DisplayDialog(DisplayControlDialog* ParentDialog, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLAYDIALOG, pParent), m_ParentDialog(ParentDialog)
{
	m_DisplayState = IS_BLANK;
	m_IsOpenSound = false;
	m_JsdCCTV = m_ParentDialog->m_JsdCCTV;
}


DisplayDialog::~DisplayDialog()
{
	m_ParentDialog = nullptr;
	m_ParentDialog->m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_PlayHD);
}


void DisplayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DisplayDialog, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// DisplayDialog 消息处理程序


void DisplayDialog::SetDisplayState(DisplayState State)
{
	if (State < IS_LIVING || State > IS_SNATCHING)
	{
		return;
	}
	m_DisplayState = State;
}


DisplayState DisplayDialog::GetDisplayState() const
{
	return m_DisplayState;
}


void DisplayDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ParentDialog->SetCurSelDisplayDialog(this);
	int LayoutState = m_ParentDialog->GetLayoutState();
	int LastLayoutState = m_ParentDialog->GetLastLayoutState();
	if (LayoutState != FULLSCREEN)
	{
		m_ParentDialog->FullScreen();
		m_ParentDialog->SetLastLayoutState(LayoutState);
	}
	else
	{
		switch (LastLayoutState)
		{
		case FULLSCREEN:
			m_ParentDialog->OneDisplayLayout();
			break;
		case FOUR_DIALOG:
			m_ParentDialog->FourDisplayLayout();
			break;
		case NINE_DIALOG:
			m_ParentDialog->NineDisplayLayout();
			break;
		case SIXTEEN_DIALOG:
			m_ParentDialog->SixteenDisplayLayout();
			break;
		default:
			break;
		}
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}


void DisplayDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ParentDialog->SetCurSelDisplayDialog(this);
	//ShowDisplayPic();
	CDialog::OnLButtonDown(nFlags, point);
}


void DisplayDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}


void DisplayDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ParentDialog->SetCurSelDisplayDialog(this);
	CDialog::OnRButtonDown(nFlags, point);
}


void DisplayDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnRButtonUp(nFlags, point);
}


BOOL DisplayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


bool DisplayDialog::IsOpenSound() const
{
	return m_IsOpenSound;
}


void DisplayDialog::EnableSound(bool Flag)
{
	m_IsOpenSound = Flag;
}