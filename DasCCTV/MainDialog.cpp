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
	m_IsLogin = false;
	m_JsdCCTV = nullptr;

	memset(m_AppWorkPath, 0, sizeof(m_AppWorkPath));
	memset(m_LogFilePath, 0, sizeof(m_LogFilePath));
	memset(m_ConfigFilePath, 0, sizeof(m_ConfigFilePath));
	memset(m_DownloadPath, 0, sizeof(m_DownloadPath));
}


MainDialog::~MainDialog()
{
	if (m_JsdCCTV)
	{
		delete m_JsdCCTV;
	}
}


void MainDialog::ReadConfigFile()
{
	/* 获取 DCS 用户信息 */
	GetPrivateProfileString(SECTION_DCSUSERINFO, CONFIG_KEY_USERNAME, DEFAULT_STR, m_DCSUserInfo.UserName, sizeof(m_DCSUserInfo.UserName), m_ConfigFilePath);
	GetPrivateProfileString(SECTION_DCSUSERINFO, CONFIG_KEY_PASSWORD, DEFAULT_STR, m_DCSUserInfo.Password, sizeof(m_DCSUserInfo.Password), m_ConfigFilePath);
	GetPrivateProfileString(SECTION_DCSUSERINFO, CONFIG_KEY_SERVERIP, DEFAULT_STR, m_DCSUserInfo.IPAddress, sizeof(m_DCSUserInfo.IPAddress), m_ConfigFilePath);
	m_DCSUserInfo.Port = GetPrivateProfileInt(SECTION_DCSUSERINFO, CONFIG_KEY_SERVERPORT, DEFAULT_INT, m_ConfigFilePath);

	/* 获取 DCR 用户信息 */
	GetPrivateProfileString(SECTION_DCRUSERINFO, CONFIG_KEY_USERNAME, DEFAULT_STR, m_DCRUserInfo.UserName, sizeof(m_DCRUserInfo.UserName), m_ConfigFilePath);
	GetPrivateProfileString(SECTION_DCRUSERINFO, CONFIG_KEY_PASSWORD, DEFAULT_STR, m_DCRUserInfo.Password, sizeof(m_DCRUserInfo.Password), m_ConfigFilePath);
	GetPrivateProfileString(SECTION_DCRUSERINFO, CONFIG_KEY_SERVERIP, DEFAULT_STR, m_DCRUserInfo.IPAddress, sizeof(m_DCRUserInfo.IPAddress), m_ConfigFilePath);
	m_DCRUserInfo.Port = GetPrivateProfileInt(SECTION_DCRUSERINFO, CONFIG_KEY_SERVERPORT, DEFAULT_INT, m_ConfigFilePath);

	/* 获取默认布局 */
	m_CurrentLayout = GetPrivateProfileInt(SECTION_GLOBAL, CONFIG_KEY_DEFAULT_LAYOUT, DEFAULT_INT, m_ConfigFilePath);

	/* 获取下载路径 */
	GetPrivateProfileString(SECTION_STORAGE, CONFIG_KEY_DOWNLOADPATH, DEFAULT_STR, m_DownloadPath, sizeof(m_DownloadPath), m_ConfigFilePath);

	/* 获取显示模式 */
	m_DisplayMode.ModeCount = GetPrivateProfileInt(SECTION_DISPLAYMODE, CONFIG_KEY_MODECOUNT, DEFAULT_INT, m_ConfigFilePath);
	unsigned int _modeCount = m_DisplayMode.ModeCount > MAX_DISPLAYMODE_CNT ? MAX_DISPLAYMODE_CNT : m_DisplayMode.ModeCount;
	for (unsigned int i = 0; i < _modeCount; ++i)
	{
		CString tempKeyName, tempKeyCamera;
		wchar_t tempCamera[RES_CODE_LEN] = { 0 };
		wchar_t tempName[NAME_LEN] = { 0 };
		tempKeyName.Format(L"%s%ud", CONFIG_KEY_MODENAME_PREFIX, i);
		tempKeyCamera.Format(L"%s%ud", CONFIG_KEY_MODECAMERA_PREFIX, i);

		GetPrivateProfileString(SECTION_DISPLAYMODE, tempKeyName, DEFAULT_STR, tempName, sizeof(tempName), m_ConfigFilePath);
		wcsncpy_s(m_DisplayMode._modeArray[i].ModeName, tempName, sizeof(m_DisplayMode._modeArray[i].ModeName));

		GetPrivateProfileString(SECTION_DISPLAYMODE, tempKeyCamera, DEFAULT_STR, tempCamera, sizeof(tempCamera), m_ConfigFilePath);
		std::vector<CString> vecCameraList = SplitString(tempCamera, ',');
		
		int CameraNum = vecCameraList.size() > MAX_DISPLAY_CNT ? MAX_DISPLAY_CNT : vecCameraList.size();
		for (int j = 0; j < CameraNum; ++j)
		{
			wcsncpy_s(m_DisplayMode._modeArray[i].ModeCamera[j], vecCameraList[j], sizeof(m_DisplayMode._modeArray[i].ModeName));
		}
	}
}


