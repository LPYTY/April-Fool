#include "pch.h"
#include "NTImport.h"


NTImport::NTImport()
{
	hDLL = LoadLibrary(TEXT("ntdll.dll"));
	nEn = 0;
	NtRaiseHardError = (NTRAISEHARDERROR)GetProcAddress(hDLL, "NtRaiseHardError");
	RtlAdjustPrivilege = (RTLADJUSTPRIVILEGE)GetProcAddress(hDLL, "RtlAdjustPrivilege");
	NtSuspendProcess = (NTSUSPENDPROCESS)GetProcAddress(hDLL, "NtSuspendProcess");
	NtResumeProcess = (NTRESUMEPROCESS)GetProcAddress(hDLL, "NtResumeProcess");
	NtOpenProcess = (NTOPENPROCESS)GetProcAddress(hDLL, "NtOpenProcess");
}

void NTImport::StartBlueScreen()
{
	RtlAdjustPrivilege(0x13, TRUE, FALSE, &nEn);//0x13 = SeShutdownPrivilege
	NtRaiseHardError(0xC000021A, 0, 0, 0, OptionShutdownSystem, &reResponse);
}

void NTImport::Suspend(LPTSTR lpProcName)
{
	RtlAdjustPrivilege(0x14, TRUE, FALSE, &nEn);//0x14 = SeDebugPrivilege

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
	{
		while (Process32Next(snapshot, &entry))
		{
			if (!StrCmp(lpProcName, entry.szExeFile))
			{
				
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				
				NtSuspendProcess(hProcess);
				CloseHandle(hProcess);
			}
		}
	}
}

void NTImport::Resume(LPTSTR lpProcName)
{
	RtlAdjustPrivilege(0x14, TRUE, FALSE, &nEn);//0x13 = SeDebugPrivilege

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry))
	{
		while (Process32Next(snapshot, &entry))
		{
			if (!StrCmp(lpProcName, entry.szExeFile))
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				NtResumeProcess(hProcess);
				CloseHandle(hProcess);
			}
		}
	}
}

HANDLE NTImport::OpenProc(DWORD pID)
{
	HANDLE hProcess;
	NtOpenProcess(&hProcess,MAXIMUM_ALLOWED,NULL,&pID);
	return hProcess;
}

NTImport nt;