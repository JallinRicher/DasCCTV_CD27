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
	memset(m_DeviceResCode, 0, RES_CODE_LEN);
	memset(m_DeviceName, 0, NAME_LEN);
	m_DeviceID = INVALID_VALUE;
	m_DeviceType = INVALID_VALUE;
	m_DeviceSubType = INVALID_VALUE;
	m_DeviceStatus = INVALID_VALUE;
	m_RegionID = INVALID_VALUE;
	memset(m_RegionResCode, 0, RES_CODE_LEN);

	m_DisplayState = IS_BLANK;
	m_IsOpenSound = false;
	m_SoundChannel = INVALID_VALUE;
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


DisplayDeviceInfo DisplayDialog::GetDisplayInfo() const
{
	DisplayDeviceInfo Retval;
	strcpy_s(Retval.DeviceResCode, sizeof(Retval.DeviceResCode), m_DeviceResCode);
	strcpy_s(Retval.DeviceName, sizeof(Retval.DeviceName), m_DeviceName);
	Retval.DeviceID = m_DeviceID;
	Retval.DeviceType = m_DeviceType;
	Retval.DeviceSubType = m_DeviceSubType;
	Retval.DeviceStatus = m_DeviceStatus;
	Retval.RegionID = m_RegionID;
	strcpy_s(Retval.RegionResCode, sizeof(Retval.RegionResCode), m_RegionResCode);

	return Retval;
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


void DisplayDialog::SetDeviceResCode(const TCHAR* DeviceResCode)
{
	if (DeviceResCode == nullptr)
	{
		return;
	}
	strcpy_s(m_DeviceResCode, sizeof(m_DeviceResCode), DeviceResCode);
}


void DisplayDialog::SetDeviceName(const TCHAR* DeviceName)
{
	if (DeviceName == nullptr)
	{
		return;
	}
	strcpy_s(m_DeviceName, sizeof(m_DeviceName), DeviceName);
}


void DisplayDialog::SetDeviceID(long DeviceID)
{
	m_DeviceID = DeviceID;
}


void DisplayDialog::SetDeviceType(int DeviceType)
{
	m_DeviceType = DeviceType;
}


void DisplayDialog::SetDeviceSubType(int DeviceSubType)
{
	m_DeviceSubType = DeviceSubType;
}


void DisplayDialog::SetDeviceStatus(int DeviceStatus)
{
	m_DeviceStatus = DeviceStatus;
}


void DisplayDialog::SetRegionID(long RegionID)
{
	m_RegionID = RegionID;
}


void DisplayDialog::SetRegionResCode(const TCHAR* RegionResCode)
{
	if (RegionResCode == nullptr)
	{
		return;
	}
	strcpy_s(m_RegionResCode, sizeof(m_RegionResCode), RegionResCode);
}


int DisplayDialog::GetSoundChannel() const
{
	return m_SoundChannel;
}


void DisplayDialog::GetDeviceResCode(TCHAR* Retval) const
{
	strcpy_s(Retval, sizeof(Retval), m_DeviceResCode);
}


void DisplayDialog::GetDeviceName(TCHAR* Retval) const
{
	strcpy_s(Retval, sizeof(Retval), m_DeviceName);
}


long DisplayDialog::GetDeviceID() const
{
	return m_DeviceID;
}


int DisplayDialog::GetDeviceType() const
{
	return m_DeviceType;
}


int DisplayDialog::GetDeviceSubType() const
{
	return m_DeviceSubType;
}


int DisplayDialog::GetDeviceStatus() const
{
	return m_DeviceStatus;
}


long DisplayDialog::GetRegionID() const
{
	return m_RegionID;
}


void DisplayDialog::GetRegionResCode(TCHAR* Retval) const
{
	strcpy_s(Retval, sizeof(Retval), m_RegionResCode);
}


#ifdef MULTI_SUBWAY_ROUTE
int DisplayDialog::GetRoute() const
{
	return m_Route;
}
#endif


void DisplayDialog::OpenSound(int SoundChannel)
{
	m_SoundChannel = SoundChannel;
	m_IsOpenSound = true;
}


bool DisplayDialog::IsOpenSound() const
{
	return m_IsOpenSound;
}
