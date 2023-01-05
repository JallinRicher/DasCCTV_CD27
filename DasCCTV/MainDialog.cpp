// MainDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "MainDialog.h"


// MainDialog 对话框

IMPLEMENT_DYNAMIC(MainDialog, CDialog)

MainDialog::MainDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINDIALOG, pParent)
{
	m_DisplayControl = nullptr;
	m_IsLogged = false;
	m_JsdCCTV = nullptr;
}


MainDialog::~MainDialog()
{
	if (m_JsdCCTV)
	{
		delete m_JsdCCTV;
	}
}


void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LAYOUT, m_LayoutComboBox);
	DDX_Control(pDX, IDC_COMBO_STATION, m_StationComboBox);
	DDX_Control(pDX, IDC_COMBO_AREA, m_AreaComboBox);
	DDX_Control(pDX, IDC_COMBO_CAMERA, m_CameraComboBox);
	DDX_Control(pDX, IDC_COMBO_SOUND, m_SoundComboBox);
	DDX_Control(pDX, IDC_BUTTON_FULLSCREEN, m_FullScreenButton);
	DDX_Control(pDX, IDC_MAINPROGRESS, m_MainDialogProgress);
	DDX_Control(pDX, IDC_STATIC_MAINPROGRESSINFO, m_MainDialogProgressText);
	DDX_Control(pDX, IDC_COMBO_DISPLAYMODE, m_DisplayComboBox);
	DDX_Control(pDX, IDC_COMBO_SWITCHMODE, m_SwitchComboBox);
	DDX_Control(pDX, IDC_BUTTON_ADDDSPMODE, m_AddDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_DELDSPMODE, m_DelDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_MODIFYDSPMODE, m_ModifyDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_STARTDSPMODE, m_StartDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_ADDSWITCHMODE, m_AddSwitchButton);
	DDX_Control(pDX, IDC_BUTTON_DELSWITCHMODE, m_DelSwitchButton);
	DDX_Control(pDX, IDC_BUTTON_MODIFYSWITCHMODE, m_ModifySwitchButton);
	DDX_Control(pDX, IDC_BUTTON_STARTSWITCHMODE, m_StartSwitchButton);
}


BEGIN_MESSAGE_MAP(MainDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_LAYOUT, &MainDialog::OnCbnSelchangeComboLayout)
	ON_CBN_SELCHANGE(IDC_COMBO_STATION, &MainDialog::OnCbnSelchangeComboStation)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA, &MainDialog::OnCbnSelchangeComboArea)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMERA, &MainDialog::OnCbnSelchangeComboCamera)
	ON_CBN_SELCHANGE(IDC_COMBO_SOUND, &MainDialog::OnCbnSelchangeComboSound)
	ON_BN_CLICKED(IDC_BUTTON_FULLSCREEN, &MainDialog::OnBnClickedButtonFullscreen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAINPROGRESS, &MainDialog::OnNMCustomdrawMainprogress)
	ON_BN_CLICKED(IDC_BUTTON_ADDDSPMODE, &MainDialog::OnBnClickedButtonAdddspmode)
	ON_BN_CLICKED(IDC_BUTTON_DELDSPMODE, &MainDialog::OnBnClickedButtonDeldspmode)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYDSPMODE, &MainDialog::OnBnClickedButtonModifydspmode)
	ON_BN_CLICKED(IDC_BUTTON_STARTDSPMODE, &MainDialog::OnBnClickedButtonStartdspmode)
	ON_BN_CLICKED(IDC_BUTTON_ADDSWITCHMODE, &MainDialog::OnBnClickedButtonAddswitchmode)
	ON_BN_CLICKED(IDC_BUTTON_DELSWITCHMODE, &MainDialog::OnBnClickedButtonDelswitchmode)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYSWITCHMODE, &MainDialog::OnBnClickedButtonModifyswitchmode)
	ON_BN_CLICKED(IDC_BUTTON_STARTSWITCHMODE, &MainDialog::OnBnClickedButtonStartswitchmode)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void MainDialog::InitChildWindow()
{
	m_DisplayControl = new DisplayControlDialog(this);
	m_DisplayControl->Create(IDD_DISPLATCONTROLDIALOG, this);
	m_DisplayControl->ShowWindow(SW_HIDE);

	CRect oRect;
	GetClientRect(&oRect);
	m_DisplayControl->MoveWindow(35, 27, oRect.Width() - 640, oRect.Height() - 320, TRUE);
	m_DisplayControl->SetDialogRect(35, 27, oRect.Width() - 640, oRect.Height() - 320);
	m_DisplayControl->ShowWindow(SW_SHOW);
	m_DisplayControl->EnableWindow(TRUE);
}


