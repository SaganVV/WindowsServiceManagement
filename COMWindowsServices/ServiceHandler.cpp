// ServiceHandler.cpp : Implementation of CServiceHandler

#include <Windows.h>
//#include <iostream>
#include "pch.h"
#include "ServiceHandler.h"

STDMETHODIMP CServiceHandler::GetServices(SAFEARRAY** pOut, LPDWORD dwServicesReturned)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!hSCManager)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    DWORD dwBytesNeeded = 0;
    DWORD dwResumeHandle = 0;

    EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &dwBytesNeeded, dwServicesReturned, &dwResumeHandle);

    if (GetLastError() != ERROR_MORE_DATA)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    LPENUM_SERVICE_STATUS lpServices = (LPENUM_SERVICE_STATUS)malloc(dwBytesNeeded);
    if (!EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, lpServices, dwBytesNeeded, &dwBytesNeeded, dwServicesReturned, &dwResumeHandle))
    {
        free(lpServices);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    SAFEARRAY* pServicesArray = SafeArrayCreateVector(VT_BSTR, 0, *dwServicesReturned);
    if (!pServicesArray)
    {
        free(lpServices);
        CloseServiceHandle(hSCManager);
        return E_OUTOFMEMORY;
    }

    for (DWORD i = 0; i < *dwServicesReturned; i++)
    {
        BSTR serviceName = SysAllocString(lpServices[i].lpServiceName);
        if (!serviceName)
        {
            free(lpServices);
            CloseServiceHandle(hSCManager);
            SafeArrayDestroy(pServicesArray);
            return E_OUTOFMEMORY;
        }

        LONG index = i;
        if (FAILED(SafeArrayPutElement(pServicesArray, &index, serviceName)))
        {
            SysFreeString(serviceName);
            free(lpServices);
            CloseServiceHandle(hSCManager);
            SafeArrayDestroy(pServicesArray);
            return E_FAIL;
        }
    }


    free(lpServices);
    CloseServiceHandle(hSCManager);

    *pOut = pServicesArray;
    return S_OK;
}

STDMETHODIMP CServiceHandler::ServiceStart(BSTR serviceName)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        
        return HRESULT_FROM_WIN32(GetLastError());
    }
    
    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_START | SERVICE_QUERY_STATUS);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    if (!StartService(hService, 0, NULL))
    {
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwBytesNeeded = 0;

    if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE) & ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
    {
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    if (ssStatus.dwCurrentState != SERVICE_STOP && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
    {
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return S_OK;
    }

    DWORD dwStartTickCount = GetTickCount();
    DWORD dwCheckPoint = 0;
    DWORD dwOldCheckPoint = ssStatus.dwCheckPoint;
    DWORD dwWaitTime = 0;

    while (ssStatus.dwCurrentState != SERVICE_RUNNING)
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
            if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
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




STDMETHODIMP CServiceHandler::ServiceCurrentState(BSTR serviceName, LPDWORD dwCurrentState)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {

        return HRESULT_FROM_WIN32(GetLastError());
    }
    
    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_QUERY_STATUS);
    if (!hService)
    {
        CloseHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwBytesNeeded;
    if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
    {
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    *dwCurrentState = ssStatus.dwCurrentState;
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return S_OK;
}
