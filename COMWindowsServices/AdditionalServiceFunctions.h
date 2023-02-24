#pragma once
#include <Windows.h>

HRESULT WaitForServiceStatus(BSTR serviceName, DWORD dwDesiredState, DWORD dwTimeout);