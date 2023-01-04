/// ==========================================================================
///
///			Copyright(C) 云从科技有限公司
///			All rights reserved
///
///
///			filename: CWALKSDKDefines.h
///         description:  DCS宏定义文件
///
///
///			create by ziqiu at 2020-08
///
///			http://www.cloudwalk.com
///
///
/// ==========================================================================

#ifndef _CWALKSDKDefines_h_
#define _CWALKSDKDefines_h_

#if defined(CWALK_SDK_DECL)
	#undef CWALK_SDK_DECL
	#define CWALK_SDK_DECL
#endif

#ifndef CWALK_SDK_DECL
	#ifdef WIN32
		#ifdef CWALK_SDK_EXPORTS
			#define CWALK_SDK_DECL __declspec(dllexport)
		#else
			#define CWALK_SDK_DECL __declspec(dllimport)
		#endif
	#else
		#if defined(__GNUC__) && __GNUC__>=4
			#define CWALK_SDK_DECL	__attribute__((visibility("default")))
		#else
			#define CWALK_SDK_DECL
		#endif
	#endif
#endif

#ifdef __cplusplus
	#define CWALK_SDK_API extern "C" CWALK_SDK_DECL
#else
	#define CWALK_SDK_API CWALK_SDK_DECL
#endif

#ifdef WIN32
	#ifndef CWALK_SDK_CALLBACK
		#define CWALK_SDK_CALLBACK CALLBACK
	#endif
	#ifndef CWALK_SDK_METHOD
		#define CWALK_SDK_METHOD __stdcall
	#endif
#else
	#ifndef CWALK_SDK_CALLBACK
		#define CWALK_SDK_CALLBACK
	#endif
	#ifndef CWALK_SDK_METHOD
		#define CWALK_SDK_METHOD
	#endif
#endif

#ifndef CWALKSDKERROR
	#define CWALKSDKERROR
	
	#include "CWALKSDKErrors.h"
	typedef INT CWALKSDKError;
#endif

#endif // !_CWALKSDKDefines_h_