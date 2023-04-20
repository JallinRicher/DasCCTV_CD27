// DisplayControlDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "DisplayControlDialog.h"

// DisplayControlDialog 对话框

IMPLEMENT_DYNAMIC(DisplayControlDialog, CDialog)

DisplayControlDialog::DisplayControlDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLATCONTROLDIALOG, pParent)
{
	m_X = 0;
	m_Y = 0;
	m_Height = 0;
	m_Width = 0;

	m_CurSelDisplayDialog = nullptr;
	m_CurSoundDisplayDialog = nullptr;

	m_LayoutState = INVALID_VALUE;
	m_LastLayoutState = INVALID_VALUE;

	m_JsdCCTV = nullptr;
	m_ParentDialog = (MainDialog*)pParent;

	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i] = nullptr;
	}
}

DisplayControlDialog::~DisplayControlDialog()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		if (m_DisplayDialogs[i])
		{
			delete m_DisplayDialogs[i];
			m_DisplayDialogs[i] = nullptr;
		}
	}

	m_CurSelDisplayDialog = nullptr;
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

	m_JsdCCTV = m_ParentDialog->m_JsdCCTV;

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

	if (m_LayoutState == FULLSCREEN)
	{
		// 退出全屏

		return;
	}
	else
	{
		CRect WindowRect;
		CRect ClientRect;
		GetWindowRect(&WindowRect);
		m_ParentDialog->ScreenToClient(&WindowRect);
		CWnd* pDeskWnd = GetDesktopWindow();
		pDeskWnd->GetClientRect(&ClientRect);

		SetParent(pDeskWnd);
		ClientRect.left += ClientRect.Width();
		ClientRect.right += ClientRect.Width();
		MoveWindow(ClientRect, TRUE);
		m_LayoutState = FULLSCREEN;
	}
}


void DisplayControlDialog::OneDisplayLayout()
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	m_LayoutState = ONE_DIALOG;
	int x = DISPLAY_INTERVAL;
	int y = DISPLAY_INTERVAL;;
	int Width = (m_Width - (2 * DISPLAY_INTERVAL));
	int Height = (m_Height - (2 * DISPLAY_INTERVAL));
	m_DisplayDialogs[0]->MoveWindow(x, y, Width, Height, TRUE);
	m_DisplayDialogs[0]->ShowWindow(SW_SHOW);
}


void DisplayControlDialog::ChangeLayout(int Layout)
{
	for (int i = 0; i < MAX_DISPLAY_CNT; ++i)
	{
		m_DisplayDialogs[i]->ShowWindow(FALSE);
	}

	CRect WindowRect;
	GetClientRect(&WindowRect);

	int _index = 0;
	int x = 0;
	int y = DISPLAY_INTERVAL;
	int Row = (int)sqrt(Layout);
	int Column = Row;
	int Width = (WindowRect.Width() - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
	int Height = (WindowRect.Height() - ((Row + 1) * DISPLAY_INTERVAL)) / Row;
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

	m_LayoutState = Layout;
}


void DisplayControlDialog::FourDisplayLayout()
{
	ChangeLayout(FOUR_DIALOG);
}


void DisplayControlDialog::NineDisplayLayout()
{
	ChangeLayout(NINE_DIALOG);
}


void DisplayControlDialog::SixteenDisplayLayout()
{
	ChangeLayout(SIXTEEN_DIALOG);
}


bool DisplayControlDialog::StartMonitorBasedCurSelDlg(const TCHAR* AvPath)
{
	if (m_CurSelDisplayDialog == nullptr)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::WARN, "In function [ %s ], m_CurSelDisplayDialog is nullptr.\n", __FUNCTION__);
		return false;
	}

	bool flag = false;
	RealPlay _realPlay;
	_realPlay.m_JsdCCTV = m_JsdCCTV;

	flag = m_JsdCCTV->CreatePlayer(&m_CurSelDisplayDialog->PlayHD(), m_CurSelDisplayDialog->GetSafeHwnd(), CWALKPLAY_STREAMTYPE_REALSTREAM, nullptr, nullptr);
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd create player failed.\n", __FUNCTION__);
		m_CurSelDisplayDialog->PlayHD() = nullptr;
		return flag;
	}

	m_JsdCCTV->SoundEnable(m_CurSelDisplayDialog->PlayHD(), FALSE);				// 默认不播放声音
	_realPlay.m_PlayHD = m_CurSelDisplayDialog->PlayHD();

	flag = m_JsdCCTV->StartStream(&m_CurSelDisplayDialog->StreamHD(), AvPath, nullptr, nullptr, (void*)&_realPlay);
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd start stream failed.\n", __FUNCTION__);
		m_JsdCCTV->ReleasePlayer(m_CurSelDisplayDialog->PlayHD());
		m_CurSelDisplayDialog->PlayHD() = nullptr;
		m_CurSelDisplayDialog->StreamHD() = nullptr;
		return flag;
	}
	_realPlay.m_StreamHD = m_CurSelDisplayDialog->StreamHD();

	flag = m_JsdCCTV->StreamRequestIFrame(m_CurSelDisplayDialog->StreamHD());
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd stream request I frame failed.\n", __FUNCTION__);
		m_JsdCCTV->ReleasePlayer(m_CurSelDisplayDialog->PlayHD());
		m_JsdCCTV->StopStream(m_CurSelDisplayDialog->StreamHD());
		m_CurSelDisplayDialog->PlayHD() = nullptr;
		m_CurSelDisplayDialog->StreamHD() = nullptr;
		return flag;
	}

	m_CurSelDisplayDialog->SetDisplayState(IS_LIVING);
	m_CurSelDisplayDialog->EnableSound(false);				// 默认不播放声音

	return true;
}


