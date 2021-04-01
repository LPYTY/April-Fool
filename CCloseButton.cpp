// CCloseButton.cpp: 实现文件
//

#include "pch.h"
#include "April Fool.h"
#include "CCloseButton.h"


// CCloseButton

IMPLEMENT_DYNAMIC(CCloseButton, CButton)

CCloseButton::CCloseButton()
{
	m_bEnter = false;
}

CCloseButton::~CCloseButton()
{
}


BEGIN_MESSAGE_MAP(CCloseButton, CButton)
	ON_WM_MOUSEHOVER()
	//ON_CONTROL_REFLECT(BN_CLICKED, &CCloseButton::OnBnClicked)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CCloseButton 消息处理程序




void CCloseButton::OnMouseHover(UINT nFlags, CPoint point)
{
	SetWindowText(TEXT("Clone"));

	CButton::OnMouseHover(nFlags, point);
}


void CCloseButton::OnBnClicked()
{
	ShellExecute(NULL, TEXT("open"), theApp.argv[0], TEXT(""), TEXT(""), SW_SHOW);
}


void CCloseButton::OnMouseLeave()
{
	SetWindowText(TEXT("Close"));
	m_bEnter = false;

	CButton::OnMouseLeave();
}


void CCloseButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bEnter)
	{
		TRACKMOUSEEVENT track;
		ZeroMemory(&track, sizeof(TRACKMOUSEEVENT));
		track.cbSize = sizeof(TRACKMOUSEEVENT);

		track.hwndTrack = m_hWnd;
		track.dwFlags = TME_LEAVE | TME_HOVER;
		track.dwHoverTime = 1;

		_TrackMouseEvent(&track);

		m_bEnter = TRUE;
	}
	

	CButton::OnMouseMove(nFlags, point);
}
