#pragma once
#include "BlueScreenMgr.h"

// CDTButton

class CDTButton : public CButton
{
	DECLARE_DYNAMIC(CDTButton)

public:
	CDTButton();
	virtual ~CDTButton();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	BlueScreenMgr m_bsm;

public:
	afx_msg void OnBnClicked();
};


