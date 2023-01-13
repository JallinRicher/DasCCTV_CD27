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
    
    TypeOrg GetCurSelStation() const { return m_vecStations[GetCurSel()]; }
    TypeOrg GetCurSelArea() const { return m_vecAreas[GetCurSel()]; }
    TypeDevice GetCurSelDevice() const { return m_vecDevices[GetCurSel()]; }
    TypeCamera GetCurSelCamera() const { return m_vecCameras[GetCurSel()]; }
    TypeMonitor GetCurSelMonitor() const { return m_vecMonitors[GetCurSel()]; }
    TypeAudio GetCurSelAudio() const { return m_vecAudios[GetCurSel()]; }
    TypeDisplayMode GetCurSelDisplayMode() const { return m_vecDisplayModes[GetCurSel()]; }

    void AddOneStation(const TypeOrg& Station);
    void AddOneArea(const TypeOrg& Area);
    void AddOneDevice(const TypeDevice& Device);
    void AddOneCamera(const TypeCamera& Camera);
    void AddOneMonitor(const TypeMonitor& Monitor);
    void AddOneAudio(const TypeAudio& Audio);
    void AddOneDisplayMode(const TypeDisplayMode DisplayMode);

    void SetComboBoxType(int ObjType) { m_ComboBoxType = ObjType; }

    void ClearAllContent();
    void DeleteCurSelRow();

private:
    void DelOneData(int index);
    void AddOneRow(LPCTSTR RowName);
    

public:
    afx_msg void OnCbnDropdown();


private:
    int m_ComboBoxType;


    std::vector<TypeOrg> m_vecStations;
    std::vector<TypeOrg> m_vecAreas;
    std::vector<TypeDevice> m_vecDevices;
    std::vector<TypeCamera> m_vecCameras;
    std::vector<TypeMonitor> m_vecMonitors;
    std::vector<TypeAudio> m_vecAudios;
    std::vector<TypeDisplayMode> m_vecDisplayModes;
    
};


