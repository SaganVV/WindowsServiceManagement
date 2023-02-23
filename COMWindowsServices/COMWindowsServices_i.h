

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Tue Jan 19 05:14:07 2038
 */
/* Compiler settings for COMWindowsServices.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0626 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COMWindowsServices_i_h__
#define __COMWindowsServices_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if _CONTROL_FLOW_GUARD_XFG
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IServiceHandler_FWD_DEFINED__
#define __IServiceHandler_FWD_DEFINED__
typedef interface IServiceHandler IServiceHandler;

#endif 	/* __IServiceHandler_FWD_DEFINED__ */


#ifndef __ServiceHandler_FWD_DEFINED__
#define __ServiceHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class ServiceHandler ServiceHandler;
#else
typedef struct ServiceHandler ServiceHandler;
#endif /* __cplusplus */

#endif 	/* __ServiceHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IServiceHandler_INTERFACE_DEFINED__
#define __IServiceHandler_INTERFACE_DEFINED__

/* interface IServiceHandler */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IServiceHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("476f3c6b-af1f-4ba6-97c1-004c5ad4d4ca")
    IServiceHandler : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetServices( 
            /* [out] */ SAFEARRAY * *pOut,
            /* [out] */ LPDWORD dwServicesReturned) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ServiceStart( 
            /* [in] */ BSTR serviceName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ServiceCurrentState( 
            /* [in] */ BSTR serviceName,
            /* [out][in] */ LPDWORD dwCurrentState) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceHandlerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceHandler * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceHandler * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceHandler * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceHandler * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceHandler * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceHandler * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceHandler * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IServiceHandler, GetServices)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetServices )( 
            IServiceHandler * This,
            /* [out] */ SAFEARRAY * *pOut,
            /* [out] */ LPDWORD dwServicesReturned);
        
        DECLSPEC_XFGVIRT(IServiceHandler, ServiceStart)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ServiceStart )( 
            IServiceHandler * This,
            /* [in] */ BSTR serviceName);
        
        DECLSPEC_XFGVIRT(IServiceHandler, ServiceCurrentState)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ServiceCurrentState )( 
            IServiceHandler * This,
            /* [in] */ BSTR serviceName,
            /* [out][in] */ LPDWORD dwCurrentState);
        
        END_INTERFACE
    } IServiceHandlerVtbl;

    interface IServiceHandler
    {
        CONST_VTBL struct IServiceHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceHandler_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceHandler_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceHandler_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceHandler_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceHandler_GetServices(This,pOut,dwServicesReturned)	\
    ( (This)->lpVtbl -> GetServices(This,pOut,dwServicesReturned) ) 

#define IServiceHandler_ServiceStart(This,serviceName)	\
    ( (This)->lpVtbl -> ServiceStart(This,serviceName) ) 

#define IServiceHandler_ServiceCurrentState(This,serviceName,dwCurrentState)	\
    ( (This)->lpVtbl -> ServiceCurrentState(This,serviceName,dwCurrentState) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServiceHandler_INTERFACE_DEFINED__ */



#ifndef __COMWindowsServicesLib_LIBRARY_DEFINED__
#define __COMWindowsServicesLib_LIBRARY_DEFINED__

/* library COMWindowsServicesLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_COMWindowsServicesLib;

EXTERN_C const CLSID CLSID_ServiceHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("c1f3a32f-8295-4a38-a8fb-487847b61ec9")
ServiceHandler;
#endif
#endif /* __COMWindowsServicesLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


