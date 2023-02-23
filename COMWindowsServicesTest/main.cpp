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
		std::cerr << "CoCreateInstance failed\n";
		return -1;
	}
    SAFEARRAY* pServices;
    DWORD dwServicesReturned;

    hr = pServiceHandler->GetServices(&pServices, &dwServicesReturned);
    if (FAILED(hr))
    {
        std::cerr << "GetServices failed\n" << hr;
        return -1;
    }

    BSTR* pServiceNames;
    hr = SafeArrayAccessData(pServices, (void**)&pServiceNames);
    if (FAILED(hr))
    {
        std::cerr << "SafeArrayAccessData failed\n";
        return -1;
    }

    for (DWORD i = 0; i < dwServicesReturned; i++)
    {
        std::wcout << pServiceNames[i] << '\n';
    }
    std::cout << dwServicesReturned;
    SafeArrayUnaccessData(pServices);
    SafeArrayDestroy(pServices);
    pServiceHandler->Release();

    CoUninitialize();

    return 0;
}