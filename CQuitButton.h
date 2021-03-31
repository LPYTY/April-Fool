#pragma once


// CQuitButton

class CQuitButton : public CButton
{
	DECLARE_DYNAMIC(CQuitButton)

public:
	CQuitButton();
	virtual ~CQuitButton();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	bool m_bismoved;
	bool m_bEnter;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


