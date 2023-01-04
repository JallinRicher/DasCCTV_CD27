#pragma once
#include "MainDialog.h"
// DasCCTVCtrl.h : DasCCTVCtrl ActiveX 控件类的声明。


// DasCCTVCtrl : 请参阅 DasCCTVCtrl.cpp 了解实现。

class DasCCTVCtrl : public COleControl
{
	DECLARE_DYNCREATE(DasCCTVCtrl)

// 构造函数
public:
	DasCCTVCtrl();
	
// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~DasCCTVCtrl();

	DECLARE_OLECREATE_EX(DasCCTVCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(DasCCTVCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(DasCCTVCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(DasCCTVCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

private:
	MainDialog m_MainDialog;

// 调度和事件 ID
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

