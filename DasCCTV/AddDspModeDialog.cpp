// AddDspModeDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "MainDialog.h"
#include "AddDspModeDialog.h"


// AddDspModeDialog 对话框

IMPLEMENT_DYNAMIC(AddDspModeDialog, CDialog)

AddDspModeDialog::AddDspModeDialog(MainDialog* ParentDialog, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADDDSPMODEDIALOG, pParent), m_ParentDialog(ParentDialog)
{
	if (m_ParentDialog && m_ParentDialog->m_JsdCCTV)
	{
		m_JsdCCTV = m_ParentDialog->m_JsdCCTV;
	}
	else
	{
		m_JsdCCTV = nullptr;
	}

}

AddDspModeDialog::~AddDspModeDialog()
{
	m_ParentDialog = nullptr;
	m_JsdCCTV = nullptr;
}

void AddDspModeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CAMERALIST, m_CameraList);
	DDX_Control(pDX, IDC_LIST_DSPMODELIST, m_DspModeList);
	DDX_Control(pDX, IDC_BUTTON_ADDTODSPMODE, m_AddToDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_REMOVEFROMDSPMODE, m_RemoveFromDspModeButton);
	DDX_Control(pDX, IDC_EDIT_MODENAME, m_ModeNameEdit);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_TipsStatic);
	DDX_Control(pDX, IDC_COMBO_ADDDSP_STATION, m_StationComboBox);
	DDX_Control(pDX, IDC_COMBO_ADDDSP_AREA, m_AreaComboBox);
}


BEGIN_MESSAGE_MAP(AddDspModeDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDTODSPMODE, &AddDspModeDialog::OnBnClickedButtonAddtodspmode)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFROMDSPMODE, &AddDspModeDialog::OnBnClickedButtonRemovefromdspmode)
	ON_BN_CLICKED(IDOK, &AddDspModeDialog::OnBnClickedOk)
END_MESSAGE_MAP()


void AddDspModeDialog::AddOneStation(const TypeStation& Stataion)
{
	m_StationComboBox.AddOneStation(Stataion);
}


void AddDspModeDialog::AddOneArea(const TypeArea& Area)
{
	m_AreaComboBox.AddOneArea(Area);
}


void AddDspModeDialog::ShowCameraList()
{
	m_JsdCCTV->ListObjects(CWALKNET_TYPE_CAMERA, nullptr, nullptr, nullptr, nullptr);
}


BOOL AddDspModeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUIFrame();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void AddDspModeDialog::InitUIFrame()
{



	m_CameraList.InsertColumn(0, _T("摄像头标题"), LVCFMT_CENTER, 40);
	m_CameraList.InsertColumn(1, _T("摄像头类型"), LVCFMT_CENTER, 80);
	m_CameraList.InsertColumn(2, _T("资源编码"), LVCFMT_CENTER, 40);
	DWORD dwCamStyle = m_CameraList.GetExtendedStyle();
	dwCamStyle |= LVS_EX_FULLROWSELECT;
	dwCamStyle |= LVS_EX_GRIDLINES;
	dwCamStyle |= LVS_SINGLESEL;
	m_CameraList.SetExtendedStyle(dwCamStyle);

	
	m_DspModeList.InsertColumn(0, _T("摄像头标题"), LVCFMT_CENTER, 40);
	m_DspModeList.InsertColumn(1, _T("摄像头类型"), LVCFMT_CENTER, 80);
	m_DspModeList.InsertColumn(2, _T("资源编码"), LVCFMT_CENTER, 40);
	DWORD dwModStyle = m_DspModeList.GetExtendedStyle();
	dwModStyle |= LVS_EX_FULLROWSELECT;
	dwModStyle |= LVS_EX_GRIDLINES;
	dwModStyle |= LVS_SINGLESEL;
	m_DspModeList.SetExtendedStyle(dwModStyle);
}


BOOL AddDspModeDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	NMHEADER* pNMHeader = (NMHEADER*)lParam;
	if ((pNMHeader->hdr.code == HDN_BEGINTRACKW) || (pNMHeader->hdr.code == HDN_DIVIDERDBLCLICKW))
	{
		*pResult = TRUE;
		return TRUE;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}


void AddDspModeDialog::OnBnClickedButtonAddtodspmode()
{
	int SelectRow = m_CameraList.GetSelectionMark();
	if (SelectRow == -1)
	{
		// LOG
		return;
	}

	CString CameraName = m_CameraList.GetItemText(SelectRow, 0);
	CString CameraType = m_CameraList.GetItemText(SelectRow, 1);
	CString CameraUrl = m_CameraList.GetItemText(SelectRow, 2);
	
	int nRow = m_DspModeList.GetItemCount();
	int _dspModeRow = m_DspModeList.InsertItem(nRow, CameraName);
	m_DspModeList.SetItemText(_dspModeRow, 0, CameraName);
	m_DspModeList.SetItemText(_dspModeRow, 1, CameraType);
	m_DspModeList.SetItemText(_dspModeRow, 2, CameraUrl);
}


void AddDspModeDialog::OnBnClickedButtonRemovefromdspmode()
{
	int SelectRow = m_DspModeList.GetSelectionMark();
	m_DspModeList.DeleteItem(SelectRow);
}


void AddDspModeDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString _modeName;
	m_ModeNameEdit.GetWindowTextA(_modeName);
	if (_modeName.IsEmpty())
	{
		m_TipsStatic.SetWindowTextA(_T("提示：请输入模式名"));
		return;
	}

	if (m_DspModeList.GetItemCount() == 0)
	{
		m_TipsStatic.SetWindowTextA(_T("提示：请选择要加入模式的摄像机"));
		return;
	}

	m_TipsStatic.SetWindowTextA(_T(""));
	CDialog::OnOK();
}
