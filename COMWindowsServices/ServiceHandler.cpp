// ServiceHandler.cpp : Implementation of CServiceHandler

#include <Windows.h>

#include "pch.h"
#include "ServiceHandler.h"


// CServiceHandler



STDMETHODIMP CServiceHandler::GetServices(BSTR** pOut)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!hSCManager)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    DWORD dwBytesNeeded = 0;
    DWORD dwServicesReturned = 0;
    DWORD dwResumeHandle = 0;
    // LPENUM_SERVICE_STATUS lpEnumServiceStatus;
    EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle);

    if (GetLastError() != ERROR_MORE_DATA)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    LPENUM_SERVICE_STATUS lpServices = (LPENUM_SERVICE_STATUS)malloc(dwBytesNeeded);
    if (!EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, lpServices, dwBytesNeeded, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle))
    {
        free(lpServices);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    BSTR* pServiceNames = (BSTR*)malloc(dwServicesReturned * sizeof(BSTR));
    for (DWORD i = 0; i < dwServicesReturned; i++)
    {
        pServiceNames[i] = lpServices[i].lpServiceName;
    }
    *pOut = pServiceNames;
    free(lpServices);
    CloseServiceHandle(hSCManager);
    return S_OK;
}
