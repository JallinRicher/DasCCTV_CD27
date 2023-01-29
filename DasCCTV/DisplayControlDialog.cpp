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
	m_X = 0;
	m_Y = 0;
	m_Height = 0;
	m_Width = 0;
	m_CurSelDisplayDialog = nullptr;
	m_LayoutState = INVALID_VALUE;
	m_LastLayoutState = INVALID_VALUE;
	m_JsdCCTV = m_ParentDialog->m_JsdCCTV;

	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i] = nullptr;
	}
}

DisplayControlDialog::~DisplayControlDialog()
{
	m_ParentDialog = nullptr;
	m_CurSelDisplayDialog = nullptr;

	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		if (m_DisplayDialogs[i])
		{
			delete m_DisplayDialogs[i];
			m_DisplayDialogs[i] = nullptr;
		}
	}
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

	m_bmpBackground.LoadBitmap(IDB_BITMAP_DISPLAYBG);		// 先这样

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


bool DisplayControlDialog::StartMonitorBasedCurSelDlg(const TCHAR* AvPath)
{
	if (m_CurSelDisplayDialog == nullptr)
	{
		return false;
	}

	RealPlay _realPlay;
	_realPlay.m_JsdCCTV = m_JsdCCTV;

	m_JsdCCTV->CreatePlayer(&m_CurSelDisplayDialog->m_PlayHD, m_CurSelDisplayDialog->GetSafeHwnd(), CWALKPLAY_STREAMTYPE_REALSTREAM, nullptr, nullptr);
	m_JsdCCTV->SoundEnable(m_CurSelDisplayDialog->m_PlayHD, FALSE);				// 默认不播放声音
	_realPlay.m_PlayHD = m_CurSelDisplayDialog->m_PlayHD;

	m_JsdCCTV->StartStream(&m_CurSelDisplayDialog->m_StreamHD, AvPath, StreamData_CallBack, nullptr, (void*)&_realPlay);
	_realPlay.m_StreamHD = m_CurSelDisplayDialog->m_StreamHD;

	m_JsdCCTV->StreamRequestIFrame(m_CurSelDisplayDialog->m_StreamHD);

	m_CurSelDisplayDialog->SetDisplayState(IS_LIVING);
	m_CurSelDisplayDialog->EnableSound(false);				// 默认不播放声音

	return true;
}


bool DisplayControlDialog::StartMonitor(const TCHAR* AvPath, int Index)
{
	if (m_DisplayDialogs[Index]->GetDisplayState() == IS_LIVING)
	{
		return false;
	}

	RealPlay _realPlay;
	_realPlay.m_JsdCCTV = m_JsdCCTV;

	m_JsdCCTV->CreatePlayer(&m_DisplayDialogs[Index]->m_PlayHD, m_DisplayDialogs[Index]->GetSafeHwnd(), CWALKPLAY_STREAMTYPE_REALSTREAM, nullptr, nullptr);
	m_JsdCCTV->SoundEnable(m_DisplayDialogs[Index]->m_PlayHD, FALSE);		// 默认不播放声音
	_realPlay.m_PlayHD = m_DisplayDialogs[Index]->m_PlayHD;

	m_JsdCCTV->StartStream(&m_DisplayDialogs[Index]->m_StreamHD, AvPath, StreamData_CallBack, nullptr, (void*)&_realPlay);
	_realPlay.m_StreamHD = m_DisplayDialogs[Index]->m_StreamHD;

	m_JsdCCTV->StreamRequestIFrame(m_DisplayDialogs[Index]->m_StreamHD);

	m_DisplayDialogs[Index]->SetDisplayState(IS_LIVING);
	m_DisplayDialogs[Index]->EnableSound(false);			// 默认不播放声音

	return true;
}


void DisplayControlDialog::StopMonitor(int Index)
{
	if (m_DisplayDialogs[Index]->GetDisplayState() == IS_BLANK)
	{
		return;
	}

	m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_DisplayDialogs[Index]->m_PlayHD);
	m_ParentDialog->m_JsdCCTV->StopStream(m_DisplayDialogs[Index]->m_StreamHD);
	m_DisplayDialogs[Index]->SetDisplayState(IS_BLANK);
}


void DisplayControlDialog::StopMonitorBasedCurSelDlg()
{
	if (m_CurSelDisplayDialog == nullptr)
	{
		// LOG
		return;
	}

	if (m_CurSelDisplayDialog->GetDisplayState() == IS_BLANK)
	{
		return;
	}

	m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_CurSelDisplayDialog->m_PlayHD);
	m_ParentDialog->m_JsdCCTV->StopStream(m_CurSelDisplayDialog->m_StreamHD);
	m_CurSelDisplayDialog->SetDisplayState(IS_BLANK);
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
	if (m_CurSelDisplayDialog == nullptr)
	{
		AfxMessageBox("请选择播放窗口");
		return;
	}

	if (m_SoundDialog.m_CurOpenSoundDialog != nullptr)
	{
		StopSound();
	}

	m_JsdCCTV->SoundEnable(m_CurSelDisplayDialog->m_PlayHD, TRUE);
	m_SoundDialog.m_CurOpenSoundDialog = m_CurSelDisplayDialog;
	m_CurSelDisplayDialog->EnableSound(true);
}


void DisplayControlDialog::StopSound()
{
	if (m_SoundDialog.m_CurOpenSoundDialog == nullptr)
	{
		return;
	}

	DisplayDialog* m_CurOpenSoundDlg = m_SoundDialog.m_CurOpenSoundDialog;
	m_JsdCCTV->SoundEnable(m_CurOpenSoundDlg->m_PlayHD, FALSE);
	m_CurOpenSoundDlg->EnableSound(false);
	m_SoundDialog.m_CurOpenSoundDialog = nullptr;
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
