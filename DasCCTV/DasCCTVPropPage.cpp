// DasCCTVPropPage.cpp : DasCCTVPropPage 属性页类的实现。

#include "pch.h"
#include "framework.h"
#include "DasCCTV.h"
#include "DasCCTVPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(DasCCTVPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(DasCCTVPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(DasCCTVPropPage, "MFCACTIVEXCONT.DasCCTVPropPage.1",
	0x25114f07,0x4eb8,0x4d6f,0x9f,0x82,0x0b,0xb1,0x4f,0xad,0xff,0xcb)

// DasCCTVPropPage::DasCCTVPropPageFactory::UpdateRegistry -
// 添加或移除 DasCCTVPropPage 的系统注册表项

BOOL DasCCTVPropPage::DasCCTVPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DASCCTV_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// DasCCTVPropPage::DasCCTVPropPage - 构造函数

DasCCTVPropPage::DasCCTVPropPage() :
	COlePropertyPage(IDD, IDS_DASCCTV_PPG_CAPTION)
{
}

// DasCCTVPropPage::DoDataExchange - 在页和属性间移动数据

void DasCCTVPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// DasCCTVPropPage 消息处理程序
