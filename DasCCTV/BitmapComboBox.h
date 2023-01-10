#pragma once
#include <afxwin.h>
#include "cwalk_netsdk.h"

class BitmapComboBox : public CComboBox
{
public:
    DECLARE_MESSAGE_MAP()

public:
    explicit BitmapComboBox();
    ~BitmapComboBox();
    
    
    void DelOneData(int index);
    
    TypeGateway GetCurSelGateway() const { return m_vecGateways[GetCurSel()]; }
    TypeDevice GetCurSelDevices() const { return m_vecDevices[GetCurSel()]; }
    TypeCamera GetCurSelCameras() const { return m_vecCameras[GetCurSel()]; }
    TypeMonitor GetCurSelMonitor() const { return m_vecMonitors[GetCurSel()]; }
    TypeAudio GetCurSelAudio() const { return m_vecAudios[GetCurSel()]; }

    void AddOneGateway(const TypeGateway& Gateway) { m_vecGateways.push_back(Gateway); }
    void AddOneDevice(const TypeDevice& Device) { m_vecDevices.push_back(Device); }
    void AddOneCamera(const TypeCamera& Camera) { m_vecCameras.push_back(Camera); }
    void AddOneMonitor(const TypeMonitor& Monitor) { m_vecMonitors.push_back(Monitor); }
    void AddAudio(const TypeAudio& Audio) { m_vecAudios.push_back(Audio); }

    void SetComboBoxType(CWALKNetObjectType ObjType) { m_ComboBoxType = ObjType; }

    void AddOneRow(const char* RowName);
    void AddOneRow(const wchar_t* RowName);
    void ClearAllContent();
    void DeleteCurSelRow();
    

public:
    afx_msg void OnCbnDropdown();


private:
    CWALKNetObjectType m_ComboBoxType;

    std::vector<TypeGateway> m_vecGateways;
    std::vector<TypeDevice> m_vecDevices;
    std::vector<TypeCamera> m_vecCameras;
    std::vector<TypeMonitor> m_vecMonitors;
    std::vector<TypeAudio> m_vecAudios;

    
};


