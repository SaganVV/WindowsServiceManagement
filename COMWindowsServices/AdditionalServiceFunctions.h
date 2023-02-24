#pragma once
#include <Windows.h>

HRESULT WaitForServiceStatus(BSTR serviceName, DWORD dwDesiredState, DWORD dwTimeout);
HRESULT ControlServiceRequest(BSTR serviceName, DWORD dwControlCode);
HRESULT ControlService(BSTR serviceName, DWORD dwControlCode, DWORD dwDesiredState, DWORD dwTimeout);