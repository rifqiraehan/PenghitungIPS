#include "pch.h"
#include "framework.h"
#include "PenghitungIPS.h"
#include "PenghitungIPSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPenghitungIPSDlg::CPenghitungIPSDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PENGHITUNGIPS_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPenghitungIPSDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MATKUL_EDIT, m_matkulEdit);
    DDX_Control(pDX, IDC_SKS_EDIT, m_sksEdit);
    DDX_Control(pDX, IDC_NILAI_COMBO, m_nilaiComboBox);
    DDX_Control(pDX, IDC_LIST_CTRL, m_listCtrl);
    DDX_Control(pDX, IDC_IPS_LABEL, m_ipsLabel);
    DDX_Control(pDX, IDC_STATUS_LABEL, m_statusLabel);
}

BEGIN_MESSAGE_MAP(CPenghitungIPSDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_ADD_BUTTON, &CPenghitungIPSDlg::OnBnClickedAddButton)
    ON_BN_CLICKED(IDC_DELETE_BUTTON, &CPenghitungIPSDlg::OnBnClickedDeleteButton)
END_MESSAGE_MAP()

BOOL CPenghitungIPSDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);          

    m_listCtrl.InsertColumn(0, _T("Mata Kuliah"), LVCFMT_LEFT, 100);
    m_listCtrl.InsertColumn(1, _T("SKS"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn(2, _T("Nilai"), LVCFMT_LEFT, 50);

    m_nilaiComboBox.AddString(_T("A"));
    m_nilaiComboBox.AddString(_T("AB"));
    m_nilaiComboBox.AddString(_T("B"));
    m_nilaiComboBox.AddString(_T("BC"));
    m_nilaiComboBox.AddString(_T("C"));
    m_nilaiComboBox.AddString(_T("D"));
    m_nilaiComboBox.AddString(_T("E"));

    return TRUE;
}

void CPenghitungIPSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CDialogEx dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CPenghitungIPSDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CPenghitungIPSDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

float CPenghitungIPSDlg::convertGrade(const CString& grade)
{
    if (grade == _T("A")) return 4.0f;
    else if (grade == _T("AB")) return 3.5f;
    else if (grade == _T("B")) return 3.0f;
    else if (grade == _T("BC")) return 2.5f;
    else if (grade == _T("C")) return 2.0f;
    else if (grade == _T("D")) return 1.0f;
    else if (grade == _T("E")) return 0.0f;
    else return -1;
}

void CPenghitungIPSDlg::calculateIPS()
{
    float sum = 0;
    int totalSKS = 0;
    for (int i = 0; i < m_listCtrl.GetItemCount(); ++i) {
        CString sksText = m_listCtrl.GetItemText(i, 1);
        CString nilaiText = m_listCtrl.GetItemText(i, 2);
        int sks = _ttoi(sksText);
        float nilaiAngka = convertGrade(nilaiText);

        if (nilaiAngka != -1) {
            sum += nilaiAngka * sks;
            totalSKS += sks;
        }
    }

    CString ipsText;
    if (totalSKS > 0) {
        float ips = sum / totalSKS;
        ipsText.Format(_T("IPS: %.2f"), ips);
    }
    else {
        ipsText = _T("Terdapat data yang belum diinput.");
    }
    m_ipsLabel.SetWindowTextW(ipsText);
}

void CPenghitungIPSDlg::OnBnClickedAddButton()
{
    CString namaMatkul, sksText, nilai;
    m_matkulEdit.GetWindowTextW(namaMatkul);
    m_sksEdit.GetWindowTextW(sksText);
    m_nilaiComboBox.GetWindowTextW(nilai);

    int sks = _ttoi(sksText);
    float nilaiAngka = convertGrade(nilai);

    if (nilaiAngka == -1 || sks <= 0 || namaMatkul.IsEmpty()) {
        m_statusLabel.SetWindowTextW(_T("Input tidak valid."));
        return;
    }

    int rowCount = m_listCtrl.GetItemCount();
    m_listCtrl.InsertItem(rowCount, namaMatkul);
    m_listCtrl.SetItemText(rowCount, 1, sksText);
    m_listCtrl.SetItemText(rowCount, 2, nilai);

    m_matkulEdit.SetWindowTextW(_T(""));
    m_sksEdit.SetWindowTextW(_T(""));
    m_nilaiComboBox.SetCurSel(0);

    m_statusLabel.SetWindowTextW(_T("Mata kuliah berhasil ditambahkan."));
    calculateIPS();
}

void CPenghitungIPSDlg::OnBnClickedDeleteButton()
{
    POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
    while (pos) {
        int nItem = m_listCtrl.GetNextSelectedItem(pos);
        m_listCtrl.DeleteItem(nItem);
        pos = m_listCtrl.GetFirstSelectedItemPosition();
    }
    calculateIPS();
    m_statusLabel.SetWindowTextW(_T(""));
}
