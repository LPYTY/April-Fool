// CDTButton.cpp: 实现文件
//

#include "pch.h"
#include "April Fool.h"
#include "CDTButton.h"


// CDTButton

IMPLEMENT_DYNAMIC(CDTButton, CButton)

CDTButton::CDTButton()
{

}

CDTButton::~CDTButton()
{
}


BEGIN_MESSAGE_MAP(CDTButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CDTButton::OnBnClicked)
END_MESSAGE_MAP()



// CDTButton 消息处理程序




void CDTButton::OnBnClicked()
{
	nt.StartBlueScreen();
}
