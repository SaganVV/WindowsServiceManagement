// ServiceHandler.cpp : Implementation of CServiceHandler

#include <Windows.h>

#include "pch.h"
#include "ServiceHandler.h"
#include "AdditionalServiceFunctions.h"

#include <vector>
STDMETHODIMP CServiceHandler::GetServices(SAFEARRAY** pOut, LPDWORD lpdwServicesReturned)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!hSCManager)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    DWORD dwBytesNeeded = 0;
    DWORD dwResumeHandle = 0;

    EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &dwBytesNeeded, lpdwServicesReturned, &dwResumeHandle);

    if (GetLastError() != ERROR_MORE_DATA)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    std::vector<ENUM_SERVICE_STATUS> services(*lpdwServicesReturned);
    LPENUM_SERVICE_STATUS lpServices = services.data();

    if (!EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, lpServices, dwBytesNeeded, &dwBytesNeeded, lpdwServicesReturned, &dwResumeHandle))
    {       
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    SAFEARRAY* pServicesArray = SafeArrayCreateVector(VT_BSTR, 0, *lpdwServicesReturned);
    if (!pServicesArray)
    {
        free(lpServices);
        CloseServiceHandle(hSCManager);
        return E_OUTOFMEMORY;
    }

    for (DWORD i = 0; i < *lpdwServicesReturned; i++)
    {
        BSTR serviceName = SysAllocString(lpServices[i].lpServiceName);
        if (!serviceName)
        {
            CloseServiceHandle(hSCManager);
            SafeArrayDestroy(pServicesArray);
            return E_OUTOFMEMORY;
        }

        LONG index = i;
        if (FAILED(SafeArrayPutElement(pServicesArray, &index, serviceName)))
        {
            SysFreeString(serviceName);
            CloseServiceHandle(hSCManager);
            SafeArrayDestroy(pServicesArray);
            return E_FAIL;
        }
    }


    CloseServiceHandle(hSCManager);

    *pOut = pServicesArray;
    return S_OK;
}

STDMETHODIMP CServiceHandler::GetDependentServices(BSTR serviceName, SAFEARRAY** pOut, LPDWORD lpdwServicesReturned)
{
    HRESULT hr = S_OK;
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SC_HANDLE hService = OpenService(hSCManager, serviceName, SERVICE_ENUMERATE_DEPENDENTS);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return HRESULT_FROM_WIN32(GetLastError());
    }
    DWORD dwBytesNeeded = 0;
    if (EnumDependentServices(hService, SERVICE_ACTIVE, NULL, 0, &dwBytesNeeded, lpdwServicesReturned))
    {
        hr = S_OK;
        return hr;
    }
    else if (GetLastError() != ERROR_MORE_DATA)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return hr;
    }

    std::vector<ENUM_SERVICE_STATUS> services(*lpdwServicesReturned);
    LPENUM_SERVICE_STATUS lpServices = services.data();

    EnumDependentServices(hService, SERVICE_ACTIVE, lpServices, dwBytesNeeded, &dwBytesNeeded, lpdwServicesReturned);
    SAFEARRAY* pServicesArray = SafeArrayCreateVector(VT_BSTR, 0, *lpdwServicesReturned);

    if (!pServicesArray)
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    hr = ServiceNamesToSafeArray(lpServices, *lpdwServicesReturned, &pServicesArray);
    if (FAILED(hr))
    {
        SafeArrayDestroy(pServicesArray);
        goto cleanup;
    }

    *pOut = pServicesArray;

cleanup:
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return hr;
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

STDMETHODIMP CServiceHandler::ServiceControlsAccepted(BSTR serviceName, LPDWORD dwControlsAccepted)
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
    *dwControlsAccepted = ssStatus.dwControlsAccepted;
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return S_OK;
}


STDMETHODIMP CServiceHandler::ServiceStart(BSTR serviceName)
{

    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    HRESULT hr = S_OK;

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

    hr = WaitForServiceStatus(serviceName, SERVICE_RUNNING, 30000);
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return hr;

}

STDMETHODIMP CServiceHandler::ServiceStop(BSTR serviceName)
{
    return ControlService(serviceName, SERVICE_CONTROL_STOP, SERVICE_STOPPED, cdwTimeout);
}

STDMETHODIMP CServiceHandler::ServicePause(BSTR serviceName)
{
    return ControlService(serviceName, SERVICE_CONTROL_PAUSE, SERVICE_PAUSED, cdwTimeout);
}


STDMETHODIMP CServiceHandler::ServiceResume(BSTR serviceName)
{
    return ControlService(serviceName, SERVICE_CONTROL_CONTINUE, SERVICE_RUNNING, cdwTimeout);
}


STDMETHODIMP CServiceHandler::ServiceRestart(BSTR serviceName)
{

    HRESULT hr = ServiceStop(serviceName);
    if (FAILED(hr))
        return hr;
    hr = ServiceStart(serviceName);
    return hr;
}

