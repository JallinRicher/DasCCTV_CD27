

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for DasCCTV.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_DasCCTVLib,0x81eadac8,0xccad,0x4861,0xb7,0x0a,0xa0,0x7c,0xae,0xce,0x9d,0x20);


MIDL_DEFINE_GUID(IID, DIID__DDasCCTV,0xfb680a1d,0xccae,0x4810,0x86,0xc3,0x24,0x2b,0x8d,0xae,0x9a,0x76);


MIDL_DEFINE_GUID(IID, DIID__DDasCCTVEvents,0x47e08345,0x8e44,0x4ff0,0x84,0xd1,0x97,0x79,0xeb,0x70,0xcb,0x83);


MIDL_DEFINE_GUID(CLSID, CLSID_DasCCTV,0x3f9c045b,0x43db,0x4280,0xb5,0x68,0x52,0x75,0xb0,0xfe,0x52,0xa2);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



