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
    
    void AddOneRow(const char* RowName);
    void ClearAllContent();
    void DeleteCurSelRow();

public:
    afx_msg void OnCbnDropdown();


public:
    CWALKNetObjectType m_ComboBoxType;

};