bool DisplayControlDialog::StartMonitor(const TCHAR* AvPath, int Index)
{
	if (m_DisplayDialogs[Index]->DisplayState() == IS_LIVING)
	{
		return false;
	}

	bool flag = false;
	RealPlay _realPlay;
	_realPlay.m_JsdCCTV = m_JsdCCTV;

	flag = m_JsdCCTV->CreatePlayer(&m_DisplayDialogs[Index]->PlayHD(), m_DisplayDialogs[Index]->GetSafeHwnd(), CWALKPLAY_STREAMTYPE_REALSTREAM, nullptr, nullptr);
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd create player failed.\n", __FUNCTION__);
		m_DisplayDialogs[Index]->PlayHD() = nullptr;
		return flag;
	}

	m_JsdCCTV->SoundEnable(m_DisplayDialogs[Index]->PlayHD(), FALSE);		// 默认不播放声音
	_realPlay.m_PlayHD = m_DisplayDialogs[Index]->PlayHD();

	flag = m_JsdCCTV->StartStream(&m_DisplayDialogs[Index]->StreamHD(), AvPath, nullptr, nullptr, (void*)&_realPlay);
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd start stream failed.\n", __FUNCTION__);
		m_JsdCCTV->ReleasePlayer(m_DisplayDialogs[Index]->PlayHD());
		m_DisplayDialogs[Index]->PlayHD() = nullptr;
		m_DisplayDialogs[Index]->StreamHD() = nullptr;
		return flag;
	}

	_realPlay.m_StreamHD = m_DisplayDialogs[Index]->StreamHD();

	flag = m_JsdCCTV->StreamRequestIFrame(m_DisplayDialogs[Index]->StreamHD());
	if (!flag)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::FATAL, "In function [ %s ], Jsd stream request I frame failed.\n", __FUNCTION__);
		m_JsdCCTV->ReleasePlayer(m_DisplayDialogs[Index]->PlayHD());
		m_JsdCCTV->StopStream(m_DisplayDialogs[Index]->StreamHD());
		m_DisplayDialogs[Index]->PlayHD() = nullptr;
		m_DisplayDialogs[Index]->StreamHD() = nullptr;
		return flag;
	}

	m_DisplayDialogs[Index]->SetDisplayState(IS_LIVING);
	m_DisplayDialogs[Index]->EnableSound(false);			// 默认不播放声音

	return true;
}


void DisplayControlDialog::StopMonitor(int Index)
{
	if (m_DisplayDialogs[Index]->DisplayState() == IS_BLANK)
	{
		return;
	}

	m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_DisplayDialogs[Index]->PlayHD());
	m_ParentDialog->m_JsdCCTV->StopStream(m_DisplayDialogs[Index]->StreamHD());
	m_DisplayDialogs[Index]->FlashSelf();
}


void DisplayControlDialog::StopMonitorBasedCurSelDlg()
{
	if (m_CurSelDisplayDialog == nullptr)
	{
		m_ParentDialog->InsertLog(LOGLEVEL::WARN, "In function [ %s ], m_CurSelDisplayDialog is nullptr.\n", __FUNCTION__);
		return;
	}

	if (m_CurSelDisplayDialog->DisplayState() == IS_BLANK)
	{
		return;
	}

	m_ParentDialog->m_JsdCCTV->ReleasePlayer(m_CurSelDisplayDialog->PlayHD());
	m_ParentDialog->m_JsdCCTV->StopStream(m_CurSelDisplayDialog->StreamHD());
	m_CurSelDisplayDialog->FlashSelf();
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

	if (m_CurSoundDisplayDialog != nullptr)
	{
		StopSound();
	}

	m_JsdCCTV->SoundEnable(m_CurSelDisplayDialog->PlayHD(), TRUE);
	m_CurSoundDisplayDialog = m_CurSelDisplayDialog;
	m_CurSelDisplayDialog->EnableSound(true);
}


void DisplayControlDialog::StopSound()
{
	if (m_CurSoundDisplayDialog == nullptr)
	{
		return;
	}

	m_JsdCCTV->SoundEnable(m_CurSoundDisplayDialog->PlayHD(), FALSE);
	m_CurSoundDisplayDialog->EnableSound(false);
	m_CurSoundDisplayDialog = nullptr;
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
	if (CurSel->IsOpenSound())
	{
		m_ParentDialog->m_SoundComboBox.SetCurSel(0);
	}
	else
	{
		m_ParentDialog->m_SoundComboBox.SetCurSel(1);
	}

	if (CurSel->DisplayState() != IS_BLANK)
	{
		m_ParentDialog->m_CameraTitleEdit.SetWindowText(CurSel->CamerType().name);
		m_ParentDialog->m_CameraTypeEdit.SetWindowText(CurSel->CamerType().type);
	}
}


DisplayDialog* DisplayControlDialog::GetCurSelDisplayDialog()
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
