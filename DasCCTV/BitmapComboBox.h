#pragma once
#include <afxwin.h>

class BitmapComboBox : public CComboBox
{
public:
    DECLARE_MESSAGE_MAP()

public:
    explicit BitmapComboBox();

    void ClearAllContent();
    void SetDeviceResCode(int index, const char* DeviceResCode);
    void SetDeviceName(int index, const char* DeviceName);
    void SetDeviceID(int index, long DeviceID);
    void SetDeviceType(int index, int DeviceType);
    void SetDeviceSubType(int index, int DeviceSubType);
    void SetDeviceStatus(int index, int DeviceStatus);
#ifdef MULTI_SUBWAY_ROUTE
    void SetRoute(int index, int Route);
#endif

    void GetCurSelDeviceResCode(char* Retval) const;
    void GetCurSelDeviceName(char* Retval) const;
    long GetCurSelDeviceID() const;
    int GetCurSelDeviceType() const;
    int GetCurSelDeviceSubType() const;
    int GetCurSelDeviceStatus() const;
#ifdef MULTI_SUBWAY_ROUTE
    int GetCurSelRoute() const;
#endif

    void AddOneRow(const char* RowName);
    void DeleteCurSelRow();

public:
    afx_msg void OnCbnDropdown();

private:
    char m_DeviceResCode[MAX_COMBO_ITEM_CNT][RES_CODE_LEN];
    char m_DeviceName[MAX_COMBO_ITEM_CNT][NAME_LEN];
    long m_DeviceID[MAX_COMBO_ITEM_CNT];
    int m_DeviceType[MAX_COMBO_ITEM_CNT];
    int m_DeviceSubType[MAX_COMBO_ITEM_CNT];
    int m_DeviceStatus[MAX_COMBO_ITEM_CNT];

#ifdef MULTI_SUBWAY_ROUTE
    int m_Routes[MAX_COMBO_ITEM_CNT];
#endif

};

