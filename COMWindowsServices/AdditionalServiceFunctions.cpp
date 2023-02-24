#include "AdditionalServiceFunctions.h"
#include "pch.h"

HRESULT WaitForServiceStatus(BSTR serviceName, DWORD dwDesiredState, DWORD dwTimeout)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {

        return HRESULT_FROM_WIN32(GetLastError());
    }

    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_QUERY_STATUS | SERVICE_STOP | SERVICE_START | SERVICE_PAUSE_CONTINUE | SERVICE_INTERROGATE | SERVICE_USER_DEFINED_CONTROL);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwBytesNeeded = 0;

    if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
    {
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    DWORD dwStartTickCount = GetTickCount();
    DWORD dwCheckPoint = 0;
    DWORD dwOldCheckPoint = ssStatus.dwCheckPoint;
    DWORD dwWaitTime = 0;

    while (ssStatus.dwCurrentState != dwDesiredState)
    {
        dwWaitTime = ssStatus.dwWaitHint / 10;
        if (dwWaitTime < 1000)
            dwWaitTime = 1000;
        else if (dwWaitTime > 10000)
            dwWaitTime = 10000;

        Sleep(dwWaitTime);

        if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
        {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return HRESULT_FROM_WIN32(GetLastError());
        }
        if (ssStatus.dwCheckPoint > dwOldCheckPoint)
        {
            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if (GetTickCount() - dwStartTickCount > dwTimeout)
            {
                CloseServiceHandle(hService);
                CloseServiceHandle(hSCManager);
                return HRESULT_FROM_WIN32(ERROR_TIMEOUT);
            }
        }
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return S_OK;
}