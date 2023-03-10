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
	m_vecStations.clear();
	m_vecAreas.clear();
	m_vecDevices.clear();
	m_vecCameras.clear();
	m_vecMonitors.clear();
	m_vecAudios.clear();
	m_vecDisplayModes.clear();

	CComboBox::Clear();
}


void BitmapComboBox::AddOneRow(LPCTSTR RowName)
{
	if (RowName == nullptr)
	{
		return;
	}

	AddString(RowName);
}


void BitmapComboBox::DeleteCurSelRow()
{
	int index = GetCurSel();
	DelOneData(index);
	DeleteString(index);
}


void BitmapComboBox::DelOneData(int index)
{
	int size = 0;
	switch (m_ComboBoxType)
	{
	case CWALKNET_TYPE_GATEWAY: 
		size = m_vecStations.size();
		for (int i = index; i < size - 1; ++i)
			m_vecStations[i] = m_vecStations[i + 1];
		m_vecStations.pop_back();
		break;
	case CWALKNET_TYPE_DEVICE: 
		size = m_vecDevices.size();
		for (int i = index; i < size - 1; ++i)
			m_vecDevices[i] = m_vecDevices[i + 1];
		m_vecDevices.pop_back();
		break;
	case CWALKNET_TYPE_CAMERA:
		size = m_vecCameras.size();
		for (int i = index; i < size - 1; ++i)
			m_vecCameras[i] = m_vecCameras[i + 1];
		m_vecCameras.pop_back();
		break;
	case CWALKNET_TYPE_MONITOR:
		size = m_vecMonitors.size();
		for (int i = index; i < size - 1; ++i)
			m_vecMonitors[i] = m_vecMonitors[i + 1];
		m_vecMonitors.pop_back();
		break;
	case CWALKNET_TYPE_AUDIO:
		size = m_vecAudios.size();
		for (int i = index; i < size - 1; ++i)
			m_vecAudios[i] = m_vecAudios[i + 1];
		m_vecAudios.pop_back();
		break;
	case CWALKNET_TYPE_DISPLAY:
		size = m_vecDisplayModes.size();
		for (int i = index; i < size - 1; ++i)
			m_vecDisplayModes[i] = m_vecDisplayModes[i + 1];
		m_vecDisplayModes.pop_back();
		break;
	case CWALKNET_TYPE_SWITCH: break;
	default: break;
	}
}


void BitmapComboBox::AddOneStation(const TypeStation& Station)
{
	AddOneRow(Station.name);
	m_vecStations.push_back(Station);
}


void BitmapComboBox::AddOneDevice(const TypeDevice& Device)
{
	AddOneRow(Device.name);
	m_vecDevices.push_back(Device);
}


void BitmapComboBox::AddOneCamera(const TypeCamera& Camera)
{
	AddOneRow(Camera.name);
	m_vecCameras.push_back(Camera);
}


void BitmapComboBox::AddOneMonitor(const TypeMonitor& Monitor)
{
	AddOneRow(Monitor.name);
	m_vecMonitors.push_back(Monitor);
}


void BitmapComboBox::AddOneAudio(const TypeAudio& Audio)
{
	AddOneRow(Audio.name);
	m_vecAudios.push_back(Audio);
}


void BitmapComboBox::AddOneDisplayMode(const TypeDisplayMode DisplayMode)
{
	AddOneRow(DisplayMode.ModeName);
	m_vecDisplayModes.push_back(DisplayMode);
}


void BitmapComboBox::AddOneArea(const TypeArea& Area)
{
	AddOneRow(Area.name);
	m_vecAreas.push_back(Area);
}
