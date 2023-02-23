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

STDMETHODIMP CServiceHandler::ServiceStart(BSTR serviceName, LONG timeout)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
  //  SC_HANDLE service = OpenService(hSCManager, CString(ServiceName, )

    return S_OK;
}


