// pubsdk_link_statement.h

#ifndef _pubsdk_link_statement_h_
#define _pubsdk_link_statement_h_

#if defined(_MSC_VER) && (_MSC_VER > 1000)
	#pragma once
#endif

#ifdef USE_AUTO_EX_LIB
	#ifndef CWALKTCM_DECL
		#define CWALKTCM_DECL
	#endif
	#ifndef CWALKLOG_DECL
		#define CWALKLOG_DECL
	#endif
	#ifndef COMM_DECL
		#define COMM_DECL
	#endif
#endif

#if defined(WIN32)
	#if defined(USE_AUTO_EX_LIB)
		#ifdef __AFX_H__
			#ifdef _DEBUG
				#if defined(USE_DEBUG_STATIC_AUTO_LIB)
					#pragma comment(lib, "CWALKIntelligentMFC_Ex_d.lib")
				#else
					#pragma comment(lib, "CWALKIntelligentMFC_Ex_NoDI.lib")
				#endif
			#else
				#pragma comment(lib, "CWALKIntelligentMFC_Ex.lib")
			#endif
		#else
			#ifdef _DEBUG
				#if defined(USE_DEBUG_STATIC_AUTO_LIB)
					#pragma comment(lib, "CWALKIntelligentSDK_Ex_d.lib")
				#else
					#pragma comment(lib, "CWALKIntelligentSDK_Ex_NoDI.lib")
				#endif
			#else
				#pragma comment(lib, "CWALKIntelligentSDK_Ex.lib")
			#endif
		#endif
	#else
		#ifdef __AFX_H__
			#ifdef _DEBUG
				#if defined(USE_DEBUG_STATIC_AUTO_LIB)
					#pragma comment(lib, "CWALKIntelligentMFC_d.lib")
				#else
					#pragma comment(lib, "CWALKIntelligentMFC_NoDI.lib")
				#endif
			#else
				#pragma comment(lib, "CWALKIntelligentMFC.lib")
			#endif
		#else
			#ifdef _DEBUG
				#if defined(USE_DEBUG_STATIC_AUTO_LIB)
					#pragma comment(lib, "CWALKIntelligentSDK_d.lib")
				#else
					#pragma comment(lib, "CWALKIntelligentSDK_NoDI.lib")
				#endif
			#else
				#pragma comment(lib, "CWALKIntelligentSDK.lib")
			#endif
		#endif

		#if (_MSC_VER <= 1200) // <= VC6.0
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_6d.lib")
				#pragma comment(lib, "cwalklog_6d.lib")
				#pragma comment(lib, "comm_6d.lib")
			#else
				#pragma comment(lib, "cwalktcm_6.lib")
				#pragma comment(lib, "cwalklog_6.lib")
				#pragma comment(lib, "comm_6.lib")
			#endif
		#elif (_MSC_VER == 1500) // VC2008
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_9d.lib")
				#pragma comment(lib, "cwalklog_9d.lib")
				#pragma comment(lib, "comm_9d.lib")
			#else
				#pragma comment(lib, "cwalktcm_9.lib")
				#pragma comment(lib, "cwalklog_9.lib")
				#pragma comment(lib, "comm_9.lib")
			#endif
		#elif (_MSC_VER == 1600) // VC2010
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_10d.lib")
				#pragma comment(lib, "cwalklog_10d.lib")
				#pragma comment(lib, "comm_10d.lib")
			#else
				#pragma comment(lib, "cwalktcm_10.lib")
				#pragma comment(lib, "cwalklog_10.lib")
				#pragma comment(lib, "comm_10.lib")
			#endif
		#elif (_MSC_VER == 1700) // VC2012
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_11d.lib")
				#pragma comment(lib, "cwalklog_11d.lib")
				#pragma comment(lib, "comm_11d.lib")
			#else
				#pragma comment(lib, "cwalktcm_11.lib")
				#pragma comment(lib, "cwalklog_11.lib")
				#pragma comment(lib, "comm_11.lib")
			#endif
		#elif (_MSC_VER == 1800) // VC2013
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_12d.lib")
				#pragma comment(lib, "cwalklog_12d.lib")
				#pragma comment(lib, "comm_12d.lib")
			#else
				#pragma comment(lib, "cwalktcm_12.lib")
				#pragma comment(lib, "cwalklog_12.lib")
				#pragma comment(lib, "comm_12.lib")
			#endif
		#elif (_MSC_VER >= 1900) // VC2015,扩展支持到VS2019版本，但是项目要重定向到VS2015
			#ifdef _DEBUG
				#pragma comment(lib, "cwalktcm_14d.lib")
				#pragma comment(lib, "cwalklog_14d.lib")
				#pragma comment(lib, "comm_14d.lib")
			#else
				#pragma comment(lib, "cwalktcm_14.lib")
				#pragma comment(lib, "cwalklog_14.lib")
				#pragma comment(lib, "comm_14.lib")
			#endif
		#else
			#error "Compiler not supported!"
		#endif
	#endif

	#if (_MSC_VER >= 1500) // >= VC2008
		#pragma comment(linker, "/nodefaultlib:LIBCMT.lib")
	#endif

	#if defined(_DEBUG) && (_MSC_VER <= 1200) // <= VC6.0
		#pragma comment(linker, "/ignore:4099")
	#endif
#endif

#endif	// #ifndef _pubsdk_link_statement_h_
