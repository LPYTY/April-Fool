
// April FoolDlg.h: 头文件
//

#pragma once
#include "CCloseButton.h"
#include "CDTButton.h"
#include "CQuitButton.h"

// CAprilFoolDlg 对话框
class CAprilFoolDlg : public CDialogEx
{
// 构造
public:
	CAprilFoolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APRILFOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	int m_iTime;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CCloseButton Close;
	CQuitButton Quit;
	CDTButton DT;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnUmRealquit(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedClose();
};
