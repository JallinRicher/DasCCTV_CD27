// DasCCTVCtrl.cpp : DasCCTVCtrl ActiveX 控件类的实现。

#include "pch.h"
#include "framework.h"
#include "DasCCTV.h"
#include "DasCCTVCtrl.h"
#include "DasCCTVPropPage.h"
#include "afxdialogex.h"
#include "MainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(DasCCTVCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(DasCCTVCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(DasCCTVCtrl, COleControl)
	DISP_FUNCTION_ID(DasCCTVCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(DasCCTVCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(DasCCTVCtrl, 1)
	PROPPAGEID(DasCCTVPropPage::guid)
END_PROPPAGEIDS(DasCCTVCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(DasCCTVCtrl, "MFCACTIVEXCONTRO.DasCCTVCtrl.1",
	0x3f9c045b,0x43db,0x4280,0xb5,0x68,0x52,0x75,0xb0,0xfe,0x52,0xa2)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(DasCCTVCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DDasCCTV = {0xfb680a1d,0xccae,0x4810,{0x86,0xc3,0x24,0x2b,0x8d,0xae,0x9a,0x76}};
const IID IID_DDasCCTVEvents = {0x47e08345,0x8e44,0x4ff0,{0x84,0xd1,0x97,0x79,0xeb,0x70,0xcb,0x83}};

// 控件类型信息

static const DWORD _dwDasCCTVOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(DasCCTVCtrl, IDS_DASCCTV, _dwDasCCTVOleMisc)

// DasCCTVCtrl::DasCCTVCtrlFactory::UpdateRegistry -
// 添加或移除 DasCCTVCtrl 的系统注册表项

BOOL DasCCTVCtrl::DasCCTVCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DASCCTV,
			IDB_DASCCTV,
			afxRegApartmentThreading,
			_dwDasCCTVOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// DasCCTVCtrl::DasCCTVCtrl - 构造函数

DasCCTVCtrl::DasCCTVCtrl()
{
	InitializeIIDs(&IID_DDasCCTV, &IID_DDasCCTVEvents);
	// TODO:  在此初始化控件的实例数据。
}

// DasCCTVCtrl::~DasCCTVCtrl - 析构函数

DasCCTVCtrl::~DasCCTVCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// DasCCTVCtrl::OnDraw - 绘图函数

void DasCCTVCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// DasCCTVCtrl::DoPropExchange - 持久性支持

void DasCCTVCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// DasCCTVCtrl::OnResetState - 将控件重置为默认状态

void DasCCTVCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// DasCCTVCtrl::AboutBox - 向用户显示“关于”框

void DasCCTVCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_DASCCTV);
	dlgAbout.DoModal();
}


// DasCCTVCtrl 消息处理程序

int DasCCTVCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_MainDialog.Create(IDD_MAINDIALOG, this);
	m_MainDialog.ShowWindow(SW_SHOW);
	return 0;
}