void MainDialog::OnCbnSelchangeComboLayout()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_LayoutComboBox.GetCurSel();
	int LayoutState = m_DisplayControl->GetLayoutState();
	switch (index)
	{
	case 0:
		m_DisplayControl->OneDisplayLayout();
		break;
	case 1:
		m_DisplayControl->FourDisplayLayout();
		break;
	case 2:
		m_DisplayControl->NineDisplayLayout();
		break;
	case 3:
		m_DisplayControl->SixteenDisplayLayout();
	default:
		break;
	}
	m_DisplayControl->SetLastLayoutState(LayoutState);
}


void MainDialog::OnCbnSelchangeComboStation()
{
	// TODO: 在此添加控件通知处理程序代码
	m_AreaComboBox.ClearAllContent();
	m_CameraComboBox.ClearAllContent();
	ShowCurAreaList();
	ShowCurCameraList();

#ifdef MULTI_SUBWAY_ROUTE
	m_SwitchComboBox.ClearAllContent();
	ShowCurSwitchList();
#endif
}


void MainDialog::OnCbnSelchangeComboArea()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CameraComboBox.ClearAllContent();
	ShowCurCameraList();
}


void MainDialog::OnCbnSelchangeComboCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DisplayControl->StopMonitor();
	m_DisplayControl->StartMonitor();
}


void MainDialog::OnCbnSelchangeComboSound()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_SoundComboBox.GetCurSel();
	switch (index)
	{
	case 0:
		m_DisplayControl->StopSound();
		m_DisplayControl->StartSound();
		break;
	case 1:
		m_DisplayControl->StopSound();
		break;
	default:
		break;
	}
}


void MainDialog::OnBnClickedButtonFullscreen()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DisplayControl->FullScreen();
}


int MainDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL MainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUIFrame();
	InitCCTV();

	m_DisplayControl = new DisplayControlDialog(this);
	m_DisplayControl->Create(IDD_DISPLATCONTROLDIALOG, this);
	m_DisplayControl->ShowWindow(SW_HIDE);

	CRect oRect;
	GetClientRect(&oRect);
	m_DisplayControl->MoveWindow(35, 27, oRect.Width() - 640, oRect.Height() - 300, TRUE);
	m_DisplayControl->SetDialogRect(35, 27, oRect.Width() - 640, oRect.Height() - 320);
	m_DisplayControl->DefaultDisplayLayout();
	m_LayoutComboBox.SetCurSel(1);
	m_DisplayControl->ShowWindow(SW_SHOW);
	m_DisplayControl->EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MainDialog::InitUIFrame()
{
	InitBitmap();
	InitAllComboBox();
	InitButton();
	InitPtzControlButton();
	
	m_MainDialogProgressText.SetWindowTextW(_T("ADDSAD"));
	m_MainDialogProgress.ShowWindow(TRUE);
}


void MainDialog::InitBitmap()
{

}


void MainDialog::InitAllComboBox()
{
	m_LayoutComboBox.Clear();
	m_StationComboBox.Clear();
	m_AreaComboBox.Clear();
	m_CameraComboBox.Clear();
	m_SoundComboBox.Clear();

	m_LayoutComboBox.AddOneRow("1 X 1");
	m_LayoutComboBox.AddOneRow("2 X 2");
	m_LayoutComboBox.AddOneRow("3 X 3");
	m_LayoutComboBox.AddOneRow("4 X 4");
	
	m_SoundComboBox.AddOneRow("打开声音");
	m_SoundComboBox.AddOneRow("关闭声音");
}


void MainDialog::InitButton()
{

}


void MainDialog::InitPtzControlButton()
{

}


void MainDialog::OnNMCustomdrawMainprogress(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UNREFERENCED_PARAMETER(pNMCD);
	*pResult = 0;
}


void MainDialog::AddOneDisplayMode(const char* ModeName)
{
	if (!ModeName)
	{
		return;
	}

	m_DisplayComboBox.AddOneRow(ModeName);
}


void MainDialog::DelCurSelDisplayMode()
{
	m_DisplayComboBox.DeleteCurSelRow();
}


void MainDialog::ModifyCurSelDisplayMode()
{
	int index = m_DisplayComboBox.GetCurSel();
	UNREFERENCED_PARAMETER(index);
}


void MainDialog::StartCurSelDisplayMode()
{
	int index = m_DisplayComboBox.GetCurSel();
	UNREFERENCED_PARAMETER(index);
}


