// PenghitungIPSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PenghitungIPS.h"
#include "PenghitungIPSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPenghitungIPSDlg dialog

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
    DDX_Control(pDX, IDC_MATKUL_LIST, m_matkulList);
    DDX_Control(pDX, IDC_STATUS_LABEL, m_statusLabel);
    DDX_Control(pDX, IDC_IPS_LABEL, m_ipsLabel);
    DDX_Control(pDX, IDC_ADD_BUTTON, m_addButton);
    DDX_Control(pDX, IDC_CALCULATE_BUTTON, m_calculateButton);
}

BEGIN_MESSAGE_MAP(CPenghitungIPSDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_ADD_BUTTON, &CPenghitungIPSDlg::OnBnClickedAddButton)
    ON_BN_CLICKED(IDC_CALCULATE_BUTTON, &CPenghitungIPSDlg::OnBnClickedCalculateButton)
END_MESSAGE_MAP()


// CPenghitungIPSDlg message handlers

BOOL CPenghitungIPSDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Menambahkan "About..." menu item ke system menu.
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Menentukan icon untuk dialog ini. Framework melakukannya secara otomatis
    SetIcon(m_hIcon, TRUE); // Set big icon
    SetIcon(m_hIcon, FALSE); // Set small icon

    // Inisialisasi kontrol dialog
    if (!m_matkulEdit.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(20, 20, 200, 40), this, IDC_MATKUL_EDIT) ||
        !m_sksEdit.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(220, 20, 280, 40), this, IDC_SKS_EDIT) ||
        !m_nilaiComboBox.Create(CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(300, 20, 380, 40), this, IDC_NILAI_COMBO))
    {
        AfxMessageBox(_T("Failed to create controls!"));
        return FALSE;
    }

    // Tambah item ke combo box
    m_nilaiComboBox.AddString(_T("A"));
    m_nilaiComboBox.AddString(_T("AB"));
    m_nilaiComboBox.AddString(_T("B"));
    m_nilaiComboBox.AddString(_T("BC"));
    m_nilaiComboBox.AddString(_T("C"));
    m_nilaiComboBox.AddString(_T("D"));
    m_nilaiComboBox.AddString(_T("E"));

    if (!m_addButton.Create(_T("Tambah"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 70, 100, 40), this, IDC_ADD_BUTTON) ||
        !m_calculateButton.Create(_T("Hitung IPS"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(120, 70, 100, 40), this, IDC_CALCULATE_BUTTON) ||
        !m_matkulList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, CRect(20, 120, 380, 300), this, IDC_MATKUL_LIST) ||
        !m_statusLabel.Create(_T(""), WS_CHILD | WS_VISIBLE, CRect(20, 430, 380, 20), this, IDC_STATUS_LABEL) ||
        !m_ipsLabel.Create(_T("IPS: "), WS_CHILD | WS_VISIBLE, CRect(20, 460, 380, 20), this, IDC_IPS_LABEL))
    {
        AfxMessageBox(_T("Failed to create controls!"));
        return FALSE;
    }

    // Setup List control
    m_matkulList.InsertColumn(0, _T("Mata Kuliah"), LVCFMT_LEFT, 150);
    m_matkulList.InsertColumn(1, _T("SKS"), LVCFMT_LEFT, 50);
    m_matkulList.InsertColumn(2, _T("Nilai"), LVCFMT_LEFT, 50);

    return TRUE;  // return TRUE unless you set the focus to a control
}


void CPenghitungIPSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPenghitungIPSDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPenghitungIPSDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CPenghitungIPSDlg::OnBnClickedAddButton()
{
    CString namaMatkul;
    m_matkulEdit.GetWindowText(namaMatkul);

    CString sksStr;
    m_sksEdit.GetWindowText(sksStr);
    int sks = _ttoi(sksStr);

    CString nilai;
    m_nilaiComboBox.GetLBText(m_nilaiComboBox.GetCurSel(), nilai);
    float nilaiAngka = ConvertGrade(nilai);

    if (nilaiAngka == -1 || sks <= 0 || namaMatkul.IsEmpty()) {
        m_statusLabel.SetWindowText(_T("Input tidak valid."));
        return;
    }

    int rowCount = m_matkulList.GetItemCount();
    m_matkulList.InsertItem(rowCount, namaMatkul);
    m_matkulList.SetItemText(rowCount, 1, sksStr);
    m_matkulList.SetItemText(rowCount, 2, nilai);

    m_matkulEdit.SetWindowText(_T(""));
    m_sksEdit.SetWindowText(_T(""));
    m_nilaiComboBox.SetCurSel(0);

    m_statusLabel.SetWindowText(_T("Mata kuliah berhasil ditambahkan."));

    CalculateIPS();
}

void CPenghitungIPSDlg::OnBnClickedCalculateButton()
{
    CalculateIPS();
}

void CPenghitungIPSDlg::CalculateIPS()
{
    float sum = 0;
    int totalSKS = 0;

    for (int i = 0; i < m_matkulList.GetItemCount(); i++) {
        CString sksStr = m_matkulList.GetItemText(i, 1);
        int sks = _ttoi(sksStr);

        CString nilai = m_matkulList.GetItemText(i, 2);
        float nilaiAngka = ConvertGrade(nilai);

        if (nilaiAngka != -1) {
            sum += nilaiAngka * sks;
            totalSKS += sks;
        }
    }

    if (totalSKS > 0) {
        float ips = sum / totalSKS;
        CString ipsStr;
        ipsStr.Format(_T("IPS: %.2f"), ips);
        m_ipsLabel.SetWindowText(ipsStr);
    }
    else {
        m_ipsLabel.SetWindowText(_T("Tidak ada SKS yang diinput."));
    }
}

float CPenghitungIPSDlg::ConvertGrade(const CString& grade)
{
    if (grade == "A") return 4.0;
    else if (grade == "AB") return 3.5;
    else if (grade == "B") return 3.0;
    else if (grade == "BC") return 2.5;
    else if (grade == "C") return 2.0;
    else if (grade == "D") return 1.0;
    else if (grade == "E") return 0.0;
    else return -1;
}