std::vector<std::string> MainDialog::SplitString(const char* _str, char _seq)
{
	std::vector<std::string> Retval;

	int strLen = strlen(_str);
	std::string tempStr;
	for (int i = 0; i < strLen; ++i)
	{
		if (_str[i] == _seq)
		{
			Retval.push_back(tempStr);
			tempStr.clear();
		}
		else
		{
			tempStr += _str[i];
		}
	}

	Retval.push_back(tempStr);
	tempStr.clear();
	return Retval;
}


std::vector<CString> MainDialog::SplitString(const wchar_t* _wstr, wchar_t _seq)
{
	std::vector<CString> Retval;

	int strLen = wcslen(_wstr);
	CString tempStr;
	for (int i = 0; i < strLen; ++i)
	{
		if (_wstr[i] == _seq)
		{
			Retval.push_back(tempStr);
			tempStr.Empty();
		}
		else
		{
			tempStr += _wstr[i];
		}
	}

	Retval.push_back(tempStr);
	tempStr.Empty();
	return Retval;
}


void MainDialog::InsertLog(LOGLEVEL Level, const char* const _Format, ...)
{
	if (!m_LogFile.is_open())
	{
		return;
	}

	va_list args;
	va_start(args, _Format);
	int len = _vscprintf(_Format, args) + 1;
	char* buffer = new char[len * sizeof(char)];
	vsnprintf(buffer, len * sizeof(char), _Format, args);
	va_end(args);

	CTime curTime = CTime::GetCurrentTime();
	char tempStr[DEFAULT_STR_LEN] = { 0 };
	sprintf_s(tempStr, DEFAULT_STR_LEN, "[ %04d-%02d-%02d %02d:%02d:%02d ] %s", curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond(), buffer);

	std::string str;
	switch (Level)
	{
	case FATAL: str = "[ FATAL ] ";	break;
	case WARN:	str = "[ WARN ]  ";	break;
	case DEBUG: str = "[ DEBUG ] ";	break;
	case INFO:	str = "[ INFO ]  ";	break;
	default: break;
	}

	str = str + tempStr;
	m_LogFile << str;

	delete[] buffer;
}


bool MainDialog::SetLogFile(const wchar_t* LogPath)
{
	m_LogFile.open(LogPath, std::ofstream::out | std::ofstream::app | std::ofstream::ate | std::ofstream::binary);
	if (!m_LogFile.is_open())
	{
		AfxMessageBox(L"打开日志文件失败");
		return false;
	}

	m_LogFile.write("123", 3);
	m_LogFile << "123" << L"123" << 0xFFFF;
	//InsertLog(INFO, "********************* Log start here *********************\n");
	return true;
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
	InitFilePath();
	ReadConfigFile();
	InitCCTV();
	
	
	CString CCTVLogFile = m_LogFilePath;
	CCTVLogFile.Append(L"\\DasCCTV_LOG.LOG");
	SetLogFile(CCTVLogFile);

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
	if (!m_IsLogin)
	{
		Login();
	}

	// TODO: 控件其他代码

	

	SetTimer(1, 2000, nullptr);
	CDialog::OnTimer(nIDEvent);
}


void MainDialog::InitCCTV()
{
	m_JsdCCTV = new JSDCCTV(m_DCSUserInfo);
	CString JsdLogFile = m_LogFilePath;
	JsdLogFile.Append(L"\\JSDCCTV_LOG.LOG");
	m_JsdCCTV->SetLogFile(JsdLogFile);

	if (wcslen(m_DCRUserInfo.IPAddress))
	{
		m_JsdCCTV->SetDCRUserInfo(m_DCRUserInfo);
	}

	m_JsdCCTV->InitSDK();
}


void MainDialog::InitFilePath()
{
	GetModuleFileName(AfxGetInstanceHandle(), m_AppWorkPath, FILE_PATH_LEN);
	PathRemoveFileSpec(m_AppWorkPath);

	CString tempWorkPath = m_AppWorkPath;
	CString tempLogPath = tempWorkPath + _T("\\Logs");
	CString tempConfigPath = tempWorkPath + L"\\" + CONFIG_FILE;
	wcsncpy_s(m_LogFilePath, tempLogPath, sizeof(m_LogFilePath));
	wcsncpy_s(m_ConfigFilePath, tempConfigPath, sizeof(m_ConfigFilePath));
}
