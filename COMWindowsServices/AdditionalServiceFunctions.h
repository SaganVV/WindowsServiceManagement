#pragma once
#include <Windows.h>
const DWORD cdwTimeout = 30000;
HRESULT WaitForServiceStatus(BSTR serviceName, DWORD dwDesiredState, DWORD dwTimeout);
HRESULT ControlServiceRequest(BSTR serviceName, DWORD dwControlCode);
HRESULT ControlService(BSTR serviceName, DWORD dwControlCode, DWORD dwDesiredState, DWORD dwTimeout);
HRESULT ServiceNamesToSafeArray(LPENUM_SERVICE_STATUS lpServices, DWORD dwServices, SAFEARRAY** pOut);