#pragma once
#include <afxwin.h>

class BitmapComboBox : public CComboBox
{
public:
    DECLARE_MESSAGE_MAP()

public:
    explicit BitmapComboBox();

    void ClearAllContent();
    void SetDeviceResCode(const char* DeviceResCode);
    void SetDeviceName(const char* DeviceName);
    void SetDeviceID(long DeviceID);
    void SetDeviceType(int DeviceType);
    void SetDeviceSubType(int DeviceSubType);
    void SetDeviceStatus(int DeviceStatus);

    void GetCurSelDeviceResCode(char* Retval) const;
    void GetCurSelDeviceName(char* Retval) const;
    long GetCurSelDeviceID() const;
    int GetCurSelDeviceType() const;
    int GetCurSelDeviceSubType() const;
    int GetCurSelDeviceStatus() const;

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

};

