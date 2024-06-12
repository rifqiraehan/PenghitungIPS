#pragma once

#include "afxwin.h"
#include "afxcmn.h"

class CPenghitungIPSDlg : public CDialogEx
{
    // Construction
public:
    CPenghitungIPSDlg(CWnd* pParent = nullptr); // standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PENGHITUNGIPS_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:

public:
    CEdit m_editMatkul;
    CEdit m_editSKS;
    CComboBox m_comboNilai;
    CButton m_buttonAdd;
    CButton m_buttonCalculate;
    CButton m_buttonDelete;
    CStatic m_statusLabel;
    CStatic m_ipsLabel;

    float ConvertGrade(const CString& grade);

    void calculateIPS();
    CListCtrl m_listCtrl;

    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonCalculate();
    afx_msg void OnBnClickedButtonDelete();
};
