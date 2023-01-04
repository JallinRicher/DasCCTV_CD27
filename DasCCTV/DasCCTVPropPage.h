#pragma once

// DasCCTVPropPage.h: DasCCTVPropPage 属性页类的声明。


// DasCCTVPropPage : 请参阅 DasCCTVPropPage.cpp 了解实现。

class DasCCTVPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(DasCCTVPropPage)
	DECLARE_OLECREATE_EX(DasCCTVPropPage)

// 构造函数
public:
	DasCCTVPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_DASCCTV };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

