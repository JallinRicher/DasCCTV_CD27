#include "pch.h"
#include "BitmapComboBox.h"

BitmapComboBox::BitmapComboBox() : CComboBox()
{

}


BitmapComboBox::~BitmapComboBox()
{

}


BEGIN_MESSAGE_MAP(BitmapComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &BitmapComboBox::OnCbnDropdown)
END_MESSAGE_MAP()


void BitmapComboBox::OnCbnDropdown()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	GetClientRect(&rc);
	SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height() + 100, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
}


void BitmapComboBox::ClearAllContent()
{
	CComboBox::Clear();
}


void BitmapComboBox::AddOneRow(const char* RowName)
{
	if (RowName == nullptr)
	{
		return;
	}
	
	int _tempLen = MultiByteToWideChar(CP_ACP, 0, RowName, strlen(RowName), nullptr, 0);
	TCHAR* _tempName = new wchar_t[_tempLen + 1];
	memset(_tempName, 0, 2 * _tempLen + 2);
	MultiByteToWideChar(CP_ACP, 0, RowName, strlen(RowName), _tempName, _tempLen);
	AddString(_tempName);
	delete[] _tempName;
}


void BitmapComboBox::DeleteCurSelRow()
{
	int index = GetCurSel();
	DeleteString(index);
}
