
// April Fool.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "April Fool.h"
#include "April FoolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAprilFoolApp

BEGIN_MESSAGE_MAP(CAprilFoolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAprilFoolApp 构造

CAprilFoolApp::CAprilFoolApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CAprilFoolApp 对象

CAprilFoolApp theApp;


// CAprilFoolApp 初始化

BOOL CAprilFoolApp::InitInstance()
{
	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	auto cmdl = GetCommandLine();
	int argc;
	auto argv = CommandLineToArgvW(cmdl, &argc);

	if (argc == 1)
	{
		CAprilFoolDlg dlg;
		m_pMainWnd = &dlg;
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = argv[0];
		ShExecInfo.lpParameters = TEXT("a");
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOW;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		hChild = ShExecInfo.hProcess;
		INT_PTR nResponse = dlg.DoModal();
		
		if (nResponse == -1)
		{
			TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
			TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
		}
	}
	else
	{
		
		while (1)
		{
			if (FindWindow(NULL, TEXT("Happy April Fool's Day!")))
			{
				break;
			}
			if (!FindWindow(NULL, TEXT("April Fool's!")))
			{
				ShellExecute(NULL, TEXT("open"), argv[0], TEXT(""), TEXT(""), SW_SHOW);
			}
		}
	}
	
	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


