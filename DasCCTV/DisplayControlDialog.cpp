// DisplayControlDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "DisplayControlDialog.h"


// DisplayControlDialog 对话框

IMPLEMENT_DYNAMIC(DisplayControlDialog, CDialog)

DisplayControlDialog::DisplayControlDialog(MainDialog* ParentDialog, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLATCONTROLDIALOG, pParent), m_ParentDialog(ParentDialog)
{
	m_CurSelDisplayDialog = nullptr;
	m_LayoutState = INVALID_VALUE;
	m_LastLayoutState = INVALID_VALUE;
}

DisplayControlDialog::~DisplayControlDialog()
{
	m_ParentDialog = nullptr;
	m_CurSelDisplayDialog = nullptr;

	delete[] m_DisplayDialogs;
}

void DisplayControlDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DisplayControlDialog, CDialog)
END_MESSAGE_MAP()


// DisplayControlDialog 消息处理程序

BOOL DisplayControlDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i] = new DisplayDialog(this);
		m_DisplayDialogs[i]->Create(IDD_DISPLATCONTROLDIALOG, this);
		m_DisplayDialogs[i]->ShowWindow(SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DisplayControlDialog::FullScreen()
{
	if (m_CurSelDisplayDialog == nullptr)
	{
		MessageBox(_T("请选择需要全屏显示的窗口！"), _T("提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = FULLSCREEN;
	int x = DISPLAY_INTERVAL;
	int y = DISPLAY_INTERVAL;;
	int Width = (m_Width - (2 * DISPLAY_INTERVAL));
	int Height = (m_Height - (2 * DISPLAY_INTERVAL));
	m_CurSelDisplayDialog->MoveWindow(x, y, Width, Height, TRUE);
	m_CurSelDisplayDialog->ShowWindow(SW_SHOW);
}


void DisplayControlDialog::OneDisplayLayout()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = FULLSCREEN;
	int x = DISPLAY_INTERVAL;
	int y = DISPLAY_INTERVAL;;
	int Width = (m_Width - (2 * DISPLAY_INTERVAL));
	int Height = (m_Height - (2 * DISPLAY_INTERVAL));
	m_DisplayDialogs[0]->MoveWindow(x, y, Width, Height, TRUE);
	m_DisplayDialogs[0]->ShowWindow(SW_SHOW);
}


void DisplayControlDialog::FourDisplayLayout()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = FOUR_DIALOG;
	int _index = 0;
	int x = 0;
	int y = DISPLAY_INTERVAL;
	int Row = (int)sqrt(m_LayoutState);
	int Column = Row;
	int Width = (m_Width - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	int Height = (m_Height - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	for (int i = 0; i < Row; ++i)
	{
		x = DISPLAY_INTERVAL;
		for (int j = 0; j < Column; j++)
		{
			m_DisplayDialogs[_index]->MoveWindow(x, y, Width, Height, TRUE);
			m_DisplayDialogs[_index]->ShowWindow(SW_SHOW);
			x += Width + DISPLAY_INTERVAL;
			_index++;
		}
		y += Height + DISPLAY_INTERVAL;
	}
}


void DisplayControlDialog::NineDisplayLayout()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = NINE_DIALOG;
	int _index = 0;
	int x = 0;
	int y = DISPLAY_INTERVAL;
	int Row = (int)sqrt(m_LayoutState);
	int Column = Row;
	int Width = (m_Width - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	int Height = (m_Height - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	for (int i = 0; i < Row; ++i)
	{
		x = DISPLAY_INTERVAL;
		for (int j = 0; j < Column; j++)
		{
			m_DisplayDialogs[_index]->MoveWindow(x, y, Width, Height, TRUE);
			m_DisplayDialogs[_index]->ShowWindow(SW_SHOW);
			x += Width + DISPLAY_INTERVAL;
			_index++;
		}
		y += Height + DISPLAY_INTERVAL;
	}
}


void DisplayControlDialog::SixteenDisplayLayout()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = SIXTEEN_DIALOG;
	int _index = 0;
	int x = 0;
	int y = DISPLAY_INTERVAL;
	int Row = (int)sqrt(m_LayoutState);
	int Column = Row;
	int Width = (m_Width - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	int Height = (m_Height - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	for (int i = 0; i < Row; ++i)
	{
		x = DISPLAY_INTERVAL;
		for (int j = 0; j < Column; j++)
		{
			m_DisplayDialogs[_index]->MoveWindow(x, y, Width, Height, TRUE);
			m_DisplayDialogs[_index]->ShowWindow(SW_SHOW);
			x += Width + DISPLAY_INTERVAL;
			_index++;
		}
		y += Height + DISPLAY_INTERVAL;
	}
}


void DisplayControlDialog::StartDisplayMode()
{

}


void DisplayControlDialog::StartMonitor()
{

}


void DisplayControlDialog::StopMonitor()
{

}


void DisplayControlDialog::StartPtzControl()
{

}


void DisplayControlDialog::StopPtzControl()
{

}


void DisplayControlDialog::StartSwitch()
{

}


void DisplayControlDialog::StopSwitch()
{

}


void DisplayControlDialog::StartSound()
{

}


void DisplayControlDialog::StopSound()
{

}


void DisplayControlDialog::SetDialogRect(int x, int y, int Width, int Height)
{
	m_X = x;
	m_Y = y;
	m_Width = Width;
	m_Height = Height;
}


void DisplayControlDialog::DefaultDisplayLayout()
{
	FourDisplayLayout();
}


void DisplayControlDialog::SetCurSelDisplayDialog(DisplayDialog* CurSel)
{
	m_CurSelDisplayDialog = CurSel;
}


DisplayDialog* DisplayControlDialog::GetCurSelDisplayDialog() const
{
	return m_CurSelDisplayDialog;
}


void DisplayControlDialog::SetLayoutState(int layoutState)
{
	m_LayoutState = layoutState;
}


int DisplayControlDialog::GetLayoutState() const
{
	return m_LayoutState;
}


void DisplayControlDialog::SetLastLayoutState(int layoutState)
{
	m_LastLayoutState = layoutState;
}


int DisplayControlDialog::GetLastLayoutState() const
{
	return m_LastLayoutState;
}
