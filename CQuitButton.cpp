﻿// CQuitButton.cpp: 实现文件
//

#include "pch.h"
#include "April Fool.h"
#include "CQuitButton.h"


// CQuitButton

IMPLEMENT_DYNAMIC(CQuitButton, CButton)

CQuitButton::CQuitButton()
{
	m_bismoved = false;
	m_bEnter = false;
}

CQuitButton::~CQuitButton()
{
}


BEGIN_MESSAGE_MAP(CQuitButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CQuitButton 消息处理程序




void CQuitButton::OnMouseMove(UINT nFlags, CPoint point)
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


void CQuitButton::OnMouseHover(UINT nFlags, CPoint point)
{
	RECT rc, prc, prcc;
	GetWindowRect(&rc);
	CWnd* pParentWnd = GetParent();
	pParentWnd->GetWindowRect(&prc);
	pParentWnd->GetClientRect(&prcc);
	RECT movedrc;
	if (m_bismoved)
	{
		movedrc = { rc.left - 5 - prc.left,rc.top - prc.top,rc.right - 5 - prc.left,rc.bottom - prc.top };
	}
	else
	{
		movedrc = { rc.left - 5 - prc.left,rc.top - 50 - prc.top,rc.right - 5 - prc.left,rc.bottom - 50 - prc.top };
	}
	MoveWindow(&movedrc);
	m_bEnter = false;
	m_bismoved = !m_bismoved;
	GetWindowRect(&rc);

	CButton::OnMouseHover(nFlags, point);
}


void CQuitButton::OnMouseLeave()
{
	m_bEnter = false;

	CButton::OnMouseLeave();
}
