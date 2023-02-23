// dllmain.h : Declaration of module class.

class CCOMWindowsServicesModule : public ATL::CAtlDllModuleT< CCOMWindowsServicesModule >
{
public :
	DECLARE_LIBID(LIBID_COMWindowsServicesLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMWINDOWSSERVICES, "{50150657-f850-49cc-8f8e-780e36172742}")
};

extern class CCOMWindowsServicesModule _AtlModule;