void MainDialog::ShowCurStationList()
{

}


void MainDialog::ShowCurAreaList()
{

}


void MainDialog::ShowCurCameraList()
{

}


void MainDialog::ShowDisplayModeList()
{

}


void MainDialog::ShowCurSwitchList()
{

}


void MainDialog::Login()
{
#ifdef MULTI_SUBWAY_ROUTE
	for (UserInfo _user : m_UserInfo)
	{
		if (strlen(_user.IPAddress) == 0)
		{
			continue;
		}

		// TODO: 登录代码
		m_IsLogged = true;
	}

	return;

#else
	if (strlen(m_UserInfo.IPAddress) == 0)
	{
		return;
	}

	// TODO: 登录代码
	m_IsLogged = true;
#endif
}


void MainDialog::SetUserInfo(UserInfo& info)
{
#ifdef MULTI_SUBWAY_ROUTE
	m_UserInfo.push_back(info);
#else
	m_UserInfo = info;
#endif
}


#ifdef MULTI_SUBWAY_ROUTE
void MainDialog::AddOneStation(const char* StationName, const char* StationResCode, int Route)
{

}


void MainDialog::AddOneArea(const char* AreaName, const char* AreaResCode, int Route)
{

}


void MainDialog::AddOneCamera(const char* CameraName, const char* CameraResCode, int CameraType, int CameraStatus, int Route)
{

}


void MainDialog::AddOneSwitch(int SwitchID, int Route)
{

}


void MainDialog::DelCurSelSwitch(int Route)
{

}


std::vector<UserInfo> MainDialog::GetUserInfo() const
{
	return m_UserInfo;
}

#else


UserInfo MainDialog::GetUserInfo() const
{
	return m_UserInfo;
}


void MainDialog::AddOneStation(const char* StationName, const char* StationResCode)
{

	int index = m_StationComboBox.GetCount();
	m_StationComboBox.SetDeviceName(index, StationName);
	m_StationComboBox.SetDeviceResCode(index, StationResCode);
	m_StationComboBox.AddOneRow(StationName);
}


void MainDialog::AddOneArea(const char* AreaName, const char* AreaResCode)
{
	int index = m_AreaComboBox.GetCount();
	m_AreaComboBox.SetDeviceName(index, AreaName);
	m_AreaComboBox.SetDeviceResCode(index, AreaResCode);
	m_AreaComboBox.AddOneRow(AreaName);
}


void MainDialog::AddOneCamera(const char* CameraName, const char* CameraResCode, int CameraType, int CameraStatus)
{
	int index = m_CameraComboBox.GetCount();
	m_CameraComboBox.SetDeviceName(index, CameraName);
	m_CameraComboBox.SetDeviceResCode(index, CameraResCode);
	m_CameraComboBox.SetDeviceType(index, CameraType);
	m_CameraComboBox.SetDeviceStatus(index, CameraStatus);
	m_CameraComboBox.AddOneRow(CameraName);
}


void MainDialog::AddOneSwitch(const char* SwitchName, const char* SwitchCode)
{
	int index = m_SwitchComboBox.GetCount();
	m_SwitchComboBox.SetDeviceName(index, SwitchName);
	m_SwitchComboBox.SetDeviceResCode(index, SwitchCode);
	m_SwitchComboBox.AddOneRow(SwitchName);
}


void MainDialog::DelCurSelSwitch()
{
	m_SwitchComboBox.DeleteCurSelRow();
}

#endif

void MainDialog::OnBnClickedButtonAdddspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOneDisplayMode(nullptr);
}


void MainDialog::OnBnClickedButtonDeldspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	DelCurSelDisplayMode();
}


void MainDialog::OnBnClickedButtonModifydspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	ModifyCurSelDisplayMode();
}


void MainDialog::OnBnClickedButtonStartdspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	StartCurSelDisplayMode();
}


void MainDialog::OnBnClickedButtonAddswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOneSwitch(nullptr, nullptr);
}


void MainDialog::OnBnClickedButtonDelswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
	DelCurSelSwitch();
}


void MainDialog::OnBnClickedButtonModifyswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MainDialog::OnBnClickedButtonStartswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MainDialog::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(1);
	if (!m_IsLogged)
	{
		Login();
	}

	// TODO: 控件其他代码

	

	SetTimer(1, 2000, nullptr);
	CDialog::OnTimer(nIDEvent);
}


void MainDialog::InitCCTV()
{
	// TODO: CCTV 初始化代码
}
