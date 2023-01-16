// MainDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "MainDialog.h"
#include "CallBack.h"


// MainDialog 对话框

IMPLEMENT_DYNAMIC(MainDialog, CDialog)

MainDialog::MainDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINDIALOG, pParent)
{
	m_DisplayControl = nullptr;
	m_IsLogin = false;
	m_IsFirstLogin = true;
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
		m_JsdCCTV = nullptr;
	}

	if (m_DisplayControl)
	{
		delete m_DisplayControl;
		m_DisplayControl = nullptr;
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


bool MainDialog::SetLogFile(const char* LogPath, int Mode)
{
	m_LogFile.open(LogPath, Mode);
	if (!m_LogFile.is_open())
	{
		AfxMessageBox("打开日志文件失败");
		return false;
	}

	InsertLog(INFO, "\n********************* Log start here *********************\n");
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
	DDX_Control(pDX, IDC_EDIT_CAMERAID, m_CameraTitleEdit);
	DDX_Control(pDX, IDC_EDIT_CAMERATYPE, m_CameraTypeEdit);
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
	ON_CBN_SELCHANGE(IDC_COMBO_DISPLAYMODE, &MainDialog::OnCbnSelchangeComboDisplaymode)
END_MESSAGE_MAP()


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
	ShowAreaList();
	ShowCameraList();
}


void MainDialog::OnCbnSelchangeComboArea()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CameraComboBox.ClearAllContent();

	TypeOrg _area = m_AreaComboBox.GetCurSelArea();

	ShowCameraList();
}


void MainDialog::OnCbnSelchangeComboCamera()
{
	TypeCamera _camera = m_CameraComboBox.GetCurSelCamera();
	
	m_DisplayControl->StopMonitorBasedCurSelDlg();
	if (!m_DisplayControl->StartMonitorBasedCurSelDlg(_camera.rtspUrl))
	{
		InsertLog(FATAL, "Start monitor failed. AvPath is %s\n", _camera.rtspUrl);
	}
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


void MainDialog::OnCbnSelchangeComboDisplaymode()
{
	// TODO: 在此添加控件通知处理程序代码
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
	CCTVLogFile.Append("\\DasCCTV_LOG.LOG");
	SetLogFile(CCTVLogFile);

	SetTimer(1, 2000, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MainDialog::InitDisplayControlDialog()
{
	m_DisplayControl = new DisplayControlDialog(this);
	m_DisplayControl->Create(IDD_DISPLATCONTROLDIALOG, this);
	m_DisplayControl->ShowWindow(SW_HIDE);

	CRect oRect;
	GetClientRect(&oRect);
	m_DisplayControl->MoveWindow(35, 27, oRect.Width() - 640, oRect.Height() - 300, TRUE);
	m_DisplayControl->SetDialogRect(35, 27, oRect.Width() - 640, oRect.Height() - 320);
	m_DisplayControl->DefaultDisplayLayout();
	m_DisplayControl->ShowWindow(SW_SHOW);
	m_DisplayControl->EnableWindow(TRUE);
}


void MainDialog::InitUIFrame()
{
	InitBitmap();
	InitButton();
	InitAllComboBox();
	InitDisplayControlDialog();
	
	m_MainDialogProgress.SetPos(0);
	m_MainDialogProgress.ShowWindow(FALSE);
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
	m_DisplayComboBox.Clear();
	m_SwitchComboBox.Clear();

	m_LayoutComboBox.SetComboBoxType(CWALKNET_TYPE_UNKNOWN);
	m_StationComboBox.SetComboBoxType(CWALKNET_TYPE_GATEWAY);
	m_AreaComboBox.SetComboBoxType(CWALKNET_TYPE_GATEWAY);
	m_CameraComboBox.SetComboBoxType(CWALKNET_TYPE_CAMERA);
	m_SoundComboBox.SetComboBoxType(CWALKNET_TYPE_AUDIO);
	m_DisplayComboBox.SetComboBoxType(CWALKNET_TYPE_DISPLAY);
	m_SwitchComboBox.SetComboBoxType(CWALKNET_TYPE_SWITCH);

	m_LayoutComboBox.AddString("1 X 1");
	m_LayoutComboBox.AddString("2 X 2");
	m_LayoutComboBox.AddString("3 X 3");
	m_LayoutComboBox.AddString("4 X 4");

	m_SoundComboBox.AddString("打开声音");
	m_SoundComboBox.AddString("关闭声音");

	m_SoundComboBox.SetCurSel(1);
	m_LayoutComboBox.SetCurSel(1);

}


void MainDialog::InitButton()
{
	InitPtzControlButton();
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


void MainDialog::ShowStationList()
{
	std::vector<TypeOrg> vecStations;
	int Len = m_JsdCCTV->GetOrganization(nullptr, nullptr, nullptr, nullptr, nullptr);

	int OrgCount = 0;
	void* Buf = (void*)new char[Len];
	m_JsdCCTV->GetOrganization(Buf, &Len, nullptr, &OrgCount, nullptr);

	void* ValueBuf = new char[RES_CODE_LEN];
	memset(ValueBuf, 0, RES_CODE_LEN);
	for (int i = 0; i < OrgCount; ++i)
	{
		TypeOrg _station;
		m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "parentId", ValueBuf, RES_CODE_LEN, nullptr);
		_station.parentid = (TCHAR*)ValueBuf;
		if (_station.parentid == "")		// 为车站
		{
			memset(ValueBuf, 0, RES_CODE_LEN);
			m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "id", ValueBuf, RES_CODE_LEN, nullptr);
			_station.id = (TCHAR*)ValueBuf;

			memset(ValueBuf, 0, RES_CODE_LEN);
			m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "name", ValueBuf, RES_CODE_LEN, nullptr);
			_station.name = (TCHAR*)ValueBuf;

			vecStations.push_back(_station);
			break;
		}
	}

	for (auto ele : vecStations)
		m_StationComboBox.AddOneStation(ele);
	
	m_StationComboBox.SetCurSel(0);

	delete[] Buf;
	delete[] ValueBuf;
}


void MainDialog::ShowAreaList()
{
	std::vector<TypeOrg> vecAreas;
	TypeOrg station = m_StationComboBox.GetCurSelStation();
	int Len = m_JsdCCTV->GetOrganization(nullptr, nullptr, nullptr, nullptr, nullptr);

	int OrgCount = 0;
	void* Buf = (void*)new char[Len];
	m_JsdCCTV->GetOrganization(Buf, &Len, nullptr, &OrgCount, nullptr);

	void* ValueBuf = new char[RES_CODE_LEN];
	memset(ValueBuf, 0, RES_CODE_LEN);
	for (int i = 0; i < OrgCount; ++i)
	{
		TypeOrg _area;
		m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "parentId", ValueBuf, RES_CODE_LEN, nullptr);
		_area.parentid = (TCHAR*)ValueBuf;
		if (_area.parentid == station.id)		// 为车站下的区域
		{
			memset(ValueBuf, 0, RES_CODE_LEN);
			m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "id", ValueBuf, RES_CODE_LEN, nullptr);
			_area.id = (TCHAR*)ValueBuf;

			memset(ValueBuf, 0, RES_CODE_LEN);
			m_JsdCCTV->ParseOrganizationInfo((TCHAR*)Buf, 1, i, "name", ValueBuf, RES_CODE_LEN, nullptr);
			_area.name = (TCHAR*)ValueBuf;

			vecAreas.push_back(_area);
		}
	}

	for (auto ele : vecAreas)
		m_AreaComboBox.AddOneArea(ele);

	m_AreaComboBox.SetCurSel(0);

	delete[] Buf;
	delete[] ValueBuf;
}


