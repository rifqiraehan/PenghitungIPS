#pragma once

#include "resource.h"

// PenghitungIPSDlg dialog
class CPenghitungIPSDlg : public CDialogEx
{
    // Construction
public:
    CPenghitungIPSDlg(CWnd* pParent = nullptr);   // standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PENGHITUNGIPS_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    HICON m_hIcon;
    CEdit m_matkulEdit;
    CEdit m_sksEdit;
    CComboBox m_nilaiComboBox;
    CListCtrl m_listCtrl;
    CStatic m_ipsLabel;
    CStatic m_statusLabel;

    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedAddButton();
    afx_msg void OnBnClickedDeleteButton();

private:
    void calculateIPS();
    float convertGrade(const CString& grade);
};
