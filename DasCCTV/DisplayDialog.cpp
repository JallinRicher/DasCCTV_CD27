// DisplayDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "DisplayDialog.h"
#include "DisplayControlDialog.h"


// DisplayDialog 对话框

IMPLEMENT_DYNAMIC(DisplayDialog, CDialog)

DisplayDialog::DisplayDialog(DisplayControlDialog* ParentDialog, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLAYDIALOG, pParent), m_ParentDialog(ParentDialog)
{
	InitVariable();
}


DisplayDialog::~DisplayDialog()
{
}


void DisplayDialog::InitVariable()
{
	memset(m_DeviceResCode, 0, RES_CODE_LEN);
	memset(m_DeviceName, 0, NAME_LEN);
	m_DeviceID = INVALID_VALUE;
	m_DeviceType = INVALID_VALUE;
	m_DeviceSubType = INVALID_VALUE;
	m_DeviceStatus = INVALID_VALUE;
	m_RegionID = INVALID_VALUE;
	memset(m_RegionResCode, 0, RES_CODE_LEN);
#ifdef MULTI_SUBWAY_ROUTE
	m_Route = INVALID_VALUE;
#endif

	m_DisplayState = IS_BLANK;
	m_IsOpenSound = false;
	m_SoundChannel = INVALID_VALUE;
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


void DisplayDialog::SetDisplayState(int State)
{
	if (State < IS_LIVING || State > IS_SNATCHING)
	{
		return;
	}
	m_DisplayState = State;
}


int DisplayDialog::GetDisplayState() const
{
	return m_DisplayState;
}


DisplayDeviceInfo DisplayDialog::GetDisplayInfo() const
{
	DisplayDeviceInfo Retval;
	wcsncpy_s(Retval.DeviceResCode, sizeof(Retval.DeviceResCode), m_DeviceResCode, sizeof(Retval.DeviceResCode));
	wcsncpy_s(Retval.DeviceName, sizeof(Retval.DeviceName), m_DeviceName, sizeof(Retval.DeviceName));
	Retval.DeviceID = m_DeviceID;
	Retval.DeviceType = m_DeviceType;
	Retval.DeviceSubType = m_DeviceSubType;
	Retval.DeviceStatus = m_DeviceStatus;
	Retval.RegionID = m_RegionID;
	wcsncpy_s(Retval.RegionResCode, sizeof(Retval.RegionResCode), m_RegionResCode, sizeof(Retval.RegionResCode));

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


void DisplayDialog::SetDeviceResCode(const wchar_t* DeviceResCode)
{
	if (DeviceResCode == nullptr)
	{
		return;
	}
	wcsncpy_s(m_DeviceResCode, sizeof(m_DeviceResCode), DeviceResCode, sizeof(m_DeviceResCode));
}


void DisplayDialog::SetDeviceName(const wchar_t* DeviceName)
{
	if (DeviceName == nullptr)
	{
		return;
	}
	wcsncpy_s(m_DeviceName, sizeof(m_DeviceName), DeviceName, sizeof(m_DeviceName));
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


void DisplayDialog::SetRegionResCode(const wchar_t* RegionResCode)
{
	if (RegionResCode == nullptr)
	{
		return;
	}
	wcsncpy_s(m_RegionResCode, sizeof(m_RegionResCode), RegionResCode, sizeof(m_RegionResCode));
}


int DisplayDialog::GetSoundChannel() const
{
	return m_SoundChannel;
}


void DisplayDialog::GetDeviceResCode(wchar_t* Retval) const
{
	wcsncpy_s(Retval, sizeof(Retval), m_DeviceResCode, sizeof(Retval));
}


void DisplayDialog::GetDeviceName(wchar_t* Retval) const
{
	wcsncpy_s(Retval, sizeof(Retval), m_DeviceName, sizeof(Retval));
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


void DisplayDialog::GetRegionResCode(wchar_t* Retval) const
{
	wcsncpy_s(Retval, sizeof(Retval), m_RegionResCode, sizeof(Retval));
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
