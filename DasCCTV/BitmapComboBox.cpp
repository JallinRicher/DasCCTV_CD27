#include "pch.h"
#include "BitmapComboBox.h"

BitmapComboBox::BitmapComboBox() : CComboBox()
{
	memset(m_DeviceName, 0, MAX_COMBO_ITEM_CNT * sizeof(m_DeviceName[0]));
	memset(m_DeviceResCode, 0, MAX_COMBO_ITEM_CNT * sizeof(m_DeviceResCode[0]));
	for (int i = 0; i < MAX_COMBO_ITEM_CNT; ++i)
	{
		m_DeviceID[i] = INVALID_VALUE;
		m_DeviceType[i] = INVALID_VALUE;
		m_DeviceSubType[i] = INVALID_VALUE;
		m_DeviceStatus[i] = INVALID_VALUE;
	}
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


void BitmapComboBox::SetDeviceResCode(const char* DeviceResCode)
{
	int index = GetCount();
	if (!DeviceResCode || index < 0 || index >= MAX_COMBO_ITEM_CNT)
	{
		return;
	}
	
	strcpy_s(m_DeviceResCode[index], RES_CODE_LEN, DeviceResCode);
}


void BitmapComboBox::SetDeviceName(const char* DeviceName)
{
	int index = GetCount();
	if (!DeviceName || index < 0 || index >= MAX_COMBO_ITEM_CNT)
	{
		return;
	}

	strcpy_s(m_DeviceName[index], NAME_LEN, DeviceName);
}


void BitmapComboBox::GetCurSelDeviceResCode(char* Retval) const
{
	int index = GetCurSel();
	strcpy_s(Retval, RES_CODE_LEN, m_DeviceResCode[index]);
}


void BitmapComboBox::GetCurSelDeviceName(char* Retval) const
{
	int index = GetCurSel();
	strcpy_s(Retval, NAME_LEN, m_DeviceName[index]);
}


void BitmapComboBox::SetDeviceType(int DeviceType)
{
	int index = GetCount();
	if (index < 0 || index >= MAX_COMBO_ITEM_CNT)
	{
		return;
	}

	m_DeviceType[index] = DeviceType;
}


void BitmapComboBox::SetDeviceStatus(int DeviceStatus)
{
	int index = GetCount();
	if (index < 0 || index >= MAX_COMBO_ITEM_CNT)
	{
		return;
	}

	m_DeviceStatus[index] = DeviceStatus;
}


int BitmapComboBox::GetCurSelDeviceType() const
{
	int index = GetCount();
	return m_DeviceType[index];
}


int BitmapComboBox::GetCurSelDeviceStatus() const
{
	int index = GetCount();
	return m_DeviceStatus[index];
}


void BitmapComboBox::SetDeviceID(long DeviceID)
{
	int index = GetCount();
	m_DeviceID[index] = DeviceID;
}


void BitmapComboBox::SetDeviceSubType(int DeviceSubType)
{
	int index = GetCount();
	m_DeviceSubType[index] = DeviceSubType;
}


long BitmapComboBox::GetCurSelDeviceID() const
{
	int index = GetCurSel();
	return m_DeviceID[index];
}


int BitmapComboBox::GetCurSelDeviceSubType() const
{
	int index = GetCurSel();
	return m_DeviceSubType[index];
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