void MainDialog::ShowCameraList()
{
	TypeCameraCallback stCameraCallback;
	m_JsdCCTV->ListObjects(CWALKNET_TYPE_CAMERA, nullptr, nullptr, ListObject_CallBack, (void*)&stCameraCallback);

	int size = stCameraCallback.m_vecCameras.size();
	for (int i = 0; i < size; ++i)
	{
		m_CameraComboBox.AddOneCamera(stCameraCallback.m_vecCameras[i]);
	}
}


void MainDialog::ShowDisplayModeList()
{
	/* 获取显示模式 */
	int _modeCount = GetPrivateProfileInt(SECTION_DISPLAYMODE, CONFIG_KEY_MODECOUNT, DEFAULT_INT, m_ConfigFilePath);
	int ModeCount = _modeCount > MAX_DISPLAYMODE_CNT ? MAX_DISPLAYMODE_CNT : _modeCount;
	for (int i = 0; i < ModeCount; ++i)
	{
		CString tempKeyName, tempKeyCamera;
		TCHAR tempName[NAME_LEN] = { 0 };
		TCHAR tempCamera[RES_CODE_LEN] = { 0 };
		TypeDisplayMode* _displayMode = new TypeDisplayMode;
		tempKeyName.Format("%s%d", CONFIG_KEY_MODENAME_PREFIX, i);
		tempKeyCamera.Format("%s%d", CONFIG_KEY_MODECAMERA_PREFIX, i);

		GetPrivateProfileString(SECTION_DISPLAYMODE, tempKeyName, DEFAULT_STR, tempName, sizeof(tempName), m_ConfigFilePath);
		strcpy_s(_displayMode->ModeName, NAME_LEN, tempName);

		GetPrivateProfileString(SECTION_DISPLAYMODE, tempKeyCamera, DEFAULT_STR, tempCamera, sizeof(tempCamera), m_ConfigFilePath);
		std::vector<std::string> vecCameraList = SplitString(tempCamera, ',');

		int CameraNum = vecCameraList.size() > MAX_DISPLAY_CNT ? MAX_DISPLAY_CNT : vecCameraList.size();
		for (int j = 0; j < CameraNum; ++j)
		{
			strcpy_s(_displayMode->ModeCamera[j], RES_CODE_LEN, vecCameraList[j].c_str());
		}
		_displayMode->CameraNumber = CameraNum;

		m_DisplayComboBox.AddOneDisplayMode((*_displayMode));
		delete _displayMode;
	}
}


