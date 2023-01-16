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
	DDX_Control(pDX, IDC_COMBO1, m_StationComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_AreaComboBox);
	DDX_Control(pDX, IDC_LIST_CAMERALIST, m_CameraList);
	DDX_Control(pDX, IDC_LIST_DSPMODELIST, m_DspModeList);
	DDX_Control(pDX, IDC_BUTTON_ADDTODSPMODE, m_AddToDspModeButton);
	DDX_Control(pDX, IDC_BUTTON_REMOVEFROMDSPMODE, m_RemoveFromDspModeButton);
}


BEGIN_MESSAGE_MAP(AddDspModeDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDTODSPMODE, &AddDspModeDialog::OnBnClickedButtonAddtodspmode)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFROMDSPMODE, &AddDspModeDialog::OnBnClickedButtonRemovefromdspmode)
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
	TypeCameraCallback stCameraCallback;
	m_JsdCCTV->ListObjects(CWALKNET_TYPE_CAMERA, nullptr, nullptr, ListObject_CallBack, (void*)&stCameraCallback);

	m_CameraList.SetRedraw(FALSE);
	int size = stCameraCallback.m_vecCameras.size();
	for (int i = 0; i < size; ++i)
	{
		if (stCameraCallback.m_vecCameras[i].ptzEnable == "1")
		{
			int nRow = m_CameraList.InsertItem(i, stCameraCallback.m_vecCameras[i].name);
			m_CameraList.SetItemText(nRow, 0, stCameraCallback.m_vecCameras[i].name);
			m_CameraList.SetItemText(nRow, 1, _T("云台"));
			m_CameraList.SetItemText(nRow, 2, stCameraCallback.m_vecCameras[i].rtspUrl);
		}
		else
		{
			int nRow = m_CameraList.InsertItem(i, stCameraCallback.m_vecCameras[i].name);
			m_CameraList.SetItemText(nRow, 1, _T("非云台"));
			m_CameraList.SetItemText(nRow, 2, stCameraCallback.m_vecCameras[i].rtspUrl);
		}
	}

	m_CameraList.SetRedraw(TRUE);
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
