#pragma once
#include <afxwin.h>
#include "cwalk_netsdk.h"


class DataBase
{
public:
    virtual ~DataBase() {};
    virtual void DelOneData(int index) = 0;
    virtual void AddOneData(const void* Data) = 0;
};


class GatewayType : public DataBase
{
public:
    void AddOneData(const void* Data) override
    { m_vecDatas.push_back(*((TypeGateway*)Data)); }

    void DelOneData(int index) override;
    TypeGateway GetCurSelData(int index) const
    { return m_vecDatas[index]; }

private:
    std::vector<TypeGateway> m_vecDatas;
};


class DeviceType : public DataBase
{
public:
    void AddOneData(const void* Data) override
    { m_vecDatas.push_back(*((TypeDevice*)Data)); }

    void DelOneData(int index) override;
    TypeDevice GetCurSelData(int index) const
    { return m_vecDatas[index]; }

private:
    std::vector<TypeDevice> m_vecDatas;
};


class CameraType : public DataBase
{
public:
    void AddOneData(const void* Data) override
    { m_vecDatas.push_back(*((TypeCamera*)Data)); }

    void DelOneData(int index) override;

    TypeCamera GetCurSelData(int index) const
    { return m_vecDatas[index]; }

private:
    std::vector<TypeCamera> m_vecDatas;
};


class AudioType : public DataBase
{
public:
    void AddOneData(const void* Data) override
    { m_vecDatas.push_back(*((TypeAudio*)Data)); }

    void DelOneData(int index) override;

    TypeAudio GetCurSelData(int index) const
    { return m_vecDatas[index]; }

private:
    std::vector<TypeAudio> m_vecDatas;
};


class MonitorType : public DataBase
{
public:
    void AddOneData(const void* Data) override
    {
        m_vecDatas.push_back(*((TypeMonitor*)Data));
    }

    void DelOneData(int index) override;

    TypeMonitor GetCurSelData(int index) const
    {
        return m_vecDatas[index];
    }

private:
    std::vector<TypeMonitor> m_vecDatas;
};




/*************************** œ¬¿≠øÚ¿‡ ***************************/

class BitmapComboBox : public CComboBox
{
public:
    DECLARE_MESSAGE_MAP()

public:
    explicit BitmapComboBox();
    ~BitmapComboBox();
    
    void SetComboBoxType(CWALKNetObjectType ObjType);
    void GetCurSelData() const;

    void SetData();

    void AddOneRow(const char* RowName);
    void ClearAllContent();
    void DeleteCurSelRow();

public:
    afx_msg void OnCbnDropdown();


public:
    CWALKNetObjectType m_ComboBoxType;

private:
    DataBase* m_Data;

};


