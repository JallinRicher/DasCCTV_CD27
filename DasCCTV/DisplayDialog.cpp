// DisplayDialog.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "MainDialog.h"
#include "DisplayDialog.h"
#include "DisplayControlDialog.h"



// DisplayDialog 对话框

IMPLEMENT_DYNAMIC(DisplayDialog, CDialog)

DisplayDialog::DisplayDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLAYDIALOG, pParent)
{
	m_DisplayState = IS_BLANK;
	m_IsOpenSound = false;
	m_PlayHD = nullptr;
	m_StreamHD = nullptr;

	m_ParentDialog = (DisplayControlDialog*)pParent;
}


DisplayDialog::~DisplayDialog()
{
	m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_PlayHD);
	FlashSelf();
	m_ParentDialog = nullptr;
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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DisplayDialog 消息处理程序


void DisplayDialog::SetDisplayState(int State)
{
	if (State < IS_LIVING || State > IS_SNATCHING)
	{
		return;
	}
	m_DisplayState = State;
}


void DisplayDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	UpdateCurSelDialogState();

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
	DisplayDialog* CurSelDialog = m_ParentDialog->GetCurSelDisplayDialog();
	if (CurSelDialog && CurSelDialog != this)
	{
		CurSelDialog->DeleteBorder();
		DrawBorder();
	}

	UpdateCurSelDialogState();
	
	CDialog::OnLButtonDown(nFlags, point);
}


void DisplayDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}


void DisplayDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	DisplayDialog* CurSelDialog = m_ParentDialog->GetCurSelDisplayDialog();
	if (CurSelDialog && CurSelDialog != this)
	{
		CurSelDialog->DeleteBorder();
		DrawBorder();
	}
	UpdateCurSelDialogState();

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
	m_NoVideoBitmap.LoadBitmap(IDB_BITMAP_NOVIDEO);

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


void DisplayDialog::UpdateCurSelDialogState()
{
	m_ParentDialog->SetCurSelDisplayDialog(this);
}


void DisplayDialog::FlashSelf()
{
	m_PlayHD = nullptr;
	m_StreamHD = nullptr;

	m_DisplayState = IS_BLANK;
	m_IsOpenSound = false;

	memset(&m_Camera, 0, sizeof(TypeCamera));
}


void DisplayDialog::DrawBorder()
{
	if (!IsWindowVisible()) return;

	//CPen* pOldPen = nullptr;
	//CPen* pPen = nullptr;

	//CRect rc(0, 0, 0, 0);
	//GetWindowRect(&rc);

	//GetParent()->GetDlgItem(IDC_STATIC_PLAYBG)->ScreenToClient(&rc);
}


void DisplayDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	DisplayDialog* CurSelDialog = m_ParentDialog->GetCurSelDisplayDialog();
	if (CurSelDialog == this)
	{
		DrawBorder();
	}

	if (m_DisplayState == IS_BLANK)
	{
		CRect DialogRect;
		GetClientRect(&DialogRect);

		CDC DialogDC;
		DialogDC.CreateCompatibleDC(&dc);

		BITMAP NoVideoBitmap;
		m_NoVideoBitmap.GetBitmap(&NoVideoBitmap);
		
		CBitmap* pOldBitmap = DialogDC.SelectObject(&m_NoVideoBitmap);
		dc.StretchBlt(0, 0, DialogRect.Width(), DialogRect.Height(), &DialogDC, 
					  0, 0, NoVideoBitmap.bmWidth, NoVideoBitmap.bmHeight, SRCCOPY);

		DialogDC.SelectObject(pOldBitmap);
		DialogDC.DeleteDC();
	}
}


void DisplayDialog::DeleteBorder()
{
	CDC* pDC = GetDC();
	ASSERT(pDC);

	pDC->SelectStockObject(BLACK_BRUSH);

}

