#pragma once
#include "NTImport.h"

// CDTButton

class CDTButton : public CButton
{
	DECLARE_DYNAMIC(CDTButton)

public:
	CDTButton();
	virtual ~CDTButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClicked();
};


