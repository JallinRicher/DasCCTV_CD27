#include "pch.h"
#include "BitmapComboBox.h"


void CameraType::DelOneData(int index)
{
	int size = m_vecDatas.size();
	for (int i = index; i < size - 1; ++i)
	{
		m_vecDatas[i] = m_vecDatas[i + 1];
	}

	m_vecDatas.pop_back();
}


void GatewayType::DelOneData(int index)
{
	int size = m_vecDatas.size();
	for (int i = index; i < size - 1; ++i)
	{
		m_vecDatas[i] = m_vecDatas[i + 1];
	}

	m_vecDatas.pop_back();
}


void DeviceType::DelOneData(int index)
{
	int size = m_vecDatas.size();
	for (int i = index; i < size - 1; ++i)
	{
		m_vecDatas[i] = m_vecDatas[i + 1];
	}

	m_vecDatas.pop_back();
}



void AudioType::DelOneData(int index)
{
	int size = m_vecDatas.size();
	for (int i = index; i < size - 1; ++i)
	{
		m_vecDatas[i] = m_vecDatas[i + 1];
	}

	m_vecDatas.pop_back();
}


void MonitorType::DelOneData(int index)
{
	int size = m_vecDatas.size();
	for (int i = index; i < size - 1; ++i)
	{
		m_vecDatas[i] = m_vecDatas[i + 1];
	}

	m_vecDatas.pop_back();
}



BitmapComboBox::BitmapComboBox() : CComboBox(), m_Data(nullptr)
{

}


void BitmapComboBox::SetComboBoxType(CWALKNetObjectType ObjType)
{
	m_ComboBoxType = ObjType;
	switch (ObjType)
	{
	case CWALKNET_TYPE_UNKNOWN: break;
	case CWALKNET_TYPE_GATEWAY:
		m_Data = new GatewayType;
		break;
	case CWALKNET_TYPE_DEVICE:
		m_Data = new DeviceType;
		break;
	case CWALKNET_TYPE_CAMERA:
		m_Data = new CameraType;
		break;
	case CWALKNET_TYPE_MONITOR:
		m_Data = new MonitorType;
		break;
	case CWALKNET_TYPE_AUDIO:
		m_Data = new AudioType;
		break;
	case CWALKNET_TYPE_TRUNKIN: break;
	case CWALKNET_TYPE_TRUNKOUT: break;
	case CWALKNET_TYPE_ALARMIN: break;
	case CWALKNET_TYPE_ALARMOUT: break;
	default: break;
	}
}


BitmapComboBox::~BitmapComboBox()
{
	if (m_Data)
	{
		delete m_Data;
		m_Data = nullptr;
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
