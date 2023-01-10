#pragma once
#include <afxwin.h>

class BitmapComboBox : public CComboBox
{
public:
    DECLARE_MESSAGE_MAP()

public:
    explicit BitmapComboBox();

    void ClearAllContent();


    void AddOneRow(const char* RowName);
    void DeleteCurSelRow();

public:
    afx_msg void OnCbnDropdown();

private:

};


