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
    
    TypeGateway GetCurSelGateway() const { return m_vecGateways[GetCurSel()]; }
    TypeDevice GetCurSelDevices() const { return m_vecDevices[GetCurSel()]; }
    TypeCamera GetCurSelCameras() const { return m_vecCameras[GetCurSel()]; }
    TypeMonitor GetCurSelMonitor() const { return m_vecMonitors[GetCurSel()]; }
    TypeAudio GetCurSelAudio() const { return m_vecAudios[GetCurSel()]; }
    TypeDisplayMode GetCurSelDisplayMode() const { return m_vecDisplayModes[GetCurSel()]; }

    void AddOneGateway(const TypeGateway& Gateway);
    void AddOneDevice(const TypeDevice& Device);
    void AddOneCamera(const TypeCamera& Camera);
    void AddOneMonitor(const TypeMonitor& Monitor);
    void AddOneAudio(const TypeAudio& Audio);
    void AddOneDisplayMode(const TypeDisplayMode& DisplayMode);

    void SetComboBoxType(int ObjType) { m_ComboBoxType = ObjType; }

    void ClearAllContent();
    void DeleteCurSelRow();

private:
    void DelOneData(int index);
    void AddOneRow(const char* RowName);
    void AddOneRow(const wchar_t* RowName);
    

public:
    afx_msg void OnCbnDropdown();


private:
    int m_ComboBoxType;

    std::vector<TypeGateway> m_vecGateways;
    std::vector<TypeDevice> m_vecDevices;
    std::vector<TypeCamera> m_vecCameras;
    std::vector<TypeMonitor> m_vecMonitors;
    std::vector<TypeAudio> m_vecAudios;
    std::vector<TypeDisplayMode> m_vecDisplayModes;
    
};