void MainDialog::ShowSwitchList()
{

}


bool MainDialog::Login()
{
	if (m_JsdCCTV->Login())
	{
		m_IsLogin = true;
	}

	return m_IsLogin;
}


void MainDialog::OnBnClickedButtonAdddspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void MainDialog::OnBnClickedButtonDeldspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void MainDialog::OnBnClickedButtonModifydspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void MainDialog::OnBnClickedButtonStartdspmode()
{
	// TODO: 在此添加控件通知处理程序代码
	TypeDisplayMode _curMode = m_DisplayComboBox.GetCurSelDisplayMode();
	int _cameraNum = _curMode.CameraNumber;

	m_MainDialogProgress.SetPos(0);
	m_MainDialogProgress.ShowWindow(TRUE);
	SetProgressCtrlText(800, "正在调用显示模式【%s】，摄像头总数：%d", _curMode.ModeName, _cameraNum);

	if (_cameraNum == 1)
	{
		m_DisplayControl->OneDisplayLayout();
	}
	else if (_cameraNum > 1 && _cameraNum <= 4)
	{
		m_DisplayControl->FourDisplayLayout();
	}
	else if (_cameraNum > 4 && _cameraNum <= 9)
	{
		m_DisplayControl->NineDisplayLayout();
	}
	else if (_cameraNum > 9 && _cameraNum <= 16)
	{
		m_DisplayControl->SixteenDisplayLayout();
	}

	m_MainDialogProgress.SetPos(20);

	int Pos = 20;
	int Step = (int)(80 / _cameraNum);
	for (int i = 0; i < _cameraNum; ++i)
	{
		Pos += Step;
		TCHAR* AvPath = _curMode.ModeCamera[i];
		m_DisplayControl->StopMonitor(i);
		if (!m_DisplayControl->StartMonitor(AvPath, i))
		{
			// LOG
		}
		m_MainDialogProgress.SetPos(Pos);
	}

	m_MainDialogProgress.SetPos(100);
	SetProgressCtrlText(500, "显示模式调用完成");
	m_MainDialogProgress.ShowWindow(FALSE);
}


void MainDialog::OnBnClickedButtonAddswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void MainDialog::OnBnClickedButtonDelswitchmode()
{
	// TODO: 在此添加控件通知处理程序代码
	
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
	TestFlag++;

	if (!m_IsLogin && m_IsFirstLogin && TestFlag > 3)
	{
		m_MainDialogProgress.ShowWindow(TRUE);
		m_MainDialogProgress.SetPos(0);
		SetProgressCtrlText(800, "登录 DCS 服务器...");
		bool flag = Login();
		if (flag == true)
		{
			SetProgressCtrlText(800, "登录成功");
		}
		else
		{
			SetProgressCtrlText(800, "登录失败");
		}

		m_MainDialogProgress.SetPos(30);
		SetProgressCtrlText(800, "获取车站列表...");
		ShowStationList();

		m_MainDialogProgress.SetPos(50);
		SetProgressCtrlText(800, "获取区域列表...");
		ShowAreaList();

		m_MainDialogProgress.SetPos(70);
		SetProgressCtrlText(800, "获取摄像头列表...");
		ShowCameraList();

		m_MainDialogProgress.SetPos(80);
		SetProgressCtrlText(800, "读取显示模式...");
		ShowDisplayModeList();

		m_MainDialogProgress.SetPos(90);
		SetProgressCtrlText(800, "获取轮切列表...");
		ShowSwitchList();

		m_IsFirstLogin = false;

		m_MainDialogProgress.SetPos(100);
		SetProgressCtrlText(800, "完成");
		SetProgressCtrlText(0, "");
		m_MainDialogProgress.SetPos(0);
		m_MainDialogProgress.ShowWindow(FALSE);
	}

	SetTimer(1, 2000, nullptr);
	CDialog::OnTimer(nIDEvent);
}


void MainDialog::InitCCTV()
{
	m_JsdCCTV = new JSDCCTV(m_DCSUserInfo);
	CString JsdLogFile = m_LogFilePath;
	JsdLogFile.Append("\\JSDCCTV_LOG.LOG");
	m_JsdCCTV->SetLogFile(JsdLogFile);

	if (strlen(m_DCRUserInfo.IPAddress))
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
	CString tempConfigPath = tempWorkPath + "\\" + CONFIG_FILE;
	strcpy_s(m_LogFilePath, FILE_PATH_LEN, tempLogPath);
	strcpy_s(m_ConfigFilePath, FILE_PATH_LEN, tempConfigPath);
}


void MainDialog::SetProgressCtrlText(int HoldMiliseconds, const char* const _Format, ...)
{ 
	va_list _args;
	va_start(_args, _Format);
	int _len = _vscprintf(_Format, _args) + 1;
	char* _buffer = new char[_len * sizeof(char)];
	vsnprintf(_buffer, _len * sizeof(char), _Format, _args);
	va_end(_args);

	m_MainDialogProgressText.SetWindowText(_buffer);
	Sleep(HoldMiliseconds); 

	delete[] _buffer;
}
