#pragma once
#include "framework.h"

#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)

class BlueScreenMgr
{
private:
    typedef /*__success(return >= 0)*/ LONG NTSTATUS;
    typedef NTSTATUS* PNTSTATUS;


    typedef struct _LSA_UNICODE_STRING {
        USHORT Length;
        USHORT MaximumLength;
        PWSTR  Buffer;
    } LSA_UNICODE_STRING, * PLSA_UNICODE_STRING, UNICODE_STRING, * PUNICODE_STRING;

    typedef enum _HARDERROR_RESPONSE_OPTION {
        OptionAbortRetryIgnore,
        OptionOk,
        OptionOkCancel,
        OptionRetryCancel,
        OptionYesNo,
        OptionYesNoCancel,
        OptionShutdownSystem
    } HARDERROR_RESPONSE_OPTION, * PHARDERROR_RESPONSE_OPTION;

    typedef enum _HARDERROR_RESPONSE {
        ResponseReturnToCaller,
        ResponseNotHandled,
        ResponseAbort,
        ResponseCancel,
        ResponseIgnore,
        ResponseNo,
        ResponseOk,
        ResponseRetry,
        ResponseYes
    } HARDERROR_RESPONSE, * PHARDERROR_RESPONSE;


	typedef NTSTATUS(__stdcall* func)(NTSTATUS, ULONG, ULONG, PULONG, UINT, PULONG);
    typedef UINT(CALLBACK* NTRAISEHARDERROR)(NTSTATUS, ULONG, PUNICODE_STRING, PVOID, HARDERROR_RESPONSE_OPTION, PHARDERROR_RESPONSE);
    typedef UINT(CALLBACK* RTLADJUSTPRIVILEGE)(ULONG, BOOL, BOOL, PINT);

    HINSTANCE hDLL;
    NTRAISEHARDERROR NtRaiseHardError;
    RTLADJUSTPRIVILEGE RtlAdjustPrivilege;
    int nEn;
    HARDERROR_RESPONSE reResponse;
public:
    BlueScreenMgr();
    void StartBlueScreen();
};

