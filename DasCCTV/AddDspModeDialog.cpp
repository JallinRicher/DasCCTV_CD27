// AddDspModeDialog.cpp: 实现文件
//

#include "pch.h"
#include "DasCCTV.h"
#include "afxdialogex.h"
#include "AddDspModeDialog.h"


// AddDspModeDialog 对话框

IMPLEMENT_DYNAMIC(AddDspModeDialog, CDialog)

AddDspModeDialog::AddDspModeDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADDDSPMODEDIALOG, pParent)
{

}

AddDspModeDialog::~AddDspModeDialog()
{
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
END_MESSAGE_MAP()


// AddDspModeDialog 消息处理程序
