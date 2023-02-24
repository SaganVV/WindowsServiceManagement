#include <iostream>
#include <windows.h>
#include "../COMWindowsServices/COMWindowsServices_i.h"
#include "../COMWindowsServices/COMWindowsServices_i.c"

int main()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	IServiceHandler* pServiceHandler = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ServiceHandler, NULL, CLSCTX_INPROC_SERVER, IID_IServiceHandler, (void**)&pServiceHandler);
	if (FAILED(hr))
	{
		std::cerr << "CoCreateInstance failed\n" << hr;
        DWORD x;
        std::wcin >> x;
		return -1;
	}
    SAFEARRAY* pServices;
    DWORD dwServicesReturned;

    hr = pServiceHandler->GetServices(&pServices, &dwServicesReturned);
    if (FAILED(hr))
    {
        std::cerr << "GetServices failed\n" << hr;
        DWORD x;
        std::wcin >> x;
        return -1;
    }

    BSTR* pServiceNames;
    hr = SafeArrayAccessData(pServices, (void**)&pServiceNames);
    if (FAILED(hr))
    {

        std::cerr << "SafeArrayAccessData failed\n";
        DWORD x;
        std::wcin >> x;
        return -1;
    }
    DWORD dwCurrentState;
    for (DWORD i = 0; i < dwServicesReturned; i++)
    {
        pServiceHandler->ServiceCurrentState(pServiceNames[i], &dwCurrentState);
        std::wcout << L"Service Name: " << pServiceNames[i] << '\n' << L"Current State: " << dwCurrentState << "\n\n";
    }
    std::cout << dwServicesReturned;
 
    SafeArrayUnaccessData(pServices);
    SafeArrayDestroy(pServices);
    BSTR serviceName = SysAllocString(L"autotimesvc");
    std::wcout << L"Service Name: " << serviceName << '\n';
    hr = pServiceHandler->ServiceCurrentState(serviceName, &dwCurrentState);
    if (FAILED(hr))
    {
        std::cout << "Error: " << hr;
    }
    std::wcout << L"Current State: " << dwCurrentState << '\n';
    std::wcout << L"Start Service" << serviceName;

    hr = pServiceHandler->ServiceStart(serviceName);
   
    if (FAILED(hr))
    {
        std::cout << "saflas" << hr;
    }
    hr = pServiceHandler->ServiceCurrentState(serviceName, &dwCurrentState);
   
    std::wcout << L"Service Name: " << serviceName << '\n';
    std::wcout << L"Current State: " << dwCurrentState << '\n';
 //   pServiceHandler->Release();


    hr = pServiceHandler->ServiceStop(serviceName);

    if (FAILED(hr))
    {
        std::cout << "Error: " << hr;
    }
    hr = pServiceHandler->ServiceCurrentState(serviceName, &dwCurrentState);

    std::wcout << L"Service Name: " << serviceName << '\n';
    std::wcout << L"Current State: " << dwCurrentState << '\n';
    pServiceHandler->Release();

    CoUninitialize();
    DWORD x;
    std::wcin >> x;
    return 0;
}