#pragma once


// CCloseButton

class CCloseButton : public CButton
{
	DECLARE_DYNAMIC(CCloseButton)

public:
	CCloseButton();
	virtual ~CCloseButton();

protected:
	bool m_bEnter;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnBnClicked();
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


