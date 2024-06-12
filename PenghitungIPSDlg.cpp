#include "pch.h"
#include "framework.h"
#include "PenghitungIPS.h"
#include "PenghitungIPSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPenghitungIPSDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CPenghitungIPSDlg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CPenghitungIPSDlg::OnBnClickedButtonCalculate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPenghitungIPSDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

CPenghitungIPSDlg::CPenghitungIPSDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PENGHITUNGIPS_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPenghitungIPSDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MATKUL, m_editMatkul);
    DDX_Control(pDX, IDC_EDIT_SKS, m_editSKS);
    DDX_Control(pDX, IDC_COMBO_NILAI, m_comboNilai);
    DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
    DDX_Control(pDX, IDC_BUTTON_CALCULATE, m_buttonCalculate);
    DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
    DDX_Control(pDX, IDC_LIST_CTRL, m_listCtrl);
    DDX_Control(pDX, IDC_STATUS_LABEL, m_statusLabel);
    DDX_Control(pDX, IDC_IPS_LABEL, m_ipsLabel);
}

BOOL CPenghitungIPSDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //SetIcon(m_hIcon, TRUE);  // Set big icon
    //SetIcon(m_hIcon, FALSE); // Set small icon

    // Initialize controls
    m_comboNilai.AddString(_T("A"));
    m_comboNilai.AddString(_T("AB"));
    m_comboNilai.AddString(_T("B"));
    m_comboNilai.AddString(_T("BC"));
    m_comboNilai.AddString(_T("C"));
    m_comboNilai.AddString(_T("D"));
    m_comboNilai.AddString(_T("E"));
        
    // Initialize the list control
    m_listCtrl.InsertColumn(0, _T("Mata Kuliah"), LVCFMT_LEFT, 150);
    m_listCtrl.InsertColumn(1, _T("SKS"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn(2, _T("Nilai"), LVCFMT_LEFT, 50);

    m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_listCtrl.ModifyStyle(0, LVS_REPORT);


    return TRUE;  // return TRUE unless you set the focus to a control
}

void CPenghitungIPSDlg::OnBnClickedButtonAdd()
{
    CString matkul, sks, nilai;
    m_editMatkul.GetWindowText(matkul);
    m_editSKS.GetWindowText(sks);
    int nSel = m_comboNilai.GetCurSel();
    if (nSel != CB_ERR)
    {
        m_comboNilai.GetLBText(nSel, nilai);
    }

    if (matkul.IsEmpty() || sks.IsEmpty() || nilai.IsEmpty())
    {
        AfxMessageBox(_T("Please fill all fields."));
        return;
    }

    // Debugging: Display values
    CString debugMsg;
    debugMsg.Format(_T("Matkul: %s, SKS: %s, Nilai: %s"), matkul, sks, nilai);
    AfxMessageBox(debugMsg);

    // Convert sks to integer
    int sksVal = _ttoi(sks);
    if (sksVal <= 0)
    {
        AfxMessageBox(_T("Please enter a valid number for SKS."));
        return;
    }

    // Add the course to the list control
    int nIndex = m_listCtrl.GetItemCount(); // Get the current item count
    nIndex = m_listCtrl.InsertItem(nIndex, matkul); // Insert at the end
    if (nIndex != -1)
    {
        m_listCtrl.SetItemText(nIndex, 1, sks);
        m_listCtrl.SetItemText(nIndex, 2, nilai);

        // Debugging: Confirm item added
        AfxMessageBox(_T("Item added successfully."));

        // Clear the input fields after adding the item
        m_editMatkul.SetWindowText(_T(""));
        m_editSKS.SetWindowText(_T(""));
        m_comboNilai.SetCurSel(-1);
    }
    else
    {
        AfxMessageBox(_T("Failed to add item."));
    }
}

void CPenghitungIPSDlg::OnBnClickedButtonCalculate()
{
    int nItemCount = m_listCtrl.GetItemCount();
    if (nItemCount == 0)
    {
        AfxMessageBox(_T("No data to calculate."));
        return;
    }

    float totalPoints = 0.0f;
    int totalSKS = 0;

    for (int i = 0; i < nItemCount; ++i)
    {
        CString sksStr = m_listCtrl.GetItemText(i, 1);
        CString gradeStr = m_listCtrl.GetItemText(i, 2);

        int sks = _ttoi(sksStr);
        float grade = ConvertGrade(gradeStr);

        totalPoints += sks * grade;
        totalSKS += sks;
    }

    if (totalSKS == 0)
    {
        AfxMessageBox(_T("Total SKS is zero, cannot calculate IPS."));
        return;
    }

    float ips = totalPoints / totalSKS;
    CString ipsStr;
    ipsStr.Format(_T("IPS: %.2f"), ips);
    m_ipsLabel.SetWindowText(ipsStr);
}

void CPenghitungIPSDlg::OnBnClickedButtonDelete()
{
    int nSelected = m_listCtrl.GetNextItem(-1, LVNI_SELECTED);
    if (nSelected != -1)
    {
        m_listCtrl.DeleteItem(nSelected);
        // Calculate IPS after deleting an item
        calculateIPS();
    }
    else
    {
        AfxMessageBox(_T("No row selected."));
    }
}

float CPenghitungIPSDlg::ConvertGrade(const CString& grade)
{
    if (grade == _T("A")) return 4.0f;
    if (grade == _T("AB")) return 3.5f;
    if (grade == _T("B")) return 3.0f;
    if (grade == _T("BC")) return 2.5f;
    if (grade == _T("C")) return 2.0f;
    if (grade == _T("D")) return 1.0f;
    if (grade == _T("E")) return 0.0f;
    return 0.0f;
}

void CPenghitungIPSDlg::calculateIPS()
{
    int nItemCount = m_listCtrl.GetItemCount();
    if (nItemCount == 0)
    {
        m_ipsLabel.SetWindowText(_T("Tidak ada SKS yang diinput."));
        return;
    }

    float totalPoints = 0.0f;
    int totalSKS = 0;

    for (int i = 0; i < nItemCount; ++i)
    {
        CString sksStr = m_listCtrl.GetItemText(i, 1);
        CString gradeStr = m_listCtrl.GetItemText(i, 2);

        int sks = _ttoi(sksStr);
        float grade = ConvertGrade(gradeStr);

        totalPoints += sks * grade;
        totalSKS += sks;
    }

    if (totalSKS > 0)
    {
        float ips = totalPoints / totalSKS;
        CString ipsStr;
        ipsStr.Format(_T("IPS: %.2f"), ips);
        m_ipsLabel.SetWindowText(ipsStr);
    }
    else
    {
        m_ipsLabel.SetWindowText(_T("Total SKS is zero, cannot calculate IPS."));
    }
}